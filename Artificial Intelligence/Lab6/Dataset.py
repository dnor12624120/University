import numpy as np
from random import sample
import string

'''
    The class loads a list of entries for which the first element is the class label,
    and the rest (nc - 1) are attribute values (separated by separator) from the specified filepath.
    These entries will be split into a training set and a test set according to the given percentage (training_p)
'''

class Dataset():
    def __init__(self, filepath, training_p, nc, separator):
        self.filepath = filepath
        self.training_p = training_p
        self.separator = separator
        self.set = []
        self.load()
        self.balance_labels = list(set(entry[0] for entry in self.set))

    def load(self):
        with open(self.filepath) as f:
            for line in f:
                split_line = line.strip().split(self.separator)
                # convert numeric labels into ints
                self.set.append([label if label.isalpha() else int(label) for label in split_line])

    def split(self):
        test_size = int(len(self.set) * (1 - self.training_p)) # actual number of test entries
        test_data = sample(self.set, test_size)
        training_data = self.get_training_data(test_data)
        return training_data, test_data

    def get_training_data(self, test_data):
        # training data means entries that are not in test_data
        return [entry for entry in self.set if entry not in test_data]

