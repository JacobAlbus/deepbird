import tkinter as tk
import psutil, subprocess

class InstructionsFrame:

  def __init__(self, parent: tk.Frame, width: int, height: int):
    # Create main frame
    self.main_frame =tk.Frame(parent, width=width, height=height, bg='grey')
    self.main_frame.pack(fill='both', expand=True)

    # Create frames for each option
    text_box1 = tk.Label(self.main_frame, text="Select a tab to see training algorithms")
    text_box1.pack(fill="both")

    text_box2 = tk.Label(self.main_frame, text="OR")
    text_box2.pack(fill="both")

    text_box3 = tk.Label(self.main_frame, text="Press 'Play' below to the play the game yourself")
    text_box3.pack(fill="both")

    play_button = tk.Button(self.main_frame, text="Play", command=self.start_game)
    play_button.pack(expand=True)

  def start_game(self):
    exe_string = r"../x64/Debug/FlappyBird.exe false true"
    process = subprocess.Popen(exe_string, stdout=subprocess.PIPE, stdin=subprocess.PIPE)
    process_util = psutil.Process(pid=process.pid)

  def get_main_frame(self):
    return self.main_frame