/* =====================================================================
//! @param		�uGameMain�v�\�[�X
//! @create		��� �T��
//! @date		17/10/12
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameMain.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

/*==============================================================
// @brief		����������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void GameMain::Initialize()
{
	// ���C�u�����C���^�t�F�[�X�̏�����
	renderer_ = make_unique<SpriteRenderer>();

	// TODO: �Q�[���֘A�̏�����

	// �X�v���C�g�摜�̓ǂݍ���
	test_ = factory_.CreateSpriteFromFile(L"cat", Vector2(100.0f));
	test_->Initialize(WINDOW_MIDDLE);
	test2_ = factory_.CreateSpriteFromFile(L"cat", Vector2(100.0f));
	test2_->Initialize(WINDOW_MIDDLE);
	test2_->SetAngle(XMConvertToRadians(180.0f));

	// �o�^
	renderer_->RegisterSprite(test_.get());
	renderer_->RegisterSprite(test2_.get(), 0);
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void GameMain::Update()
{
	// TODO: �Q�[���֘A�̍X�V

	StepTimer& timer = StepTimer::GetInstance();
	if (timer.GetFrameCount() > 120)
	{
		renderer_->SetOrder(test2_.get(), 1);
	}
}

/*==============================================================
// @brief		�`�揈��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void GameMain::Render()
{
	// �o�^���ꂽ�X�v���C�g�̕`��
	renderer_->Draw();

	// TODO: �Q�[���֘A�̕`��
}

/*==============================================================
// @brief		�I������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void GameMain::Finalize()
{
	// TODO: �Q�[���֘A�̏I������
}