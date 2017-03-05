#!/usr/bin/python3
#Ameya Bahirat
#Fall 2014
#Homework #4
#In this homework assignment, we are essentially creating a code that will take a file containing candidate names and vote and arrange them a specific way, and give us a winner
#Worked with Austin Chau to complete this assignment. 
import sys


fo = open(sys.argv[1],"r") #Opens and reads given file
data = [5] #Number of Data values in file
overall_sum = 0      #Starting values
winner = 0
winner_string = 0
candidates = {} #puts all candidates in dictionary so file does not need to be read once more


for line in fo:
	data = line.split() #splits data every space
	total_votes_per_candidate = int(data[2]) + int(data[3]) + int(data[4]) + int(data[5]) #creates integers from values in data and adds them for total vote per candidate
	overall_sum = total_votes_per_candidate + overall_sum #Takes into account all total votes per candidate for overall sum
	
	if total_votes_per_candidate > winner: #Establishes winner
		winner = total_votes_per_candidate
		winner_string = data[0] + " " + data[1]
	candidates[data[0] + " " + data[1]] = total_votes_per_candidate

print (str("Candidates").center(15), "Votes".rjust(8), "Percent".rjust(10)) #formatting
print (str("="*10).center(15), ('='*5).rjust(8), ("="*7).rjust(10))


for i in candidates:
	percent = int((candidates[i]/overall_sum)*100) #candidates = total_vote_per_candidate
	
	print ( str(i).center(15), str(candidates[i]).rjust(8), ('%.f %%' %percent).rjust(10))


print ("")
print("The winner is" ,winner_string, "with" , winner, "votes!")	
print("")
print("Total votes polled:" , overall_sum)


	
	





fo.close()
