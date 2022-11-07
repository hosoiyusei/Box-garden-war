#pragma once
#include<SimpleMath.h>
#include<vector>
#include"Scene/Utility.h"
#include"../Collision/Capsule.h"
#include"SpawnUnit.h"
#include"StageTileData.h"
#include"../UnitManager/Unit/UnitLevel.h"
#include"../ItemManager/Item/ItemType.h"
#include"Player_Param.h"

//�O���錾
class StageRead;
class UnitManager;
class StageDraw;
class ItemManager;
class GameUI;

class Player :private SpawnUnit
{
private:

	//�J�����̃p�����[�^�[
	VIEW mCameraView, mCameraView2;

	//�v���C���[�̍��W
	DirectX::SimpleMath::Vector3 mPos;
	DirectX::SimpleMath::Vector3 mGoalPos;

	DirectX::SimpleMath::Vector3 mSecondTarget;

	//���[���h
	DirectX::SimpleMath::Matrix mWorld;

	//�v���C���[�̃X�e�[�W�f�[�^
	std::vector<std::vector<STAGE_DATA>> mStageData;

	//�X�e�[�W��Capsule�Ƃ̓����蔻��
	Capsule mCapsule;

	//�X�e�[�W�̗����Ɖ���
	int mHorizontal, mVertical;

	//�v���C���[�̗̑�
	int mLife;

	//��
	int mMoney;

	//�N���A�t���O
	bool mClear;

	//�Q�[���I�[�o�[�t���O
	bool mGameOver;

	//Unit�Ăяo���t���O
	bool mUnitSpawnFlag;

	//�J�����𓮂����Ă��邩�ǂ����̃t���O
	bool mCameraMoveFlag;

	//�^�[�Q�b�g�̑傫��
	float mTargetSize;

	//���j�b�g���o�����Ƃ��o���邩�ǂ����̃t���O
	bool mFlag_of_whether_the_unit_can_be_put_out;

	//�����邩��
	int mScrollMoney;

	ITEM_TYPE mItemType;

	//���j�b�g�̊Ǘ��҂̃|�C���^
	UnitManager* mpUnitManager;

	//�X�e�[�W�`��̃|�C���^
	StageDraw* mpStageDraw;

	ItemManager* mpItemManager;

	Player_Param mParam;

	//�_��
	float mBlinking;

	GameUI* mpGameUI;

public:

	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();

	//������
	void Initialize(
		StageRead* pStageRead
		, UnitManager* pUnitManager
		, StageDraw* pStageDraw
		, Player* pPlayer
		, ItemManager* pItemManager
		, GameUI* pGameUI);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�_���[�W���󂯂�
	void LifeDamage();

	//�N���A�t���O���󂯎��
	void SetClear(const bool& clear) { mClear = clear; }

	//�N���A�t���O��Ԃ�
	const bool GetClear() { return mClear; }

	//�Q�[���I�[�o�[�̃t���O��Ԃ�
	const bool GetGameOver() { return mGameOver; }

	//�J�����̃p�����[�^�[��Ԃ�
	const VIEW GetCameraParam() { return mCameraView; }

	//���𑝂₷
	void SetMoney(const int money);

	//���̎擾
	const int GetMoney() { return mScrollMoney; }

	//Unit�̑I���t���O��Ԃ�
	const bool GetUnitSelectFlag(){return SpawnUnit::GetUnitSelectFlag();}

	//Unit�̋����t���O��Ԃ�
	const bool GetReinforcementFlag(){return SpawnUnit::GetReinforcementFlag();}

	//�X�e�[�W�̃f�[�^�̏�������
	void SetTileNum(
		const int& x
		, const int& y
		, const TILE_DATA& newTileData
		, const UNIT_LEVEL& newLevelData)
	{
		mStageData[y][x].tileData = newTileData; 
		mStageData[y][x].unit_Level = newLevelData;
	}

	//�X�e�[�W�̔z��̔ԍ���Ԃ�
	const STAGE_DATA GetStageData(const int& x, const int& y) { return mStageData[y][x]; }

	const DirectX::SimpleMath::Vector3 GetPlayerPos() { return mPos; }

	//�A�C�e�����Z�b�g
	void SetItem(const ITEM_TYPE& type) { mItemType = type; }

	//�v���C���[�̎��A�C�e��
	const ITEM_TYPE GetPlayerItem() { return mItemType; }

	//Target���d�Ȃ��Ă���Ƃ�
	const bool Stage_Target_Duplicate();

	void SetFlag_of_whether_the_unit_can_be_put_out(const bool& set) { mFlag_of_whether_the_unit_can_be_put_out = set; }

	const int GetPlayerLife() { return mLife; }

	const bool Get_Unit_Spawn_Flag() { return mUnitSpawnFlag; }

private:

	//�v���C���[�̈ړ�
	void CameraMove();

	//Unit���X�|�[��
	void UnitSpawn();

	//�X�N���[�����W�����[���h���W�ɕϊ�����s����쐬����֐� 
	const DirectX::SimpleMath::Matrix CreateMatrix_Screen2World();

	//�}�E�X���C�L���X�g
	void MouseRayCast();

	//���������̃X�e�[�W�f�[�^�̐ݒ�
	const TILE_DATA SetStageData(const int& datanum);

	//�{��
	void SpeedUp();

	//�ꎞ��~
	void Pause();

	void GetItem();

	void UseItem();

	//�X�e�[�W�Ƃ̌�_�����߂�
	const DirectX::SimpleMath::Vector3 IntersectPlaneAndLine(
		const DirectX::SimpleMath::Vector3&  A,   //�����n�_
		const DirectX::SimpleMath::Vector3&  B,   //�����I�_
		const DirectX::SimpleMath::Plane&     PL); //����

	//���j�b�g�̍U���͈͂̕`��
	void Drawing_the_attack_range_of_the_unit();
};