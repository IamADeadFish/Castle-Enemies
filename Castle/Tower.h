#ifndef Tower_h
#define Tower_h

//#include "..\Enemies\Enemy.h"
class Enemy;

class Tower
{
	double Health;
	double FirePower;
	double UnpavedDistance;
	int MaxEnemies;
	int Freezed;

public:

	Tower();    // set data members to zero
	~Tower();
	void SetHealth(double h);   
	void SetFirePower(double f);
	void DecrementUnpavedDistance(double p);
	void SetMaxEnemies(int N);
	void SetFreezed(int F);
	void ResetDistance();
	void ResetFreezed();

	double GetHealth() const;
	double GetFirePower()const;
	double GetUnpavedDistance()const;
	int GetMaxEnemies()const;
	bool IsFreezed(int t) const;
	bool IsKilled()const;    //return killed if health = 0

	void AttackTower (Enemy * e);
	void AttackEnemy (Enemy * e);

};
#endif
