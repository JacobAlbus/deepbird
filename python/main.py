from game_env import GameEnv
import time
import psutil, time, subprocess
import os
import signal

# cmd = r"../x64/Debug/FlappyBird.exe true"

# process = subprocess.Popen(cmd, stdout=subprocess.PIPE)
# process_util = psutil.Process(pid=process.pid)

# # time.sleep(3)
# print(process.stdout.read1().decode("utf-8"))
# # time.sleep(3)

# # process_util.suspend()
# # os.kill(process.pid, signal.SIGTERM)

cmd = r"../x64/Debug/FlappyBird.exe true"

env = GameEnv(cmd, "*!*!*", "!*!*!")

for _ in range(10):
  state = env.get_state(0)
  print(state)
  time.sleep(0.25)

for _ in range(30):
  state = env.get_state(1)
  print(state)
  time.sleep(0.25)

env.end_game()