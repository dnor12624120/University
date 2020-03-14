import random


class CypherSolver:
    def __init__(self, word1, word2, op, result):
        self.__word1 = word1
        self.__word2 = word2
        self.__op = op
        self.__result = result
        self.__set = set(word1 + word2 + result)
        self.__map = {}
        self.__ops = { "+" : lambda x, y : x + y, "-" : lambda x, y : x - y, "*" : lambda x, y : x * y, "/" : lambda x, y : x / y}
        if len(self.__set) > 16:
            raise ValueError

    def setmap(self, m):
        self.__map = m

    def reset(self):
        self.__map = {}

    def convert(self, string):
        res = 0
        for i in range(0, len(string)):
            res += (16 ** i) * self.__map[string[i]]
        return res

    def solve(self, k):
        if len(self.__map) == len(self.__set):
            num1 = self.convert(self.__word1)
            num2 = self.convert(self.__word2)
            res = self.convert(self.__result)
            if self.__ops[self.__op](num1, num2) == res and self.__map[self.__result[0]] != 0:
                return self.__map
            return None
        self.__map[list(self.__set)[k]] = random.randint(0, 15)
        return self.solve(k + 1)
