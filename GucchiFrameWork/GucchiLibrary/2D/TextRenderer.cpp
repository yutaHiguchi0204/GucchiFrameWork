/* =====================================================================
//! @param		�uTextRenderer�v�\�[�X
//! @create		��� �T��
//! @date		17/10/26
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "TextRenderer.h"
#include <SpriteFont.h>
#include "GucchiLibrary.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;

// �����o�֐��̒�`

/*==============================================================
// @brief		�e�L�X�g�̓o�^
// @param		�e�L�X�g�iText*�j
// @return		�Ȃ�
===============================================================*/
void TextRenderer::RegisterText(Text* text)
{
	textList_.push_back(*text);
}

/*==============================================================
// @brief		�A�N�e�B�u��Ԃ̕ύX
// @param		�e�L�X�g�iText*�j�A�A�N�e�B�u��ԁibool�j
// @return		�Ȃ�
===============================================================*/
void TextRenderer::SetActive(Text* text, bool active)
{
	text->SetActive(active);
}

/*==============================================================
// @brief		�e�L�X�g�`��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void TextRenderer::Draw()
{
	DeviceResources& deviceResource = DeviceResources::GetInstance();
	DirectXToolKidResources& dxtk = DirectXToolKidResources::GetInstance();

	// �o�b�`�����J�n
	dxtk.GetSpriteBatch()->Begin(SpriteSortMode::SpriteSortMode_Deferred, deviceResource.GetCommonStates()->NonPremultiplied());

	// �`�揈��
	for (auto text : textList_)
	{
		// �A�N�e�B�u��Ԃ̃X�v���C�g�̂ݕ\��
		if (text.GetActive())
		{
			// ���_�ݒ�
			Vector2 origin = dxtk.GetSpriteFont()->MeasureString(text.GetString().c_str()) / 2.f;

			// �`��
			dxtk.GetSpriteFont()->DrawString(dxtk.GetSpriteBatch().get(), text.GetString().c_str(), text.GetPos(), text.GetColor(), 0.f, origin, text.GetFontSize() / DEFAULT_FONT_SIZE);
		}
	}

	// �o�b�`�����I��
	dxtk.GetSpriteBatch()->End();
}