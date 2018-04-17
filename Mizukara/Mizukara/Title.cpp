//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

#include "Title.h"
extern int g_SceneNumber;

//コンストラクタ
CTitle::CTitle()
	:m_x(0), m_y(0)
	,key_flag(false)
{

}

CTitle::~CTitle()
{

}

void CTitle::Action()
{
	if (Input::KeyPush(VK_RETURN) == true)
	{
		if (key_flag)
		{
			g_SceneNumber = GAME;
			is_delete = true;
			key_flag = false;
		}
	}
	else
	{
		key_flag = true;
	}

	if (Input::KeyPush('S') == true)
	{
		if (key_flag)
		{
			is_delete = true;
			key_flag = false;
		}
	}
	else
	{
		key_flag = true;
	}

}

void CTitle::Draw()
{
	Draw::Draw2D(13, m_x, m_y);
}