#ifndef ZOMBIES_H
#define ZOMBIES_H
#include <string>
#include <vector>
struct vertex;
struct itm;

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
    std::string name;
    std::vector<adjVertex> adj;
    int id=-1;
    bool visited=false;
    bool userVisit=false;
    int distance;
    std::vector<vertex*> path;
    std::vector<itm> it;
};
struct queueVertex{
    int distance;   //number of edges on path
       //vertices on the path
};
struct itm
{
    std::string name;
    int uses;
    std::string type;
    bool found;
    bool usable;
    int killNum=0;
    vertex *loc;
};
struct user
{
    vertex *currentArea;
    std::string name;
    int party = 1;
    int health=100;
    int kills = 0;
    std::vector<itm> items;
    bool carInLoc = false;
    bool victory=false;
};


class Graph
{
    public:
        Graph();
        ~Graph();
        void travelCar();
        void addEdge(std::string v1, std::string v2, int weight);
        void addVertex(std::string name);
        void displayEdges();
        void findDistricts();
        bool idCheck();
        void onFoot();
        void Victory();
        void setUser(std::string u, int p);
        void shortestPath(std::string start, std::string endi);
        int shortestDistance(std::string start, std::string endi);
        void displayStats();
        void createItems();
        void Look();
        void Dead();
        void fightZombies();
        std::string findName(int index);
        vertex* findV(std::string name);
        vertex findVertex(int i);
        user u{};
    protected:
    private:
        //vector<edge> edges;
        std::vector<vertex> vertices;
        std::vector<itm> allItems;
};
#endif
