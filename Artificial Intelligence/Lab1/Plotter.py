import matplotlib as plt

class Plotter():
    def __init__(self):
        pass
    
    def plot(self, x, f, linewidth, color):
        count, bins, ignored = plt.hist(x, bins="auto", density=True)
        plt.plot(bins, f, linewidth, color)
        plt.show()