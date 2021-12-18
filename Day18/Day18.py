import math, itertools

class Tree:
	def __init__(self, string = ""):
		depth = 0
		self.left = self.right = self.parent = None
		for pos,ch in enumerate(string[1:-1]):
			if ch == '[': 
				depth += 1
			elif ch == ']': 
				depth -= 1
			elif ch == ',' and depth == 0: 
				self.left = Tree(string[1:pos+1])
				self.right = Tree(string[pos+2:-1])
				self.left.parent = self.right.parent = self
				break
		self.value = int(string) if string.isnumeric() and not self.left else None

	def __add__(self, other):
		tree = Tree()
		tree.left = Tree(str(self))
		tree.right = Tree(str(other))
		tree.left.parent = tree
		tree.right.parent = tree
		while (tree.explode(0) or tree.split()) : continue
		return tree

	def __radd__(self, other):
		if other == 0: return self
		else: return self.__add__(other)

	def  __repr__(self):
		if bool(not self.left): return str(self.value);
		else: return "[" + str(self.left) + "," + str(self.right) + "]"

	def split(self):
		if self.value and self.value > 9:
			self.left = Tree(str(math.floor(self.value/2)))
			self.right = Tree(str(math.ceil(self.value/2)))
			self.left.parent = self.right.parent = self
			self.value = None
			return True
		if self.left:
			return self.left.split() or self.right.split()
		return False

	def explode(self, depth):
		if self.left:
			if depth == 4 and not self.left.left and not self.right.left:
				
				leftVal = self.parent
				oldVal = self
				while (leftVal and leftVal.left == oldVal):
					oldVal = leftVal 
					leftVal = leftVal.parent
				if (leftVal): leftVal = leftVal.left
				while leftVal and leftVal.right: leftVal = leftVal.right

				rightVal = self.parent
				oldVal = self
				while (rightVal and rightVal.right == oldVal):
					oldVal = rightVal 
					rightVal = rightVal.parent
				if (rightVal): rightVal = rightVal.right
				while rightVal and rightVal.left: rightVal = rightVal.left

				if leftVal: leftVal.value += self.left.value
				if rightVal: rightVal.value += self.right.value
				self.left = None
				self.right = None
				self.value = 0

				return True
			return self.left.explode(depth+1) or self.right.explode(depth+1)
		return False

	def magnitude(self):
		if self.left:
			return 3*self.left.magnitude() + 2*self.right.magnitude()
		else:
			return int(self.value)
 
trees = [Tree(line) for line in open('input.txt').read().splitlines()]

# Part 1
print(sum(trees).magnitude()) # 4057

# Part 2
print(max(tree.magnitude() for tree in [a + b for a, b in itertools.permutations(trees, 2)])) # 4683