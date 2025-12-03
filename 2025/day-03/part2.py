def get_lines():
	with open("input.txt") as file:
	    return [line.rstrip() for line in file]

lines = get_lines()

joltage = 0

nr_indices = 12

for line in lines:
	highest_indices = []
	for nr in range(0, nr_indices):
		if len(highest_indices) == 0:
			start = 0
		else:
			start = highest_indices[-1] + 1
		cur_index = start

		for i in range(start, len(line) - nr_indices + nr + 1):
			if line[i] > line[cur_index]:
				cur_index = i
		highest_indices.append(cur_index)

	value_to_add = ""
	for i in highest_indices:
		value_to_add += line[i]
	value_to_add = int(value_to_add)

	print(f"Adding {value_to_add}")
	joltage += value_to_add

print(f"Final joltage {joltage}")