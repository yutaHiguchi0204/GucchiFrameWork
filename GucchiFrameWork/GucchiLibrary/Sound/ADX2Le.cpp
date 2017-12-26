/* =====================================================================
//! @param		「ADX2Le」ソース
//! @create		樋口 裕太
//! @date		17/12/01
===================================================================== */
#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")

// ヘッダファイルのインクルード
#include "ADX2Le.h"
#include "../Common/DebugSwitch.h"

// 名前空間
using namespace GucchiLibrary;

// 静的メンバの定義
const int ADX2Le::MAX_VOICE = 24;
const int ADX2Le::MAX_VIRTUAL_VOICE = 64;
const int ADX2Le::MAX_CRIFS_LOADER = 64;
const int ADX2Le::MAX_SAMPLING_RATE = (48000 * 2);
const int ADX2Le::SAMPLINGRATE_HCAMX = 32000;
CriAtomExVoicePoolHn	ADX2Le::standardVoicePool_;
CriAtomExVoicePoolHn	ADX2Le::hcamxVoicePool_;
CriAtomDbasId			ADX2Le::dbasID_;
ADX2LePlayer			ADX2Le::player_;

// メンバ関数の定義

// コンストラクタ
ADX2LePlayer::ADX2LePlayer()
	: acbHandle_(nullptr)
	, player_(nullptr)
{
}

/*==============================================================
// @brief		プレイヤーの作成
// @param		なし
// @return		なし
===============================================================*/
void ADX2LePlayer::Create()
{
	// プレイヤーの作成
	if (!player_)
	{
		player_ = criAtomExPlayer_Create(nullptr, nullptr, 0);
	}
}

/*==============================================================
// @brief		Acbファイルの読み込み
// @param		Acbファイル名（char*）、Awbファイル名（char*）
// @return		なし
===============================================================*/
void ADX2LePlayer::LoadAcb(const char* acb, const char* awb)
{
	if (acbHandle_)
	{
		// Acbハンドルの破棄
		criAtomExAcb_Release(acbHandle_);
	}

	// Acbファイルの読み込み
	acbHandle_ = criAtomExAcb_LoadAcbFile(nullptr, acb, nullptr, awb, nullptr, 0);
}

/*==============================================================
// @brief		プレイヤーの解放
// @param		なし
// @return		なし
===============================================================*/
void ADX2LePlayer::Release()
{
	// プレイヤーハンドルの破棄
	if (player_)
	{
		criAtomExPlayer_Destroy(player_);
	}

	// Acbハンドルの破棄
	if (acbHandle_)
	{
		criAtomExAcb_Release(acbHandle_);
	}
}

/*==============================================================
// @brief		指定したキューの再生
// @param		キューID（CriAtomExCueId）、音量（float）
// @return		なし
===============================================================*/
CriAtomExPlaybackId ADX2LePlayer::Play(CriAtomExCueId cueID, float volume)
{
	// 音量設定
	criAtomExPlayer_SetVolume(player_, volume);

	// キューIDの指定
	criAtomExPlayer_SetCueId(player_, acbHandle_, cueID);

	// 再生
	return criAtomExPlayer_Start(player_);
}

/*==============================================================
// @brief		音量設定
// @param		音量（float）
// @return		なし
===============================================================*/
void ADX2LePlayer::SetVolume(float volume)
{
	criAtomExPlayer_SetVolume(player_, volume);
	criAtomExPlayer_UpdateAll(player_);
}

/*==============================================================
// @brief		指定した再生IDの音量設定
// @param		再生ID（CriAtomExPlaybackId）、音量（float）
// @return		なし
===============================================================*/
void ADX2LePlayer::SetVolumeByID(CriAtomExPlaybackId playbackID, float volume)
{
	criAtomExPlayer_SetVolume(player_, volume);
	criAtomExPlayer_Update(player_, playbackID);
}

/*==============================================================
// @brief		プレイヤーの一時停止
// @param		なし
// @return		なし
===============================================================*/
void ADX2LePlayer::Pause()
{
	// ポーズ中であれば解除し、なければポーズする
	criAtomExPlayer_Pause(player_, criAtomExPlayer_IsPaused(player_) == CRI_TRUE ? CRI_FALSE : CRI_TRUE);
}

/*==============================================================
// @brief		指定した再生IDの一時停止
// @param		再生ID（CriAtomExPlaybackId）
// @return		なし
===============================================================*/
void ADX2LePlayer::PauseByID(CriAtomExPlaybackId playbackID)
{
	// ポーズ中であれば解除し、なければポーズする
	criAtomExPlayback_Pause(playbackID, criAtomExPlayback_IsPaused(playbackID) == CRI_TRUE ? CRI_FALSE : CRI_TRUE);
}

/*==============================================================
// @brief		プレイヤーのポーズ状態の取得
// @param		なし
// @return		ポーズ状態（bool）
===============================================================*/
bool ADX2LePlayer::IsPause()
{
	return criAtomExPlayer_IsPaused(player_) == CRI_TRUE ? true : false;
}

/*==============================================================
// @brief		指定した再生IDのポーズ状態の取得
// @param		再生ID（CriAtomExPlaybackId）
// @return		ポーズ状態（bool）
===============================================================*/
bool ADX2LePlayer::IsPauseByID(CriAtomExPlaybackId playbackID)
{
	return criAtomExPlayback_IsPaused(playbackID) == CRI_TRUE ? true : false;
}

/*==============================================================
// @brief		プレイヤーの停止
// @param		なし
// @return		なし
===============================================================*/
void ADX2LePlayer::Stop()
{
	criAtomExPlayer_Stop(player_);
}

/*==============================================================
// @brief		指定した再生IDの停止
// @param		再生ID（CriAtomExPlaybackId）
// @return		なし
===============================================================*/
void ADX2LePlayer::StopByID(CriAtomExPlaybackId playbackID)
{
	criAtomExPlayback_Stop(playbackID);
}

// エラーコールバック関数のユーザ実装
void ADX2Le::UserErrorCallback(const CriChar8* errID, CriUint32 p1, CriUint32 p2, CriUint32* parray)
{
	const CriChar8* errmsg;

	// エラーコードからエラー文字列に変換してコンソール出力する
	errmsg = criErr_ConvertIdToMessage(errID, p1, p2);

	const unsigned int dataSize = 256;
	wchar_t wlocal[dataSize + 1] = { 0x00 };

	// マルチバイト文字をUnicodeへ変換する
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, errmsg, dataSize, wlocal, dataSize + 1);

	// コンソール出力する
#if defined(MODE_DEBUG)
	OutputDebugString(wlocal);
#endif

	return;
}

//	メモリ確保関数のユーザ実装
void* ADX2Le::UserAlloc(void* obj, CriUint32 size)
{
	void* ptr;
	ptr = malloc(size);

	return ptr;
}

// メモリ解放関数のユーザ実装
void ADX2Le::UserFree(void* obj, void* ptr)
{
	free(ptr);
}

/*==============================================================
// @brief		初期化処理
// @param		acfファイル名（char*）
// @return		なし
===============================================================*/
void ADX2Le::Initialize(const char* acf)
{
	// エラーコールバック関数の登録
	criErr_SetCallback(UserErrorCallback);

	// メモリアロケータの登録
	criAtomEx_SetUserAllocator(UserAlloc, UserFree, nullptr);

	// ライブラリ初期化
	CriAtomExConfig_PC libConfig;
	CriFsConfig fsConfig;
	criAtomEx_SetDefaultConfig_PC(&libConfig);
	criFs_SetDefaultConfig(&fsConfig);
	libConfig.atom_ex.max_virtual_voices = MAX_VIRTUAL_VOICE;
	libConfig.hca_mx.output_sampling_rate = SAMPLINGRATE_HCAMX;
	fsConfig.num_loaders = MAX_CRIFS_LOADER;
	libConfig.atom_ex.fs_config = &fsConfig;
	criAtomEx_Initialize_PC(&libConfig, nullptr, 0);

	// ストリーミング用バッファの作成
	dbasID_ = criAtomDbas_Create(nullptr, nullptr, 0);

	// ACFファイルの読み込みと登録
	criAtomEx_RegisterAcfFile(nullptr, acf, nullptr, 0);

	// DSPバス設定の登録
	criAtomEx_AttachDspBusSetting("DspBusSetting_0", nullptr, 0);

	// ボイスプールの作成（最大ボイス数変更／最大ピッチ変更／ストリーム再生対応）
	CriAtomExStandardVoicePoolConfig standardVpoolConfig;
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&standardVpoolConfig);
	standardVpoolConfig.num_voices = MAX_VOICE;
	standardVpoolConfig.player_config.max_sampling_rate = MAX_SAMPLING_RATE;
	standardVpoolConfig.player_config.streaming_flag = CRI_TRUE;
	standardVoicePool_ = criAtomExVoicePool_AllocateStandardVoicePool(&standardVpoolConfig, nullptr, 0);

	// HCA-MX再生用：ボイスプールの作成
	CriAtomExHcaMxVoicePoolConfig hcamxVpoolConfig;
	criAtomExVoicePool_SetDefaultConfigForHcaMxVoicePool(&hcamxVpoolConfig);
	hcamxVpoolConfig.num_voices = MAX_VOICE;
	hcamxVpoolConfig.player_config.max_sampling_rate = MAX_SAMPLING_RATE;
	hcamxVpoolConfig.player_config.streaming_flag = CRI_TRUE;
	hcamxVoicePool_ = criAtomExVoicePool_AllocateHcaMxVoicePool(&hcamxVpoolConfig, NULL, 0);

	// プレイヤーの作成
	player_.Create();
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void ADX2Le::Update()
{
	criAtomEx_ExecuteMain();
}

/*==============================================================
// @brief		終了処理
// @param		なし
// @return		なし
===============================================================*/
void ADX2Le::Finalize()
{
	// プレイヤーの破棄
	player_.Release();

	// DSPのデタッチ
	criAtomEx_DetachDspBusSetting();

	// ボイスプールの破棄
	criAtomExVoicePool_Free(hcamxVoicePool_);
	criAtomExVoicePool_Free(standardVoicePool_);

	// ACFの登録解除
	criAtomEx_UnregisterAcf();

	// D-BASの破棄
	criAtomDbas_Destroy(dbasID_);

	// ライブラリの終了
	criAtomEx_Finalize_PC();
}

/*==============================================================
// @brief		プレイヤーの取得
// @param		なし
// @return		プレイヤー（ADX2LePlayer*）
===============================================================*/
ADX2LePlayer* ADX2Le::GetPlayer()
{
	return &player_;
}

/*==============================================================
// @brief		Acbファイルの読み込み
// @param		Acbファイル名（char*）、Awbファイル名（char*）
// @return		なし
===============================================================*/
void ADX2Le::LoadAcb(const char* acb, const char* awb)
{
	player_.LoadAcb(acb, awb);
}

/*==============================================================
// @brief		指定したキューの再生
// @param		キューID（CriAtomExCueId）、音量（float）
// @return		再生ID（CriAtomExPlaybackId）
===============================================================*/
CriAtomExPlaybackId ADX2Le::Play(CriAtomExCueId cueID, float volume)
{
	return player_.Play(cueID, volume);
}

/*==============================================================
// @brief		プレイヤーの音量設定
// @param		音量（float）
// @return		なし
===============================================================*/
void ADX2Le::SetVolume(float volume)
{
	player_.SetVolume(volume);
}

/*==============================================================
// @brief		プレイヤーのポーズ
// @param		なし
// @return		なし
===============================================================*/
void ADX2Le::Pause()
{
	player_.Pause();
}

/*==============================================================
// @brief		プレイヤーのポーズ状態の取得
// @param		なし
// @return		ポーズ状態（bool）
===============================================================*/
bool ADX2Le::IsPause()
{
	return player_.IsPause();
}

/*==============================================================
// @brief		プレイヤーの停止
// @param		なし
// @return		なし
===============================================================*/
void ADX2Le::Stop()
{
	player_.Stop();
}