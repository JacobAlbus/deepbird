from game_env import GameEnv
from space import Space
from dp_policy_iteration import PolicyIteration

import json
import random
import time

state_space = Space((120, 80, 90, 36))
terminal_state = (121, 80, 90, 36)

# with open('policies/initial_policy.json') as json_file:
#     initial_policy = json.load(json_file)

# model = PolicyIteration(state_space, terminal_state, initial_policy, change_threshold=1.1, discount_factor=0.9)

# model.train(epochs=100)

# with open('policies/policy_99.json') as json_file:
#     policy = json.load(json_file)

start_time = time.time()

policy = {}

for state in state_space:
    player_height = state[0] * 8
    pipe1_height = (state[2] * 4) + 150
    if (player_height - pipe1_height) < 30:
        policy[state] = 0
    else:
       policy[state] = 1

print(f"Time to create policy: {time.time() - start_time}")

cmd = r"../x64/Debug/FlappyBird.exe true"
env = GameEnv(cmd, vert_divisons=120, hori_divisions=80,  pipe_height_divisions=90, velo_divisions=36)


state, reward, is_terminated = env.step(0)

while True:
  if is_terminated:
    env.reset()
    is_terminated = False
  else:
    try:
      action = policy[state]
    except KeyError:
      action = random.randint(0, 1)
      print(f"KeyError: {state}")
    state, reward, is_terminated = env.step(action)

env.end_game()