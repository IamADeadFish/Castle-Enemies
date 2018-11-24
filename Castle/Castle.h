#pragma once

#include "..\Defs.h"
#include "Tower.h"

class Castle
{
	Tower Towers[NoOfRegions];

public:

	Castle();
	void SetTowersHealth(double h);
	void SetFreezed (int index , int f);
	void SetTowersFirePower(double f);
	void SetTowersMaxEnemies(double N);
	bool CastleLose()const;
	int GetTowersMaxEnemies()const;
	double GetTowerFirePower()const;
	double GetTowerHealth(int index) const;
	double GetUnpavedDistance(int index)const;
	bool IsFreezed (int index,int t) const;
	void AttackTower (int index , Enemy * e);
	void AttackEnemy (int index , Enemy * e);
	void ResetUnpavedDistance();
	void ResetFreezed();
	bool IsKilled(int i)const;
};