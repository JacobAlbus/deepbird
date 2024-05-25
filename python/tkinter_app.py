import tkinter as tk
from tkinter import ttk

from tkinter_frames.td_sarsa_frame import TdSarsaFrame
from tkinter_frames.instructions_frame import InstructionsFrame
from tkinter_frames.policy_iteration_frame import PolicyIterationFrame
from tkinter_frames.double_expected_sarsa_frame import DoubleExpectedSarsaFrame

width = 600
height = 400

root = tk.Tk()
root.title('DeepBird GUI')
root.geometry(f'{width}x{height}')

# Instantiating the notebook
nbook = ttk.Notebook(root)
nbook.pack(fill="both", expand=True)

policy_iteration_frame = tk.Frame(nbook, width=width, height=height, bg='grey')

# Frame packing
instructions_frame = InstructionsFrame(nbook, width, height)
nbook.add(instructions_frame.get_main_frame(), text="Instructions")

policy_iteration_frame = PolicyIterationFrame(nbook, width, height)
nbook.add(policy_iteration_frame.get_main_frame(), text="Policy Iteration")

td_sarsa_frame = TdSarsaFrame(nbook, width, height)
nbook.add(td_sarsa_frame.get_main_frame(), text="TD Sarsa")

double_expected_sarsa_frame = DoubleExpectedSarsaFrame(nbook, width, height)
nbook.add(double_expected_sarsa_frame.get_main_frame(), text="Double Expected Sarsa")

root.mainloop()