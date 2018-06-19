#pragma once
//�g�p����w�b�_
#include "GameEngine\\Draw2DPolygon.h"
#include "GameEngine\\Input.h"
#include "GameEngine\\Audio.h"
#include "GameEngine\\TaskSystem.h"
#include "GameEngine\\Collision.h"

//�M�~�b�N2(������u���b�N)�N���X
class ObjBoat :public CObj
{
public:
	ObjBoat();
	~ObjBoat();

	void Action();
	void Draw();

	//void AddY(float y) { m_gy += y; }  //�����Y���������
	void SetRopeSizeScaffold(float rss) { m_RopeSizeScaffold += rss; }
	//void SetY(float y) { m_y += y; }  //����u���b�N�̓����蔻�蓮�������

private:
	float m_x;//�ʒu
	float m_y;

	float m_gx;//�O���t�B�b�N�̈ʒu
	float m_gy;

	float m_RopeSizeScaffold;

	float m_scroll;

	HitLine* m_hit_line_Boat[4];//�����蔻��
};