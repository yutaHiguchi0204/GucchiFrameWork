/* =====================================================================
//! @param		�uAStar�v�w�b�_
//! @create		��� �T��
//! @date		17/12/28
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <list>
#include <SimpleMath.h>
#include <vector>
#include "MapTip2D.h"
#include "MapTip3D.h"

namespace GucchiLibrary
{
	/*
	// @class		Node �N���X
	// @content		�m�[�h�N���X
	*/
	class Node
	{
	public:
		/*
		// @content		�m�[�h�̑���
		// @mode		NONE	�F�@���ɉ����Ȃ�
		// @mode		WALL	�F�@��Q������
		// @mode		SWAMP	�F�@������i�n�`�R�X�g�������j
		// @mode		START	�F�@�o�H�T���J�n�n�_
		// @mode		GOAL	�F�@�o�H�T���I���n�_
		*/
		enum class ATTRIBUTE
		{
			NONE,
			WALL,
			SWAMP,
			START,
			GOAL
		};

		/*
		// @content		�m�[�h�̏��
		// @mode		FREE	�F	�������Ă��Ȃ��m�[�h
		// @mode		OPEN	�F	�I�[�v�����X�g
		// @mode		CLOSED	�F	�N���[�Y�h���X�g
		*/
		enum class STATE
		{
			FREE,
			OPEN,
			CLOSED
		};

		/*
		// @struct		Point �\����
		// @content		�|�C���g�\���́iVector2��int�o�[�W�����j
		*/
		struct Point
		{
			int posX;
			int posY;
		};

	private:
		int cost_;								// �R�X�g
		int terrainCost_;						// �n�`�R�X�g
		int heuristic_;							// �q���[���X�e�B�b�N

		Node* parentNode_;						// �e�m�[�h

		Point pos_;								// ���W

		ATTRIBUTE attribute_;					// �m�[�h�̑���
		STATE state_;							// �`�b�v�̏��

	public:
		// �R���X�g���N�^
		Node();

		// �f�X�g���N�^
		virtual ~Node() {}

		/* �A�N�Z�b�T */

		void SetCost(int cost)					{ cost_ = cost; }
		void SetTerrainCost(int cost)			{ terrainCost_ = cost; }
		void SetHeuristic(int heuristic)		{ heuristic_ = heuristic; }
		void SetParentNode(Node* parent)		{ parentNode_ = parent; }
		void SetPos(const Point& pos)			{ pos_ = pos; }
		void SetPosX(int posX)					{ pos_.posX = posX; }
		void SetPosY(int posY)					{ pos_.posY = posY; }
		void SetAttribute(ATTRIBUTE attribute)	{ attribute_ = attribute; }
		void SetState(STATE state)				{ state_ = state; }

		inline int GetCost()					{ return cost_; }
		inline int GetTerrainCost()				{ return terrainCost_; }
		inline int GetHeuristic()				{ return heuristic_; }
		inline Node* GetParentNode()			{ return parentNode_; }
		inline const Point& GetPos() const		{ return pos_; }
		inline int GetPosX() const				{ return pos_.posX; }
		inline int GetPosY() const				{ return pos_.posY; }
		inline ATTRIBUTE GetAttribute() const	{ return attribute_; }
		inline STATE GetState() const			{ return state_; }
	};

	/*
	// @class		AStar �N���X
	// @content		A* �o�H�T�� �N���X
	*/
	class AStar
	{
	public:
		static const int NUM_ADJOIN = 8;									// �אڃ^�C����

	private:
		static Node::Point offset_[NUM_ADJOIN];								// �אڃ^�C����

		static std::vector<std::vector<Node*>> mapData_;					// �}�b�v�f�[�^
		static std::list<Node*> openList_;									// �I�[�v�����X�g
		static std::vector<Node*> shortestRoute_;							// �ŒZ�o�H

		static Node::Point start_;											// �J�n�n�_
		static Node::Point end_;											// �I���n�_

		static DirectX::SimpleMath::Vector3 mapPos_;						// �}�b�v���̂̍��W�i�f�t�H���g�͂O�ł����A�}�b�v�f�[�^�̃_�~�[�I�u�W�F�N�g�̈ʒu��o�^���邱�Ƃ��ł��܂��j

		static std::vector<std::unique_ptr<Object>> routePlane_;			// �ŒZ�o�H�i�r�Q�[�^�[

	public:
		/*
		// @method		Initialize�istatic�j
		// @content		����������
		// @param		�}�b�v�f�[�^�ivector<vector<int>>�j
		*/
		static void Initialize(std::vector<std::vector<int>> map);

		/*
		// @method		Finalize�istatic�j
		// @content		�I�������i���������[�N�΍�̂��߁AA* �o�H�T���A���S���Y����p�����ꍇ�͕K���Ă�ł��������j
		*/
		static void Finalize();

		/*
		// @method		Search�istatic�j
		// @content		�o�H�T��
		// @return		�o�H�T�������������f�[�^�ivector<vector<Node*>>�j
		*/
		static std::vector<std::vector<Node*>> Search();

		/*
		// @method		GetShortestRoute�istatic�j
		// @content		�ŒZ�o�H���X�g���擾
		// @return		�ŒZ�o�H���X�g�ivector<Node*>�j
		*/
		static std::vector<Node*> GetShortestRoute();

		/*
		// @method		DrawResult�istatic�j
		// @content		�T�����ʂ��l�p�`�ŕ\��
		*/
		static void DrawResult();

		/*
		// @method		SetNavigatorActive�istatic�j
		// @content		�ŒZ�o�H�i�r�Q�[�^�[�̃A�N�e�B�u��Ԃ�ύX
		// @param		�A�N�e�B�u��ԁibool�j
		*/
		static void SetNavigatorActive(bool active);

		/*
		// @method		CheckAdjoin�istatic�j
		// @content		�אڂ���^�C���W�𒲂ׂ�
		// @param		�`�F�b�N���̃m�[�h�iNode*�j
		*/
		static void CheckAdjoin(Node* node);

		/*
		// @method		SetTerrainCost�istatic�j
		// @content		�n�`�R�X�g�̐ݒ�
		// @param		���g�̈ʒux�iint�j
		// @param		���g�̈ʒuy�iint�j
		// @return		�q���[���X�e�B�b�N�l�iint�j
		*/
		static int SetTerrainCost(int x, int y);

		/*
		// @method		SetHeuristic�istatic�j
		// @content		�q���[���X�e�B�b�N�̌v�Z
		// @param		���g�̈ʒux�iint�j
		// @param		���g�̈ʒuy�iint�j
		// @return		�q���[���X�e�B�b�N�l�iint�j
		*/
		static int SetHeuristic(int x, int y);

		/*
		// @method		CheckMinScoreNode�istatic�j
		// @content		�I�[�v�����X�g�̒��ŃX�R�A���ŏ��̃m�[�h���`�F�b�N
		// @return		�I�[�v�����X�g�̒��ŃX�R�A���ŏ��̃m�[�h�iNode*�j
		*/
		static Node* CheckMinScoreNode();

		/*
		// @method		GetCost�istatic�j
		// @content		�R�X�g�̌v�Z
		// @param		�R�X�g���擾�������m�[�h�iNode*�j
		// @return		�R�X�g�iint�j
		*/
		static int GetCost(Node* node);

		/*
		// @method		GetScore�istatic�j
		// @content		�X�R�A�̌v�Z
		// @param		�X�R�A���擾�������m�[�h�iNode*�j
		// @return		�X�R�A�iint�j
		*/
		static int GetScore(Node* node);

		/* �A�N�Z�b�T */

		static Node* GetNode(Node::Point point)		{ return mapData_[point.posY][point.posX]; }
		static Node* GetNode(int posX, int posY)	{ return mapData_[posY][posX]; }

		static void SetMapPos(MapTip2D* map)		{ mapPos_ = DirectX::SimpleMath::Vector3(map->GetPos().x, map->GetPos().y, 0); }
		static void SetMapPos(MapTip3D* map)		{ mapPos_ = map->GetTranslate(); }
	};
}