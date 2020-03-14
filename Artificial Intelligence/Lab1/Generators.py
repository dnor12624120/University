import numpy as np


class NormalGenerator():
    def __init__(self):
        pass
    
    
    def generate(self, mu, sigma, n):
        return np.random.normal(mu, sigma, n)
    

class BinomialGenerator():
    def __init__(self):
        pass


    def generate(self, N, P, n):
        return np.random.binomial(N, P, n)
    

class GeometricGenerator():
    def __init__(self):
        pass
    
    
    def generate(self, p, n):
        return np.random.geometric(p, n)


class LaplaceGenerator():
    def __init__(self):
        pass
    
    def generate(self, mu, lmbda, n):
        return np.random.laplace(mu, lmbda, n)