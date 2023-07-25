#pragma once
#include <fstream> 
#include <vector>
#include <iostream> 
#include <string> 
#include "Soldier.h"
#include <random>


using namespace std;

const int NUM_ARMIES = 2;

class LevelData
{
public:
    LevelData();

    ~LevelData();

    // Getters and Setters
    char getTile(int x, int y) {
        return levelData[y][x];
    }
    Soldier* getSoldier(int x, int y);

    void setTile(int x, int y, char tile, Soldier* soldier) {
        levelData[y][x] = tile;
        soldierGrid[y][x] = soldier;
    }

    // Public Functions
    void intiMap();
    void printMap();
   
    void Update();
    

private:
    void moveSoldier(Soldier* soldier, int x, int y);
    void battle(Soldier* soldier, int targetx, int targety);
    // Private Functions
    void processPlayerMove(char d, Soldier* soldier);


    // Private Variables
    ifstream map;
    vector<string> levelData;
    vector<vector <Soldier*> > soldierGrid;
    string levelInput;
    vector <Soldier* > armies[NUM_ARMIES];
    
};
