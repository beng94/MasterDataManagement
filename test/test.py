#!/usr/bin/python

lines_dict = {}

with open("../training_data.csv") as file:
    for line in file:
        chunks = line.replace('\n', '').replace('\r', '').split(',')
        lines_dict[int(chunks[0])] = ",".join(chunks[1:])

file_w = open("duplicates.txt", 'w+')
with open("../training_ground_truth.csv") as file:
    for line in file:
        chunks = line.split(",")
        file_w.write(chunks[0] + "," + lines_dict[int(chunks[0])] + '\n')
        file_w.write(chunks[1].replace('\n', '').replace('\r','') + "," + lines_dict[int(chunks[1])] + '\n')
    print "Program terminated"
file_w.close()


