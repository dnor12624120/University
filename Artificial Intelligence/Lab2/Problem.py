from State import State
from Utility import filter_zeros

class Problem:
    def __init__(self, initial_state):
        self.initial_state = initial_state
        self.final_state = None
        self.current_states = [initial_state]
        self.invalid_problems = [2, 3] # there are no solutions for boards of size 2 and 3
        if self.initial_state.size in self.invalid_problems:
            raise ValueError

    def set_final_state(self, final_state):
        self.final_state = final_state

    # returns all valid possible states that follow from a given state
    def expand(self, state):
        expanded_states = []
        if state.is_complete():
            return []
        for i in range(1, state.size + 1):
            new_state = state.place_queen(i)
            if new_state.is_valid():
                expanded_states.append(new_state)
        return expanded_states

    # the heuristic function is represented by the absolute difference between the positions of queens on all rows
    def heuristic(self, state, final_state):
        return sum([abs(c - f) for (c, f) in zip(state.values, final_state.values)])

