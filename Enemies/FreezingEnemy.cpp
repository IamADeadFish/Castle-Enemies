#include "FreezingEnemy.h"

FreezingEnemy::FreezingEnemy() : Enemy()
{
	type=FREEZING;
}

FreezingEnemy::~FreezingEnemy() 
{
}
void FreezingEnemy::DecrementHealth(double f)
{
	Health -= f / 2 / Distance;
}
void FreezingEnemy::SetColor()
{
	Clr = WHITE;
}
void FreezingEnemy::Attack(Tower * Tptr)
{
	Tptr->SetFreezed(TimeStep + FirePower);
}
void  FreezingEnemy::SetC1(double c1)
{
	C1 = c1;
}
void FreezingEnemy::SetC2(double c2)
{
	C2 = c2;
}
void FreezingEnemy::SetC3(double c3)
{
	C3 = c3;
}
void FreezingEnemy::SetC4(double c4)
{
	C4 = c4;
}
double FreezingEnemy::GetC1()
{
	return C1;
}
double FreezingEnemy::GetC2()
{
	return C2;
}
double FreezingEnemy::GetC3()
{
	return C3;
}
double FreezingEnemy::GetC4()
{
	return C4;
}
double FreezingEnemy::C1 = 0;
double FreezingEnemy::C2 = 0;
double FreezingEnemy::C3 = 0;
double FreezingEnemy::C4 = 0;

double FreezingEnemy::GetPriority()const
{
	if (!IsActive())
		return 0;
	return (FirePower * C1 / Distance + C2 / (RemainingTimeforShot() + 1) + Health * C3 + C4);
}
void FreezingEnemy::SetPriority()
{
	Priority = GetPriority();
}