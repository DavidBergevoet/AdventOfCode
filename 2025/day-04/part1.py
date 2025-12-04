
def get_lines():
	with open("input.txt") as file:
	    return [line.rstrip() for line in file]

def get_adjacent(row, col):
	row_indices = []
	if row == 0:
		row_indices = [row, row + 1]
	elif row == len(mat) - 1:
		row_indices = [row -1, row]
	else:
		row_indices = [row - 1, row, row + 1]

	col_indices = []
	if col == 0:
		col_indices = [col, col + 1]
	elif col == len(mat[0]) - 1:
		col_indices = [col - 1, col]
	else:
		col_indices = [col -1, col, col + 1]

	adj = []
	for r in row_indices:
		for c in col_indices:
			if r != row or c != col:
				adj.append(mat[r][c])
	return adj

mat = get_lines()

rolls = 0
for row in range(0, len(mat)):
	for col in range(0, len(mat[row])):
		if mat[row][col] == '@' and get_adjacent(row, col).count('@') < 4:
			# print(f"{row}, {col}")
			rolls += 1

print(f"Total rolls: {rolls}")