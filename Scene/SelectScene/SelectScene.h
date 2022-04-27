#pragma once
#include"Scene/IScene.h"
#include"Scene/Utility.h"

class SelectUI;

class SelectScene :public IScene
{
private:

	VIEW mCameraView;

	//���[�h����X�e�[�W�̔ԍ�
	int mStageNum;

	std::unique_ptr<SelectUI> mpSelectUI;

	float mSceneFade;

	bool mMoveFadeFlag;

public:

	//�R���X�g���N�^
	SelectScene();
	//�f�X�g���N�^
	~SelectScene();

	//������
	void Initialize() override;

	//�X�V
	GAME_SCENE Update(const DX::StepTimer& timer) override;

	//�`��
	void Draw() override;
	void Draw2()override {};

	void Forward()override {};

	//�I������
	void Finalize() override;

};