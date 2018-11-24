#include "Enemy.h"

Enemy::Enemy()
{
	ArrivalTimeStamp = 0;
	FirePower = 0;
	ReloadPeriod = 0;
	Health = 0;
	Speed=0;
	Distance = MaxDistance;
	FD = 0;
	KD = 0;
	LT = 0;
	Priority = 0;
	Killed = false;
	FirstShot = false;
	Region=A_REG;
}

Enemy::~Enemy()
{
}

bool Enemy::IsActive()const
{
	return (ArrivalTimeStamp<=TimeStep && !Killed);
}
color Enemy::GetColor() const
{
	return Clr;
}
ENEMY_TYPE Enemy::GetType() const
{
return type;
}

REGION Enemy::GetRegion() const
{
	return Region;
}

void Enemy::Move(int p)
{
	if (Distance-Speed > p)
		Distance-=Speed;
	else
		Distance=p;
}


void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}
void Enemy::SetSpeed(int s)
{
	Speed = (s > 1) ? s : 1;
}
int Enemy::GetSpeed() const
{
	return Speed;
}
int Enemy::GetDistance() const
{
	return Distance;
}
int Enemy::GetID()const
{
	return ID;
}

void Enemy::SetID(int i)
{
	ID = i;
}
double Enemy::GetHealth()const
{
	return Health;
}
double Enemy::GetFirePower()const
{
	return FirePower;
}
int Enemy::GetArrivalTimeStamp()const
{
	return ArrivalTimeStamp;
}
int Enemy::GetReloadPeriod()const
{
	return ReloadPeriod;
}
int Enemy::GetFD()const
{
	return FD;
}
int Enemy::GetKD()const
{
	return KD;
}
int Enemy::GetLT()const
{
	return LT;
}

bool Enemy::IsReloadPeriod()const
{
	return ((TimeStep - ArrivalTimeStamp) % (ReloadPeriod+1) != 0);
}
void Enemy::Attacked(double f)
{
	if (!IsShot())
		SetShot();
	DecrementHealth(f);
	if (Health <= 0)
		SetKilled();
}
int Enemy::RemainingTimeforShot()const
{
	if (IsReloadPeriod())
		return (ReloadPeriod - (TimeStep - ArrivalTimeStamp) % (ReloadPeriod+1));
	else
		return 0;
}
void Enemy::SetKilled()
{
	Killed = true;
	KD = TimeStep - FD - ArrivalTimeStamp;
	LT = KD + FD;
}
bool Enemy::IsKilled()const
{
	return Killed;
}
bool Enemy::IsShot()const
{
	return FirstShot;
}
void Enemy::SetShot()
{
	FirstShot = true;
	FD = TimeStep - ArrivalTimeStamp;
}



void Enemy::SetHealth(double h)
{
	Health = (h > 0) ? h : 0;
}
void Enemy::SetFirePower(double f)
{
	FirePower = (f > 0) ? f : 0;
}
void Enemy::SetArrivalTimeStamp(int t)
{
	ArrivalTimeStamp = (t > 0) ? t : 0;
}
void Enemy::SetReloadPeriod(int r)
{
	ReloadPeriod = (r > 0) ? r : 0;
}
void Enemy::SetRegion(char c)
{
	if(c=='A')
		Region=A_REG;
	else if (c=='B')
		Region=B_REG;
	else if(c=='C')
		Region=C_REG;
	else
		Region=D_REG;
}

void Enemy::DecrementHealth(double f)
{
	Health -= f / Distance;
}

void Enemy::IncrementTimeStep()
{
	++TimeStep;
}
int Enemy::GetTimeStep()
{
	return TimeStep;
}
int Enemy::TimeStep = 0;

void Enemy::ResetTimeStep()
{
	TimeStep=0;
}
void Enemy::SetPriority()
{
	Priority = 0;
}
bool Enemy::operator < (const Enemy & E) const
{
	if (IsKilled() && E.IsKilled())
		return FD < E.FD;
	else
		return Priority < E.Priority;
}
