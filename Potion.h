#ifndef POTION_H
#define POTION_H

#include "Item.h"
#include "CharacterDecorator.h"
#include <string>

class Potion: public Item {
	string type;
	CharacterDecorator *effect;
public:
	Potion(size_t x, size_t y, string type, CharacterDecorator *effect);
	bool isWalkable() override;
	bool isSpawnable() override;
	void pickup(CharacterDecorator *entity) override;
};

#endif
