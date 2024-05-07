from td_sarsa import TdSarsa
from dp_policy_iteration import PolicyIteration

# TD Sarsa train code
model = TdSarsa("", False, 0.1, 0.9, 0.01)
model.train()

# TD Sarsa play code (playss the game with the given action value function)
# model = TdSarsa("action_value_functions/action_value_function.json", True, 0.1, 0.9, 0.01)
# model.play()

# Policy Iteration  training code
# state_space = Space((120, 90, 60))
# terminal_state = (999, 999, 999)
# model = PolicyIteration(state_space, terminal_state, initial_policy, change_threshold=0.005, discount_factor=0.9)
# model.train(epochs=101)

# Policy Iteration play code (playss the game with the given action value function)
# state_space = Space((120, 90, 60))
# terminal_state = (999, 999, 999)
# model = PolicyIteration(state_space, terminal_state, initial_policy, change_threshold=0.005, discount_factor=0.9)
# model.train(policy_path="policies/policy.json")