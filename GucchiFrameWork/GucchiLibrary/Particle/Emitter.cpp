/* =====================================================================
//! @param		�uEmitter�v�\�[�X
//! @create		��� �T��
//! @date		17/12/27
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Emitter.h"
#include "../Common/Constant.h"
#include "../Common/DeviceResources.h"

// ���O���
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// �ÓI�����o�̒�`
const int Emitter::FOREVER_EXIST = -1;			// ����

// �����o�֐��̒�`

// �R���X�g���N�^
Emitter::Emitter(const Vector3& pos, float exisTime)
	: texture_(nullptr)
	, pos_(pos)
	, exisTime_(exisTime)
	, nowFrame_(0.0f)
	, isExist_(true)
	, parentObject_(nullptr)
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();

	// �v���~�e�B�u�o�b�`�̐ݒ�
	primitiveBatch_ = make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void Emitter::Update()
{
	// ���݂ł��鎞�Ԃ��w�肳��Ă�����`�F�b�N
	if (exisTime_ != FOREVER_EXIST)
	{
		// ���݂ł��鎞�Ԃ𒴂��Ă���j��
		if (nowFrame_ / FRAME_PER_SECOND >= exisTime_)
		{
			isExist_ = false;
		}
	}

	// �t���[���̍X�V
	nowFrame_++;

	// �p�[�e�B�N���̍X�V
	for (auto particleItr = particle_.begin(); particleItr != particle_.end();)
	{
		// ���݂��Ă��Ȃ������烊�X�g�������
		if (!(*particleItr)->IsExist())
		{
			particleItr = particle_.erase(particleItr);
			continue;
		}

		(*particleItr)->Update();

		++particleItr;
	}
}

/*==============================================================
// @brief		�`�揈��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void Emitter::Draw()
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();

	// �o�b�`�����J�n
	primitiveBatch_->Begin();

	for (auto& particle : particle_)
	{
		// �u�����h�X�e�[�g�ݒ�
		Asset3D::SetBlendState(particle->GetBlendMode());

		// �e�N�X�`���ݒ�
		context->PSSetShaderResources(0, 1, texture_->GetShaderResourceView().GetAddressOf());

		// ���W�̐ݒ�i���[�J���{�G�~�b�^�[�j
		VertexPositionColorTexture vertex = particle->GetVertexNow();
		vertex.position = vertex.position + pos_;

		// �e���f�����ݒ肳��Ă�����e���f���̍��W������
		if (parentObject_)
		{
			Object* p = parentObject_;
			while (p != nullptr)
			{
				vertex.position = vertex.position + p->GetTranslate();
				p = p->GetParent();
			}
		}

		// �p�[�e�B�N���̕`��
		primitiveBatch_->Draw(D3D_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex, 1);
	}

	// �o�b�`�����I��
	primitiveBatch_->End();
}

/*==============================================================
// @brief		�p�[�e�B�N������
// @param		�����ifloat�j�A�n�_���iVertexPositionColorTexture�j�A�I�_���iVertexPositionColorTexture�j�A�u�����h���[�h�iBLEND_MODE�j�A���[�v���[�h�iLOOP_MODE�j
// @return		�Ȃ�
===============================================================*/
void Emitter::Entry(float exisTime, VertexPositionColorTexture vertexDataStart, VertexPositionColorTexture vertexDataEnd, Asset3D::BLEND_MODE blendMode, Particle::LOOP_MODE loopMode)
{
	// �p�[�e�B�N���̍쐬
	unique_ptr<Particle> particle = make_unique<Particle>();
	particle->Initialize(exisTime, vertexDataStart, vertexDataEnd, blendMode, loopMode);

	// �p�[�e�B�N���̓o�^
	particle_.emplace_back(move(particle));
}

/*==============================================================
// @brief		�e�N�X�`���̓ǂݍ���
// @param		�e�N�X�`���t�@�C�����iwstring�j
// @return		�Ȃ�
===============================================================*/
void Emitter::LoadTexture(const wstring fileName)
{
	TextureCache& textureCache = TextureCache::GetInstance();
	texture_ = textureCache.LoadTexture(fileName);
}