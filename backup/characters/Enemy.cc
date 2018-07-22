#include <stdlib.h>
#include "Enemy.h"
#include "Character.h"
#include "DungeonMap.h"
#include "Direction.h"
#include <math.h>

using namespace std;

Enemy::Enemy(size_t x, size_t y, char icon, double hp, double maxHp, double atk, double def) : 
	BaseCharacter(x, y, icon, hp, maxHp, atk, def){}

void Enemy::moveTick(DungeonMap &map) {
	vector<Direction> dirs = map.getSpawnableDirections(this);
	// If the enemy is not stuck in a location
	if (dirs.size() > 0) {
		// Moves in one of the random available directions
		// TODO map.move(dirs[rand() % dirs.size()]);
	}
}

bool Enemy::hit(Character &other) {
	if (rand() % 2) {
		BaseCharacter::hit(other);
		return true;
	}
	return false;
}

Enemy::~Enemy(){}