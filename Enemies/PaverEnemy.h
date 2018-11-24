#pragma once
#include "Enemy.h"

class PaverEnemy : public Enemy
{
public:
	PaverEnemy();
	~PaverEnemy();
	virtual void SetColor();
	virtual void Move(int p);
	virtual void Attack(Tower * Tptr); // Attack tower


private:

};