#include "Battle.h"
#include <fstream>
#include <thread>
#include <Windows.h>
#define InititialX 50
#define DiffrenceINx 300
#define InititialY 650-140
#define NEW_LINE 15
#define NUMBERS_SPACE 50
#define WINDOW_MIDDLE_X  1200/2.5

Battle::Battle()
{
	EnemyCount = 0;
	TimeStep = 0;
	for (int i = 0; i<4; i++)
		NK[i] = 0;
	pGUI = new GUI;
	SS.playHorn();
	Mode = CONTINUE;
}

void Battle::SetGameMode(MenuItem & CurrentGame)
{
	Point p;
	if (Mode == INTERACTIVE_MODE && CurrentGame == CONTINUE)
	{
		pGUI->GetPointClicked(p);
		CurrentGame = pGUI->GetCurrentClick(p);
	}
	else if (Mode == STEP_BY_STEP_MODE && CurrentGame == CONTINUE)
	{
		std::this_thread::sleep_for(chrono::seconds(1));
		pGUI->Click(p);
		CurrentGame = pGUI->GetCurrentClick(p);
	}
	if (Mode == CONTINUE)
	{
		pGUI->PrintMessage("CHOOSE YOUR GAME MODE");
		pGUI->GetPointClicked(p);
		CurrentGame = pGUI->GetCurrentClick(p);
		Mode = CurrentGame;
		if (Mode != CONTINUE)
			Clear();
	}
	else if (CurrentGame != CONTINUE)
	{
		Clear();
		Mode = CurrentGame;
	}
}

MenuItem Battle::GetGameMode() const
{
	return Mode;
}

void Battle::MergeEnemies(int i, int j)
{
	Stack<Enemy*>Merged;
	while (!Enemies[i].IsEmpty() && !Enemies[j].IsEmpty())
	{
		if (Enemies[i].Peek()->GetArrivalTimeStamp() < Enemies[j].Peek()->GetArrivalTimeStamp())
		{
			Merged.Push(Enemies[i].Peek());
			Enemies[i].Pop();
		}
		else
		{
			Merged.Push(Enemies[j].Peek());
			Enemies[j].Pop();
		}
	}
	while (!Enemies[i].IsEmpty())
	{
		Merged.Push(Enemies[i].Peek());
		Enemies[i].Pop();
	}
	while (!Enemies[j].IsEmpty())
	{
		Merged.Push(Enemies[j].Peek());
		Enemies[j].Pop();
	}
	while (!Merged.IsEmpty())
	{
		Merged.Peek()->SetRegion('A' + i);
		Merged.Peek()->SetDistance(max(Merged.Peek()->GetDistance(), BCastle.GetUnpavedDistance(i)));
		Enemies[i].Push(Merged.Peek());
		Merged.Pop();
	}
	while (!PriorityEnemies[j].isEmpty())
	{
		PriorityEnemies[j].peekTop()->SetRegion('A' + i);
		PriorityEnemies[j].peekTop()->SetDistance(max(PriorityEnemies[j].peekTop()->GetDistance(), BCastle.GetUnpavedDistance(i)));
		PriorityEnemies[i].add(PriorityEnemies[j].peekTop());
		PriorityEnemies[j].remove();
	}
}

void Battle::AddEnemy(Enemy* Ptr)
{
	if (EnemyCount < MaxEnemyCount)
		BEnemiesForDraw[EnemyCount++] = Ptr;
}

void Battle::DrawEnemies(GUI * pGUI)
{
	pGUI->DrawEnemies(BEnemiesForDraw, EnemyCount);
}

Castle * Battle::GetCastle()
{
	return &BCastle;
}

void Battle::Read()
{
	string filename;
	pGUI->PrintMessage("ENTER FILE NAME ");
	filename = pGUI->GetString();
	ifstream input;
	input.open(filename);
	while (!input.is_open())
	{
		pGUI->PrintMessage("ERROR | File not found");
		std::this_thread::sleep_for(chrono::seconds(1));
		pGUI->PrintMessage("ENTER FILE NAME ");
		filename = pGUI->GetString();
		input.open(filename);
	}
	// when this point is reached .. a valid file is reached
	int temp, ID;
	input >> temp; // starting health of towers
	BCastle.SetTowersHealth(temp);
	input >> temp; // the maximum number of enemies a tower can attack at any time step
	BCastle.SetTowersMaxEnemies(temp);
	input >> temp; // tower fire power
	BCastle.SetTowersFirePower(temp);
	float c1, c2, c3;
	input >> c1 >> c2 >> c3; //priority constants in battle class
	ShieldedFighterEnemy::SetC1(c1);
	ShieldedFighterEnemy::SetC2(c2);
	ShieldedFighterEnemy::SetC3(c3);
	FreezingEnemy::SetC1(c1);
	FreezingEnemy::SetC2(c2);
	FreezingEnemy::SetC3(c3);
	FreezingEnemy::SetC4((c1+c2+c3)/3);
	input >> ID; //sequence no
	while (ID != -1)
	{
		int type;
		Enemy * e;
		input >> type;
		switch (type)
		{
		case 0:
		{
			e = new PaverEnemy();
			break;
		};
		case 1:
		{
			e = new FighterEnemy();
			break;
		};
		case 2:
		{
			e = new ShieldedFighterEnemy();
			break;
		};
		case 3:
		{
			e = new HealerEnemy();
			break;
		};
		case 4:
		{
			e = new FreezingEnemy();
			break;
		};

		}//end switch
		e->SetID(ID);
		int detail;
		input >> detail;
		e->SetColor();
		e->SetArrivalTimeStamp(detail);
		input >> detail;
		e->SetHealth(detail);
		input >> detail;
		e->SetFirePower(detail);
		input >> detail;
		e->SetReloadPeriod(detail);
		input >> detail;
		e->SetSpeed(detail);
		char region;
		input >> region;
		e->SetRegion(region);
		ShieldedFighterEnemy * shieldedptr = dynamic_cast<ShieldedFighterEnemy*> (e);
		FreezingEnemy * Freezerptr = dynamic_cast<FreezingEnemy*> (e);
		if (shieldedptr || Freezerptr)
		{
			PriorityEnemies[region - 'A'].add(e);
		}//end if
		else
		{
			Enemies[region - 'A'].Push(e);
		}
		input >> ID; //new enemy
	}//end while
	for (int i = 0; i < 4; i++)		//Reverse Stacks
	{
		Enemies[i].Reverse();
	}
	pGUI->PrintMessage("Input File is Successuflly Read..");
	if (Mode == SILENT_MODE)
		std::this_thread::sleep_for(chrono::seconds(1));
}// end func

int Battle::Ended() const
{
	bool b = true;
	for (int i = 0; i<4; i++)
	{
		if (!PriorityEnemies[i].isEmpty() || !Enemies[i].IsEmpty())
			b = false;
	}
	if (b)
		return 1;
	if (BCastle.CastleLose())
		return 2;
	return 0;
}

void Battle::Proceed()
{
	if (Mode == CONTINUE)
		return;
	TimeStep++;
	Enemy::IncrementTimeStep();
	Shift();
	if (Mode != SILENT_MODE)
	{
		Draw();
		Print();
	}
	Fight();
	OutputDead();
	if (Ended())
	{
		if (Mode != SILENT_MODE)
		{
			Draw();
			Print();
			std::this_thread::sleep_for(chrono::seconds(1));
		}
		OutputFile();
		if (Ended() == 1)
			pGUI->PrintMessage(" Victory ");
		else
			pGUI->PrintMessage(" Defeat ");
		std::this_thread::sleep_for(chrono::seconds(2));
		Mode = CONTINUE;
	}
}

void Battle::ResetOutFile()
{
	ofstream Output;
	ofstream aux;
	LPCSTR file="auxiliary.txt";
	SetFileAttributes(file,FILE_ATTRIBUTE_NORMAL);
	aux.open("auxiliary.txt",ios_base::out);
	aux<<0<<endl;
	aux<<0<<endl;
	aux<<0<<endl;
	SetFileAttributes(file,FILE_ATTRIBUTE_HIDDEN);
	aux.close();
	Output.open("Results.txt");
	Output.clear();
	Output<<"KTS   S   FD   KD   LT"<<endl; 
	Output.close();
}

void Battle::Heal(Enemy * H,Stack<Enemy*>&outAUX)
{
	int i;
	i = H->GetRegion();
	Stack<Enemy*> saux;
	Enemy* temp;

	/// for enemy heap
	while (!PriorityEnemies[i].isEmpty())
	{
		temp = PriorityEnemies[i].peekTop();
		if (abs(temp->GetDistance() - H->GetDistance()) <= 1 && temp->IsActive())
		{
			temp->SetHealth(temp->GetHealth() + H->GetFirePower());
		}
		saux.Push(temp);
		PriorityEnemies[i].remove();
	}
	while (!saux.IsEmpty())
	{
		temp = saux.Peek();
		PriorityEnemies[i].add(temp);
		saux.Pop();
	}

	/// for enemy stack
	while (!Enemies[i].IsEmpty() && Enemies[i].Peek()->IsActive())
	{
		temp = Enemies[i].Peek();
		if (abs(temp->GetDistance() - H->GetDistance()) <= 1)
		{
			temp->SetHealth(temp->GetHealth() + H->GetFirePower());
		}
		saux.Push(temp);
		Enemies[i].Pop();
	}
	while (!saux.IsEmpty())
	{
		temp = saux.Peek();
		Enemies[i].Push(temp);
		saux.Pop();
	}

	// for external aux 

		while (!outAUX.IsEmpty() && outAUX.Peek()->IsActive())
	{
		temp = outAUX.Peek();
		if (abs(temp->GetDistance() - H->GetDistance()) <= 1)
		{
			temp->SetHealth(temp->GetHealth() + H->GetFirePower());
		}
		saux.Push(temp);
		outAUX.Pop();
	}
	while (!saux.IsEmpty())
	{
		temp = saux.Peek();
		outAUX.Push(temp);
		saux.Pop();
	}

}

void Battle::Draw()
{
	Stack<Enemy*>aux;
	EnemyCount = 0;
	for (int i = 0; i<4; i++)
	{
		while (!PriorityEnemies[i].isEmpty())
		{
			Enemy * e;
			e = PriorityEnemies[i].peekTop();
			PriorityEnemies[i].remove();
			aux.Push(e);
			if (e->IsActive())
			{
				AddEnemy(e);
			}
		}
		while (!aux.IsEmpty())
		{
			Enemy* e;
			e = aux.Peek();
			aux.Pop();
			e->SetPriority();
			PriorityEnemies[i].add(e);
		}
		while (!Enemies[i].IsEmpty() && Enemies[i].Peek()->IsActive())
		{
			Enemy* e;
			e = Enemies[i].Peek();
			Enemies[i].Pop();
			aux.Push(e);
			if (e->IsActive())
			{
				AddEnemy(e);
			}

		}
		while (!aux.IsEmpty())
		{
			Enemy* e;
			e = aux.Peek();
			aux.Pop();
			Enemies[i].Push(e);
		}
	}
	pGUI->ClearBattleArea();
	pGUI->ClearStatusBar();
	pGUI->DrawCastle(!BCastle.IsKilled(0), !BCastle.IsKilled(1), !BCastle.IsKilled(2), !BCastle.IsKilled(3));
	pGUI->Drawpaved(BCastle.GetUnpavedDistance(0),BCastle.GetUnpavedDistance(1),BCastle.GetUnpavedDistance(2),BCastle.GetUnpavedDistance(3));
	DrawEnemies(pGUI);
}

void Battle::Fight()
{
	Stack<Enemy*>aux;
	for (int i = 0; i<4; i++)
	{
		int n = 0;
		while (!PriorityEnemies[i].isEmpty())
		{
			Enemy * e;
			e = PriorityEnemies[i].peekTop();
			PriorityEnemies[i].remove();
			if (e->IsActive())
			{
				if (n<BCastle.GetTowersMaxEnemies() && !BCastle.IsFreezed(i, TimeStep))
				{
					BCastle.AttackEnemy(i, e);
					n++;
				}
				if (!e->IsReloadPeriod())
					BCastle.AttackTower(i, e);
				e->Move(BCastle.GetUnpavedDistance(i));
			}
			if (!e->IsKilled())
				aux.Push(e);
			else
			{
				KilledArr[i].add(e);
				NK[i]++;
			}
		}
		while (!aux.IsEmpty())
		{
			Enemy* e;
			e = aux.Peek();
			aux.Pop();
			PriorityEnemies[i].add(e);
		}
		while (!Enemies[i].IsEmpty() && Enemies[i].Peek()->IsActive())
		{
			Enemy* e;
			e = Enemies[i].Peek();
			Enemies[i].Pop();
			if (n<BCastle.GetTowersMaxEnemies() && !BCastle.IsFreezed(i, TimeStep))
			{
				BCastle.AttackEnemy(i, e);
				n++;
			}
			if (!e->IsReloadPeriod())
			{
				if (e->GetType() == 3)
					Heal(e,aux);
				else
					BCastle.AttackTower(i, e);
			}
			e->Move(BCastle.GetUnpavedDistance(i));

			if (!e->IsKilled())
				aux.Push(e);
			else
			{
				KilledArr[i].add(e);
				NK[i]++;
			}
		}
		while (!aux.IsEmpty())
		{
			Enemy* e;
			e = aux.Peek();
			aux.Pop();
			Enemies[i].Push(e);
		}
	}
}

void Battle::Shift()
{
	for (int i = 0; i < 4; i++)
	{
		if (BCastle.IsKilled(i))
		{
			int j = i + 1;
			while (1)
			{
				j %= 4;
				if (!BCastle.IsKilled(j))
				{
					MergeEnemies(j, i);
					break;
				}
				j++;
			}
		}
	}
}

void Battle::OutputDead()
{
	ifstream aux_Read;
	ofstream aux_Write;
	LPCSTR file="auxiliary.txt";
	SetFileAttributes(file,FILE_ATTRIBUTE_NORMAL);
	aux_Read.open("auxiliary.txt",ios_base::out);
	int SumFD;
	int SumKD;
	int Count;
	aux_Read >> Count;
	aux_Read >>SumKD;
	aux_Read>>SumFD;
	ofstream Output;
	Output.open("Results.txt",ios_base::app);
	for(int i=0;i<4;i++)
	{
		while(!(KilledArr[i].isEmpty()))
		{
			Enemy* Ptr=KilledArr[i].peekTop();
			Output<<Ptr->GetTimeStep()<<"   "<<Ptr->GetID()<<"   "<<Ptr->GetFD()<<"   "<<Ptr->GetKD()<<"   "<<Ptr->GetLT()<<endl;
			SumFD+=Ptr->GetFD();
			SumKD+=Ptr->GetKD();
			Count++;
			KilledArr[i].remove();
			delete Ptr;
		}
	}
	aux_Read.clear();
	aux_Write.open("auxiliary.txt",ios_base::out);
	SetFileAttributes(file,FILE_ATTRIBUTE_HIDDEN);
	aux_Write<<Count<<endl;
	aux_Write<<SumKD<<endl;
	aux_Write<<SumFD<<endl;
	aux_Write.close();
	Output.close();
}

Battle::~Battle()
{
	Clear();
	delete pGUI;
	pGUI = nullptr;
}

void Battle::Print()
{
	string temp;
	pGUI->ClearStatusBar();
	/******************************* printing time step ***********************/
	temp = to_string(TimeStep);
	pGUI->DrawString(InititialX + WINDOW_MIDDLE_X, InititialY, "Time step : ");
	pGUI->DrawString(InititialX + WINDOW_MIDDLE_X + 2 * NUMBERS_SPACE, InititialY, temp);

	/*********************************printing regions**************************/
	pGUI->DrawString(InititialX, InititialY + NEW_LINE, "REGION A");//position A
	pGUI->DrawString(InititialX + DiffrenceINx, InititialY + NEW_LINE, "REGION B");//position B
	pGUI->DrawString(InititialX + 2 * DiffrenceINx, InititialY + NEW_LINE, "REGION C");//position C
	pGUI->DrawString(InititialX + 3 * DiffrenceINx, InititialY + NEW_LINE, "REGION D");//position D
																					   //	/****************************************towers**************************/
	string temparr[4];
	// HEALTH
	for (int i = 0; i<NoOfRegions; i++)
	{
		temparr[i] = to_string(BCastle.GetTowerHealth(i));
	}
	for (int i = 0; i<4; i++)
	{
		pGUI->DrawString(InititialX + i*DiffrenceINx, InititialY + 2 * NEW_LINE, "HEALTH : ");
		pGUI->DrawString(InititialX + i*DiffrenceINx + 2 * NUMBERS_SPACE, InititialY + 2 * NEW_LINE, temparr[i]);
	}
	// UN PAVED DISTANCE
	for (int i = 0; i<NoOfRegions; i++)
	{
		temparr[i] = to_string(BCastle.GetUnpavedDistance(i));
	}
	for (int i = 0; i<4; i++)
	{
		pGUI->DrawString(InititialX + i*DiffrenceINx, InititialY + 3 * NEW_LINE, "UnPaved : ");
		pGUI->DrawString(InititialX + i*DiffrenceINx + 2 * NUMBERS_SPACE, InititialY + 3 * NEW_LINE, temparr[i]);
	}
	//	/**************************end printing towers information******************/
	//
	//	/************************* dead enemies ***********************************/
	for (int i = 0; i<4; i++)
	{
		temparr[i] = to_string(NK[i]);
		pGUI->DrawString(InititialX + i*DiffrenceINx, InititialY + 5 * NEW_LINE, "KILLED NO. : ");
		pGUI->DrawString(InititialX + i*DiffrenceINx + 2 * NUMBERS_SPACE, InititialY + 5 * NEW_LINE, temparr[i]);//position A
	}


	/**************************active enemies **********************************/
	int activearr[4] = { 0,0,0,0 };
	Stack<Enemy*> aux;
	for (int i = 0; i<4; i++)
	{
		//normal enemies
		while (!Enemies[i].IsEmpty() && Enemies[i].Peek()->IsActive())
		{
			Enemy * e;
			e = Enemies[i].Peek();
			Enemies[i].Pop();
			aux.Push(e);
			activearr[i]++;
		}
		while (!aux.IsEmpty())
		{
			Enemy* e;
			e = aux.Peek();
			aux.Pop();
			Enemies[i].Push(e);
		}

		//high priority enemies
		while (!PriorityEnemies[i].isEmpty())
		{
			Enemy * e;
			e = PriorityEnemies[i].peekTop();
			PriorityEnemies[i].remove();
			aux.Push(e);
			if (e->IsActive())
			{
				activearr[i]++;
			}
		}
		while (!aux.IsEmpty())
		{
			Enemy* e;
			e = aux.Peek();
			aux.Pop();
			PriorityEnemies[i].add(e);
		}
	}
	//print no
	for (int i = 0; i<4; i++)
	{
		temp = to_string(activearr[i]);
		pGUI->DrawString(InititialX + i*DiffrenceINx, InititialY + 6 * NEW_LINE, "Active NO. : ");
		pGUI->DrawString(InititialX + i*DiffrenceINx + NUMBERS_SPACE * 2, InititialY + 6 * NEW_LINE, temp);
	}

}

void Battle::Clear()
{
	for (int i = 0; i<4; i++)
	{
		Enemy* Temp;
		while (!Enemies[i].IsEmpty())
		{
			Temp = Enemies[i].Peek();
			Enemies[i].Pop();
			delete Temp;
		}
		while (!PriorityEnemies[i].isEmpty())
		{
			Temp = PriorityEnemies[i].peekTop();
			PriorityEnemies[i].remove();
			delete Temp;
		}
		while (!KilledArr[i].isEmpty())
		{
			Temp = KilledArr[i].peekTop();
			KilledArr[i].remove();
			delete Temp;
		}
		NK[i] = 0;
	}
	EnemyCount = 0;
	TimeStep = 0;
	BCastle.ResetUnpavedDistance();
	BCastle.ResetFreezed();
	Enemy::ResetTimeStep();
	pGUI->ClearBattleArea();
	pGUI->Drawpaved();
	pGUI->ClearStatusBar();
	pGUI->DrawCastle();
	ResetOutFile();
}

void Battle::OutputFile()
{
	ofstream Output;
	double SumFD=0;
	double SumKD=0;
	int count=0;
	int ALive=0;
	ifstream aux_Read;
	LPCSTR file="auxiliary.txt";
	SetFileAttributes(file,FILE_ATTRIBUTE_NORMAL);
	aux_Read.open("auxiliary.txt",ios::out);
	aux_Read >> count >> SumKD >> SumFD;
	aux_Read.close();
	SetFileAttributes(file,FILE_ATTRIBUTE_HIDDEN);
	Output.open("Results.txt",ios_base::app);
	for(int i=0;i<4;i++)
	{
		ALive+=Enemies[i].GetSize();
		ALive+=PriorityEnemies[i].getNumberOfNodes();
	}
		Output<<"T1_Total_Damage   T2_Total_Damage   T3_Total_Damage   T4_Total_Damage"<<endl;
		for(int i=0;i<4;i++)
			Output<<BCastle.GetTowerHealth(i)<<"               ";
		Output<<endl;
		Output<<"R1_Unpaved_Dist   R2_Unpaved_Dist   R3_Unpaved_Dist   R4_Unpaved_Dist"<<endl;
		for(int i=0;i<4;i++)
			Output<<BCastle.GetUnpavedDistance(i)<<"                ";
		Output<<endl;
		if(BCastle.CastleLose())
		{
			Output<<"Game is LOSS"<<endl;
			Output<<"Number of Killed Enemies="<<count<<endl;
			Output<<"Number of Alive Enemies (active and inactive)="<<ALive<<endl;
			if (count)
			{
				Output << "Average First-Shot Delay for Killed Enemies=" << (SumFD / count) << endl;
				Output << "Average Kill Delay for Killed Enemies=" << (SumKD / count) << endl;
			}
		}
			
		else
		{
			Output<<"Game is WIN"<<endl;
			Output<<"Total Enemies="<<count<<endl;
			if (count)
			{
				Output << "Average First-Shot Delay=" << (SumFD / count) << endl;
				Output << "Average Kill Delay=" << (SumKD / count) << endl;
			}
		}
	Output.close();
}