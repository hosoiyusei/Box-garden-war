#include"pch.h"
#include"Player.h"

#include"../Stage/StageRead.h"
#include"../UnitManager/UnitManager.h"
#include"../Stage/StageDraw.h"
#include"../DoubleSpeed/DoubleSpeed.h"
#include"../ItemManager/ItemManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const int SCREEN_W = 1600;
const int SCREEN_H = 900;

//コンストラクタ
Player::Player()
	: mStageData{}
	, mPos()
	, mHorizontal(0)
	, mVertical(0)
	, mWorld()
	, mpUnitManager(nullptr)
	, mLife(10)
	, mClear(false)
	, mCameraView()
	, mCameraHeight(10.0f)
	, mMoney(200)
	, mGameOver(false)
	, mCapsule()
	, mpStageDraw(nullptr)
	, mUnitSpawnFlag(false)
	, mCameraMoveFlag(false)
	, mTargetSize(1.0f)
	, mItemType(ITEM_TYPE::NONE)
	, mGoalPos()
{

}

//デストラクタ
Player::~Player()
{

}

//初期化
void Player::Initialize(
	  StageRead* pStageRead
	, UnitManager* pUnitManager
	, StageDraw* pStageDraw
	, Player* pPlayer
, ItemManager* pItemManager)
{
	//ポインタを取得
	mpUnitManager = pUnitManager;
	mpStageDraw = pStageDraw;

	//ステージの横幅を取得
	mHorizontal = pStageRead->GetHorizontal();
	//ステージの立幅を取得
	mVertical = pStageRead->GetVertical();

	mpItemManager = pItemManager;

	//ステージデータの取得
	for (int i = 0; i < mVertical; i++)
	{
		//ステージデータの配列を追加
		mStageData.push_back(std::vector<STAGE_DATA>());

		for (int j = 0; j < mHorizontal; j++)
		{
			//ステージデータの配列を追加
			mStageData[i].push_back(STAGE_DATA());

			mStageData[i][j].tileData = SetStageData(pStageRead->GetStageData(j, i));

			if (mStageData[i][j].tileData == TILE_DATA::Goal)
			{
				mGoalPos.x = static_cast<float>(j);
				mGoalPos.z = static_cast<float>(i);
			}

			mStageData[i][j].unit_Level = UNIT_LEVEL::NONE;
		}
	}

	//カメラの座標の初期化
	mCameraView.eyeX = static_cast<float>(mHorizontal * 0.5f);
	mCameraView.eyeY = mCameraHeight;
	mCameraView.eyeZ = static_cast<float>(mVertical * 0.5f) + 0.1f;

	mCameraView.targetX = static_cast<float>(mHorizontal * 0.5f);
	mCameraView.targetY = 0.0f;
	mCameraView.targetZ = static_cast<float>(mVertical * 0.5f);

	SpawnUnit::Initialize(mpUnitManager, pPlayer);

	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	mpDoubleSpeed.SetSpeed(1.0f);

	InputManager& inputManager = InputManager::GetInstance();

	inputManager.Reset();
}

//更新
void Player::Update()
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	if (mpDoubleSpeed.GetExecutionFlag() == true)
	{
		//ユニットをスポーン
		if (mClear == false &&
			mGameOver == false &&
			mCameraMoveFlag == false)
		{
			UnitSpawn();
		}

		if (mLife == 0)
		{
			mGameOver = true;
		}

		if (mUnitSpawnFlag == false)
		{
			//カメラの移動
			CameraMove();

			//マウスレイキャスト
			MouseRayCast();
		}

		//Targetの大きさの拡縮
		mTargetSize -= 0.005f;

		//縮んだら元に戻す
		if (mTargetSize < 0.8f)
		{
			mTargetSize = 1.0f;
		}

		//スピードアップ
		SpeedUp();

		//アイテムを使う
		UseItem();

		//アイテムを取得
		GetItem();
	}

	//一時停止
	Pause();
}

//描画
void Player::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();
	pObject.GetTexture3D()->SetColor();

	//プレイヤーの移動
	mWorld = Matrix::Identity;
	mWorld *= Matrix::CreateRotationX(-1.57f);
	mWorld *= Matrix::CreateScale(mTargetSize);
	mWorld *= Matrix::CreateTranslation(mPos);

	//プレイヤーの位置の描画
	pObject.GetTexture3D()->DrawShader(mWorld, TEXTURE3D::TARGET);

	int x = mLife;
	float posx = mGoalPos.x+0.2f;
	for (int i = 0; i < 2; i++)
	{
		int a = 0;

		a = x % 10;
		mWorld = Matrix::Identity;
		mWorld *= Matrix::CreateRotationY(3.14f);
		mWorld *= Matrix::CreateRotationX(-1.57f);
		mWorld *= Matrix::CreateTranslation(posx, mGoalPos.y+0.7f, mGoalPos.z);
		pObject.GetTexture3D()->SetColor(1.0f, 1.0f, 1.0f);
		NumDraw(a);
		posx -= 0.3f;
		x /= 10;
	}
}

//ダメージを受ける
void Player::LifeDamage()
{
	if (mLife != 0)
	{
		mLife--;
	}
}

void Player::SetMoney(const int money)
{
	mMoney += money;
}

/**********************************************************************/

//カメラの移動
void Player::CameraMove()
{
	InputManager& inputManager = InputManager::GetInstance();

	//カメラのズーム
	if (16000 > abs(inputManager.GetMouseState().scrollWheelValue))
		mCameraView.eyeY = inputManager.GetMouseState().scrollWheelValue * -0.005;
}

//Unitをスポーン
void Player::UnitSpawn()
{
	InputManager& inputManager = InputManager::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	if (inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
	{
		//Unitを呼び出す
		mUnitSpawnFlag = SpawnUnit::Spawn(mPos.x, mPos.z);

		//ウィンドウが出てなかったら鳴らす
		if (mUnitSpawnFlag == true)
		{
			soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		}
	}
}

//スクリーン座標をワールド座標に変換する行列を作成する関数 
const Matrix& Player::CreateMatrix_Screen2World()
{
	CameraParam& pCm = CameraParam::GetInstance();

	Matrix viewport;

	viewport._11 = 1600 / 2.0f;

	viewport._22 = -SCREEN_H / 2.0f;

	viewport._41 = 1600 / 2.0f;

	viewport._42 = SCREEN_H / 2.0f;

	// 逆行列を作成
	Matrix invS = viewport.Invert();

	Matrix invP = pCm.GetProjection().Invert();

	Matrix invV = pCm.GetView().Invert();

	// 『ビューポートスケーリング行列の逆行列』 × 『射影行列の逆行列』 × 『ビュー行列の逆行列』
	return invS * invP * invV;
}

//マウスレイキャスト
void Player::MouseRayCast()
{
	InputManager& inputManager = InputManager::GetInstance();

	Vector3 mouseStart(
		  static_cast<float>(inputManager.GetMouseState().x)
		, static_cast<float>(inputManager.GetMouseState().y)
		, 0.0f);

	Vector3 mouseEnd(
		  static_cast<float>(inputManager.GetMouseState().x)
		, static_cast<float>(inputManager.GetMouseState().y)
		, 1.0f);

	Matrix screen2WorldMatrix = CreateMatrix_Screen2World();

	mouseStart = Vector3::Transform(mouseStart, screen2WorldMatrix);

	mouseEnd = Vector3::Transform(mouseEnd, screen2WorldMatrix);

	//Capsuleの当たり判定
	mCapsule.a = mouseStart;
	mCapsule.b = mouseEnd;

	//ステージのブロックとマウスとの当たり判定
	mPos = mpStageDraw->ObjectCollision(mCapsule);
}

//初期化時のステージデータの設定
const TILE_DATA Player::SetStageData(const int& datanum)
{
	if (datanum == 1)
	{
		return TILE_DATA::Wall;
	}
	else if (datanum == 2)
	{
		return TILE_DATA::Goal;
	}
	else if (
		datanum == 3 ||
		datanum == 4 ||
		datanum == 5
		)
	{
		return TILE_DATA::EnemyStart;
	}
	else if (datanum == 0)
	{
		return TILE_DATA::Road;
	}
	else if (datanum == -1)
	{
		return TILE_DATA::Unit_Scaffolding;
	}

	return TILE_DATA::NONE;
}

//倍速
void Player::SpeedUp()
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	if (1400-30 <= inputManager.GetMouseState().x &&//縮小
		1400+30 >= inputManager.GetMouseState().x &&
		850-30 <= inputManager.GetMouseState().y &&
		850+30 >= inputManager.GetMouseState().y &&
		inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
	{
		if (mpDoubleSpeed.GetSpeed() == 1.0f)
		{
			mpDoubleSpeed.SetSpeed(2.0f);
			soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		}
		else if (mpDoubleSpeed.GetSpeed() == 2.0f)
		{
			mpDoubleSpeed.SetSpeed(3.0f);
			soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		}
		else
		{
			mpDoubleSpeed.SetSpeed(1.0f);
			soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		}
	}
}

//一時停止
void Player::Pause()
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	if (1500-30 <= inputManager.GetMouseState().x &&//縮小
		1500+30 >= inputManager.GetMouseState().x &&
		850-30 <= inputManager.GetMouseState().y &&
		850+30 >= inputManager.GetMouseState().y &&
		inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
	{
		if (mpDoubleSpeed.GetExecutionFlag() == true)
		{
			mpDoubleSpeed.SetExecutionFlag(false);
			soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		}
		else
		{
			mpDoubleSpeed.SetExecutionFlag(true);
			soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		}
	}
}

void Player::GetItem()
{
	if (mItemType == ITEM_TYPE::NONE)
	{
		mpItemManager->CheckHitCapsule(mCapsule);
	}

	if (mItemType == ITEM_TYPE::Money)
	{
		mMoney += 100;
		mItemType = ITEM_TYPE::NONE;
	}
}

void Player::UseItem()
{
	InputManager& inputManager = InputManager::GetInstance();

	int PosX = static_cast<int>(mPos.x);
	int PosY = static_cast<int>(mPos.z);
	if (mItemType != ITEM_TYPE::NONE)
	{
		if (mItemType==ITEM_TYPE::Pit&&
			GetStageData(PosX, PosY).tileData == TILE_DATA::Road&&
			inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
		{
			mpItemManager->Use(mPos, mItemType);
			mItemType = ITEM_TYPE::NONE;
		}
		else if (mItemType == ITEM_TYPE::Mallet &&
			GetStageData(PosX, PosY).tileData == TILE_DATA::Goal &&
			inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
		{
			if (mLife != 10)
			{
				mLife++;
			}
			mItemType = ITEM_TYPE::NONE;
		}
	}
}

void Player::NumDraw(const int& num)
{
	DrawManager& pObject = DrawManager::GetInstance();
	switch (num)
	{
		case 0: {pObject.GetTexture3D()->DrawShader(mWorld, TEXTURE3D::NUM0); break; }
		case 1: {pObject.GetTexture3D()->DrawShader(mWorld, TEXTURE3D::NUM1); break; }
		case 2: {pObject.GetTexture3D()->DrawShader(mWorld, TEXTURE3D::NUM2); break; }
		case 3: {pObject.GetTexture3D()->DrawShader(mWorld, TEXTURE3D::NUM3); break; }
		case 4: {pObject.GetTexture3D()->DrawShader(mWorld, TEXTURE3D::NUM4); break; }
		case 5: {pObject.GetTexture3D()->DrawShader(mWorld, TEXTURE3D::NUM5); break; }
		case 6: {pObject.GetTexture3D()->DrawShader(mWorld, TEXTURE3D::NUM6); break; }
		case 7: {pObject.GetTexture3D()->DrawShader(mWorld, TEXTURE3D::NUM7); break; }
		case 8: {pObject.GetTexture3D()->DrawShader(mWorld, TEXTURE3D::NUM8); break; }
		case 9: {pObject.GetTexture3D()->DrawShader(mWorld, TEXTURE3D::NUM9); break; }
		default:break;
	}
}