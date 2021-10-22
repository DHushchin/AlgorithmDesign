from BNode import BNode
import re
import math


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
        found, node, pos, comp = self.root.search(val, 0)
        if found:  # the value already exists, can't add it twice
            print("The data already exists.")
            return False
        res = node.add(self, val, pos, None)
        self.root.write_to_file()
        return res

    def delete(self, val):
        found, node, pos, comp = self.root.search(val, 0)
        if not found:  # the value doesn't exist, can't delete it
            print("Can't delete unexisted data. Please, try again.")
            return False
        res = node.delete(self, val, pos)
        self.root.write_to_file()
        return res

    def search(self, val):
        res = self.root.search(val, 0)
        print(f'Comparisons: {res[3]}')
        if res[0]:
            return res[1].values[res[2]]
        return 'You are trying to delete unexisting key'

    def _read_file(self):
        with open('db.txt', 'r') as file:
            for node in file.readlines():
                for elem in re.findall(r'\((.*?)\)', node):
                    key = int(elem[0: elem.index(',')])
                    value = elem[elem.index(',') + 1: -2]
                    self.add((key, value))
