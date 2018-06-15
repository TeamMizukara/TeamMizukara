//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

#include "Result.h"
#include "Hero.h"
#include "ObjGround.h"
#include "ObjGround2.h"
#include "ObjGround3.h"
#include "Sprinkler.h"
#include "Sprinkler2.h"
#include "Sprinkler3.h"

extern int g_SceneNumber;
extern bool g_key_flag;
extern float g_TankRemaining;
extern bool g_clearlist;

//コンストラクタ
CResult::CResult()
	:m_x(0), m_y(0), m_cursor(0)
{
	m_name = RESULT;
}

CResult::~CResult()
{

}

void CResult::Action()
{
	Audio::StopLoopMusic(6);

	Audio::StartLoopMusic(10);
	Audio::LoopMusicVolume(10, 0.07f);

	//上を押したら上に
	if (Input::KeyPush(VK_UP) == true)
	{
		if (key_flag)
		{
			if (m_cursor != 0)m_cursor--;
			key_flag = false;
		}
	}
	//下を押したら下に
	else if (Input::KeyPush(VK_DOWN) == true)
	{
		if (key_flag)
		{
			if (m_cursor != 2)m_cursor++;
			key_flag = false;
		}
	}
	else key_flag = true;

	ObjGround3* ground3 = (ObjGround3*)TaskSystem::GetObj(GROUND3);
	if (ground3 != nullptr) {
		m_cursor = 1;
	}

	if (m_cursor == 0)
	{
		if (Input::KeyPush(VK_RETURN) == true)
		{
			CObjGround* ground = (CObjGround*)TaskSystem::GetObj(GROUND);
			ObjGround2* ground2 = (ObjGround2*)TaskSystem::GetObj(GROUND2);

			if (g_key_flag)
			{
				if (ground != nullptr) {
					Audio::StopLoopMusic(5);
					Audio::StartMusic(0);
					g_SceneNumber = GAME2;
					Audio::StartLoopMusic(7);
					Audio::LoopMusicVolume(7, 0.05f);
					g_clearlist = true;
					TaskSystem::TaskClear();
					is_delete = true;
					g_key_flag = false;
				}
				else if (ground2 != nullptr) {
					Audio::StopLoopMusic(5);
					Audio::StartMusic(0);
					g_SceneNumber = GAME3;
					Audio::StartLoopMusic(8);
					Audio::LoopMusicVolume(8, 0.05f);
					g_clearlist = true;
					TaskSystem::TaskClear();
					is_delete = true;
					g_key_flag = false;
				}
			}
		}
		else
		{
			g_key_flag = true;
		}

	}
	//カーソル位置が上ならタイトルへ
	else if (m_cursor == 1)
	{
		if (Input::KeyPush(VK_RETURN) == true)
		{
			if (g_key_flag)
			{
				Audio::StartMusic(0);
				Audio::StopLoopMusic(10);
				g_SceneNumber = TITLE;
				g_clearlist = true;
				TaskSystem::TaskClear();
				is_delete = true;
				g_key_flag = false;
			}
		}
		else
		{
			g_key_flag = true;
		}
	}
	//カーソル位置が下ならステージセレクトへ
	else if (m_cursor == 2)
	{
		if (Input::KeyPush(VK_RETURN) == true)
		{
			if (g_key_flag)
			{
				if (ground3 != nullptr) {
					g_SceneNumber = ALLCLEAR;
					g_clearlist = true;
					TaskSystem::TaskClear();
					is_delete = true;
					g_key_flag = false;
				}
				else {
					Audio::StartMusic(0);
					Audio::StopLoopMusic(10);
					g_SceneNumber = STAGESELECTO;
					g_clearlist = true;
					TaskSystem::TaskClear();
					is_delete = true;
					g_key_flag = false;
				}
			}
		}
		else
		{
			g_key_flag = true;
		}
	}
	
}

void CResult::Draw()
{
	CSPRI* spri = (CSPRI*)TaskSystem::GetObj(SPRI);
	CSPRI2* spri2 = (CSPRI2*)TaskSystem::GetObj(SPRI2);
	CSPRI3* spri3 = (CSPRI3*)TaskSystem::GetObj(SPRI3);

	if (spri!=nullptr && spri->GetCrearCnt1())
	{
		Draw::Draw2D(101, m_x, m_y);
	}
	else if (spri2 != nullptr && spri2->GetCrearCnt2())
	{
		Draw::Draw2D(102, m_x, m_y);
	}
	else if (spri3 != nullptr && spri3->GetCrearCnt3())
	{
		Draw::Draw2D(103, m_x, m_y);
	}

	if (m_cursor == 0)
	{
		Draw::Draw2D(14, 295, 90);
	}
	else if (m_cursor == 1)
	{
		Draw::Draw2D(14, 300, 215);
	}
	else {
		Draw::Draw2D(14,295, 320);
	}

	//ランク表示
	if (g_TankRemaining >= 40)
	{
		Draw::Draw2D(108, 83, 243);
	}
	else if (g_TankRemaining >= 35)
	{
		Draw::Draw2D(107, 83, 243);
	}
	else if (g_TankRemaining >= 25)
	{
		Draw::Draw2D(106, 83, 243);
	}
	else if (g_TankRemaining >= 10)
	{
		Draw::Draw2D(105, 83, 243);
	}
	else if (g_TankRemaining >= 1)
	{
		Draw::Draw2D(104, 83, 243);
	}
}