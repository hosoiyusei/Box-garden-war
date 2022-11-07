#pragma once

class Player;

class Tutorial
{
private:

	//�`���[�g���A���̃C�x���g�̔ԍ�
	int mTutorial_event_number;

	//�ꎞ�ۑ��p�X�e�[�W���W
	int mX, mY;

	int mTutorial_UI_Timer;

	Player* mpPlayer;

public:

	Tutorial();
	~Tutorial() = default;

	//������
	void Initialize(Player* pPlayer);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�`��2
	void Draw2();

	//�C�x���g�̔ԍ�
	const int GetmTutorial_event_number() { return mTutorial_event_number; }

	//�C�x���g�̔ԍ��̃Z�b�g
	void SetmTutorial_event_number(const int& eventnum) { mTutorial_event_number = eventnum; }

private:

	//�e�L�X�g�̍Đ�
	void Play_text(
		const wchar_t* txt
		, const DirectX::XMFLOAT2& pos
		, const int& event_num
		, DirectX::FXMVECTOR& color = DirectX::Colors::White);

	//�}�E�X���͈͓��ɂ��邩�̔���
	const bool Determining_if_the_mouse_is_on(const RECT& rect);

	//�`���[�g���A����UI
	void Tutorial_Guide_UI(const RECT& rect, const int& event_num);

	//�`���[�g���A����UI
	void Tutorial_Guide_UI2(const int& event_num);
};