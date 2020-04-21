from Dataset import Dataset
from Service import Service
import numpy as np

input_filepath = "data.txt"
output_filepath = "output.txt"
num_columns = 6
y_index = 5

dataset = Dataset(input_filepath, num_columns, y_index)
service = Service(dataset)

with open(output_filepath, "w") as f:
    for i in range(len(dataset.xs)):
        entry = dataset.xs[i]
        value = dataset.ys[i]
        f.write("Trying model for entry " + str(entry) + "\n")
        f.write("Actual value: " + str(value) + "\n")
        prediction = service.predict(entry)
        f.write("Predicted value: " + str(prediction) + "\n")
