#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"

enum class CharacterType {
	Shade,
	Drow,
	Vampire,
	Troll,
	Goblin,
	Human,
	Dwarf,
	Elf,
	Orc,
	Merchant,
	Dragon,
	Halfling
};

class Character: public Entity {
protected:
	virtual void deathCheck() = 0;
public:
	Character();
	virtual void hit(Character &other) = 0;
	virtual void damage(Character &other, int damage) = 0;
	virtual int score() = 0;
	virtual int getHP() = 0;
	virtual int getMaxHP() = 0;
	virtual int getAtk() = 0;
	virtual int getDef() = 0;
	virtual void addGold(int value) = 0;
	virtual int getGold() = 0;
	virtual int getFloor() = 0;
	virtual CharacterType getType() = 0;
	virtual ~Character() = 0;
};

#endif
