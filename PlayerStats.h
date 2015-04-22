#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H
#include <vector>
#include <iostream>

struct Stats {
    int intStats[13]; //"Year", "G", "AB", "R", "H", "2B", "3B", "HR", "RBI", "BB", "K", "SB", "CS"
    double doubleStats[4]; //"AVG", "SLG", "OBP", "OPS"
};

struct Player {
    std::string name;
    std::string pos;
    std::vector<Stats> seasonalStats;
    //std::string team;
};

struct Team {
    std::string name;
    std::string abbreviation;
    std::vector<Player*> roster[5];
};

class PlayerStats {
    public:
        PlayerStats();
        ~PlayerStats();
        void showTeams();
        bool showPlayersOnTeam(std::string teamAbbreviation, int year);
        bool showIndividualPlayerStats(std::string name);
        bool selectPlayer(std::string name);
        int numberOfPlayersSelected();
        bool deselectPlayer(std::string name);
        void showSelectedPlayers();
        bool compareStatsSideBySide(int year);
    protected:
    private:
        void readInStats();
        int hashSum(std::string name, int s);
        Player* findPlayer(std::string name);
        void addPlayer(Player* newPlayer);
        void addPlayerToTeam(Player *player, std::string teamAbbreviation, int year);
        void initializeTeams();
        Team* findTeam(std::string teamAbbreviation);
        Team* teams[30];
        std::vector<Player*> players[26];
        std::vector<Player*> selectedPlayers;
        std::string statsTypes[17] = {"Year", "G", "AB", "R", "H", "2B", "3B", "HR", "RBI", "BB", "K", "SB", "CS", "AVG", "SLG", "OBP", "OPS"};

};

#endif // PLAYERSTATS_H
