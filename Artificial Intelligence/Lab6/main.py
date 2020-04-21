from Service import Service
from Dataset import Dataset

import numpy as np

filepath = "data.txt"
training_percentage = 0.8
number_of_columns = 5
label_separator = ","
runs = 10

dataset = Dataset(filepath, training_percentage, number_of_columns, label_separator)
service = Service(dataset)

accuracy_list = []

for i in range(runs):
	print("Iteration #" + str(i))
	accuracy = service.run()
	accuracy_list.append(accuracy)
	print("Accuracy: " + str(accuracy) + "%")

print("Average accuracy " + str(np.mean(accuracy_list)) + "%")