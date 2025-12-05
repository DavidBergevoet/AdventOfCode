combinations = []
ingredients = []

with open("input.txt") as file:
    combi = True
    for line in [line.rstrip() for line in file]:
    	if len(line) == 0:
    		combi = False
    		continue
    	if combi:
    		split_line = line.split('-')
    		combinations.append([int(split_line[0]), int(split_line[1])])
    	else:
    		ingredients.append(int(line))

# print(combinations)
# print(ingredients)

fresh = 0
for i in ingredients:
	for c in combinations:
		if i >= c[0] and i <= c[1]:
			print(f"{i} is fresh")
			fresh += 1
			break

print(f"Fresh products: {fresh}")