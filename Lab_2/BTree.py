from node import Node

class BTree:
	def __init__(self, order : int):
		self.root = Node(True)
		self.order = order


	def print_tree(self, node : Node, level : int = 0) -> None:
		print(f'Level, {level}  {len(node.keys)}', end = ":")
		for key in node.keys:
			print(key, end=" ")
		print()
		level += 1
		if len(node.children) > 0:
			for child in node.children:
				self.print_tree(child, level)


	def insert(self, key : tuple) -> None:
		current_root = self.root
		#Keys are full, so we must split child
		if len(current_root.keys) == (2 * self.order) - 1:
			new_root = Node()
			self.root = new_root			
			new_root.children.insert(0, current_root) #Former root becomes 0th child of new root 'temp'
			self._split_child(new_root, 0) #And we split it
		self._insert_nonfull(self.root, key)
    
    
	def _insert_nonfull(self, current_node : Node, key : tuple) -> None:
		i = len(current_node.keys) - 1
		if current_node.leaf:
            #find index and insert (key, value)
			current_node.keys.append((None, None))
			while i >= 0 and key[0] < current_node.keys[i][0]:
				current_node.keys[i + 1] = current_node.keys[i]
				i -= 1
			current_node.keys[i + 1] = key
		else:
			while i >= 0 and key[0] < current_node.keys[i][0]:
				i -= 1
			i += 1
			if len(current_node.children[i].keys) == (2 * self.order) - 1:
				self._split_child(current_node, i)
				if key[0] > current_node.keys[i][0]:
					i += 1
			self._insert_nonfull(current_node.children[i], key)


	def _split_child(self, parent_node : Node, split_index : int) -> None:
		order = self.order
		first_half = parent_node.children[split_index]
		second_half = Node(first_half.leaf)
		parent_node.children.insert(split_index + 1, second_half) #new empty node
		parent_node.keys.insert(split_index, first_half.keys[order - 1]) #move median key to parent
        #distribute keys between two parts
		second_half.keys = first_half.keys[order : 2 * order - 1]
		first_half.keys = first_half.keys[0 : order - 1]
		if not first_half.leaf: #distribute children between two parts
			second_half.children = first_half.children[order : 2 * order]
			first_half.children = first_half.children[0 : order - 1]

	
	def search(self, key : tuple, current_node : Node = None):
		if current_node != None:
			i = 0
			while i < len(current_node.keys) and key > current_node.keys[i][0]:
				i += 1
			if i < len(current_node.keys) and key == current_node.keys[i][0]:
				return (current_node, i)
			elif current_node.leaf:
				return None
			else:
				#Search in children
				return self.search(key, current_node.children[i])
		else:
			#Search entire tree as node not provided
			return self.search(key, self.root)