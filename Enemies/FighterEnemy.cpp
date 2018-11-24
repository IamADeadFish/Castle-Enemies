#include "FighterEnemy.h"

FighterEnemy::FighterEnemy() : Enemy()
{
	type=FIGHTER;
}

FighterEnemy::~FighterEnemy()
{
}

void FighterEnemy::SetColor()
{
	Clr = GREY;
}
void FighterEnemy::Attack(Tower * Tptr)
{
	double damage = FirePower / Distance;
	Tptr->SetHealth(Tptr->GetHealth() - damage);
}