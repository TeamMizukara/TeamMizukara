//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

#include "ObjDownBlock_TankStage2.h"
#include "ObjDownBlockStage2.h"
#include "ObjGround2.h"
#include "BucketMeter.h"
extern int g_SceneNumber;

const float ObjDownBlock_TankStage2::m_WaveSize_x = 0.23f*0.2f;

ObjDownBlock_TankStage2::ObjDownBlock_TankStage2()
	:m_x(889), m_y(210), m_gx(691), m_gy(135), m_wave_x(889), m_wave_y(218),
	m_ani_time1(0.0f), m_ani_time2(0.0f), m_WaveSize_y(0.3f*0.2f)
	, m_water_x(889), m_water_y(223), m_moveY(162),
	m_RopeSizeBucket(0.3f), m_water_remaining(2.0f)
	, m_bucket_remaining(0.4f), m_PulleyAni(0)
{
	//ヒットラインの作成(左)
	m_hit_line_DwBlS2Tank = Collision::HitLineInsert(this);
	m_hit_line_DwBlS2Tank->SetPos1(m_x, m_y);
	m_hit_line_DwBlS2Tank->SetPos2(m_x, m_y + 100);
	m_hit_line_DwBlS2Tank->SetElement(2);		//属性を2にする
	m_hit_line_DwBlS2Tank->SetInvisible(false);	//無敵モード無効
}

ObjDownBlock_TankStage2::~ObjDownBlock_TankStage2()
{

}

void ObjDownBlock_TankStage2::Action()
{
	ObjGround2* ground2 = (ObjGround2*)TaskSystem::GetObj(GROUND2);

	if (m_PulleyAni > 8) m_PulleyAni = 0;

	//タンクから水を汲む＆戻す
	for (int i = 0; i < 10; i++)
	{
		if (m_hit_line_DwBlS2Tank->GetHitData()[i] != nullptr)
		{
			//自分の当たり判定の中に主人公の当たり判定があったら
			if (m_hit_line_DwBlS2Tank->GetHitData()[i]->GetElement() == 0)
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
							ObjDownBlockStage2* db = (ObjDownBlockStage2*)TaskSystem::GetObj(DOWNBLOCKSTAGE2);

							m_gy -= 0.5f;  //バケツ移動
							m_RopeSizeBucket -= 0.0015f;  //バケツ側ロープ長さ変更

							db->AddY(0.8f);  //足場ブロック移動
							db->SetRopeSizeScaffold(0.0025f);  //足場ロープ長さ変更

							db->SetY(0.8f);  //足場当たり判定移動

							m_bucket_remaining -= 0.006f;  //水減らす
														   //波の位置
							if (m_wave_y < 248)m_wave_y -= 0.26f;
							else m_wave_y -= 0.3f;
							m_water_y -= 0.325f;  //水の位置

							if (bm != nullptr) {
								//バケツメーターにセット
								bm->PushX();
							}

							//（バケツ満タン/75フレーム）
							m_water_remaining -= 0.02666;

							m_PulleyAni++;

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
						if (m_water_remaining < 2.0f) {
							//足場オブジェクト取得
							ObjDownBlockStage2* db = (ObjDownBlockStage2*)TaskSystem::GetObj(DOWNBLOCKSTAGE2);
							m_gy += 0.5f;  //バケツ移動
							m_RopeSizeBucket += 0.0015f;  //バケツ側ロープ長さ変更

							db->AddY(-0.8f);  //足場ブロック移動
							db->SetRopeSizeScaffold(-0.0025f);  //足場ロープ長さ変更

							db->SetY(-0.8f);  //足場当たり判定移動

							m_bucket_remaining += 0.006f;  //水減らす
														   //波の位置
							if (m_wave_y < 248)m_wave_y += 0.26f;
							else m_wave_y += 0.3f;
							m_water_y += 0.325f;  //水の位置
												
							if (bm != nullptr) {
								//バケツメーターにセット
								bm->PushC();
							}

							//（バケツ満タン/75フレーム）
							m_water_remaining += 0.02666;

							m_PulleyAni++;

						}
					}
				}
				break;
			}
		}
	}

	m_WaveSize_y = m_water_remaining *0.06f;
	if (m_WaveSize_y > 0.6f)m_WaveSize_y = 0.6f;

	//当たり判定位置の更新
	m_hit_line_DwBlS2Tank->SetPos1(m_x + ground2->GetScroll(), m_y);
	m_hit_line_DwBlS2Tank->SetPos2(m_x + ground2->GetScroll(), m_y + 100);
}

void ObjDownBlock_TankStage2::Draw()
{
	ObjGround2* ground2 = (ObjGround2*)TaskSystem::GetObj(GROUND2);

	//ロープ表示
	Draw::Draw2D(62, m_gx + 206 + ground2->GetScroll(), 100, 1, m_RopeSizeBucket);
	//横ロープ表示
	Draw::Draw2D(59, m_gx + 206 + ground2->GetScroll(), 85, 0.9, 1);
	//滑車表示
	if (m_PulleyAni <= 4)
		Draw::Draw2D(80, m_gx + 200 + ground2->GetScroll(), 80, 1, 1);
	else
		Draw::Draw2D(80, m_gx + 350 + ground2->GetScroll(), 80, -1, 1);

	//ギミックに近づいたらアイコンを出す
	for (int i = 0; i < 10; i++)
	{
		if (m_hit_line_DwBlS2Tank->GetHitData()[i] != nullptr)
		{
			if (m_hit_line_DwBlS2Tank->GetHitData()[i]->GetElement() == 0)
			{
				Draw::Draw2D(70, m_x-20 + ground2->GetScroll(), m_y-195);
			}
		}
	}

	//水表示
	if (m_bucket_remaining >= 0.0f)
		Draw::Draw2D(48, m_water_x + ground2->GetScroll(), m_water_y, 0.025, m_bucket_remaining/18);

	//波アニメーション(後ろ)
	if (m_ani_time1 >= 109)
	{
		m_ani_time1 = 0;
	}
	else
	{
		m_ani_time1++;
	}
	//波アニメーション描画(後ろ)
	if (m_bucket_remaining >= 0.0f)
		Draw::Draw2D(36 + (m_ani_time1 / 10), m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);

	//波アニメーション(前)
	if (m_ani_time2 >= 54)
	{
		m_ani_time2 = 0;
	}
	else
	{
		m_ani_time2++;
	}
	//波アニメーション描画(前)
	if (m_bucket_remaining >= 0.0f)
		Draw::Draw2D(25 + (m_ani_time2 / 5), m_wave_x + ground2->GetScroll(), m_wave_y, m_WaveSize_x, m_WaveSize_y);	
	//バケツ表示
	Draw::Draw2D(56, m_gx + 197 + ground2->GetScroll(), m_gy + 64, 1, 1);
}