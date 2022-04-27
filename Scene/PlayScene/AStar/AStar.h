#pragma once
#include<map>
#include<vector>
#include"../../Utility.h"
#include<SimpleMath.h>

//�O���錾
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

	//�X�^�[�g�ƃS�[���̈ʒu
	Int2 mGoal, mStart, mPos;

	//�ړI�n
	Int2 mDestination;

	//�X�e�[�W�f�[�^
	std::vector<std::vector<int>> ndata, ndata_2;

	//�X�e�[�W�̗����Ɖ���
	int mHorizontal, mVertical;

public:

	//�R���X�g���N�^
	AStar();
	//�f�X�g���N�^
	~AStar();

	//������
	void Initialize(StageRead* pStageRead);

	const float& Move();

	//A*���s
	const DirectX::SimpleMath::Vector3& _tmain(const int& startnum);

	//���W�̎擾
	const Int2& GetPos() { return mPos; }

	//�S�[���ɂ������̊m�F
	const bool& CheckGoal();

private:

	//�X�^�[�Ƃ̃Z�b�g
	void SetStart(const int& startnum);
	
	// �}���n�b�^���������΂߈ړ�������l�����ċ��߂�
	const int& GetDistance(
		const int& from_x
		, const int& from_y
		, const int& to_x
		,const  int& to_y);

	// �m�[�h������x�ɃZ�b�g����
	const anode* SetNode(
		anode* n
		, const int& nx
		, const int& ny
		, const int& npx
		, const int& npy
		, const int& ncost);

	// �w�肵���n�_����X�^�[�g�n�_�܂ł̋��������߂�
	const int& BackTrace(
		const int& x
		, const int& y);

	// A*�Ōo�H�T������
	const int& Search(const int& count);

	// �ŒZ���[�g���}�b�v�f�[�^�ɏ����o��
	void TraceRoute(const int& x, const int& y);
};