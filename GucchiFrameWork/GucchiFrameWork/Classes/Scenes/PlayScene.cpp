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
	// �f�t�H���g�J������ݒ�
	camera_ = make_unique<DefaultCamera>(WINDOW_WIDTH, WINDOW_HEIGHT);
	objectFactory_.SetCamera(camera_.get());

	skyDome_ = objectFactory_.CreateObjectFromFile(L"skyDome");

	// �I�u�W�F�N�g�̓o�^
	objectRenderer_.RegisterObject(skyDome_.get());

	// �f�[�^�擾
	wstring wstr[2] = { L"block", L"block2" };
	TipData::TIP_TYPE type[2] = { TipData::TIP_TYPE::NONE, TipData::TIP_TYPE::SOLID };
	vector<vector<int>> data = CSVFileDirector::LoadCSVFile(L"test");
	stage_ = make_unique<MapTip3D>(data, Vector3::One, wstr, 2, type);
	stage_->SetTranslate(Vector3(-2.f, 0.f, -2.f));
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void PlayScene::Update()
{
	// �J�����̍X�V
	camera_->Update();
}

/*==============================================================
// @brief		�`�揈��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void PlayScene::Draw()
{
	
}

/*==============================================================
// @brief		�I������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void PlayScene::Finalize()
{
	
}