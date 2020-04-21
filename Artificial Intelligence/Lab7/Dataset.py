import numpy as np

class Dataset():
    def __init__(self, filepath, num_columns, y_index):
        self.filepath = filepath
        self.num_columns = num_columns
        self.y_index = y_index
        self.load()

    def load(self):
        xs = []
        ys = []
        with open(self.filepath, "r") as f:
            for line in f:
                if line != "\n":
                    split_line = line.split(" ")
                    xs.append([float(val) for val in split_line[:-1]])
                    ys.append(float(split_line[-1]))
        self.xs = np.array(xs)
        self.ys = np.array(ys)
        self.ys.shape = (len(ys), 1)
                    
    