import psutil, subprocess
import json
from collections import deque
import os
import signal

class GameEnv:
    
  def __init__(self, exe_string: str, vert_divisons: int, hori_divisions: int, velo_divisions: int):
    """
    Parameters:
      exe_path -- command to run the game
      vert_divisions -- number of divisions in vertical direction (e.g. if screen height is 1000 pixels and n=10 then
                        the vertical state will be divided into 100 pixel intervals)
      hori_divisions -- number of divisions in horizontal direction (e.g. if screen width is 1000 pixels and n=20 then
                        the horizontal state will be divided into 50 pixel intervals)
      velo_divisions -- number of divisions in velocity 
    """

    # start process
    self.process = subprocess.Popen(exe_string, stdout=subprocess.PIPE, stdin=subprocess.PIPE)
    self.process_util = psutil.Process(pid=self.process.pid)

    # grab initial game info from game's output
    self.START_MESSAGE_STR = "*!*!*"
    self.END_MESSAGE_STR = "!*!*!"

    self.stdout_buffer = deque()
    self.__empty_message_buffer__()

    game_info = self.__read_message__()
    
    # Calculate minimum velocity (which is achieved by falling from top of screen to bottom of screen)
    # TODO: figure out closed form solution
    gravity = -1 * int(game_info["gravity"])
    height = int(game_info["max_height"])
    self.MIN_VELO = 0

    seconds_per_frame = 1/60
    while height > 0:
      self.MIN_VELO += gravity * seconds_per_frame
      height += self.MIN_VELO
    
    self.MIN_VELO = int(self.MIN_VELO)

    # set intervals used for calcuating state
    max_velo = int(game_info["player_jump_velo"])
    self.VERT_INTERVAL = int(int(game_info["max_height"]) / vert_divisons)
    self.HORI_INTERVAL = int(int(game_info["max_width"]) / hori_divisions)
    self.VELO_INTERVAL = int((max_velo + abs(self.MIN_VELO)) / velo_divisions)
        
  def reset(self):
    """
    Tells the game to reset. Only works if the current run is terminated (i.e. the bird is dead)
    """
    self.perform_action(2)    

  def perform_action(self, action: int) -> None:
    """
    Writes input to the game, which will be received as action.

    Parameters:
      action -- action to be performed. 0 corresponds to jump, 1 corresponds to nothing, 2 corresponds to reset.
    """
    action = bytes(str(action), 'UTF-8')
    self.process.stdin.write(action)

    END_INPUT = bytes('\n', 'UTF-8')
    self.process.stdin.write(END_INPUT)

    self.process.stdin.flush()
    
  def step(self, action: int) -> dict:
    """
    Performs action and returns resulting state.

    Parameters:
      action -- action to be performed. 0 corresponds to jump, 1 corresponds to nothing, 2 corresponds to reset.
    """
    self.perform_action(action)

    game_state = self.__read_message__()

    height_state = int(game_state["player_height"] / self.VERT_INTERVAL)
    width_state = int(game_state["pipe_distance"] / self.HORI_INTERVAL)
    velo_state = int((game_state["player_velocity"] + abs(self.MIN_VELO)) / self.VELO_INTERVAL)
    state = (height_state, width_state, velo_state)

    reward = self.calculate_reward()
    is_terminated = game_state["is_terminated"]

    return state, reward, is_terminated
  
  def calculate_reward(self) -> float:
    return 0.5
  
  def __read_message__(self) -> dict:
    """
    Reads output of the game and looks for messages which start with START_MESSAGE_STR and end with END_MESSAGE_STR
    """

    # keep reading until we found start of message
    while self.__message_buffer_to_string__() != self.START_MESSAGE_STR:
      new_char = self.__get_next_char__()

      self.message_buffer.popleft()
      self.message_buffer.append(new_char)

    # read until we found end of message
    message = []
    while self.__message_buffer_to_string__() != self.END_MESSAGE_STR:   
      new_char = self.__get_next_char__()

      message.append(new_char)

      self.message_buffer.popleft()
      self.message_buffer.append(new_char)

    # remove end message string from actual message
    for _ in self.message_buffer:
      message.pop()
    
    self.__empty_message_buffer__()

    message = "".join(message)
    print(message)
    return json.loads(message)

  def end_game(self) -> None:
    """
    Ends the game (i.e. kills the proccess)
    """

    os.kill(self.process.pid, signal.SIGTERM)

  def __message_buffer_to_string__(self) -> str:
    """
    Converts message buffer from deque to string and returns
    """
    return "".join(self.message_buffer)
  
  def __empty_message_buffer__(self):
    """
    Sets messsage buffer to default values
    """
    self.message_buffer = deque(' ' * len(self.START_MESSAGE_STR))
  
  def __read_stdout__(self) -> None:
    """
    Reads current output of game and writes to buffer
    """
    output = self.process.stdout.read1().decode("utf-8")
    self.stdout_buffer.extend(output)

  def __get_next_char__(self) -> str:
    """
    Reads and returns a single char from game output
    """
    if len(self.stdout_buffer) == 0:
      self.__read_stdout__()

    return self.stdout_buffer.popleft()