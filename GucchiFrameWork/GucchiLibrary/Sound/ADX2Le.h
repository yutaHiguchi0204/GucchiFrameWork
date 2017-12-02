/* =====================================================================
//! @param		「ADX2Le」ヘッダ
//! @create		樋口 裕太
//! @date		17/12/01
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <cri_adx2le.h>

namespace GucchiLibrary
{
	/*
	// @class		ADX2LePlayer クラス
	// @content		音楽の再生・停止などを制御するクラス
	// @use			サウンドマネージャで使用
	*/
	class ADX2LePlayer
	{
	private:
		// Acbハンドル
		CriAtomExAcbHn acbHandle_;

		// プレイヤーハンドル
		CriAtomExPlayerHn player_;

	public:
		// コンストラクタ
		ADX2LePlayer();

		/*
		// @method		Create
		// @content		プレイヤーの作成
		*/
		void Create();

		/*
		// @method		LoadAcb
		// @content		Acbファイルの読み込み
		// @param		acbファイル名（char*）
		// @param		awbファイル名（char*）　：　デフォルト（nullptr）
		*/
		void LoadAcb(const char* acb, const char* awb = nullptr);
		
		/*
		// @method		Release
		// @content		プレイヤーの解放
		*/
		void Release();

		/*
		// @method		Play
		// @content		指定したキューの再生
		// @param		キューID（CriAtomExCueId）
		// @param		音量（float）　：　デフォルト（1.0f）
		// @return		再生ID（CriAtomExPlaybackId）
		*/
		CriAtomExPlaybackId Play(CriAtomExCueId cueID, float volume = 1.0f);

		/*
		// @method		SetVolume
		// @content		音量設定
		// @param		音量（float）
		*/
		void SetVolume(float volume);

		/*
		// @method		SetVolumeByID
		// @content		指定した再生IDの音量設定
		// @param		再生ID（CriAtomExPlaybackId）
		// @param		音量（float）
		*/
		void SetVolumeByID(CriAtomExPlaybackId playbackID, float volume);

		/*
		// @method		Pause
		// @content		プレイヤーの一時停止
		*/
		void Pause();

		/*
		// @method		PauseByID
		// @content		指定した再生IDの一時停止
		// @param		再生ID（CriAtomExPlaybackId）
		*/
		void PauseByID(CriAtomExPlaybackId playbackID);

		/*
		// @method		IsPause
		// @content		プレイヤーのポーズ状態の取得
		// @return		ポーズ状態（bool）
		*/
		bool IsPause();

		/*
		// @method		IsPauseByID
		// @content		指定した再生IDのポーズ状態の取得
		// @param		再生ID（CriAtomExPlaybackId）
		// @return		ポーズ状態（bool）
		*/
		bool IsPauseByID(CriAtomExPlaybackId playbackID);

		/*
		// @method		Stop
		// @content		プレイヤーの停止
		*/
		void Stop();

		/*
		// @method		StopByID
		// @content		指定した再生IDの停止
		*/
		void StopByID(CriAtomExPlaybackId playbackID);

		/* アクセッサ */

		inline CriAtomExPlayerHn GetPlayerHandle() const { return player_; }
	};

	/*
	// @class		ADX2Le クラス
	// @content		ADX2Leに関する関数をまとめたクラス
	// @use			サウンドマネージャで使用
	*/
	class ADX2Le
	{
	private:
		// 最大ボイス数を増やすための関連パラメータ
		static const int MAX_VOICE;
		static const int MAX_VIRTUAL_VOICE;
		static const int MAX_CRIFS_LOADER;

		// 最大サンプリングレート（ピッチ変更含む）
		static const int MAX_SAMPLING_RATE;

		// HCA-MXコーデックのサンプリングレート
		static const int SAMPLINGRATE_HCAMX;

		static CriAtomExVoicePoolHn	standardVoicePool_;
		static CriAtomExVoicePoolHn	hcamxVoicePool_;
		static CriAtomDbasId		dbasID_;

		// プレイヤー
		static ADX2LePlayer player_;

	private:
		// エラーコールバック関数のユーザ実装
		static void  UserErrorCallback(const CriChar8* errID, CriUint32 p1, CriUint32 p2, CriUint32* parray);

		//	メモリ確保関数のユーザ実装
		static void* UserAlloc(void* obj, CriUint32 size);

		// メモリ解放関数のユーザ実装
		static void  UserFree(void* obj, void* ptr);

	public:
		/*
		// @method		Initialize（static）
		// @content		初期化処理
		// @param		acfファイル名（char*）
		*/
		static void Initialize(const char* acf);

		/*
		// @method		Update（static）
		// @content		更新処理
		*/
		static void Update();

		/*
		// @method		Finalize（static）
		// @content		終了処理
		*/
		static void Finalize();

		/*
		// @method		GetPlayer（static）
		// @content		プレイヤーの取得
		// @return		プレイヤー（ADX2LePlayer*）
		*/
		static ADX2LePlayer* GetPlayer();

		/*
		// @method		LoadAcb（static）
		// @content		Acbファイルの読み込み
		// @param		Acbファイル名（char*）
		// @param		Awbファイル名（char*）　：　デフォルト（nullptr）
		*/
		static void LoadAcb(const char* acb, const char* awb = nullptr);

		/*
		// @method		Play（static）
		// @content		指定したキューの再生
		// @param		キューID（CriAtomExCueId）
		// @param		音量（float）　：　デフォルト（1.0f）
		// @return		再生ID（CriAtomExPlaybackId）
		*/
		static CriAtomExPlaybackId Play(CriAtomExCueId cueID, float volume = 1.0f);

		/*
		// @method		SetVolume（static）
		// @content		プレイヤーの音量設定
		// @param		音量（float）
		*/
		static void SetVolume(float volume);

		/*
		// @method		Pause（static）
		// @content		プレイヤーのポーズ
		*/
		static void Pause();

		/*
		// @method		IsPause（static）
		// @content		プレイヤーのポーズ状態の取得
		// @return		ポーズ状態
		*/
		static bool IsPause();

		/*
		// @method		Stop（static）
		// @content		プレイヤーの停止
		*/
		static void Stop();
	};
}