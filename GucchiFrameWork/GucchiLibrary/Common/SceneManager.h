/* =====================================================================
//! @param		�uSceneManager�v�w�b�_
//! @create		��� �T��
//! @date		17/10/30
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "SingletonDirector.h"
#include "../2D/SpriteRenderer.h"
#include "../2D/TextRenderer.h"
#include "../3D/ObjectRenderer.h"
#include "../Particle/ParticleRenderer.h"
#include "../Primitive/PrimitiveRenderer.h"
#include "../Sound/SoundManager.h"

namespace GucchiLibrary
{
	/*
	// @class		IScene �N���X
	// @content		�V�[���̊��N���X
	*/
	class IScene
	{
	protected:
		using Vector2    = DirectX::SimpleMath::Vector2;
		using Vector3    = DirectX::SimpleMath::Vector3;
		using Vector4    = DirectX::SimpleMath::Vector4;
		using Color      = DirectX::SimpleMath::Color;
		using Matrix     = DirectX::SimpleMath::Matrix;
		using Quaternion = DirectX::SimpleMath::Quaternion;

	protected:
		// TODO: ���ʃ����o
		std::unique_ptr<Object> skyDome_;		// �V��
		std::unique_ptr<Camera> camera_;		// �J����

		// ���C�u�����C���^�t�F�[�X
		ObjectRenderer&			objectRenderer_			= ObjectRenderer::GetInstance();			// �I�u�W�F�N�g�`��p
		ObjectFactory&			objectFactory_			= ObjectFactory::GetInstance();				// �I�u�W�F�N�g�����p
		ParticleRenderer&		particleRenderer_		= ParticleRenderer::GetInstance();			// �p�[�e�B�N���`��p
		PrimitiveRenderer&		primitiveRenderer_		= PrimitiveRenderer::GetInstance();			// �v���~�e�B�u�`��p
		SpriteRenderer&			spriteRenderer_			= SpriteRenderer::GetInstance();			// �X�v���C�g�`��p
		SpriteFactory&			spriteFactory_			= SpriteFactory::GetInstance();				// �X�v���C�g�����p
		TextRenderer&			textRenderer_			= TextRenderer::GetInstance();				// �e�L�X�g�`��p
		SoundManager&			soundManager_			= SoundManager::GetInstance();				// �T�E���h�}�l�[�W��

	public:
		// �R���X�g���N�^
		IScene() = default;

		// �f�X�g���N�^
		virtual ~IScene() = default;

		/*
		// @method		Initialize�ipure�j
		// @content		����������
		*/
		virtual void Initialize() = 0;

		/*
		// @method		Update�ipure�j
		// @content		�X�V����
		*/
		virtual void Update() = 0;

		/*
		// @method		Draw�ipure�j
		// @content		�`�揈��
		*/
		virtual void Draw() = 0;

		/*
		// @method		Finalize�ipure�j
		// @content		�I������
		*/
		virtual void Finalize() = 0;

		/*
		// @method		CommonInitialize
		// @content		�S�V�[�����ʂ̏���������
		*/
		virtual void CommonInitialize();

		/*
		// @method		CommonUpdate
		// @content		�S�V�[�����ʂ̍X�V����
		*/
		virtual void CommonUpdate();

		/*
		// @method		CommonDraw
		// @content		�S�V�[�����ʂ̕`�揈��
		*/
		virtual void CommonDraw();

		/*
		// @method		CommonFinalize
		// @content		�S�V�[�����ʂ̏I������
		*/
		virtual void CommonFinalize();

		/*
		// @method		ResetDevice
		// @content		���C�u�����C���^�t�F�[�X�̃��Z�b�g
		*/
		virtual void ResetDevice();
	};

	/*
	// @class		SceneManager �N���X�iSingleton�j
	// @content		�V�[���}�l�[�W��
	// @use			RegisterScene�֐��ŃV�[����o�^���Ă������Ƃɂ���āA�o�^���ꂽ�V�[���ɗe�ՂɕύX���ł���
	*/
	class SceneManager : public SingletonDirector<SceneManager>
	{
	private:
		std::map<std::string, std::unique_ptr<IScene>> sceneList_;			// �o�^���ꂽ�V�[��
		std::string nowScene_;												// ���݂̃V�[��
		std::string beforeScene_;											// �O�t���[���̃V�[��

	private:
		friend class SingletonDirector<SceneManager>;

		SceneManager();

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
		// @method		Finalize
		// @content		�I������
		*/
		void Finalize();

		/*
		// @method		RegisterScene
		// @content		�V�[���̓o�^
		// @param		�V�[�����istring�j
		// @param		�V�[���C���X�^���X�iunique_ptr<IScene>�j
		*/
		void RegisterScene(std::string scene, std::unique_ptr<IScene> newScene);

		/*
		// @method		ChangeScene
		// @content		�V�[���̕ύX
		// @param		�V�[�����istring�j
		// @param		�V�[���C���X�^���X�iunique_ptr<IScene>�j
		*/
		void ChangeScene(std::string scene, std::unique_ptr<IScene> newScene);

		/*
		// @method		CheckScene
		// @content		�O�t���[���ƃV�[�����������ǂ������`�F�b�N����i�قȂ�ꍇ��Draw���Ă΂Ȃ��j
		// @return		���ʁibool�j
		*/
		bool CheckScene();
	};
}