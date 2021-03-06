#include"pch.h"
#include"Ninja.h"
#include"../../EffectManager/EffectManager.h"
#include"../../Player/Player.h"

#include"../../DoubleSpeed/DoubleSpeed.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

//Enemyの基礎の速さ
const float ENEMY_SPEED(0.01f);

//コンストラクタ
Ninja::Ninja()
	:mLevel(ENEMY_LEVEL::NONE)
	, mHP(0)
	, mSlowFootTimer(0)
	, mSpeed(0.0f)
	, mpEffectManager(nullptr)
	, mpPlayer(nullptr)
	, mEnemy_Status(Enemy_Status::generally)
	, mEnemy_Status2(Enemy_Status::generally)
	, mCombustionTimer(0)
	, mPos()
	,mLeftHandPos()
	,mRightHandPos()
	,mHandAngle(0.0f)
	, mDisappearTimer(0)
{

}

//デストラクタ
Ninja::~Ninja()
{

}

//Enemyを出現させる
void Ninja::Spawn(EffectManager* pEffectManager, Player* pPlayer, const ENEMY_LEVEL& level)
{
	mpEffectManager = pEffectManager;
	mpPlayer = pPlayer;

	mSpeed = ENEMY_SPEED;

	mLevel = level;

	mHP = SetHP();
}

//エフェクトの色の設定
const DirectX::SimpleMath::Vector3 Ninja::GetEffectColor()
{
	switch (mLevel)
	{
		case ENEMY_LEVEL::LEVEL1: {return DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f); break; }
		case ENEMY_LEVEL::LEVEL2: {return DirectX::SimpleMath::Vector3(1.0f, 1.0f, 0.0f); break; }
		case ENEMY_LEVEL::LEVEL3: {return DirectX::SimpleMath::Vector3(1.0f, 0.0f, 1.0f); break; }
		case ENEMY_LEVEL::LEVEL4: {return DirectX::SimpleMath::Vector3(0.0f, 1.0f, 1.0f); break; }
		case ENEMY_LEVEL::LEVEL5: {return DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f); break; }
		default:break;
	}
}

//更新
void Ninja::Update()
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	for (int i = 0; i < mpDoubleSpeed.GetSpeed(); i++)
	{
		mDisappearTimer++;
	}

	if (mDisappearTimer >= 120)
	{
		mDisappearTimer = 0;
	}

	mLeftHandPos = Vector3(0.0f, -0.3f, 0.5f);
	mRightHandPos = Vector3(0.0f, -0.3f, -0.5f);
	mHandAngle += 0.1f * mpDoubleSpeed.GetSpeed();
	Processingofeachstate();
	Processingofeachstate2();
}

//描画
void Ninja::Draw(const Vector3& pos
	, const float& angle)
{
	if (mDisappearTimer > 60)
	{
		DrawManager& pObject = DrawManager::GetInstance();

		mPos = pos;

		Matrix body			//胴体
			, head			//頭
			, leftHand		//左手
			, rightHand;		//右手

		//胴
		body = Matrix::CreateScale(0.8f);
		body *= Matrix::CreateRotationY(angle);
		body *= Matrix::CreateTranslation(pos);

		pObject.GetGeometry()->DrawSetColor(body, SHAPE::CONE, Color(GetEffectColor()));

		//頭
		head = Matrix::CreateScale(0.5f);
		head *= Matrix::CreateTranslation(Vector3(0.0f, 0.5f, 0.0f));
		head *= body;

		pObject.GetGeometry()->Draw(head, SHAPE::SPHERE, Color(GetEffectColor()));

		//右手
		rightHand = Matrix::CreateScale(0.3f);
		rightHand *= Matrix::CreateTranslation(mRightHandPos);
		rightHand *= Matrix::CreateRotationZ(XMConvertToRadians(static_cast<float>(sin(mHandAngle) * 50.0f)));
		rightHand *= body;

		pObject.GetGeometry()->Draw(rightHand, SHAPE::SPHERE, Colors::BurlyWood);

		//左手
		leftHand = Matrix::CreateScale(0.3f);
		leftHand *= Matrix::CreateTranslation(mLeftHandPos);
		leftHand *= Matrix::CreateRotationZ(XMConvertToRadians(static_cast<float>(-sin(mHandAngle) * 50.0f)));
		leftHand *= body;

		pObject.GetGeometry()->Draw(leftHand, SHAPE::SPHERE, Colors::BurlyWood);
	}
}

//エフェクトの描画
void Ninja::EffectDraw(const Vector3& pos)
{
	DrawManager& pObject = DrawManager::GetInstance();
	pObject.GetTexture3D()->SetColor();

	//影の描画
	Matrix world = Matrix::Identity;
	world *= Matrix::CreateScale(1.0f);
	world *= Matrix::CreateRotationX(-1.57f);
	world *= Matrix::CreateTranslation(Vector3(pos.x, pos.y - 0.4f, pos.z));
	pObject.GetTexture3D()->DrawShader(world, TEXTURE3D::SHADOW);


	//HPゲージの描画
	pObject.GetTexture3D()->SetColor(0.0f, 1.0f);

	world = Matrix::Identity;
	pObject.GetTexture3D()->DrawBillboard(world);
	world *= Matrix::CreateScale((static_cast<float>(mHP) / static_cast<float>(SetHP())), 0.1f, 0.1f);
	world *= Matrix::CreateTranslation(Vector3(pos.x, pos.y + 0.8f, pos.z - 0.3f));

	pObject.GetTexture3D()->DrawShader(world, TEXTURE3D::ENEMY_HP);

	switch (mEnemy_Status)
	{
		case Enemy_Status::combustion: {mpEffectManager->Play(pos, Vector3(1.0f, 0.0f, 0.0f), 1, TEXTURE3D::SHADOW, 0.003f, 0.1f); break; }
		case Enemy_Status::Slowfoot: {mpEffectManager->Play(pos, Vector3(1.0f, 0.0f, 1.0f), 1, TEXTURE3D::SHADOW, 0.003f, 0.1f); break; }
		case Enemy_Status::generally: {break; }
		default:break;
	}

	switch (mEnemy_Status2)
	{
		case Enemy_Status::combustion: {mpEffectManager->Play(pos, Vector3(1.0f, 0.0f, 0.0f), 1, TEXTURE3D::SHADOW, 0.003f, 0.1f); break; }
		case Enemy_Status::Slowfoot: {mpEffectManager->Play(pos, Vector3(1.0f, 0.0f, 1.0f), 1, TEXTURE3D::SHADOW, 0.003f, 0.1f); break; }
		case Enemy_Status::generally: {break; }
		default:break;
	}
}

//Damageの処理
const bool& Ninja::Damage(const DirectX::SimpleMath::Vector3& pos
	, const int& damage, const BULLET_TYPE& type, const UNIT_LEVEL& level)
{
	if (mDisappearTimer < 60)
	{
		SoundManager& soundmanager = SoundManager::GetInstance();

		int Damage = damage;
		//Enemyが無敵でないなら
		mHP -= Damage;
		soundmanager.SE_Run(SOUND_SE::SE_DAMAGE, SE_RUN::PLAY);

		//当たった攻撃が剣だったら
		if (level == UNIT_LEVEL::LEVEL_3 || level == UNIT_LEVEL::LEVEL_4 || level == UNIT_LEVEL::LEVEL_5)
		{
			if (mEnemy_Status == Enemy_Status::generally)
			{
				if (type == BULLET_TYPE::SLASHING)
				{
					mEnemy_Status = Enemy_Status::Slowfoot;
					SlowFoot();
				}
				else if (type == BULLET_TYPE::SHOOT)
				{
					//燃焼
					mEnemy_Status = Enemy_Status::combustion;
					Combustion();
				}
			}
			else if (mEnemy_Status2 == Enemy_Status::generally)
			{
				if (type == BULLET_TYPE::SLASHING)
				{
					mEnemy_Status2 = Enemy_Status::Slowfoot;
					SlowFoot();
				}
				else if (type == BULLET_TYPE::SHOOT)
				{
					//燃焼
					mEnemy_Status2 = Enemy_Status::combustion;
					Combustion();
				}
			}
		}

		//HPが0いかになったら殺す
		if (mHP <= 0)
		{
			mHP = 0;

			//エフェクトの実行
			mpEffectManager->Play(pos, GetEffectColor(), 20, TEXTURE3D::SHADOW);

			//金を増やす
			mpPlayer->SetMoney(GetMoney());

			return false;
		}
	}

	return true;
}

//死んでいるかどうか
const bool& Ninja::Whetherdead()
{
	//HPが0いかになったら殺す
	if (mHP <= 0)
	{
		mHP = 0;

		//エフェクトの実行
		mpEffectManager->Play(mPos, GetEffectColor(), 20, TEXTURE3D::SHADOW);

		//金を増やす
		mpPlayer->SetMoney(GetMoney());

		return false;
	}

	return true;
}

/***************************************************************************************************************************************************************/

//鈍足状態
void Ninja::SlowFoot()
{
	mSlowFootTimer = 0;
	mSpeed = ENEMY_SPEED * 0.5f;
}

//燃焼状態
void Ninja::Combustion()
{
	mCombustionTimer = 0;
}

//HPの設定
const int& Ninja::SetHP()
{
	switch (mLevel)
	{
		case ENEMY_LEVEL::LEVEL1: {return 10; break; }
		case ENEMY_LEVEL::LEVEL2: {return 20; break; }
		case ENEMY_LEVEL::LEVEL3: {return 30; break; }
		case ENEMY_LEVEL::LEVEL4: {return 40; break; }
		case ENEMY_LEVEL::LEVEL5: { return 70; break; }
		default:break;
	}
}

//金
const int& Ninja::GetMoney()
{
	switch (mLevel)
	{
		case ENEMY_LEVEL::LEVEL1: {return 7; break; }
		case ENEMY_LEVEL::LEVEL2: {return 8; break; }
		case ENEMY_LEVEL::LEVEL3: {return 9; break; }
		case ENEMY_LEVEL::LEVEL4: {return 10; break; }
		case ENEMY_LEVEL::LEVEL5: {return 11; break; }
		default:break;
	}
}

//状態ごとの処理
void Ninja::Processingofeachstate()
{
	switch (mEnemy_Status)
	{
		case Enemy_Status::combustion:
		{
			mCombustionTimer++;

			int time = mCombustionTimer;

			time %= 60;
			if (time == 0)
			{
				mHP -= 2;
			}

			if (mCombustionTimer >= 300)
			{
				mCombustionTimer = 0;
				mEnemy_Status = Enemy_Status::generally;

			}
			break;
		}
		case Enemy_Status::Slowfoot:
		{
			//鈍足状態の時
			mSlowFootTimer++;

			//鈍足状態を解除
			if (mSlowFootTimer >= 300)
			{
				mSlowFootTimer = 0;
				mSpeed = ENEMY_SPEED;
				mEnemy_Status = Enemy_Status::generally;
			}
			break;
		}
		case Enemy_Status::generally:
		{
			break;
		}
		default:break;
	}
}

//状態ごとの処理
void Ninja::Processingofeachstate2()
{
	switch (mEnemy_Status2)
	{
		case Enemy_Status::combustion:
		{
			mCombustionTimer++;

			int time = mCombustionTimer;

			time %= 60;
			if (time == 0)
			{
				mHP -= 1;
			}

			if (mCombustionTimer >= 300)
			{
				mCombustionTimer = 0;
				mEnemy_Status2 = Enemy_Status::generally;

			}
			break;
		}
		case Enemy_Status::Slowfoot:
		{
			//鈍足状態の時
			mSlowFootTimer++;

			//鈍足状態を解除
			if (mSlowFootTimer >= 300)
			{
				mSlowFootTimer = 0;
				mSpeed = ENEMY_SPEED;
				mEnemy_Status2 = Enemy_Status::generally;
			}
			break;
		}
		case Enemy_Status::generally:
		{
			break;
		}
		default:break;
	}
}