def get_lines():
	with open("input.txt") as file:
	    return [line.rstrip() for line in file]

splitter_cols = {}

lines = get_lines()

for i in range(0, len(lines[0])):
	if lines[0][i] == 'S':
		splitter_cols[i] = 1
		break

total_split = 0

for line in lines:
	new_splitter_cols = splitter_cols.copy()
	for i in range(0, len(line)):
		for splitter in splitter_cols.keys():
			if i == splitter and line[i] == '^' and splitter_cols[splitter] > 0:
				if i-1 in new_splitter_cols.keys() and new_splitter_cols[i-1] > 0:
					new_splitter_cols[i-1] += new_splitter_cols[splitter]
				else:
					new_splitter_cols[i-1] = new_splitter_cols[splitter]
				if i+1 in new_splitter_cols.keys() and new_splitter_cols[i+1] > 0:
					new_splitter_cols[i+1] += new_splitter_cols[splitter]
				else:
					new_splitter_cols[i+1] = new_splitter_cols[splitter]
				del new_splitter_cols[splitter]

	splitter_cols = new_splitter_cols.copy()
	# print(splitter_cols)

for key in splitter_cols.keys():
	total_split += splitter_cols[key]
print(f"Total splits: {total_split}")
