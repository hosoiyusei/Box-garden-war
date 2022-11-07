#include"pch.h"
#include"Player.h"

#include"../Stage/StageRead.h"
#include"../UnitManager/UnitManager.h"
#include"../Stage/StageDraw.h"
#include"../DoubleSpeed/DoubleSpeed.h"
#include"../ItemManager/ItemManager.h"

#include"../UnitManager/Unit/Swordfighter/Swordfighter_Param.h"
#include"../UnitManager/Unit/Archer/Archer_Param.h"
#include"../UnitManager/Unit/Gunner/Gunner_Param.h"
#include"../UnitManager/Unit/Cannon/Cannon_Param.h"

#include"../GameUI/GameUI.h"

#pragma warning(disable:26812)

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
	, mMoney(200)
	, mGameOver(false)
	, mCapsule()
	, mpStageDraw(nullptr)
	, mUnitSpawnFlag(false)
	, mCameraMoveFlag(false)
	, mTargetSize(1.0f)
	, mItemType(ITEM_TYPE::NONE)
	, mGoalPos()
	, mpItemManager(nullptr)
	, mSecondTarget()
	, mFlag_of_whether_the_unit_can_be_put_out(true)
	, mScrollMoney(200)
	, mBlinking(0)
	, mCameraView2()
	, mpGameUI(nullptr)
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
	, ItemManager* pItemManager
	, GameUI* pGameUI)
{
	//ポインタを取得
	mpUnitManager = pUnitManager;
	mpStageDraw = pStageDraw;
	mpGameUI = pGameUI;

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
	mCameraView2.eyeX = static_cast<float>(mHorizontal * mParam.mCamera_position_adjustment);
	mCameraView2.eyeY = 25.0f;
	mCameraView2.eyeZ = static_cast<float>(mVertical * mParam.mCamera_position_adjustment) + mParam.mDisplace_camera_little;

	mCameraView.eyeX = static_cast<float>(mHorizontal * mParam.mCamera_position_adjustment);
	mCameraView.eyeY = 25.0f;
	mCameraView.eyeZ = static_cast<float>(mVertical * mParam.mCamera_position_adjustment) + mParam.mDisplace_camera_little;

	mCameraView.targetX = static_cast<float>(mHorizontal * mParam.mCamera_position_adjustment);
	mCameraView.targetY = mParam.mCamera_Target;
	mCameraView.targetZ = static_cast<float>(mVertical * mParam.mCamera_position_adjustment);

	SpawnUnit::Initialize(mpUnitManager, pPlayer,pGameUI);

	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	mpDoubleSpeed.SetSpeed(mParam.mGame_Speed);

	InputManager& inputManager = InputManager::GetInstance();

	inputManager.Reset();

	mCameraView.eyeZ = mCameraView2.eyeZ + 100.0f;
	mCameraView.eyeY = 200.0f;
}

//更新
void Player::Update()
{
	InputManager& inputManager = InputManager::GetInstance();

	//ユニットをスポーン
	if (mClear == false &&
		mGameOver == false &&
		mCameraMoveFlag == false)
	{
		UnitSpawn();
	}

	//ライフがゼロの時
	const int life_zero(0);

	if (mLife == life_zero)
	{
		mGameOver = true;
	}

	//マウスレイキャスト
	if (inputManager.GetMouseState().x < 1300)
		MouseRayCast();

	//カメラの移動
	CameraMove();

	//Targetの大きさの拡縮
	mTargetSize -= mParam.mTarget_Size;

	//Targetの最小サイズ
	const float minimum_Target_Size(0.8f);

	//Targetの元のサイズ
	const float target_Default_Size(1.0f);

	//縮んだら元に戻す
	if (mTargetSize < minimum_Target_Size)
	{
		mTargetSize = target_Default_Size;
	}

	if (mMoney < mScrollMoney)
	{
		mScrollMoney--;
	}
	else if (mMoney > mScrollMoney)
	{
		mScrollMoney++;
	}

	//スピードアップ
	SpeedUp();

	//アイテムを使う
	UseItem();

	//アイテムを取得
	GetItem();

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

	if (mUnitSpawnFlag == true && mPos == mSecondTarget)
	{
		pObject.GetTexture3D()->SetColor(1.0f, 1.0f, 1.0f);
	}

	STAGE_DATA tiledata = mStageData[static_cast<int>(mPos.z)][static_cast<int>(mPos.x)];

	pObject.GetTexture3D()->SetColor(0.0f, 1.0f, 1.0f,static_cast<float> (sin(mBlinking) * 0.5f + 0.5f) * 0.9f);

	if (tiledata.tileData == TILE_DATA::Unit_Scaffolding)
	{
		mBlinking += 0.05f;

		pObject.GetTexture3D()->DrawShader(mWorld, TEXTURE3D::ENEMY_HP);
	}
	else
	{
		mBlinking = 0.0f;
	}

	pObject.GetTexture3D()->SetColor();
	pObject.GetTexture3D()->DrawShader(mWorld, TEXTURE3D::TARGET);

	Drawing_the_attack_range_of_the_unit();
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

	//真上視点のカメラの高さ
	float Top_view_camera_height = 22.0f;

	//斜め視点のカメラの高さ
	float Oblique_view_camera_height = 13.5f;

	//カメラを引いた座標
	float Coordinates_minus_the_camera=12.0f;

	if (inputManager.GetButtonStateTracker()->rightButton == inputManager.GetButtonStateTracker()->PRESSED &&
		mCameraView2.eyeY != Oblique_view_camera_height)
	{
		mCameraView2.eyeZ = mCameraView2.eyeZ + Coordinates_minus_the_camera;
		mCameraView2.eyeY = Oblique_view_camera_height;
	}
	else if (inputManager.GetButtonStateTracker()->rightButton == inputManager.GetButtonStateTracker()->PRESSED &&
		mCameraView2.eyeY == Oblique_view_camera_height)
	{
		mCameraView2.eyeZ = mCameraView2.eyeZ - Coordinates_minus_the_camera;
		mCameraView2.eyeY = Top_view_camera_height;
	}
	else if(mCameraView.eyeY == 200.0f)
	{
		mCameraView2.eyeZ = mCameraView2.eyeZ + Coordinates_minus_the_camera;
		mCameraView2.eyeY = Oblique_view_camera_height;
	}

	Vector3 pos = Vector3(mCameraView.eyeX, mCameraView.eyeY, mCameraView.eyeZ);

	pos += (Vector3(mCameraView2.eyeX, mCameraView2.eyeY, mCameraView2.eyeZ)- pos) * 0.035f;

	mCameraView.eyeX = pos.x;
	mCameraView.eyeY = pos.y;
	mCameraView.eyeZ = pos.z;

	//マウスホイールの回転のリセット
	if (inputManager.GetMouseState().scrollWheelValue < -481 ||
		inputManager.GetMouseState().scrollWheelValue > 481)
	{
		inputManager.Reset();
	}
}

//Unitをスポーン
void Player::UnitSpawn()
{
	if (mFlag_of_whether_the_unit_can_be_put_out == false)return;

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
const Matrix Player::CreateMatrix_Screen2World()
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
	mCapsule.mStart = mouseStart;
	mCapsule.mEnd = mouseEnd;

	Plane plane = Plane(0.0f, 1.0f, 0.0f, 0.0f);

	Vector3 intersection = IntersectPlaneAndLine(mouseStart, mouseEnd, plane);

	//ステージのブロックとマウスとの当たり判定
	if (mUnitSpawnFlag == false)
	{
		mPos = mpStageDraw->ObjectCollision(intersection);
	}
	else
	{
		mSecondTarget = mpStageDraw->ObjectCollision(intersection);
	}
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

	if (1370 <= inputManager.GetMouseState().x &&//縮小
		1430 >= inputManager.GetMouseState().x &&
		820 <= inputManager.GetMouseState().y &&
		880 >= inputManager.GetMouseState().y &&
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

	if (1470 <= inputManager.GetMouseState().x &&//縮小
		1530 >= inputManager.GetMouseState().x &&
		820 <= inputManager.GetMouseState().y &&
		880 >= inputManager.GetMouseState().y &&
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

//線分ABと平面の交点を計算する
const Vector3 Player::IntersectPlaneAndLine(
	const Vector3& A,   //線分始点
	const Vector3& B,   //線分終点
	const Plane& PL) //平面
{
	//平面上の点P
	Vector3 P = Vector3(PL.x * PL.w, PL.y * PL.w, PL.z * PL.w);

	//PA PBベクトル
	Vector3 PA = Vector3(P.x - A.x, P.y - A.y, P.z - A.z);
	Vector3 PB = Vector3(P.x - B.x, P.y - B.y, P.z - B.z);

	//PA PBそれぞれを平面法線と内積
	float dot_PA = static_cast<float>(PA.x * PL.x + PA.y * PL.y + PA.z * PL.z);
	float dot_PB = static_cast<float>(PB.x * PL.x + PB.y * PL.y + PB.z * PL.z);

	//これは線端が平面上にあった時の計算の誤差を吸収しています。調整して使ってください。
	if (abs(dot_PA) < 0.000001f) { dot_PA = 0.0f; }
	if (abs(dot_PB) < 0.000001f) { dot_PB = 0.0f; }

	//以下、交点を求める 

	Vector3 AB = Vector3(B.x - A.x, B.y - A.y, B.z - A.z);

	//交点とAの距離 : 交点とBの距離 = dot_PA : dot_PB
	float hiritu = abs(dot_PA) / (abs(dot_PA) + abs(dot_PB));

	return Vector3(A.x + (AB.x * hiritu), A.y + (AB.y * hiritu), A.z + (AB.z * hiritu));
}

//Targetが重なっているとき
const bool Player::Stage_Target_Duplicate()
{
	if (mPos == mSecondTarget)
	{
		return true;
	}

	return false;
}

//ユニットの攻撃範囲の描画
void Player::Drawing_the_attack_range_of_the_unit()
{
	DrawManager& pObject = DrawManager::GetInstance();

	//ステージデータの取得
	STAGE_DATA tiledata = mStageData[static_cast<int>(mPos.z)][static_cast<int>(mPos.x)];

	Matrix world = Matrix::Identity;

	if (tiledata.tileData == TILE_DATA::Swordfighter)
	{
		Swordfighter_Param swordfighter_Param;
		world = Matrix::CreateScale(swordfighter_Param.mAttack_range * 2.0f);
	}
	else if (tiledata.tileData == TILE_DATA::Archer)
	{
		Archer_Param archer_Param;
		world = Matrix::CreateScale(archer_Param.mAttack_range * 2.0f);
	}
	else if (tiledata.tileData == TILE_DATA::Gunner)
	{
		Gunner_Param gunner_Param;
		world = Matrix::CreateScale(gunner_Param.mAttack_range * 2.0f);
	}
	else if (tiledata.tileData == TILE_DATA::Cannon)
	{
		Cannon_Param cannon_Param;
		world = Matrix::CreateScale(cannon_Param.mAttack_range * 2.0f);
	}
	else
	{
		InputManager& inputManager = InputManager::GetInstance();

		if (GetUnitSelectFlag() == true)
		{
			if (mpGameUI->Summon_Unit_Button(UNIT_TYPE::SWORDFIGHTER)->When_the_mouse_cursor_enters_the_range() == true)
			{
				Swordfighter_Param swordfighter_Param;
				world = Matrix::CreateScale(swordfighter_Param.mAttack_range * 2.0f);
			}
			else if (mpGameUI->Summon_Unit_Button(UNIT_TYPE::ARCHER)->When_the_mouse_cursor_enters_the_range() == true)
			{
				Archer_Param archer_Param;
				world = Matrix::CreateScale(archer_Param.mAttack_range * 2.0f);
			}
			else if (mpGameUI->Summon_Unit_Button(UNIT_TYPE::GUNNER)->When_the_mouse_cursor_enters_the_range() == true)
			{
				Gunner_Param gunner_Param;
				world = Matrix::CreateScale(gunner_Param.mAttack_range * 2.0f);
			}
			else if (mpGameUI->Summon_Unit_Button(UNIT_TYPE::CANNON)->When_the_mouse_cursor_enters_the_range() == true)
			{
				Cannon_Param cannon_Param;
				world = Matrix::CreateScale(cannon_Param.mAttack_range * 2.0f);
			}
			else if (inputManager.GetMouseState().scrollWheelValue == 0)
			{
				Swordfighter_Param swordfighter_Param;
				world = Matrix::CreateScale(swordfighter_Param.mAttack_range * 2.0f);
			}
			else if (inputManager.GetMouseState().scrollWheelValue == -120 ||
				inputManager.GetMouseState().scrollWheelValue == 480)
			{
				Archer_Param archer_Param;
				world = Matrix::CreateScale(archer_Param.mAttack_range * 2.0f);
			}
			else if (inputManager.GetMouseState().scrollWheelValue == -240 || 
				inputManager.GetMouseState().scrollWheelValue == 360)
			{
				Gunner_Param gunner_Param;
				world = Matrix::CreateScale(gunner_Param.mAttack_range * 2.0f);
			}
			else if (inputManager.GetMouseState().scrollWheelValue == -360 || 
				inputManager.GetMouseState().scrollWheelValue == 240)
			{
				Cannon_Param cannon_Param;
				world = Matrix::CreateScale(cannon_Param.mAttack_range * 2.0f);
			}
			else
				return;
		}
		else
			return;
	}

	world *= Matrix::CreateRotationX(XMConvertToRadians(90.0f));
	world *= Matrix::CreateTranslation(Vector3(mPos.x, mPos.y + 0.5f, mPos.z));

	pObject.GetTexture3D()->SetColor(0.3f,0.3f,1.0f,0.8f);
	pObject.GetTexture3D()->DrawShader(world, TEXTURE3D::RANGE);
}