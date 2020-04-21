import numpy as np


class Service():
    def __init__(self, dataset):
        self.dataset = dataset
        self.calculate_beta_coeff()
        
    def calculate_beta_coeff(self):
        # Calculate beta coefficients according to formula
        # beta = inv(transpose(X) * X) * transpose(X) * Y
        
        # prepend column of 1s to X for the formula to work
        ones = np.array([1] * len(self.dataset.xs))
        ones.shape = (len(self.dataset.xs), 1)
        xs = np.hstack((ones, self.dataset.xs))

        self.beta_coeff = np.dot(np.linalg.inv(np.dot(np.transpose(xs), xs)), np.dot(np.transpose(xs), self.dataset.ys))
        
    def predict(self, entry):
        return sum([x[0] * x[1] for x in list(zip(entry, self.beta_coeff[1:]))]) + self.beta_coeff[0]