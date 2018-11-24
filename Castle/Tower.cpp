#include "Tower.h"
#include "..\Enemies\Enemy.h"
Tower::Tower()
{
	Health = 0;
	FirePower = 0;
	UnpavedDistance = 30;
}
Tower::~Tower()
{

}

void Tower:: SetFreezed(int f)
{
	if (f > Freezed)
		Freezed = f;
}

void Tower::ResetDistance()
{
	UnpavedDistance = 30;
}

void Tower::ResetFreezed()
{
	Freezed = 0;
}

void Tower::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}
void Tower::DecrementUnpavedDistance(double p)
{
	UnpavedDistance -= (p > 0) ? p : 0;
	if (UnpavedDistance < 2)
		UnpavedDistance = 2;
}

double Tower::GetHealth() const
{
	return Health;
}
double Tower::GetFirePower()const
{
	return FirePower;
}
double Tower::GetUnpavedDistance()const
{
	return UnpavedDistance;
}
bool Tower:: IsFreezed(int t) const
{
	return Freezed > t;
}
bool Tower::IsKilled()const
{
	return Health == 0;
}
void Tower::SetFirePower(double f)
{
	FirePower = (f > 0) ? f : 0;
}
void Tower:: SetMaxEnemies(int N)
{
	MaxEnemies=N;
}
int Tower::GetMaxEnemies() const
{
	return MaxEnemies;
}

void Tower:: AttackTower (Enemy * e)
{
	e->Attack(this);
}
void Tower:: AttackEnemy(Enemy * e)
{
	e->Attacked(GetFirePower());
}