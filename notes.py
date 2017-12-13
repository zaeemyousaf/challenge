# ATM machine, delivers cash
# author: Zaeem yousaf
# copyright: GPL 

note_1000 = 1000	# making notes
note_100 = 100
note_50 = 50
note_10 = 10
# ++++++++++++++++++
cash = int(input("Enter the amount of 5's mulitple: "))
no_1000_notes = 0
no_100_notes = 0
no_50_notes = 0
no_10_notes = 0

remaining = cash	# cash remaining
while remaining >= note_1000:
	# giving note of 1000
	no_1000_notes = no_1000_notes + 1
	remaining = remaining - 1000

while remaining >= note_100:
	# giving notes of 100
	no_100_notes = no_100_notes + 1
	remaining = remaining - 100

while remaining >= note_50:
	# giving note of 50
	no_50_notes = no_50_notes + 1
	remaining = remaining - 50

while remaining >= note_10:
	# giving note of 10
	no_10_notes = no_10_notes + 1
	remaining = remaining - 10

no_coins = remaining	# number of coins

# if notes are zero, don't print them
if no_1000_notes != 0:
	print("Thousands: ", no_1000_notes)
if no_100_notes !=0:
	print("hundred: ",no_100_notes)
if no_50_notes !=0:
	print("fifty: ",no_50_notes)
if no_10_notes !=0:
	print("Ten: ",no_10_notes)
if no_coins !=0:
	print("Coins: ",no_coins)
