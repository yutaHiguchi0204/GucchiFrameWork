/* =====================================================================
//! @param		�uPrimitiveRenderer�v�\�[�X
//! @create		��� �T��
//! @date		17/12/23
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "PrimitiveRenderer.h"
#include <vector>
#include "../Common/DeviceResources.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

/*==============================================================
// @brief		����������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::Initialize()
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	ID3D11Device* device = deviceResources.GetD3DDevice();
	ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();

	// �v���~�e�B�u�o�b�`�̐ݒ�
	primitiveBatch_ = make_unique<PrimitiveBatch<VertexPositionColor>>(context);

	// �G�t�F�N�g�̐ݒ�
	basicEffect_ = std::make_unique<BasicEffect>(device);

	// ���_�J���[�̗L����
	basicEffect_->SetVertexColorEnabled(true);

	// �V�F�[�_����
	void const* shaderByteCode;
	size_t byteCodeLength;

	// �`��ݒ�����ɓK�؂ȃV�F�[�_���擾
	basicEffect_->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	// ���̓��C�A�E�g���쐬
	device->CreateInputLayout(VertexPositionColor::InputElements, VertexPositionColor::InputElementCount, shaderByteCode, byteCodeLength, inputLayout_.ReleaseAndGetAddressOf());

	// ��ʃT�C�Y���擾
	RECT rect = DeviceResources::GetInstance().GetOutputSize();

	// �e��ϊ��s����Z�b�g
	basicEffect_->SetWorld(Matrix::Identity);
	basicEffect_->SetView(Matrix::CreateLookAt(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0)));
	basicEffect_->SetProjection(Matrix::CreateOrthographicOffCenter((float)rect.left, (float)rect.right, (float)rect.bottom, (float)rect.top, 0.1f, 10.0f));
}

/*==============================================================
// @brief		�`�揈��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::Draw()
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();
	CommonStates* states = deviceResources.GetCommonStates();

	// �[�x�X�e���V���̐ݒ�
	context->OMSetDepthStencilState(states->DepthNone(), 0);

	// �u�����h�X�e�[�g�̐ݒ�
	context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xffffffff);

	// �J�����O�ݒ�
	context->RSSetState(states->CullNone());

	// ���̓��C�A�E�g���Z�b�g
	context->IASetInputLayout(inputLayout_.Get());

	// �G�t�F�N�g�̓K�p
	basicEffect_->Apply(context);

	// �`�揈��
	for (auto& primitive : primitiveList_)
	{
		// �v���~�e�B�u�^�C�v
		Primitive::PRIMITIVE_TYPE type = primitive->GetType();

		// �h��Ԃ��w��̏ꍇ�A�e��p�`��֐��ŕ`��
		if (primitive->GetFillFlag())
		{
			switch (type)
			{
			case Primitive::PRIMITIVE_TYPE::POINT:			// �_
				DrawPoint(primitive->GetPoints(), primitive->GetColor());
				break;

			case Primitive::PRIMITIVE_TYPE::LINE:			// ��
				DrawLine(primitive->GetPoints(), primitive->GetColor());
				break;

			case Primitive::PRIMITIVE_TYPE::TRIANGLE:		// �O�p
				DrawTriangle(primitive->GetPoints(), primitive->GetColor());
				break;

			case Primitive::PRIMITIVE_TYPE::SQUARE:			// �l�p
				DrawSquare(primitive->GetPoints(), primitive->GetColor());
				break;

			case Primitive::PRIMITIVE_TYPE::CIRCLE:			// �~
				DrawCircle(primitive->GetPoints(), primitive->GetColor());
				break;
			}

			continue;
		}

		// ���_���̎擾
		int vertexNum = GetNumVertex(primitive->GetPoints());

		// �~�̏ꍇ�͒��_����[������+1]�ɂ���
		if (type == Primitive::PRIMITIVE_TYPE::CIRCLE)
		{
			vertexNum = (int)(primitive->GetPoints()["rad&div"].y) + 1;
		}

		// ���_�f�[�^�̐ݒ�
		VertexPositionColor* vertices = SetVertices(type, primitive->GetPoints(), primitive->GetColor(), vertexNum);

		// �v���~�e�B�u�̕`��
		DrawPrimitive(vertices, vertexNum);

		// �v���~�e�B�u�̉��
		delete vertices;
	}
}

/*==============================================================
// @brief		�v���~�e�B�u�̕`��
// @param		���_�f�[�^�iVertexPositionColor*�j�A���_���iint�j
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::DrawPrimitive(const VertexPositionColor* vertices, int vertexCount)
{
	primitiveBatch_->Begin();
	primitiveBatch_->Draw(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP, vertices, vertexCount);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		�_�̕`��
// @param		���_�f�[�^�iVertexPositionColor*�j�A�F�iColor�j
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::DrawPoint(map<string, Vector2> vertex, const Color& color)
{
	VertexPositionColor point;

	// �ʒu�ݒ�
	point.position = Vector3(vertex["point"].x, vertex["point"].y, 0);

	// �F�ݒ�
	point.color = color;

	// �`��
	primitiveBatch_->Begin();
	primitiveBatch_->Draw(D3D_PRIMITIVE_TOPOLOGY_POINTLIST, &point, 1);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		���̕`��
// @param		���_�f�[�^�iVertexPositionColor*�j�A�F�iColor�j
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::DrawLine(map<string, Vector2> vertices, const Color& color)
{
	VertexPositionColor start, end;

	// �ʒu�ݒ�
	start.position = Vector3(vertices["start"].x, vertices["start"].y, 0);
	end.position = Vector3(vertices["end"].x, vertices["end"].y, 0);

	// �F�ݒ�
	start.color = color;
	end.color = color;

	// �`��
	primitiveBatch_->Begin();
	primitiveBatch_->DrawLine(start, end);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		�O�p�̕`��
// @param		���_�f�[�^�iVertexPositionColor*�j�A�F�iColor�j
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::DrawTriangle(map<string, Vector2> vertices, const Color& color)
{
	VertexPositionColor p1, p2, p3;

	// �ʒu�ݒ�
	p1.position = Vector3(vertices["p1"].x, vertices["p1"].y, 0);
	p2.position = Vector3(vertices["p2"].x, vertices["p2"].y, 0);
	p3.position = Vector3(vertices["p3"].x, vertices["p3"].y, 0);

	// �F�ݒ�
	p1.color = color;
	p2.color = color;
	p3.color = color;

	// �`��
	primitiveBatch_->Begin();
	primitiveBatch_->DrawTriangle(p1, p2, p3);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		�l�p�̕`��
// @param		���_�f�[�^�iVertexPositionColor*�j�A�F�iColor�j
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::DrawSquare(map<string, Vector2> vertices, const Color& color)
{
	VertexPositionColor tl, tr, bl, br;

	// �ʒu�ݒ�
	tl.position = Vector3(vertices["topLeft"].x, vertices["topLeft"].y, 0);
	tr.position = Vector3(vertices["topRight"].x, vertices["topRight"].y, 0);
	bl.position = Vector3(vertices["bottomLeft"].x, vertices["bottomLeft"].y, 0);
	br.position = Vector3(vertices["bottomRight"].x, vertices["bottomRight"].y, 0);

	// �F�ݒ�
	tl.color = color;
	tr.color = color;
	bl.color = color;
	br.color = color;

	// �`��
	primitiveBatch_->Begin();
	primitiveBatch_->DrawQuad(tl, tr, br, bl);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		�~�̕`��
// @param		���_�f�[�^�iVertexPositionColor*�j�A�F�iColor�j
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::DrawCircle(map<string, Vector2> vertices, const Color& color)
{
	// ������
	const int div = (int)vertices["rad&div"].y;

	// ���S���W
	Vector3 center3D = Vector3(vertices["center"].x, vertices["center"].y, 0);

	// �C���f�b�N�X�f�[�^����
	uint16_t* indices = new uint16_t[div * 3];
	VertexPositionColor* v = new VertexPositionColor[div + 1];

	// �C���f�b�N�X�f�[�^�̐ݒ�
	for (int i = 0; i < div; i++)
	{
		indices[i * 3 + 0] = div;
		indices[i * 3 + 1] = i;
		indices[i * 3 + 2] = i + 1;
	}
	indices[(div - 1) * 3 + 2] = 0;

	// ���_���W����U�S�Ē��S�_�̍��W�Őݒ�
	for (int i = 0; i < div + 1; i++)
	{
		v[i].position = center3D;
		v[i].color = color;
	}

	// �~�̊O�������炷
	for (int i = 0; i < div; i++)
	{
		string key = "Rad" + to_string(i);
		v[i].position.x += vertices[key].x - vertices["center"].x;
		v[i].position.y += vertices[key].y - vertices["center"].y;
	}

	// �`��
	primitiveBatch_->Begin();
	primitiveBatch_->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, indices, div * 3, v, div + 1);
	primitiveBatch_->End();

	// �f�[�^�̉��
	delete indices;
	delete v;
}

/*==============================================================
// @brief		�v���~�e�B�u�̓o�^
// @param		�v���~�e�B�u�iPrimitive*�j
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::RegisterPrimitive(Primitive* primitive)
{
	primitiveList_.emplace_back(primitive);
}

/*==============================================================
// @brief		�w�肳�ꂽ���_�����Ƃɒ��_�f�[�^��ݒ�
// @param		�v���~�e�B�u�^�C�v�iPRIMITIVE_TYPE�j�A���_�f�[�^�imap<string, Vector2>�j�A�F�iColor�j�A���_���iint�j
// @return		���_�f�[�^�iVertexPositionColor*�j
===============================================================*/
VertexPositionColor* PrimitiveRenderer::SetVertices(Primitive::PRIMITIVE_TYPE type, map<string, Vector2> vertices, Color color, int vertexNum)
{
	VertexPositionColor* vertex = new VertexPositionColor[vertexNum];

	// �F�̐ݒ�
	for (int i = 0; i < vertexNum; i++)
	{
		vertex[i].color = color;
	}

	// ���_�f�[�^�̐ݒ�
	switch (type)
	{
	case Primitive::PRIMITIVE_TYPE::TRIANGLE:		// �O�p
		vertex[0].position = Vector3(vertices["p1"].x, vertices["p1"].y, 0);
		vertex[1].position = Vector3(vertices["p2"].x, vertices["p2"].y, 0);
		vertex[2].position = Vector3(vertices["p3"].x, vertices["p3"].y, 0);
		vertex[3].position = vertex[0].position;

		return vertex;
		break;

	case Primitive::PRIMITIVE_TYPE::SQUARE:			// �l�p
		vertex[0].position = Vector3(vertices["topLeft"].x, vertices["topLeft"].y, 0);
		vertex[1].position = Vector3(vertices["bottomRight"].x, vertices["topLeft"].y, 0);
		vertex[2].position = Vector3(vertices["bottomRight"].x, vertices["bottomRight"].y, 0);
		vertex[3].position = Vector3(vertices["topLeft"].x, vertices["bottomRight"].y, 0);
		vertex[4].position = vertex[0].position;

		return vertex;
		break;

	case Primitive::PRIMITIVE_TYPE::CIRCLE:			// �~
		for (int i = 0; i < vertexNum - 1; i++)
		{
			string key = "Rad" + to_string(i);
			vertex[i].position = Vector3(vertices[key].x, vertices[key].y, 0);
		}
		vertex[vertexNum - 1].position = vertex[0].position;

		return vertex;
		break;

	default:
		break;
	}

	// �����ɂ͂��Ȃ�
	return nullptr;
}

/*==============================================================
// @brief		���_���̎擾
// @param		���_�f�[�^�imap<string, Vector2>�j
// @return		���_���iint�j
===============================================================*/
int PrimitiveRenderer::GetNumVertex(map<string, Vector2> vertices)
{
	return vertices.size() + 1;
}

/*==============================================================
// @brief		���X�g���Z�b�g
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::Reset()
{
	primitiveList_.clear();
}