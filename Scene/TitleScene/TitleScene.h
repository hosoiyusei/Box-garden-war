#pragma once
#include"Scene/IScene.h"
#include"Scene/Utility.h"

//�O���錾
class TitleUI;

class TitleScene:public IScene
{
private:

	VIEW mCameraView;

	std::unique_ptr<TitleUI> mpTitleUI;

	bool mInitialFlag;

public:

	//�R���X�g���N�^
	TitleScene();
	//�f�X�g���N�^
	~TitleScene();

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