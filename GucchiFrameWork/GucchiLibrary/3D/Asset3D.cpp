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

// �ÓI�����o�̒�`
ID3D11BlendState* Asset3D::blendStateSubtract_;

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
	, isUseQuaternion_(false)
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
	blendStateSubtract_ = objectRenderer.SetSubtractive();

	// ��ԃX�e�[�g�̏���
	interpolateDirector_ = make_unique<InterpolateDirector>();
}

// �R�s�[�R���X�g���N�^
Asset3D::Asset3D(const Asset3D& asset)
{
	basicEffect_         = asset.basicEffect_;
	inputLayout_         = asset.inputLayout_;
	effectFactory_       = asset.effectFactory_;
	camera_              = asset.camera_;
	scale_               = asset.scale_;
	rot_                 = asset.rot_;
	quat_                = asset.quat_;
	trans_               = asset.trans_;
	world_               = asset.world_;
	blendStateSubtract_  = asset.blendStateSubtract_;
	blendMode_           = asset.blendMode_;
	isActive_            = asset.isActive_;
	isUseQuaternion_     = asset.isUseQuaternion_;
	interpolateDirector_ = make_unique<InterpolateDirector>();
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void Asset3D::Update()
{
	// ��ԃX�e�[�g�̍X�V
	interpolateDirector_->Update();

	// �X�P�[�����O�s��̌v�Z
	Matrix scaleMat = Matrix::CreateScale(scale_);

	// ��]�s��̌v�Z
	Matrix rotMat = Matrix::Identity;
	if (isUseQuaternion_)
	{
		// �N�H�[�^�j�I���Ōv�Z
		rotMat = Matrix::CreateFromQuaternion(quat_);
	}
	else
	{
		// �I�C���[�p�Ōv�Z
		rotMat = Matrix::CreateFromYawPitchRoll(rot_.y, rot_.x, rot_.z);
	}

	// ���s�ړ��s��̌v�Z
	Matrix transMat = Matrix::CreateTranslation(trans_);

	// ���[���h�s��̌v�Z
	world_ = scaleMat * rotMat * transMat;
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