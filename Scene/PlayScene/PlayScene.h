#pragma once
#include"Scene/IScene.h"
#include"Scene/Utility.h"
#include<SimpleMath.h>

//�O���錾
class StageRead;
class StageDraw;
class EnemyManager;
class Player;
class UnitManager;
class BulletManager;
class EffectManager;
class CollisionManager;
class GameUI;
class ItemManager;

class PlayScene:public IScene
{
private:

	//�J�����̃p�����[�^�[
	VIEW mCameraView;

	//�^�C�}�[
	DX::StepTimer mTimer;

	//���[���h
	DirectX::SimpleMath::Matrix mWorld;

	int mResultTimer;

	bool mInitialFlag;

	float mFade;

	bool mFadeFlag;

	float mResultEffect;

	//�X�e�[�W�f�[�^�̃|�C���^
	std::unique_ptr<StageRead> mpStageRead;
	//�X�e�[�W��`�悷��|�C���^
	std::unique_ptr<StageDraw> mpStageDraw;
	//Enemy�̊Ǘ��҂̃|�C���^
	std::unique_ptr<EnemyManager> mpEnemyManager;
	//�v���C���[�̃|�C���^
	std::unique_ptr<Player> mpPlayer;
	//Unit�̊Ǘ��҂��|�C���^
	std::unique_ptr<UnitManager> mpUnitManager;
	//�e�̊Ǘ��҂̃|�C���^
	std::unique_ptr<BulletManager> mpBulletManager;
	//�G�t�F�N�g�̊Ǘ��҂̃|�C���^
	std::unique_ptr<EffectManager> mpEffectManager;
	//�����蔻��̊Ǘ��҂̃|�C���^
	std::unique_ptr<CollisionManager> mpCollisionManager;

	std::unique_ptr<GameUI> mpGameUI;

	//�A�C�e���̊Ǘ��҂̃|�C���^
	std::unique_ptr<ItemManager> mpItemManager;

public:

	//�R���X�g���N�^
	PlayScene();
	//�f�X�g���N�^
	~PlayScene();

	//������
	void Initialize() override;

	//�X�V
	GAME_SCENE Update(const DX::StepTimer& timer) override;

	//�`��
	void Draw() override;
	void Draw2()override;

	void Forward()override;

	//�I������
	void Finalize() override;
};