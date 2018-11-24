#pragma once
#include "Defs.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include "GUI\GUI.h"
#include "soundSystem.h"
#include "Enemies\Enemy.h"
#include "Castle\Castle.h"
#include "Enemies\FighterEnemy.h"
#include "Enemies\PaverEnemy.h"
#include "Enemies\ShieldedFighterEnemy.h"
#include "Enemies\FreezingEnemy.h"
#include "Enemies\HealerEnemy.h"
#include "Castle\Tower.h"
#include "DataStructures\Heap.cpp"
#include "DataStructures\Stack.cpp"
// it is the controller of the project
//Application Manager
class Battle
{
private:
	Castle BCastle;
	soundSystem SS;
	GUI * pGUI;
	MenuItem Mode;
	int EnemyCount;	//the actual number of enemies in the game
	Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
											// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function
	int TimeStep;
	void Print();
	Stack<Enemy*>Enemies[4];				//	(Non Shielded Enemies-Sorted by arrival time)

	Heap<Enemy*>PriorityEnemies[4];			//ShieldedRegions		(Shielded Enemies-Sorted by priority)

	Heap<Enemy*>KilledArr[4];				//KilledRegions		(Killed Enemies-Sorted by priority)

	int NK[4];								//Number of Killed Enemies at each region
	void MergeEnemies(int i, int j);
	void AddEnemy(Enemy* Ptr);
	void DrawEnemies(GUI * pGUI);
	Castle * GetCastle();
	void Clear();
	void OutputDead();						// print dead enemies
	void OutputFile();						// print rest of outputfile
	void ResetOutFile();					// reset the outputfile
	void Heal(Enemy * e,Stack<Enemy*>&outAUX);
	void Draw();
	void Fight();
	void Shift();
	int Ended()const;
public:

	Battle();
	void SetGameMode(MenuItem & m);
	MenuItem GetGameMode() const;
	void Read();
	void Proceed();						//	Simulation
	~Battle();
};

