import tkinter as tk
from td_sarsa import TdSarsa

class TdSarsaFrame:

  def __init__(self, parent: tk.Frame, width: int, height: int):
    # Create main frame
    self.main_frame = tk.Frame(parent, width=width, height=height, bg='grey')
    self.main_frame.pack(fill='both', expand=True)

    # Create frames for each option
    td_sarsa_algorithms = ['Start From Scratch', 'Continue From Prev', 'Watch Model Play']
    self.start_from_scratch_frame = tk.Frame(self.main_frame, width=width, height=height)
    self.continue_from_prev_frame = tk.Frame(self.main_frame, width=width, height=height)
    self.watch_model_play_frame = tk.Frame(self.main_frame, width=width, height=height)

    # Create and track drop down menu
    self.options_tracker = tk.StringVar()
    self.options_tracker.set('Select Options')

    td_sarsa_options = tk.OptionMenu(self.main_frame, self.options_tracker, *td_sarsa_algorithms)
    td_sarsa_options.grid()

    self.options_tracker.trace_add("write", self.set_td_sarsa)

    # Paths to action value function file
    self.continue_from_prev_file_path = tk.StringVar(value="./action_value_functions/action_value_function_1874.json")
    self.watch_model_play_file_path = tk.StringVar(value="./action_value_functions/action_value_function.json")

    self.width = width
    self.height = height


  def set_td_sarsa(self, *args):
    # clear frames on each change
    self.continue_from_prev_frame.destroy()
    self.start_from_scratch_frame.destroy()
    self.watch_model_play_frame.destroy()

    if self.options_tracker.get() == "Start From Scratch":
      self.set_start_from_scratch_frame()
    elif self.options_tracker.get() == "Continue From Prev":
      self.set_continue_from_prev_frame()
    elif self.options_tracker.get() == "Watch Model Play":
      self.set_watch_model_play_frame()

  def set_start_from_scratch_frame(self):
    self.start_from_scratch_frame = tk.Frame(self.main_frame, width=self.width, height=self.height)
    self.start_from_scratch_frame.grid(row=0, column=1, padx=10)

    play_button = tk.Button(self.start_from_scratch_frame, text="Start Train", command=self.start_train)
    play_button.grid(row=1, column=1, pady=10)

  def set_continue_from_prev_frame(self):
    self.continue_from_prev_frame = tk.Frame(self.main_frame, width=self.width, height=self.height)
    self.continue_from_prev_frame.grid(row=0, column=1, sticky="ew", padx=10)

    enter_path_label = tk.Label(self.continue_from_prev_frame, text="Enter Path to Model")
    enter_path_label.grid(row=0, column=0, sticky="ew")

    enter_path = tk.Entry(self.continue_from_prev_frame, textvariable=self.continue_from_prev_file_path)
    enter_path.grid(row=0, column=1, sticky="ew", columnspan=4, pady=10, padx=10)

    play_button = tk.Button(self.continue_from_prev_frame, text="Continue Training", command=self.continue_train)
    play_button.grid(row=1, column=1, sticky="ew", pady=10)

  def set_watch_model_play_frame(self):
    self.watch_model_play_frame = tk.Frame(self.main_frame, width=self.width, height=self.height)
    self.watch_model_play_frame.grid(row=0, column=1, padx=10)

    enter_path_label = tk.Label(self.watch_model_play_frame, text="Enter Path to Model")
    enter_path_label.grid(row=0, column=0)

    enter_path = tk.Entry(self.watch_model_play_frame, textvariable=self.watch_model_play_file_path)
    enter_path.grid(row=0, column=1, pady=10, padx=10)

    play_button = tk.Button(self.watch_model_play_frame, text="Watch Play", command=self.watch_play)
    play_button.grid(row=1, column=1, pady=10)

  def start_train(self):
    model = TdSarsa("", use_starting_value_function=False, alpha=0.1, gamma=0.9, epsilon=0.05)
    model.train()

  def continue_train(self):
    starting_action_value_function_path = self.continue_from_prev_file_path.get()
    model = TdSarsa(starting_action_value_function_path, use_starting_value_function=True, alpha=0.1, gamma=0.9, epsilon=0.01)
    model.train()

  def watch_play(self):
    starting_action_value_function_path = self.watch_model_play_file_path.get()
    model = TdSarsa(starting_action_value_function_path, use_starting_value_function=True, alpha=0.1, gamma=0.9, epsilon=0.01)
    model.play()

  def get_main_frame(self):
    return self.main_frame