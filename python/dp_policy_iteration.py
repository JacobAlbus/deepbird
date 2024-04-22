import sys
import json
import time

from collections import defaultdict
from space import Space


class PolicyIteration:

  def __init__(self, state_space: Space, terminal_state: tuple, policy: dict, change_threshold: float, discount_factor: float):
    self.DISCOUNT_FACTOR = discount_factor
    self.STATE_SPACE = state_space
    self.CHANGE_THRESHOLD = change_threshold
    self.TERMINAL_STATE = terminal_state

    self.value_function = {}
    for state in self.STATE_SPACE:
      self.value_function[str(state)] = 0
    self.value_function[str(self.TERMINAL_STATE)] = 0

    self.policy = policy

  def train(self, epochs: int) -> None:
    for index in range(epochs):

      start_time = time.time()

      self.policy_evaluation(index)
      self.policy_improvement(index)

      print(f"FINISHED Epoch {index}, Time: {time.time()-start_time}")

      if index % 10 == 0:
        with open(f"policies/policy_{index}.json", "w") as file:
          json.dump(self.policy, file)
        with open(f"policies/value_function_{index}.json", "w") as file:
          json.dump(self.value_function, file)

    with open(f"policies/policy_{index}.json", "w") as file:
      json.dump(self.policy, file)

  def policy_evaluation(self, num_epoch: int):
    max_change = sys.maxsize
    index = 0

    while max_change > self.CHANGE_THRESHOLD:
      max_change = 0

      for state in self.STATE_SPACE:
        prev_value = self.value_function[str(state)]

        action = self.policy[str(state)]
        next_state = self.calculate_next_state(state, action)
        reward = self.calculate_reward(next_state) 
        
        self.value_function[str(state)] = reward + (self.DISCOUNT_FACTOR * self.value_function[str(next_state)])
        max_change = max(max_change, abs(prev_value - self.value_function[str(state)]))

      index += 1
      if index % 10 == 0:
        print(f"Finsiehd evaluation {index}, for epoch {num_epoch}")
    
  # PLAYER_HEIGHT_RANGE = 960
  # PIPE_HEIGHT_RANGE = 360 (150 -> 510)
  # PIPE_DISTANCE_RANGE = 480
  # space = (960 / 8, 360 / 4, 480 / 8) = (120, 90, 60)

  def calculate_next_state(self, current_state: tuple, action: int) -> tuple:
    next_state = list(current_state)

    next_state[2] = max(next_state[2] - 2, 0)

    # TODO: make more modular
    # update player_height state
    if action == 0:
      next_state[0] = min(next_state[0] + 1, self.STATE_SPACE.shape[0] - 1)
    else:
      next_state[0] = max(next_state[0] - 3, 0)

    if next_state[0] <= 0:
      return self.TERMINAL_STATE 

    # Check if we hit terminal state (i.e. player dies)
    player_height = next_state[0] * 8
    pipe1_height = (next_state[1] * 4) + 150
    pipe2_height = pipe1_height + 300
    pipe_distance = next_state[2] * 8
    if pipe_distance < 200 and ((player_height <= pipe1_height) or (player_height + 60 >= pipe2_height)):
      return self.TERMINAL_STATE 

    return tuple(next_state)

  # TODO: calculate reward using game_env's calculate reward function
  def calculate_reward(self, state: tuple) -> tuple:
    if state == self.TERMINAL_STATE:
      return -100
    
    # Check if player is between pipes
    player_height = state[0] * 8
    pipe1_height = (state[1] * 4) + 150
    pipe2_height = pipe1_height + 300
    pipe_distance = state[2] * 8
    if pipe_distance < 200 and (player_height - 10) > pipe1_height and (player_height + 70) < pipe2_height:
      return 50
    
    # Penalize  player for not being level with pipe opening
    reward = 40
    if player_height < pipe1_height:
      reward -= 0.1 * (pipe1_height + 10 - player_height)
    elif player_height + 70 > pipe2_height:
      reward -= 0.1 * (player_height + 80 - pipe2_height)

    return reward

  def policy_improvement(self, num_epoch: int):
    policy_stable = False
    index = 0

    while not policy_stable:
      policy_stable = True

      for state in self.STATE_SPACE:
        old_action = self.policy[str(state)]

        max_action = -1
        max_value = -sys.maxsize
        for action in range(2):
          next_state = self.calculate_next_state(state, action)
          expected_value = self.calculate_reward(next_state) + (self.DISCOUNT_FACTOR * self.value_function[str(next_state)])
          
          if expected_value > max_value:
            max_value = expected_value
            max_action = action
        
        self.policy[str(state)] = max_action

        if max_action != old_action:
          policy_stable = False
    
      index += 1
      if index % 10 == 0:
        print(f"Finsiehd Improvement {index}, for epoch {num_epoch}")