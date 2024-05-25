from game_env import GameEnv
from space import Space
from collections import defaultdict
from pathlib import Path

import random
import json

class DoubleExpectedSarsa:

  def __init__(self, start_function_path: str, use_starting_value_function: bool, alpha: float, gamma: float, epsilon: float):
    self.alpha = alpha
    self.gamma = gamma
    self.epsilon = epsilon

    if use_starting_value_function:
      with open(start_function_path) as json_file:
        self.action_value_function = json.load(json_file)
    else:
      state_space = Space((120, 90, 60))
      self.action_value_function_a = {}
      self.action_value_function_b = {}
      for state in state_space:
        self.action_value_function_a[str(state)] = {'0': 0, '1': 0}
        self.action_value_function_b[str(state)] = {'0': 0, '1': 0}

  def policy_prob(self, state: str) -> float:
    """
      Returns probability of jumping and resting given state
    """
    jump_value = self.action_value_function_a[state]['0'] + self.action_value_function_b[state]['0']
    rest_value = self.action_value_function_a[state]['1'] + self.action_value_function_b[state]['1']

    greedy_prob = 1 - (self.epsilon / 2)
    if jump_value > rest_value:
      return greedy_prob, 1 - greedy_prob
    else:
      return 1 - greedy_prob, greedy_prob

  def policy(self, state: str) -> tuple:
    """
      Returns selected action, probability of selecting said action, and the other possible action
    """
    jump_prob, rest_prob = self.policy_prob(state)

    if random.uniform(0, 1) < jump_prob:
      return '0', jump_prob, '1'
    else:
      return '1', rest_prob, '0'

  def train(self, starting_save_count: int):
    cmd = r"../x64/Debug/FlappyBird.exe true false"
    self.env = GameEnv(cmd, vert_divisons=120, hori_divisions=60,  pipe_height_divisions=90, velo_divisions=36)

    frame_count = 0
    save_count = starting_save_count

    average_score = 0
    high_score = 0

    while True:

      # initialize state and choose initial action
      prev_state, reward, is_terminated, _ = self.env.step('0')
      prev_state = str(prev_state)
      prev_action, _, _ = self.policy(prev_state)

      update_function_a = True
      game_count = 0

      while not is_terminated:
        # perform action
        state, reward, is_terminated, info = self.env.step(prev_action)
        str_state = str(state)
        action, prob, other_action = self.policy(str_state)

        # update value function
        if update_function_a:
          expected_target = prob * self.action_value_function_b[str_state][action]
          expected_target += (1 - prob) * self.action_value_function_b[str_state][other_action]
          
          td = (reward + (self.gamma * expected_target) - self.action_value_function_a[prev_state][prev_action])
          self.action_value_function_a[prev_state][prev_action] += self.alpha * td

        else:
          expected_target = prob * self.action_value_function_a[str_state][action]
          expected_target += (1 - prob) * self.action_value_function_a[str_state][other_action]

          td = (reward + (self.gamma * expected_target) - self.action_value_function_b[prev_state][prev_action])
          self.action_value_function_b[prev_state][prev_action] += self.alpha * td

        # save state and action
        prev_state = str_state
        prev_action = action

        frame_count += 1
        update_function_a = not update_function_a

      high_score = max(high_score, info["score"])
      average_score = (average_score * game_count) + info["score"]
      game_count += 1
      average_score /= game_count

      self.env.reset()

      if frame_count > 1000000:
        frame_count = 0
        save_count += 1
        print(f"Played for {frame_count: _} frames and {game_count: _} games, average score of {average_score}, high score of {high_score}")
        with open(f"des_action_value_functions/action_value_function_a_{save_count}.json", "w") as file:
            json.dump(self.action_value_function_a, file)
        with open(f"des_action_value_functions/action_value_function_b_{save_count}.json", "w") as file:
            json.dump(self.action_value_function_b, file)

    