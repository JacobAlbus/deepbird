import tkinter as tk
from space import Space
from dp_policy_iteration import PolicyIteration

class PolicyIterationFrame:

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
    self.watch_model_play_file_path = tk.StringVar(value="./policies/policy_3.json")

    self.width = width
    self.height = height


  def set_td_sarsa(self, *args):
    # clear frames on each change
    self.continue_from_prev_frame.destroy()
    self.start_from_scratch_frame.destroy()
    self.watch_model_play_frame.destroy()

    if self.options_tracker.get() == "Start From Scratch":
      self.set_start_from_scratch_frame()
    elif self.options_tracker.get() == "Watch Model Play":
      self.set_watch_model_play_frame()

  def set_start_from_scratch_frame(self):
    self.start_from_scratch_frame = tk.Frame(self.main_frame, width=self.width, height=self.height)
    self.start_from_scratch_frame.grid(row=0, column=1, padx=10)

    play_button = tk.Button(self.start_from_scratch_frame, text="Start Train", command=self.start_train)
    play_button.grid(row=1, column=1, pady=10)

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
    state_space = Space((960, 360))
    terminal_state = (999, 999)
    model = PolicyIteration(state_space, terminal_state, change_threshold=0.0005, discount_factor=0.9)
    model.train(epochs=101)

  def watch_play(self):
    state_space = Space((960, 360))
    terminal_state = (999, 999)
    model = PolicyIteration(state_space, terminal_state, change_threshold=0.005, discount_factor=0.9)
    policy_path = self.watch_model_play_file_path.get()
    model.play(policy_path=policy_path)

  def get_main_frame(self):
    return self.main_frame