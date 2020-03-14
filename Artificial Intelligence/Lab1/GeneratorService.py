import matplotlib.pyplot as plt
import numpy as np
import scipy.special


class GeneratorService():
    def __init__(self, generators):
        self.__generators = generators

        
    def showNormal(self, mu, sigma, n):
        x = self.__generators["normal"].generate(mu, sigma, n)
        count, bins, ignored = plt.hist(x, bins=50, density=True)
        plt.plot(bins, 1/(sigma * np.sqrt(2 * np.pi)) * np.exp( - (bins - mu)**2 / (2 * sigma**2) ), linewidth=2, color='r')
        plt.show()
        

    def showBino(self, N, P, n):
        x = self.__generators["bino"].generate(N, P, n)
        count, bins, ignored = plt.hist(x, bins=50, density=True)
        plt.plot(bins, scipy.special.comb(N, bins) * (P ** bins) * ((1 - P) ** (N - bins)), linewidth=2, color='r')
        plt.show()
        
    
    def showGeo(self, p, n):
        x = self.__generators["geo"].generate(p, n)
        count, bins, ignored = plt.hist(x, bins=20, density=True)
        plt.plot(bins, (1 - p) ** (bins - 1) * p, linewidth=2, color='r')
        plt.show()
        
    
    def showLaplace(self, mu, lmbda, n):
        x = self.__generators["laplace"].generate(mu, lmbda, n)
        count, bins, ignored = plt.hist(x, bins=30, density=True)
        plt.plot(bins, np.exp(-abs(bins - mu) / lmbda) / (2. * lmbda), linewidth=2, color='r')
        plt.show()