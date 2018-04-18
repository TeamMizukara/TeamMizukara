//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

#include "Title.h"
extern int g_SceneNumber;

//コンストラクタ
CTitle::CTitle()
	:m_x(0), m_y(0),m_cursor(LEFT), m_IsDrawOpe(false)
{

}

CTitle::~CTitle()
{

}

void CTitle::Action()
{
	//左を押したら左に
	if (Input::KeyPush(VK_LEFT)==true)
	{
		m_cursor = LEFT;
	}
	//右を押したら右に
	else if (Input::KeyPush(VK_RIGHT) == true)
	{
		m_cursor = RIGHT;
	}
	//下を押したら下に
	else if (Input::KeyPush(VK_DOWN) == true)
	{
		if(m_cursor!=UNDER)
			m_BefCursor = m_cursor;
		m_cursor = UNDER;
	}
	else if (Input::KeyPush(VK_UP) == true && m_cursor==UNDER)
	{
		m_cursor = m_BefCursor;
	}

	//カーソル位置が左なら
	if (m_cursor==LEFT)
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
	}
	//カーソル位置が右なら
	else if(m_cursor==RIGHT)
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
	}
	//カーソル位置が下なら
	else 
	{
		if (Input::KeyPush(VK_RETURN) == true)
		{
			if (key_flag)
			{
				m_IsDrawOpe = !(m_IsDrawOpe);
				key_flag = false;
			}
		}
		else
		{
			key_flag = true;
		}
	}
}

void CTitle::Draw()
{
	Draw::Draw2D(13, m_x, m_y);

	if (m_cursor == LEFT)
	{
		Draw::Draw2D(14, 80, 280);
	}
	else if(m_cursor==RIGHT)
	{
		Draw::Draw2D(14,450, 280);
	}
	else 
	{
		Draw::Draw2D(14, 280, 440);
	}

	if (m_IsDrawOpe) 
	{
		Draw::Draw2D(17, 0, 0);
	}
}