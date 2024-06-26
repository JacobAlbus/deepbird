import tkinter as tk
from double_expected_sarsa import DoubleExpectedSarsa

class DoubleExpectedSarsaFrame:

  def __init__(self, parent: tk.Frame, width: int, height: int):
    # Create main frame
    self.main_frame = tk.Frame(parent, width=width, height=height, bg='grey')
    self.main_frame.pack(expand=True)

    self.create_instructions_text()

    # Create frames for each option
    td_sarsa_algorithms = ['Start From Scratch', 'Continue Training', 'Watch Play']
    self.start_from_scratch_frame = tk.Frame(self.main_frame, width=width, height=height)
    self.continue_training_frame = tk.Frame(self.main_frame, width=width, height=height)
    self.watch_play_frame = tk.Frame(self.main_frame, width=width, height=height)

    self.continue_training_number = tk.StringVar(value="25")
    self.watch_play_model_number = tk.StringVar(value="25")
    
    # Create and track drop down menu
    self.options_tracker = tk.StringVar()
    self.options_tracker.set('Select Options')

    td_sarsa_options = tk.OptionMenu(self.main_frame, self.options_tracker, *td_sarsa_algorithms)
    td_sarsa_options.grid(row=2, column=0, pady=10)

    self.options_tracker.trace_add("write", self.set_td_sarsa)

    self.width = width
    self.height = height

  def create_instructions_text(self):
    instructions_frame = tk.Frame(self.main_frame)
    instructions_frame.grid(row=0, column=0, pady=5)

    text_box1 = tk.Label(instructions_frame, text="All action value functions are saved in the dse_action_value_functions directory")
    text_box1.grid(row=0, column=0)

  def set_td_sarsa(self, *args):
    # clear frames on each change
    self.start_from_scratch_frame.destroy()
    self.continue_training_frame.destroy()
    self.watch_play_frame.destroy()

    if self.options_tracker.get() == "Start From Scratch":
      self.set_start_from_scratch_frame()
    if self.options_tracker.get() == "Continue Training":
      self.set_continue_training_frame()
    if self.options_tracker.get() == "Watch Play":
      self.set_watch_play_frame()

  def set_start_from_scratch_frame(self):
    self.start_from_scratch_frame = tk.Frame(self.main_frame, width=self.width, height=self.height)
    self.start_from_scratch_frame.grid(row=3, column=0, padx=10)

    play_button = tk.Button(self.start_from_scratch_frame, text="Start Train", command=self.start_train)
    play_button.grid(row=1, column=1)

  def set_continue_training_frame(self):
    self.continue_training_frame = tk.Frame(self.main_frame, width=self.width, height=self.height)
    self.continue_training_frame.grid(row=3, column=0, padx=10)

    enter_path_label = tk.Label(self.continue_training_frame, text="Enter Model No.")
    enter_path_label.grid(row=0, column=0)

    enter_path = tk.Entry(self.continue_training_frame, textvariable=self.continue_training_number)
    enter_path.grid(row=0, column=1, pady=10, padx=10)

    play_button = tk.Button(self.continue_training_frame, text="Continue Training", command=self.continue_train)
    play_button.grid(row=1, column=1, pady=10)

  def set_watch_play_frame(self):
    self.watch_play_frame = tk.Frame(self.main_frame, width=self.width, height=self.height)
    self.watch_play_frame.grid(row=3, column=0, padx=10)

    enter_path_label = tk.Label(self.watch_play_frame, text="Enter Model No.")
    enter_path_label.grid(row=0, column=0)

    enter_path = tk.Entry(self.watch_play_frame, textvariable=self.watch_play_model_number)
    enter_path.grid(row=0, column=1, pady=10, padx=10)

    play_button = tk.Button(self.watch_play_frame, text="Watch Play", command=self.watch_play)
    play_button.grid(row=1, column=1, pady=10)

  def start_train(self):
    model = DoubleExpectedSarsa("", use_starting_value_function=False, alpha=0.5, gamma=0.9, epsilon=0.1)
    model.train(0)
  
  def continue_train(self):
    model_number = int(self.continue_training_number.get())
    model = DoubleExpectedSarsa(model_number, use_starting_value_function=True, alpha=0.1, gamma=0.9, epsilon=0.01)
    model.train(model_number)

  def watch_play(self):
    model_number = int(self.watch_play_model_number.get())
    model = DoubleExpectedSarsa(model_number, use_starting_value_function=True, alpha=0.1, gamma=0.9, epsilon=0.01)
    model.play()

  def get_main_frame(self):
    return self.main_frame