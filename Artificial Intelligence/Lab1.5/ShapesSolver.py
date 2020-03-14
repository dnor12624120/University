from copy import deepcopy
from random import randint


class Shape:
    def __init__(self, n, m, board):
        self.n = n
        self.m = m
        self.board = board


class ShapesSolver:
    def __init__(self):
        self.__n = 5
        self.__m = 6
        self.__board = [[0 for _ in range(self.__m)] for _ in range(self.__n)]
        self.__shapes = []
        self.__shapes.append(Shape(1, 4, [[1, 1, 1, 1]]))
        self.__shapes.append(Shape(2, 3, [[1, 0, 1], [1, 1, 1]]))
        self.__shapes.append(Shape(2, 3, [[1, 0, 0], [1, 1, 1]]))
        self.__shapes.append(Shape(2, 3, [[0, 0, 1], [1, 1, 1]]))
        self.__shapes.append(Shape(2, 3, [[0, 1, 0], [1, 1, 1]]))

    def get_board(self):
        return self.__board

    def get_empty_board(self):
        return [[0 for _ in range(self.__m)] for _ in range(self.__n)]

    def next_free(self):
        for i in range(self.__n):
            for j in range(self.__m):
                if self.__board[i][j] == 0:
                    return i, j
        return -1, -1

    def can_place(self, shape, board, x, y):
        if x + shape.n > self.__n or y + shape.m > self.__m:
            return False
        for i in range(shape.n):
            for j in range(shape.m):
                if board[i + x][j + y] == 1 and shape.board[i][j] == 1:
                    return False
        return True

    def place(self, shape, board, x, y):
        copy = deepcopy(board)
        for i in range(shape.n):
            for j in range(shape.m):
                if i + x < self.__n and j + y < self.__m:
                    copy[i + x][j + y] = shape.board[i][j]
        return copy

    def solve(self, n, shapes, board):
        if n == len(self.__shapes):
            return board

        x = randint(0, len(shapes) - 1)
        while shapes[x] == -1:
            x = randint(0, len(shapes) - 1)
        i = randint(0, self.__n - 1)
        j = randint(0, self.__m - 1)
        if self.can_place(self.__shapes[x], board, i, j):
            copy = self.place(self.__shapes[x], board, i, j)
            shapes[x] = -1
            return self.solve(n + 1, shapes, copy)
        else:
            return None

