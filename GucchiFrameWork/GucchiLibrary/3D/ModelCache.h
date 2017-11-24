/* =====================================================================
//! @param		「ModelCache」ヘッダ
//! @create		樋口 裕太
//! @date		17/11/15
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <CommonStates.h>
#include <Effects.h>
#include <map>
#include <Model.h>
#include <string>
#include "../Common/SingletonDirector.h"

namespace GucchiLibrary
{
	/*
	// @class		ModelCache クラス（Singleton）
	// @content		モデル管理用
	// @use			LoadModel関数でロードしたモデルを管理する
	*/
	class ModelCache : public SingletonDirector<ModelCache>
	{
	private:
		std::map<std::wstring, std::unique_ptr<DirectX::Model>> models_;
		DirectX::EffectFactory* factory_;

	private:
		friend class SingletonDirector<ModelCache>;

		ModelCache() {}

	public:
		/*
		// @method		LoadModel
		// @content		モデルのロード
		// @param		モデルファイル名（wstring）
		// @param		エフェクトファクトリ（EffectFactory*）
		*/
		DirectX::Model* LoadModel(const std::wstring cmoFileName, DirectX::EffectFactory* factory);
	};
}