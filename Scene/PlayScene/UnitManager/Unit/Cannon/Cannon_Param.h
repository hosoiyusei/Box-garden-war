#pragma once

struct Cannon_Param
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

	//砲身の大きさ
	const DirectX::SimpleMath::Vector3 mGun_tube_size;

	//砲身のX軸の回転
	const float mGun_tube_x_axis_rotation;

	//砲身のY軸の回転
	const float mGun_tube_y_axis_rotation;

	//砲身の座標の調整
	const float mGun_tube_coordinate_adjustment;

	//銃口の座標
	const DirectX::SimpleMath::Vector3 mMuzzle_size;

	//銃口のY軸の回転
	const float mMuzzle_y_axis_rotation;

	//銃口の座標
	const DirectX::SimpleMath::Vector3 mMuzzle_coordinate;

	//車輪の大きさ
	const DirectX::SimpleMath::Vector3 mWheel_size;

	//車輪のY軸の回転角
	const float mWheel_y_axis_rotation_angle;

	//車輪のZ軸の回転角
	const float mWheel_z_axis_rotation_angle;

	//左車輪の座標
	const DirectX::SimpleMath::Vector3 mLeft_wheel_coordinate;

	//右車輪の座標
	const DirectX::SimpleMath::Vector3 mRight_wheel_coordinate;

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


	Cannon_Param()
		:mHit_test_size(0.5f)
		, mBlinkinginterval(2)
		, mShift_the_coordinates_of_the_effect(0.3f)
		, mNumber_of_effects_generated(10)
		, mGun_tube_size(0.4f, 0.7f, 0.4f)
		, mAttack_interval_gauge_drawing(0.8f)
		, mAttack_interval_gauge_color(1.0f)
		, mPower_up_effect_timer(60)
		, mEffect_color_preference(0.0f, 1.0f, 0.0f)
		, mEffect_generation_number(1)
		, mPower_up_effect_speed(0.05f)
		, mPower_up_effect_size(1.0f)
		, mAttack_interval(400)
		, mAttack_range(5.0f)
		, mZero_got_moment_attack(0)
		, mLevelUpTime_Level_2(120)
		, mLevelUpTime_Level_3(240)
		, mLevelUpTime_Level_4(360)
		, mLevelUpTime_Level_5(480)
		, mAttack_motion_timer_zero_time(0)
		, mAttack_power_when_level_1(6)
		, mAttack_power_when_level_2(12)
		, mAttack_power_when_level_3(18)
		, mAttack_power_when_level_4(24)
		, mAttack_power_when_level_5(30)
		, mAttack_power_ascend_in_power_up_1(2)
		, mAttack_power_ascend_in_power_up_2(4)
		, mAttack_power_ascend_in_power_up_3(6)
		, mAttack_power_ascend_in_power_up_4(8)
		, mAttack_power_ascend_in_power_up_5(10)
		, mGun_tube_x_axis_rotation(1.57f)
		, mGun_tube_y_axis_rotation(1.57f)
		, mMuzzle_size(1.0f, 0.7f, 1.0f)
		, mGun_tube_coordinate_adjustment(-0.6f)
		, mMuzzle_y_axis_rotation(1.57f)
		, mWheel_size(0.6f, 1.3f, 0.6f)
		, mWheel_y_axis_rotation_angle(1.57f)
		, mWheel_z_axis_rotation_angle(1.57f)
		, mLeft_wheel_coordinate(0.7f, 0.2f, 0.0f)
		, mRight_wheel_coordinate(-0.7f, 0.2f, 0.0f)
		, mMuzzle_coordinate(0.0f, -0.5f, 0.0f)
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