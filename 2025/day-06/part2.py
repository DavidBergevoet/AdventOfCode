def get_lines():
	with open("input.txt") as file:
	    return [line[:len(line)-1] for line in file]

lines = get_lines()

start_of_columns = []
for i in range(0, len(lines[-1])):
	if lines[-1][i] != ' ':
		start_of_columns.append(i)

mat = []

operators = lines[-1].split()

for line in lines:
	line_arr = []
	for i in range(1, len(start_of_columns)):
		line_arr.append(line[start_of_columns[i-1]:start_of_columns[i]])
	line_arr.append(line[start_of_columns[-1]:])
	mat.append(line_arr)
mat =  mat[:len(mat)-1]


total_sum = 0
for c in range(0, len(mat[0])):
	capped_ints = []
	for i in range(len(mat[0][c])-1, -1, -1):
		capped_int = ""
		for r in range(0, len(mat)):
			if mat[r][c][i] != ' ':
				capped_int += (mat[r][c][i])
		if len(capped_int) != 0:
			capped_ints.append(capped_int)
	value_to_add = eval(operators[c].join(capped_ints))
	print(value_to_add)
	total_sum += value_to_add

print(f"Total sum: {total_sum}")

