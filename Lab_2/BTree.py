from BNode import BNode
import os
import re


class BTree:

    def __init__(self, order):
        if order <= 2:
            raise ValueError("B-tree order must be at least 3")
        self.root = BNode()
        self.order = order
        self.max_values = 2 * order - 1
        self.min_values = order - 1
        self.height = 1
        self.size = 0
        self._read_file()

    def __str__(self):
        return f'BTree(height: {self.height}, items: {self.size}, order: {self.order})'

    def add(self, val):  # find the leaf node where the value should be added
        found, node, pos = self.root.search(val)
        if found:  # the value already exists, can't add it twice
            print("The data already exists.")
            return False
        res = node.add(self, val, pos, None)
        self.root.write_to_file()
        return res

    def delete(self, val):
        found, node, pos = self.root.search(val)
        if not found:  # the value doesn't exist, can't delete it
            print("Can't delete unexisted data. Please, try again.")
            return False
        return node.delete(self, val, pos)

    def search(self, val):
        return self.root.search(val)[0]

    def _read_file(self):
        with open('db.txt', 'r') as file:
            print()
            for node in file.readlines():
                for row in [re.findall(r'\d+', elem) for elem in re.findall(r'\((.*?)\)', node)]:
                    for i in range(0, len(row), 2):
                        self.add((int(row[i]), row[i + 1]))
            print()




