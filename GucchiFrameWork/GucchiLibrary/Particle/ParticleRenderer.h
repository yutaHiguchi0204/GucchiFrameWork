/* =====================================================================
//! @param		�uParticleRenderer�v�w�b�_
//! @create		��� �T��
//! @date		17/12/26
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "../Common/SingletonDirector.h"
#include <d3d11_1.h>
#include <map>
#include <memory>
#include <PrimitiveBatch.h>
#include <SimpleMath.h>
#include <vector>
#include <VertexTypes.h>
#include <wrl/client.h>
#include "Emitter.h"
#include "../Camera/Camera.h"

namespace GucchiLibrary
{
	/*
	// @class		ParticleRenderer �N���X�iSingleton�j
	// @content		�p�[�e�B�N���`��p
	*/
	class ParticleRenderer : public SingletonDirector<ParticleRenderer>
	{
	public:
		/*
		// @struct		�R���X�^���g�o�b�t�@ �\����
		// @content		�p�[�e�B�N����`�悷��ۂɕK�v�ƂȂ�����܂Ƃ߂��\����
		*/
		struct Constants
		{
			DirectX::SimpleMath::Matrix wvpMat;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
			DirectX::SimpleMath::Matrix billboard;		// �r���{�[�h�s��
		};

	public:
		static const std::vector<D3D11_INPUT_ELEMENT_DESC>	INPUT_LAYOUT;		// ���̓��C�A�E�g
		static const int									MAX_PARTICLE;		// �p�[�e�B�N���̍ő吔

	private:
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>	primitiveBatch_;		// �v���~�e�B�u�o�b�`
		Microsoft::WRL::ComPtr<ID3D11InputLayout>										inputLayout_;			// ���̓��C�A�E�g

		Microsoft::WRL::ComPtr<ID3D11VertexShader>										vertexShader_;			// ���_�V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11GeometryShader>									geometryShader_;		// �W�I���g���V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11PixelShader>										pixelShader_;			// �s�N�Z���V�F�[�_

		Microsoft::WRL::ComPtr<ID3D11Buffer>											cBuffer_;				// �R���X�^���g�o�b�t�@

		Microsoft::WRL::ComPtr<ID3D11SamplerState>										sampler_;				// �e�N�X�`���T���v���[

		std::map<std::wstring, Emitter*>												emitter_;				// �G�~�b�^�[

		Camera*																			camera_;				// �J����

	private:
		friend class SingletonDirector<ParticleRenderer>;

		ParticleRenderer() {}

	public:
		/*
		// @method		Initialize
		// @content		����������
		*/
		void Initialize();

		/*
		// @method		Update
		// @content		�X�V����
		*/
		void Update();

		/*
		// @method		Draw
		// @content		�`�揈��
		*/
		void Draw();

		/*
		// @method		Reset
		// @content		���X�g���Z�b�g
		*/
		void Reset();

		/*
		// @method		RegisterEmitter
		// @content		�G�~�b�^�[�̓o�^
		// @param		�G�~�b�^�[�iEmitter*�j
		// @param		�G�~�b�^�[���iwstring�j
		// @param		�p�[�e�B�N���p�e�N�X�`���t�@�C�����iwstring�j
		// @param		�G�~�b�^�[�̍��W�iVector3�j	�F	�f�t�H���g�iVector3::Zero�j
		*/
		void RegisterEmitter(Emitter* emitter, std::wstring emitterName, std::wstring textureFileName, DirectX::SimpleMath::Vector3 emitterPos = DirectX::SimpleMath::Vector3::Zero);

		/*
		// @method		DisposeEmitter
		// @content		�G�~�b�^�[�̉��
		*/
		void DisposeEmitter(std::wstring emitterName);

		/* �A�N�Z�b�T */

		void SetCamera(Camera* camera) { camera_ = camera; }
	};
}