#include "Simon.h"



CSimon::CSimon()
{
	CreateAnimation();
	k = CKeyGame::getInstance();
	whip = new CWhip();
}


CSimon::~CSimon()
{
}
void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	CMovingObject::Update(dt);
	KeyBoardHandler();
	Move();
	whip->SetPosition(position);
	velocity.y += SIMON_GRAVITY;
	if (position.y > GROUND_HEIGHT)
	{
		velocity.y = 0;
		position.y = GROUND_HEIGHT;
		isOnGround = true;
		if (state == SIMON_STATE_JUMP || state == SIMON_STATE_JUMP_TO)
			SetState(SIMON_STATE_IDDLE);
	}
	else isOnGround = false;

	if (velocity.x > 0 && position.x > LIMIT_SRCEEN_RIGHT)
		position.x = LIMIT_SRCEEN_RIGHT;
	else if (velocity.x < 0 && position.x < LIMIT_SRCEEN_LEFT)
		position.x = LIMIT_SRCEEN_LEFT;
}
void CSimon::Render()
{
	
	if (state == SIMON_STATE_ATTACK)
	{
		whip->Render();
	}
	animations[ani]->Render(position);
	if (animations[ani]->getDone() == true)
	{
		if (state == SIMON_STATE_ATTACK || state == SIMON_STATE_SIT_ATTACK)
		{
			animations[ani]->setDone(false);
			animations[ani]->setCurrentFrame(-1);
		}
		if (state != SIMON_STATE_WALK && state != SIMON_STATE_JUMP && state != SIMON_STATE_JUMP_TO)
		{
			SetState(SIMON_STATE_IDDLE);
		}
	}
}
void CSimon::Move()
{
	CMovingObject::Move();
}
void CSimon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_WALK:
		velocity = { SIMON_WALKING_SPEED*direction, 0 };
		if (direction == -1)
			ani = SIMON_ANI_WALKING_LEFT;
		else ani = SIMON_ANI_WALKING_RIGHT;
		break;
	case SIMON_STATE_JUMP:
		velocity = {0, -SIMON_JUMP_SPEED_Y};
		if (direction == -1)
			ani = SIMON_ANI_JUMP_LEFT;
		else ani = SIMON_ANI_JUMP_RIGHT;
		break;
	case SIMON_STATE_SIT:
		velocity = { 0, 0 };
		if (direction == -1)
			ani = SIMON_ANI_SIT_LEFT;
		else ani = SIMON_ANI_SIT_RIGHT;
		break;
	case SIMON_STATE_ATTACK:
		if (isOnGround == true)
		{
			velocity = { 0,0 };
		}
		else velocity.y += SIMON_GRAVITY;
		if (direction == -1)
			ani = SIMON_ANI_ATTACK_LEFT;
		else ani = SIMON_ANI_ATTACK_RIGHT;
		//whip = new CWhip();
		whip->setDirection(direction);
		break;
	case SIMON_STATE_IDDLE:
		velocity = { 0, 0 };
		if (direction == -1)
			ani = SIMON_ANI_IDLE_LEFT;
		else ani = SIMON_ANI_IDLE_RIGHT;
		break;
	case SIMON_STATE_JUMP_TO:
		if (position.y >= GROUND_HEIGHT)
			if (position.y > LIMIT_JUMP_HEIGHT)
				velocity = { direction*JUMP_FAR, -SIMON_JUMP_SPEED_Y };
		if (direction == -1)
			ani = SIMON_ANI_JUMP_LEFT;
		else ani = SIMON_ANI_JUMP_RIGHT;
		break;
	case SIMON_STATE_SIT_ATTACK:
		if (direction == -1)
			ani = SIMON_ANI_SIT_ATTACK_LEFT;
		else ani = SIMON_ANI_SIT_ATTACK_RIGHT;
		break;
	}
}
void CSimon::CreateAnimation()
{
	CTextures *textures = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	textures->Add(ID_SIMON_TEX, L"SIMON.png", SIMON_COLOR);
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_SIMON_TEX);

	sprites->Add(10004, 740, 2, 768, 64, texSimon); //walk right
	sprites->Add(10003, 794, 2, 824, 64, texSimon);
	sprites->Add(10002, 858, 2, 882, 64, texSimon);
	sprites->Add(10001, 916, 2, 948, 64, texSimon);

	sprites->Add(10011, 12, 2, 44, 64, texSimon); //walk left
	sprites->Add(10012, 78, 2, 102, 64, texSimon);
	sprites->Add(10013, 136, 2, 166, 64, texSimon);
	sprites->Add(10014, 196, 2, 220, 64, texSimon);

	sprites->Add(10020, 12, 2, 44, 64, texSimon);
	sprites->Add(10021, 312, 2, 344, 64, texSimon); //attack left
	sprites->Add(10022, 372, 2, 404, 64, texSimon);
	sprites->Add(10023, 432, 2, 464, 64, texSimon);

	sprites->Add(10031, 616, 2, 648, 64, texSimon);
	sprites->Add(10032, 556, 2, 588, 64, texSimon); //attack right
	sprites->Add(10033, 496, 2, 528, 64, texSimon);
	sprites->Add(10030, 916, 2, 948, 64, texSimon);

	sprites->Add(10041, 252, 2, 284, 64, texSimon); //jump left or sit left 
	sprites->Add(10042, 676, 2, 708, 64, texSimon); //jump right or sit right

	sprites->Add(10050, 252, 2, 284, 64, texSimon);
	sprites->Add(10051, 432, 68, 464, 130, texSimon); //sit attack left
	sprites->Add(10052, 12, 134, 44, 196, texSimon);
	sprites->Add(10053, 72, 134, 104, 196, texSimon);

	sprites->Add(10060, 676, 2, 708, 64, texSimon);
	sprites->Add(10061, 496, 68, 528, 130, texSimon); //sit attack right
	sprites->Add(10062, 916, 134, 948, 196, texSimon);
	sprites->Add(10063, 856, 134, 888, 196, texSimon);

	LPANIMATION ani;

	ani = new CAnimation(100); //walk left
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	animations->Add(501, ani);

	ani = new CAnimation(100); //walk right
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	animations->Add(500, ani);

	ani = new CAnimation(100); //idle left
	ani->Add(10011);
	animations->Add(502, ani);

	ani = new CAnimation(100); //idle right
	ani->Add(10001);
	animations->Add(503, ani);

	ani = new CAnimation(50);  //attack left
	ani->Add(10020);
	ani->Add(10021);
	ani->Add(10022);
	ani->Add(10023);
	animations->Add(504, ani);

	ani = new CAnimation(1000); //attack right
	ani->Add(10030);
	ani->Add(10031);
	ani->Add(10032);
	ani->Add(10033);
	animations->Add(505, ani);

	ani = new CAnimation(100); //Jump left
	ani->Add(10042);
	animations->Add(506, ani);

	ani = new CAnimation(100); //Jump right
	ani->Add(10041);
	animations->Add(507, ani);

	ani = new CAnimation(100);  //sit attack left
	ani->Add(10050);
	ani->Add(10051);
	ani->Add(10052);
	ani->Add(10053);
	animations->Add(508, ani);

	ani = new CAnimation(100);  // sit attack left
	ani->Add(10060);
	ani->Add(10061);
	ani->Add(10062);
	ani->Add(10063);
	animations->Add(509, ani);

	this->AddAnimation(503);
	this->AddAnimation(502);
	this->AddAnimation(501);
	this->AddAnimation(500);
	this->AddAnimation(504);
	this->AddAnimation(505);
	this->AddAnimation(506);
	this->AddAnimation(507);
	this->AddAnimation(509);
	this->AddAnimation(508);
}

void CSimon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

void CSimon::KeyBoardHandler()
{
	if (k->keyAttack)
	{
		if (k->keyDown) SetState(SIMON_STATE_SIT_ATTACK);
		else SetState(SIMON_STATE_ATTACK);
	}
	if (state != SIMON_STATE_ATTACK && state != SIMON_STATE_SIT_ATTACK)
	{
		if (isOnGround)
		{
			if (k->keyDown)
			{
				SetState(SIMON_STATE_SIT);
			}
			else
			{
				if (k->keyJumpPress)
				{
					if (k->keyMove) SetState(SIMON_STATE_JUMP_TO);
					else SetState(SIMON_STATE_JUMP);
				}
				else if (k->keyMove)
				{
					SetState(SIMON_STATE_WALK);
				}
				else SetState(SIMON_STATE_IDDLE);
			}
		}
	}
	if (k->keyLeft) direction = -1;
	else if (k->keyRight) direction = 1;
}
