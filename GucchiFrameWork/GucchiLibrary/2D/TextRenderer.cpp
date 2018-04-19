/* =====================================================================
//! @param		「TextRenderer」ソース
//! @create		樋口 裕太
//! @date		17/10/26
===================================================================== */

// ヘッダファイルのインクルード
#include "TextRenderer.h"
#include <SpriteFont.h>
#include "../Common/Constant.h"
#include "../Common/DeviceResources.h"

// 名前空間
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

/*==============================================================
// @brief		テキストの登録
// @param		テキスト名（wstring）、文字列（wstring）、表示位置（Vector2）、フォントの色（Color）、フォントサイズ（float）、フォント名（拡張子を除く）（wstring）
// @return		なし
===============================================================*/
void TextRenderer::RegisterText(const std::wstring& name, const std::wstring& str, const Vector2& pos, const Color& color, float fontSize, const std::wstring& font)
{
	Text* text = new Text(str, pos);
	
	// 初期設定
	text->SetColor(color);
	text->SetFontSize(fontSize);
	text->SetFont(font);

	textList_[name] = text;
}

/*==============================================================
// @brief		テキストの登録
// @param		テキスト名（wstring）、テキスト（Text*）
// @return		なし
===============================================================*/
void TextRenderer::RegisterText(const std::wstring& name, Text* text)
{
	if (textList_.count(name))
	{
		textList_[name] = text;
	}
}

/*==============================================================
// @brief		文字列の変更
// @param		テキスト名（wstring）、文字列（wstring）
// @return		なし
===============================================================*/
void TextRenderer::SetString(const std::wstring& name, const std::wstring& str)
{
	if (textList_.count(name))
	{
		textList_[name]->SetString(str);
	}
}

/*==============================================================
// @brief		表示位置の変更
// @param		テキスト名（wstring）、表示位置（Vector2）
// @return		なし
===============================================================*/
void TextRenderer::SetPos(const std::wstring& name, const Vector2& pos)
{
	if (textList_.count(name))
	{
		textList_[name]->SetPos(pos);
	}
}

/*==============================================================
// @brief		アンカーポイントの変更
// @param		テキスト名（wstring）、アンカーポイント（Vector2）
// @return		なし
===============================================================*/
void TextRenderer::SetAnchor(const std::wstring& name, const Vector2& anchor)
{
	if (textList_.count(name))
	{
		textList_[name]->SetAnchor(anchor);
	}
}

/*==============================================================
// @brief		色の変更
// @param		テキスト名（wstring）、色（Color）
// @return		なし
===============================================================*/
void TextRenderer::SetColor(const std::wstring& name, const Color& color)
{
	if (textList_.count(name))
	{
		textList_[name]->SetColor(color);
	}
}

/*==============================================================
// @brief		サイズの変更
// @param		テキスト名（wstring）、フォントサイズ（float）
// @return		なし
===============================================================*/
void TextRenderer::SetFontSize(const std::wstring& name, float fontSize)
{
	if (textList_.count(name))
	{
		textList_[name]->SetFontSize(fontSize);
	}
}

/*==============================================================
// @brief		フォントの種類の変更
// @param		テキスト名（wstring）、フォント（wstring）
// @return		なし
===============================================================*/
void TextRenderer::SetFont(const std::wstring& name, const std::wstring& font)
{
	if (textList_.count(name))
	{
		textList_[name]->SetFont(font);
	}
}

/*==============================================================
// @brief		アクティブ状態の変更
// @param		テキスト名（wstring）、アクティブ状態（bool）
// @return		なし
===============================================================*/
void TextRenderer::SetActive(const std::wstring& name, bool active)
{
	if (textList_.count(name))
	{
		textList_[name]->SetActive(active);
	}
}

/*==============================================================
// @brief		テキスト描画
// @param		なし
// @return		なし
===============================================================*/
void TextRenderer::Draw()
{
	DeviceResources& deviceResource = DeviceResources::GetInstance();
	DirectXToolKidResources& dxtk = DirectXToolKidResources::GetInstance();

	// バッチ処理開始
	dxtk.GetSpriteBatch()->Begin(SpriteSortMode::SpriteSortMode_Deferred, deviceResource.GetCommonStates()->NonPremultiplied());

	// 描画処理
	for (auto text : textList_)
	{
		// アクティブ状態のスプライトのみ表示
		if (text.second->GetActive())
		{
			// アンカーポイントの設定
			Vector2 origin = dxtk.GetSpriteFont()->MeasureString(text.second->GetString().c_str());
			origin *= text.second->GetAnchor();

			// 描画
			dxtk.GetSpriteFont()->DrawString(dxtk.GetSpriteBatch(), text.second->GetString().c_str(), text.second->GetPos(), text.second->GetColor(), 0.f, origin, text.second->GetFontSize() / Text::DEFAULT_FONT_SIZE);
		}
	}

	// バッチ処理終了
	dxtk.GetSpriteBatch()->End();
}

/*==============================================================
// @brief		リストリセット
// @param		なし
// @return		なし
===============================================================*/
void TextRenderer::Reset()
{
	for (auto& text : textList_)
	{
		delete text.second;
	}

	textList_.clear();
}