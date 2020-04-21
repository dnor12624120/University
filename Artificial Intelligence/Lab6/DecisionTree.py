from Utility import best_split, get_dominant_label
from Dataset import Dataset

class Node():
    def __init__(self, column, label, left_split, right_split):
        self.column = column 
        self.label = label
        self.left_split = left_split
        self.right_split = right_split
        self.left_child = None
        self.right_child = None

class DecisionTree():
    def __init__(self, training_data):
        self.training_data = training_data
        self.root = Node(*best_split(training_data))
        DecisionTree.build(self.root)
        
    @staticmethod
    def build(current_node):
        # if either list is empty it means we can no longer split, so we'll create an end node
        # with the most dominant label from the 2 current splits
        if not current_node.left_split or not current_node.right_split:
            current_node.left_child = current_node.right_child = get_dominant_label(current_node)
            return
        # split on left side
        current_node.left_child = Node(*best_split(current_node.left_split))
        DecisionTree.build(current_node.left_child)   
        # split on right side    
        current_node.right_child = Node(*best_split(current_node.right_split))
        DecisionTree.build(current_node.right_child)    

    def match(self, entry):
        # Return the tree's predicition for the entry
        current_node = self.root
        while True:
            if entry[current_node.column] < current_node.label:
                if type(current_node.left_child) == str:
                    return current_node.left_child
                else:
                    current_node = current_node.left_child
            else:
                if type(current_node.right_child) == str:
                    return current_node.right_child
                else:
                    current_node = current_node.right_child
