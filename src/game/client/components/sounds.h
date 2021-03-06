// copyright (c) 2007 magnus auvinen, see licence.txt for more info
#ifndef GAME_CLIENT_COMPONENTS_SOUNDS_H
#define GAME_CLIENT_COMPONENTS_SOUNDS_H
#include <game/client/component.h>

class CSounds : public CComponent
{
	enum
	{
		QUEUE_SIZE = 32,
	};
	int m_aQueue[QUEUE_SIZE];
	int m_QueuePos;
	int64 m_QueueWaitTime;

public:
	// sound channels
	enum
	{
		CHN_GUI=0,
		CHN_MUSIC,
		CHN_WORLD,
		CHN_GLOBAL,
	};

	virtual void OnInit();
	virtual void OnReset();
	virtual void OnRender();
	
	void ClearQueue();
	void Enqueue(int SetId);
	void Play(int Channel, int SetId, float Vol, vec2 Pos);
	void PlayAndRecord(int Channel, int SetId, float Vol, vec2 Pos);
};


#endif
