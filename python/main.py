from game_env import GameEnv
import time

cmd = r"../x64/Debug/FlappyBird.exe true"
env = GameEnv(cmd, vert_divisons=10, hori_divisions=10, velo_divisions=10)

state, reward, is_terminated = env.step(0)

for _ in range(100):
  state, reward, is_terminated = env.step(1)
  print(state)
  time.sleep(0.25)

env.end_game()