#pragma once

//オブジェクトの種類
enum class OBJECT_TYPE :int
{
	ROAD,
	WALL,
	PLACEMENT_SPACE,
	ENEMY_GOAL,
	ENEMY_START,

	NONE,
};