#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "PlayerStats.h"

using namespace std;

void menuPlayersOnTeam(PlayerStats *playerStats);
void menuIndividualPlayer(PlayerStats *playerStats);
void menuComparePlayers(PlayerStats *playerStats);
void menuSelectPlayer(PlayerStats *playerStats);
void menuDeselectPlayer(PlayerStats *playerStats);
void menuCompareStats(PlayerStats *playerStats);

int main(int argc, char* argv[]) {
    PlayerStats *playerStats = new PlayerStats();

    //runs until the user quits
    bool continueRunning = true;
    while (continueRunning) {

        cout << "\n-----Main Menu-----" << endl;
        cout << "1. Show Teams" << endl;
        cout << "2. Show Players on Team" << endl;
        cout << "3. Show Individual Player Stats" << endl;
        cout << "4. Compare Players" << endl;
        cout << "5. Quit" << endl;
        int userInput = 0;
        cin >> userInput;

        //Checks the user input
        if (userInput == 1) {
            playerStats->showTeams();
        } else if (userInput == 2) {
            menuPlayersOnTeam(playerStats);
        } else if (userInput == 3) {
            menuIndividualPlayer(playerStats);
        } else if (userInput == 4) {
            menuComparePlayers(playerStats);
        } else if (userInput == 5) {
            delete playerStats;
            continueRunning = false;
        } else {
            cout << "Invalid Input" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    return 0;
}

//Menu for displaying the players on a team for a particular season.
void menuPlayersOnTeam(PlayerStats *playerStats) {
    string teamAbbreviation;
    string year;
    cout << "\n-----Show Players on Team-----" << endl;
    //User must input a team abbreviation(typically 2 or 3 characters) not the full team name.
    cout << "\tTeam(abbreviation): ";
    cin.ignore(10000,'\n');
    getline(cin, teamAbbreviation);
    //User must enter a year between 2010 and 2014.
    cout << "\tYear(2010-2014): ";
    getline(cin, year);
    //Prints if showPlayersOnTeam returns false, team not found or invalid year.
    if (!playerStats->showPlayersOnTeam(teamAbbreviation, atoi(year.c_str()))) {
        cout << "\t** Invalid information **" << endl;
    }
}

//Menu for displaying all stats for an individual player
void menuIndividualPlayer(PlayerStats *playerStats) {
    string playerName;
    cout << "\n-----Show Individual Player Stats-----" << endl;
    cout << "\tName: ";
    cin.ignore(10000,'\n');
    getline(cin, playerName);
    //Prints if showIndividualPlayerStats returns false, player is not found.
    if (!playerStats->showIndividualPlayerStats(playerName)) {
        cout << "\t** Invalid name **" << endl;
    }
}

//Menu that comes up when compare players is selected in the main menu
void menuComparePlayers(PlayerStats *playerStats) {
    bool continueComparing = true;
    while (continueComparing) {
        cout << "\n-----Compare Players-----" << endl;
        cout << "1. Select Player" << endl;
        cout << "2. Deselect Player" << endl;
        cout << "3. Show Selected Players" << endl;
        cout << "4. Compare Stats" << endl;
        cout << "5. Back" << endl;
        int userInput = 0;
        cin >> userInput;

        //Checks the user input
        if (userInput == 1) {
            //Only allows the user to select up to 5 players at once
            if (playerStats->numberOfPlayersSelected() < 5) {
                menuSelectPlayer(playerStats);
            } else {
                cout << "Only up to 5 players may be selected" << endl;
            }
        } else if (userInput == 2) {
            //Only allows the user to deselect players if there are players currently selected
            if (playerStats->numberOfPlayersSelected() != 0) {
                menuDeselectPlayer(playerStats);
            } else {
                cout << "No players to deselect" << endl;
            }
        } else if (userInput == 3) {
            playerStats->showSelectedPlayers();
        }else if (userInput == 4) {
            //Only compares players if there is at least one player selected
            if (playerStats->numberOfPlayersSelected() != 0) {
                menuCompareStats(playerStats);
            } else {
                cout << "No players to compare" << endl;
            }
        } else if (userInput == 5) {
            continueComparing = false;
        } else {
            cout << "Invalid Input" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

//Menu that is displayed when selecting a player to compare
void menuSelectPlayer(PlayerStats *playerStats) {
    string playerName;
    cout << "\n-----Select Player-----" << endl;
    cout << "\tName: ";
    cin.ignore(10000,'\n');
    getline(cin, playerName);
    if (playerStats->selectPlayer(playerName)) {
        cout << "\t** Player Selected **"<< endl;
    } else {
        cout << "\t** Invalid name **" << endl;
    }
}

//Menu that is displayed when deselecting a player
void menuDeselectPlayer(PlayerStats *playerStats) {
    string playerName;
    cout << "\n-----Deselect Player-----" << endl;
    cout << "\tName: ";
    cin.ignore(10000,'\n');
    getline(cin, playerName);
    if (playerStats->deselectPlayer(playerName)) {
        cout << "\t** Player Deselected **" << endl;
    } else {
        cout << "\t** Invalid name **" << endl;
    }
}

//Menu that is displayed when comparing player(s)
void menuCompareStats(PlayerStats *playerStats) {
    string year;
    cout << "\n-----Compare Stats-----" << endl;
    cout << "\tYear(2010-2014): ";
    cin.ignore(10000,'\n');
    getline(cin, year);
    if (!playerStats->compareStatsSideBySide(atoi(year.c_str()))) {
        cout << "\t** Invalid year **" << endl;
    }
}


