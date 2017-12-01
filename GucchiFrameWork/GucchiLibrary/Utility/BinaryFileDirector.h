/* =====================================================================
//! @param		「BinaryFileDirector」ヘッダ（バイナリファイル管理）
//! @create		樋口 裕太
//! @date		17/11/27
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <memory>
#include <string>

namespace GucchiLibrary
{
	/*
	// @class		BinaryFile クラス
	// @content		バイナリファイル
	*/
	class BinaryFile
	{
	private:
		std::unique_ptr<char[]> data_;		// バイナリファイルから取得したデータ
		unsigned int size_;					// データサイズ

	public:
		BinaryFile();						// デフォルトコンストラクタ
		BinaryFile(BinaryFile&& _in);		// ムーブコンストラクタ
		virtual ~BinaryFile() {}

		/*
		// @method		ResetData
		// @content		バイナリデータのリセット
		*/
		void ResetData();

		/* アクセッサ */

		void SetSize(unsigned int size)			{ size_ = size; }

		inline char* GetData() const			{ return data_.get(); }
		inline unsigned int GetSize() const		{ return size_; }
	};

	/*
	// @class		BinaryFileDirector クラス
	// @content		バイナリファイルを扱うクラス
	*/
	class BinaryFileDirector
	{
	public:
		/*
		// @method		LoadBinaryFile（static）
		// @content		バイナリファイルの読み込み（全体）
		// @param		ファイル名（wstring）
		// @return		バイナリファイル（BinaryFile）
		*/
		static BinaryFile LoadBinaryFile(const std::wstring fileName);

		/*
		// @method		LoadBinaryFile（static）
		// @content		バイナリファイルの読み込み（一部分）
		// @param		ファイル名（wstring）
		// @return		バイナリファイル（BinaryFile）
		*/
		static BinaryFile LoadBinaryFile(const std::wstring fileName, int part);

		/*
		// @method		SaveBinaryFile（static）
		// @content		バイナリファイルの書込み
		// @param		ファイル名（wstring）
		// @param		バイナリデータ（BinaryFile）
		*/
		static void SaveBinaryFile(const std::wstring fileName, const BinaryFile& data);
	};
}