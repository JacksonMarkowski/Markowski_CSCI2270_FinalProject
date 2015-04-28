# Markowski_CSCI2270_FinalProject

Project Summary:

	The project will be a way to view and compare stats of batters in the MLB in recent 
	seasons.  Txt files containing all players in a season and their various batting stats
	will be read in.  The user will be able to select from options such as view all the players
	on a team for a certain season, view all stats available for a player, and compare stats
	of multiple players side by side.


How to Run:

	1. The following files need to be in the same directory.
		- 2010_Batting.txt, 2011_Batting.txt, 2012_Batting.txt,
		 2013_Batting.txt, 2014_Batting.txt, Driver.cpp, PlayerStats.cpp, PlayerStats.h

	2. Compile the files and run
 		Example: Linux CS-VM terminal: Io compile type: g++ -std=c++11 Driver.cpp PlayerStats.cpp 
		To run type: ./a.out

	3. The program should begin running and display the main menu, as shown below.

	4. How the program works:

	-----Main menu-----
	1. Show Teams
	2. Show Players on Team
	3. Show Individual Player Stats
	4. Compare Players
	5. Quit

		1. Show Teams: No other input needed, returns to the main menu

		2. Show Players on Team: Team abbreviation should be entered, not the full team name.
		This is the abbreviation that appears next to the team name in opton 1, show teams.
			example: COL

		3. Show Individual Player Stats: Enter the full name, first and last, of a player (Case sensitive).
		Same as they appear when displayed when option 2, show players on team, is selected for a particular team.
			example: Todd Helton

		4. Compare Players: A compare players menu should appear, options displayed below

		5. Quit: Quits the program
	
	-----Compare Players-----
	1. Select Player
	2. Deselect Player
	3. Show Selected Players
	4. Compare Stats
	5. Back

		1. Select Player: Selects a player to be compared, enter the full name, first and last,
		of a player (Case sensitive). The same way as you would in option 3, show individual player stats.
			example 1: Todd Helton
			example 2: Troy Tulowitzki

		2. Deselect Player: Deselects a player that is being compared, enter the full name, first and last,
		of a player that has already been selected.
			example 1: Todd Helton

		3. Show Selected Players: No other input needed, returns to compare players menu.

		4. Compare Stats: Enter a year between 2010-2014, nothing will be displayed if the player(s)
		selected have no stats for the year inputted.
			example: 2012

		5. Back: Returns to the main menu


Dependencies:

	N/A

System Requirements: 

	N/A

Group	Members: 

	Jackson Markowski

Contributors: 

	N/A

Open issues/bugs: 

	1. Checking/Finding a player/team is case sensitive
