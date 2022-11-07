#pragma once

struct Archer_Param
{

#pragma region constant

	//�U���Ԋu�Q�[�W�̒����̒���
	const float mAttack_interval_gauge_length_adjustment;

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

	//�|�̑傫��
	const float mBow_size;

	//�U���Ԋu�̃Q�[�W�̕`��
	const float mAttack_interval_gauge_drawing;

	//�U���Ԋu�Q�[�W�̐F
	const float mAttack_interval_gauge_color;

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

	//�U���Ԋu
	const int mAttack_interval;

	//�U���͈�
	const float mAttack_range;

	//�[���ɂȂ����u�ԂɍU������
	const int mZero_got_moment_attack;

	//�ʏ�̎��̍���̍��W
	const DirectX::SimpleMath::Vector3 mNormal_when_left_hand_coordinate;

	//�ʏ�̎��̍���̍��W
	const DirectX::SimpleMath::Vector3 mNormal_when_right_hand_coordinate;

	//�ʏ펞�̋|�̉�]
	const float mMrotation_in_normal_bow;

	//�U���J�n���̍���̍��W
	const DirectX::SimpleMath::Vector3 mLeft_hand_coordinate_at_attack_start;

	//�U���J�n���̉E��̍��W
	const DirectX::SimpleMath::Vector3 mRight_hand_coordinate_at_attack_start;

	//�U���̃A�j���[�V�����̎���
	const int mAttack_animation_time;

	//�U�����̋|�̉�]
	const float mBow_rotation_at_attack;

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


	Archer_Param()
		:mHit_test_size(0.5f)
		, mBlinkinginterval(2)
		, mShift_the_coordinates_of_the_effect(0.3f)
		, mNumber_of_effects_generated(10)
		, mTorso_size(0.8f)
		, mHead_size(0.5f)
		, mHead_coordinates(0.0f, 0.5f, 0.0f)
		, mRight_hand_size(0.3f)
		, mLeft_hand_size(0.3f)
		, mBow_size(0.08f)
		, mAttack_interval_gauge_drawing(0.8f)
		, mAttack_interval_gauge_color(1.0f)
		, mPower_up_effect_timer(60)
		, mEffect_color_preference(0.0f, 1.0f, 0.0f)
		, mEffect_generation_number(1)
		, mPower_up_effect_speed(0.05f)
		, mPower_up_effect_size(1.0f)
		, mAttack_interval(120)
		, mAttack_range(2.2f)
		, mZero_got_moment_attack(0)
		, mNormal_when_left_hand_coordinate(0.0f, 0.3f, 0.5f)
		, mNormal_when_right_hand_coordinate(0.0f, 0.3f, -0.5f)
		, mMrotation_in_normal_bow(3.14f)
		, mLeft_hand_coordinate_at_attack_start(0.35f, 0.3f, 0.35f)
		, mRight_hand_coordinate_at_attack_start(-0.5f, 0.3f, 0.2f)
		, mAttack_animation_time(15)
		, mBow_rotation_at_attack(2.8f)
		, mLevelUpTime_Level_2(60)
		, mLevelUpTime_Level_3(120)
		, mLevelUpTime_Level_4(180)
		, mLevelUpTime_Level_5(240)
		, mAttack_motion_timer_zero_time(0)
		, mAttack_power_when_level_1(1)
		, mAttack_power_when_level_2(2)
		, mAttack_power_when_level_3(3)
		, mAttack_power_when_level_4(4)
		, mAttack_power_when_level_5(5)
		, mAttack_power_ascend_in_power_up_1(2)
		, mAttack_power_ascend_in_power_up_2(4)
		, mAttack_power_ascend_in_power_up_3(6)
		, mAttack_power_ascend_in_power_up_4(8)
		, mAttack_power_ascend_in_power_up_5(10)
		, mAttack_interval_gauge_length_adjustment(0.8f)
	{

	}

	//�U���Ԋu�Q�[�W�̕`��
	const DirectX::SimpleMath::Vector3 Attack_interval_gauge_position(const DirectX::SimpleMath::Vector3& pos)
	{
		return DirectX::SimpleMath::Vector3(pos.x, pos.y + 0.7f, pos.z - 0.2f);
	}

	//�U���Ԋu�Q�[�W�̑傫��
	const DirectX::SimpleMath::Vector3 Attack_interval_gauge_size(const float& length)
	{
		return DirectX::SimpleMath::Vector3(length, 0.1f, 0.1f);
	}

	//�p���[�A�b�v�G�t�F�N�g�̍��W
	const DirectX::SimpleMath::Vector3 Effect_coordinate(const DirectX::SimpleMath::Vector3 pos)
	{
		return  DirectX::SimpleMath::Vector3(pos.x, pos.y - 0.5f, pos.z);
	}


};