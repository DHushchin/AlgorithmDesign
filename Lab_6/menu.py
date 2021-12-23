import tkinter as tk
from tkinter import ttk, messagebox
from dice import Game


class Menu(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title('Players')
        self.geometry("350x70")
        self.columnconfigure(0, weight=1)
        self.columnconfigure(1, weight=1)
        self.columnconfigure(2, weight=1)
        self.players = tk.StringVar()
        self.bucks = tk.StringVar()
        self.create_widgets()


    @staticmethod
    def display_error(error):
        messagebox.showerror("Error", error)


    def create_widgets(self):
        padding = {'padx': 5, 'pady': 5}

        ttk.Label(self, text='Number of players:').grid(column=0, row=0, **padding)

        players_entry = ttk.Entry(self, textvariable=self.players)
        players_entry.grid(column=1, row=0, **padding)
        players_entry.focus()

        game_button = ttk.Button(self, text='Start game!', command=self.start_game)
        game_button.grid(column=3, row=0, **padding)


        ttk.Label(self, text='Bucks: ').grid(column=0, row=1, **padding)

        bucks_entry = ttk.Entry(self, textvariable=self.bucks)
        bucks_entry.grid(column=1, row=1, **padding)
        bucks_entry.focus()



    def validate(self, players, bucks) -> bool:
        if players == '' or  bucks == '':
            self.display_error("Enter something!")
            return False
        if not players.isdigit() or not bucks.isdigit():
            self.display_error("Enter number!")
            return False
        if int(bucks) < 1:
            self.display_error("There should be at least 1 bucks!")
            return False
        if int(bucks) > 6:
            self.display_error("There can be maximum 6 bucks!")
            return False
        return True


    def start_game(self):
        players = self.players.get()
        bucks = self.bucks.get()
        if self.validate(players, bucks):
            game = Game(self, int(players), int(bucks))
            game.mainloop()
            

menu = Menu()
menu.mainloop()
