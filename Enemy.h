#ifndef ENEMY_H
#define ENEMY_H

#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter{
public :
        Enemy(size_t x, size_t y, char icon, double hp, double maxHp, double atk, double def);
	bool hit(Character &other) override;
	virtual ~Enemy() = 0;
};
#endif
