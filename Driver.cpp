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
    //ToDo: possible make this not a pointer
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

        if (userInput == 1) {
            //playerStats->showTeams();
        } else if (userInput == 2) {
            menuPlayersOnTeam(playerStats);
        } else if (userInput == 3) {
            menuIndividualPlayer(playerStats);
        } else if (userInput == 4) {
            menuComparePlayers(playerStats);
        } else if (userInput == 5) {
            continueRunning = false;
        }
    }
    return 0;
}

void menuPlayersOnTeam(PlayerStats *playerStats) {
    string teamName;
    string year;
    cout << "\n-----Show Players on Team-----" << endl;
    cout << "\tTeam: ";
    cin.ignore(10000,'\n');
    getline(cin, teamName);
    cout << "\tYear: ";
    getline(cin, year);
}

void menuIndividualPlayer(PlayerStats *playerStats) {
    string playerName;
    cout << "\n-----Show Individual Player Stats-----" << endl;
    cout << "\tName: ";
    cin.ignore(10000,'\n');
    getline(cin, playerName);
    if (!playerStats->showIndividualPlayerStats(playerName)) {
        cout << "\t** Invalid name **" << endl;
    }
}

void menuComparePlayers(PlayerStats *playerStats) {
    bool continueComparing = true;
    while (continueComparing) {
        cout << "\n-----Compare Players-----" << endl;
        cout << "1. Select Player" << endl;
        cout << "2. Deselect Player" << endl;
        cout << "3. Compare Stats" << endl;
        cout << "4. Back" << endl;
        int userInput = 0;
        cin >> userInput;

        if (userInput == 1) {
            menuSelectPlayer(playerStats);
        } else if (userInput == 2) {
            menuDeselectPlayer(playerStats);
        } else if (userInput == 3) {
            menuCompareStats(playerStats);
        } else if (userInput == 4) {
            continueComparing = false;
        }
    }
}

void menuSelectPlayer(PlayerStats *playerStats) {
    string playerName;
    cout << "\n-----Select Player-----" << endl;
    cout << "\tName: ";
    cin.ignore(10000,'\n');
    getline(cin, playerName);
    if (!playerStats->selectPlayer(playerName)) {
        cout << "\t** Invalid name **" << endl;
    }
}

void menuDeselectPlayer(PlayerStats *playerStats) {
    string playerName;
    cout << "\n-----Deselect Player-----" << endl;
    cout << "\tName: ";
    cin.ignore(10000,'\n');
    getline(cin, playerName);
    if (!playerStats->deselectPlayer(playerName)) {
        cout << "\t** Invalid name **" << endl;
    }
}

void menuCompareStats(PlayerStats *playerStats) {

}
