from game_env import GameEnv
from space import Space
from collections import defaultdict
from pathlib import Path

import random
import json

class TdSarsa:

  def __init__(self, start_function_path: str, use_starting_value_function: bool, alpha: float, gamma: float, epsilon: float):
    self.alpha = alpha
    self.gamma = gamma
    self.epsilon = epsilon

    if use_starting_value_function:
      with open(start_function_path) as json_file:
        self.action_value_function = json.load(json_file)
    else:
      state_space = Space((120, 90, 60))
      self.action_value_function = {}
      for state in state_space:
        self.action_value_function[str(state)] = {'0': 0, '1': 0}
      

  def policy(self, state: tuple):
    if random.uniform(0, 1) < self.epsilon:
      return str(random.randint(0, 1))

    str_state = str(state)
    if self.action_value_function[str_state]['0'] > self.action_value_function[str_state]['1']:
      return '0'
  
    return '1'
  
  def train(self, starting_save_count: int):
    cmd = r"../x64/Debug/FlappyBird.exe true false"
    self.env = GameEnv(cmd, vert_divisons=120, hori_divisions=60,  pipe_height_divisions=90, velo_divisions=36)

    frame_count = 0
    save_count = starting_save_count

    while True:

      # initialize state and choose initial action
      prev_state, reward, is_terminated, _ = self.env.step('0')
      prev_state = str(prev_state)
      prev_action = self.policy(prev_state)

      while not is_terminated:
        state, reward, is_terminated, _ = self.env.step(prev_action)
        action = self.policy(state)

        td = (reward + (self.gamma * self.action_value_function[str(state)][action]) -  self.action_value_function[prev_state][prev_action])
        self.action_value_function[prev_state][prev_action] += self.alpha * td

        prev_state = str(state)
        prev_action = action

        frame_count += 1

      self.env.reset()

      if frame_count > 1000000:
        frame_count = 0
        save_count += 1
        with open(f"action_value_functions/action_value_function_{save_count}.json", "w") as file:
            json.dump(self.action_value_function, file)
  
  def play(self):
    cmd = r"../x64/Debug/FlappyBird.exe true true"
    self.env = GameEnv(cmd, vert_divisons=120, hori_divisions=60,  pipe_height_divisions=90, velo_divisions=36)
    self.epsilon = 0

    while True:

      # initialize state and choose initial action
      prev_state, _, is_terminated, _ = self.env.step('0')
      action = self.policy(prev_state)

      while not is_terminated:
        state, _, is_terminated, _ = self.env.step(action)
        action = self.policy(state)

      self.env.reset()

  def play_with_statistics(self, save_path: str, max_frame_count: int):
    cmd = r"../x64/Debug/FlappyBird.exe true false"
    self.env = GameEnv(cmd, vert_divisons=120, hori_divisions=60,  pipe_height_divisions=90, velo_divisions=36)
    self.epsilon = 0

    scores = []
    visited_states = defaultdict(int)

    frame_count = 0
    while frame_count < max_frame_count:

      # initialize state and choose initial action
      prev_state, _, is_terminated, info = self.env.step('0')
      action = self.policy(prev_state)

      while not is_terminated:
        state, _, is_terminated, info = self.env.step(action)
        action = self.policy(state)

        frame_count += 1
        visited_states[str(state)] += 1

      scores.append(info["score"])
      self.env.reset()

    # First creates directory if doesn't exist, then writes
    file = Path(f"{save_path}/scores.txt")
    file.parent.mkdir(parents=True, exist_ok=True)
    file.write_text(str(scores))

    with open(f"{save_path}/visited_states.json", "w") as file:
      json.dump(visited_states, file)

    self.env.end_game()
    