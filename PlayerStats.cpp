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
    return false;
}

bool PlayerStats::showIndividualPlayerStats(std::string name) {
    Player *player = findPlayer(name);
    if (player != NULL) {
        cout << player->name << " - " << player->pos << endl;
        int seasonalStatsSize = player->seasonalStats.size();
        for (int i = 0; i < 17; i++) {
            cout << statsTypes[i];
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
            if (i == 4) fullName = fullName.substr(1);

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
            newPlayerStats.intStats[0] = fileYear;
            for (int j = 1; j < 13; j++) {
                getline(individualPlayerRow, stat, '\t');
                newPlayerStats.intStats[j] = atoi(stat.c_str());
            }
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

int PlayerStats::hashSum(std::string name, int s) {
    int sum = 0;
    sum = name.at(0) % s;
    return sum;
}

Player* PlayerStats::findPlayer(std::string name) {
    std::vector<Player*> playersAtHashSum = players[hashSum(name, 26)];
    for (int i = 0; i < playersAtHashSum.size(); i++) {
        if (playersAtHashSum[i]->name == name) {
            return playersAtHashSum[i];
        }
    }
    Player *player;
    player = NULL;
    return player;
}

void PlayerStats::addPlayer(Player *newPlayer) {
    players[hashSum(newPlayer->name, 26)].push_back(newPlayer);
}
