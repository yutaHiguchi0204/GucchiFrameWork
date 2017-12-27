/* =====================================================================
//! @param		�uSceneManager�v�\�[�X
//! @create		��� �T��
//! @date		17/10/30
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "PlayScene.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

/*==============================================================
// @brief		����������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void PlayScene::Initialize()
{
	// �S�V�[�����ʏ���������
	IScene::CommonInitialize();

	spr_ = spriteFactory_.CreateSpriteFromFile(L"cat", Vector2(100.0f, 100.0f));
	spr_->SetPos(WINDOW_MIDDLE);
	spriteRenderer_.RegisterSprite(spr_.get());

	t_ = make_unique<Text>(L"�Ă���", WINDOW_MIDDLE);
	t_->SetAnchor(ANCHOR_MM);
	textRenderer_.RegisterText(t_.get());

	point_ = make_unique<Primitive>();
	point_->Entry(Vector2(64.0f, 64.0f), Color(1, 1, 0));
	primitiveRenderer_.RegisterPrimitive(point_.get());

	triangle_ = make_unique<Primitive>();
	triangle_->Entry(false, Vector2(400.0f, 100.0f), Vector2(200.0f, 400.0f), Vector2(600.0f, 400.0f), Color(0, 1, 1));
	primitiveRenderer_.RegisterPrimitive(triangle_.get());

	emitter_ = make_unique<Emitter>();
	particleRenderer_.RegisterEmitter(emitter_.get(), L"test", L"effect1");
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void PlayScene::Update()
{
	// �S�V�[�����ʍX�V����
	IScene::CommonUpdate();

	// �G�~�b�^�[�̍X�V
	emitter_->Entry(
		1.0f,
		VertexPositionColorTexture(Vector3(0.0f, 0.5f, 0.0f), Color(2.0f, 0.0f, 0.0f, 1.0f), Vector2(0.3f, 0.0f)),
		VertexPositionColorTexture(Vector3(0.0f, 0.0f, 0.0f), Color(2.0f, 1.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f)),
		Asset3D::BLEND_MODE::ADDITIVE
	);
}

/*==============================================================
// @brief		�`�揈��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void PlayScene::Draw()
{
	// �S�V�[�����ʕ`�揈��
	IScene::CommonDraw();
}

/*==============================================================
// @brief		�I������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void PlayScene::Finalize()
{
	// �S�V�[�����ʏI������
	IScene::CommonFinalize();
}