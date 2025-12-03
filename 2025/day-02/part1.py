def get_combinations():
	with open("input.txt") as file:
	    linearr = [line.split(',') for line in file][0]
	    return [code.split('-') for code in linearr]


combinations = get_combinations()
invalid_code_value = 0

for code in combinations:
	first_value = int(code[0])
	second_value = int(code[1])
	for i in range(first_value, second_value+1):
		string_code = str(i)
		if len(string_code) % 2 == 0:
			half = int(len(string_code)/2)
			if string_code[:half] == string_code[half:]:
				invalid_code_value += i

print(f"Invalid codes: {invalid_code_value}")