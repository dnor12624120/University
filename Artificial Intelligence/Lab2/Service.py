from Problem import Problem
from State import State
import timeit

class Service:
    def __init__(self):
        self.computed_final_states = {}

    def __depth_first_search(self, problem):
        states = [problem.initial_state]

        while not states[0].is_final_solution():
            current_state = states.pop(0)
            states = problem.expand(current_state) + states

        self.computed_final_states[states[0].size] = states[0]
        return states[0]

    def __greedy(self, problem):
        state_size = problem.initial_state.size
        if state_size not in self.computed_final_states:
            self.depth_first_search(problem)

        final_state = self.computed_final_states[state_size]
        states = [problem.initial_state]
        
        while states[0] != final_state:
            current_state = states.pop(0)
            states += problem.expand(current_state)
            states.sort(key = lambda s : problem.heuristic(s, final_state))

        return states[0]

    def depth_first_search(self, problem):
        start = timeit.default_timer()
        state = self.__depth_first_search(problem)
        end = timeit.default_timer()
        return end - start, state

    def greedy(self, problem):
        start = timeit.default_timer()
        state = self.__greedy(problem)
        end = timeit.default_timer()
        return end - start, state

