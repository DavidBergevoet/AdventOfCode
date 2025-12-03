def get_lines():
	with open("input.txt") as file:
	    return [line.rstrip() for line in file]

lines = get_lines()

joltage = 0

for line in lines:
	highest_first_index = 0
	for i in range(1, len(line)-1):
		if line[i] > line[highest_first_index]:
			highest_first_index = i

	highest_second_index = highest_first_index + 1
	for i in range(highest_second_index, len(line)):
		if line[i] > line[highest_second_index]:
			highest_second_index = i
	print(f"Adding {int(line[highest_first_index]+line[highest_second_index])}")
	joltage += int(line[highest_first_index]+line[highest_second_index])

print(f"Final joltage {joltage}")