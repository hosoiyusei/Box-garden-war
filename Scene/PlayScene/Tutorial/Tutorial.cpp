#include"pch.h"
#include"Tutorial.h"
#include"../Stage/StageNum.h"
#include"../DoubleSpeed/DoubleSpeed.h"

#include"../Player/StageTileData.h"
#include"../Player/Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Tutorial::Tutorial()
	:mTutorial_event_number(-1)
	, mpPlayer(nullptr)
	, mX(0)
	, mY(0)
	, mTutorial_UI_Timer(0)
{

}

//������
void Tutorial::Initialize(Player* pPlayer)
{
	mpPlayer = pPlayer;
}

//�X�V
void Tutorial::Update()
{
	StageNum& setstage = StageNum::GetInstance();
	DoubleSpeed& mpDoubleSpeed = DoubleSpeed::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();
	SoundManager& soundmanager = SoundManager::GetInstance();

	if (setstage.GetStageNum() != STAGE_NUM::TUTORIAL)return;

	const int x = inputManager.GetMouseState().x;
	const int y = inputManager.GetMouseState().y;

	++mTutorial_UI_Timer %= 60;

	if (mTutorial_event_number == -1)
	{
		mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);

		mX = 8;
		mY = 1;
	}
	else if (mTutorial_event_number == 0)
	{
		mpDoubleSpeed.SetExecutionFlag(false);

		//�X�e�[�W�f�[�^�̎擾
		STAGE_DATA tiledata = mpPlayer->GetStageData(
			static_cast<int>(mpPlayer->GetPlayerPos().x)
			, static_cast<int>(mpPlayer->GetPlayerPos().z));

		if (static_cast<int>(mpPlayer->GetPlayerPos().x) == mX &&
			static_cast<int>(mpPlayer->GetPlayerPos().z) == mY)
		{
			mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(true);
		}
		else
		{
			mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);
		}

		if (static_cast<int>(mpPlayer->GetPlayerPos().x) == mX &&
			static_cast<int>(mpPlayer->GetPlayerPos().z) == mY &&
			inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
		{
			mTutorial_event_number = 1;
			soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
		}
	}
	else if (mTutorial_event_number == 1)
	{
		mpDoubleSpeed.SetExecutionFlag(false);

		if (Determining_if_the_mouse_is_on({ 1400, 100, 1500, 200 }) == false)
		{
			mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);
		}
		else
			mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(true);

		inputManager.Reset();

		if (inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED &&
			Determining_if_the_mouse_is_on({ 1400, 100, 1500, 200 }) == true)
		{
			soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
			mTutorial_event_number = 2;
		}
	}
	else if (mTutorial_event_number == 2)
	{
		mpDoubleSpeed.SetExecutionFlag(false);
		mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);

		if(mX == static_cast<int>(mpPlayer->GetPlayerPos().x) &&
			mY == static_cast<int>(mpPlayer->GetPlayerPos().z))
		{
			mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(true);

			if (inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
			{
				mTutorial_event_number = 3;
				soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
			}
		}
	}
	else if (mTutorial_event_number == 3)
	{
		mpDoubleSpeed.SetExecutionFlag(false);
		mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);

		if (Determining_if_the_mouse_is_on({ 1400, 100, 1500, 200 }) == true)
		{
			mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(true);

			if (inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
			{
				mX = 6;
				mTutorial_event_number = 4;
				mpDoubleSpeed.SetExecutionFlag(true);
				soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
			}
		}
	}
	else if (mTutorial_event_number == 4)
	{
		mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);
	}
	else if (mTutorial_event_number == 5)
	{
		mpDoubleSpeed.SetExecutionFlag(false);
		

		if (mX == static_cast<int>(mpPlayer->GetPlayerPos().x) &&
			mY == static_cast<int>(mpPlayer->GetPlayerPos().z))
		{
			mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(true);

			if (inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
			{
				mTutorial_event_number = 6;
				soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
			}
		}
		else
		{
			mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);
		}
	}
	else if (mTutorial_event_number == 6)
	{
		mpDoubleSpeed.SetExecutionFlag(false);
		mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);

		if (mpPlayer->Stage_Target_Duplicate() == true)
		{
			if (inputManager.GetMouseState().scrollWheelValue == -120 || inputManager.GetMouseState().scrollWheelValue == 480)
			{
				if (inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
				{
					mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(true);
					mX = 9;
					mTutorial_event_number = 7;

					mpDoubleSpeed.SetExecutionFlag(true);

					soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
				}
			}
		}
	}
	else if (mTutorial_event_number == 7)
	{
		mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);
	}
	else if (mTutorial_event_number == 8)
	{
		mpDoubleSpeed.SetExecutionFlag(false);

		if (mX == static_cast<int>(mpPlayer->GetPlayerPos().x) &&
			mY == static_cast<int>(mpPlayer->GetPlayerPos().z))
		{
			mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(true);

			if (inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
			{
				soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
				mTutorial_event_number = 9;
			}
		}
		else
		{
			mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);
		}
	}
	else if (mTutorial_event_number == 9)
	{
		//���Ԓ�~
		mpDoubleSpeed.SetExecutionFlag(false);
		mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);

		//���������𖞂����Ă��邩�ǂ���
		if (mpPlayer->Stage_Target_Duplicate() == true && inputManager.GetMouseState().scrollWheelValue == -240 ||
			mpPlayer->Stage_Target_Duplicate() == true && inputManager.GetMouseState().scrollWheelValue == 360 ||
			Determining_if_the_mouse_is_on({ 1400, 300, 1500, 400 }) == true)
		{
			mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(true);

			if (inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
			{
				mX = 7;
				mTutorial_event_number = 10;
				mpDoubleSpeed.SetExecutionFlag(true);
				soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
			}
		}
	}
	else if (mTutorial_event_number == 10)
	{
		mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);
	}
	else if (mTutorial_event_number == 11)
	{
		mpDoubleSpeed.SetExecutionFlag(false);

		if (mX == static_cast<int>(mpPlayer->GetPlayerPos().x) &&
			mY == static_cast<int>(mpPlayer->GetPlayerPos().z))
		{
			mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(true);

			if (inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
			{
				soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
				mTutorial_event_number = 12;
			}
		}
		else
		{
			mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);
		}
	}
	else if (mTutorial_event_number == 12)
	{
		//���Ԓ�~
		mpDoubleSpeed.SetExecutionFlag(false);
		mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);

		//���������𖞂����Ă��邩�ǂ���
		if (mpPlayer->Stage_Target_Duplicate() == true && inputManager.GetMouseState().scrollWheelValue == -480 ||
			mpPlayer->Stage_Target_Duplicate() == true && inputManager.GetMouseState().scrollWheelValue == 120 ||
			Determining_if_the_mouse_is_on({ 1400, 500, 1500, 600 }) == true)
		{
			mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(true);

			if (inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
			{
				mX = 7; mY = 3;
				mTutorial_event_number = 13;
				mpDoubleSpeed.SetExecutionFlag(true);
				soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
			}
		}
	}
	else if (mTutorial_event_number == 13)
	{
		mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);
	}
	else if (mTutorial_event_number == 14)
	{
		mpDoubleSpeed.SetExecutionFlag(false);

		//�X�e�[�W�̍��W�w��
		if (mX == static_cast<int>(mpPlayer->GetPlayerPos().x) &&
			mY == static_cast<int>(mpPlayer->GetPlayerPos().z))
		{
			mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(true);

			if (inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
			{
				soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
				mTutorial_event_number = 15;
			}
		}
		else
		{
			mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);
		}
	}
	else if (mTutorial_event_number == 15)
	{
		//���Ԓ�~
		mpDoubleSpeed.SetExecutionFlag(false);
		mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);

		//���������𖞂����Ă��邩�ǂ���
		if (mpPlayer->Stage_Target_Duplicate() == true && inputManager.GetMouseState().scrollWheelValue == -360 ||
			mpPlayer->Stage_Target_Duplicate() == true && inputManager.GetMouseState().scrollWheelValue == 240 ||
			Determining_if_the_mouse_is_on({ 1400, 400, 1500, 500 }) == true)
		{
			mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(true);

			if (inputManager.GetButtonStateTracker()->leftButton == inputManager.GetButtonStateTracker()->PRESSED)
			{
				mTutorial_event_number = 16;
				mpDoubleSpeed.SetExecutionFlag(true);
				soundmanager.SE_Run(SOUND_SE::SE_BUTTON1, SE_RUN::PLAY);
			}
		}
	}
	else if (mTutorial_event_number == 16)
	{
		mpPlayer->SetFlag_of_whether_the_unit_can_be_put_out(false);
	}
}

//�`��
void Tutorial::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();
	StageNum& setstage = StageNum::GetInstance();

	if (setstage.GetStageNum() != STAGE_NUM::TUTORIAL)return;

	pObject.GetTexture2D()->Draw(TEXTURE2D::WINDOW, RECT{ 500,500 }, RECT{ 0,600,1300,900 }, Colors::Black*0.5f);

	Tutorial_Guide_UI2(0);
	Tutorial_Guide_UI2(2);
	Tutorial_Guide_UI2(5);
	Tutorial_Guide_UI2(6);
	Tutorial_Guide_UI2(8);
	Tutorial_Guide_UI2(11);
	Tutorial_Guide_UI2(14);
	Tutorial_Guide_UI2(15);
}

void Tutorial::Draw2()
{
	
	Play_text(L"�G������܂���", XMFLOAT2(0, 620), 0);
	Play_text(L"���j�b�g���o���Č}�����܂�", XMFLOAT2(0, 670), 0);
	Play_text(L"�X�e�[�W�̗΂̕��������N���b�N���Ă�������", XMFLOAT2(0, 720), 0);

	Play_text(L"���̃A�C�R�������N���b�N���Ă�������", XMFLOAT2(0, 620), 1);
	Tutorial_Guide_UI({ 1400, 100, 1500, 200 }, 1);

	Play_text(L"���m����������܂���", XMFLOAT2(0, 620), 2);
	Play_text(L"�����������j�b�g���N���b�N���Ă�������", XMFLOAT2(0, 670), 2);
	
	Play_text(L"���j�b�g���������Ă�������", XMFLOAT2(0, 620), 3);
	Tutorial_Guide_UI({ 1400, 100, 1500, 200 }, 3);

	Play_text(L"���m�͍U������������ꎞ�I�ɒx���ł��܂�", XMFLOAT2(0, 620), 4);

	Play_text(L"���@�g��������܂���", XMFLOAT2(0, 620), 5);
	Play_text(L"���m�ł͖��@�g���ɍU���ł��܂���", XMFLOAT2(0, 670), 5);
	Play_text(L"�X�e�[�W�̗΂̕��������N���b�N���Ă�������", XMFLOAT2(0, 720), 5);
	
	Play_text(L"���j�b�g�͂��̏�ł�����x�N���b�N���ďo�����Ƃ��o���܂�", XMFLOAT2(0, 620), 6);
	Play_text(L"�}�E�X�z�C�[��", XMFLOAT2(0, 670), 6,Colors::Red);
	Play_text(L"����]���ċ|�̃A�C�R����I����", XMFLOAT2(250, 670), 6);
	Play_text(L"���̏�ł�����x���N���b�N���Ă�������", XMFLOAT2(0, 720), 6);
	Tutorial_Guide_UI({ 1400, 200, 1500, 300 }, 6);
	
	Play_text(L"�|������������܂���", XMFLOAT2(0, 620), 7);
	Play_text(L"�|���͍U����������Ɉ�莞�Ԍp���_���[�W��^���܂�", XMFLOAT2(0, 670), 7);

	Play_text(L"�E�҂�����܂���", XMFLOAT2(0, 620), 8);
	Play_text(L"�E�҂͈��Ԋu�œ����ɂȂ�U����������Ȃ��Ȃ�܂�", XMFLOAT2(0, 670), 8);
	Play_text(L"���j�b�g�ׂ̗̗΂̕��������N���b�N���Ă�������", XMFLOAT2(0, 720), 8);
	
	Play_text(L"���j�b�g�̏e�m���������Ă�������", XMFLOAT2(0, 650), 9);
	Tutorial_Guide_UI({ 1400, 300, 1500, 400 }, 9);

	Play_text(L"�e�m�͔E�҂������ł��U���ł��܂�", XMFLOAT2(0, 620), 10);

	Play_text(L"���x��2�̕��m������܂���", XMFLOAT2(0, 620), 11);
	Play_text(L"���j�b�g�̏��R���������Ă�������", XMFLOAT2(0, 670), 11);
	
	Play_text(L"���x��2�̕��m������܂���", XMFLOAT2(0, 620), 12);
	Play_text(L"���j�b�g�̏��R���������Ă�������", XMFLOAT2(0, 670), 12);
	Tutorial_Guide_UI({ 1400, 500, 1500, 600 }, 12);

	Play_text(L"���͎��͂̃��j�b�g�̍U���͂��㏸�����܂�", XMFLOAT2(0, 620), 13);

	Play_text(L"�Z��������܂���", XMFLOAT2(0, 620), 14);
	Play_text(L"�Z���̓_���[�W���قƂ�ǎ󂯂܂���", XMFLOAT2(0, 670), 14);
	Play_text(L"�X�e�[�W�̗΂̕��������N���b�N���Ă�������", XMFLOAT2(0, 720), 14);

	Play_text(L"��C���������Ă�������", XMFLOAT2(0, 620), 15);
	Tutorial_Guide_UI({ 1400, 400, 1500, 500 }, 15);

	Play_text(L"��C�͊Z���ɑ傫�ȃ_���[�W��^���Z���͂����܂�", XMFLOAT2(0, 620), 16);
}

//�e�L�X�g�̍Đ�
void Tutorial::Play_text(const wchar_t* txt, const DirectX::XMFLOAT2& pos, const int& event_num, DirectX::FXMVECTOR& color)
{
	DrawManager& pObject = DrawManager::GetInstance();
	
	if (event_num == mTutorial_event_number)
		pObject.GetText()->TextDraw(txt, pos,color);
}

//�}�E�X������Ă��邩�̔���
const bool Tutorial::Determining_if_the_mouse_is_on(const RECT& rect)
{
	InputManager& inputManager = InputManager::GetInstance();

	int mouseX = inputManager.GetMouseState().x;
	int mouseY = inputManager.GetMouseState().y;

	int left = static_cast<int>(rect.left);
	int right = static_cast<int>(rect.right);
	int top = static_cast<int>(rect.top);
	int bottom = static_cast<int>(rect.bottom);

	if (
		left < mouseX &&
		right > mouseX &&
		top < mouseY &&
		bottom > mouseY)
	{
		return true;
	}

	return false;
}

//�}�E�X������Ă��邩�̔���
void Tutorial::Tutorial_Guide_UI(const RECT& rect, const int& event_num)
{
	if (mTutorial_UI_Timer < 30)return;

	DrawManager& pObject = DrawManager::GetInstance();

	//�摜�؂���
	RECT rect2{ 145,150 };

	if (event_num == mTutorial_event_number)
		pObject.GetTexture2D()->Draw(TEXTURE2D::TARGET, rect2, rect, Colors::Red);
}

//�`���[�g���A����UI
void Tutorial::Tutorial_Guide_UI2(const int& event_num)
{
	if (mTutorial_UI_Timer < 30)return;

	DrawManager& pObject = DrawManager::GetInstance();

	if (event_num == mTutorial_event_number)
	{
		Matrix world = Matrix::Identity;
		world *= Matrix::CreateRotationX(-1.57f);
		world *= Matrix::CreateTranslation(
			static_cast<float>(mX)
			, 0.2f
			, static_cast<float>(mY)
		);
		pObject.GetTexture3D()->SetColor(1.0f);
		pObject.GetTexture3D()->DrawShader(world, TEXTURE3D::TARGET);
	}
}