from Matrix import Matrix

class Population():
    def __init__(self, num_matrices, matrix_size):
        self.num_matrices = num_matrices
        self.matrices = [Matrix(matrix_size) for _ in range(self.num_matrices)]

    def get_size(self):
        return self.num_matrices

    def set_matrices(self, matrices):
        self.matrices = matrices

    def get_matrices(self):
        return self.matrices

    def get_fitness_for_all(self):
        return [x.fitness() for x in self.matrices]
    

    