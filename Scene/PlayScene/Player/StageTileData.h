#pragma once
#include"../UnitManager/Unit/UnitLevel.h"

enum class TILE_DATA :int
{
	Wall,
	Road,
	Unit_Scaffolding,
	Goal,
	EnemyStart,

	Swordfighter,

	Archer,

	Gunner,

	Cannon,

	Wizard,

	Shogun,

	NONE,
};

//プレイヤーが持つステージのデータ
struct STAGE_DATA
{
	TILE_DATA tileData;

	UNIT_LEVEL unit_Level;
};