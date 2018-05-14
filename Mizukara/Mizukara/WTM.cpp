//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

#include "WTM.h"
#include "ObjGround.h"
extern int g_SceneNumber;

CWTM::CWTM()
	:m_x(1186), m_y(234),m_x1(1190),m_y1(150),m_ani_time1(0.0f),m_ani_time2(0.0f)
	,im_x(1166), im_y(30)
{
	//ヒットラインの作成(左)
	m_p_hit_line_wtm = Collision::HitLineInsert(this);
	m_p_hit_line_wtm->SetPos1(m_x, m_y);
	m_p_hit_line_wtm->SetPos2(m_x, m_y+100);
	m_p_hit_line_wtm->SetElement(2);		//属性を2にする
	m_p_hit_line_wtm->SetInvisible(false);	//無敵モード無効
}

CWTM::~CWTM()
{

}

void CWTM::Action()
{
	CObjGround* ground = (CObjGround*)TaskSystem::GetObj(GROUND);

	//当たり判定位置の更新
	m_p_hit_line_wtm->SetPos1(m_x+ground->GetScroll(), m_y);
	m_p_hit_line_wtm->SetPos2(m_x+ground->GetScroll(), m_y + 100);
}

void CWTM::Draw()
{
	CObjGround* ground = (CObjGround*)TaskSystem::GetObj(GROUND);

	//WTMに近づいたらアイコンを出す
	for (int i = 0; i < 10; i++)
	{
		if (m_p_hit_line_wtm->GetHitData()[i] != nullptr)
		{
			if (m_p_hit_line_wtm->GetHitData()[i]->GetElement() == 0)
			{
				Draw::Draw2D(21, im_x + ground->GetScroll(), im_y);
			}
		}
	}

	//波アニメーション(後ろ)
	if (m_ani_time1 >= 109)
	{
		m_ani_time1 = 0;
	}
	else
	{
		m_ani_time1++;
	}

	if (m_ani_time1 < 10)
	{
		Draw::Draw2D(36, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time1 < 20)
	{
		Draw::Draw2D(37, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time1 < 30)
	{
		Draw::Draw2D(38, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time1 < 40)
	{
		Draw::Draw2D(39, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time1 < 50)
	{
		Draw::Draw2D(40, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time1 < 60)
	{
		Draw::Draw2D(41, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time1 < 70)
	{
		Draw::Draw2D(42, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time1 < 80)
	{
		Draw::Draw2D(43, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time1 < 90)
	{
		Draw::Draw2D(44, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time1 < 100)
	{
		Draw::Draw2D(45, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time1 < 110)
	{
		Draw::Draw2D(46, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}

	//波アニメーション(前)
	if (m_ani_time2 >= 54)
	{
		m_ani_time2 = 0;
	}
	else
	{
		m_ani_time2++;
	}

	if (m_ani_time2 < 5)
	{
		Draw::Draw2D(25, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time2 < 10)
	{
		Draw::Draw2D(26, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time2 < 15)
	{
		Draw::Draw2D(27, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time2 < 20)
	{
		Draw::Draw2D(28, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time2 < 25)
	{
		Draw::Draw2D(29, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time2 < 30)
	{
		Draw::Draw2D(30, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time2 < 35)
	{
		Draw::Draw2D(31, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time2 < 40)
	{
		Draw::Draw2D(32, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time2 < 45)
	{
		Draw::Draw2D(33, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time2 < 50)
	{
		Draw::Draw2D(34, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}
	else if (m_ani_time2 < 55)
	{
		Draw::Draw2D(35, m_x1 + ground->GetScroll(), m_y1, 0.5, 0.4);
	}

	//Draw::Draw2D(21, a, m_y);
}