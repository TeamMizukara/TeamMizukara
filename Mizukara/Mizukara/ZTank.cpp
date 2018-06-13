//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

#include "ZTank.h"
#include "ObjGround2.h"
#include "BucketMeter.h"
extern int g_SceneNumber;

const float ObjElephant_Tank::m_WaveSize_x = 0.25f;
const float ObjElephant_Tank::m_WaveSize_y = 0.4f;

//コンストラクタ
ObjElephant_Tank::ObjElephant_Tank()
	:m_x(2230), m_y(175), m_wave_x(2230), m_wave_y(200), m_water_x(2230), m_water_y(210),
	m_ani_time1(0), m_ani_time2(0), m_ani_time_Shower(0), m_water_remaining(0.0f),m_alpha(0.0f)
{
	//ヒットラインの作成(左)
	m_hit_line_ZTank = Collision::HitLineInsert(this);
	m_hit_line_ZTank->SetPos1(m_x, m_y);
	m_hit_line_ZTank->SetPos2(m_x, m_y + 100);
	m_hit_line_ZTank->SetElement(5);		//属性を5にする
	m_hit_line_ZTank->SetInvisible(false);	//無敵モード無効
	m_hit_line_ZTank->SetAngle();
												//ヒットラインの作成2(左)
	m_hit_line_ZTankWall = Collision::HitLineInsert(this);
	m_hit_line_ZTankWall->SetPos1(m_x+60, m_y+100);
	m_hit_line_ZTankWall->SetPos2(m_x+60, m_y-200);
	m_hit_line_ZTankWall->SetElement(1);		//属性を6にする
	m_hit_line_ZTankWall->SetInvisible(false);	//無敵モード無効
	m_hit_line_ZTankWall->SetAngle();
	m_hit_line_ZTankWall->Set4direc(HIT_LEFT);
}

//デストラクタ
ObjElephant_Tank::~ObjElephant_Tank()
{

}

//アクション
void ObjElephant_Tank::Action()
{
	ObjGround2* ground = (ObjGround2*)TaskSystem::GetObj(GROUND2);

	//0じゃなかったら時間加算
	if (m_ani_time_Shower != 0 && m_ani_time_Shower < 150) {
		m_water_remaining -= 0.02f;
		m_ani_time_Shower++;
	}

	//タンクから水を汲む＆戻す
	for (int i = 0; i < 10; i++)
	{
		if (m_hit_line_ZTank->GetHitData()[i] != nullptr)
		{
			//自分の当たり判定の中に主人公の当たり判定があったら
			if (m_hit_line_ZTank->GetHitData()[i]->GetElement() == 0)
			{
				//タンクから水を汲む
				if (Input::KeyPush('X'))
				{

					//バケツメーターオブジェクト取得
					CBucketMeter* bm = (CBucketMeter*)TaskSystem::GetObj(BUCKETMETER);
					//バケツが満タンじゃなかったら
					if (bm->GetWaterRem() < 3.0f) {
						//残量がなかったら汲めない
						if (m_water_remaining > 0.0f) {

							if (bm != nullptr) {
								//バケツメーターにセット
								bm->PushX();
							}

							//　　　　　　　　　（バケツ満タン/75フレーム）
							m_water_remaining -= 0.02666;
						}
					}
				}
				//水をタンクに戻す
				if (Input::KeyPush('C'))
				{

					//バケツメーターオブジェクト取得
					CBucketMeter* bm = (CBucketMeter*)TaskSystem::GetObj(BUCKETMETER);
					//バケツが空じゃなかったら
					if (bm->GetWaterRem() > 0.0f) {
						//満タンだったら入れれない
						if (m_water_remaining < 6.0f) {

							if (bm != nullptr) {
								//バケツメーターにセット
								bm->PushC();
							}

							//（バケツ満タン/75フレーム）
							m_water_remaining += 0.02666;
						}
						else{
							//満タンになったらシャワーアニメーション開始
							m_ani_time_Shower++;
							//m_hit_line_ZTankWall->SetInvisible(true);	//無敵モード無効
							//m_alpha += 0.01f;
						}
					}
				}
				break;
			}
		}

	}

	//当たり判定位置の更新
	m_hit_line_ZTank->SetPos1(m_x + ground->GetScroll(), m_y);
	m_hit_line_ZTank->SetPos2(m_x + ground->GetScroll(), m_y + 100);

	m_hit_line_ZTankWall->SetPos1(m_x+60 + ground->GetScroll(), m_y+100);
	m_hit_line_ZTankWall->SetPos2(m_x+60 + ground->GetScroll(), m_y-200);

	//シャワーアニメーションが終わったら壁を消して虹を出す
	if (m_ani_time_Shower == 150) {
		m_hit_line_ZTankWall->SetInvisible(true);	//無敵モード無効
		m_alpha += 0.01f;
	}

	if (m_alpha!= 0.0f && m_alpha < 1.0f)m_alpha += 0.01f;

}

//ドロー
void ObjElephant_Tank::Draw()
{
	ObjGround2* ground = (ObjGround2*)TaskSystem::GetObj(GROUND2);

	//WTMに近づいたらアイコンを出す
	for (int i = 0; i < 10; i++)
	{
		if (m_hit_line_ZTank->GetHitData()[i] != nullptr)
		{
			if (m_hit_line_ZTank->GetHitData()[i]->GetElement() == 0)
			{
				Draw::Draw2D(70, m_x - 30 + ground->GetScroll(), m_y - 50);
			}
		}
	}

	//水表示
	Draw::Draw2D(48, m_water_x + ground->GetScroll(), m_water_y, 0.74, -(0.64 * m_water_remaining * 1 / 6));

	//波アニメーション(後ろ)
	if (m_ani_time1 >= 109)
	{
		m_ani_time1 = 0;
	}
	else
	{
		m_ani_time1++;
	}

	//波アニメーション(後ろ)
	if (m_ani_time1 < 10)
	{
		Draw::Draw2D(36, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 20)
	{
		Draw::Draw2D(37, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 30)
	{
		Draw::Draw2D(38, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 40)
	{
		Draw::Draw2D(39, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 50)
	{
		Draw::Draw2D(40, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 60)
	{
		Draw::Draw2D(41, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 70)
	{
		Draw::Draw2D(42, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 80)
	{
		Draw::Draw2D(43, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 90)
	{
		Draw::Draw2D(44, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 100)
	{
		Draw::Draw2D(45, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 110)
	{
		Draw::Draw2D(46, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
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

	//波アニメーション
	if (m_ani_time2 < 5)
	{
		Draw::Draw2D(25, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 10)
	{
		Draw::Draw2D(26, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 15)
	{
		Draw::Draw2D(27, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 20)
	{
		Draw::Draw2D(28, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 25)
	{
		Draw::Draw2D(29, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 30)
	{
		Draw::Draw2D(30, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 35)
	{
		Draw::Draw2D(31, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 40)
	{
		Draw::Draw2D(32, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 45)
	{
		Draw::Draw2D(33, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 50)
	{
		Draw::Draw2D(34, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 55)
	{
		Draw::Draw2D(35, m_wave_x + ground->GetScroll(), m_wave_y - m_water_remaining * 2, m_WaveSize_x, m_WaveSize_y);
	}

	Draw::Draw2D(88, m_x + ground->GetScroll(), m_y, 1, 1);

	float c[4] = { 1.0f,1.0f,1.0f,m_alpha };

	//虹
	Draw::Draw2D(87, ground->GetScroll() + 2450, 200,c);

	//シャワー
	if (m_ani_time_Shower != 0 && m_ani_time_Shower != 150) {
		//10フレームずつ切り替え
		if((m_ani_time_Shower/10)%2)
			Draw::Draw2D(109, ground->GetScroll() + 2400, 230);
		else
			Draw::Draw2D(109, ground->GetScroll() + 2430, 240);
	}
}
