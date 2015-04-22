#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H
#include <vector>
#include <iostream>

struct Stats {
    int intStats[13]; //"Year", "G", "AB", "R", "H", "2B", "3B", "HR", "RBI", "BB", "K", "SB", "CS"
    double doubleStats[4]; //"AVG", "SLG", "OBP", "OPS"
};

struct Player {
    std::vector<Stats> seasonalStats;
    std::string name;
    std::string pos;
    //std::string team;
};

struct Team {
    std::string name;
    int year;
    std::vector<Player> roster;
};

class PlayerStats {
    public:
        PlayerStats();
        ~PlayerStats();
        void showTeams();
        bool showPlayersOnTeam(std::string team, int year);
        bool showIndividualPlayerStats(std::string name);
        bool selectPlayer(std::string name);
        bool deselectPlayer(std::string name);
        void showSelectedPlayers();
        void compareStatsSideBySide();
        void compareStatsGraph();
    protected:
    private:
        void readInStats();
        int hashSum(std::string name, int s);
        Player* findPlayer(std::string name);
        void addPlayer(Player* newPlayer);
        std::vector<Team> teams;
        std::vector<Player*> players[26];
        std::vector<Player*> selectedPlayers;
        std::string statsTypes[17] = {"Year", "G", "AB", "R", "H", "2B", "3B", "HR", "RBI", "BB", "K", "SB", "CS", "AVG", "SLG", "OBP", "OPS"};

};

#endif // PLAYERSTATS_H
