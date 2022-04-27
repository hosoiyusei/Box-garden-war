#include"pch.h"
#include"ArmoredSoldier.h"
#include"../../EffectManager/EffectManager.h"
#include"../../Player/Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//Enemyの基礎の速さ
const float ENEMY_SPEED(0.01f);

//コンストラクタ
ArmoredSoldier::ArmoredSoldier()
	:mLevel(ENEMY_LEVEL::NONE)
	, mHP(0)
	, mSlowFootFlag(false)
	, mSlowFootTimer(0)
	, mSpeed(0.0f)
	, mpEffectManager(nullptr)
	, mpPlayer(nullptr)
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

	mLevel = level;

	mHP = SetHP();

	mSpeed = ENEMY_SPEED;
}

//更新
void ArmoredSoldier::Update()
{
	//鈍足状態の時
	if (mSlowFootFlag == true)
	{
		mSlowFootTimer++;
	}

	//鈍足状態を解除
	if (mSlowFootTimer >= 180)
	{
		mSlowFootTimer = 0;
		mSlowFootFlag = false;
		mSpeed = ENEMY_SPEED;
	}
}

//描画
void ArmoredSoldier::Draw(const Vector3& pos
	, const float& angle)
{
	DrawManager& pObject = DrawManager::GetInstance();

	//pObject.GetGeometry()->Draw(world, SHAPE::Sphere, Colors::Red);
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
	world *= Matrix::CreateTranslation(Vector3(pos.x, pos.y - 0.4f, pos.z));
	pObject.GetTexture3D()->DrawShader(world, TEXTURE3D::SHADOW);


	//HPゲージの描画
	pObject.GetTexture3D()->SetColor(0.0f, 1.0f);

	world = Matrix::Identity;
	pObject.GetTexture3D()->DrawBillboard(world);
	world *= Matrix::CreateScale((static_cast<float>(mHP) / static_cast<float>(SetHP())), 0.1f, 0.1f);
	world *= Matrix::CreateTranslation(Vector3(pos.x, pos.y + 0.8f, pos.z - 0.3f));

	pObject.GetTexture3D()->DrawShader(world, TEXTURE3D::ENEMY_HP);
}

//Damageの処理
const bool& ArmoredSoldier::Damage(const DirectX::SimpleMath::Vector3& pos
	, const int& damage, const BULLET_TYPE& type, const UNIT_LEVEL& level)
{
	SoundManager& soundmanager = SoundManager::GetInstance();

	//Enemyが無敵でないなら
	mHP -= damage;
	soundmanager.SE_Run(SOUND_SE::SE_DAMAGE, SE_RUN::PLAY);

	//当たった攻撃が魔法だったら
	if (type == BULLET_TYPE::MAGIC)
	{
		SlowFoot();
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

/***************************************************************************************************************************************************************/

//鈍足状態
void ArmoredSoldier::SlowFoot()
{
	mSlowFootFlag = true;
	mSlowFootTimer = 0;
	mSpeed = ENEMY_SPEED * 0.5f;
}

//HPの設定
const int& ArmoredSoldier::SetHP()
{
	switch (mLevel)
	{
		case ENEMY_LEVEL::LEVEL1: {return 20; break; }
		case ENEMY_LEVEL::LEVEL2: {return 40; break; }
		case ENEMY_LEVEL::LEVEL3: {return 60; break; }
		case ENEMY_LEVEL::LEVEL4: {return 80; break; }
		case ENEMY_LEVEL::LEVEL5: { return 100; break; }
		default:break;
	}
}

//金
const int& ArmoredSoldier::GetMoney()
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