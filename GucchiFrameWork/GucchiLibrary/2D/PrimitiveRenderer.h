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

namespace GucchiLibrary
{
	/*
	// @class		PrimitiveRenderer �N���X�iSingleton�j
	// @content		�v���~�e�B�u�`��p
	*/
	class PrimitiveRenderer : public SingletonDirector<PrimitiveRenderer>
	{
	private:
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>	primitiveBatch_;
		std::unique_ptr<DirectX::BasicEffect>									basicEffect_;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>								inputLayout_;

		std::list<Primitive*>													primitiveList_;

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
		// @method		DrawPrimitive
		// @content		�v���~�e�B�u�̕`��
		// @param		���_�f�[�^�iVertexPositionColor*�j
		// @param		���_���iint�j
		*/
		void DrawPrimitive(const DirectX::VertexPositionColor* vertices, int vertexCount);

		/*
		// @method		DrawPoint
		// @content		�_�̕`��
		// @param		���_�f�[�^�imap<string, Vector2>�j
		// @param		�F�iColor�j
		*/
		void DrawPoint(std::map<std::string, DirectX::SimpleMath::Vector2> vertex, const DirectX::SimpleMath::Color& color);

		/*
		// @method		DrawLine
		// @content		���̕`��
		// @param		���_�f�[�^�imap<string, Vector2>�j
		// @param		�F�iColor�j
		*/
		void DrawLine(std::map<std::string, DirectX::SimpleMath::Vector2> vertices, const DirectX::SimpleMath::Color& color);

		/*
		// @method		DrawTriangle
		// @content		�O�p�̕`��
		// @param		���_�f�[�^�imap<string, Vector2>�j
		// @param		�F�iColor�j
		*/
		void DrawTriangle(std::map<std::string, DirectX::SimpleMath::Vector2> vertices, const DirectX::SimpleMath::Color& color);

		/*
		// @method		DrawSquare
		// @content		�l�p�̕`��
		// @param		���_�f�[�^�imap<string, Vector2>�j
		// @param		�F�iColor�j
		*/
		void DrawSquare(std::map<std::string, DirectX::SimpleMath::Vector2> vertices, const DirectX::SimpleMath::Color& color);

		/*
		// @method		DrawCircle
		// @content		�~�̕`��
		// @param		���_�f�[�^�imap<string, Vector2>�j
		// @param		�F�iColor�j
		*/
		void DrawCircle(std::map<std::string, DirectX::SimpleMath::Vector2> vertices, const DirectX::SimpleMath::Color& color);

		/*
		// @method		RegisterPrimitive
		// @content		�v���~�e�B�u�̓o�^
		// @param		�o�^����v���~�e�B�u�iPrimitive*�j
		*/
		void RegisterPrimitive(Primitive* primitive);

		/*
		// @method		SetVertices
		// @content		�w�肳�ꂽ���_�����Ƃɒ��_�f�[�^��ݒ�
		// @param		�v���~�e�B�u�^�C�v�iPRIMITIVE_TYPE�j
		// @param		���_�f�[�^�imap<string, Vector2>�j
		// @param		�F�iColor�j
		// @param		���_���iint�j
		// @return		���_�f�[�^�iVertexPositionColor*�j
		*/
		DirectX::VertexPositionColor* SetVertices(Primitive::PRIMITIVE_TYPE type, std::map<std::string, DirectX::SimpleMath::Vector2> vertices, DirectX::SimpleMath::Color color, int vertexNum);

		/*
		// @method		GetNumVertex
		// @content		���_���̎擾
		// @param		���_�f�[�^�imap<string, Vector2>�j
		// @return		���_���iint�j
		*/
		int GetNumVertex(std::map<std::string, DirectX::SimpleMath::Vector2> vertices);

		/*
		// @method		Reset
		// @content		�o�^���ꂽ�v���~�e�B�u�̃��X�g�����Z�b�g
		*/
		void Reset();
	};
}