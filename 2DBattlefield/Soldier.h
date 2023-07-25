#pragma once
#include <string>
#include <vector>

using namespace std;

class Soldier
{
public:
    // Constructors
    Soldier();
    Soldier(string name, int level, char tile, int attack, int armourHP, int HP, int army);

    // Getters and Setters
    int getPosX() { return posx; }
    int getPosY() { return posy; }
    int getArmy() { return army_; }
    string getName() { return name; }
    char getCharacter() { return tile; }

    void setPos(int x, int y) {
        posx = x;
        posy = y;
    }

    // Business Logic Methods
    int attack();
    int takeDamage(int attack);
    // AI move command
    char getMove(vector<Soldier*> armies[], int numArmies);

private:
    Soldier* getClosestEnemy(vector<Soldier*> armies[], int numArmies);

    string name;
    char tile;
    int level;
    int _attack;
    int armourHP;
    int HP;
    int army_;
    int posx, posy;
};
