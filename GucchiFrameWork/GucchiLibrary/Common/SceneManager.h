/* =====================================================================
//! @param		�uSceneManager�v�w�b�_
//! @create		��� �T��
//! @date		17/10/30
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "SingletonDirector.h"
#include <CommonStates.h>

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
	};

	// �V�[���}�l�[�W��
	class SceneManager : public SingletonDirector<SceneManager>
	{
	public:
		enum SCENE
		{
			PLAY
		};

	private:
		SCENE nowScene_;
		SCENE beforeFrameScene_;

	private:
		friend class SingletonDirector<SceneManager>;

		SceneManager();

	public:
		std::unique_ptr<IScene> ChangeScene(SCENE scene);	// �V�[���̕ύX
		void Update();										// �V�[���Ǘ��̍X�V
		bool CheckScene();									// �V�[���`�F�b�N�i�O�t���[���ƃV�[�����قȂ�ꍇ�͕`�悵�Ȃ��j
	};
}