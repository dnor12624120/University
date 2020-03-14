from random import randint
from math import sqrt
from copy import deepcopy


class SudokuSolver:
    def __init__(self, n, board):
        self.__n = n
        self.__board = board
        if sqrt(n) != int(sqrt(n)):
            raise ValueError

    def find_next_empty(self, board):
        for i in range(0, self.__n):
            for j in range(0, self.__n):
                if board[i][j] == 0:
                    return i, j
        return -1, -1

    @staticmethod
    def is_set(l):
        for x in l:
            if x != 0 and l.count(x) != 1:
                return False
        return True

    def valid(self, board):
        for x in range(0, self.__n):
            r = []
            c = []
            for y in range(0, self.__n):
                r.append(board[x][y])
                c.append(board[y][x])
            if not SudokuSolver.is_set(r) or not SudokuSolver.is_set(c):
                return False

        nr = int(sqrt(self.__n))

        for r in range(0, self.__n, nr):
            for c in range(0, self.__n, nr):
                l = []
                for i in range(r, r + nr):
                    for j in range(c, c + nr):
                        l.append(board[i][j])
                if not SudokuSolver.is_set(l):
                    return False

        return True

    def filled(self, board):
        for i in range(0, self.__n):
            for j in range(0, self.__n):
                if board[i][j] == 0:
                    return False
        return True

    def solve(self, board):
        i, j = self.find_next_empty(board)
        if i == -1:
            if self.valid(board):
                return board
            else:
                return None
        val = randint(1, self.__n)
        copy = deepcopy(board)
        copy[i][j] = val
        return self.solve(copy)
