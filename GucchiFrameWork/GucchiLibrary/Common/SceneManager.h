/* =====================================================================
//! @param		�uSceneManager�v�w�b�_
//! @create		��� �T��
//! @date		17/10/30
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "SingletonDirector.h"
#include <CommonStates.h>
#include <map>
#include <string>
#include "../2D/SpriteRenderer.h"
#include "../2D/TextRenderer.h"
#include "../3D/ObjectRenderer.h"

namespace GucchiLibrary
{
	/*
	// @class		IScene �N���X
	// @content		�V�[���̊��N���X
	*/
	class IScene
	{
	protected:
		// TODO: ���ʃ����o
		std::unique_ptr<Camera> camera_;

		// ���C�u�����C���^�t�F�[�X
		ObjectRenderer&		objectRenderer_		= ObjectRenderer::GetInstance();			// �I�u�W�F�N�g�`��p
		ObjectFactory&		objectFactory_		= ObjectFactory::GetInstance();				// �I�u�W�F�N�g�����p
		SpriteRenderer&		spriteRenderer_		= SpriteRenderer::GetInstance();			// �X�v���C�g�`��p
		SpriteFactory&		spriteFactory_		= SpriteFactory::GetInstance();				// �X�v���C�g�����p
		TextRenderer&		textRenderer_		= TextRenderer::GetInstance();				// �e�L�X�g�`��p

	public:
		// �R���X�g���N�^
		IScene() {}

		// �f�X�g���N�^
		virtual ~IScene() {};

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
		void Initialize();																// �V�[���̏�����
		void Update();																	// �V�[���̍X�V
		void Draw();																	// �V�[���̕`��
		void Finalize();																// �V�[���̏I������

		void RegisterScene(std::string scene, std::unique_ptr<IScene> newScene);		// �V�[���̓o�^
		void ChangeScene(std::string scene);											// �V�[���̕ύX
		bool CheckScene();																// �V�[���`�F�b�N�i�O�t���[���ƃV�[�����قȂ�ꍇ�͕`�悵�Ȃ��j
	};
}