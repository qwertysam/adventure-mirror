#ifndef BASECHARACTER_H
#define BASECHARACTER_H

#include "Character.h"
#include "Item.h"

class BaseCharacter: public Character {
protected:
	size_t x, y;
	char icon;
	double hp;
	double maxHp;
	double atk;
	double def;
	int gold = 0;
	int floor = 0;
	CharacterType type;
public:
	bool deathCheck() override;
	BaseCharacter(size_t x, size_t y, char icon, double hp, double maxHp, double atk, double def);
	bool hit(Character &other) override;
	double hitPower(Character &other) override;
	bool takeDamage(Character &from, double damage) override;
	void addHP(double hp) override;
	double score() override;
	double getHP() override;
	double getMaxHP() override;
	double getAtk() override;
	double getDef() override;
	void addGold(int value) override;
	int getGold() override;
	int getFloor() override;
	size_t getX() override;
	size_t getY() override;
	void setX(size_t x) override;
	void setY(size_t y) override;
	char print() override;
	CharacterType getType();
};

#endif