#include"pch.h"
#include"ArmoredSoldier.h"
#include"../../EffectManager/EffectManager.h"
#include"../../Player/Player.h"

#include"../../DoubleSpeed/DoubleSpeed.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//Enemyの基礎の速さ
const float ENEMY_SPEED(0.01f);

//コンストラクタ
ArmoredSoldier::ArmoredSoldier()
	:mSpearAngle(0.0f)
	, mLeftHandPos()
	, mRightHandPos()
	, mLevel(ENEMY_LEVEL::NONE)
	, mHandAngle(0.0f)
	, mHP(0)
	, mSlowFootTimer(0)
	, mSpeed(0.0f)
	, mpEffectManager(nullptr)
	, mpPlayer(nullptr)
	, mEnemy_Status(Enemy_Status::generally)
	, mEnemy_Status2(Enemy_Status::generally)
	, mCombustionTimer(0)
	, mPos()
	, mArmor_point(true)
{

}

//デストラクタ
ArmoredSoldier::~ArmoredSoldier()
{

}

//Enemyを出現させる
void ArmoredSoldier::Spawn(EffectManager* pEffectManager, Player* pPlayer, const ENEMY_LEVEL& level)
{
	mpEffectManager = pEffectManager;
	mpPlayer = pPlayer;

	mSpeed = ENEMY_SPEED;

	mLevel = level;

	mHP = SetHP();

	mArmor_point = true;
}

//エフェクトの色の設定
const Vector3 ArmoredSoldier::GetEffectColor()
{
	switch (mLevel)
	{
		case ENEMY_LEVEL::LEVEL1: {return Vector3(1.0f, 0.0f, 0.0f); break; }
		case ENEMY_LEVEL::LEVEL2: {return Vector3(1.0f, 1.0f, 0.0f); break; }
		case ENEMY_LEVEL::LEVEL3: {return Vector3(1.0f, 0.0f, 1.0f); break; }
		case ENEMY_LEVEL::LEVEL4: {return Vector3(0.0f, 1.0f, 1.0f); break; }
		case ENEMY_LEVEL::LEVEL5: {return Vector3(0.0f, 1.0f, 0.0f); break; }
		default:break;
	}

	return Vector3();
}

//更新
void ArmoredSoldier::Update()
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	mLeftHandPos = Vector3(0.0f, -0.3f, 0.5f);
	mRightHandPos = Vector3(0.0f, -0.3f, -0.5f);
	mSpearAngle = 1.0f;
	mHandAngle += 0.1f * mpDoubleSpeed.GetSpeed();

	Processingofeachstate();
	Processingofeachstate2();
}

//描画
void ArmoredSoldier::Draw(const Vector3& pos
	, const float& angle, const float& fade)
{
	DrawManager& pObject = DrawManager::GetInstance();
	ResourceManager& pRm = ResourceManager::GetInstance();

	mPos = pos;

	Matrix body			//胴体
		, head			//頭
		, leftHand		//左手
		, rightHand		//右手
		, spear;		//槍

	//胴
	body = Matrix::CreateScale(0.7f, 0.8f, 0.7f);
	body *= Matrix::CreateRotationY(angle);
	if (mHP == 0)
	{
		body *= Matrix::CreateRotationX(angle);
		body *= Matrix::CreateRotationZ(angle);
	}
	body *= Matrix::CreateTranslation(pos.x, pos.y-0.5f, pos.z);

	pObject.GetGeometry()->DrawSetColor(body, SHAPE::CONE, Color(GetEffectColor())* fade);

	//頭
	head *= Matrix::CreateRotationY(XMConvertToRadians(-90.0f));
	head *= Matrix::CreateScale(0.4f);
	head *= Matrix::CreateTranslation(Vector3(0.0f, -1.4f, 0.0f));
	head *= body;
	
	if (mArmor_point == true)
	{
		pRm.GetResourceModel()->SetColor(MODEL_NAME::MASK, Colors::Black* fade);

		if (fade == 1.0f)
		{
			pObject.GetModel()->Draw(head, MODEL_NAME::MASK);
			pObject.GetModel()->Draw(head, MODEL_NAME::HELMET);
		}
		else
		{
			static int fadetimer = 0;

			++fadetimer %= 2;

			if (fadetimer == 0)
			{
				pObject.GetModel()->Draw(head, MODEL_NAME::MASK);
				pObject.GetModel()->Draw(head, MODEL_NAME::HELMET);
			}
		}
		
	}
	else
	{
		head = Matrix::Identity;
		head = Matrix::CreateScale(0.5f);
		head *= Matrix::CreateTranslation(Vector3(0.0f, 0.5f, 0.0f));
		head *= body;
		pObject.GetGeometry()->Draw(head, SHAPE::SPHERE, Colors::BurlyWood* fade);
	}
	
	

	//右手
	rightHand = Matrix::CreateScale(0.3f);
	rightHand *= Matrix::CreateTranslation(mRightHandPos);
	rightHand *= Matrix::CreateRotationZ(XMConvertToRadians(static_cast<float>(sin(mHandAngle) * 50.0f)));
	rightHand *= body;



	pObject.GetGeometry()->Draw(rightHand, SHAPE::SPHERE, Colors::BurlyWood* fade);

	//左手
	leftHand = Matrix::CreateScale(0.3f);
	leftHand *= Matrix::CreateTranslation(mLeftHandPos);
	leftHand *= Matrix::CreateRotationZ(XMConvertToRadians(static_cast<float>(-sin(mHandAngle) * 50.0f)));
	leftHand *= body;

	pObject.GetGeometry()->Draw(leftHand, SHAPE::SPHERE, Colors::BurlyWood* fade);

	spear = Matrix::CreateScale(0.004f);
	spear *= Matrix::CreateRotationX(XMConvertToRadians(-60.0f));
	spear *= Matrix::CreateRotationY(XMConvertToRadians(90.0f));
	spear *= Matrix::CreateTranslation(-0.6f, 0.5f, 0.0f);
	spear *= rightHand;

	if (fade == 1.0f)
	{
		pObject.GetModel()->Draw(spear, MODEL_NAME::SWORD);
	}
	else
	{
		static int fadetimer = 0;

		++fadetimer %= 2;

		if (fadetimer == 0)
		{
			pObject.GetModel()->Draw(spear, MODEL_NAME::SWORD);
		}
	}
}

//エフェクトの描画
void ArmoredSoldier::EffectDraw(const Vector3& pos)
{
	DrawManager& pObject = DrawManager::GetInstance();
	pObject.GetTexture3D()->SetColor();

	//影の描画
	Matrix world = Matrix::Identity;
	world *= Matrix::CreateScale(1.0f);
	world *= Matrix::CreateRotationX(-1.57f);
	world *= Matrix::CreateTranslation(Vector3(pos.x, pos.y - 0.99f, pos.z));
	pObject.GetTexture3D()->DrawShader(world, TEXTURE3D::SHADOW);


	//HPゲージの描画
	pObject.GetTexture3D()->SetColor(0.0f, 1.0f);

	world = Matrix::Identity;
	pObject.GetTexture3D()->DrawBillboard(world);
	world *= Matrix::CreateScale((static_cast<float>(mHP) / static_cast<float>(SetHP())), 0.1f, 0.1f);
	world *= Matrix::CreateTranslation(Vector3(pos.x, pos.y, pos.z - 0.3f));

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
const bool ArmoredSoldier::Damage(const DirectX::SimpleMath::Vector3& pos
	, const int& damage, const BULLET_TYPE& type, const UNIT_LEVEL& level)
{
	UNREFERENCED_PARAMETER(level);

	SoundManager& soundmanager = SoundManager::GetInstance();

	if (mArmor_point == false)
	{
		int Damage = damage;
		//Enemyが無敵でないなら
		mHP -= Damage;
		soundmanager.SE_Run(SOUND_SE::SE_DAMAGE, SE_RUN::PLAY);

		//当たった攻撃が剣だったら
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
	else if (mArmor_point == true)
	{
		int Damage = damage;

		if (BULLET_TYPE::CANNONBALL == type)
		{
			mArmor_point = false;
			mHP -= Damage;
		}
		mHP--;
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

	return true;
}

//死んでいるかどうか
const bool ArmoredSoldier::Whetherdead()
{
	//HPが0いかになったら殺す
	if (mHP <= 0)
	{
		mHP = 0;

		//エフェクトの実行
		mpEffectManager->Play(mPos, GetEffectColor(), 15, TEXTURE3D::SHADOW);

		//金を増やす
		mpPlayer->SetMoney(GetMoney());

		return false;
	}

	return true;
}

/***************************************************************************************************************************************************************/

//鈍足状態
void ArmoredSoldier::SlowFoot()
{
	mSlowFootTimer = 0;
	mSpeed = ENEMY_SPEED * 0.5f;
}

//燃焼状態
void ArmoredSoldier::Combustion()
{
	mCombustionTimer = 0;
}

//HPの設定
const int ArmoredSoldier::SetHP()
{
	switch (mLevel)
	{
		case ENEMY_LEVEL::LEVEL1: {return 6; break; }
		case ENEMY_LEVEL::LEVEL2: {return 12; break; }
		case ENEMY_LEVEL::LEVEL3: {return 25; break; }
		case ENEMY_LEVEL::LEVEL4: {return 30; break; }
		case ENEMY_LEVEL::LEVEL5: { return 40; break; }
		default:break;
	}

	return 0;
}

//金
const int ArmoredSoldier::GetMoney()
{
	switch (mLevel)
	{
		case ENEMY_LEVEL::LEVEL1: {return 8 ; break; }
		case ENEMY_LEVEL::LEVEL2: {return 9 ; break; }
		case ENEMY_LEVEL::LEVEL3: {return 10; break; }
		case ENEMY_LEVEL::LEVEL4: {return 11; break; }
		case ENEMY_LEVEL::LEVEL5: {return 12; break; }
		default:break;
	}

	return 0;
}

//状態ごとの処理
void ArmoredSoldier::Processingofeachstate()
{
	switch (mEnemy_Status)
	{
		case Enemy_Status::combustion:
		{
			mCombustionTimer++;

			int time = mCombustionTimer;

			time %= 100;

			//燃焼ダメージを与える
			if (time == 0)
			{
				mHP -= 1;
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
void ArmoredSoldier::Processingofeachstate2()
{
	switch (mEnemy_Status2)
	{
		case Enemy_Status::combustion:
		{
			mCombustionTimer++;

			int time = mCombustionTimer;

			time %= 100;

			//燃焼ダメージを与える
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