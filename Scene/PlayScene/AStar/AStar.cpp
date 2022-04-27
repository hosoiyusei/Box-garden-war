#include"pch.h"
#include"AStar.h"

#include"../Stage/StageRead.h"

#define KEY(X, Y) ((X) * 100 + (Y))
#define KEYDATA(X, Y, N) std::pair<int, anode>(KEY(X,Y), N)

//�R���X�g���N�^
AStar::AStar()
	: mapOpen()
	, mapClose()
	, mGoal()
	, mStart()
	, mPos()
	, mHorizontal(0)
	, mVertical(0)
	, ndata{}
	, ndata_2{}
	, mDestination()
{

}

//�f�X�g���N�^
AStar::~AStar()
{

}

//������
void AStar::Initialize(StageRead* pStageRead)
{
	//�X�e�[�W�̉����̎擾
	mHorizontal = pStageRead->GetHorizontal();
	//�X�e�[�W�̗����̎擾
	mVertical = pStageRead->GetVertical();
	//�X�e�[�W�f�[�^�̎擾
	for (int i = 0; i < mVertical; i++)
	{
		ndata.push_back(std::vector<int>());
		ndata_2.push_back(std::vector<int>());

		for (int j = 0; j < mHorizontal; j++)
		{
			ndata[i].push_back(0);
			ndata_2[i].push_back(0);

			if (pStageRead->GetStageData(j, i) == 1)
			{
				ndata_2[i][j] = -1;
			}
			else
			{
				ndata_2[i][j] = pStageRead->GetStageData(j, i);
			}

			//�S�[���̃Z�b�g
			if (ndata_2[i][j] == 2)
			{
				mGoal.mX = j;
				mGoal.mY = i;
			}
		}
	}
}

//Enemy�̍��W
const float& AStar::Move()
{
	//��������
	if (mPos.mX - 1 >= 0)
	{
		if (ndata[mPos.mY][mPos.mX - 1] == 10)
		{
			mDestination = mPos;

			ndata[mPos.mY][mPos.mX] = 11;
			mPos.mX -= 1;

			return atan2f(
				static_cast<float>(mPos.mY - mDestination.mY)
				, static_cast<float>(mPos.mX + mDestination.mX));
		}
	}
	
	//�E������
	if (mPos.mX + 1 <= mHorizontal)
	{
		if (ndata[mPos.mY][mPos.mX + 1] == 10)
		{
			mDestination = mPos;

			ndata[mPos.mY][mPos.mX] = 11;
			mPos.mX += 1;

			return atan2f(
				static_cast<float>(mPos.mY - mDestination.mY)
				, static_cast<float>((mPos.mX - 100) + mDestination.mX));
		}
	}

	//�������
	if (mPos.mY - 1 >= 0)
	{
		if (ndata[mPos.mY - 1][mPos.mX] == 10)
		{
			mDestination = mPos;

			ndata[mPos.mY][mPos.mX] = 11;
			mPos.mY -= 1;

			return atan2f(
				static_cast<float>(mPos.mY - mDestination.mY)
				, static_cast<float>(mPos.mX - mDestination.mX));
		}
	}
	
	//��������
	if (mPos.mY + 1 <= mVertical)
	{
		if (ndata[mPos.mY + 1][mPos.mX] == 10)
		{
			mDestination = mPos;

			ndata[mPos.mY][mPos.mX] = 11;
			mPos.mY += 1;

			return atan2f(
				static_cast<float>(mPos.mY - mDestination.mY)
				, static_cast<float>(mPos.mX - mDestination.mX));
		}
	}

	//�ǂ����ʂ�Ȃ�������
	return 0.0f;
}

//A*�̎��s
const DirectX::SimpleMath::Vector3& AStar::_tmain(const int& startnum)
{
	for (int i = 0; i < mVertical; i++)
	{
		for (int j = 0; j < mHorizontal; j++)
		{
			ndata[i][j] = ndata_2[i][j];
		}
	}

	SetStart(startnum);

	anode start;

	SetNode(
		&start,
		mStart.mX, mStart.mY,
		-1, -1,
		0
	);

	mapOpen.insert(KEYDATA(mStart.mX, mStart.mY, start));

	Search(0);

	TraceRoute(mGoal.mX, mGoal.mY);

	return DirectX::SimpleMath::Vector3(
		  static_cast<float>(mPos.mX)
		, 1.0f
		, static_cast<float>(mPos.mY));
}

//�S�[���ɂ��ǂ蒅�������ǂ���
const bool& AStar::CheckGoal()
{
	if (mPos.mX == mGoal.mX&&
		mPos.mY==mGoal.mY)
	{
		return true;
	}

	return false;
}

/*******************************************************************************/

// �}���n�b�^���������΂߈ړ�������l�����ċ��߂�
const int& AStar::GetDistance(
	const int& from_x
	, const int& from_y
	, const int& to_x
	, const  int& to_y)
{
	int cx = from_x - to_x;
	int cy = from_y - to_y;

	if (cx < 0) cx *= -1;
	if (cy < 0) cy *= -1;

	// ����ړ��R�X�g���v�Z
	if (cx < cy) {
		return (cx + (cy - cx));
	}
	else {
		return (cy + (cx - cy));
	}
}

// �m�[�h������x�ɃZ�b�g����
const anode* AStar::SetNode(
	  anode* n
	, const int& nx
	, const int& ny
	, const int& npx
	, const int& npy
	, const int& ncost)
{
	n->x = nx;
	n->y = ny;
	n->px = npx;
	n->py = npy;
	n->cost = ncost;

	return n;
}

// �w�肵���n�_����X�^�[�g�n�_�܂ł̋��������߂�
const int& AStar::BackTrace(
	const int& x
	, const  int& y)
{
	if (x == mStart.mX && y == mStart.mY)
	{
		return 1;
	}

	std::map<int, anode>::iterator tmp = mapClose.find(KEY(x, y));

	if (tmp == mapClose.end()) return 0;

	return BackTrace(tmp->second.px, tmp->second.py) + 1;
}

// A*�Ōo�H�T������
const int& AStar::Search(const int& count)
{
	// open���X�g����Ȃ�I��
	if (mapOpen.empty()) return -9;

	anode nodes[8];

	int way[4][2] = {
		{  0, -1},
		{  1,  0},
		{  0,  1},
		{ -1,  0},
	};

	std::map<int, anode>::iterator it;
	std::map<int, anode>::iterator it_min;

	anode n;

	int cost_min = 9999;
	int BackCost = 0;

	//Open���X�g����ŏ��̃R�X�g�����m�[�h�����o��
	it = mapOpen.begin();
	while (it != mapOpen.end())
	{
		if (cost_min > GetDistance(it->second.x, it->second.y, mGoal.mX, mGoal.mY))
		{
			cost_min = GetDistance(it->second.x, it->second.y, mGoal.mX, mGoal.mY);
			it_min = it;
		}
		it++;
	}

	SetNode(
		&n,
		it_min->second.x, it_min->second.y,
		it_min->second.px, it_min->second.py,
		it_min->second.cost
	);

	// Open���X�g����Close���X�g�ֈړ�
	mapClose.insert(KEYDATA(n.x, n.y, n));
	mapOpen.erase(KEY(n.x, n.y));

	// �ŏ��R�X�g�̃m�[�h����X�^�[�g�܂ł̈ړ��R�X�g
	BackCost = BackTrace(n.x, n.y);

	for (int i = 0; i < 4; i++)
	{
		// �אڂ���}�X�̍��W���v�Z
		int cx = n.x + way[i][0];
		int cy = n.y + way[i][1];

		if (cx < 0) continue;
		if (cy < 0) continue;

		if (cx >= mHorizontal) continue;
		if (cy >= mVertical) continue;

		// �ʂ�Ȃ������悯��
		if (ndata[cy][cx] == -1) continue;

		SetNode(
			&nodes[i],
			cx, cy,
			n.x, n.y,
			BackCost + GetDistance(cx, cy, mGoal.mX, mGoal.mY) + 1	// ����ړ��R�X�g
		);

		//Open���X�g�ɂ��̍��W�Ɠ����m�[�h�����邩�m�F
		if (mapOpen.find(KEY(cx, cy)) != mapOpen.end())
		{
			if (nodes[i].cost < mapOpen[KEY(cx, cy)].cost)
			{
				mapOpen[KEY(cx, cy)].px = n.x;
				mapOpen[KEY(cx, cy)].py = n.y;

				mapOpen[KEY(cx, cy)].cost = nodes[i].cost;
			}
			continue;
		}

		//Close���X�g�ɂ��̍��W�Ɠ����m�[�h�����邩�m�F
		if (mapClose.find(KEY(cx, cy)) != mapClose.end())
		{
			if (nodes[i].cost < mapClose[KEY(cx, cy)].cost)
			{
				anode tmp;

				SetNode(
					&tmp,
					cx, cy,
					n.x, n.y,
					nodes[i].cost
				);

				mapOpen.insert(KEYDATA(cx, cy, tmp));
				mapClose.erase(KEY(cx, cy));
			}
			continue;
		}

		// ������Ȃ���ΐV�K�Ƃ���Open���X�g�֒ǉ�
		mapOpen.insert(KEYDATA(nodes[i].x, nodes[i].y, nodes[i]));
	}

	//����������T���I��
	if (n.x == mGoal.mX && n.y == mGoal.mY) return -1;

	return Search(count + 1);
}

//�X�^�[�g�n�_���Z�b�g
void AStar::SetStart(const int& startnum)
{
	for (int i = 0; i < mVertical; i++)
	{
		for (int j = 0; j < mHorizontal; j++)
		{
			if (ndata[i][j] == startnum)
			{
				mStart.mX = j;
				mStart.mY = i;
				mPos = mStart;
				break;
			}
		}
	}
}

// �ŒZ���[�g���}�b�v�f�[�^�ɏ����o��
void AStar::TraceRoute(const int& x, const int& y)
{
	if (x == mStart.mX && y == mStart.mY)
		return;

	std::map<int, anode>::iterator node_it = mapClose.find(KEY(x, y));

	if (node_it != mapClose.end())
	{
		ndata[y][x] = 10;

		TraceRoute(node_it->second.px, node_it->second.py);

		if (x == mGoal.mX && y == mGoal.mY)
			return;
	}

	return;
}