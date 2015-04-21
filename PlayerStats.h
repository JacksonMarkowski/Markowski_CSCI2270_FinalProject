#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H
#include <vector>
#include <iostream>

struct Stats {
    int year;
    int games;
    int atBats;
    int runs;
    int hits;
    int doubles;
    int triples;
    int homeRuns;
    int rbi;
    int baseOnBalls;
    int strickOuts;
    int stollenBases;
    int caugtStealing;
    double average;
    double sluggingAverage;
    double onBasePercentage;
    double onBasePlusSlugging;
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

};

#endif // PLAYERSTATS_H
