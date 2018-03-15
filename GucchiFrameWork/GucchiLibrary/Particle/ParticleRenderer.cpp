/* =====================================================================
//! @param		�uParticleRenderer�v�\�[�X
//! @create		��� �T��
//! @date		17/12/26
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "ParticleRenderer.h"
#include "../Common/Constant.h"
#include "../Common/DeviceResources.h"
#include "../System/DebugSystem.h"
#include "../Utility/BinaryFileManager.h"

// ���O���
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// �ÓI�����o�̒�`
const vector<D3D11_INPUT_ELEMENT_DESC> ParticleRenderer::INPUT_LAYOUT = {		// ���̓��C�A�E�g
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,									D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, sizeof(Vector3),						D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, sizeof(Vector3) + sizeof(Vector4),	D3D11_INPUT_PER_VERTEX_DATA, 0 }
};
const int ParticleRenderer::MAX_PARTICLE = 32768;								// �p�[�e�B�N���̍ő吔

// �����o�֐��̒�`

/*==============================================================
// @brief		����������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void ParticleRenderer::Initialize()
{
	DeviceResources& deviceResources	= DeviceResources::GetInstance();
	ID3D11Device* device				= deviceResources.GetD3DDevice();
	ID3D11DeviceContext* context		= deviceResources.GetD3DDeviceContext();

	// �t�@�C��
	const wstring SHADER_DIRECTORY = L"Resources/Shaders/";
	const wstring FILE_VS = SHADER_DIRECTORY + L"ParticleVertexShader"		+ EXT_CSO;
	const wstring FILE_GS = SHADER_DIRECTORY + L"ParticleGeometryShader"	+ EXT_CSO;
	const wstring FILE_PS = SHADER_DIRECTORY + L"ParticlePixelShader"		+ EXT_CSO;

	// �V�F�[�_�t�@�C���̓ǂݍ���
	BinaryFile shaderVS = BinaryFileManager::LoadBinaryFile(FILE_VS);
	BinaryFile shaderGS = BinaryFileManager::LoadBinaryFile(FILE_GS);
	BinaryFile shaderPS = BinaryFileManager::LoadBinaryFile(FILE_PS);

	// ���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(shaderVS.GetData(), shaderVS.GetSize(), NULL, vertexShader_.ReleaseAndGetAddressOf())))
	{
		DebugSystem::DebugLog(L"CreateVertexShader Failed.", true);
		return;
	}

	// �W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(shaderGS.GetData(), shaderGS.GetSize(), NULL, geometryShader_.ReleaseAndGetAddressOf())))
	{
		DebugSystem::DebugLog(L"CreateGeometryShader Failed.", true);
		return;
	}

	// �s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(shaderPS.GetData(), shaderPS.GetSize(), NULL, pixelShader_.ReleaseAndGetAddressOf())))
	{
		DebugSystem::DebugLog(L"CreatePixelShader Failed.", true);
		return;
	}

	// �v���~�e�B�u�o�b�`�쐬
	primitiveBatch_ = make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context, 1, MAX_PARTICLE);

	// ���_�t�H�[�}�b�g���w�肵�ē��̓��C�A�E�g���쐬
	device->CreateInputLayout(
		&INPUT_LAYOUT[0],
		INPUT_LAYOUT.size(),
		shaderVS.GetData(),
		shaderVS.GetSize(),
		inputLayout_.GetAddressOf()
	);

	// �R���X�^���g�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC cBuffer;
	cBuffer.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	cBuffer.ByteWidth			= sizeof(Constants);
	cBuffer.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
	cBuffer.MiscFlags			= 0;
	cBuffer.StructureByteStride = 0;
	cBuffer.Usage				= D3D11_USAGE_DYNAMIC;

	// �R���X�^���g�o�b�t�@�̍쐬
	if (FAILED(device->CreateBuffer(&cBuffer, nullptr, cBuffer_.ReleaseAndGetAddressOf())))
	{
		DebugSystem::DebugLog(L"CreateBuffer Failed.", true);
		return;
	}

	// �e�N�X�`���T���v���[�̐ݒ�
	D3D11_SAMPLER_DESC sampler;
	ZeroMemory(&sampler, sizeof(sampler));				// �[���N���A
	sampler.Filter		= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler.AddressU	= D3D11_TEXTURE_ADDRESS_WRAP;
	sampler.AddressV	= D3D11_TEXTURE_ADDRESS_WRAP;
	sampler.AddressW	= D3D11_TEXTURE_ADDRESS_WRAP;

	// �e�N�X�`���T���v���[�̍쐬
	if (FAILED(device->CreateSamplerState(&sampler, sampler_.ReleaseAndGetAddressOf())))
	{
		DebugSystem::DebugLog(L"Create sampler state failed.", true);
		return;
	}
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void ParticleRenderer::Update()
{
	// ���݂��Ă��Ȃ��G�~�b�^�[�̓��X�g�������
	for (auto& emitter : emitter_)
	{
		if (emitter.second && !emitter.second->IsExist())
		{
			DisposeEmitter(emitter.first);
		}
	}

	// �G�~�b�^�[�X�V
	for (auto& emitter : emitter_)
	{
		if (emitter.second && emitter.second->GetActive())
		{
			emitter.second->Update();
		}
	}
}

/*==============================================================
// @brief		�`�揈��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void ParticleRenderer::Draw()
{
	DeviceResources& deviceResources	= DeviceResources::GetInstance();
	ID3D11DeviceContext* context		= deviceResources.GetD3DDeviceContext();
	CommonStates* states				= deviceResources.GetCommonStates();

	// �s�񐶐�
	Matrix world = Matrix::CreateScale(3.0f);
	Matrix view = camera_->GetView();
	Matrix proj = camera_->GetProjection();

	// �s��̍���
	Matrix wvp = world * view * proj;

	// �e��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(context->Map(cBuffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		Constants constants;

		constants.wvpMat = wvp;
		constants.billboard = camera_->GetBillboard();
		memcpy_s(pData.pData, pData.RowPitch, &constants, sizeof(constants));

		// ���������
		context->Unmap(cBuffer_.Get(), 0);
	}

	// �R���X�^���g�o�b�t�@�̃Z�b�g
	context->VSSetConstantBuffers(0, 0, nullptr);
	context->GSSetConstantBuffers(0, 1, cBuffer_.GetAddressOf());
	context->PSSetConstantBuffers(0, 0, nullptr);

	// �V�F�[�_�[���Z�b�g
	context->VSSetShader(vertexShader_.Get(), nullptr, 0);
	context->GSSetShader(geometryShader_.Get(), nullptr, 0);
	context->PSSetShader(pixelShader_.Get(), nullptr, 0);

	// ���̓��C�A�E�g���Z�b�g
	context->IASetInputLayout(inputLayout_.Get());

	// �J�����O�ݒ�
	context->RSSetState(states->CullNone());

	// �[�x�X�e���V���ݒ�
	context->OMSetDepthStencilState(states->DepthNone(), 0);

	// �e�N�X�`���T���v���[�ݒ�
	context->PSSetSamplers(0, 1, sampler_.GetAddressOf());

	// �G�~�b�^�[�̕`��
	for (auto& emitter : emitter_)
	{
		if (emitter.second && emitter.second->GetActive())
		{
			emitter.second->Draw();
		}
	}

	// �V�F�[�_�[�N���A
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

/*==============================================================
// @brief		���Z�b�g
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void ParticleRenderer::Reset()
{
	emitter_.clear();
}

/*==============================================================
// @brief		�G�~�b�^�[�̓o�^
// @param		�G�~�b�^�[�iEmitter*�j�A�G�~�b�^�[���iwstring�j�A�e�N�X�`���t�@�C�����iwstring�j�A�G�~�b�^�[�̍��W�iVector3�j
// @return		�Ȃ�
===============================================================*/
void ParticleRenderer::RegisterEmitter(Emitter* emitter, wstring emitterName, wstring textureFileName, const Vector3& emitterPos)
{
	emitter_[emitterName] = emitter;
	emitter_[emitterName]->LoadTexture(textureFileName);
	emitter_[emitterName]->SetPos(emitterPos);
}

/*==============================================================
// @brief		�G�~�b�^�[�̓o�^
// @param		�G�~�b�^�[���iwstring�j
// @return		�Ȃ�
===============================================================*/
void ParticleRenderer::DisposeEmitter(wstring emitterName)
{
	emitter_[emitterName] = nullptr;
}