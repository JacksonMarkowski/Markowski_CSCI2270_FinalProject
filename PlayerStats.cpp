#include "PlayerStats.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

PlayerStats::PlayerStats() {
    initializeTeams();
    readInStats();
}

PlayerStats::~PlayerStats() {

}

void PlayerStats::showTeams() {
    for (int i = 0; i < 30; i++) {
        cout << teams[i]->name << " - " << teams[i]->abbreviation << endl;
    }
}

bool PlayerStats::showPlayersOnTeam(std::string teamAbbreviation, int year) {
    Team *team = findTeam(teamAbbreviation);
    if (team != NULL) {
        if (year >= 2010 && year <= 2014) {
            cout << team->name << " - " << team->abbreviation << " - " << year << endl;
            int rosterYear = std::abs(year - 2014);
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

int PlayerStats::numberOfPlayersSelected() {
    return selectedPlayers.size();
}

//ToDO: only allow so many players to be selected at once (3ish)
bool PlayerStats::selectPlayer(std::string name) {
    Player *p = findPlayer(name);
    if (p != NULL) {
        selectedPlayers.push_back(p);
        return true;
    } else {
        return false;
    }
}

bool PlayerStats::deselectPlayer(std::string name) {
    for (int i = 0; i < selectedPlayers.size(); i++) {
        if (selectedPlayers[i]->name == name) {
            selectedPlayers.erase(selectedPlayers.begin()+i);
            return true;
        }
    }
    return false;
}

void PlayerStats::showSelectedPlayers() {
    int selectedPlayersSize = selectedPlayers.size();
    if (selectedPlayersSize == 0) {
        cout << "No players selected" << endl;
    } else {
        cout << "Players selected: ";
        for (int i = 0; i < selectedPlayersSize; i++) {
            cout << selectedPlayers[i]->name;
            if (i < selectedPlayersSize - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
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
                string ignore;
                getline(individualPlayerRow, ignore, '\t');
                getline(individualPlayerRow, ignore, '\t');
            }

            //Reads in player's team
            string teamAbbreviation;
            getline(individualPlayerRow, teamAbbreviation, '\t');
            addPlayerToTeam(player, teamAbbreviation, fileYear);

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

void PlayerStats::addPlayerToTeam(Player *player, std::string teamAbbreviation, int year) {
    Team *t = findTeam(teamAbbreviation);
    if (t != NULL) {
        t->roster[std::abs(year - 2014)].push_back(player);

    }
}

void PlayerStats::initializeTeams() {
    std::string teamName[30] = {"Los Angeles Angles", "Atlanta Braves", "Houston Astros", "Milwaukee Brewers",
    "Oakland Athletics", "St. Louis Cardinals", "Toronto Blue Jays", "Chicago Cubs", "Tampa Bay Rays", "Arizona Diamondbacks",
    "Cleveland Indians", "Los Angeles Dodgers", "Seattle Mariners", "San Francisco Giants", "Baltimore Orioles", "Miami Marlins",
    "Texas Rangers", "New York Mets", "Boston Red Sox", "Washington Nationals", "Kansas City Royals", "San Diego Padres", "Detroit Tigers",
    "Philadelphia Phillies", "Minnesota Twins", "Pittsburgh Pirates", "Chicago White Sox", "Cincinnati Reds", "New York Yankees", "Colorado Rockies"};
    std::string teamAbbreviation[30] = {"LAA", "ATL", "HOU", "MIL", "OAK", "STL", "TOR", "CHC", "TB", "AZ", "CLE", "LAD", "SEA", "SF", "BAL", "MIA",
    "TEX", "NYM", "BOS", "WSH", "KC", "SD", "DET", "PHI", "MIN", "PIT", "CHW", "CIN", "NYY", "COL"};

    for (int i = 0; i < 30; i++) {
        Team *newTeam = new Team;
        newTeam->name = teamName[i];
        newTeam->abbreviation = teamAbbreviation[i];
        teams[i] = newTeam;
    }
}

Team* PlayerStats::findTeam(std::string teamAbbreviation) {
    for (int i = 0; i < 30; i++) {
        if (teamAbbreviation == teams[i]->abbreviation) {
            return teams[i];
        }
    }
    Team *team;
    team = NULL;
    return team;
}
