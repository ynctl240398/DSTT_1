#include "Whip.h"



CWhip::CWhip()
{
	CreateAnimation();
	quarter = Behind;
	ani = 0;
}


CWhip::~CWhip()
{
}


void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	CStaticObject::Update(dt);
}

void CWhip::CreateAnimation()
{
	CTextures *textures = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	textures->Add(ID_WHIP_TEX, L"WHIP.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texWhip = textures->Get(ID_WHIP_TEX);

	sprites->Add(20000, 0, 0, 0, 0, texWhip);
	sprites->Add(20001, 57, 16, 84, 81, texWhip); // stand attack left 1 sau
	sprites->Add(20002, 145, 20, 174, 84, texWhip);

	sprites->Add(20003, 215, 15, 268, 77, texWhip); //stand attack left 1 truoc

	sprites->Add(20010, 0, 0, 0, 0, texWhip);
	sprites->Add(20011, 687, 18, 716, 83, texWhip); // stand attack right 1sau
	sprites->Add(20012, 597, 22, 626, 84, texWhip);

	sprites->Add(20013, 503, 17, 556, 79, texWhip); //stand attack right 1 truoc

	sprites->Add(20020, 74, 262, 104, 341, texWhip); // sit attack left 1sau
	sprites->Add(20021, 179, 269, 209, 331, texWhip);

	sprites->Add(20022, 261, 274, 315, 336, texWhip);// sit attack left 1 truoc

	sprites->Add(20030, 722, 261, 750, 340, texWhip); // sit attack right 1sau
	sprites->Add(20031, 563, 271, 593, 333, texWhip);

	sprites->Add(20032, 451, 274, 505, 336, texWhip);// sit attack right 1 truoc

	LPANIMATION ani; // frames

	ani = new CAnimation(1000);  //stand attack right 1
	ani->Add(20010);
	ani->Add(20011);
	ani->Add(20012);
	//ani->Add(20013);
	animations->Add(600, ani);

	ani = new CAnimation(1000);
	ani->Add(20013);
	animations->Add(601, ani);

	ani = new CAnimation(50);  //stand attack left 1
	ani->Add(20000);
	ani->Add(20001);
	ani->Add(20002);
	animations->Add(602, ani);

	ani = new CAnimation(50);
	ani->Add(20003);
	animations->Add(603, ani);

	ani = new CAnimation(100);  //sit attack left 1
	ani->Add(20020);
	ani->Add(20021);
	animations->Add(604, ani);

	ani = new CAnimation(100);  //sit attack left 1
	ani->Add(20022);
	animations->Add(605, ani);

	ani = new CAnimation(100);  //stand attack left 1
	ani->Add(20030);
	ani->Add(20031);
	animations->Add(606, ani);
	ani = new CAnimation(100);  //stand attack left 1
	ani->Add(20032);
	animations->Add(607, ani);

	this->AddAnimation(600);
	this->AddAnimation(601);
	this->AddAnimation(602);
	this->AddAnimation(603);
	this->AddAnimation(604);
	this->AddAnimation(605);
	this->AddAnimation(606);
	this->AddAnimation(607);
}

void CWhip::Render()
{
	direction = CGameObject::direction;
	if (direction == -1)
	{
		if (quarter == Behind)
		{
			ani = WHIP_I_ANI_BEHIND_SIMON_STAND_LEFT;
			this->pos = { position.x + 32, position.y };
			if (animations[ani]->getDone())
			{
				quarter = Front;
				animations[ani]->setDone(false);
				animations[ani]->setCurrentFrame(-1);
			}
		}
		else
		{
			ani = WHIP_I_ANI_FRONT_SIMON_STAND_LEFT;
			this->pos = { position.x - 53, position.y };
			if (animations[ani]->getDone())
			{
				quarter = Behind;
				animations[ani]->setDone(false);
				animations[ani]->setCurrentFrame(-1);
			}
		}
	}
	else
	{
		if (quarter == Behind)
		{
			ani = WHIP_I_ANI_BEHIND_SIMON_STAND_RIGHT;
			this->pos = { position.x - 29, position.y };
			if (animations[ani]->getDone())
			{
				quarter = Front;
				animations[ani]->setDone(false);
				animations[ani]->setCurrentFrame(-1);
			}
		}
		else
		{
			ani = WHIP_I_ANI_FRONT_SIMON_STAND_RIGHT;
			this->pos = { position.x + 32, position.y };
			if (animations[ani]->getDone())
			{
				quarter = Behind;
				animations[ani]->setDone(false); 
				animations[ani]->setCurrentFrame(-1);
			}
		}
		//ani = WHIP_I_ANI_SIMON_STAND_RIGHT;
		///*if (animations[ani]->GetCurrentFrame() == animations[ani]->GetTotalFrame())
		//{
		//	return;
		//}*/
		//if (animations[ani]->GetCurrentFrame() == animations[ani]->GetTotalFrame() - 1)
		//{
		//	this->pos = { position.x + 32, position.y };
		//}
		//else this->pos = { position.x - 29, position.y };
	}
	DebugOut(L"%d", animations[ani]->GetCurrentFrame());
	animations[ani]->Render(pos);
}

void CWhip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

