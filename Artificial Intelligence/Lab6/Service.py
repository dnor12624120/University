from Dataset import Dataset
from DecisionTree import DecisionTree

class Service():
    def __init__(self, dataset):
        self.dataset = dataset

    def run(self):
        training, test = self.dataset.split()
        tree = DecisionTree(training)
        accurate = len([True for entry in test if tree.match(entry) == entry[0]])
        return accurate / len(test)
