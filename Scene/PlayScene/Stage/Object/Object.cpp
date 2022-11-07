#include"pch.h"
#include"Object.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ
Object::Object()
	: mPos()
	, mType(OBJECT_TYPE::NONE)
	, mWorld()
{

}

//デストラクタ
Object::~Object()
{

}

//初期化
void Object::Initialize(int stagetilenum)
{
	if (stagetilenum == 0)
	{
		//敵の通り道
		mType = OBJECT_TYPE::ROAD;
	}
	else if (stagetilenum == 1)
	{
		//壁
		mType = OBJECT_TYPE::WALL;
	}
	else if (stagetilenum == -1)
	{
		//Unit配置スペース
		mType = OBJECT_TYPE::PLACEMENT_SPACE;
	}
	else if (stagetilenum == 2)
	{
		//敵の最終到達地点
		mType = OBJECT_TYPE::ENEMY_GOAL;
	}
	else
	{
		//敵のスタート位置
		mType = OBJECT_TYPE::ENEMY_START;
	}
}

//オブジェクトの座標の設定
void Object::SetPos(
	const float& x
	, const float& z)
{
	mPos.x = x;
	mPos.z = z;
}

//描画
void Object::Draw()
{
	DrawManager& pObject = DrawManager::GetInstance();

	//ワールドの初期化
	mWorld = Matrix::Identity;

	pObject.GetTexture3D()->SetColor();

	switch (mType)
	{
		case OBJECT_TYPE::ROAD:
		{
			mWorld *= Matrix::CreateRotationX(XMConvertToRadians(90.0f));
			mWorld *= Matrix::CreateTranslation(mPos);
			
			pObject.GetTexture3D()->DrawShader(mWorld, TEXTURE3D::LAND);
			break;
		}
		case OBJECT_TYPE::WALL:
		{
			mWorld *= Matrix::CreateScale(1.0f, 1.0f, 1.0f);
			mWorld *= Matrix::CreateTranslation(mPos.x, mPos.y-0.5f, mPos.z);
			//pObject.GetModel()->Draw(mWorld, MODEL_NAME::WALL);

			pObject.GetGeometry()->Draw(mWorld, SHAPE::CUBE, Colors::DarkGreen);

			mWorld = Matrix::Identity;
			mWorld *= Matrix::CreateScale(0.0035f);
			mWorld *= Matrix::CreateTranslation(mPos.x, mPos.y + 0.2f, mPos.z);
			pObject.GetModel()->Draw(mWorld, MODEL_NAME::tree);
			break;
		}
		case OBJECT_TYPE::PLACEMENT_SPACE:
		{
			mWorld *= Matrix::CreateRotationX(XMConvertToRadians(90.0f));
			mWorld *= Matrix::CreateTranslation(mPos);
			//pObject.GetGeometry()->Draw(mWorld, SHAPE::CUBE, Colors::LightGreen);
			pObject.GetTexture3D()->DrawShader(mWorld, TEXTURE3D::GRASSLAND);
			break;
		}
		case OBJECT_TYPE::ENEMY_GOAL:
		{
			mWorld *= Matrix::CreateTranslation(mPos.x, mPos.y - 0.5f, mPos.z);
			pObject.GetGeometry()->Draw(mWorld, SHAPE::CUBE, Colors::Aqua);

			mWorld = Matrix::Identity;
			mWorld *= Matrix::CreateScale(0.0013f);
			mWorld *= Matrix::CreateTranslation(mPos.x,mPos.y+0.4f,mPos.z);
			
			pObject.GetModel()->Draw(mWorld, MODEL_NAME::HOUSE);
			break;
		}
		case OBJECT_TYPE::ENEMY_START:
		{
			mWorld = Matrix::CreateTranslation(mPos.x, mPos.y - 0.5f, mPos.z);
			pObject.GetGeometry()->Draw(mWorld, SHAPE::CUBE, Colors::Red);
			break;
		}
		case OBJECT_TYPE::NONE:
		{
			break;
		}
		default:
			break;
	}
}

//オブジェクトの座標を返す
const Vector3 Object::GetPos()
{
	//オブジェクトごとの位置情報のずれ
	const float Locationinformationofeachobject0 = 0.1f;
	const float Locationinformationofeachobject1 = 0.1f;
	const float Locationinformationofeachobject2 = 0.1f;
	const float Locationinformationofeachobject3 = 0.1f;
	const float Locationinformationofeachobject4 = 0.1f;

	switch (mType)
	{
		case OBJECT_TYPE::ROAD:
		{
			return Vector3(mPos.x, mPos.y + Locationinformationofeachobject0, mPos.z);
			break;
		}
		case OBJECT_TYPE::WALL:
		{
			return Vector3(mPos.x, mPos.y + Locationinformationofeachobject1, mPos.z);
			break;
		}
		case OBJECT_TYPE::PLACEMENT_SPACE:
		{
			return Vector3(mPos.x, mPos.y + Locationinformationofeachobject2, mPos.z);
			break;
		}
		case OBJECT_TYPE::ENEMY_GOAL:
		{
			return Vector3(mPos.x, mPos.y + Locationinformationofeachobject3, mPos.z);
			break;
		}
		case OBJECT_TYPE::ENEMY_START:
		{
			return Vector3(mPos.x, mPos.y + Locationinformationofeachobject4, mPos.z);
			break;
		}
		default:
			break;
	}

	return mPos;
}