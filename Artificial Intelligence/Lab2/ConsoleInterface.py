from Problem import Problem
from State import State
from Utility import generate_empty_list

class Command:
    def __init__(self, desc, func):
        self.desc = desc
        self.func = func

    def run(self):
        self.func()


class ConsoleInterface:
    def __init__(self, service):
        self.menus = {}
        self.running = True
        self.service = service

        self.init_menus()
    
    def init_menus(self):
        self.menus["0"] = Command("0. Exit", self.__exit)
        self.menus["1"] = Command("1. Solve using DFS", self.__depth_first_search)
        self.menus["2"] = Command("2. Solve using Greedy", self.__greedy)

    def print_menu(self):
        [print(v.desc) for (_, v) in self.menus.items()]

    def run(self):
        while self.running:
            self.print_menu()
            user_input = input(">\n")
            try:
                self.validate_input(user_input)
                self.menus[user_input].run()
            except ValueError:
                print("No input entered.")
            except RuntimeError:
                print("Invalid command option.")

    def validate_input(self, user_input):
        if len(user_input) == 0:
            raise ValueError
        if int(user_input) not in range(len(self.menus)):
            raise RuntimeError

    def __exit(self):
        self.running = False

    def __depth_first_search(self):
        print("Trying to solve problem using DFS.")
        n = int(input("Enter board size.\n"))
        try:
            time, sol = self.service.depth_first_search(Problem(State(generate_empty_list(n))))
            print("Solution found in " + str(time) + ".")
            print(sol)
        except ValueError:
            print("Could not find a solution for given board size.")

    def __greedy(self):
        print("Trying to solve problem using greedy BFS.")
        n = int(input("Enter board size.\n"))
        try:
            time, sol = self.service.greedy(Problem(State(generate_empty_list(n))))
            print("Solution found in " + str(time) + ".")
            print(sol)
        except ValueError:
            print("Could not find a solution for given board size.")