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

//�R���X�g���N�^
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

//�f�X�g���N�^
Player::~Player()
{

}

//������
void Player::Initialize(
	  StageRead* pStageRead
	, UnitManager* pUnitManager
	, StageDraw* pStageDraw
	, Player* pPlayer
, ItemManager* pItemManager)
{
	//�|�C���^���擾
	mpUnitManager = pUnitManager;
	mpStageDraw = pStageDraw;

	//�X�e�[�W�̉������擾
	mHorizontal = pStageRead->GetHorizontal();
	//�X�e�[�W�̗������擾
	mVertical = pStageRead->GetVertical();

	mpItemManager = pItemManager;

	//�X�e�[�W�f�[�^�̎擾
	for (int i = 0; i < mVertical; i++)
	{
		//�X�e�[�W�f�[�^�̔z���ǉ�
		mStageData.push_back(std::vector<STAGE_DATA>());

		for (int j = 0; j < mHorizontal; j++)
		{
			//�X�e�[�W�f�[�^�̔z���ǉ�
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

	//�J�����̍��W�̏�����
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

//�X�V
void Player::Update()
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();

	if (mpDoubleSpeed.GetExecutionFlag() == true)
	{
		//���j�b�g���X�|�[��
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
			//�J�����̈ړ�
			CameraMove();

			//�}�E�X���C�L���X�g
			MouseRayCast();
		}

		//Target�̑傫���̊g�k
		mTargetSize -= 0.005f;

		//�k�񂾂猳�ɖ߂�
		if (mTargetSize < 0.8f)
		{
			mTargetSize = 1.0f;
		}

		//�X�s�[�h�A�b�v
		SpeedUp();

		//�A�C�e�����g��
		UseItem();

		//�A�C�e�����擾
		GetItem();
	}

	//�ꎞ��~
	Pause();
}

//�`��
void Player::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();
	pObject.GetTexture3D()->SetColor();

	//�v���C���[�̈ړ�
	mWorld = Matrix::Identity;
	mWorld *= Matrix::CreateRotationX(-1.57f);
	mWorld *= Matrix::CreateScale(mTargetSize);
	mWorld *= Matrix::CreateTranslation(mPos);

	//�v���C���[�̈ʒu�̕`��
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

//�_���[�W���󂯂�
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

//�J�����̈ړ�
void Player::CameraMove()
{
	InputManager& inputManager = InputManager::GetInstance();

	//�J�����̃Y�[��
	if (16000 > abs(inputManager.GetMouseState().scrollWheelValue))
		mCameraView.eyeY = inputManager.GetMouseState().scrollWheelValue * -0.005;
}

//Unit���X�|�[��
void Player::UnitSpawn()
{
	InputManager& inputManager = InputManager::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	if (inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
	{
		//Unit���Ăяo��
		mUnitSpawnFlag = SpawnUnit::Spawn(mPos.x, mPos.z);

		//�E�B���h�E���o�ĂȂ�������炷
		if (mUnitSpawnFlag == true)
		{
			soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		}
	}
}

//�X�N���[�����W�����[���h���W�ɕϊ�����s����쐬����֐� 
const Matrix& Player::CreateMatrix_Screen2World()
{
	CameraParam& pCm = CameraParam::GetInstance();

	Matrix viewport;

	viewport._11 = 1600 / 2.0f;

	viewport._22 = -SCREEN_H / 2.0f;

	viewport._41 = 1600 / 2.0f;

	viewport._42 = SCREEN_H / 2.0f;

	// �t�s����쐬
	Matrix invS = viewport.Invert();

	Matrix invP = pCm.GetProjection().Invert();

	Matrix invV = pCm.GetView().Invert();

	// �w�r���[�|�[�g�X�P�[�����O�s��̋t�s��x �~ �w�ˉe�s��̋t�s��x �~ �w�r���[�s��̋t�s��x
	return invS * invP * invV;
}

//�}�E�X���C�L���X�g
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

	//Capsule�̓����蔻��
	mCapsule.a = mouseStart;
	mCapsule.b = mouseEnd;

	//�X�e�[�W�̃u���b�N�ƃ}�E�X�Ƃ̓����蔻��
	mPos = mpStageDraw->ObjectCollision(mCapsule);
}

//���������̃X�e�[�W�f�[�^�̐ݒ�
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

//�{��
void Player::SpeedUp()
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	if (1400-30 <= inputManager.GetMouseState().x &&//�k��
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

//�ꎞ��~
void Player::Pause()
{
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	if (1500-30 <= inputManager.GetMouseState().x &&//�k��
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