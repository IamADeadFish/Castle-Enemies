#pragma once
#include "Enemy.h"

class ShieldedFighterEnemy : public Enemy
{
public:
	ShieldedFighterEnemy();
	~ShieldedFighterEnemy();
	virtual void SetColor();
	static void SetC1(double c1);
	static void SetC2(double c2);
	static void SetC3(double c3);
	static double GetC1();
	static double GetC2();
	static double GetC3();
	double GetPriority()const;
	virtual void Attack(Tower * Tptr); // Attack tower
	virtual void SetPriority();


private:
	static double C1, C2, C3;
	virtual void DecrementHealth(double f);

};