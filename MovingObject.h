#pragma once
#include "GameObject.h"

class CMovingObject : public CGameObject
{
public:
	CMovingObject();
	~CMovingObject();

	virtual	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual	void Render() = 0;
	virtual	void Move();
};

