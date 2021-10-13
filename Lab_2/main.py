from BTree import BTree

def main():
	B = BTree(5)
	for i in range(20):
		B.insert((i, str(2*i)))
	B.print_tree(B.root)
	print(B.search(7))

if __name__ == '__main__':
	main()