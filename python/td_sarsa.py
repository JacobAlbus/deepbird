from game_env import GameEnv
from space import Space
from collections import defaultdict
from pathlib import Path
from time import perf_counter

import random
import json
import sys
import numpy as np

class TdSarsa:

  def __init__(self, start_function_path: str, use_starting_value_function: bool, n_steps: int, alpha: float, gamma: float, epsilon: float):
    self.alpha = alpha
    self.gamma = gamma
    self.epsilon = epsilon
    self.n_steps = n_steps

    if use_starting_value_function:
      with open(start_function_path) as json_file:
        self.action_value_function = json.load(json_file)
    else:
      state_space = Space((120, 90, 80))
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
    self.env = GameEnv(cmd, vert_divisons=120, hori_divisions=80,  pipe_height_divisions=90, velo_divisions=36)

    frame_count = 0
    save_count = starting_save_count

    average_score = 0
    high_score = 0
    game_count = 0
    discount_factors = np.array([self.gamma**i for i in range(self.n_steps)])

    start_time = perf_counter()

    while True:

      # initialize state and choose initial action
      state, reward, is_terminated, info = self.env.step('0')
      state = str(state)
      action = self.policy(state)

      T = sys.maxsize
      time_step = 0
      tau = 0

      actions = [action]
      rewards = []
      states = [state]

      # keep going until the state we're updating is the terminal state
      while tau < T:

        # Only run simulation until we hit terminal state, at which point
        # we keep updating remaining state-action pairs        
        if not is_terminated:
          state, reward, is_terminated, info = self.env.step(action)
          states.append(str(state))
          rewards.append(reward)

          if is_terminated:
            T = time_step + 1
          else:
            action = self.policy(state)
            actions.append(action)
        
        # Only update state-action pairs if we have enough future rewards
        tau = time_step - self.n_steps + 1
        if tau >= 0 and tau < T:
            reward_limit = min(T, self.n_steps + tau)
            discounted_rewards = np.array(rewards[tau:reward_limit]) * discount_factors[:(reward_limit - tau)]
            G = np.sum(discounted_rewards)

            # no need to boostrap if our future rewards extends until termination
            if (tau + self.n_steps) < T:
              nth_state = states[tau + self.n_steps]
              nth_action = actions[tau + self.n_steps]
              G += (self.gamma ** self.n_steps) * self.action_value_function[nth_state][nth_action]
            
            update_state = states[tau]
            update_action = actions[tau]
            td = G - self.action_value_function[update_state][update_action]
            self.action_value_function[update_state][update_action] += self.alpha * td

        time_step += 1

      frame_count += time_step
      high_score = max(high_score, info["score"])
      average_score = (average_score * game_count) + info["score"]
      game_count += 1
      average_score /= game_count

      self.env.reset()

      if frame_count > 1000000:
        print(f"Writing model #{save_count}, time elapsed: {perf_counter() - start_time}")
        print(f"Played {game_count: _} games, average score of {average_score}, high score of {high_score}")
        frame_count = 0
        save_count += 1
        game_count = 0
        average_score = 0
        high_score = 0
        with open(f"td_sarsa_functions3/action_value_function_{save_count}.json", "w") as file:
            json.dump(self.action_value_function, file)
  
  def play(self):
    cmd = r"../x64/Debug/FlappyBird.exe true true"
    self.env = GameEnv(cmd, vert_divisons=120, hori_divisions=80,  pipe_height_divisions=90, velo_divisions=36)
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
    self.env = GameEnv(cmd, vert_divisons=120, hori_divisions=80,  pipe_height_divisions=90, velo_divisions=36)
    self.epsilon = 0

    scores = []
    death_states = []
    visited_states = defaultdict(int)

    frame_count = 0
    while frame_count < max_frame_count:

      # initialize state and choose initial action
      prev_state, _, is_terminated, info = self.env.step('0')
      action = self.policy(prev_state)

      state = None
      prev_score = -1

      while not is_terminated:
        prev_state = state

        state, _, is_terminated, info = self.env.step(action)
        action = self.policy(state)

        frame_count += 1
        visited_states[str(state)] += 1

        # keep track of pipe height before we transition to next set of pipes
        if prev_score != info["score"]:
          prev_score = info["score"]
          prev_death_state = prev_state

      death_states.append((prev_death_state, state))
      scores.append(info["score"])
      self.env.reset()

    # First creates directory if doesn't exist, then writes
    file = Path(f"{save_path}/scores.txt")
    file.parent.mkdir(parents=True, exist_ok=True)
    file.write_text(str(scores))

    file = Path(f"{save_path}/death_states.txt")
    file.parent.mkdir(parents=True, exist_ok=True)
    file.write_text(str(death_states))

    with open(f"{save_path}/visited_states.json", "w") as file:
      json.dump(visited_states, file)

    self.env.end_game()
    