#pragma once
//使用するヘッダ
#include "GameEngine\\Draw2DPolygon.h"
#include "GameEngine\\Input.h"
#include "GameEngine\\Audio.h"
#include "GameEngine\\TaskSystem.h"
#include "GameEngine\\Collision.h"

//背景クラス
class CBackground : public CObj
{
public:
	CBackground();
	~CBackground();
	void Action();
	void Draw();
private:
	float m_x; //位置
	float m_y;
	float m_x2;

	float m_x_2;  //2枚目の空の位置
	float m_x2_2;

	//float m_x_scroll;  //空のスクロール用

	float m_scroll;//左右スクロール用
};