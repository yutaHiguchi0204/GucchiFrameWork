/* =====================================================================
//! @param		�uADX2Le�v�w�b�_
//! @create		��� �T��
//! @date		17/12/01
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <cri_adx2le.h>

namespace GucchiLibrary
{
	/*
	// @class		ADX2LePlayer �N���X
	// @content		���y�̍Đ��E��~�Ȃǂ𐧌䂷��N���X
	// @use			�T�E���h�}�l�[�W���Ŏg�p
	*/
	class ADX2LePlayer
	{
	private:
		// Acb�n���h��
		CriAtomExAcbHn acbHandle_;

		// �v���C���[�n���h��
		CriAtomExPlayerHn player_;

	public:
		// �R���X�g���N�^
		ADX2LePlayer();

		/*
		// @method		Create
		// @content		�v���C���[�̍쐬
		*/
		void Create();

		/*
		// @method		LoadAcb
		// @content		Acb�t�@�C���̓ǂݍ���
		// @param		acb�t�@�C�����ichar*�j
		// @param		awb�t�@�C�����ichar*�j�@�F�@�f�t�H���g�inullptr�j
		*/
		void LoadAcb(const char* acb, const char* awb = nullptr);
		
		/*
		// @method		Release
		// @content		�v���C���[�̉��
		*/
		void Release();

		/*
		// @method		Play
		// @content		�w�肵���L���[�̍Đ�
		// @param		�L���[ID�iCriAtomExCueId�j
		// @param		���ʁifloat�j�@�F�@�f�t�H���g�i1.0f�j
		// @return		�Đ�ID�iCriAtomExPlaybackId�j
		*/
		CriAtomExPlaybackId Play(CriAtomExCueId cueID, float volume = 1.0f);

		/*
		// @method		SetVolume
		// @content		���ʐݒ�
		// @param		���ʁifloat�j
		*/
		void SetVolume(float volume);

		/*
		// @method		SetVolumeByID
		// @content		�w�肵���Đ�ID�̉��ʐݒ�
		// @param		�Đ�ID�iCriAtomExPlaybackId�j
		// @param		���ʁifloat�j
		*/
		void SetVolumeByID(CriAtomExPlaybackId playbackID, float volume);

		/*
		// @method		Pause
		// @content		�v���C���[�̈ꎞ��~
		*/
		void Pause();

		/*
		// @method		PauseByID
		// @content		�w�肵���Đ�ID�̈ꎞ��~
		// @param		�Đ�ID�iCriAtomExPlaybackId�j
		*/
		void PauseByID(CriAtomExPlaybackId playbackID);

		/*
		// @method		IsPause
		// @content		�v���C���[�̃|�[�Y��Ԃ̎擾
		// @return		�|�[�Y��ԁibool�j
		*/
		bool IsPause();

		/*
		// @method		IsPauseByID
		// @content		�w�肵���Đ�ID�̃|�[�Y��Ԃ̎擾
		// @param		�Đ�ID�iCriAtomExPlaybackId�j
		// @return		�|�[�Y��ԁibool�j
		*/
		bool IsPauseByID(CriAtomExPlaybackId playbackID);

		/*
		// @method		Stop
		// @content		�v���C���[�̒�~
		*/
		void Stop();

		/*
		// @method		StopByID
		// @content		�w�肵���Đ�ID�̒�~
		*/
		void StopByID(CriAtomExPlaybackId playbackID);

		/* �A�N�Z�b�T */

		inline CriAtomExPlayerHn GetPlayerHandle() const { return player_; }
	};

	/*
	// @class		ADX2Le �N���X
	// @content		ADX2Le�Ɋւ���֐����܂Ƃ߂��N���X
	// @use			�T�E���h�}�l�[�W���Ŏg�p
	*/
	class ADX2Le
	{
	private:
		// �ő�{�C�X���𑝂₷���߂̊֘A�p�����[�^
		static const int MAX_VOICE;
		static const int MAX_VIRTUAL_VOICE;
		static const int MAX_CRIFS_LOADER;

		// �ő�T���v�����O���[�g�i�s�b�`�ύX�܂ށj
		static const int MAX_SAMPLING_RATE;

		// HCA-MX�R�[�f�b�N�̃T���v�����O���[�g
		static const int SAMPLINGRATE_HCAMX;

		static CriAtomExVoicePoolHn	standardVoicePool_;
		static CriAtomExVoicePoolHn	hcamxVoicePool_;
		static CriAtomDbasId		dbasID_;

		// �v���C���[
		static ADX2LePlayer player_;

	private:
		// �G���[�R�[���o�b�N�֐��̃��[�U����
		static void  UserErrorCallback(const CriChar8* errID, CriUint32 p1, CriUint32 p2, CriUint32* parray);

		//	�������m�ۊ֐��̃��[�U����
		static void* UserAlloc(void* obj, CriUint32 size);

		// ����������֐��̃��[�U����
		static void  UserFree(void* obj, void* ptr);

	public:
		/*
		// @method		Initialize�istatic�j
		// @content		����������
		// @param		acf�t�@�C�����ichar*�j
		*/
		static void Initialize(const char* acf);

		/*
		// @method		Update�istatic�j
		// @content		�X�V����
		*/
		static void Update();

		/*
		// @method		Finalize�istatic�j
		// @content		�I������
		*/
		static void Finalize();

		/*
		// @method		GetPlayer�istatic�j
		// @content		�v���C���[�̎擾
		// @return		�v���C���[�iADX2LePlayer*�j
		*/
		static ADX2LePlayer* GetPlayer();

		/*
		// @method		LoadAcb�istatic�j
		// @content		Acb�t�@�C���̓ǂݍ���
		// @param		Acb�t�@�C�����ichar*�j
		// @param		Awb�t�@�C�����ichar*�j�@�F�@�f�t�H���g�inullptr�j
		*/
		static void LoadAcb(const char* acb, const char* awb = nullptr);

		/*
		// @method		Play�istatic�j
		// @content		�w�肵���L���[�̍Đ�
		// @param		�L���[ID�iCriAtomExCueId�j
		// @param		���ʁifloat�j�@�F�@�f�t�H���g�i1.0f�j
		// @return		�Đ�ID�iCriAtomExPlaybackId�j
		*/
		static CriAtomExPlaybackId Play(CriAtomExCueId cueID, float volume = 1.0f);

		/*
		// @method		SetVolume�istatic�j
		// @content		�v���C���[�̉��ʐݒ�
		// @param		���ʁifloat�j
		*/
		static void SetVolume(float volume);

		/*
		// @method		Pause�istatic�j
		// @content		�v���C���[�̃|�[�Y
		*/
		static void Pause();

		/*
		// @method		IsPause�istatic�j
		// @content		�v���C���[�̃|�[�Y��Ԃ̎擾
		// @return		�|�[�Y���
		*/
		static bool IsPause();

		/*
		// @method		Stop�istatic�j
		// @content		�v���C���[�̒�~
		*/
		static void Stop();
	};
}