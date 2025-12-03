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
		half = int(len(string_code)/2)
		for check_len in range(1, half + 1):
			# print(f"{i}, {check_len}")
			if len(string_code) % check_len == 0:
				# print(f"In there! {string_code[:check_len]}, {len(string_code)}, {string_code.count(string_code[:check_len])}")
				if string_code.count(string_code[:check_len]) == len(string_code) / check_len:
					print(f"Adding {i}")
					invalid_code_value += i
					break

print(f"Invalid codes: {invalid_code_value}")