/* =====================================================================
//! @param		�uSpriteRenderer�v�\�[�X
//! @create		��� �T��
//! @date		17/10/17
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "SpriteRenderer.h"
#include "../Common/DeviceResources.h"

// ���O���
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

/*==============================================================
// @brief		�X�v���C�g�̓o�^
// @param		�X�v���C�g�iSprite*�j�A�\�����iint�j
//				�f�t�H���g��-1�ɐݒ肳��Ă��܂����A���X�g�̈�ԍŌ�ɓo�^�����Ƃ����Ӗ��ł�
// @return		�Ȃ�
===============================================================*/
void SpriteRenderer::RegisterSprite(Sprite* sprite, int order)
{
	// �X�v���C�g�̓o�^
	// �����݂͕\�����֌W�Ȃ��������ɒǉ����邾��
	spriteList_.push_back(*sprite);
}

/*==============================================================
// @brief		�A�N�e�B�u��Ԃ̕ύX
// @param		�X�v���C�g�iSprite*�j�A�A�N�e�B�u��ԁibool�j
// @return		�Ȃ�
===============================================================*/
void SpriteRenderer::SetActive(Sprite* sprite, bool active)
{
	sprite->SetActive(active);
}

/*==============================================================
// @brief		�A�N�e�B�u��Ԃ̃X�v���C�g��\��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void SpriteRenderer::Draw()
{
	DeviceResources& deviceResource = DeviceResources::GetInstance();
	DirectXToolKidResources& dxtk = DirectXToolKidResources::GetInstance();

	// �o�b�`�����J�n
	dxtk.GetSpriteBatch()->Begin(SpriteSortMode::SpriteSortMode_Deferred, deviceResource.GetCommonStates()->NonPremultiplied());

	// �`�揈��
	for (auto sprite : spriteList_)
	{
		// �A�N�e�B�u��Ԃ̃X�v���C�g�̂ݕ\��
		if (sprite.GetActive())
		{
			dxtk.GetSpriteBatch()->Draw(sprite.GetTexture()->GetShaderResourceView().Get(), sprite.GetPos());
		}
	}

	// �o�b�`�����I��
	dxtk.GetSpriteBatch()->End();
}

/*==============================================================
// @brief		�X�v���C�g�̐���
// @param		�t�@�C�����iwstring�j
// @return		�Ȃ�
===============================================================*/
unique_ptr<Sprite> SpriteFactory::CreateSpriteFromFile(const wstring fileName)
{
	unique_ptr<Sprite> sprite = make_unique<Sprite>();

	// �e�N�X�`���̊i�[�ɂ�����
	TextureCache& cache = TextureCache::GetInstance();

	// �e�N�X�`���̓ǂݍ���
	Texture* texture = cache.LoadTexture(fileName);
	sprite->SetTexture(texture);

	return std::move(sprite);
}