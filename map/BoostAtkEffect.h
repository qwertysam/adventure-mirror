#ifndef BOOSTATKEFFECT_H
#define BOOSTATKEFFECT_H

#include "CharacterDecorator.h"

class BoostAtkEffect: public CharacterDecorator {
public:
	BoostAtkEffect();
	double getAtk() override;
	std::string to_string() override;
};

#endif

