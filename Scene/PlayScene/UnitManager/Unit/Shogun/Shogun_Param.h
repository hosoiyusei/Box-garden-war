#pragma once

struct Shogun_Param
{

#pragma region constant

	//�����蔻��̑傫��
	const float mHit_test_size;

	//�������̓_�ł̊Ԋu
	const int mBlinkinginterval;

	//�G�t�F�N�g�̍��W����
	const float mShift_the_coordinates_of_the_effect;

	//�G�t�F�N�g�̔�����
	const int mNumber_of_effects_generated;

	//���̂̑傫��
	const float mTorso_size;

	//���̑傫��
	const float mHead_size;

	//���̍��W
	const DirectX::SimpleMath::Vector3 mHead_coordinates;

	//�E��̑傫��
	const float mRight_hand_size;

	//����̑傫��
	const float mLeft_hand_size;

	//�����̑傫���̑傫��
	const float mCrown_size��;

	//�����̍��W
	const DirectX::SimpleMath::Vector3 mCrown_coordinate;

	//�p���[�A�b�v�G�t�F�N�g�^�C�}�[
	const int mPower_up_effect_timer;

	//�p���[�A�b�v�G�t�F�N�g�̐F�̐ݒ�
	const DirectX::SimpleMath::Vector3 mEffect_color_preference;

	//�p���[�A�b�v�G�t�F�N�g�̔�����
	const int mEffect_generation_number;

	//�p���[�A�b�v�G�t�F�N�g�̑���
	const float mPower_up_effect_speed;

	//�p���[�A�b�v�G�t�F�N�g�̑傫��
	const float mPower_up_effect_size;

	//�ʏ�̎��̍���̍��W
	const DirectX::SimpleMath::Vector3 mNormal_when_left_hand_coordinate;

	//�ʏ�̎��̍���̍��W
	const DirectX::SimpleMath::Vector3 mNormal_when_right_hand_coordinate;

	//���x���A�b�v�ɂ����鎞��
	const int mLevelUpTime_Level_2;
	const int mLevelUpTime_Level_3;
	const int mLevelUpTime_Level_4;
	const int mLevelUpTime_Level_5;

	//�U�����[�V�����̃^�C�}�[���[���̎�
	const int mAttack_motion_timer_zero_time;

	//�U���͂̐ݒ�
	const int mAttack_power_when_level_1;
	const int mAttack_power_when_level_2;
	const int mAttack_power_when_level_3;
	const int mAttack_power_when_level_4;
	const int mAttack_power_when_level_5;

	//�p���[�A�b�v�ŏ㏸����U����
	const int mAttack_power_ascend_in_power_up_1;
	const int mAttack_power_ascend_in_power_up_2;
	const int mAttack_power_ascend_in_power_up_3;
	const int mAttack_power_ascend_in_power_up_4;
	const int mAttack_power_ascend_in_power_up_5;

#pragma endregion


	Shogun_Param()
		:mBlinkinginterval(2)
		, mShift_the_coordinates_of_the_effect(0.3f)
		, mNumber_of_effects_generated(10)
		, mTorso_size(0.8f)
		, mHead_size(0.5f)
		, mHead_coordinates(0.0f, 0.5f, 0.0f)
		, mRight_hand_size(0.3f)
		, mLeft_hand_size(0.3f)
		, mCrown_size��(0.0022f)
		, mPower_up_effect_timer(60)
		, mEffect_color_preference(0.0f, 1.0f, 0.0f)
		, mEffect_generation_number(1)
		, mPower_up_effect_speed(0.05f)
		, mPower_up_effect_size(1.0f)
		, mNormal_when_left_hand_coordinate(0.5f, 0.3f, 0.0f)
		, mNormal_when_right_hand_coordinate(-0.5f, 0.3f, -0.0f)
		, mLevelUpTime_Level_2(120)
		, mLevelUpTime_Level_3(240)
		, mLevelUpTime_Level_4(360)
		, mLevelUpTime_Level_5(480)
		, mAttack_motion_timer_zero_time(0)
		, mAttack_power_when_level_1(2)
		, mAttack_power_when_level_2(4)
		, mAttack_power_when_level_3(6)
		, mAttack_power_when_level_4(8)
		, mAttack_power_when_level_5(10)
		, mAttack_power_ascend_in_power_up_1(1)
		, mAttack_power_ascend_in_power_up_2(2)
		, mAttack_power_ascend_in_power_up_3(3)
		, mAttack_power_ascend_in_power_up_4(4)
		, mAttack_power_ascend_in_power_up_5(5)
		, mHit_test_size(1.3f)
		, mCrown_coordinate(0.0f, 0.88f, 0.0f)
	{

	}

	//�U���Ԋu�Q�[�W�̕`��
	const DirectX::SimpleMath::Vector3& Attack_interval_gauge_position(const DirectX::SimpleMath::Vector3& pos)
	{
		return DirectX::SimpleMath::Vector3(pos.x, pos.y + 0.7f, pos.z - 0.2f);
	}

	//�U���Ԋu�Q�[�W�̑傫��
	const DirectX::SimpleMath::Vector3& Attack_interval_gauge_size(const float& length)
	{
		return DirectX::SimpleMath::Vector3(length, 0.1f, 0.1f);
	}

	//�p���[�A�b�v�G�t�F�N�g�̍��W
	const DirectX::SimpleMath::Vector3 Effect_coordinate(const DirectX::SimpleMath::Vector3 pos)
	{
		return  DirectX::SimpleMath::Vector3(pos.x, pos.y - 0.5f, pos.z);
	}


};