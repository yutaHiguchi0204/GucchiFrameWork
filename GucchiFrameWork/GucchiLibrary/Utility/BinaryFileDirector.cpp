/* =====================================================================
//! @param		「BinaryFileDirector」ソース（バイナリファイル管理）
//! @create		樋口 裕太
//! @date		17/11/27
===================================================================== */

// ヘッダファイルのインクルード
#include "BinaryFileDirector.h"
#include <cassert>
#include <d3d11_1.h>
#include <fstream>

// 名前空間
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

// コンストラクタ
BinaryFile::BinaryFile()
	: size_(0)
{
}

// ムーブコンストラクタ
BinaryFile::BinaryFile(BinaryFile&& _in)
{
	data_ = std::move(_in.data_);
	size_ = _in.size_;
}

/*==============================================================
// @brief		バイナリデータのリセット
// @param		なし
// @return		なし
===============================================================*/
void BinaryFile::DataReset()
{
	data_.reset(new char[size_]);
}

/*==============================================================
// @brief		バイナリファイルの読み込み（全体）
// @param		ファイル名（wstring）
// @return		バイナリファイル（BinaryFile）
===============================================================*/
BinaryFile BinaryFileDirector::LoadBinaryFile(const wstring fileName)
{
	BinaryFile bin;

	// ファイル読み込み準備
	ifstream ifs;

	// ファイルを開く
	ifs.open(fileName.c_str(), ios::in | ios::binary);

	// エラー処理
	if (!ifs)
	{
		OutputDebugString(L"BinaryFile opening failed.");
		assert(ifs);
	}

	// ファイルサイズを取得
	ifs.seekg(0, fstream::end);
	streamoff eofPos = ifs.tellg();
	ifs.clear();
	ifs.seekg(0, fstream::beg);
	streamoff begPos = ifs.tellg();
	bin.SetSize(static_cast<unsigned int>(eofPos - begPos));

	// メモリ確保
	bin.DataReset();

	// ファイルの先頭からバッファへデータをコピー
	ifs.read(bin.GetData(), bin.GetSize());

	// ファイルを閉じる
	ifs.close();

	return move(bin);
}

/*==============================================================
// @brief		バイナリファイルの読み込み（一部分）
// @param		ファイル名（wstring）
// @return		バイナリファイル（BinaryFile）
===============================================================*/
BinaryFile BinaryFileDirector::LoadBinaryFile(const wstring fileName, int part)
{
	BinaryFile bin;

	// ファイル読み込み準備
	ifstream ifs;

	// ファイルを開く
	ifs.open(fileName.c_str(), ios::in | ios::binary);

	// エラー処理
	if (!ifs)
	{
		OutputDebugString(L"BinaryFile opening failed.");
		assert(ifs);
	}

	// ファイルサイズを取得
	ifs.seekg(part * sizeof(unsigned int));
	bin.SetSize(sizeof(unsigned int));

	// メモリ確保
	bin.DataReset();

	// ファイルの先頭からバッファへデータをコピー
	ifs.read(bin.GetData(), bin.GetSize());

	// ファイルを閉じる
	ifs.close();

	return move(bin);
}

/*==============================================================
// @brief		バイナリファイルの書込み
// @param		ファイル名（wstring）、バイナリデータ（BinaryFile）
// @return		なし
===============================================================*/
void BinaryFileDirector::SaveBinaryFile(const wstring fileName, const BinaryFile& data)
{
	// ファイル読み込み準備
	ifstream ifs;

	// ファイルを開く
	ifs.open(fileName.c_str(), ios::out | ios::binary | ios::trunc);

	// エラー処理
	if (!ifs)
	{
		OutputDebugString(L"BinaryFile opening failed.");
		assert(ifs);
	}
}