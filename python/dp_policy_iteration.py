import sys
import json

from collections import defaultdict
from space import Space


class PolicyIteration:

  def __init__(self, state_space: Space, terminal_state: tuple, policy: dict, change_threshold: float, discount_factor: float):
    self.DISCOUNT_FACTOR = discount_factor
    self.STATE_SPACE = state_space
    self.CHANGE_THRESHOLD = change_threshold
    self.TERMINAL_STATE = terminal_state

    self.value_function = defaultdict(int)
    for state in self.STATE_SPACE:
      self.value_function[state] = 50
    self.value_function[self.TERMINAL_STATE] = 0

    self.policy = policy

  def train(self, epochs: int) -> None:
    for index in range(epochs):
      print(f"Epoch {index + 1}")

      self.policy_evaluation()
      print("FINISHED EVALUATING")
      self.policy_improvement()
      print("FINISHED IMPROVING")

      with open(f"policies/policy_{index}.json", "w") as file:
        json.dump(self.policy, file)


  def policy_evaluation(self):
    max_change = sys.maxsize
    index = 0

    while max_change > self.CHANGE_THRESHOLD:
      max_change = 0

      for state in self.STATE_SPACE:
        prev_value = self.value_function[state]

        action = self.policy[str(state)]
        next_state = self.calculate_next_state(state, action)
        reward = self.calculate_reward(next_state) 
        
        self.value_function[state] = reward + (self.DISCOUNT_FACTOR * self.value_function[next_state])
        max_change = max(max_change, abs(prev_value - self.value_function[state]))

      print(f"Finsiehd evaluation {index}")
      index += 1
    
  # PLAYER_HEIGHT_RANGE = 960
  # PIPE_DISTANCE_RANGE = 480
  # PIPE_HEIGHT_RANGE = 360 (150 -> 510)
  # PLAYER_VELOCITY_RANGE = 36 (-31 -> 5)
  # space = (960 / 8, 480 / 6, 360 / 4, 36) = (120, 80, 90, 36)

  def calculate_next_state(self, current_state: tuple, action: int) -> tuple:
    next_state = list(current_state)

    # TODO: make more modular
    # update player_height state
    if current_state[3] > 28:
      next_state[0] -= 3
    elif current_state[3] > 20:
      next_state[0] -= 2
    elif current_state[3] > 8:
      next_state[0] -= 1
    elif current_state[3] > 2 or action == 0:
      next_state[0] = max(next_state[0] + 1, 119)
    
    if next_state[0] < 0:
      return self.TERMINAL_STATE 

    # update pipe_distance state
    next_state[1] = max((next_state[1] + 1), 79)

    # update player_velocity state
    if action == 0:
      next_state[3] = 0
    else:
      next_state[3] = max(35, next_state[3] + 1)

    # Check if we hit terminal state (i.e. player dies)
    player_height = next_state[0] * 8
    pipe1_height = next_state[2] * 4
    pipe2_height = pipe1_height + 300
    pipe_distance = next_state[1] * 6
    if pipe_distance < 200 and ((player_height <= pipe1_height) or (player_height + 50 >= pipe2_height)):
      return self.TERMINAL_STATE 

    return tuple(next_state)

  # TODO: calculate reward using game_env's calculate reward function
  def calculate_reward(self, current_state: tuple) -> tuple:
    if current_state == self.TERMINAL_STATE:
      return 0
    
    return 0.5

  def policy_improvement(self):
    policy_stable = False
    index = 0

    while not policy_stable:
      policy_stable = True

      for state in self.STATE_SPACE:
        old_action = self.policy[str(state)]

        max_action = -1
        max_value = -1
        for action in range(1):
          next_state = self.calculate_next_state(state, action)
          expected_value = self.calculate_reward(next_state) + (self.DISCOUNT_FACTOR * self.value_function[next_state])
          
          if expected_value > max_value:
            max_value = expected_value
            max_action = action
        
        self.policy[str(state)] = max_action

        if max_action != old_action:
          policy_stable = False
    
      print(f"Finsih improvement {index}")
      index +=1