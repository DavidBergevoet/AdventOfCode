def get_lines():
	with open("input.txt") as file:
	    return [line.rstrip() for line in file]

lines = get_lines()
points = []
for line in lines:
	split_line = line.split(',')
	points.append([int(split_line[0]), int(split_line[1])])

def calc_area(i, j):
	return (abs(points[i][0] - points[j][0])+1) * (abs(points[i][1] - points[j][1])+1)

most_area = 0
for i in range(0, len(points)):
	for j in range(i, len(points)):
		area = calc_area(i, j)
		if area > most_area:
			print(points[i], points[j])
			most_area = area

print("Most area", most_area)