import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
from BTree import BTree


class TreeCreator(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title('BTree Editor')
        self.geometry("300x50")
        self.order_var = tk.StringVar()
        self.columnconfigure(0, weight=1)
        self.columnconfigure(1, weight=1)
        self.columnconfigure(2, weight=1)
        self.create_widgets()

    @staticmethod
    def display_error(error):
        messagebox.showinfo("Error", error)

    def create_widgets(self):
        padding = {'padx': 5, 'pady': 5}
        # label
        ttk.Label(self, text='Tree order:').grid(column=0, row=0, **padding)

        # Entry
        key_entry = ttk.Entry(self, textvariable=self.order_var)
        key_entry.grid(column=1, row=0, **padding)
        key_entry.focus()

        # Button
        add_button = ttk.Button(self, text='Create tree', command=self.create_tree)
        add_button.grid(column=3, row=0, **padding)

    def validate(self, order):
        if order == '':
            self.display_error("Enter tree order")
            return
        if not order.isdigit():
            self.display_error("Enter number")
            return
        if int(order) < 3:
            self.display_error("B-tree order must be at least 3")
            return

    def create_tree(self):
        order = self.order_var.get()
        self.validate(order)
        self.destroy()
        editor = TreeEditor(int(order))
        editor.mainloop()


class TreeEditor(tk.Tk):
    def __init__(self, order: int):
        super().__init__()

        self.tree = BTree(order)

        self.key_var = tk.StringVar()
        self.from_var = tk.StringVar()
        self.to_var = tk.StringVar()
        self.value_input = tk.StringVar()

        self.key_value = None
        self.from_value = None
        self.to_value = None
        self.value = None

        for i in range(6):
            self.columnconfigure(i, weight=1)

        self.create_widgets()

    @staticmethod
    def display_error(error):
        messagebox.showinfo("Error", error)

    def create_widgets(self):
        padding = {'padx': 5, 'pady': 5}
        # label
        ttk.Label(self, text='Key:').grid(column=0, row=0, **padding)
        ttk.Label(self, text='From:').grid(column=0, row=1, **padding)
        ttk.Label(self, text='To:').grid(column=0, row=2, **padding)
        ttk.Label(self, text='Value:').grid(column=0, row=3, **padding)

        # Entry
        key_entry = ttk.Entry(self, textvariable=self.key_var)
        key_entry.grid(column=1, row=0, **padding)
        key_entry.focus()

        from_entry = ttk.Entry(self, textvariable=self.from_var)
        from_entry.grid(column=1, row=1, **padding)
        from_entry.focus()

        to_entry = ttk.Entry(self, textvariable=self.to_var)
        to_entry.grid(column=1, row=2, **padding)
        to_entry.focus()

        value_input = ttk.Entry(self, textvariable=self.value_input)
        value_input.grid(column=1, row=3, **padding)
        value_input.focus()

        # Button
        add_button = ttk.Button(self, text='Add', command=self.add)
        add_button.grid(column=0, row=4, **padding)

        delete_button = ttk.Button(self, text='Delete', command=self.delete)
        delete_button.grid(column=1, row=4, **padding)

        search_button = ttk.Button(self, text='Search', command=self.search)
        search_button.grid(column=2, row=4, **padding)

    def validate(self):
        self.key_value = self.key_var.get()
        self.from_value = self.from_var.get()
        self.to_value = self.to_var.get()
        self.value = self.value_input.get()
        if self.key_value != '' and (self.from_value != '' or self.to_value != ''):
            self.display_error("Key should be entered separately")
            return
        if self.key_value == '' and self.from_value == '' and self.to_value == '':
            self.display_error("Enter some data")
            return
        if (self.from_value == '' and self.to_value != '') or (self.from_value != '' and self.to_value == ''):
            self.display_error("Both fields should be filled")
            return
        if (self.key_value != '' and not self.key_value.isdigit()) or \
            (self.to_value != '' and not self.to_value.isdigit()) or \
           (self.from_value != '' and not self.from_value.isdigit()):
            self.display_error("Keys should be numbers")
            return
        if (self.key_value != '' and int(self.key_value) < 0) or  \
           (self.to_value != '' and int(self.to_value) < 0) or \
           (self.from_value != '' and int(self.from_value) < 0):
            self.display_error("Keys can't be negative")
            return

    def add(self):
        self.validate()
        if self.key_value != '':
            self.tree.add((int(self.key_value), self.value))
        else:
            for i in range(int(self.from_value), int(self.to_value)):
                self.tree.add((i, self.value))

    def delete(self):
        self.validate()
        if self.key_value != '':
            self.tree.delete((int(self.key_value), self.value))
        else:
            for i in range(int(self.from_value), int(self.to_value)):
                self.tree.delete((i, self.value))

    def search(self):
        self.validate()
        if self.key_value != '':
            messagebox.showinfo("Key", self.tree.search((int(self.key_value), )))
            return
        self.display_error('Enter key')
