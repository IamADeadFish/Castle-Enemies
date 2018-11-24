#include "ShieldedFighterEnemy.h"

ShieldedFighterEnemy::ShieldedFighterEnemy() : Enemy()
{
	type=SHIELDED;
}
double ShieldedFighterEnemy::C1 = 0;
double ShieldedFighterEnemy::C2 = 0;
double ShieldedFighterEnemy::C3 = 0;

ShieldedFighterEnemy::~ShieldedFighterEnemy()
{
}
void ShieldedFighterEnemy::SetColor()
{
	Clr = RED;
}
void ShieldedFighterEnemy::DecrementHealth(double f)
{
	Health -= f / 2 / Distance;
}
void  ShieldedFighterEnemy::SetC1(double c1)
{
	C1 = c1;
}
void ShieldedFighterEnemy::SetC2(double c2)
{
	C2 = c2;
}
void ShieldedFighterEnemy::SetC3(double c3)
{
	C3 = c3;
}
double ShieldedFighterEnemy::GetC1()
{
	return C1;
}
double ShieldedFighterEnemy::GetC2()
{
	return C2;
}
double ShieldedFighterEnemy::GetC3()
{
	return C3;
}
double ShieldedFighterEnemy::GetPriority()const
{
	if (!IsActive())
		return 0;
	return (FirePower * C1 / Distance + C2 / (RemainingTimeforShot()+1) + Health * C3);
}
void ShieldedFighterEnemy::Attack(Tower * Tptr)
{
	double damage = FirePower * 2  / Distance;
	Tptr->SetHealth(Tptr->GetHealth() - damage);
}
void ShieldedFighterEnemy::SetPriority()
{
	Priority = GetPriority();
}