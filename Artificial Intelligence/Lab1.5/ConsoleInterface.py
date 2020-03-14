class Command:
    def __init__(self, desc, func):
        self.__desc = desc
        self.__func = func

    @property
    def desc(self):
        return self.__desc

    @desc.setter
    def desc(self, d):
        self.__desc = d

    @property
    def func(self):
        return self.__func

    @func.setter
    def func(self, f):
        self.__func = f

    def __str__(self):
        return self.__desc
    
    
class ConsoleInterface:
    def run(self):
        while self.__running:
            for c in self.__menu:
                print(c)
            user_input = input(">")
            if int(user_input) < 0 or int(user_input) > len(self.__menu):
                print("Invalid option.")
            else:
                self.__menu[int(user_input)].func()

    def init_menu(self):
        self.__menu.append(Command("0. Exit", self.exit))
        self.__menu.append(Command("1. Solve sudoku", self.solve_sudoku))
        self.__menu.append(Command("2. Solve cypher", self.solve_cypher))
        self.__menu.append(Command("3. Solve shapes", self.solve_shapes))

    def __init__(self, service):
        self.__running = True
        self.__menu = []
        self.__service = service
        self.init_menu()
        self.run()

    def exit(self):
        self.__running = False

    def solve_sudoku(self):
        attempts = int(input("Enter number of attempts.\n"))
        self.__service.solve_sudoku(attempts)

    def solve_cypher(self):
        word1 = input("Enter first word.\n")
        word2 = input("Enter second word.\n")
        op = input("Enter operation (+/-).\n")
        result = input("Enter result.\n")
        attempts = int(input("Enter number of attempts.\n"))
        self.__service.solve_cypher(word1, word2, op, result, attempts)

    def solve_shapes(self):
        attempts = int(input("Enter number of attempts.\n"))
        self.__service.solve_shapes(attempts)
