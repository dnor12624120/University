from Utility import filter_zeros

"""
    State holds information regarding an NxN chess board
    with queens placed on certain positions, represented by
    a list. A non-zero element of a list indicates that
    a queen can be found on position (row, col) on the board,
    with row being the index of the element and col being
    the element itself.
"""

class State:
    def __init__(self, values):
        self.values = values
        self.size = len(values)

    def is_valid(self):
        # check for queens being placed on the same column 
        # (queens can't be placed on the same row by default)
        if len(set(filter_zeros(self.values))) != len(filter_zeros(self.values)):
            return False
         
        # create a list of tuples (i, v) where v is a non-zero value from values
        # and i is its original index in the list 
        indexed_list = list(zip(range(1, len(self.values) + 1), self.values))
        indexed_list = [(k, v) 
                        for (k, v) in indexed_list 
                        if v != 0]

        # create a list with queens that have been placed on the same (semi) diagonal
        # if the list contains any elements, the state is not valid
        if(len([True
                for (a, b) in indexed_list
                for (c, d) in indexed_list 
                if  abs(a - c) - abs(b - d) == 0 
                    and a != c 
                    and b != d
                ])):
            return False
        return True

    def is_complete(self):
        return len(set(filter_zeros(self.values))) == len(self.values)

    def is_final_solution(self):
        return self.is_valid() and self.is_complete()

    def place_queen(self, col):
        # place a queen on column col on the first free row
        copy = self.values[:]
        copy[self.values.index(0)] = col
        return State(copy)

    def __eq__(self, other):
        return self.values == other.values

    def __str__(self):
        return "".join([(" " * (x - 1)) + ("*" if x != 0 else "") + (" " * (len(self.values) - x - 1)) + '\n' for x in self.values])

