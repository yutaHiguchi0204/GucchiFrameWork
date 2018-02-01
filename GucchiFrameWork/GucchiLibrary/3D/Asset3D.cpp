/* =====================================================================
//! @param		�uAsset3D�v�\�[�X
//! @create		��� �T��
//! @date		17/11/06
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Asset3D.h"
#include "ObjectRenderer.h"
#include "../Common/Constant.h"
#include "../Common/DebugSwitch.h"
#include "../Common/DeviceResources.h"

// ���O���
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// �ÓI�����o�̒�`
ID3D11BlendState* Asset3D::blendStateSubtractive_;

// �����o�֐��̒�`

// �R���X�g���N�^
Asset3D::Asset3D(const Vector3& trans, const Vector3& scale, const Vector3& rot, const Quaternion& quat, BLEND_MODE mode)
	: camera_(nullptr)
	, scale_(scale)
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
	blendStateSubtractive_ = SetSubtractive();

	// ��ԃX�e�[�g�̏���
	interpolateDirector_ = make_unique<InterpolateDirector>();
}

// �R�s�[�R���X�g���N�^
Asset3D::Asset3D(const Asset3D& asset)
{
	basicEffect_           = asset.basicEffect_;
	inputLayout_           = asset.inputLayout_;
	effectFactory_         = asset.effectFactory_;
	camera_                = asset.camera_;
	scale_                 = asset.scale_;
	rot_                   = asset.rot_;
	quat_                  = asset.quat_;
	trans_                 = asset.trans_;
	world_                 = asset.world_;
	blendStateSubtractive_ = asset.blendStateSubtractive_;
	blendMode_             = asset.blendMode_;
	isActive_              = asset.isActive_;
	isUseQuaternion_       = asset.isUseQuaternion_;
	interpolateDirector_   = make_unique<InterpolateDirector>();
}

/*==============================================================
// @brief		�u�����h�ݒ�
// @param		�u�����h���[�h�iBLEND_MODE�j
// @return		�Ȃ�
===============================================================*/
void Asset3D::SetBlendState(BLEND_MODE mode)
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();
	CommonStates* states = deviceResources.GetCommonStates();

	// �u�����h���[�h�ݒ�
	switch (mode)
	{
	case Asset3D::BLEND_MODE::ALPHA:			// �A���t�@�u�����h
		context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xffffffff);
		break;

	case Asset3D::BLEND_MODE::ADDITIVE:			// ���Z�u�����h
		context->OMSetBlendState(states->Additive(), nullptr, 0xffffffff);
		break;

	case Asset3D::BLEND_MODE::SUBTRACTIVE:		// ���Z�u�����h
		context->OMSetBlendState(blendStateSubtractive_, nullptr, 0xffffffff);
		break;

	default:
		context->OMSetBlendState(states->Opaque(), nullptr, 0xffffffff);
		break;
	}
}

/*==============================================================
// @brief		���Z�`��ݒ�
// @param		�Ȃ�
// @return		���Z�`��p�u�����h�X�e�[�g�iID3D11BlendState*�j
===============================================================*/
ID3D11BlendState* Asset3D::SetSubtractive()
{
	// ���Z�`��p�̃u�����h�X�e�[�g���쐬
	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable					= false;
	desc.IndependentBlendEnable					= false;
	desc.RenderTarget[0].BlendEnable			= true;
	desc.RenderTarget[0].SrcBlend				= D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlend				= D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOp				= D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha			= D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOpAlpha			= D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE_ALL;

	DeviceResources& deviceResources = DeviceResources::GetInstance();

	// �u�����h�X�e�[�g�̍쐬
	ID3D11BlendState* blendState;
	if (FAILED(deviceResources.GetD3DDevice()->CreateBlendState(&desc, &blendState)))
	{
#if defined(MODE_DEBUG)
		OutputDebugString(L"Create blend state is failed.");
#endif
		assert(false);
	}

	return blendState;
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
	SetBlendState(blendMode_);

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