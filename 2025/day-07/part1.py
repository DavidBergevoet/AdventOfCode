def get_lines():
	with open("input.txt") as file:
	    return [line.rstrip() for line in file]

splitter_cols = []

lines = get_lines()

for i in range(0, len(lines[0])):
	if lines[0][i] == 'S':
		splitter_cols.append(i)
		break

total_split = 0

for line in lines:
	new_splitter_cols = splitter_cols
	for i in range(0, len(line)):
		for splitter in splitter_cols:
			if i == splitter and line[i] == '^':
				new_splitter_cols.remove(splitter)
				new_splitter_cols.append(i-1)
				new_splitter_cols.append(i+1)
				total_split += 1
	splitter_cols = new_splitter_cols
	splitter_cols = list(set(new_splitter_cols))
	# print(splitter_cols)

print(f"Total splits: {total_split}")
