#pragma once
#include "Enemy.h"

class HealerEnemy : public Enemy
{
public:
	HealerEnemy();
	~HealerEnemy();
	virtual void SetColor();
	virtual void Attack(Tower * Tptr); // Attack tower


private:

};