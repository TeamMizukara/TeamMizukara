#pragma once
//使用するヘッダ
#include "GameEngine\\Draw2DPolygon.h"
#include "GameEngine\\Input.h"
#include "GameEngine\\Audio.h"
#include "GameEngine\\TaskSystem.h"
#include "GameEngine\\Collision.h"

//ギミック8(色付きドア？扉？門？)クラス
class ObjColorDoor :public CObj
{
public:
	ObjColorDoor(float x,float y, int color_number,bool ud, unsigned int n);
	~ObjColorDoor();
	void Action();
	void Draw();

	void AddY(float y);

private:
	float m_x;//位置
	float m_y;
	float m_x2;//位置
	float m_y2;

	int m_color_number;//赤か緑のグラフィックのIDセット用

	bool m_Up_or_Down;//上がるドアか下がるドアか

	//float m_gx;  //グラフィック位置
	//float m_gy;

	HitLine* m_hit_line_ColorDoor[4];//当たり判定
};

