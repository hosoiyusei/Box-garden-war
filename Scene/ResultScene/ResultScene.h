#pragma once
#include"Scene/IScene.h"
#include"Scene/Utility.h"

class Button;

class ResultScene :public IScene
{
private:

	float mSceneFade;

	VIEW mCameraView;

	std::map<std::string, std::unique_ptr<Button>> mpButtons;

public:

	//�R���X�g���N�^
	ResultScene();
	//�f�X�g���N�^
	~ResultScene();

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