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
using namespace DirectX::SimpleMath;
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
	if (order != -1)
	{
		auto itr = spriteList_.begin();

		// �w��ꏊ�ɓo�^�i����ɂ��\�������ς��j
		int orderNum = 0;
		while (orderNum < order - 1)
		{
			itr++;
			orderNum++;
		}

		spriteList_.insert(itr, *sprite);
		return;
	}

	// �X�v���C�g�̓o�^
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
// @brief		�X�v���C�g�̕\����
// @param		�X�v���C�g�iSprite*�j�A�\�����iint�j
// @return		�Ȃ�
===============================================================*/
void SpriteRenderer::SetOrder(Sprite* sprite, int order)
{
	auto itr = spriteList_.begin();

	// �w��ʒu������
	int orderNum = 0;
	while (orderNum <= order)
	{
		itr++;
		orderNum++;
	}

	// ���݂̈ʒu���擾
	auto now = find(spriteList_.begin(), spriteList_.end(), *sprite);

	// �w��ʒu�Ɉړ�
	spriteList_.splice(itr, spriteList_, now);
}

/*==============================================================
// @brief		�A�N�e�B�u��Ԃ̃X�v���C�g��`��
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
	for (auto& sprite : spriteList_)
	{
		// �A�N�e�B�u��Ԃ̃X�v���C�g�̂ݕ\��
		if (sprite.GetActive())
		{
			DrawSprite(&sprite);
		}
	}

	// �o�b�`�����I��
	dxtk.GetSpriteBatch()->End();
}

/*==============================================================
// @brief		�X�v���C�g�̕`��
// @param		�X�v���C�g�iSprite*�j
// @return		�Ȃ�
===============================================================*/
void SpriteRenderer::DrawSprite(Sprite* sprite)
{
	DirectXToolKidResources& dxtk = DirectXToolKidResources::GetInstance();

	// �e����̍��W�ݒ�
	Vector2 position = sprite->GetPos();
	if (sprite->GetParent())
	{
		position += GetParentSpritePos(sprite->GetParent());
	}

	// �`��
	dxtk.GetSpriteBatch()->Draw(sprite->GetTexture()->GetShaderResourceView().Get(), position, sprite->GetRect(), Colors::White, sprite->GetAngle(), Vector2(sprite->GetSize().x / 2, sprite->GetSize().y / 2));

	// �q�X�v���C�g������Ȃ�q�ǂ����`��
	if (sprite->GetChildren().size() != 0)
	{
		for (auto& child : sprite->GetChildren())
		{
			if (child->GetActive())
			{
				DrawSprite(child);
			}
		}
	}
}

/*==============================================================
// @brief		�e�̈ʒu��H��
// @param		�e�X�v���C�g�iSprite*�j
// @return		�ŏI�ʒu�iVector2�j
===============================================================*/
Vector2 SpriteRenderer::GetParentSpritePos(Sprite* sprite)
{
	Vector2 localPos = sprite->GetPos();

	// ��������ɐe������Ȃ炳��ɒH��
	if (sprite->GetParent())
	{
		localPos += GetParentSpritePos(sprite->GetParent());
	}

	return localPos;
}

/*==============================================================
// @brief		���X�g���Z�b�g
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void SpriteRenderer::Reset()
{
	spriteList_.clear();
}

/*==============================================================
// @brief		�X�v���C�g�̐���
// @param		�t�@�C�����iwstring�j�A�摜�T�C�Y�iVector2�j
// @return		�X�v���C�g�iunique_ptr<Sprite>�j
===============================================================*/
unique_ptr<Sprite> SpriteFactory::CreateSpriteFromFile(const wstring fileName, const Vector2& size)
{
	unique_ptr<Sprite> sprite = make_unique<Sprite>(size);

	// �e�N�X�`���̊i�[�ɂ�����
	TextureCache& cache = TextureCache::GetInstance();

	// �e�N�X�`���̓ǂݍ���
	Texture* texture = cache.LoadTexture(fileName);
	sprite->SetTexture(texture);

	return std::move(sprite);
}