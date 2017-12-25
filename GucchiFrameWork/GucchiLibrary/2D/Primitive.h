/* =====================================================================
//! @param		�uPrimitive�v�w�b�_
//! @create		��� �T��
//! @date		17/12/23
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <map>
#include <SimpleMath.h>
#include <string>

namespace GucchiLibrary
{
	/*
	// @class		Primitive �N���X
	// @content		�v���~�e�B�u
	*/
	class Primitive
	{
	public:
		/*
		// @content		�v���~�e�B�u�^�C�v
		// @mode		LINE		�F	��
		// @mode		TRIANGLE	�F	�O�p
		*/
		enum class PRIMITIVE_TYPE
		{
			LINE,
			TRIANGLE,
			SQUARE,
			CIRCLE
		};

	private:
		PRIMITIVE_TYPE											type_;
		std::map<std::string, DirectX::SimpleMath::Vector2>		point_;
		DirectX::SimpleMath::Color								color_;
		bool													isFill_;

		// �~�v���~�e�B�u�p
		DirectX::SimpleMath::Vector2							center_;
		float													radius_;

	public:
		// �R���X�g���N�^
		Primitive();

		// �f�X�g���N�^
		virtual ~Primitive() {}

		/*
		// @method		Entry
		// @content		�v���~�e�B�u�쐬�i���j
		// @param		�n�_�iVector2�j
		// @param		�I�_�iVector2�j
		// @param		�F�iColor�j	�F	�f�t�H���g�iColor(1, 1, 1, 1)�j
		*/
		void Entry(const DirectX::SimpleMath::Vector2& start, const DirectX::SimpleMath::Vector2& end, const DirectX::SimpleMath::Color& color = DirectX::SimpleMath::Color(1, 1, 1, 1));

		/*
		// @method		Entry
		// @content		�v���~�e�B�u�쐬�i�O�p�j
		// @param		�h��Ԃ����ǂ����ibool�j
		// @param		�P�_�ځiVector2�j
		// @param		�Q�_�ځiVector2�j
		// @param		�R�_�ځiVector2�j
		// @param		�F�iColor�j					�F	�f�t�H���g�iColor(1, 1, 1, 1)�j
		*/
		void Entry(bool fillFlag, const DirectX::SimpleMath::Vector2& _p1, const DirectX::SimpleMath::Vector2& _p2, const DirectX::SimpleMath::Vector2& _p3, const DirectX::SimpleMath::Color& color = DirectX::SimpleMath::Color(1, 1, 1, 1));

		/*
		// @method		Entry
		// @content		�v���~�e�B�u�쐬�i�l�p�j
		// @param		�h��Ԃ����ǂ����ibool�j
		// @param		����̍��W�iVector2�j
		// @param		�E���̍��W�iVector2�j
		// @param		�F�iColor�j					�F	�f�t�H���g�iColor(1, 1, 1, 1)�j
		*/
		void Entry(bool fillFlag, const DirectX::SimpleMath::Vector2& topLeft, const DirectX::SimpleMath::Vector2& bottomRight, const DirectX::SimpleMath::Color& color = DirectX::SimpleMath::Color(1, 1, 1, 1));

		/*
		// @method		Entry
		// @content		�v���~�e�B�u�쐬�i�~�j
		// @param		�h��Ԃ����ǂ����ibool�j
		// @param		���S���W�iVector2�j
		// @param		���a�ifloat�j
		// @param		�������iint�j
		// @param		�F�iColor�j					�F	�f�t�H���g�iColor(1, 1, 1, 1)�j
		*/
		void Entry(bool fillFlag, const DirectX::SimpleMath::Vector2& center, float radius, int div, const DirectX::SimpleMath::Color& color = DirectX::SimpleMath::Color(1, 1, 1, 1));

		/* �A�N�Z�b�T */

		void SetColor(const DirectX::SimpleMath::Color& color)							{ color_ = color; }
		void SetFillFlag(bool fillFlag)													{ isFill_ = fillFlag; }

		inline PRIMITIVE_TYPE GetType()	const											{ return type_; }
		inline std::map<std::string, DirectX::SimpleMath::Vector2> GetPoints() const 	{ return point_; }
		inline DirectX::SimpleMath::Color GetColor() const								{ return color_; }
		inline bool GetFillFlag() const													{ return isFill_; }
		inline DirectX::SimpleMath::Vector2 GetCircleCenterPos() const					{ return center_; }
		inline float GetCircleRadius() const											{ return radius_; }
	};
}