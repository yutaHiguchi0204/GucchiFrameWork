/* =====================================================================
//! @param		�uADX2Le�v�\�[�X
//! @create		��� �T��
//! @date		17/12/01
===================================================================== */
#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")

// �w�b�_�t�@�C���̃C���N���[�h
#include "ADX2Le.h"
#include "../Common/DebugSwitch.h"

// ���O���
using namespace GucchiLibrary;

// �ÓI�����o�̒�`
const int ADX2Le::MAX_VOICE = 24;
const int ADX2Le::MAX_VIRTUAL_VOICE = 64;
const int ADX2Le::MAX_CRIFS_LOADER = 64;
const int ADX2Le::MAX_SAMPLING_RATE = (48000 * 2);
const int ADX2Le::SAMPLINGRATE_HCAMX = 32000;
CriAtomExVoicePoolHn	ADX2Le::standardVoicePool_;
CriAtomExVoicePoolHn	ADX2Le::hcamxVoicePool_;
CriAtomDbasId			ADX2Le::dbasID_;
ADX2LePlayer			ADX2Le::player_;

// �����o�֐��̒�`

// �R���X�g���N�^
ADX2LePlayer::ADX2LePlayer()
	: acbHandle_(nullptr)
	, player_(nullptr)
{
}

/*==============================================================
// @brief		�v���C���[�̍쐬
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void ADX2LePlayer::Create()
{
	// �v���C���[�̍쐬
	if (!player_)
	{
		player_ = criAtomExPlayer_Create(nullptr, nullptr, 0);
	}
}

/*==============================================================
// @brief		Acb�t�@�C���̓ǂݍ���
// @param		Acb�t�@�C�����ichar*�j�AAwb�t�@�C�����ichar*�j
// @return		�Ȃ�
===============================================================*/
void ADX2LePlayer::LoadAcb(const char* acb, const char* awb)
{
	if (acbHandle_)
	{
		// Acb�n���h���̔j��
		criAtomExAcb_Release(acbHandle_);
	}

	// Acb�t�@�C���̓ǂݍ���
	acbHandle_ = criAtomExAcb_LoadAcbFile(nullptr, acb, nullptr, awb, nullptr, 0);
}

/*==============================================================
// @brief		�v���C���[�̉��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void ADX2LePlayer::Release()
{
	// �v���C���[�n���h���̔j��
	if (player_)
	{
		criAtomExPlayer_Destroy(player_);
	}

	// Acb�n���h���̔j��
	if (acbHandle_)
	{
		criAtomExAcb_Release(acbHandle_);
	}
}

/*==============================================================
// @brief		�w�肵���L���[�̍Đ�
// @param		�L���[ID�iCriAtomExCueId�j�A���ʁifloat�j
// @return		�Ȃ�
===============================================================*/
CriAtomExPlaybackId ADX2LePlayer::Play(CriAtomExCueId cueID, float volume)
{
	// ���ʐݒ�
	criAtomExPlayer_SetVolume(player_, volume);

	// �L���[ID�̎w��
	criAtomExPlayer_SetCueId(player_, acbHandle_, cueID);

	// �Đ�
	return criAtomExPlayer_Start(player_);
}

/*==============================================================
// @brief		���ʐݒ�
// @param		���ʁifloat�j
// @return		�Ȃ�
===============================================================*/
void ADX2LePlayer::SetVolume(float volume)
{
	criAtomExPlayer_SetVolume(player_, volume);
	criAtomExPlayer_UpdateAll(player_);
}

/*==============================================================
// @brief		�w�肵���Đ�ID�̉��ʐݒ�
// @param		�Đ�ID�iCriAtomExPlaybackId�j�A���ʁifloat�j
// @return		�Ȃ�
===============================================================*/
void ADX2LePlayer::SetVolumeByID(CriAtomExPlaybackId playbackID, float volume)
{
	criAtomExPlayer_SetVolume(player_, volume);
	criAtomExPlayer_Update(player_, playbackID);
}

/*==============================================================
// @brief		�v���C���[�̈ꎞ��~
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void ADX2LePlayer::Pause()
{
	// �|�[�Y���ł���Ή������A�Ȃ���΃|�[�Y����
	criAtomExPlayer_Pause(player_, criAtomExPlayer_IsPaused(player_) == CRI_TRUE ? CRI_FALSE : CRI_TRUE);
}

/*==============================================================
// @brief		�w�肵���Đ�ID�̈ꎞ��~
// @param		�Đ�ID�iCriAtomExPlaybackId�j
// @return		�Ȃ�
===============================================================*/
void ADX2LePlayer::PauseByID(CriAtomExPlaybackId playbackID)
{
	// �|�[�Y���ł���Ή������A�Ȃ���΃|�[�Y����
	criAtomExPlayback_Pause(playbackID, criAtomExPlayback_IsPaused(playbackID) == CRI_TRUE ? CRI_FALSE : CRI_TRUE);
}

/*==============================================================
// @brief		�v���C���[�̃|�[�Y��Ԃ̎擾
// @param		�Ȃ�
// @return		�|�[�Y��ԁibool�j
===============================================================*/
bool ADX2LePlayer::IsPause()
{
	return criAtomExPlayer_IsPaused(player_) == CRI_TRUE ? true : false;
}

/*==============================================================
// @brief		�w�肵���Đ�ID�̃|�[�Y��Ԃ̎擾
// @param		�Đ�ID�iCriAtomExPlaybackId�j
// @return		�|�[�Y��ԁibool�j
===============================================================*/
bool ADX2LePlayer::IsPauseByID(CriAtomExPlaybackId playbackID)
{
	return criAtomExPlayback_IsPaused(playbackID) == CRI_TRUE ? true : false;
}

/*==============================================================
// @brief		�v���C���[�̒�~
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void ADX2LePlayer::Stop()
{
	criAtomExPlayer_Stop(player_);
}

/*==============================================================
// @brief		�w�肵���Đ�ID�̒�~
// @param		�Đ�ID�iCriAtomExPlaybackId�j
// @return		�Ȃ�
===============================================================*/
void ADX2LePlayer::StopByID(CriAtomExPlaybackId playbackID)
{
	criAtomExPlayback_Stop(playbackID);
}

// �G���[�R�[���o�b�N�֐��̃��[�U����
void ADX2Le::UserErrorCallback(const CriChar8* errID, CriUint32 p1, CriUint32 p2, CriUint32* parray)
{
	const CriChar8* errmsg;

	// �G���[�R�[�h����G���[������ɕϊ����ăR���\�[���o�͂���
	errmsg = criErr_ConvertIdToMessage(errID, p1, p2);

	const unsigned int dataSize = 256;
	wchar_t wlocal[dataSize + 1] = { 0x00 };

	// �}���`�o�C�g������Unicode�֕ϊ�����
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, errmsg, dataSize, wlocal, dataSize + 1);

	// �R���\�[���o�͂���
#if defined(MODE_DEBUG)
	OutputDebugString(wlocal);
#endif

	return;
}

//	�������m�ۊ֐��̃��[�U����
void* ADX2Le::UserAlloc(void* obj, CriUint32 size)
{
	void* ptr;
	ptr = malloc(size);

	return ptr;
}

// ����������֐��̃��[�U����
void ADX2Le::UserFree(void* obj, void* ptr)
{
	free(ptr);
}

/*==============================================================
// @brief		����������
// @param		acf�t�@�C�����ichar*�j
// @return		�Ȃ�
===============================================================*/
void ADX2Le::Initialize(const char* acf)
{
	// �G���[�R�[���o�b�N�֐��̓o�^
	criErr_SetCallback(UserErrorCallback);

	// �������A���P�[�^�̓o�^
	criAtomEx_SetUserAllocator(UserAlloc, UserFree, nullptr);

	// ���C�u����������
	CriAtomExConfig_PC libConfig;
	CriFsConfig fsConfig;
	criAtomEx_SetDefaultConfig_PC(&libConfig);
	criFs_SetDefaultConfig(&fsConfig);
	libConfig.atom_ex.max_virtual_voices = MAX_VIRTUAL_VOICE;
	libConfig.hca_mx.output_sampling_rate = SAMPLINGRATE_HCAMX;
	fsConfig.num_loaders = MAX_CRIFS_LOADER;
	libConfig.atom_ex.fs_config = &fsConfig;
	criAtomEx_Initialize_PC(&libConfig, nullptr, 0);

	// �X�g���[�~���O�p�o�b�t�@�̍쐬
	dbasID_ = criAtomDbas_Create(nullptr, nullptr, 0);

	// ACF�t�@�C���̓ǂݍ��݂Ɠo�^
	criAtomEx_RegisterAcfFile(nullptr, acf, nullptr, 0);

	// DSP�o�X�ݒ�̓o�^
	criAtomEx_AttachDspBusSetting("DspBusSetting_0", nullptr, 0);

	// �{�C�X�v�[���̍쐬�i�ő�{�C�X���ύX�^�ő�s�b�`�ύX�^�X�g���[���Đ��Ή��j
	CriAtomExStandardVoicePoolConfig standardVpoolConfig;
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&standardVpoolConfig);
	standardVpoolConfig.num_voices = MAX_VOICE;
	standardVpoolConfig.player_config.max_sampling_rate = MAX_SAMPLING_RATE;
	standardVpoolConfig.player_config.streaming_flag = CRI_TRUE;
	standardVoicePool_ = criAtomExVoicePool_AllocateStandardVoicePool(&standardVpoolConfig, nullptr, 0);

	// HCA-MX�Đ��p�F�{�C�X�v�[���̍쐬
	CriAtomExHcaMxVoicePoolConfig hcamxVpoolConfig;
	criAtomExVoicePool_SetDefaultConfigForHcaMxVoicePool(&hcamxVpoolConfig);
	hcamxVpoolConfig.num_voices = MAX_VOICE;
	hcamxVpoolConfig.player_config.max_sampling_rate = MAX_SAMPLING_RATE;
	hcamxVpoolConfig.player_config.streaming_flag = CRI_TRUE;
	hcamxVoicePool_ = criAtomExVoicePool_AllocateHcaMxVoicePool(&hcamxVpoolConfig, NULL, 0);

	// �v���C���[�̍쐬
	player_.Create();
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void ADX2Le::Update()
{
	criAtomEx_ExecuteMain();
}

/*==============================================================
// @brief		�I������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void ADX2Le::Finalize()
{
	// �v���C���[�̔j��
	player_.Release();

	// DSP�̃f�^�b�`
	criAtomEx_DetachDspBusSetting();

	// �{�C�X�v�[���̔j��
	criAtomExVoicePool_Free(hcamxVoicePool_);
	criAtomExVoicePool_Free(standardVoicePool_);

	// ACF�̓o�^����
	criAtomEx_UnregisterAcf();

	// D-BAS�̔j��
	criAtomDbas_Destroy(dbasID_);

	// ���C�u�����̏I��
	criAtomEx_Finalize_PC();
}

/*==============================================================
// @brief		�v���C���[�̎擾
// @param		�Ȃ�
// @return		�v���C���[�iADX2LePlayer*�j
===============================================================*/
ADX2LePlayer* ADX2Le::GetPlayer()
{
	return &player_;
}

/*==============================================================
// @brief		Acb�t�@�C���̓ǂݍ���
// @param		Acb�t�@�C�����ichar*�j�AAwb�t�@�C�����ichar*�j
// @return		�Ȃ�
===============================================================*/
void ADX2Le::LoadAcb(const char* acb, const char* awb)
{
	player_.LoadAcb(acb, awb);
}

/*==============================================================
// @brief		�w�肵���L���[�̍Đ�
// @param		�L���[ID�iCriAtomExCueId�j�A���ʁifloat�j
// @return		�Đ�ID�iCriAtomExPlaybackId�j
===============================================================*/
CriAtomExPlaybackId ADX2Le::Play(CriAtomExCueId cueID, float volume)
{
	return player_.Play(cueID, volume);
}

/*==============================================================
// @brief		�v���C���[�̉��ʐݒ�
// @param		���ʁifloat�j
// @return		�Ȃ�
===============================================================*/
void ADX2Le::SetVolume(float volume)
{
	player_.SetVolume(volume);
}

/*==============================================================
// @brief		�v���C���[�̃|�[�Y
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void ADX2Le::Pause()
{
	player_.Pause();
}

/*==============================================================
// @brief		�v���C���[�̃|�[�Y��Ԃ̎擾
// @param		�Ȃ�
// @return		�|�[�Y��ԁibool�j
===============================================================*/
bool ADX2Le::IsPause()
{
	return player_.IsPause();
}

/*==============================================================
// @brief		�v���C���[�̒�~
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void ADX2Le::Stop()
{
	player_.Stop();
}