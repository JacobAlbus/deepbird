import psutil, time, subprocess
import sys
import json
from collections import deque
import os
import signal

class GameEnv:
    
  def __init__(self, exe_path: str, start_message_str: str, end_message_str: str):
    assert len(start_message_str) == len(end_message_str)

    self.EXE_PATH = exe_path
    self.START_MESSAGE_STR = start_message_str
    self.END_MESSAGE_STR = end_message_str

    self.reset()
    
  def reset(self):
    self.process = subprocess.Popen(self.EXE_PATH, stdout=subprocess.PIPE, stdin=subprocess.PIPE)
    self.process_util = psutil.Process(pid=self.process.pid)
    # self.process_util.suspend()

    self.stdout_buffer = deque()
    self.__empty_buffer__()

    init_state = self.__read_message__()
    print(init_state)

  def perform_action(self, action: str) -> None:
    action = bytes(str(action), 'UTF-8')
    self.process.stdin.write(action)

    END_INPUT = bytes('\n', 'UTF-8')
    self.process.stdin.write(END_INPUT)

    self.process.stdin.flush()
    
  def get_state(self, action: str) -> dict:
    self.perform_action(action)

    return self.__read_message__()
  
  def __read_message__(self):
    # keep reading until we're given the state
    while self.__buffer_to_string__() != self.START_MESSAGE_STR:
      new_char = self.__get_next_char__()

      self.message_buffer.popleft()
      self.message_buffer.append(new_char)

    # read the state
    state = []
    while self.__buffer_to_string__() != self.END_MESSAGE_STR:   
      new_char = self.__get_next_char__()

      state.append(new_char)

      self.message_buffer.popleft()
      self.message_buffer.append(new_char)
    
    # remove end message string from state string
    for _ in self.message_buffer:
      state.pop()
    
    self.__empty_buffer__()

    state = "".join(state)
    return json.loads(state)

  def end_game(self) -> None:
    os.kill(self.process.pid, signal.SIGTERM)

  def __buffer_to_string__(self) -> str:
    return "".join(self.message_buffer)
  
  def __empty_buffer__(self):
    self.message_buffer = deque('*' * len(self.START_MESSAGE_STR))
  
  # def __read_stdout__(self) -> None:
  #   print("START")
  #   # Start and stop game
  #   self.process_util.resume()
  #   # new_char = self.process.stdout.read(1).decode("utf-8")
  #   time.sleep(1)
  #   self.process_util.suspend()
  #   print("END")

  #   # Add game output to buffer
  #   # self.stdout_buffer.append(new_char)
  #   print("START READ")
  #   new_char = self.process.stdout.read1().decode("utf-8")
  #   self.stdout_buffer.extend(new_char)

  def __get_next_char__(self) -> str:
    return self.process.stdout.read(1).decode("utf-8")
    # if len(self.stdout_buffer) == 0:
      # self.__read_stdout__()

    # return self.stdout_buffer.popleft()