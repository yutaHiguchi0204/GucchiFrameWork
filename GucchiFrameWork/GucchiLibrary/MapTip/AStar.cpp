/* =====================================================================
//! @param		�uAStar�v�\�[�X
//! @create		��� �T��
//! @date		17/12/28
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "AStar.h"
#include <cassert>
#include <d3d11_1.h>
#include "../3D/ObjectRenderer.h"
#include "../Common/DebugSwitch.h"

// ���O���
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// �ÓI�����o�̒�`
const int AStar::NUM_ADJOIN;									// �אڃ^�C����
/*
// �P�Q�R
// �W�@�S
// �V�U�T
*/
Node::Point						AStar::offset_[NUM_ADJOIN] = {		// �I�t�Z�b�g���X�g
									{ -1, -1 }, { 0, -1 }, { 1, -1 }, { 1,  0 }, { 1,  1 }, { 0,  1 }, { -1,  1 }, { -1,  0 }
								};
vector<vector<Node*>>			AStar::mapData_;					// �}�b�v�f�[�^
list<Node*>						AStar::openList_;					// �I�[�v�����X�g
vector<Node*>					AStar::shortestRoute_;				// �ŒZ�o�H
Node::Point						AStar::start_;						// �o�H�T���J�n�n�_
Node::Point						AStar::end_;						// �o�H�T���I���n�_
DirectX::SimpleMath::Vector3	AStar::mapPos_;						// �}�b�v���̂̍��W
vector<unique_ptr<Object>>		AStar::routePlane_;					// �ŒZ�o�H�i�r�Q�[�^�[

// �����o�֐��̒�`

// �R���X�g���N�^
Node::Node()
	: cost_(0)
	, terrainCost_(0)
	, heuristic_(0)
	, parentNode_(nullptr)
	, pos_(Point{ 0, 0 })
	, attribute_(ATTRIBUTE::NONE)
	, state_(STATE::FREE)
{
}

/*==============================================================
// @brief		����������
// @param		�}�b�v�f�[�^�ivector<vector<int>>�j
// @return		�Ȃ�
===============================================================*/
void AStar::Initialize(vector<vector<int>> map)
{
	start_	= { -1, -1 };
	end_	= { -1, -1 };

	// �e�m�[�h�̐���
	for (auto& mapRow : map)
	{
		mapData_.emplace_back();
		for (auto& mapTip : mapRow)
		{
			// �V�m�[�h
			Node* node = new Node;

			int row = mapData_.size() - 1;
			mapData_[row].emplace_back(node);

			int column = mapData_[row].size() - 1;

			// �ʒu�̕ۑ�
			mapData_[row][column]->SetPos(Node::Point{ column, row });

			// �����̕ۑ�
			mapData_[row][column]->SetAttribute(static_cast<Node::ATTRIBUTE>(mapTip));

			// �X�^�[�g�ƃS�[���̐ݒ�
			if (mapData_[row][column]->GetAttribute() == Node::ATTRIBUTE::START)
			{
				start_ = Node::Point{ column, row };
			}
			else if (mapData_[row][column]->GetAttribute() == Node::ATTRIBUTE::GOAL)
			{
				end_ = Node::Point{ column, row };
			}
		}
	}

	// �R�X�g�ƃq���[���X�e�B�b�N�̌v�Z
	for (int i = 0; i < static_cast<int>(mapData_.size()); i++)
	{
		for (int j = 0; j < static_cast<int>(mapData_[i].size()); j++)
		{
			// �n�`�R�X�g�̐ݒ�
			int terrainCost = SetTerrainCost(j, i);
			mapData_[i][j]->SetTerrainCost(terrainCost);

			// �q���[���X�e�B�b�N�̌v�Z
			int heuristic = SetHeuristic(j, i);
			mapData_[i][j]->SetHeuristic(heuristic);
		}
	}

	// �X�^�[�g�������̓S�[�����ݒ肳��Ă��Ȃ�������G���[
	if (start_.posX == -1 || start_.posY == -1 || end_.posX == -1 || end_.posY == -1)
	{
#if defined(MODE_DEBUG)
		// �}�b�v�f�[�^�G���[
		OutputDebugString(L"Map data error.");
#endif
		assert(false);
	}

	// �}�b�v���̂̍��W���O�ɐݒ�
	mapPos_ = Vector3::Zero;
}

/*==============================================================
// @brief		�I������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void AStar::Finalize()
{
	for (auto& mapRow : mapData_)
	{
		for (auto& mapTip : mapRow)
		{
			delete mapTip;
		}
	}
}

/*==============================================================
// @brief		�o�H�T��
// @param		�Ȃ�
// @return		�o�H�T�������������f�[�^�ivector<vector<Node*>>�j
===============================================================*/
vector<vector<Node*>> AStar::Search()
{
	// �S�[���n�_�̃m�[�h���I�[�v�����A�I�[�v�����X�g�ɒǉ�����
	mapData_[end_.posY][end_.posX]->SetState(Node::STATE::OPEN);
	openList_.emplace_back(mapData_[end_.posY][end_.posX]);

	// ���݂̃m�[�h
	Node* checkNode = mapData_[end_.posY][end_.posX];

	// �S�[������X�^�[�g�܂ł�A*�o�H�T��
	// �I�[�v�����X�g����łȂ�
	while (!openList_.empty())
	{
		// �I�[�v�����X�g�̂����A�X�R�A���ŏ��̃m�[�h���擾
		checkNode = CheckMinScoreNode();

		// �o�H�������������ǂ���
		if (checkNode->GetAttribute() == Node::ATTRIBUTE::START)
		{
			checkNode->SetState(Node::STATE::CLOSED);
			return mapData_;
		}
		else
		{
			// �אڃ^�C�����`�F�b�N
			CheckAdjoin(checkNode);
		}
	}

	// �����ɂ��邱�Ƃ͂Ȃ�
	return mapData_;
}

/*==============================================================
// @brief		�ŒZ�o�H���X�g���擾
// @param		�Ȃ�
// @return		�ŒZ�o�H���X�g�ivector<Node*>�j
===============================================================*/
vector<Node*> AStar::GetShortestRoute()
{
	// �o�H�T�����I����Ă��Ȃ���΃G���[
	if (mapData_[start_.posY][start_.posX]->GetState() != Node::STATE::CLOSED)
	{
#if defined(MODE_DEBUG)
		// �T���I�����ĂȂ��G���[
		OutputDebugString(L"Don't finish search.");
#endif
		assert(false);
	}

	// �ŒZ�o�H�����X�g�ɒǉ�
	shortestRoute_.emplace_back(mapData_[start_.posY][start_.posX]);

	// �e�m�[�h�����ǂ�A�S�[���܂Ń��X�g�ɒǉ�����
	Node* parent = mapData_[start_.posY][start_.posX]->GetParentNode();
	while (parent != nullptr)
	{
		shortestRoute_.emplace_back(parent);
		parent = parent->GetParentNode();
	}

	return shortestRoute_;
}

/*==============================================================
// @brief		�T�����ʂ��l�p�`�ŕ\��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void AStar::DrawResult()
{
	// �ڕW�n�_���N���[�Y�h���X�g�Ɋ܂܂�ĂȂ�������T�����������Ă��Ȃ��̂łȂɂ����Ȃ�
	if (mapData_[start_.posY][start_.posX]->GetState() == Node::STATE::CLOSED)
	{
		ObjectFactory& factory = ObjectFactory::GetInstance();
		ObjectRenderer& renderer = ObjectRenderer::GetInstance();

		// �ڕW�n�_�Ƀi�r�Q�[�^�[���ʂ�ݒu
		routePlane_.emplace_back(factory.CreateObjectFromFile(L"routePlane"));
		routePlane_.back()->SetTranslate(Vector3(start_.posX + mapPos_.x, mapPos_.y + 1.f, start_.posY + mapPos_.z));
		renderer.RegisterObject(routePlane_.back().get());

		// �e�m�[�h�����ǂ�A���ׂĂɃi�r�Q�[�^�[���ʂ�ݒu
		Node* parent = mapData_[start_.posY][start_.posX]->GetParentNode();
		while (parent != nullptr)
		{
			routePlane_.emplace_back(factory.CreateObjectFromFile(L"routePlane"));
			routePlane_.back()->SetTranslate(Vector3(parent->GetPosX() + mapPos_.x, mapPos_.y + 1.f, parent->GetPosY() + mapPos_.z));
			renderer.RegisterObject(routePlane_.back().get());

			// �e�m�[�h�����ǂ�
			parent = parent->GetParentNode();
		}
	}
}

/*==============================================================
// @brief		�ŒZ�o�H�i�r�Q�[�^�[�̃A�N�e�B�u��Ԃ�ύX
// @param		�A�N�e�B�u��ԁibool�j
// @return		�Ȃ�
===============================================================*/
void AStar::SetNavigatorActive(bool active)
{
	for (auto& routePlane : routePlane_)
	{
		routePlane->SetActive(active);
	}
}

/*==============================================================
// @brief		�אڂ���^�C���W�𒲂ׂ�
// @param		�`�F�b�N���̃m�[�h�iNode*�j
// @return		�Ȃ�
===============================================================*/
void AStar::CheckAdjoin(Node* node)
{
	// ���݂̃m�[�h���N���[�Y�h���X�g�ɒǉ�
	node->SetState(Node::STATE::CLOSED);

	// ���݂̃m�[�h���I�[�v�����X�g����폜
	for (auto itr = openList_.cbegin(); itr != openList_.cend();)
	{
		if (*itr == node)
		{
			openList_.erase(itr);
			break;
		}
		
		++itr;
	}

	// �אڂ���W�̃m�[�h�𒲂ׂ�
	for (auto& i : offset_)
	{
		// �`�F�b�N����אڃ^�C��
		int x = node->GetPosX() + i.posX;
		int y = node->GetPosY() + i.posY;

		// �}�b�v�����ǂ���
		bool insideMap = (x >= 0 && y >= 0) && (y < static_cast<int>(mapData_.size())) && (x < static_cast<int>(mapData_[y].size()));

		if (insideMap)
		{
			// ���łɃI�[�v�����X�g�E�N���[�Y�h���X�g�Ɋ܂܂�Ă���Ƃ��A
			// �܂��͏�Q���̏ꍇ�͖�������
			if (mapData_[y][x]->GetState() != Node::STATE::OPEN				&&
				mapData_[y][x]->GetState() != Node::STATE::CLOSED			&&
				mapData_[y][x]->GetAttribute() != Node::ATTRIBUTE::WALL)
			{
				// �e�m�[�h��ݒ�
				mapData_[y][x]->SetParentNode(node);

				// �R�X�g�v�Z
				int cost = GetCost(mapData_[y][x]);
				mapData_[y][x]->SetCost(cost);

				// �I�[�v�����X�g�ɒǉ�
				mapData_[y][x]->SetState(Node::STATE::OPEN);
				openList_.emplace_back(mapData_[y][x]);
			}
		}
	}
}

/*==============================================================
// @brief		�n�`�R�X�g�̐ݒ�
// @param		���g�̈ʒux�iint�j�A���g�̈ʒuy�iint�j
// @return		�n�`�R�X�g�iint�j
===============================================================*/
int AStar::SetTerrainCost(int x, int y)
{
	switch (mapData_[y][x]->GetAttribute())
	{
	case Node::ATTRIBUTE::NONE:		return 1;	break;		// �ʏ�̓�
	case Node::ATTRIBUTE::SWAMP:	return 3;	break;		// ��
	default:						return 0;	break;
	}
}

/*==============================================================
// @brief		�q���[���X�e�B�b�N�̌v�Z
// @param		���g�̈ʒux�iint�j�A���g�̈ʒuy�iint�j
// @return		�q���[���X�e�B�b�N�l�iint�j
===============================================================*/
int AStar::SetHeuristic(int x, int y)
{
	// X, Y�̋��������߂�
	int distanceX = abs(x - start_.posX) * 10;
	int distanceY = abs(y - start_.posY) * 10;

	// �������傫������Ԃ�
	return distanceX > distanceY ? distanceX : distanceY;
}

/*==============================================================
// @brief		�I�[�v�����X�g�̒��ŃX�R�A���ŏ��̃m�[�h���`�F�b�N
// @param		�Ȃ�
// @return		�I�[�v�����X�g�̒��ŃX�R�A���ŏ��̃m�[�h�iNode*�j
===============================================================*/
Node* AStar::CheckMinScoreNode()
{
	// �I�[�v�����X�g�Ƀm�[�h���Ȃ�������null��Ԃ�
	if (openList_.empty())
	{
		return nullptr;
	}

	Node* checkNode = nullptr;

	// ���݂̃m�[�h�ɃI�[�v�����X�g�̂����X�R�A���ŏ��̃m�[�h��ݒ�
	int scoreMin = 999;
	for (auto& node : openList_)
	{
		// �X�R�A�v�Z
		int score = GetScore(node);

		// �X�R�A���ŏ��̃m�[�h��ݒ�
		if (score <= scoreMin)
		{
			scoreMin = score;
			checkNode = node;
		}
	}

	return checkNode;
}

/*==============================================================
// @brief		�R�X�g�̌v�Z
// @param		�R�X�g���擾�������m�[�h�iNode*�j
// @return		�R�X�g�iint�j
===============================================================*/
int AStar::GetCost(Node* node)
{
	int cost = 0;

	// �e�m�[�h������΂���ɒH��
	if (node->GetParentNode())
	{
		// �㉺���E
		if (abs(node->GetParentNode()->GetPosX() - node->GetPosX()) + abs(node->GetParentNode()->GetPosY() - node->GetPosY()) == 1)
		{
			cost += GetCost(node->GetParentNode()) + node->GetTerrainCost() * 10;
		}
		// �΂�
		else
		{
			cost += GetCost(node->GetParentNode()) + node->GetTerrainCost() * 15;
		}
	}

	return cost;
}

/*==============================================================
// @brief		�X�R�A�̌v�Z
// @param		�X�R�A���擾�������m�[�h�iNode*�j
// @return		�X�R�A�iint�j
===============================================================*/
int AStar::GetScore(Node* node)
{
	return node->GetCost() + node->GetHeuristic();
}