#include "soundSystem.h"
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll


soundSystem::soundSystem(void)
{
	engine = createIrrKlangDevice();
}
void soundSystem:: playHorn()
{
	engine->play2D("sounds/horn.mp3",true);

}
void soundSystem:: playBell()
{
	engine->play2D("sounds/bell.wav",true);

}
void soundSystem::stopAllSounds()
{
	engine->stopAllSounds();
}
soundSystem::~soundSystem(void)
{
	engine->drop(); // delete engine

}
