#include "MovingObject.h"



CMovingObject::CMovingObject()
{
}


CMovingObject::~CMovingObject()
{
}

void CMovingObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
}

void CMovingObject::Move()
{
	position += dPos;
}
