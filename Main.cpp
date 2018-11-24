#include "Battle.h"
int main()
{
	Battle Game;
	MenuItem gMode = CONTINUE;
	while (1)
	{
		Game.SetGameMode(gMode);
		if (Game.GetGameMode() == MENU_EXIT)
		{
			break;
		}
		if (gMode != CONTINUE)
		{
			Game.Read();
			gMode = CONTINUE;
		}
		else
			Game.Proceed();
	}
	return 0;
}