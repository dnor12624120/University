import numpy as np


class NormalGenerator():
    def __init__(self):
        pass
    
    def generate(self, mu, sigma, n):
        return np.random.normal(mu, sigma, n)