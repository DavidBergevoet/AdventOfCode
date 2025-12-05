combinations = []

with open("input.txt") as file:
	for line in [line.rstrip() for line in file]:
		if len(line) == 0:
			break
		split_line = line.split('-')
		combinations.append([int(split_line[0]), int(split_line[1])])

sorted_data = sorted(combinations, key=lambda x: x[0])


min_value = 0
total_fresh = 0

for i in sorted_data:
	# print(f"{i}, {min_value}")
	if i[1] > min_value:
		to_add = i[1] - max(min_value+1, i[0]) + 1
		# print(f"Adding: {to_add}")
		total_fresh += to_add 
		min_value = i[1]

print(f"Possibly fresh: {total_fresh}")