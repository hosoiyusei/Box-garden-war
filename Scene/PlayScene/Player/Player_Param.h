#pragma once

struct Player_Param
{
	//カメラの位置調整
	const float mCamera_position_adjustment;

	//カメラを少しずらす
	const float mDisplace_camera_little;

	//カメラのターゲット
	const float mCamera_Target;

	//ゲームのスピード
	const float mGame_Speed;

	//Targetの大きさの収縮
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