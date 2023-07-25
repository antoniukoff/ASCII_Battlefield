#include "Soldier.h"
#include <random>
#include <ctime>

// Constructors
Soldier::Soldier() {}

Soldier::Soldier(string name_, int level_, char tile_, int attack_,
	int armourHP_, int HP_, int army) {
	name = name_;
	level = level_;
	tile = tile_;
	_attack = attack_;
	armourHP = armourHP_;
	HP = HP_;
	army_ = army;
}

// Getter and Setter Methods
// Currently not present in the code

// Business Logic Methods

// Attack method
int Soldier::attack() {
	static default_random_engine randomEngine(time(0));
	uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);
}

// Take Damage method
int Soldier::takeDamage(int attack) {
	attack -= armourHP;
	if (attack > 0) {
		HP -= attack;
		if (HP <= 0) {
			return 1;
		}
	}
	return 0;
}

// Get Move method
char Soldier::getMove(vector<Soldier*> armies[], int numArmies) {
	static default_random_engine randEngine(time(0));
	uniform_int_distribution<int> moveRoll(0, 6);

	Soldier* closestSoldier = getClosestEnemy(armies, numArmies);

	if (closestSoldier == nullptr) {
		return '.';
	}

	int soldierX, soldierY;

	soldierX = closestSoldier->getPosX();
	soldierY = closestSoldier->getPosY();

	int dx = posx - soldierX;
	int dy = posy - soldierY;
	int adx = abs(dx);
	int ady = abs(dy);

	//Moving along X axis
	if (adx > ady) {
		if (dx > 0) {
			return 'a';
		}
		else {
			return 'd';
		}
	}
	else { //Moving along Y axis
		if (dy > 0) {
			return 'w';
		}
		else {
			return 's';
		}
	}
}

// Get Closest Enemy method
Soldier* Soldier::getClosestEnemy(vector<Soldier*> armies[], int numArmies) {
	Soldier* closestSoldier = nullptr;
	int closestDistance = INT_MAX;
	int enemyX, enemyY;
	int distance;
	for (int i = 0; i < numArmies; i++) {
		if (i != army_) {
			for (int j = 0; j < armies[i].size(); j++) {
				enemyX = armies[i][j]->getPosX();
				enemyY = armies[i][j]->getPosY();

				distance = abs(enemyX - posx) + abs(enemyY - posy);
				if (distance < closestDistance) {
					closestSoldier = armies[i][j];
					closestDistance = distance;
				}
			}
		}
	}
	return closestSoldier;
}
