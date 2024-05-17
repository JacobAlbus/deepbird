import tkinter as tk
from tkinter import ttk

from tkinter_frames.td_sarsa_frame import TdSarsaFrame
from tkinter_frames.instructions_frame import InstructionsFrame

width = 600
height = 300

root = tk.Tk()
root.title('DeepBird GUI')
root.geometry(f'{width}x{height}')

# Instantiating the notebook
nbook = ttk.Notebook(root)
nbook.pack()

policy_iteration_frame = tk.Frame(nbook, width=width, height=height, bg='grey')

# Frame packing
instructions_frame = InstructionsFrame(nbook, width, height)
nbook.add(instructions_frame.get_main_frame(), text="Instructions")

policy_iteration_frame.pack(fill='both', expand=1)
nbook.add(policy_iteration_frame, text="Policy Iteration")

td_sarsa_frame = TdSarsaFrame(nbook, width, height)
nbook.add(td_sarsa_frame.get_main_frame(), text="TD Sarsa")

root.mainloop()