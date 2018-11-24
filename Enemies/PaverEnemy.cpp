#include "PaverEnemy.h"

PaverEnemy::PaverEnemy() : Enemy()
{
	type = PAVER;
}

PaverEnemy::~PaverEnemy()
{
}
void PaverEnemy::SetColor()
{
	Clr = BROWN;
}
void PaverEnemy::Move(int p)
{
	if (!IsReloadPeriod())
	{
		if (Distance - FirePower > MinDistance)
			Distance -= FirePower;
		else
			Distance = MinDistance;
	}
	else
		Enemy::Move(p);
}
void PaverEnemy::Attack(Tower * Tptr)
{
	if (Distance == Tptr->GetUnpavedDistance())
		Tptr->DecrementUnpavedDistance(FirePower);
}