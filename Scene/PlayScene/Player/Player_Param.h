#pragma once

struct Player_Param
{
	//�J�����̈ʒu����
	const float mCamera_position_adjustment;

	//�J�������������炷
	const float mDisplace_camera_little;

	//�J�����̃^�[�Q�b�g
	const float mCamera_Target;

	//�Q�[���̃X�s�[�h
	const float mGame_Speed;

	//Target�̑傫���̎��k
	const float mTarget_Size;

	Player_Param()
		: mCamera_position_adjustment(0.5f)
		, mDisplace_camera_little(0.1f)
		, mCamera_Target(0.0f)
		, mGame_Speed(1.0f)
		, mTarget_Size(0.005f)
	{

	}
};