#pragma once

struct Gunner_Param
{
	
#pragma region constant

	//当たり判定の大きさ
	const float mHit_test_size;

		//強化時の点滅の間隔
		const int mBlinkinginterval;

		//エフェクトの座標調整
		const float mShift_the_coordinates_of_the_effect;

		//エフェクトの発生数
		const int mNumber_of_effects_generated;

		//胴体の大きさ
		const float mTorso_size;

		//頭の大きさ
		const float mHead_size;

		//頭の座標
		const DirectX::SimpleMath::Vector3 mHead_coordinates;

		//右手の大きさ
		const float mRight_hand_size;

		//左手の大きさ
		const float mLeft_hand_size;

		//銃の大きさ
		const float mGun_size;

		//攻撃間隔のゲージの描画
		const float mAttack_interval_gauge_drawing;

		//攻撃間隔ゲージの色
		const float mAttack_interval_gauge_color;

		//パワーアップエフェクトタイマー
		const int mPower_up_effect_timer;

		//パワーアップエフェクトの色の設定
		const DirectX::SimpleMath::Vector3 mEffect_color_preference;

		//パワーアップエフェクトの発生数
		const int mEffect_generation_number;

		//パワーアップエフェクトの速さ
		const float mPower_up_effect_speed;

		//パワーアップエフェクトの大きさ
		const float mPower_up_effect_size;

		//攻撃間隔
		const int mAttack_interval;

		//攻撃範囲
		const float mAttack_range;

		//ゼロになった瞬間に攻撃する
		const int mZero_got_moment_attack;

		//通常の時の左手の座標
		const DirectX::SimpleMath::Vector3 mNormal_when_left_hand_coordinate;

		//通常の時の左手の座標
		const DirectX::SimpleMath::Vector3 mNormal_when_right_hand_coordinate;

		//銃のY軸回転角の初期角
		const float mGun_y_axis_rotation_angle_initial_angle;

		//銃のX軸回転角の初期角
		const float mGun_x_axis_rotation_angle_initial_angle;

		//銃のZ軸回転角の初期角
		const float mGun_z_axis_rotation_angle_initial_angle;

		//攻撃開始時の左手の座標
		const DirectX::SimpleMath::Vector3 mLeft_hand_coordinate_at_attack_start;

		//攻撃開始時の右手の座標
		const DirectX::SimpleMath::Vector3 mRight_hand_coordinate_at_attack_start;

		//攻撃開始時の銃のY軸の初期回転角
		const float mAttack_start_when_gun_y_axis_initial_rotation_angle;

		//攻撃開始時の銃のX軸の初期回転角
		const float mAttack_start_when_gun_x_axis_initial_rotation_angle;

		//攻撃のアニメーションの時間
		const int mAttack_animation_time;

		//呼応激時の左手の移動
		const DirectX::SimpleMath::Vector3 mLeft_hand_move_at_attack;

		//攻撃時の銃のZ軸の回転
		const float mAttack_when_gun_z_axis_rotation;

		//レベルアップにかかる時間
		const int mLevelUpTime_Level_2;
		const int mLevelUpTime_Level_3;
		const int mLevelUpTime_Level_4;
		const int mLevelUpTime_Level_5;

		//攻撃モーションのタイマーがゼロの時
		const int mAttack_motion_timer_zero_time;

		//攻撃力の設定
		const int mAttack_power_when_level_1;
		const int mAttack_power_when_level_2;
		const int mAttack_power_when_level_3;
		const int mAttack_power_when_level_4;
		const int mAttack_power_when_level_5;

		//パワーアップで上昇する攻撃力
		const int mAttack_power_ascend_in_power_up_1;
		const int mAttack_power_ascend_in_power_up_2;
		const int mAttack_power_ascend_in_power_up_3;
		const int mAttack_power_ascend_in_power_up_4;
		const int mAttack_power_ascend_in_power_up_5;

#pragma endregion
	

		Gunner_Param()
			:mHit_test_size(0.5f)
			, mBlinkinginterval(2)
			, mShift_the_coordinates_of_the_effect(0.3f)
			, mNumber_of_effects_generated(10)
			, mTorso_size(0.8f)
			, mHead_size(0.5f)
			, mHead_coordinates(0.0f, 0.5f, 0.0f)
			, mRight_hand_size(0.3f)
			, mLeft_hand_size(0.3f)
			, mGun_size(0.45f)
			, mAttack_interval_gauge_drawing(0.8f)
			, mAttack_interval_gauge_color(1.0f)
			, mPower_up_effect_timer(60)
			, mEffect_color_preference(0.0f, 1.0f, 0.0f)
			, mEffect_generation_number(1)
			, mPower_up_effect_speed(0.05f)
			, mPower_up_effect_size(1.0f)
			, mAttack_interval(120)
			, mAttack_range(3.2f)
			, mZero_got_moment_attack(0)
			, mNormal_when_left_hand_coordinate(-0.3f, -0.1f, 0.5f)
			, mNormal_when_right_hand_coordinate(-0.3f, -0.3f, -0.3f)
			, mGun_y_axis_rotation_angle_initial_angle(3.14f)
			, mGun_x_axis_rotation_angle_initial_angle(-0.3f)
			, mGun_z_axis_rotation_angle_initial_angle(0.0f)
			, mLeft_hand_coordinate_at_attack_start(-0.7f, 0.0f, -0.2f)
			, mRight_hand_coordinate_at_attack_start(0.0f, 0.0f, -0.2f)
			, mAttack_start_when_gun_y_axis_initial_rotation_angle(1.57f)
			, mAttack_start_when_gun_x_axis_initial_rotation_angle(0.0f)
			, mAttack_animation_time(15)
			, mLeft_hand_move_at_attack(0.0f, 0.015f, 0.0f)
			, mAttack_when_gun_z_axis_rotation(0.02f)
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
			, mAttack_power_ascend_in_power_up_1(2)
			, mAttack_power_ascend_in_power_up_2(4)
			, mAttack_power_ascend_in_power_up_3(6)
			, mAttack_power_ascend_in_power_up_4(8)
			, mAttack_power_ascend_in_power_up_5(10)
	{

	}

	//攻撃間隔ゲージの描画
	const DirectX::SimpleMath::Vector3 Attack_interval_gauge_position(const DirectX::SimpleMath::Vector3& pos)
	{
		return DirectX::SimpleMath::Vector3(pos.x, pos.y + 0.7f, pos.z - 0.2f);
	}

	//攻撃間隔ゲージの大きさ
	const DirectX::SimpleMath::Vector3 Attack_interval_gauge_size(const float& length)
	{
		return DirectX::SimpleMath::Vector3(length, 0.1f, 0.1f);
	}

	//パワーアップエフェクトの座標
	const DirectX::SimpleMath::Vector3 Effect_coordinate(const DirectX::SimpleMath::Vector3 pos)
	{
		return  DirectX::SimpleMath::Vector3(pos.x, pos.y - 0.5f, pos.z);
	}

	
};