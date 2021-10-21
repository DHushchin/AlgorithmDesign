import bisect  # maintaining a list in sorted order without having to sort the list after each insertion
import os

class BNode:
    def __init__(self, values=None, children=None):
        self.parent = None
        self.values = values or []
        self.children = children
        # update the parent node in children in case it has changed
        if self.children:
            for child in self.children:
                child.parent = self

    def __str__(self):
        return str(self.values)

    def print_tree(self, tab=''):
        print(f'{tab}{self}')
        if self.children:
            for child in self.children:
                child.print_tree(tab + '   ')

    def write_to_file(self, tab=''):
        is_root = os.stat("db.txt").st_size and not self.parent  # rewriting tree
        with open('db.txt', 'w' if is_root else 'a') as file:
            file.write(f'{tab}{self}\n')
        if self.children:
            for child in self.children:
                child.write_to_file(tab + '   ')

    def check_valid(self, tree):
        """
            Check (recursively) tree integrity according to the B-tree rules.
            This is used to check the correctness of the algorithms.
        """
        inner_node = self.children is not None
        root_node = self.parent is None

        assert (self.values is not None)

        # an inner node except the root has at least min_values
        if not root_node and inner_node:
            assert(tree.min_values <= len(self.values))

        # a node can't have more than max_values
        assert(len(self.values) <= tree.max_values)

        # The root has at least two children if it is not a leaf node.
        if root_node and inner_node:
            assert (len(self.children) >= 2)

        # A non-leaf node with k children contains k-1 keys.
        if inner_node:
            assert ((len(self.values) + 1) == len(self.children))

        # check that values are sorted
        prev = None
        for i in self.values:
            if prev is not None:
                assert (i > prev)
            prev = i

        if self.children:
            for i in self.children:
                assert (i.parent is self)
                i.check_valid(tree)

    def search(self, val):
        """
            Search for a value starting with this node.

            If the value does not exist in the tree, move down the tree and
            return the leaf node and the insertion position in that node where
            the value should be placed. i.e the tuple: (False, node, pos)
            If val exists in the tree, return the tuple: (True, node, pos),
            where 'node' is the node containing the value and 'pos' is the
            position of the value within that node.
        """
        i = bisect.bisect_left(self.values, val)
        if i != len(self.values) and not val[0] < self.values[i][0]:
            assert (self.values[i][0] == val[0])  # the value already exists
            return True, self, i

        if self.children is not None:
            assert (len(self.children) >= i and self.children[i])  # recursively search down the appropriate child node
            return self.children[i].search(val)
        return False, self, i

    def _split_node(self, tree, val=None, pos=None, new_children=None):
        """
            Split a B-tree node in two.

            If 'val' and 'pos' are given then also insert val into the
            resulting nodes. If additionally 'children' are given
            then '_split_node' is recursively called from add and
            'children' represent the nodes separated by the value 'val'
            in the node's parent.
        """
        assert (val is None or (pos is not None))

        if pos is None:
            pos = 0

        middle_list = [] if val is None else [val]
        # get the median of self.values and val
        values_to_split = self.values[0:pos] + middle_list + self.values[pos:]
        median_index = len(values_to_split) // 2

        left_values = values_to_split[0:median_index]
        median_value = values_to_split[median_index]
        right_values = values_to_split[median_index + 1:]

        is_inner_node = self.children is not None

        if is_inner_node:
            if new_children is not None:
                children_to_split = (self.children[0:pos] + list(new_children) + self.children[pos + 1:])
            else:
                children_to_split = self.children
            left_children = children_to_split[0:len(left_values) + 1]
            right_children = children_to_split[len(left_values) + 1:]
        else:
            left_children = None
            right_children = None

        left_node = BNode(left_values, left_children)
        right_node = BNode(right_values, right_children)

        if self.parent:
            self.parent.add(tree, median_value, None, (left_node, right_node))
        else:
            # create new root and increment the tree depth
            new_root = BNode([median_value], [left_node, right_node])
            left_node.parent = new_root
            right_node.parent = new_root
            tree.root = new_root
            tree.height += 1
            tree.size += 1

    def add(self, tree, val: tuple, pos=None, children=None):
        """
            Add a new value to the B-tree 'tree'. The value must not already exist.
        """

        '''
            All insertions should start at a leaf node, unless we call add recursively into the parent
            as a result of node splitting when we are adding the median value to the parent
        '''
        assert (self.children is None or children)

        '''
            If this is an inner node, not a leaf or the root - then self.children is not None, 
            then also this function must have been called recursively from '_split_node' 
            with 'children' not None, 'val' not None and len(children) == 2
        '''
        if self.children is not None:
            assert (children and len(children) == 2)
        else:
            assert (children is None)

        # If not already found, find the insert position among the current node's values
        if pos is None:
            pos = bisect.bisect_left(self.values, val)

        # check if we can do the insertion to the current node's values
        if len(self.values) < tree.max_values:
            self.values.insert(pos, val)
            tree.size += 1
            if children:  # update the parent reference in the nodes we are about to add
                for child in children:
                    child.parent = self
                self.children[pos:pos + 1] = children
            return True

        # the current node is full, so we have to split it
        self._split_node(tree, val, pos, children)
        return True

    def min_value(self, pos=0):
        if self.children:
            return self.children[pos].min_value()
        return self.values[0], self, 0

    def max_value(self, pos=None):
        if pos is None:
            pos = len(self.values) - 1
        if self.children:
            return self.children[pos + 1].max_value()
        return self.values[-1], self, len(self.values) - 1

    def delete(self, tree, val, pos=None):
        """
        Delete a value from the B-tree. The value must exist.
        """
        inner_node = self.children is not None
        if pos is None:
            assert (pos is not None)
            pos = bisect.bisect_left(self.values, val)

        assert (pos != len(self.values) and self.values[pos][0] == val[0])

        if not inner_node:  # perform deletion from a leaf
            del self.values[pos]
            tree.size -= 1
            if len(self.values) < tree.min_values:
                self.rebalance(tree)  # underflow happened in the leaf node - rebalance tree starting with this node
        else:  # find the minimum value in the right subtree and use it as the separator value to replace 'val'
            new_separator, node, idx = self.min_value(pos + 1)
            self.values[pos] = new_separator
            del node.values[idx]
            tree.size -= 1
            if len(node.values) < tree.min_values:
                node.rebalance(tree)

    def rebalance(self, tree):
        """
            Rebalance a B-tree starting with the current node.
        """
        left_sibling, right_sibling, tmp_index = self.get_siblings()

        # only the root doesn't have siblings
        assert (right_sibling or left_sibling or self.parent is None)

        if self.parent is None:  # this is a no-op for the root node
            return

        is_inner_node = self.children is not None
        if is_inner_node:  # conditions for rebalance
            assert (right_sibling is None or right_sibling.children is not None)
            assert (left_sibling is None or left_sibling.children is not None)
        else:
            assert (right_sibling is None or right_sibling.children is None)
            assert (left_sibling is None or left_sibling.children is None)

        if not is_inner_node:
            if right_sibling and len(right_sibling.values) > tree.min_values:
                sep_index = tmp_index
                sep_value = self.parent.values[sep_index]
                # borrow node from right sibling to perform a left rotate
                self.parent.values[sep_index] = right_sibling.values[0]
                del right_sibling.values[0]
                self.values.append(sep_value)
                return
            elif left_sibling and len(left_sibling.values) > tree.min_values:
                sep_index = tmp_index - 1
                sep_value = self.parent.values[sep_index]
                # borrow node from left sibling to perform a right rotate
                self.parent.values[sep_index] = left_sibling.values[-1]
                del left_sibling.values[-1]
                self.values.insert(0, sep_value)
                return

        # we have to merge 2 nodes
        if left_sibling is not None:
            sep_index = tmp_index - 1
            left_node = left_sibling
            right_node = self
        elif right_sibling is not None:
            sep_index = tmp_index
            left_node = self
            right_node = right_sibling
        else:
            assert False

        sep_value = self.parent.values[sep_index]
        left_node.values.append(sep_value)
        left_node.values.extend(right_node.values)
        del right_node.values[:]
        del self.parent.values[sep_index]
        assert (self.parent.children[sep_index + 1] is right_node)
        del self.parent.children[sep_index + 1]

        if right_node.children:
            left_node.children.extend(right_node.children)
            for i in right_node.children:
                i.parent = left_node

        if len(left_node.values) > tree.max_values:
            # split the newly formed node (arise only when merging inner nodes)
            assert is_inner_node
            left_node._split_node(tree)

        if len(self.parent.values) < tree.min_values:
            self.parent.rebalance(tree)  # rebalance the parent

        if self.parent.parent is None and not self.parent.values:
            tree.root = left_node
            tree.root.parent = None

    def get_siblings(self):
        """
            Get the adjacent siblings of this node.

            Return the tuple: (left sibling node, right sibling node, separator index).
            If a sibling does not exist, None is returned instead.
            The separator index represents the index of this node in its parent's children list.
        """
        if not self.parent:
            return None, None, 0  # the root doesn't have siblings

        assert self.parent.children

        left_sibling = None
        right_sibling = None
        sep_index = 0

        for i, j in enumerate(self.parent.children):
            if j is self:
                if i != 0:
                    left_sibling = self.parent.children[i - 1]
                if (i + 1) < len(self.parent.children):
                    right_sibling = self.parent.children[i + 1]
                sep_index = i
                break

        return left_sibling, right_sibling, sep_index
