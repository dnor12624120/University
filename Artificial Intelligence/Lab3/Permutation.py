class Permutation():
    def __init__(self, symbols):
        self.size = len(symbols)
        self.symbols = symbols

    def get_symbols(self):
        return self.symbols

    def __str__(self):
        return str(self.symbols)

    def __mul__(self, i):
        return Permutation([x * i for x in self.symbols])

    def __add__(self, other):
        return Permutation([x[0] + x[1] for x in list(zip(self.symbols, other.symbols))])

    def __sub__(self, other):
        return Permutation([x[0] - x[1] for x in list(zip(self.symbols, other.symbols))])
