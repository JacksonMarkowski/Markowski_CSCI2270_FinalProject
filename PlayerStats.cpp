#include "PlayerStats.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

PlayerStats::PlayerStats() {
    readInStats();
}

PlayerStats::~PlayerStats() {

}

void PlayerStats::showTeams() {

}

void PlayerStats::showPlayersOnTeam(std::string team, int year) {

}

Player PlayerStats::findPlayer(std::string name) {

}

bool PlayerStats::selectPlayer(std::string name) {

}

bool PlayerStats::deselectPlayer(std::string name) {

}

void PlayerStats::compareStatsSideBySide() {

}

void PlayerStats::compareStatsGraph() {

}

void PlayerStats::readInStats() {
    //ToDO: add all file names to an array in order to open and read all them with a loop
    ifstream file;
    file.open("MLB_Stats/2014_Batting.txt");
    if (!file)
    {
        cout << "Could not open the file" << endl;
        return;
    }

    string line;
    getline(file, line);
    getline(file, line);
    //while(getline(file, line)) {
        //ToDO: check if player exists, if so add to stats, if not create new player
        istringstream individualPlayerRow(line);
        Player newPlayer;

        //Reads in player's name
        string lastName;
        string firstName;
        getline(individualPlayerRow, lastName, ',');
        getline(individualPlayerRow, firstName, '"');
        newPlayer.name = firstName.substr(1) + " " + lastName.substr(1);

        //Reads in player's position
        string pos;
        getline(individualPlayerRow, pos, '\t');
        getline(individualPlayerRow, pos, '\t');
        newPlayer.pos = pos;

        //Reads in player's team
        string team;
        getline(individualPlayerRow, team, '\t');
        newPlayer.team = team;

        //Reads in player's stats
        /*
        string stat;
        getline(individualPlayerRow, stat, '\t');
        newPlayer.games = stat;
        getline(individualPlayerRow, stat, '\t');
        newPlayer.atBats = stat;
        getline(individualPlayerRow, stat, '\t');
        newPlayer.runs = stat;
        getline(individualPlayerRow, stat, '\t');
        newPlayer.hits = stat;
        getline(individualPlayerRow, stat, '\t');
        newPlayer.doubles = stat;
        getline(individualPlayerRow, stat, '\t');
        newPlayer.triples = stat;
        getline(individualPlayerRow, stat, '\t');
        newPlayer.homeRuns = stat;
        getline(individualPlayerRow, stat, '\t');
        newPlayer.rbi = stat;
        getline(individualPlayerRow, stat, '\t');
        newPlayer.baseOnBalls = stat;
        getline(individualPlayerRow, stat, '\t');
        newPlayer.strickOuts = stat;
        getline(individualPlayerRow, stat, '\t');
        newPlayer.stollenBases = stat;
        getline(individualPlayerRow, stat, '\t');
        newPlayer.caugtStealing = stat;
        getline(individualPlayerRow, stat, '\t');
        newPlayer.average = stat;
        getline(individualPlayerRow, stat, '\t');
        newPlayer.sluggingAverage = stat;
        getline(individualPlayerRow, stat, '\t');
        newPlayer.onBasePercentage = stat;
        getline(individualPlayerRow, stat, '\t');
        newPlayer.onBasePlusSlugging = stat;
        }
        */
    //}

}
