import tkinter as tk
from random import choice
from tkinter import messagebox


class Game(tk.Tk):
	def __init__(self, menu, players_num : int, bucks : int) -> None:
		super().__init__()

		self.menu = menu

		self.title('Roll the Dice')
		self.geometry("500x400")
		self.configure(bg='black')

		# Create players
		self.players = {i : 0 for i in range(players_num)}
		self.players_num = players_num
		self.current_player = 0
		self.bucks = bucks

		# Create A Dice List
		self.my_dice = ['\u2680', '\u2681','\u2682','\u2683','\u2684','\u2685',]

		# Create a Frame
		self.my_frame = tk.Frame(self)
		self.my_frame.pack(pady=20)

		# Create Dice Labels
		self.dice_label1 = tk.Label(self.my_frame, text='', font=("Helvetica", 100), fg="white", bg='black')
		self.dice_label1.grid(row=0, column=0, padx=5)

		self.dice_label2 = tk.Label(self.my_frame, text='', font=("Helvetica", 100), fg="white", bg='black')
		self.dice_label2.grid(row=0, column=1, padx=5)

		self.dice_label3 = tk.Label(self.my_frame, text='', font=("Helvetica", 100), fg="white", bg='black')
		self.dice_label3.grid(row=0, column=2, padx=5)


		# Create Player Label
		self.player_label = tk.Label(self, text=f'Player {self.current_player} - your move', font=("Helvetica", 24), fg='white', bg='black')
		self.player_label.pack()

		# Create Roll Button
		self.my_button = tk.Button(self, text="Roll Dice", command=self.roll_dice, font=("Helvetica", 24), fg='white', bg='black')
		self.my_button.pack(pady=20)

		# Create Totals Label
		self.current_res_label = tk.Label(self, text="", font=("Helvetica", 24), fg="white", bg='black')
		self.current_res_label.pack()


	# Roll the dice
	def roll_dice(self):
		again = False

		# Roll Random Dice
		d1 = choice(self.my_dice)
		d2 = choice(self.my_dice)
		d3 = choice(self.my_dice)
		
		# Determine Dice Number
		sd1 = self.get_number(d1)
		sd2 = self.get_number(d2)
		sd3 = self.get_number(d3)
		
		# Update Labels
		self.dice_label1.config(text=d1)
		self.dice_label2.config(text=d2)
		self.dice_label3.config(text=d3)
		
		# Update Total 
		if sd1  == sd2 == sd3 == self.bucks:
			self.players[self.current_player] = 15
		elif sd1  == sd2 == sd3 and sd1 != self.bucks:
			if self.players[self.current_player] + 5 <= 15:
				self.players[self.current_player] += 5
		else:
			for i in (sd1, sd2, sd3):
				if i == self.bucks:
					self.players[self.current_player] += 1
					again = True
					if self.players[self.current_player] > 15:
						self.players[self.current_player] -= 2
						again = False
						break
		

		self.current_res_label.config(text=f'Current result: {self.players[self.current_player]}')
			
		if self.players[self.current_player] == 15:
			messagebox.showinfo(title='Congrats', message=f'Player {self.current_player} won!')
			if self.current_player == self.players_num - 1:
				self.players_num -= 1
			self.players.pop(self.current_player)

		if len(self.players) == 1:
			ind = list(self.players.keys())[0]
			print(ind)
			print(self.players)
			messagebox.showinfo(title='Oops', message=f'Player {ind} lose!')
			self.menu.destroy()
			self.destroy()
			return


		while not again or self.current_player not in self.players.keys():
			if self.current_player == self.players_num:
				self.current_player = 0
			else:
				self.current_player += 1
			again = True


		print(self.current_player)
		if self.current_player == self.players_num:
			next_player = 0
		else:
			next_player = self.current_player
		self.player_label.config(text = f'Player {next_player} - your move.')
		self.player_label.pack()

		print(self.players)


	# Get The Dice Number
	@staticmethod
	def get_number(x):
		if x == '\u2680':
			return(1)
		elif x == '\u2681':
			return(2)
		elif x == '\u2682':
			return(3)
		elif x == '\u2683':
			return(4)
		elif x == '\u2684':
			return(5)
		elif x == '\u2685':
			return(6)

