#pragma once
#include "GameEngine\\Draw2DPolygon.h"
#include "GameEngine\\Input.h"
#include "GameEngine\\Audio.h"
#include "GameEngine\\TaskSystem.h"
#include "GameEngine\\Collision.h"

//ステージ2地面クラス
class ObjGround2 : public CObj
{
public:
	ObjGround2();
	~ObjGround2();
	void Action();
	void Draw();

	float GetScroll() { return m_scroll; }  //m_scroll取得用

private:
	float m_scroll;//左右スクロール用
};

