#include "GUI.h"

//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
	pWind = new window(WindWidth+15,WindHeight,0,0);
	pWind->ChangeTitle("The Castle Game");
	DrawMenu();
	
	ClearStatusBar();
	ClearBattleArea();
	Drawpaved();
	DrawCastle();
	
	
}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ====================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::GetPointClicked(Point &P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////
string GUI::GetString() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		
		PrintMessage(Label);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(BLACK);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight)+10, msg); // You may need to change these coordinates later 
	                                                                      // to be able to write multi-line
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(BLACK);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawMenu() const
{
	//You can draw the menu icons any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in enum MenuItem

	pWind->SetPen(SNOWBLUE, 3);
	pWind->SetBrush(SNOWBLUE);
	pWind->DrawRectangle(0, 0, WindWidth,MenuBarHeight );

	string MenuItemImages[MENU_ITM_COUNT];

	MenuItemImages[INTERACTIVE_MODE] = "images\\MenuItems\\Menu_interactive_mode.jpg";
	MenuItemImages[STEP_BY_STEP_MODE] = "images\\MenuItems\\Menu_stepbystep_mode.jpg";
	MenuItemImages[SILENT_MODE] = "images\\MenuItems\\Menu_silent_mode.jpg";
	MenuItemImages[MENU_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";
	//
	//TODO: Prepare images for each menu item (an icon for each modes) and add it to the list
	//

	// You should add an icon for each mode of operation (silent, step by step, ...etc.)

	//Draw menu item one image at a time
	for(int i=0; i<MENU_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);



	//Draw a line under the menu bar
	pWind->SetPen(BLACK, 4);
	pWind->DrawLine(0, MenuBarHeight, WindWidth, MenuBarHeight);
	pWind->DrawLine(0,0,WindWidth,0);

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	pWind->SetPen(SNOWBLUE, 3);
	pWind->SetBrush(SNOWBLUE);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight , WindWidth, WindHeight);	

	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight , WindWidth, WindHeight - StatusBarHeight);	
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearBattleArea() const
{
	// Clearing the battle area
	/*string BackGround="images\\Background\\BattleField.jpg";
	pWind->DrawImage(BackGround,0,MenuBarHeight,WindWidth,WindHeight-StatusBarHeight-MenuBarHeight);*/

	pWind->SetPen(SAND, 3);
	pWind->SetBrush(SAND);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawCastle(bool A,bool B,bool C,bool D) const
{
	string Towers[4];
	if(A==true)
		Towers[0]="images\\Towers\\Tower_A.jpg";
	else
		Towers[0]="images\\Towers\\Destoyed\\Tower_A.jpg";
	if(B==true)
		Towers[1]="images\\Towers\\Tower_B.jpg";
	else
		Towers[1]="images\\Towers\\Destoyed\\Tower_B.jpg";
	if(C==true)
		Towers[2]="images\\Towers\\Tower_C.jpg";
	else
		Towers[2]="images\\Towers\\Destoyed\\Tower_C.jpg";
	if(D==true)
		Towers[3]="images\\Towers\\Tower_D.jpg";
	else
		Towers[3]="images\\Towers\\Destoyed\\Tower_D.jpg";

	pWind->DrawImage(Towers[0],CastleStartX, CastleStartY,(CastleEndX-CastleStartX)/2,(CastleEndY-CastleStartY)/2);
	pWind->DrawImage(Towers[1],CastleStartX+(CastleEndX-CastleStartX)/2, CastleStartY,(CastleEndX-CastleStartX)/2,(CastleEndY-CastleStartY)/2);
	pWind->DrawImage(Towers[2],CastleStartX+(CastleEndX-CastleStartX)/2, CastleStartY+(CastleEndY-CastleStartY)/2,(CastleEndX-CastleStartX)/2,(CastleEndY-CastleStartY)/2);
	pWind->DrawImage(Towers[3],CastleStartX, CastleStartY+(CastleEndY-CastleStartY)/2,(CastleEndX-CastleStartX)/2,(CastleEndY-CastleStartY)/2);

	int L = CastleWidth / 2;
	
	

	//  Drawing the 2 black crossed lines (for making 4 regions)
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, YHalfBattleArea, WindWidth, YHalfBattleArea);
	pWind->DrawLine(WindWidth/2, MenuBarHeight, WindWidth/2, WindHeight-StatusBarHeight);

	// Writing the letter of each region (A, B, C, D)
	pWind->SetPen(WHITE);
	pWind->SetFont(25, BOLD , BY_NAME, "Arial");
	pWind->DrawString(CastleStartX + 0.44*L, CastleStartY + 5*L/12, "A");
	pWind->DrawString(CastleStartX + 0.44*L, YHalfBattleArea + 5*L/12, "D");
	pWind->DrawString(WindWidth/2 + 0.44*L, CastleStartY + 5*L/12, "B");
	pWind->DrawString(WindWidth/2 + 0.44*L, YHalfBattleArea + 5*L/12, "C");


}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::Drawpaved(int A,int B,int C,int D)
{
	pWind->SetPen(KHAKI, 3);
	pWind->SetBrush(KHAKI);
	int refX;								//for A & D
	refX = (WindWidth/2 - CastleWidth/2);

	int refx;								//for B & C
	refx=(WindWidth/2 + CastleWidth/2);		

											//region A
	int x_A;
	x_A=refX-A*EnemyWidth-A;
	pWind->DrawRectangle(0,MenuBarHeight,x_A + EnemyWidth,CastleStartY+(CastleEndY-CastleStartY)/2);
	//pWind->DrawRectangle(x_A,MenuBarHeight,CastleStartX,CastleStartY+(CastleEndY-CastleStartY)/2);

											//region B
	int x_B;
	x_B= refx + (B)*EnemyWidth + B;
	pWind->DrawRectangle(WindWidth,MenuBarHeight,x_B - EnemyWidth,CastleStartY+(CastleEndY-CastleStartY)/2);
	//pWind->DrawRectangle(x_B,MenuBarHeight,CastleEndX,CastleStartY+(CastleEndY-CastleStartY)/2);
	
											//region C
	int x_C;
	x_C = refx + (C)*EnemyWidth + C;
	pWind->DrawRectangle(WindWidth,CastleStartY+(CastleEndY-CastleStartY)/2,x_C - EnemyWidth,WindHeight-StatusBarHeight);
	//pWind->DrawRectangle(x_C,CastleStartY+(CastleEndY-CastleStartY)/2,CastleEndX,WindHeight-StatusBarHeight);		

											//region D
	int x_D;
	x_D = refX - D*EnemyWidth - D;
	pWind->DrawRectangle(0,CastleStartY+(CastleEndY-CastleStartY)/2,x_D + EnemyWidth,WindHeight-StatusBarHeight);

	//pWind->DrawRectangle(x_D,CastleStartY+(CastleEndY-CastleStartY)/2,CastleStartX ,WindHeight-StatusBarHeight );


	//  Drawing the 2 black crossed lines (for making 4 regions)
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, YHalfBattleArea, WindWidth, YHalfBattleArea);
	pWind->DrawLine(WindWidth/2, MenuBarHeight, WindWidth/2, WindHeight-StatusBarHeight);


}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawEnemy(const Enemy & E, int YPos) const       // It's a private function
{
	color clr = E.GetColor();
	REGION Region = E.GetRegion();
	int Distance = E.GetDistance();

	int x, y, refX, refY;
	//First calculate x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	switch (Region)
	{
	case A_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case B_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case C_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	case D_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the enemy
	pWind->SetPen(clr);
	pWind->SetBrush(clr);
	pWind->DrawRectangle(x, y, x + EnemyWidth, y + EnemyHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
/* A function to draw a list of enemies and ensure there is no overflow in the drawing*/
// To use this function, you must prepare its input parameters as specified
// [Input Parameters]:
//    enemies [ ] : array of enemy pointers (ALL enemies from all regions in one array)
//    size : the size of the array (total no. of enemies)
void GUI::DrawEnemies(Enemy* enemies[], int size) const
{
	//draw enemies at each region 
	for(int region = A_REG; region <= D_REG; region++)
	{
		int CountEnemies = 0;	// count Enemies at the same distance to draw them vertically if they are <= 15 enemy 
		                        // else print number of enemy in the region
		bool draw=true;
		for(int distance = MaxDistance ; distance >= MinDistance ; distance--)
		{
			CountEnemies = 0;

			for(int i = 0 ; i < size ; i++)
			{	
				if(enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region)
				{
					CountEnemies++;
				}
			}
			if(CountEnemies > 15)
			{
				draw=false;
				break;
			}
		}
		if(draw)
		{
			for( int distance = MaxDistance ; distance > 1 ; distance-- )
			{
				CountEnemies=0;

				for(int i = 0 ; i < size ; i++)
				{	
					if(enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region)
					{
						DrawEnemy(*(enemies[i]), CountEnemies + 1);
						CountEnemies++;
					}
				}
			}
		}
		else // print message maximum reached in this region
		{
			PrintMessage("Cannot Draw Enemies of region " + to_string(region+1) + 
				"! More than" + to_string(MaxVerticaEnemies) + " enemies are in the same region and distance..");
			Sleep(1000); // because may be more than one region has drawing overflow
		}
	}
}

MenuItem GUI::GetCurrentClick(Point&p) const 
{
	if(p.y>=0&&p.y<MenuBarHeight&&p.x<=15*MenuItemWidth)
	{
		int ItemOrder=(p.x/MenuItemWidth);
		switch(ItemOrder)
		{
		case INTERACTIVE_MODE:return INTERACTIVE_MODE;
		case STEP_BY_STEP_MODE:return STEP_BY_STEP_MODE;
		case SILENT_MODE:return SILENT_MODE;
		case MENU_EXIT:return MENU_EXIT;
		}
	}
	return CONTINUE;
}

void GUI::Click(Point &p) const
{
	pWind->GetMouseClick(p.x,p.y);
}