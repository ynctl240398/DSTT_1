#pragma once

#include "MovingObject.h"
#include "Game.h"
#include "debug.h"
#include "Textures.h"
#include "Define.h"
#include "KeyGame.h"
#include "Whip.h"

class CSimon : public CMovingObject
{
	bool isOnGround;
	CKeyGame* k;
	int ani;
	CWhip *whip;
public:
	CSimon();
	~CSimon();

	virtual	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual	void Move();
	void SetState(int state);
	int GetState() { return state; }
	void CreateAnimation();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void KeyBoardHandler();
	int GetDirection() { return direction; }
};

