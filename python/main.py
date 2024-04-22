from game_env import GameEnv
from space import Space
from dp_policy_iteration import PolicyIteration

import json
import random
import time
import sys

state_space = Space((120, 90, 60))
terminal_state = (420, 420, 420)

# initial_policy = {}
# for state in state_space:
#   initial_policy[str(state)] = random.randint(0, 1)

# model = PolicyIteration(state_space, terminal_state, initial_policy, change_threshold=0.005, discount_factor=0.95)

# model.train(epochs=100)

with open('policies/policy_99.json') as json_file:
    policy = json.load(json_file)

cmd = r"../x64/Debug/FlappyBird.exe true"
env = GameEnv(cmd, terminal_state=terminal_state, vert_divisons=120, hori_divisions=60,  pipe_height_divisions=90, velo_divisions=36)

state, reward, is_terminated = env.step(0)

for i in range(100000):
  if is_terminated:
    env.reset()
    is_terminated = False
    state, reward, is_terminated = env.step(0)
  else:
    action = policy[str(state)]
    print(action, state)
    state, reward, is_terminated = env.step(action)

env.end_game()