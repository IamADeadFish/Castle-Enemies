#ifndef Enemy_h
#define Enemy_h
#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Castle\Tower.h"

// Enemy is the base class of each type of enemy
// Enemy is an abstract class.
class Enemy
{

protected:
	int ID;         //Each enemy has a unique ID (sequence number)
	color Clr;	    //Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	REGION Region;  //Region of this enemy
	ENEMY_TYPE type; // enum determining the type of enemy 

	int Distance;	//Horizontal distance between enemy & the tower of its region
	                 //Always positive (ranges from 2 to 60)
	double Health;	//Enemy health
	double FirePower; // Enemy firepower
	int Speed;			//Enemy Speed
	int ArrivalTimeStamp; // Arrival time
	int ReloadPeriod; // Reload period of enemy
	int FD, KD, LT;    //such that :
	                    //FD : the time elapsed until an enemy is first shot by a tower
	                     //KD : the time elapsed between first time a tower shoots the enemy and its kill time 
	                      //LT : the total time an enemy stays alive until being killed
	bool FirstShot;    // Always false till the first shot
	bool Killed;       // True if enemy is killed
	double Priority;    // priority to be shot

	bool IsShot()const;            // check if enemy was shot before
	void SetShot();      // set FirstShot true && set FD
	void SetKilled();    // set killed true && set KD , LT
	virtual void DecrementHealth(double f);
	int RemainingTimeforShot()const;
	static int TimeStep;


public:
	Enemy();
	virtual ~Enemy();

	// Get funs
	color GetColor() const;
	REGION GetRegion() const;
	ENEMY_TYPE GetType() const;
	int GetDistance() const;
	double GetHealth()const;
	double GetFirePower()const;
	int GetArrivalTimeStamp()const; 
	int GetReloadPeriod()const;
	int GetFD()const;
	int GetKD()const;
	int GetLT()const;
	int GetID()const;
	int GetSpeed() const;
	static int GetTimeStep();      // return current time step

	//Set funcs
	void SetDistance(int d);
	void SetID(int i);
	void SetHealth(double h);
	void SetFirePower(double f);
	void SetArrivalTimeStamp(int t);
	void SetReloadPeriod(int r);
	void SetRegion(char c);
	void SetSpeed(int s);
	virtual void SetColor() = 0;
	static void ResetTimeStep();

	// main funcs
	virtual void Move(int p);
	bool IsReloadPeriod()const;     // Returns if the enemy is in its reload period
	void Attacked(double f);   // Decreases health of the enemy
	bool IsKilled()const;
	static void IncrementTimeStep();
	bool IsActive()const;
	virtual void Attack(Tower * Tptr)=0; // Attack tower
	virtual void SetPriority();
	bool operator < (const Enemy & E) const;

};
#endif