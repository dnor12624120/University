from SudokuSolver import SudokuSolver
from CypherSolver import CypherSolver


class SolverService:
    def __init__(self, sudoku_solver, cypher_solver, shapes_solver):
        self.__sudoku_solver = sudoku_solver
        self.__cypher_solver = cypher_solver
        self.__shapes_solver = shapes_solver

    def read_board(self):
        f = open("sudoku.txt", "r")
        n = int(f.read(1))
        board = [[0 for x in range(n)] for y in range(n)]
        f.read(1)
        for i in range(0, n):
            for j in range(0, n):
                board[i][j] = int(f.read(1))
            f.read(1)
        return n, board

    def solve_sudoku(self, attempts):
        n, board = self.read_board()
        try:
            self.__sudoku_solver = SudokuSolver(n, board)
            found = False
            sol = None
            for i in range(0, attempts):
                sol = self.__sudoku_solver.solve(board)
                if sol is not None:
                    found = True
                    break
            if not found:
                print("No solution could be found in ", str(attempts), " attempts.")
            else:
                print("Found solution:\n")
                for l in sol:
                    print(l)
        except ValueError:
            print("n is not a square number.")

    def solve_cypher(self, word1, word2, op, result, attempts):
        self.__cypher_solver = CypherSolver(word1, word2, op, result)
        found = False
        sol = None
        for i in range(0, attempts):
            sol = self.__cypher_solver.solve(0)
            if sol is not None:
                found = True
                break
            self.__cypher_solver.reset()
        if not found:
            print("No solution could be found in ", str(attempts), " attempts.")
        else:
            print("Found solution:\n")
            print(sol)

    def solve_shapes(self, attempts):
        found = False
        sol = None
        for i in range(0, attempts):
            sol = self.__shapes_solver.solve(0, list(range(5)), self.__shapes_solver.get_empty_board())
            if sol is not None:
                found = True
                break

        if not found:
            print("No solution could be found in ", str(attempts), " attempts.")
        else:
            print("Found solution:\n")
            for l in sol:
                print(l)
