/* =====================================================================
//! @param		�uPrimitiveRenderer�v�w�b�_
//! @create		��� �T��
//! @date		17/12/23
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "../Common/SingletonDirector.h"
#include <Effects.h>
#include <memory>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <wrl/client.h>
#include "Primitive.h"
#include "../Camera/Camera.h"

namespace GucchiLibrary
{
	/*
	// @class		PrimitiveRenderer �N���X�iSingleton�j
	// @content		�v���~�e�B�u�`��p
	*/
	class PrimitiveRenderer : public SingletonDirector<PrimitiveRenderer>
	{
	private:
		using Vector2 = DirectX::SimpleMath::Vector2;
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Matrix  = DirectX::SimpleMath::Matrix;
		using Color   = DirectX::SimpleMath::Color;

	private:
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>	primitiveBatch_;		// �v���~�e�B�u�o�b�`
		std::unique_ptr<DirectX::BasicEffect>									basicEffect_;			// �G�t�F�N�g
		Microsoft::WRL::ComPtr<ID3D11InputLayout>								inputLayout_;			// ���̓��C�A�E�g

		std::list<Primitive*>													primitiveList_;			// �v���~�e�B�u���X�g

		Camera*																	camera_;				// �J����

	private:
		friend class SingletonDirector<PrimitiveRenderer>;

		PrimitiveRenderer() = default;

	public:
		/*
		// @method		Initialize
		// @content		����������
		*/
		void Initialize();

		/*
		// @method		Draw
		// @content		�`�揈��
		*/
		void Draw();

		/*
		// @method		Draw2D
		// @content		�Q�c�p�`�揈��
		// @param		�Q�c�v���~�e�B�u�iPrimitive2D*�j
		// @param		�v���~�e�B�u�^�C�v�iPRIMITIVE_TYPE�j
		*/
		void Draw2D(Primitive2D* primitive, Primitive::PRIMITIVE_TYPE type);

		/*
		// @method		Draw3D
		// @content		�R�c�p�`�揈��
		// @param		�R�c�v���~�e�B�u�iPrimitive3D*�j
		*/
		void Draw3D(Primitive3D* primitive);

		/*
		// @method		GetVerticesArray
		// @content		�`��p�ɂ܂Ƃ߂�ꂽ���_�f�[�^�̔z����擾
		// @param		�v���~�e�B�u�iPrimitive2D*�j
		// @return		���_�f�[�^�z��iVertexPositionColor*�j
		*/
		DirectX::VertexPositionColor* GetVerticesArray(Primitive2D* primitive);

		/*
		// @method		DrawPrimitive
		// @content		�v���~�e�B�u�̕`��
		// @param		���_�f�[�^�iVertexPositionColor*�j
		// @param		���_���iint�j
		*/
		void DrawPrimitive(const DirectX::VertexPositionColor* vertices, int vertexCount);

		/*
		// @method		DrawPoint
		// @content		�_�̕`��
		// @param		���_�f�[�^�imap<string, VertexPositionColor>�j
		*/
		void DrawPoint(std::map<std::string, DirectX::VertexPositionColor> vertices);

		/*
		// @method		DrawSegment
		// @content		�����̕`��
		// @param		���_�f�[�^�imap<string, VertexPositionColor>�j
		*/
		void DrawSegment(std::map<std::string, DirectX::VertexPositionColor> vertices);

		/*
		// @method		DrawTriangle
		// @content		�O�p�̕`��
		// @param		���_�f�[�^�imap<string, VertexPositionColor>�j
		*/
		void DrawTriangle(std::map<std::string, DirectX::VertexPositionColor> vertices);

		/*
		// @method		DrawRectangle
		// @content		�l�p�̕`��
		// @param		���_�f�[�^�imap<string, VertexPositionColor>�j
		*/
		void DrawRectangle(std::map<std::string, DirectX::VertexPositionColor> vertices);

		/*
		// @method		DrawCircle
		// @content		�~�̕`��
		// @param		���_�f�[�^�imap<string, VertexPositionColor>�j
		// @param		�������iint�j
		*/
		void DrawCircle(std::map<std::string, DirectX::VertexPositionColor> vertices, int div);

		/*
		// @method		RegisterPrimitive
		// @content		�v���~�e�B�u�̓o�^
		// @param		�o�^����v���~�e�B�u�iPrimitive*�j
		*/
		void RegisterPrimitive(Primitive* primitive);

		/*
		// @method		DisposePrimitive
		// @content		�v���~�e�B�u�̉��
		// @param		�������v���~�e�B�u�iPrimitive*�j
		*/
		void DisposePrimitive(Primitive* primitive);

		/*
		// @method		Reset
		// @content		�o�^���ꂽ�v���~�e�B�u�̃��X�g�����Z�b�g
		*/
		void Reset();

		/* �A�N�Z�b�T */

		void SetCamera(Camera* camera) { camera_ = camera; }
	};

	/*
	// @class		PrimitiveFactory �N���X
	// @content		�v���~�e�B�u�����p
	*/
	class PrimitiveFactory
	{
	public:
		using Vector2 = DirectX::SimpleMath::Vector2;
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Color = DirectX::SimpleMath::Color;

	public:
		/*
		// @method		CreatePoint�istatic�j
		// @content		�_�v���~�e�B�u�̐���
		// @param		���W�iVector2�j
		// @param		�F�iColor�j	�F	�f�t�H���g�iColor(1, 1, 1, 1)�j
		// @return		�v���~�e�B�u�istd::unique_ptr<Primitive>�j
		*/
		static std::unique_ptr<Primitive> CreatePoint(const Vector2& point, const Color& color = Color(1, 1, 1, 1));

		/*
		// @method		CreatePoint�istatic�j
		// @content		�_�v���~�e�B�u�̐���
		// @param		���W�iVector3�j
		// @param		�F�iColor�j	�F	�f�t�H���g�iColor(1, 1, 1, 1)�j
		// @return		�v���~�e�B�u�istd::unique_ptr<Primitive>�j
		*/
		static std::unique_ptr<Primitive> CreatePoint(const Vector3& point, const Color& color = Color(1, 1, 1, 1));

		/*
		// @method		CreateSegment�istatic�j
		// @content		�����v���~�e�B�u�̐���
		// @param		�n�_�iVector2�j
		// @param		�I�_�iVector2�j
		// @param		�F�iColor�j	�F	�f�t�H���g�iColor(1, 1, 1, 1)�j
		// @return		�v���~�e�B�u�istd::unique_ptr<Primitive>�j
		*/
		static std::unique_ptr<Primitive> CreateSegment(const Vector2& start, const Vector2& end, const Color& color = Color(1, 1, 1, 1));

		/*
		// @method		CreateSegment�istatic�j
		// @content		�����v���~�e�B�u�̐���
		// @param		�n�_�iVector3�j
		// @param		�I�_�iVector3�j
		// @param		�F�iColor�j	�F	�f�t�H���g�iColor(1, 1, 1, 1)�j
		// @return		�v���~�e�B�u�istd::unique_ptr<Primitive>�j
		*/
		static std::unique_ptr<Primitive> CreateSegment(const Vector3& start, const Vector3& end, const Color& color = Color(1, 1, 1, 1));

		/*
		// @method		CreateTriangle�istatic�j
		// @content		�O�p�v���~�e�B�u�̐���
		// @param		�P�_�ځiVector2�j
		// @param		�Q�_�ځiVector2�j
		// @param		�R�_�ځiVector2�j
		// @param		�F�iColor�j					�F	�f�t�H���g�iColor(1, 1, 1, 1)�j
		// @param		�h��Ԃ����ǂ����ibool�j	�F	�f�t�H���g�ifalse�j
		// @return		�v���~�e�B�u�istd::unique_ptr<Primitive>�j
		*/
		static std::unique_ptr<Primitive> CreateTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color = Color(1, 1, 1, 1), bool isFill = false);

		/*
		// @method		CreateRectangle�istatic�j
		// @content		�����`�v���~�e�B�u�̐���
		// @param		������W�iVector2�j
		// @param		�E�����W�iVector2�j
		// @param		�F�iColor�j					�F	�f�t�H���g�iColor(1, 1, 1, 1)�j
		// @param		�h��Ԃ����ǂ����ibool�j	�F	�f�t�H���g�ifalse�j
		// @return		�v���~�e�B�u�istd::unique_ptr<Primitive>�j
		*/
		static std::unique_ptr<Primitive> CreateRectangle(const Vector2& topLeft, const Vector2& bottomRight, const Color& color = Color(1, 1, 1, 1), bool isFill = false);

		/*
		// @method		CreateBox�istatic�j
		// @content		�����̃v���~�e�B�u�̐���
		// @param		�T�C�Y�iVector3�j
		// @param		�F�iColor�j					�F	�f�t�H���g�iColor(1, 1, 1, 1)�j
		// @param		�h��Ԃ����ǂ����ibool�j	�F	�f�t�H���g�ifalse�j
		// @return		�v���~�e�B�u�iunique_ptr<Primitive3D>�j
		*/
		static std::unique_ptr<Primitive3D> CreateBox(const Vector3& size, const Color& color = Color(1, 1, 1, 1), bool isFill = false);

		/*
		// @method		CreateCircle�istatic�j
		// @content		�~�v���~�e�B�u�̐���
		// @param		���S���W�iVector2�j
		// @param		���a�ifloat�j
		// @param		�������iint�j
		// @param		�F�iColor�j					�F	�f�t�H���g�iColor(1, 1, 1, 1)�j
		// @param		�h��Ԃ����ǂ����ibool�j	�F	�f�t�H���g�ifalse�j
		// @return		�v���~�e�B�u�istd::unique_ptr<Primitive>�j
		*/
		static std::unique_ptr<Primitive> CreateCircle(const Vector2& center, float radius, int div, const Color& color = Color(1, 1, 1, 1), bool isFill = false);

		/*
		// @method		CreateSphere�istatic�j
		// @content		���v���~�e�B�u�̐���
		// @param		���a�ifloat�j
		// @param		�������iint�j
		// @param		�F�iColor�j					�F	�f�t�H���g�iColor(1, 1, 1, 1)�j
		// @param		�h��Ԃ����ǂ����ibool�j	�F	�f�t�H���g�ifalse�j
		// @return		�v���~�e�B�u�iunique_ptr<Primitive3D>�j
		*/
		static std::unique_ptr<Primitive3D> CreateSphere(float diameter, int div, const Color& color = Color(1, 1, 1, 1), bool isFill = false);
	};
}