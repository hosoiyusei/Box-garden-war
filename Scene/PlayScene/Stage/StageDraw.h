#pragma once
#include<SimpleMath.h>
#include"../Collision/Capsule.h"

//前方宣言
class StageRead;
class Object;

class StageDraw final
{
private:

	//ワールド
	DirectX::SimpleMath::Matrix mWorld;

	//ステージデータのポインタ
	StageRead* mpStageRead;
	 
	//ステージのタイル
	std::vector<
		std::vector<
		std::unique_ptr<Object>>> mpObject;

public:

	//コンストラクタ
	StageDraw();
	//デストラクタ
	~StageDraw();

	//初期化
	void Initialize(StageRead* pStageRead);

	//描画
	void Draw();

	//プレイヤーのマウスレイキャストの当たり判定
	const DirectX::SimpleMath::Vector3& ObjectCollision(const Capsule& playerCapsule);
};