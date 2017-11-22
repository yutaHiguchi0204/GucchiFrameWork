/* =====================================================================
//! @param		�uAsset3D�v�\�[�X
//! @create		��� �T��
//! @date		17/11/06
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Asset3D.h"
#include "ObjectRenderer.h"
#include "../Common/Constant.h"
#include "../Common/DeviceResources.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

// �R���X�g���N�^
Asset3D::Asset3D(const Vector3& trans, const Vector3& scale, const Vector3& rot, const Quaternion& quat, BLEND_MODE mode)
	: scale_(scale)
	, rot_(rot)
	, quat_(quat)
	, trans_(trans)
	, world_(Matrix::Identity)
	, blendMode_(mode)
	, isActive_(true)
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();

	// �G�t�F�N�g�쐬
	basicEffect_ = make_shared<BasicEffect>(deviceResources.GetD3DDevice());
	basicEffect_->SetVertexColorEnabled(true);

	// �V�F�[�_�̎擾
	void const* shaderByteCode;
	size_t byteCodeLength;
	basicEffect_->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	// ���̓��C�A�E�g�̐ݒ�
	deviceResources.GetD3DDevice()->CreateInputLayout(
		VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode,
		byteCodeLength,
		inputLayout_.GetAddressOf()
	);

	// �G�t�F�N�g�t�@�N�g���̍쐬
	effectFactory_ = make_shared<EffectFactory>(deviceResources.GetD3DDevice());

	// �e�N�X�`���ǂݎ��p�X��ݒ�
	effectFactory_->SetDirectory(FILE_PATH_MODEL.c_str());

	// ���Z�`��ݒ�
	ObjectRenderer& objectRenderer = ObjectRenderer::GetInstance();
	objectRenderer.SetSubtractive(blendStateSubtract_);
}

/*==============================================================
// @brief		�`��O�̏���
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void Asset3D::DrawApply()
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();
	CommonStates* states = deviceResources.GetCommonStates();

	// �u�����h���[�h�ݒ�
	ObjectRenderer& objectRenderer = ObjectRenderer::GetInstance();
	objectRenderer.SetBlendState(blendMode_);

	// �[�x�X�e���V�����X�V���Ȃ�
	context->OMSetDepthStencilState(states->DepthRead(), 0);

	// �`��ݒ�
	context->RSSetState(states->CullNone());

	// �s��̐ݒ�
	basicEffect_->SetWorld(world_);
	basicEffect_->SetView(camera_->GetView());
	basicEffect_->SetProjection(camera_->GetProjection());

	// �G�t�F�N�g�̎��s
	basicEffect_->Apply(context);

	// ���̓��C�A�E�g�̐ݒ�
	context->IASetInputLayout(inputLayout_.Get());
}