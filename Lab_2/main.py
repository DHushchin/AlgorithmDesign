from BTree import BTree


def main():
    tree = BTree(3)

    for i in range(10, 20):
        tree.add((i, str(i*2)))
        assert (tree.search((i, )))
    tree.root.check_valid(tree)

    tree.root.print_tree()


if __name__ == '__main__':
    main()
