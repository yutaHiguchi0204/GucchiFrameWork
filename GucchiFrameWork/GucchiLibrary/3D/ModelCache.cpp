/* =====================================================================
//! @param		�uModelCache�v�\�[�X
//! @create		��� �T��
//! @date		17/11/15
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "ModelCache.h"
#include "../Common/Constant.h"
#include "../Common/DeviceResources.h"

// ���O���
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

/*==============================================================
// @brief		���f���ǂݍ���
// @param		�t�@�C�����iwstring�j�A�G�t�F�N�g�t�@�N�g���iEffectFactory*�j
// @return		���f���iModel*�j
===============================================================*/
Model* ModelCache::LoadModel(const wstring cmoFileName, EffectFactory* factory)
{
	// ���łɓǂݍ��ݍς݂Ȃ�ǂݍ��܂Ȃ�
	if (models_.count(cmoFileName) == 0)
	{
		// �f�o�C�X����
		DeviceResources& deviceResources = DeviceResources::GetInstance();

		// ���f������
		unique_ptr<Model> model = make_unique<Model>();

		// �t���p�X�쐬
		wstring fullPath = FILE_PATH_MODEL + cmoFileName + EXT_CMO;

		// ���f���쐬
		model = Model::CreateFromCMO(deviceResources.GetD3DDevice(), fullPath.c_str(), *factory);

		// ���f���i�[
		models_[cmoFileName] = std::move(model);
	}

	return models_[cmoFileName].get();
}