#pragma once
#include "Enemy.h"

class FighterEnemy : public Enemy
{
public:
	FighterEnemy();
	~FighterEnemy();
	virtual void SetColor();
	virtual void Attack(Tower * Tptr); // Attack tower


private:

};