#pragma once
//�g�p����w�b�_
#include "GameEngine\\Draw2DPolygon.h"
#include "GameEngine\\Input.h"
#include "GameEngine\\Audio.h"
#include "GameEngine\\TaskSystem.h"
#include "GameEngine\\Collision.h"

//�M�~�b�N1�^���N�N���X
class ObjBoat_Tank : public CObj
{
public:
	ObjBoat_Tank();
	~ObjBoat_Tank();
	void Action();
	void Draw();

	float GetBoatWaterVolume() { return m_water_remaining; }
	//HitLine* GetHitLineBoatTank() { return m_hit_line_BoatTank[4]; }
private:
	float m_x; //�M�~�b�N4�̈ʒu
	float m_y;

	float m_gx;//�O���t�B�b�N�̈ʒu
	float m_gy;

	float m_moveY;

	float m_wave_x;  //�g�̈ʒu
	float m_wave_y;
	float m_wave_x2;
	float m_wave_y2;

	float m_water_x;  //���̈ʒu
	float m_water_y;
	float m_water_x2;  
	float m_water_y2;

	int m_ani_time_x;//�{�[�g�𓮂���
	int m_move_x;

	int m_ani_time1;  //�g�A�j���[�V�����p
	int m_ani_time2;
	int m_ani_time3;  //�{�[�g�A�j���[�V�����p

	float m_water_remaining;
	float m_bucket_remaining;
	//float m_point_position[4];

	static const float m_WaveSize_x;  //�g�̃T�C�Y�p
	static const float m_WaveSize_x2;
	float m_WaveSize_y;
	static const float m_WaterSize_x;//���̃T�C�Y
	float m_WaterSize_y;
	static const float m_WaterSize_x2;
	static const float m_WaterSize_y2;

	int m_BoatAni;//�{�[�g�A�j���[�V����(�^���N)�p

	float m_scroll;

	float m_RopeSizeBucket;//�o�P�c�̕��̃��[�v�̒���

	HitLine* m_hit_line_BoatTank[4];//�����蔻��
	HitLine* m_hit_line_Boat[2];//�����蔻��
};