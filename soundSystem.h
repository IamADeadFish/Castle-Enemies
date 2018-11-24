#pragma once
#include <irrKlang.h>
using namespace irrklang;

class soundSystem
{
	ISoundEngine* engine ;
public:
	soundSystem(void);
	void stopAllSounds();
	void playHorn();
	void playBell();
	~soundSystem(void);
};

