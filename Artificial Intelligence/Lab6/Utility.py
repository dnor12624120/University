from Dataset import Dataset

def split_by_label(dataset, column, label):
    # The function split a dataset into 2 sets: entries for which the label on column 'column' is
    # less than 'labels' (left), and the rest (right)
    left, right = [], []
    for entry in dataset:
        if entry[column] < label:
            left.append(entry)
        else:
            right.append(entry)
    return left, right

def gini(dataset, left, right):
    # Calculate gini index for the 2 splits according to the course formula. 
    balance_labels = list(set(entry[0] for entry in dataset)) 
    splits = [left, right]
    total_size = len(left) + len(right)
    score = 0.0
    for split in splits:
        split_size = len(split)
        if split_size != 0:    
            split_score = 0
            for class_val in balance_labels:
                ratio = [entry[0] for entry in split].count(class_val) / split_size
                split_score += ratio ** 2
            score += (split_size / total_size) * (1 - split_score)
    return score
    

def best_split(dataset):
    # Find the best column and attribute to split on (Best/minimal gain). 
    best_column = float('inf')
    best_label = float('inf')
    best_score = float('inf')
    best_left, best_right = None, None
    for column in range(1, len(dataset[0])):
        for entry in dataset:
            left, right = split_by_label(dataset, column, entry[column])
            score = gini(dataset, left, right)
            if score < best_score:
                best_column = column
                best_label = entry[column]
                best_score = score
                best_left, best_right = left, right
    return best_column, best_label, best_left, best_right

def get_dominant_label(node):
    # Finds the most frequent balance label in the 2 splits
    labels = [entry[0] for entry in node.left_split + node.right_split]
    return max(set(labels), key = labels.count) 