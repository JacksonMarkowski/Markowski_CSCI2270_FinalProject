#include "PlayerStats.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
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

Player* PlayerStats::findPlayer(std::string name) {
    Player *p;
    p = NULL;
    return p;
}

bool PlayerStats::selectPlayer(std::string name) {
    return false;
}

bool PlayerStats::deselectPlayer(std::string name) {
    return false;
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

    int fileYear = 2014;
    string line;
    getline(file, line);
    //getline(file, line);
    while(getline(file, line)) {
        istringstream individualPlayerRow(line);

        //Reads in player's name
        string lastName;
        string firstName;
        string fullName;
        getline(individualPlayerRow, lastName, ',');
        getline(individualPlayerRow, firstName, '"');
        fullName = firstName.substr(1) + " " + lastName.substr(1);

        Player *player = findPlayer(fullName);
        if (player == NULL) {
            player = new Player;
            players.push_back(player);
            //ToDo: add player to collection of all players

            player->name = fullName;

            //Reads in player's position
            string pos;
            getline(individualPlayerRow, pos, '\t');
            getline(individualPlayerRow, pos, '\t');
            player->pos = pos;

        } else {
            //ToDo:
            string ignore;
            getline(individualPlayerRow, ignore, '\t');
            getline(individualPlayerRow, ignore, '\t');
        }

        //ToDo: add player to team
        //Reads in player's team
        string team;
        getline(individualPlayerRow, team, '\t');

        //Reads in player's stats
        Stats newPlayerStats;
        newPlayerStats.year = fileYear;
        string stat;
        getline(individualPlayerRow, stat, '\t');
        newPlayerStats.games = atoi(stat.c_str());
        getline(individualPlayerRow, stat, '\t');
        newPlayerStats.atBats = atoi(stat.c_str());
        getline(individualPlayerRow, stat, '\t');
        newPlayerStats.runs = atoi(stat.c_str());
        getline(individualPlayerRow, stat, '\t');
        newPlayerStats.hits = atoi(stat.c_str());
        getline(individualPlayerRow, stat, '\t');
        newPlayerStats.doubles = atoi(stat.c_str());
        getline(individualPlayerRow, stat, '\t');
        newPlayerStats.triples = atoi(stat.c_str());
        getline(individualPlayerRow, stat, '\t');
        newPlayerStats.homeRuns = atoi(stat.c_str());
        getline(individualPlayerRow, stat, '\t');
        newPlayerStats.rbi = atoi(stat.c_str());
        getline(individualPlayerRow, stat, '\t');
        newPlayerStats.baseOnBalls = atoi(stat.c_str());
        getline(individualPlayerRow, stat, '\t');
        newPlayerStats.strickOuts = atoi(stat.c_str());
        getline(individualPlayerRow, stat, '\t');
        newPlayerStats.stollenBases = atoi(stat.c_str());
        getline(individualPlayerRow, stat, '\t');
        newPlayerStats.caugtStealing = atoi(stat.c_str());
        getline(individualPlayerRow, stat, '\t');
        newPlayerStats.average = atof(stat.c_str());
        getline(individualPlayerRow, stat, '\t');
        newPlayerStats.sluggingAverage = atof(stat.c_str());
        getline(individualPlayerRow, stat, '\t');
        newPlayerStats.onBasePercentage = atof(stat.c_str());
        getline(individualPlayerRow, stat, '\t');
        newPlayerStats.onBasePlusSlugging = atof(stat.c_str());

        player->seasonalStats.push_back(newPlayerStats);
    }
    cout << players[500]->name << endl;

}
