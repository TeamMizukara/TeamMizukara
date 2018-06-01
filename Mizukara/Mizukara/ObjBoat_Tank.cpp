//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

#include "ObjBoat_Tank.h"
#include "ObjBoat.h"
#include "ObjGround2.h"
#include "BucketMeter.h"
extern int g_SceneNumber;

const float ObjBoat_Tank::m_WaveSize_x = 3.25f;
const float ObjBoat_Tank::m_WaterSize_x = 9.47f;
const float ObjBoat_Tank::m_WaterSize_y = 3.90f;

ObjBoat_Tank::ObjBoat_Tank()
	:m_x(276), m_y(400), m_gx(275), m_gy(330), m_wave_x(275), m_wave_y(410),m_move_x(0.0f),
	m_ani_time1(0.0f), m_ani_time2(0.0f), m_ani_time3(0.0f), m_WaveSize_y(1.5f)
	, m_water_x(275), m_water_y(409), m_moveY(162),
	m_RopeSizeBucket(0.3f), m_water_remaining(2.0f)
	, m_bucket_remaining(0.4f), m_BoatAni(0)
{
	//ヒットラインの作成(左)
	m_hit_line_BoatTank[0] = Collision::HitLineInsert(this);
	m_hit_line_BoatTank[0]->SetPos1(m_x, m_y);
	m_hit_line_BoatTank[0]->SetPos2(m_x, m_y + 100);
	m_hit_line_BoatTank[0]->SetElement(2);		//属性を2にする
	m_hit_line_BoatTank[0]->SetInvisible(false);	//無敵モード無効

	//ボートの前方ヒットライン
	m_hit_line_BoatTank[1] = Collision::HitLineInsert(this);
	m_hit_line_BoatTank[1]->SetPos1(m_x+113, m_y);
	m_hit_line_BoatTank[1]->SetPos2(m_x+113, m_y + 100);
	m_hit_line_BoatTank[1]->SetElement(2);		//属性を2にする
	m_hit_line_BoatTank[1]->SetInvisible(false);	//無敵モード無効

	//ボートの後方ヒットライン												//ボートの前方ヒットライン
	m_hit_line_BoatTank[2] = Collision::HitLineInsert(this);
	m_hit_line_BoatTank[2]->SetPos1(m_x, m_y);
	m_hit_line_BoatTank[2]->SetPos2(m_x, m_y + 100);
	m_hit_line_BoatTank[2]->SetElement(2);		//属性を2にする
	m_hit_line_BoatTank[2]->SetInvisible(false);	//無敵モード無効
}

ObjBoat_Tank::~ObjBoat_Tank()
{

}

void ObjBoat_Tank::Action()
{
	ObjGround2* ground2 = (ObjGround2*)TaskSystem::GetObj(GROUND2);

	if (m_BoatAni > 8) m_BoatAni = 0;

	//タンクから水を汲む＆戻す
	for (int i = 0; i < 10; i++)
	{
		if (m_hit_line_BoatTank[0]->GetHitData()[i] != nullptr)
		{
			//自分の当たり判定の中に主人公の当たり判定があったら
			if (m_hit_line_BoatTank[0]->GetHitData()[i]->GetElement() == 0)
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
							//足場オブジェクト取得
							ObjBoat* bt = (ObjBoat*)TaskSystem::GetObj(BOAT);

							m_gy -= 0.5f;  //バケツ移動
							m_RopeSizeBucket -= 0.0015f;  //バケツ側ロープ長さ変更

						//	bt->AddY(0.5f);  //足場ブロック移動
							bt->SetRopeSizeScaffold(0.002f);  //足場ロープ長さ変更

					//		bt->SetY(0.5f);  //足場当たり判定移動

							m_bucket_remaining -= 0.006f;  //水減らす
														   //波の位置
							if (m_wave_y < 248)m_wave_y -= 0.26f;
							else m_wave_y -= 0.3f;
							m_water_y -= 0.325f;  //水の位置
												  //m_WaveSize_y -= 0.01f;
												  //m_RopeSizeBoard -= 0.0006f;
												  //m_RopeSizeBucket += 0.0006f;

							if (bm != nullptr) {
								//バケツメーターにセット
								bm->PushX();
							}

							//（バケツ満タン/75フレーム）
							m_water_remaining -= 0.02666;

							m_BoatAni++;

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
							//足場オブジェクト取得
							ObjBoat* bt = (ObjBoat*)TaskSystem::GetObj(BOAT);
							//m_moveY += 0.2f;
							//db->AddY(-0.2f);
							m_gy += 0.5f;  //バケツ移動
							m_RopeSizeBucket += 0.0015f;  //バケツ側ロープ長さ変更

							//bt->AddY(-0.5f);  //足場ブロック移動
							bt->SetRopeSizeScaffold(-0.002f);  //足場ロープ長さ変更

						//	db->SetY(-0.5f);  //足場当たり判定移動

							m_bucket_remaining += 0.006f;  //水減らす
														   //波の位置
							if (m_wave_y < 248)m_wave_y += 0.26f;
							else m_wave_y += 0.3f;
							m_water_y += 0.325f;  //水の位置
												  //m_WaveSize_y += 0.01f;
												  ////m_RopeSizeBoard += 0.0006f;
												  //m_RopeSizeBucket -= 0.0006f;

							if (bm != nullptr) {
								//バケツメーターにセット
								bm->PushC();
							}

							//（バケツ満タン/75フレーム）
							m_water_remaining += 0.02666;

							m_BoatAni++;

						}
					}
				}
				break;
			}
		}
	}

	m_WaveSize_y = m_water_remaining *0.5f;
	if (m_WaveSize_y > 0.6f)m_WaveSize_y = 0.6f;

	//当たり判定位置の更新
	m_hit_line_BoatTank[0]->SetPos1(m_x + ground2->GetScroll(), m_y);
	m_hit_line_BoatTank[0]->SetPos2(m_x + ground2->GetScroll(), m_y + 100);
}

void ObjBoat_Tank::Draw()
{
	ObjGround2* ground2 = (ObjGround2*)TaskSystem::GetObj(GROUND2);

	Draw::Draw2D(73, m_gx + m_move_x + ground2->GetScroll(), m_gy, 1, 1);
	//ボート表示
	/*m_ani_time3++;
	if (m_ani_time3 = 100)
	{
		m_move_x++;

		if (m_move_x = 100)
		{
			m_move_x = 160;
		}
	}*/

	//ギミックに近づいたらアイコンを出す
	for (int i = 0; i < 10; i++)
	{
		if (m_hit_line_BoatTank[0]->GetHitData()[i] != nullptr)
		{
			if (m_hit_line_BoatTank[0]->GetHitData()[i]->GetElement() == 0)
			{
				Draw::Draw2D(70, m_x - 15 + ground2->GetScroll(), m_y - 150);
			}
		}
	}

	//水表示
	Draw::Draw2D(48, m_water_x + ground2->GetScroll(), m_water_y, m_WaterSize_x, m_WaterSize_y);

	//波アニメーション(後ろ)
	if (m_ani_time1 >= 109)
	{
		m_ani_time1 = 0;
	}
	else
	{
		m_ani_time1++;
	}

	//波アニメーション
	if (m_ani_time1 < 10)
	{
		Draw::Draw2D(36, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 20)
	{
		Draw::Draw2D(37, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 30)
	{
		Draw::Draw2D(38, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 40)
	{
		Draw::Draw2D(39, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 50)
	{
		Draw::Draw2D(40, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 60)
	{
		Draw::Draw2D(41, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 70)
	{
		Draw::Draw2D(42, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 80)
	{
		Draw::Draw2D(43, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 90)
	{
		Draw::Draw2D(44, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 100)
	{
		Draw::Draw2D(45, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time1 < 110)
	{
		Draw::Draw2D(46, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
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
		Draw::Draw2D(25, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 10)
	{
		Draw::Draw2D(26, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 15)
	{
		Draw::Draw2D(27, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 20)
	{
		Draw::Draw2D(28, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 25)
	{
		Draw::Draw2D(29, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 30)
	{
		Draw::Draw2D(30, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 35)
	{
		Draw::Draw2D(31, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 40)
	{
		Draw::Draw2D(32, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 45)
	{
		Draw::Draw2D(33, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 50)
	{
		Draw::Draw2D(34, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}
	else if (m_ani_time2 < 55)
	{
		Draw::Draw2D(35, m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);
	}

	//Draw::Draw2D(21, a, m_y);

	
	
}