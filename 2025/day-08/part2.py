import math

junk_boxes = []
class JunkBox:
	def __init__(self, coords):
		self.x = int(coords[0])
		self.y = int(coords[1])
		self.z = int(coords[2])
		self.neighbour = []

	def point(self):
		return (self.x, self.y, self.z)		

	def __str__(self):
		return f"{self.x},{self.y},{self.z},{self.neighbour}"
	def __repr__(self):
		return self.__str__()

with open("input.txt") as f:
	lines = f.readlines()
	for line in lines:
		junk_boxes.append(JunkBox(line.split(',')))

def calc_dist(box1, box2):
	return math.dist(box1.point(), box2.point())

first_largest = 0
second_largest = 0
third_largest = 0

indices_had = []
def find_path_size(index):
	indices_had.append(index)
	path_size = 1
	added_size = 0
	for i in junk_boxes[index].neighbour:
		if i not in indices_had:
			path_size += find_path_size(i)
	return path_size

pairs = []
for i in range(0, len(junk_boxes)):
	for j in range(i, len(junk_boxes)):
		if i != j:
			pairs.append([i, j])

pairs = sorted(pairs, key=lambda x: calc_dist(junk_boxes[x[0]], junk_boxes[x[1]]))

# print(pairs)

def connected(a, b):
    visited = set()
    def dfs(x):
        if x == b:
            return True
        visited.add(x)
        for nxt in junk_boxes[x].neighbour:
            if nxt not in visited:
                if dfs(nxt):
                    return True
        return False
    return dfs(a)

last_pair=[]
counter = 0
for p in pairs:
	# print(f"\rProgress {counter}/{len(pairs)} {counter/len(pairs)*100}", end="", flush=True)
	counter += 1
	if not connected(p[0], p[1]):
		last_pair = p
		junk_boxes[p[0]].neighbour.append(p[1])
		junk_boxes[p[1]].neighbour.append(p[0])


print(junk_boxes[last_pair[0]], junk_boxes[last_pair[1]], junk_boxes[last_pair[0]].x * junk_boxes[last_pair[1]].x)
