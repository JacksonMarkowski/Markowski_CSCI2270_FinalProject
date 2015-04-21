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

bool PlayerStats::showPlayersOnTeam(std::string team, int year) {

}

bool PlayerStats::showIndividualPlayerStats(std::string name) {
    cout << name << endl;
    Player *p = findPlayer(name);
    if (p != NULL) {
        cout << p->name << " - " << p->pos << endl;
    } else {
        return false;
    }
}

Player* PlayerStats::findPlayer(std::string name) {
    std::vector<Player*> playersAtHashSum = players[hashSum(name, 26)];
    for (int i = 0; i < playersAtHashSum.size(); i++) {
        if (playersAtHashSum[i]->name == name) {
            return playersAtHashSum[i];
        }
    }
    Player *p;
    p = NULL;
    return p;
}

bool PlayerStats::selectPlayer(std::string name) {
    return false;
}

bool PlayerStats::deselectPlayer(std::string name) {
}

void PlayerStats::compareStatsSideBySide() {

}

void PlayerStats::compareStatsGraph() {

}

void PlayerStats::readInStats() {
    //ToDO: Clean up opening files and reading in data
    ifstream file;
    int fileYear = 2015;
    for (int i = 0; i < 5; i++) {
        fileYear--;
        if (i == 0) file.open("MLB_Stats/2014_Batting.txt");
        if (i == 1) file.open("MLB_Stats/2013_Batting.txt");
        if (i == 2) file.open("MLB_Stats/2012_Batting.txt");
        if (i == 3) file.open("MLB_Stats/2011_Batting.txt");
        if (i == 4) file.open("MLB_Stats/2010_Batting.txt");

        string line;
        getline(file, line);
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

                player->name = fullName;
                addPlayer(player);

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
            string stat;
            Stats newPlayerStats;
            newPlayerStats.year = fileYear;
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

            //Adds newPlayerStats to player's vector of seasonalStats
            player->seasonalStats.push_back(newPlayerStats);
        }
        file.close();
    }
}

int PlayerStats::hashSum(std::string name, int s) {
    int sum = 0;
    sum = name.at(0) % s;
    return sum;
}

void PlayerStats::addPlayer(Player *newPlayer) {
    players[hashSum(newPlayer->name, 26)].push_back(newPlayer);
}
