/* =====================================================================
//! @param		�uParticle�v�\�[�X
//! @create		��� �T��
//! @date		17/12/27
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Particle.h"
#include "../Common/Constant.h"
#include "../Utility/Math.h"

// ���O���
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// �ÓI�����o�̒�`
const int Particle::FOREVER_EXIST = -1;			// �i���I����
const float Particle::DEFAULT_SCALE = 1.0f;		// �����X�P�[��
const float Particle::DEFAULT_ROTATE = 0.0f;	// ������]�p

// �����o�֐��̒�`

// �R�s�[�R���X�g���N�^
Particle::Particle(const Particle& particle)
{
	vertexStart_         = particle.vertexStart_;
	vertexEnd_           = particle.vertexEnd_;
	vertexNow_           = particle.vertexNow_;
	exisTime_            = particle.exisTime_;
	nowFrame_            = particle.nowFrame_;
	blendMode_           = particle.blendMode_;
	loopMode_            = particle.loopMode_;
	isExist_             = particle.isExist_;
	interpolateDirector_ = make_unique<InterpolateDirector>();
	interpolateDirector_->stateV3_->Entry(L"pos",	vertexStart_.position,				vertexEnd_.position,			exisTime_, INTERPOLATE_MODE::LERP);
	interpolateDirector_->stateV4_->Entry(L"color", vertexStart_.color,					vertexEnd_.color,				exisTime_, INTERPOLATE_MODE::LERP);
	interpolateDirector_->stateF_->Entry(L"scale",	vertexStart_.textureCoordinate.x,	vertexEnd_.textureCoordinate.x, exisTime_, INTERPOLATE_MODE::LERP);
	interpolateDirector_->stateF_->Entry(L"rot",	vertexStart_.textureCoordinate.y,	vertexEnd_.textureCoordinate.y, exisTime_, INTERPOLATE_MODE::LERP);
}

/*==============================================================
// @brief		����������
// @param		�����ifloat�j�A�n�_���iVertexPositionColorTexture�j�A�I�_���iVertexPositionColorTexture�j�A�u�����h���[�h�iBLEND_MODE�j�A���[�v���[�h�iLOOP_MODE�j
// @return		�Ȃ�
===============================================================*/
void Particle::Initialize(float exisTime, VertexPositionColorTexture vertexDataStart, VertexPositionColorTexture vertexDataEnd, Asset3D::BLEND_MODE blendMode, LOOP_MODE loopMode)
{
	// �J�n���_�̃f�[�^��ݒ�
	vertexStart_ = vertexDataStart;

	// �I�����_�̃f�[�^��ݒ�
	vertexEnd_ = vertexDataEnd;

	// ���݂̒��_�f�[�^�ɊJ�n���_�̃f�[�^��ݒ�
	vertexNow_ = vertexStart_;

	// �u�����h���[�h�̐ݒ�
	blendMode_ = blendMode;

	// ���Ԋ֌W
	exisTime_ = exisTime;
	nowFrame_ = 0;

	// ���[�v���[�h�̐ݒ�
	loopMode_ = loopMode;

	// ����
	isExist_ = true;

	// ��ԃX�e�[�g�̏���
	interpolateDirector_ = make_unique<InterpolateDirector>();
	interpolateDirector_->stateV3_->Entry(L"pos",	vertexStart_.position,				vertexEnd_.position,			exisTime_, INTERPOLATE_MODE::LERP);
	interpolateDirector_->stateV4_->Entry(L"color", vertexStart_.color,					vertexEnd_.color,				exisTime_, INTERPOLATE_MODE::LERP);
	interpolateDirector_->stateF_->Entry(L"scale",	vertexStart_.textureCoordinate.x,	vertexEnd_.textureCoordinate.x, exisTime_, INTERPOLATE_MODE::LERP);
	interpolateDirector_->stateF_->Entry(L"rot",	vertexStart_.textureCoordinate.y,	vertexEnd_.textureCoordinate.y, exisTime_, INTERPOLATE_MODE::LERP);
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void Particle::Update()
{
	// ��ԃX�e�[�g�̍X�V
	interpolateDirector_->Update();

	// �������w�肳��Ă�����`�F�b�N
	if (exisTime_ != FOREVER_EXIST)
	{
		// �����𒴂��Ă���j��
		if (nowFrame_ / FRAME_PER_SECOND >= exisTime_)
		{
			// ���[�v���[�h��REPEAT�Őݒ肳��Ă���ŏ�����
			if (loopMode_ == LOOP_MODE::REPEAT)
			{
				Reset();
				return;
			}
			// TURN�ɐݒ肳��Ă���start��end�����ւ��čŏ�����
			else if (loopMode_ == LOOP_MODE::TURN)
			{
				// �f�[�^�̓���ւ�
				Math::SwapData(&vertexStart_, &vertexEnd_);
				Reset();
				return;
			}

			isExist_ = false;
			return;
		}
	}

	// �p�[�e�B�N���̍X�V
	vertexNow_.position				= interpolateDirector_->stateV3_->GetResult(L"pos");
	vertexNow_.color				= interpolateDirector_->stateV4_->GetResult(L"color");
	vertexNow_.textureCoordinate.x	= interpolateDirector_->stateF_->GetResult(L"scale");
	vertexNow_.textureCoordinate.y	= interpolateDirector_->stateF_->GetResult(L"rot");

	// �t���[���̍X�V
	nowFrame_++;
}

/*==============================================================
// @brief		���Z�b�g
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void Particle::Reset()
{
	vertexNow_ = vertexStart_;
	nowFrame_ = 0;

	// ��ԃX�e�[�g�̃��Z�b�g
	interpolateDirector_->Reset();
}