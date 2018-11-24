#include "Castle.h"

Castle::Castle()
{
}


void Castle:: SetFreezed (int index , int f)
{
	Towers[index].SetFreezed(f);
}
void Castle::SetTowersHealth(double h)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetHealth(h);
	}
}
void Castle::SetTowersFirePower(double f)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetFirePower(f);
	}
}
bool Castle::CastleLose() const
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		if(!Towers[i].IsKilled())
			return false;
	}
	return true;
}
void Castle::SetTowersMaxEnemies(double N)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetMaxEnemies(N);
	}
}
int Castle::GetTowersMaxEnemies()const
{
	for (int i=0; i<NoOfRegions; i++)
		if(!Towers[i].IsKilled())
			return Towers[i].GetMaxEnemies();
	return 0;
}
double Castle::GetTowerFirePower()const
{
	for (int i=0; i<NoOfRegions; i++)
		if(!Towers[i].IsKilled())
			return Towers[i].GetFirePower();
	return 0;
}
double Castle::GetTowerHealth(int index) const
{
	if(!Towers[index].IsKilled())
		return Towers[index].GetHealth();
	else
		return 0;
}
double Castle::GetUnpavedDistance(int index)const
{
	return Towers[index].GetUnpavedDistance();
}
bool Castle::IsFreezed (int index, int t) const
{
	return 	Towers[index].IsFreezed(t);

}

void Castle:: AttackTower (int index , Enemy * e)
{
Towers[index].AttackTower(e);
}

void Castle:: AttackEnemy (int index , Enemy * e)
{
Towers[index].AttackEnemy(e);
}

void Castle::ResetUnpavedDistance()
{
	for (int i = 0; i < NoOfRegions; i++)
		Towers[i].ResetDistance();
}

void Castle::ResetFreezed()
{
	for (int i = 0; i < NoOfRegions; i++)
		Towers[i].ResetFreezed();
}

bool Castle::IsKilled(int i) const
{
	return Towers[i].IsKilled();
}

