#pragma once
//使用するヘッダ
#include "GameEngine\\Draw2DPolygon.h"
#include "GameEngine\\Input.h"
#include "GameEngine\\Audio.h"
#include "GameEngine\\TaskSystem.h"
#include "GameEngine\\Collision.h"

//ギミック2(下がるブロック)クラス
class ObjDownBlock :public CObj
{
public:
	ObjDownBlock(float x,float y);
	~ObjDownBlock();

	void Action();
	void Draw();

	void AddY(float y) { m_gy += y; }  //足場のY動かすやつ
	void SetRopeSizeScaffold(float rss) { m_RopeSizeScaffold += rss; }
	void SetY(float y) { m_y += y; }  //足場ブロックの当たり判定動かすやつ

private:
	float m_x;//位置
	float m_y;

	float m_gx;//グラフィックの位置
	float m_gy;

	float m_rope_y;//ロープの位置
	float m_RopeSizeScaffold;

	HitLine* m_hit_line_DwBl[4];//当たり判定
};