#pragma once
#include "Define.h"
#include "debug.h"
#include "Game.h"
#include "StaticObject.h"
#include "Textures.h"
#include "KeyGame.h"

enum Quarter
{
	Behind, Front
};

class CWhip : public CStaticObject
{
	int ani;
	Quarter quarter;
	D3DXVECTOR2 pos;
public:
	CWhip();
	~CWhip();
	virtual	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void CreateAnimation();
	void setDirection(int dir) { this->direction = dir; }
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

