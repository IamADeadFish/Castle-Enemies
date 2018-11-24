#pragma once
#include "Enemy.h"

class FreezingEnemy : public Enemy
{
public:
	FreezingEnemy();
	~FreezingEnemy();
	virtual void SetColor();
	virtual void Attack(Tower * Tptr); // Attack tower
	virtual void SetPriority();
	double GetPriority()const;
	static void SetC1(double c1);
	static void SetC2(double c2);
	static void SetC3(double c3);
	static void SetC4(double c4);
	static double GetC1();
	static double GetC2();
	static double GetC3();
	static double GetC4();

private:
	virtual void DecrementHealth(double f);
	static double C1, C2, C3, C4;
};