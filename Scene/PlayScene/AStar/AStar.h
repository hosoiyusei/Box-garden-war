#pragma once
#include<map>
#include<vector>
#include"../../Utility.h"
#include<SimpleMath.h>

//前方宣言
class StageRead;

typedef struct
{
	int x;
	int y;
	int px;
	int py;
	int cost;
} anode;

class AStar
{
private:

	std::map <int, anode> mapOpen;
	std::map <int, anode> mapClose;

	//スタートとゴールの位置
	Int2 mGoal, mStart, mPos;

	//目的地
	Int2 mDestination;

	//ステージデータ
	std::vector<std::vector<int>> ndata, ndata_2;

	//ステージの立幅と横幅
	int mHorizontal, mVertical;

public:

	//コンストラクタ
	AStar();
	//デストラクタ
	~AStar();

	//初期化
	void Initialize(StageRead* pStageRead);

	const float& Move();

	//A*実行
	const DirectX::SimpleMath::Vector3& _tmain(const int& startnum);

	//座標の取得
	const Int2& GetPos() { return mPos; }

	//ゴールについたかの確認
	const bool& CheckGoal();

private:

	//スターとのセット
	void SetStart(const int& startnum);
	
	// マンハッタン距離を斜め移動ありを考慮して求める
	const int& GetDistance(
		const int& from_x
		, const int& from_y
		, const int& to_x
		,const  int& to_y);

	// ノード情報を一度にセットする
	const anode* SetNode(
		anode* n
		, const int& nx
		, const int& ny
		, const int& npx
		, const int& npy
		, const int& ncost);

	// 指定した地点からスタート地点までの距離を求める
	const int& BackTrace(
		const int& x
		, const int& y);

	// A*で経路探査する
	const int& Search(const int& count);

	// 最短ルートをマップデータに書き出す
	void TraceRoute(const int& x, const int& y);
};