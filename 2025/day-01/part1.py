import os

def get_lines():
	with open("input.txt") as file:
	    return [line.rstrip() for line in file]


start_value = 50
total_zeros = 0

for line in get_lines():
	line_value = int(line[1:])

	for i in range(0, line_value):
		if line[0] == 'R':
			start_value += 1
		if line[0] == 'L':
			start_value -= 1

		if start_value < 0:
			start_value = 99
		elif start_value == 100:
			start_value = 0
	print(f"{line_value} \t: {start_value}")

	if start_value == 0:
		total_zeros += 1

print(f"Total zeros: {total_zeros}")
