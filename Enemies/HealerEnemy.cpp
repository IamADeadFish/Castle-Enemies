#include "HealerEnemy.h"

HealerEnemy::HealerEnemy() : Enemy()
{
	type=HEALER;
}

HealerEnemy::~HealerEnemy()
{
}
void HealerEnemy::SetColor()
{
	Clr = GREEN;
}
void HealerEnemy::Attack(Tower * Tptr)
{
	return;
}