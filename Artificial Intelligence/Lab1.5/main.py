from ConsoleInterface import ConsoleInterface
from SolverService import SolverService
from SudokuSolver import SudokuSolver
from CypherSolver import CypherSolver
from ShapesSolver import ShapesSolver


def main():
    sudoku = SudokuSolver(0, [])
    cypher = CypherSolver("", "", "", "")
    shapes = ShapesSolver()
    ss = SolverService(sudoku, cypher, shapes)
    ci = ConsoleInterface(ss)
    ci.run()
    
    
if __name__ == "__main__":
    main()
