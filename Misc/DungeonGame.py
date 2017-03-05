#Ameya Bahirat
#Fall 2014
#Dungeon game that allows you to circle between different rooms, and within the Library it goes through a separate loop so you can find the princess


print ("Welcome to Ameya's Dungeon!")
command = 'c'
room = 'Kitchen' #Establishes room as a variable



while (command != 'q'):
	if room == 'Kitchen': #Already established room as Kitchen, so this will always print when the program starts
		command = input ("You are in the kitchen. There are doors to the west (w), south (s), and east (e).")
		if command == 'w': #Different command inputs change room to a different variable, once the room is changed to a different variable, it goes to a different if statement
			room = 'Hallway'
		elif command == 's':
			room = 'Furnace'
		elif command == 'e':
			room = 'Living Room'
	if room == 'Hallway':	
		command = input ("You are in the Hallway there are doors to the east (e) and south (s).")
		if command == 's':
				room = 'Library'
		elif command == 'e':
				room = 'Kitchen'
	if room == 'Furnace':
		print ("You entered the furnace and you fry yourself to death!")
		print ("Goodbye!")
		command = 'q' #Quits the program without user need to type in q, command is set to q no matter what
	if room == 'Living Room':
		command = input("You are in the Living Room. There is a door to the west (w).")
		if command == 'w':
			room = 'Kitchen'
	if room == 'Library':
		command = input ("You are in the Library. You sense the princess is here, but where? Look around (l)")
		if command == 'n': #Takes you back to the Hallway
				room = 'Hallway'
		elif command == 'l':
			while (command !='q'): #Different while loop for second or sub-series of questions
					if command == 'b':
						command = input("You look through the bookcase, and see your Python textbook.")
					elif command == 'c':
						command = input ("You rummage through the closet, and you find SKELETONS!")
					elif command == 'p':
						print ("You look at the picture, and see the princess hiding in it! You are a hero!")
						print ("Goodbye!")
						command = 'q'
					else:
						command = input("You look, you see a picture (p), bookcase (b), closet (c)") #Else statement allows this to print if any other letter than b c or p are put in. 
						#Beforehand we see that you have to enter in l to look around the room, this satisfies the else statement so this can print initially as well
					
						
	
			
																																																		
	
	
	
	
