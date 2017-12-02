/* =====================================================================
//! @param		「SoundManager」ヘッダ
//! @create		樋口 裕太
//! @date		17/12/01
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "../Common/SingletonDirector.h"
#include <string>
#include "ADX2Le.h"

namespace GucchiLibrary
{
	/*
	// @class		SoundManager クラス（Singleton）
	// @content		サウンドマネージャ
	// @use			
	*/
	class SoundManager : public SingletonDirector<SoundManager>
	{
	private:
		friend class SingletonDirector<SoundManager>;

		SoundManager() {}

	public:
		/*
		// @method		Initialize
		// @content		初期化処理
		// @param		Acfファイル名（string）
		// @param		Acbファイル名（string）
		// @param		Awbファイル名（string）
		*/
		void Initialize(std::string acf, std::string acb, std::string awb)
		{
			static const std::string FILE_PATH_SOUND = "Resources/Sounds/";
			static const std::string EXT_ACF = ".acf";
			static const std::string EXT_ACB = ".acb";
			static const std::string EXT_AWB = ".awb";

			// ファイル名の指定
			std::string filePathAcf = FILE_PATH_SOUND + acf + EXT_ACF;
			std::string filePathAcb = FILE_PATH_SOUND + acb + EXT_ACB;
			std::string filePathAwb = FILE_PATH_SOUND + awb + EXT_AWB;

			// サウンドデータの読み込み
			ADX2Le::Initialize(filePathAcf.c_str());
			ADX2Le::LoadAcb(filePathAcb.c_str(), filePathAwb.c_str());
		}

		/*
		// @method		Update
		// @content		更新処理
		*/
		void Update()
		{
			ADX2Le::Update();
		}

		/*
		// @method		PlayAudio
		// @content		音の再生
		// @param		キューID（int）
		*/
		void PlayAudio(int audioID)
		{
			ADX2Le::Play(audioID);
		}

		/*
		// @method		StopAudio
		// @content		音の停止
		*/
		void StopAudio()
		{
			ADX2Le::Stop();
		}

		/*
		// @method		Dispose
		// @content		終了処理
		*/
		void Dispose()
		{
			ADX2Le::Finalize();
		}
	};
}