#pragma once

struct Shogun_Param
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

	//王冠の大きさの大きさ
	const float mCrown_sizeｍ;

	//王冠の座標
	const DirectX::SimpleMath::Vector3 mCrown_coordinate;

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

	//通常の時の左手の座標
	const DirectX::SimpleMath::Vector3 mNormal_when_left_hand_coordinate;

	//通常の時の左手の座標
	const DirectX::SimpleMath::Vector3 mNormal_when_right_hand_coordinate;

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


	Shogun_Param()
		:mBlinkinginterval(2)
		, mShift_the_coordinates_of_the_effect(0.3f)
		, mNumber_of_effects_generated(10)
		, mTorso_size(0.8f)
		, mHead_size(0.5f)
		, mHead_coordinates(0.0f, 0.5f, 0.0f)
		, mRight_hand_size(0.3f)
		, mLeft_hand_size(0.3f)
		, mCrown_sizeｍ(0.0022f)
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

	//攻撃間隔ゲージの描画
	const DirectX::SimpleMath::Vector3& Attack_interval_gauge_position(const DirectX::SimpleMath::Vector3& pos)
	{
		return DirectX::SimpleMath::Vector3(pos.x, pos.y + 0.7f, pos.z - 0.2f);
	}

	//攻撃間隔ゲージの大きさ
	const DirectX::SimpleMath::Vector3& Attack_interval_gauge_size(const float& length)
	{
		return DirectX::SimpleMath::Vector3(length, 0.1f, 0.1f);
	}

	//パワーアップエフェクトの座標
	const DirectX::SimpleMath::Vector3 Effect_coordinate(const DirectX::SimpleMath::Vector3 pos)
	{
		return  DirectX::SimpleMath::Vector3(pos.x, pos.y - 0.5f, pos.z);
	}


};