def get_lines():
	with open("input.txt") as file:
	    lines = [line.rstrip() for line in file]
	    mat = []
	    for line in lines:
	    	mat.append(line.split())

	    return mat

mat = get_lines()

total_result = 0
for i in range(0, len(mat[0])):
	operator = mat[-1][i]
	total_string = mat[0][i]
	for j in range(1, len(mat)-1):
		total_string += operator + mat[j][i]

	add_result = eval(total_string)
	print(f"{total_string} = {add_result}")
	total_result += add_result

print(f"Total result: {total_result}")