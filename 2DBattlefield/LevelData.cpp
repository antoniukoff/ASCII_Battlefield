#include "LevelData.h"

// Constructors
LevelData::LevelData() {}

// Destructor
LevelData::~LevelData() {
    for (int i = 0; i < NUM_ARMIES; i++) {
        for (int j = 0; j < armies[i].size(); j++) {
            delete armies[i][j];
        }
    }
}

// Public Methods

// Initialize Map
void LevelData::intiMap() {
    map.open("myMap.txt");
    if (map.fail()) {
        perror("myMap.txt");
        exit(1);
    }

    while (getline(map, levelInput)) {
        levelData.push_back(levelInput);
        soldierGrid.push_back(vector<Soldier*>());
        soldierGrid.back().resize(levelInput.size(), nullptr);
    }

    map.close();

    // Initialize soldier objects in the game map based on the characters in the level data
    for (int i = 0; i < levelData.size(); i++) {
        for (int j = 0; j < levelData[i].size(); j++) {
            char tile;
            tile = levelData[i][j];
            switch (tile) {
            case '1':
                armies[0].push_back(new Soldier("1", 1, tile, 5, 1, 10, 0));
                armies[0].back()->setPos(j, i);
                soldierGrid[i][j] = armies[0].back();
                break;

            case '2':
                armies[1].push_back(new Soldier("2", 2, tile, 10, 3, 10, 1));
                armies[1].back()->setPos(j, i);
                soldierGrid[i][j] = armies[1].back();
                break;
            }
        }
    }

    random_device::result_type seed = random_device()();
    mt19937 randomEngine(seed);
    Soldier* temp;

    for (int i = 0; i < NUM_ARMIES; i++) {
        for (int j = armies[i].size() - 1; j > 1; j--) {
            uniform_int_distribution<int> randSwap(0, j - 1);
            int swap = randSwap(randomEngine);
            temp = armies[i][j];
            armies[i][j] = armies[i][swap];
            armies[i][swap] = temp;
        }
    }
}

// Print the Map
void LevelData::printMap() {
    for (int i = 0; i < levelData.size(); i++) {
        cout << levelData[i] << endl;
    }
}

// Update the game state
void LevelData::Update() {
    char move;

    int i = 0;

    bool isDone = false;

    while (isDone == false) {
        isDone = true;
        for (int j = 0; j < NUM_ARMIES; j++) {
            if (i < armies[j].size()) {
                move = armies[j][i]->getMove(armies, NUM_ARMIES);
                processPlayerMove(move, armies[j][i]);
                isDone = false;
            }
        }
        i++;
    }
}

// Get a soldier at a specific position
Soldier* LevelData::getSoldier(int x, int y) {
    return soldierGrid[y][x];
}

// Private Methods

// Process player move
void LevelData::processPlayerMove(char d, Soldier* soldier) {
    int x, y;
    int targetX, targetY;
    x = soldier->getPosX();
    y = soldier->getPosY();
    switch (d) {
    case 'w': // up
        targetX = x;
        targetY = y - 1;
        break;
    case 'a': // left
        targetX = x - 1;
        targetY = y;
        break;
    case 's': // down
        targetX = x;
        targetY = y + 1;
        break;
    case 'd': // right
        targetX = x + 1;
        targetY = y;
        break;
    case'.':
        return;
    }
    char targetTile = getTile(targetX, targetY);
    switch (targetTile) {
    case '#':
        break;
    case '.':
        moveSoldier(soldier, targetX, targetY);
        break;
    default:
        battle(soldier, targetX, targetY);
        break;
    }
}

// Move a soldier to a new position
void LevelData::moveSoldier(Soldier* soldier, int targetx, int targety) {
    int x, y;
    x = soldier->getPosX();
    y = soldier->getPosY();

    setTile(x, y, '.', nullptr);
    setTile(targetx, targety, soldier->getCharacter(), soldier);

    soldier->setPos(targetx, targety);
}

// Execute a battle between two soldiers
void LevelData::battle(Soldier* soldier, int targetx, int targety) {
    int x, y;
    x = soldier->getPosX();
    y = soldier->getPosY();
    int enemyArmy;
    Soldier* targetSoldier = getSoldier(targetx, targety);

    if (targetSoldier == nullptr) {
        return;
    }
    enemyArmy = targetSoldier->getArmy();

    if (enemyArmy == soldier->getArmy()) {
        return;
    }

    int result = targetSoldier->takeDamage(soldier->attack());
    if (result == 1) {
        for (int i = 0; i < armies[enemyArmy].size(); i++) {
            if (armies[enemyArmy][i] == targetSoldier) {
                armies[enemyArmy][i] = armies[enemyArmy].back();
                armies[enemyArmy].pop_back();

                delete targetSoldier;

                setTile(targetx, targety, '.', nullptr);
                break;
            }
        }
    }
}
