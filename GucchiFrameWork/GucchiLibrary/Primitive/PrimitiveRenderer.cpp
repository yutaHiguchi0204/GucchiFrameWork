/* =====================================================================
//! @param		�uPrimitiveRenderer�v�\�[�X
//! @create		��� �T��
//! @date		17/12/23
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "PrimitiveRenderer.h"
#include "../Common/DeviceResources.h"
#include "System/DebugSystem.h"

// ���O���
using namespace DirectX;
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
	basicEffect_->SetProjection(Matrix::CreateOrthographicOffCenter(static_cast<float>(rect.left), static_cast<float>(rect.right), static_cast<float>(rect.bottom), static_cast<float>(rect.top), 0.1f, 10.0f));
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
		if (primitive->GetActive())
		{
			// �v���~�e�B�u�^�C�v
			Primitive::PRIMITIVE_TYPE type = primitive->GetType();

			// �Q�c�ϊ�
			Primitive2D* primitive2D = dynamic_cast<Primitive2D*>(primitive);

			// �Q�c�`��
			if (primitive2D)
			{
				Draw2D(primitive2D, type);
				continue;
			}

			// �R�c�ϊ�
			Primitive3D* primitive3D = dynamic_cast<Primitive3D*>(primitive);

			// �R�c�`��
			if (primitive3D)
			{
				Draw3D(primitive3D);
			}
		}
	}
}

/*==============================================================
// @brief		�Q�c�p�`�揈��
// @param		�Q�c�v���~�e�B�u�iPrimitive2D*�j�A�v���~�e�B�u�^�C�v�iPRIMITIVE_TYPE�j
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::Draw2D(Primitive2D* primitive, Primitive::PRIMITIVE_TYPE type)
{
	// POINT3D��SEGMENT�̏ꍇ�̓r���[�s��ƃv���W�F�N�V�����s��ɃJ������ݒ肷��
	if (type == Primitive::PRIMITIVE_TYPE::POINT3D || type == Primitive::PRIMITIVE_TYPE::SEGMENT)
	{
		basicEffect_->SetView(camera_->GetView());
		basicEffect_->SetProjection(camera_->GetProjection());
	}
	else
	{
		// ��ʃT�C�Y���擾
		RECT rect = DeviceResources::GetInstance().GetOutputSize();

		basicEffect_->SetView(Matrix::CreateLookAt(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0)));
		basicEffect_->SetProjection(Matrix::CreateOrthographicOffCenter(static_cast<float>(rect.left), static_cast<float>(rect.right), static_cast<float>(rect.bottom), static_cast<float>(rect.top), 0.1f, 10.0f));
	}

	// �h��Ԃ��w��̏ꍇ�A�e��p�`��֐��ŕ`��
	if (primitive->isFill_)
	{
		switch (type)
		{
		case Primitive::PRIMITIVE_TYPE::POINT:			// �_
		case Primitive::PRIMITIVE_TYPE::POINT3D:		// �_
			DrawPoint(primitive->vertices_);
			break;

		case Primitive::PRIMITIVE_TYPE::LINE:			// ��
		case Primitive::PRIMITIVE_TYPE::SEGMENT:		// ����
			DrawSegment(primitive->vertices_);
			break;

		case Primitive::PRIMITIVE_TYPE::TRIANGLE:		// �O�p
			DrawTriangle(primitive->vertices_);
			break;

		case Primitive::PRIMITIVE_TYPE::RECTANGLE:		// �l�p
			DrawRectangle(primitive->vertices_);
			break;

		case Primitive::PRIMITIVE_TYPE::CIRCLE:			// �~
			Circle* circle = dynamic_cast<Circle*>(primitive);
			DrawCircle(circle->vertices_, circle->div_);
			break;
		}

		return;
	}

	// ���_�f�[�^���܂Ƃ߂�
	VertexPositionColor* v = GetVerticesArray(primitive);

	// �v���~�e�B�u�̕`��
	DrawPrimitive(v, primitive->vertices_.size());

	// �f�[�^�̉��
	delete[] v;
}

/*==============================================================
// @brief		�R�c�p�`�揈��
// @param		�R�c�v���~�e�B�u�iPrimitive3D*�j
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::Draw3D(Primitive3D* primitive)
{
	// �s�񐶐�
	Matrix world = Matrix::Identity;
	Matrix view = camera_->GetView();
	Matrix proj = camera_->GetProjection();

	// �v���~�e�B�u�̕`��
	//primitive->geometry_->Draw(world, view, proj, primitive->color_, nullptr, !primitive->isFill_);
}

/*==============================================================
// @brief		�`��p�ɂ܂Ƃ߂�ꂽ���_�f�[�^�̔z����擾
// @param		�v���~�e�B�u�iPrimitive2D*�j
// @return		���_�f�[�^�z��iVertexPositionColor*�j
===============================================================*/
VertexPositionColor* PrimitiveRenderer::GetVerticesArray(Primitive2D* primitive)
{
	VertexPositionColor* v = new VertexPositionColor[primitive->vertices_.size()];

	// ���_�f�[�^�z��̍쐬
	if (primitive->GetType() == Primitive::PRIMITIVE_TYPE::CIRCLE)
	{
		Circle* circle = dynamic_cast<Circle*>(primitive);
		for (int i = 0; i < circle->div_; i++)
		{
			string key = "Rad" + to_string(i / 10) + to_string(i % 10);
			v[i] = circle->vertices_[key];
		}
		v[circle->div_] = v[0];
	}
	else
	{
		int i = 0;
		for (auto& vertex : primitive->vertices_)
		{
			v[i] = vertex.second;
			i++;
		}
	}

	return v;
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
// @param		���_�f�[�^�imap<string, VertexPositionColor>�j
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::DrawPoint(map<string, VertexPositionColor> vertices)
{
	primitiveBatch_->Begin();
	primitiveBatch_->Draw(D3D_PRIMITIVE_TOPOLOGY_POINTLIST, &vertices["point"], 1);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		�����̕`��
// @param		���_�f�[�^�imap<string, VertexPositionColor>�j
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::DrawSegment(map<string, VertexPositionColor> vertices)
{
	primitiveBatch_->Begin();
	primitiveBatch_->DrawLine(vertices["start"], vertices["end"]);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		�O�p�̕`��
// @param		���_�f�[�^�imap<string, VertexPositionColor>�j
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::DrawTriangle(map<string, VertexPositionColor> vertices)
{
	primitiveBatch_->Begin();
	primitiveBatch_->DrawTriangle(vertices["p0"], vertices["p1"], vertices["p2"]);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		�l�p�̕`��
// @param		���_�f�[�^�imap<string, VertexPositionColor>�j
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::DrawRectangle(map<string, VertexPositionColor> vertices)
{
	primitiveBatch_->Begin();
	primitiveBatch_->DrawQuad(vertices["p0"], vertices["p1"], vertices["p2"], vertices["p3"]);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		�~�̕`��
// @param		���_�f�[�^�imap<string, VertexPositionColor>�j�A�������iint�j
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::DrawCircle(map<string, VertexPositionColor> vertices, int div)
{
	// �C���f�b�N�X�f�[�^�̐ݒ�
	uint16_t* indices = new uint16_t[div * 3];
	for (int i = 0; i < div; i++)
	{
		indices[i * 3 + 0] = div;
		indices[i * 3 + 1] = i;
		indices[i * 3 + 2] = i + 1;
	}
	indices[(div - 1) * 3 + 2] = 0;

	// �`��p���_�f�[�^�̐ݒ�
	VertexPositionColor* v = new VertexPositionColor[div + 1];

	// ���_���W����U�S�Ē��S�_�̍��W�Őݒ�
	for (int i = 0; i < div + 1; i++)
	{
		v[i].position = vertices["center"].position;
		v[i].color = vertices["center"].color;
	}

	// �~�̊O�������炷
	for (int i = 0; i < div; i++)
	{
		string key = "Rad" + to_string(i / 10) + to_string(i % 10);
		v[i].position.x += vertices[key].position.x - vertices["center"].position.x;
		v[i].position.y += vertices[key].position.y - vertices["center"].position.y;
	}

	// �`��
	primitiveBatch_->Begin();
	primitiveBatch_->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, indices, div * 3, v, div + 1);
	primitiveBatch_->End();

	// �f�[�^�̉��
	delete[] v;
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
// @brief		�v���~�e�B�u�̉��
// @param		�v���~�e�B�u�iPrimitive*�j
// @return		�Ȃ�
===============================================================*/
void PrimitiveRenderer::DisposePrimitive(Primitive* primitive)
{
	primitiveList_.remove(primitive);
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

/*==============================================================
// @brief		�_�v���~�e�B�u�̐���
// @param		���W�iVector2�j�A�F�iColor�j
// @return		�v���~�e�B�u�iunique_ptr<Primitive>�j
===============================================================*/
unique_ptr<Primitive> PrimitiveFactory::CreatePoint(const Vector2& point, const Color& color)
{
	unique_ptr<Primitive> primitive = CreatePoint(Vector3(point.x, point.y, 0), color);

	// �v���~�e�B�u�^�C�v��"�_"�ɐݒ�
	primitive->SetType(Primitive::PRIMITIVE_TYPE::POINT);

	return primitive;
}

/*==============================================================
// @brief		�_�v���~�e�B�u�̐���
// @param		���W�iVector3�j�A�F�iColor�j
// @return		�v���~�e�B�u�iunique_ptr<Primitive>�j
===============================================================*/
unique_ptr<Primitive> PrimitiveFactory::CreatePoint(const Vector3& point, const Color& color)
{
	unique_ptr<Primitive2D> primitive = make_unique<Primitive2D>();

	// �ʒu�ݒ�
	primitive->vertices_["point"].position = point;

	// �F�ݒ�
	primitive->vertices_["point"].color = color;

	// �v���~�e�B�u�^�C�v��"�_"�ɐݒ�
	primitive->SetType(Primitive::PRIMITIVE_TYPE::POINT3D);

	return move(primitive);
}

/*==============================================================
// @brief		�����v���~�e�B�u�̐���
// @param		�n�_�iVector2�j�A�I�_�iVector2�j�A�F�iColor�j
// @return		�v���~�e�B�u�iunique_ptr<Primitive>�j
===============================================================*/
unique_ptr<Primitive> PrimitiveFactory::CreateSegment(const Vector2& start, const Vector2& end, const Color& color)
{
	unique_ptr<Primitive> primitive = CreateSegment(Vector3(start.x, start.y, 0), Vector3(end.x, end.y, 0), color);

	// �v���~�e�B�u�^�C�v��"�_"�ɐݒ�
	primitive->SetType(Primitive::PRIMITIVE_TYPE::LINE);

	return primitive;
}

/*==============================================================
// @brief		�����v���~�e�B�u�̐���
// @param		�n�_�iVector3�j�A�I�_�iVector3�j�A�F�iColor�j
// @return		�v���~�e�B�u�iunique_ptr<Primitive>�j
===============================================================*/
unique_ptr<Primitive> PrimitiveFactory::CreateSegment(const Vector3& start, const Vector3& end, const Color& color)
{
	unique_ptr<Primitive2D> primitive = make_unique<Primitive2D>();

	// �ʒu�ݒ�
	primitive->vertices_["start"].position = start;
	primitive->vertices_["end"].position = end;

	// �F�ݒ�
	for (auto& vertex : primitive->vertices_)
	{
		vertex.second.color = color;
	}

	// �v���~�e�B�u�^�C�v��"��"�ɐݒ�
	primitive->SetType(Primitive::PRIMITIVE_TYPE::SEGMENT);

	return move(primitive);
}

/*==============================================================
// @brief		�O�p�v���~�e�B�u�̐���
// @param		�P�_�ځiVector2�j�A�Q�_�ځiVector2�j�A�R�_�ځiVector2�j�A�F�iColor�j�A�h��Ԃ����ǂ����ibool�j
// @return		�v���~�e�B�u�iunique_ptr<Primitive>�j
===============================================================*/
unique_ptr<Primitive> PrimitiveFactory::CreateTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color, bool isFill)
{
	unique_ptr<Primitive2D> primitive = make_unique<Primitive2D>();

	// �ʒu�ݒ�
	primitive->vertices_["p0"].position = Vector3(p1.x, p1.y, 0);
	primitive->vertices_["p1"].position = Vector3(p2.x, p2.y, 0);
	primitive->vertices_["p2"].position = Vector3(p3.x, p3.y, 0);

	// �F�ݒ�
	for (auto& vertex : primitive->vertices_)
	{
		vertex.second.color = color;
	}

	// �h��Ԃ����Ȃ��ꍇ�̏���
	primitive->isFill_ = isFill;
	if (!isFill)
	{
		// �n�_�i�P�_�ځj�ɖ߂�
		primitive->vertices_["p3"] = primitive->vertices_["p0"];
	}

	// �v���~�e�B�u�^�C�v��"�O�p"�ɐݒ�
	primitive->SetType(Primitive::PRIMITIVE_TYPE::TRIANGLE);

	return move(primitive);
}

/*==============================================================
// @brief		�����`�v���~�e�B�u�̐���
// @param		������W�iVector2�j�A�E����W�iVector2�j�A�F�iColor�j�A�h��Ԃ����ǂ����ibool�j
// @return		�v���~�e�B�u�iunique_ptr<Primitive>�j
===============================================================*/
unique_ptr<Primitive> PrimitiveFactory::CreateRectangle(const Vector2& topLeft, const Vector2& bottomRight, const Color& color, bool isFill)
{
	unique_ptr<Primitive2D> primitive = make_unique<Primitive2D>();

	// �ʒu�ݒ�
	primitive->vertices_["p0"].position = Vector3(topLeft.x, topLeft.y, 0);
	primitive->vertices_["p1"].position = Vector3(bottomRight.x, topLeft.y, 0);
	primitive->vertices_["p2"].position = Vector3(bottomRight.x, bottomRight.y, 0);
	primitive->vertices_["p3"].position = Vector3(topLeft.x, bottomRight.y, 0);

	// �F�ݒ�
	for (auto& vertex : primitive->vertices_)
	{
		vertex.second.color = color;
	}

	// �h��Ԃ����Ȃ��ꍇ�̏���
	primitive->isFill_ = isFill;
	if (!isFill)
	{
		// �n�_�i�P�_�ځj�ɖ߂�
		primitive->vertices_["p4"] = primitive->vertices_["p0"];
	}

	// �v���~�e�B�u�^�C�v��"�����`"�ɐݒ�
	primitive->SetType(Primitive::PRIMITIVE_TYPE::RECTANGLE);

	return move(primitive);
}

/*==============================================================
// @brief		�����̃v���~�e�B�u�̐���
// @param		�T�C�Y�iVector3�j�A�F�iColor�j�A�h��Ԃ����ǂ����ibool�j
// @return		�v���~�e�B�u�iunique_ptr<Primitive3D>�j
===============================================================*/
unique_ptr<Primitive3D> PrimitiveFactory::CreateBox(const Vector3& size, const Color& color, bool isFill)
{
	unique_ptr<Primitive3D> primitive = make_unique<Primitive3D>();

	// �R���e�L�X�g
	ID3D11DeviceContext* context = DeviceResources::GetInstance().GetD3DDeviceContext();

	// ���v���~�e�B�u�̓o�^
	primitive->geometry_ = GeometricPrimitive::CreateBox(context, size);

	// �F�ݒ�
	primitive->color_ = color;

	// �h��Ԃ����ǂ���
	primitive->isFill_ = isFill;

	// �v���~�e�B�u�^�C�v��"������"�ɐݒ�
	primitive->SetType(Primitive::PRIMITIVE_TYPE::BOX);

	return primitive;
}

/*==============================================================
// @brief		�~�v���~�e�B�u�̐���
// @param		���S���W�iVector2�j�A���a�ifloat�j�A�������iint�j�A�F�iColor�j�A�h��Ԃ����ǂ����ibool�j
// @return		�v���~�e�B�u�iunique_ptr<Primitive>�j
===============================================================*/
unique_ptr<Primitive> PrimitiveFactory::CreateCircle(const Vector2& center, float radius, int div, const Color& color, bool isFill)
{
	unique_ptr<Circle> primitive = make_unique<Circle>();

	// ���S���W��ۑ�
	primitive->vertices_["center"].position = Vector3(center.x, center.y, 0);

	// ���a�ƕ�������ݒ�
	primitive->radius_ = radius;
	primitive->div_ = div;

	// ���_�f�[�^�̐ݒ�
	string key;
	for (int i = 0; i < div; i++)
	{
		key = "Rad" + to_string(i / 10) + to_string(i % 10);
		primitive->vertices_[key].position.x = center.x + cosf(XM_2PI / div * i) * radius;
		primitive->vertices_[key].position.y = center.y + sinf(XM_2PI / div * i) * radius;
	}
	key = "Rad" + to_string(div / 10) + to_string(div % 10);
	primitive->vertices_[key] = primitive->vertices_["Rad00"];

	// �F�ݒ�
	for (auto& vertex : primitive->vertices_)
	{
		vertex.second.color = color;
	}

	// �h��Ԃ����Ȃ��ꍇ�̏���
	primitive->isFill_ = isFill;

	// �v���~�e�B�u�^�C�v��"�~"�ɐݒ�
	primitive->SetType(Primitive::PRIMITIVE_TYPE::CIRCLE);

	return move(primitive);
}

/*==============================================================
// @brief		���v���~�e�B�u�̐���
// @param		���a�ifloat�j�A�������iint�j�A�F�iColor�j�A�h��Ԃ����ǂ����ibool�j
// @return		�v���~�e�B�u�iunique_ptr<Primitive3D>�j
===============================================================*/
unique_ptr<Primitive3D> PrimitiveFactory::CreateSphere(float diameter, int div, const Color& color, bool isFill)
{
	unique_ptr<Primitive3D> primitive = make_unique<Primitive3D>();

	// �R���e�L�X�g
	ID3D11DeviceContext* context = DeviceResources::GetInstance().GetD3DDeviceContext();

	// ���v���~�e�B�u�̓o�^
	//primitive->geometry_ = GeometricPrimitive::CreateSphere(context, diameter, div);

	// �F�ݒ�
	primitive->color_ = color;

	// �h��Ԃ����ǂ���
	primitive->isFill_ = isFill;

	// �v���~�e�B�u�^�C�v��"��"�ɐݒ�
	primitive->SetType(Primitive::PRIMITIVE_TYPE::SPHERE);

	return primitive;
}