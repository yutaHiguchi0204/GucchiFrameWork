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

namespace GucchiLibrary
{
	// �V�[���C���^�t�F�[�X
	class IScene
	{
	public:
		IScene() {};
		virtual ~IScene() {};

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void Finalize() = 0;

		virtual void ResetDevice();
	};

	// �V�[���}�l�[�W��
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