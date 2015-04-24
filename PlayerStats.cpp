#include "PlayerStats.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

/*
Function prototype:
PlayerStats::PlayerStats()

Function description:
Constructor for PlayerStats.  Creates all teams and players by calling initializeTeams() and readInStats().

Example:
PlayerStats s;

Precondition: N/A
Post condition: All teams and players needed for running any further methods are created.
*/
PlayerStats::PlayerStats() {
    //Creates all the teams
    initializeTeams();
    //Reads in all the stats so all players, stats, teams contain all the information need to run
    readInStats();
}

/*
Function prototype:
PlayerStats::~PlayerStats()

Function description:
Destructor for PlayerStats class.  Deletes all player and teams.

Example:
PlayerStats s;
delete s;

Precondition: Vector players and array teams must have been created and filled with players and teams.
Post condition: Deletes all players and teams.
*/
PlayerStats::~PlayerStats() {
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < players[i].size(); j++) {
            delete players[i].at(j);
        }
    }
    for (int i = 0; i < 30; i++) {
        delete teams[i];
    }
}

/*
Function prototype:
void PlayerStats::showTeams()

Function description:
Displays each team inside teams vector.  Prints out the team name followed by the team abbreviation.

Example:
PlayerStats s;
s.showTeams();

Precondition: Vector of teams has been created and filled with 30 teams, each with name and abbreviation.  Calling initializeTeams() will insure all preconditions are meet.
Post condition: Team names and abbreviations printed to the console.
*/
void PlayerStats::showTeams() {
    //Loops through 30 times because there is always 30 teams to show
    for (int i = 0; i < 30; i++) {
        cout << teams[i]->name << " - " << teams[i]->abbreviation << endl;
    }
}

/*
Function prototype:
bool PlayerStats::showPlayersOnTeam(string, int)

Function description:
Displays all the names of the players who were on a team for a certain year.

Example:
PlayerStats s;
s.showPlayersOnTeam("TB", 2014);

Precondition: If teamAbbreviation matches a team abbreviation, the team must have a name and roster[] initialized.
Post condition: Returns false if teamAbbreviation does not match a team in  the vector of teams.
Also returns false if year is not between 2010 - 2014.  Returns true if all players in team's roster are displayed.
*/
bool PlayerStats::showPlayersOnTeam(std::string teamAbbreviation, int year) {
    Team *team = findTeam(teamAbbreviation);
    //If teamAbbreviation matches a team the team roster is printed
    if (team != NULL) {
        //year must be between 2010-2014 since those are the only years of rosters available
        if (year >= 2010 && year <= 2014) {
            cout << team->name << " - " << team->abbreviation << " - " << year << endl;
            //2014 corresponds to roster[0] and 2010 corresponds to roster[4]
            int rosterYear = std::abs(year - 2014);
            //prints out every player in the roster year
            for (int i = 0; i < team->roster[rosterYear].size(); i++) {
                cout << team->roster[rosterYear].at(i)->name << endl;
            }
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

/*
Function prototype:
bool PlayerStats::showIndividualPlayerStats(string)

Function description:
Displays all the stats for a individual player for every year the player has stats

Example:
PlayerStats s;
s.showIndividualPlayerStats("Evan Longoria")

Precondition: All stats for every seasonalStats for a player, must be initialized. Valid string input
Post condition: Returns true if player was found based on input string name.  Returns false if a player was not found.
*/
bool PlayerStats::showIndividualPlayerStats(std::string name) {
    Player *player = findPlayer(name);
    //Prints out the stats if he player is found based off inputed name
    if (player != NULL) {
        cout << player->name << " - " << player->pos << endl;
        //number of seasons the player has stats
        int seasonalStatsSize = player->seasonalStats.size();
        //prints out every stat type
        for (int i = 0; i < 17; i++) {
            cout << statsTypes[i];
            //prints out the stat for every season the player played
            for (int j = 0; j < seasonalStatsSize; j++) {
                if (i < 13) {
                    cout << "\t" << player->seasonalStats[j].intStats[i];
                } else {
                    cout << "\t" << player->seasonalStats[j].doubleStats[i-13];
                }
            }
            cout << endl;
        }
        return true;
    } else {
        return false;
    }
}

/*
Function prototype:
int PlayerStats::numberOfPlayersSelected()

Function description:
Returns the number of players that have been selected, size of selectedPlayers.

Example:
PlayerStats s;
s.numberOfPlayersSelected();

Precondition: selectedPlayers has been initialized.
Post condition: Returns int that is the size of vector selectedPlayers
*/
int PlayerStats::numberOfPlayersSelected() {
    return selectedPlayers.size();
}

/*
Function prototype:
bool PlayerStats::selectPlayer(string)

Function description:
Finds a player based off an inputted name.  If the player is found the method adds the player to vector selectedPlayers to be used later.

Example:
PlayerStats s;
s.selectPlayer("Evan Longoria");

Precondition: Valid string input.
Post condition: Returns true if the player is found and added to selectedPlayer.  Returns false if the player if not found.
*/
bool PlayerStats::selectPlayer(std::string name) {
    //Attempts to find the player
    Player *p = findPlayer(name);
    //If the player is found it adds the player to selectedPlayers
    if (p != NULL) {
        selectedPlayers.push_back(p);
        return true;
    } else {
        return false;
    }
}

/*
Function prototype:
bool PlayerStats::deselectPlayer(string)

Function description:
Removes a player from selectedPlayers vector if the player is already in the vector

Example:
PlayerStats s;
s.deselectPlayer("Evan Longoria");

Precondition: Valid string input.  selectedPlayers must be initialized.
Post condition: Returns true if the player is found and removed from selectedPlayers vector.  Returns false if a player is not found.
*/
bool PlayerStats::deselectPlayer(std::string name) {
    //Goes through every selected player
    for (int i = 0; i < selectedPlayers.size(); i++) {
        //if the inputed name matches a name in the vector the player is removed from selected players
        if (selectedPlayers[i]->name == name) {
            selectedPlayers.erase(selectedPlayers.begin()+i);
            return true;
        }
    }
    return false;
}

/*
Function prototype:
void PlayerStats::showSelectedPlayers()

Function description:
Displays all the players names who have been selected, are in selectedPlayers.

Example:
PlayerStats s;
s.showSelectedPlayers();

Precondition: selectedPlayers must be initialized.
Post condition: Prints out the selected players to the console.
*/
void PlayerStats::showSelectedPlayers() {
    int selectedPlayersSize = selectedPlayers.size();
    //If there are no players selected
    if (selectedPlayersSize == 0) {
        cout << "No players selected" << endl;
    } else {
        cout << "Players selected: ";
        //Loops through and displays all the selected payers in vector
        for (int i = 0; i < selectedPlayersSize; i++) {
            cout << selectedPlayers[i]->name;
            if (i < selectedPlayersSize - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

/*
Function prototype:
bool PlayerStats::compareStatsSideBySide(int)

Function description:
Displays all the stats for a particular season of the players who have been selected, selectedPlayers.

Example:
PlayerStats s;
s.compareStatsSideBySide(2014);

Precondition: Number of players selected (selectedPlayers size) should be no more than 5
Post condition: Returns false if inputed year is not between 2010 - 2014
*/
bool PlayerStats::compareStatsSideBySide(int year) {
    if (year > 2014 || year < 2010) {
        return false;
    }

    std::vector<Player*> playersToBeDisplayed;
    std::vector<Stats*> statsToBeDisplayed;
    //Loops through all the players who have been selected
    for (int i = 0; i < selectedPlayers.size(); i++) {
        //Gets the stats for that player for the inputed year, will be NULL if the player doesn't have stats for the year
        Stats *stats = findPlayerStatsForYear(selectedPlayers[i], year);
        //Adds the player to a vector of players to be displayed if they have stats for the inputed year
        if (stats != NULL) {
            playersToBeDisplayed.push_back(selectedPlayers[i]);
            statsToBeDisplayed.push_back(stats);
        } else {
            cout << " ** A player has no stats for the selected year **" << endl;
        }
    }

    //Prints out all the initials of the players who stats should be displayed
    cout << "Name";
    for (int i = 0; i < playersToBeDisplayed.size(); i++) {
        cout << "\t" << playersToBeDisplayed[i]->initials;
    }
    cout << endl;

    //Prints out all the stats for the players to be displayed
    for (int i = 0; i < 17; i++) {
        cout << statsTypes[i];
        for (int j = 0; j < playersToBeDisplayed.size(); j++) {
            if (i < 13) {
                cout << "\t" << statsToBeDisplayed[j]->intStats[i];
            } else {
                cout << "\t" << statsToBeDisplayed[j]->doubleStats[i-13];
            }
        }
        cout << endl;
    }
    return true;
}

/*
Function prototype:
void PlayerStats::readInStats()

Function description:
Reads in all the stats from all the stats files and stores the information in struc

Example:
readInStats();

Precondition: initializeTeams() has been called.  Able to open and read files inside MLB_Stats folder
Post condition: Information from txt files is stored in vectors of players and teams
*/
void PlayerStats::readInStats() {
    //ToDO: Clean up opening files and reading in data
    ifstream file;
    int fileYear = 2015;
    //Loops for every file of stats, 5 different files
    for (int i = 0; i < 5; i++) {
        //fileYear corresponds to file year
        fileYear--;
        if (i == 0) file.open("2014_Batting.txt");
        if (i == 1) file.open("2013_Batting.txt");
        if (i == 2) file.open("2012_Batting.txt");
        if (i == 3) file.open("2011_Batting.txt");
        if (i == 4) file.open("2010_Batting.txt");

        string line;
        getline(file, line);
        //Reads in every line, each new line is a different player and stats
        while(getline(file, line)) {
            istringstream individualPlayerRow(line);

            //Reads in player's name
            string lastName;
            string firstName;
            string fullName;
            string initials;
            getline(individualPlayerRow, lastName, ',');
            getline(individualPlayerRow, firstName, '"');
            //removes unwanted characters from players name
            fullName = firstName.substr(1) + " " + lastName.substr(1);
            initials = firstName.substr(1,1) + lastName.substr(1,1);
            if (i == 4) fullName = fullName.substr(1);

            //Checks to see if the player has already been created.
            //If the player hasn't been created it creates them and adds them to list of players
            //Else the stats are read in for the file and added to the player as a new season
            Player *player = findPlayer(fullName);
            if (player == NULL) {
                player = new Player;

                player->name = fullName;
                player->initials = initials;
                addPlayer(player);

                //Reads in player's position
                string pos;
                getline(individualPlayerRow, pos, '\t');
                getline(individualPlayerRow, pos, '\t');
                player->pos = pos;

            } else {
                //skips the lines if the player has already been created
                string ignore;
                getline(individualPlayerRow, ignore, '\t');
                getline(individualPlayerRow, ignore, '\t');
            }

            //Reads in player's team
            string teamAbbreviation;
            getline(individualPlayerRow, teamAbbreviation, '\t');
            //adds the player to a team for the current file season
            addPlayerToTeam(player, teamAbbreviation, fileYear);

            //Reads in player's stats
            string stat;
            Stats newPlayerStats;
            newPlayerStats.intStats[0] = fileYear;
            //stats that are read in that are stored in intStats
            for (int j = 1; j < 13; j++) {
                getline(individualPlayerRow, stat, '\t');
                newPlayerStats.intStats[j] = atoi(stat.c_str());
            }
            //stats that are read in that are stored in doubleStats
            for (int j = 0; j < 4; j++) {
                getline(individualPlayerRow, stat, '\t');
                newPlayerStats.doubleStats[j] = atof(stat.c_str());
            }

            //Adds newPlayerStats to player's vector of seasonalStats
            player->seasonalStats.push_back(newPlayerStats);
        }
        file.close();
    }
}

/*
Function prototype:
int PlayerStats::hashSum(string, int)

Function description:
Generates a hash code that is based off the ascii value of the first character of the inputed string and inputed int value that is the size of the array.

Example:
hashSum("Evan Longoria", 26);

Precondition: Int input is a positive number of the size of hashTable. Valid string input.
Post condition: Returns the hashCode value.
*/
int PlayerStats::hashSum(std::string name, int s) {
    int sum = 0;
    //hashCode is based off first character of the name
    sum = name.at(0) % s;
    return sum;
}

/*
Function prototype:
Player* PlayerStats::findPlayer(string);

Function description:
Finds a pointer to a player in the vector of players that has the same name as the inputed name.

Example:
findPlayer("Evan Longoria");

Precondition: Inputed string is valid.  Vector players has been created and filled with all available players.
Post condition: Returns the pointer to the player that matches the inputed name.  Returns a NULL player if no player is found to match the name.
*/
Player* PlayerStats::findPlayer(std::string name) {
    //Finds the vector that the player(name) would be stored at using hashCode
    std::vector<Player*> playersAtHashSum = players[hashSum(name, 26)];
    for (int i = 0; i < playersAtHashSum.size(); i++) {
        if (playersAtHashSum[i]->name == name) {
            //returns the pointer to player if the player is found
            return playersAtHashSum[i];
        }
    }
    //returns a NULL pointer of a player if a player is not found based off inputed name
    Player *player;
    player = NULL;
    return player;
}

/*
Function prototype:
void PlayerStats::addPlayer(Player*)

Function description:
Takes a player and adds it to a players based off the player's hashCode.

Example:
Player *p = new Player;
p->name = "Ben";
addPlayer(p);

Precondition: newPlayer is a valid player.  Vector players has been initialized.
Post condition: Vector players contains the inputed player
*/
void PlayerStats::addPlayer(Player *newPlayer) {
    //Adds the player to a vector in an array of size 26, using a hashCode
    players[hashSum(newPlayer->name, 26)].push_back(newPlayer);
}

/*
Function prototype:
void PlayerStats::addPlayerToTeam(Player*, string, int)

Function description:
Adds a player to a team based off the inputed team abbreviation and year.

Example:
Player *p = new Player;
addPlayerToTeam(p, "BOS", 2013);

Precondition: Inputed year must be between 2010-2014, teamAbbreviation must match one of the 30 teams if the player is to be added
Post condition: Adds a player to a team's roster for the inputed year.
*/
void PlayerStats::addPlayerToTeam(Player *player, std::string teamAbbreviation, int year) {
    //Finds the team that the teamAbbreviation matches
    Team *t = findTeam(teamAbbreviation);
    //If a team is found the player is added to that team for the inputed year
    if (t != NULL) {
        //team rosters[0] corresponds to 2014 and rosters[4] corresponds to 2010
        t->roster[std::abs(year - 2014)].push_back(player);

    }
}

/*
Function prototype:
void PlayerStats::initializeTeams()

Function description:
Creates all the teams and adds them to a vector of teams, each team is given a name and a corresponding abbreviation.

Example:
initializeTeam();

Precondition: teams vector must be initialized.
Post condition: All 30 teams will be created and will be pointed to by teams vector.
*/
void PlayerStats::initializeTeams() {
    //Array of all the team names and abbreviations.  Team name and abbreviation have a matching index in the arrays
    std::string teamName[30] = {"Los Angeles Angles", "Atlanta Braves", "Houston Astros", "Milwaukee Brewers",
    "Oakland Athletics", "St. Louis Cardinals", "Toronto Blue Jays", "Chicago Cubs", "Tampa Bay Rays", "Arizona Diamondbacks",
    "Cleveland Indians", "Los Angeles Dodgers", "Seattle Mariners", "San Francisco Giants", "Baltimore Orioles", "Miami Marlins",
    "Texas Rangers", "New York Mets", "Boston Red Sox", "Washington Nationals", "Kansas City Royals", "San Diego Padres", "Detroit Tigers",
    "Philadelphia Phillies", "Minnesota Twins", "Pittsburgh Pirates", "Chicago White Sox", "Cincinnati Reds", "New York Yankees", "Colorado Rockies"};
    std::string teamAbbreviation[30] = {"LAA", "ATL", "HOU", "MIL", "OAK", "STL", "TOR", "CHC", "TB", "AZ", "CLE", "LAD", "SEA", "SF", "BAL", "MIA",
    "TEX", "NYM", "BOS", "WSH", "KC", "SD", "DET", "PHI", "MIN", "PIT", "CHW", "CIN", "NYY", "COL"};

    //Creates a new team and adds it to a vector of teams for all 30 teams
    for (int i = 0; i < 30; i++) {
        Team *newTeam = new Team;
        newTeam->name = teamName[i];
        newTeam->abbreviation = teamAbbreviation[i];
        teams[i] = newTeam;
    }
}

/*
Function prototype:
Team* PlayerStats::findTeam(string)

Function description:
Finds a team based off an inputed team abbreviation.

Example:
Team *t;
t = findTeam("NYY");

Precondition: teams vector must be created and contain all 30 teams.  initializeTeams() should be called prior.
Post condition: Returns the team matching the inputed teamAbbreviation.  Returns a NULL team if no team is found to match.
*/
Team* PlayerStats::findTeam(std::string teamAbbreviation) {
    //Loops through the vector of teams and if the inputed teamAbbreviation matches the team abbreviation a pointer to the team is returned
    for (int i = 0; i < 30; i++) {
        if (teamAbbreviation == teams[i]->abbreviation) {
            return teams[i];
        }
    }
    //Returns a NULL team if no team matches the inputed teamAbbreviation
    Team *team;
    team = NULL;
    return team;
}

/*
Function prototype:
Stats* PlayerStats::findPlayerStatsForYear(Player*, int)

Function description:
Finds a player's stats for the inputed year.  Not all players have stats for every year so this method finds attempts to find stats for a certain year and returns them if found.

Example:
Player *p;
findPlayerStatsForYear(p, 2014);

Precondition: Player seasonalStats should be initialized.
Post condition: Returns player's stats matching inputed year.  Returns NULL stats if no starts are found to match the year.
*/
Stats* PlayerStats::findPlayerStatsForYear(Player* player, int year) {
    for (int i = 0; i < player->seasonalStats.size(); i++) {
        if (player->seasonalStats[i].intStats[0] == year) {
            return &player->seasonalStats[i];
        }
    }
    Stats *stats;
    stats = NULL;
    return stats;
}
