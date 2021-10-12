class Node:  

    def __init__(self, leaf : bool = False) -> None:
        self.children = []
        self.keys = []
        self.leaf = leaf
    
    def __repr__(self):
        return f'Node({self.keys} {self.children})'
        
    def __str__(self):
        return f'({self.keys} {self.children})'
