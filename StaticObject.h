#pragma once
#include "GameObject.h"

class CStaticObject : public CGameObject
{
public:
	CStaticObject();
	~CStaticObject();
	virtual	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
};

