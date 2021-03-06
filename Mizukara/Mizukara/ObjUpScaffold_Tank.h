#pragma once
//使用するヘッダ
#include "GameEngine\\Draw2DPolygon.h"
#include "GameEngine\\Input.h"
#include "GameEngine\\Audio.h"
#include "GameEngine\\TaskSystem.h"
#include "GameEngine\\Collision.h"

//ギミック1タンククラス
class ObjUpScaffold_Tank : public CObj
{
public:
	ObjUpScaffold_Tank();
	~ObjUpScaffold_Tank();
	void Action();
	void Draw();
private:
	float m_x; //ギミック1の位置
	float m_y;

	float m_gx;  //グラフィック位置
	float m_gy;

	float m_moveY;

	float m_wave_x;  //波の位置
	float m_wave_y;

	float m_water_x;  //水の位置
	float m_water_y;

	int m_ani_time1;  //波アニメーション用
	int m_ani_time2;

	float m_water_remaining;

	static const float m_WaveSize_x;  //波のサイズ用

	float m_WaterSize_y;//水用
	float m_WaveSize_y;//波用

	float m_RopeSizeBoard;//蓋の方のロープの長さ
	float m_RopeSizeScaffold;//足場の方のロープの長さ

	int m_PulleyAni;//滑車アニメーション用

	HitLine* m_hit_line_UpScTank;//当たり判定
};
