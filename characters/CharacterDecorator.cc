#include "CharacterDecorator.h"
#include "Character.h"
#include "Item.h"

CharacterDecorator::CharacterDecorator() {}
CharacterDecorator::CharacterDecorator(int floor) : activeFloor{floor} {}
CharacterDecorator::CharacterDecorator(Character *component) : component{component}, activeFloor{component->getFloor()} {}

bool CharacterDecorator::hit(Character &other) {
	return component->hit(other);
}

bool CharacterDecorator::takeDamage(Character &from, double damage) {
	return component->takeDamage(from, damage);
}

double CharacterDecorator::hitPower(Character &other) { return component->hitPower(other); }

void CharacterDecorator::decorate(CharacterDecorator *o) {
	o->component = component;
	component = o;
}

void CharacterDecorator::addHP(double hp) { component->addHP(hp); }
double CharacterDecorator::score() { return component->score(); }
double CharacterDecorator::getHP() { return component->getHP(); }
double CharacterDecorator::getMaxHP() { return component->getMaxHP(); }
double CharacterDecorator::getAtk() { return component->getAtk(); }
double CharacterDecorator::getDef() { return component->getDef(); }
void CharacterDecorator::addGold(int value) { component->addGold(value); }
int CharacterDecorator::getGold() { return component->getGold(); }
int CharacterDecorator::getFloor() { return component->getFloor(); }
size_t CharacterDecorator::getX() { return component->getX(); }
size_t CharacterDecorator::getY() { return component->getY(); }
void CharacterDecorator::setX(size_t x) { component->setX(x); }
void CharacterDecorator::setY(size_t y) { component->setY(y); }
char CharacterDecorator::print() { return component->print(); }
bool CharacterDecorator::deathCheck() { return component->deathCheck(); }
CharacterType CharacterDecorator::getType() { return component->getType(); }
