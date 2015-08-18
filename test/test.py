lines = []

with open("../training_data.csv") as file:
    for line in file:
        lines.append(line)

file_w = open("duplicates.txt", 'w+')
with open("../training_ground_truth.csv") as file:
    for line in file:
        chunks = line.split(",")
        file_w.write(lines[int(chunks[0])])
        file_w.write(lines[int(chunks[1])])
file_w.close()


