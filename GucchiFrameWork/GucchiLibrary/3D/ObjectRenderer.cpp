/* =====================================================================
//! @param		�uObjectRenderer�v�\�[�X
//! @create		��� �T��
//! @date		17/11/06
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "ObjectRenderer.h"
#include "ModelCache.h"
#include "../Common/DeviceResources.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

/*==============================================================
// @brief		�I�u�W�F�N�g�̓o�^
// @param		�I�u�W�F�N�g�iObject*�j
// @return		�Ȃ�
===============================================================*/
void ObjectRenderer::RegisterObject(Object* object)
{
	objectList_.push_back(*object);
}

/*==============================================================
// @brief		�A�N�e�B�u��Ԃ̕ύX
// @param		�I�u�W�F�N�g�iObject*�j�A�A�N�e�B�u��ԁibool�j
// @return		�Ȃ�
===============================================================*/
void ObjectRenderer::SetActive(Object* object, bool active)
{
	object->SetActive(active);
}

/*==============================================================
// @brief		�A�N�e�B�u��Ԃ̃I�u�W�F�N�g��`��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void ObjectRenderer::Draw()
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();

	// �e���ڂ̏���
	ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();
	CommonStates* states = deviceResources.GetCommonStates();

	// �`�揈��
	for (auto& object : objectList_)
	{
		// �A�N�e�B�u��Ԃ̃I�u�W�F�N�g�̂ݕ\��
		if (object.GetActive())
		{
			// �`��O�̏���
			object.DrawApply();

			// �J����
			Camera* camera = object.GetCamera();

			// ���Z�`��̏ꍇ�͌��Z�w�������
			if (object.GetBlendMode() == Asset3D::BLEND_MODE::SUBTRACTIVE)
			{
				object.GetModel()->Draw(context, *states, object.GetWorld(), camera->GetView(), camera->GetProjection(), false, [&]() { 
					context->OMSetBlendState(object.GetBlendStateSubtract(), nullptr, 0xffffffff);
				});
			}
			else
			{
				object.GetModel()->Draw(context, *states, object.GetWorld(), camera->GetView(), camera->GetProjection());
			}
		}
	}
}

/*==============================================================
// @brief		���X�g���Z�b�g
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void ObjectRenderer::Reset()
{
	objectList_.clear();
}

/*==============================================================
// @brief		�u�����h�ݒ�
// @param		�u�����h���[�h�iBLEND_MODE�j
// @return		�Ȃ�
===============================================================*/
void ObjectRenderer::SetBlendState(Asset3D::BLEND_MODE mode)
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();
	CommonStates* states = deviceResources.GetCommonStates();

	// �u�����h���[�h�ݒ�
	switch (mode)
	{
	case Asset3D::BLEND_MODE::ALPHA:		// �A���t�@�u�����h
		context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xffffffff);
		break;

	case Asset3D::BLEND_MODE::ADDITIVE:		// ���Z�u�����h
		context->OMSetBlendState(states->Additive(), nullptr, 0xffffffff);
		break;

	default:
		context->OMSetBlendState(states->Opaque(), nullptr, 0xffffffff);
		break;
	}
}

/*==============================================================
// @brief		���Z�`��ݒ�
// @param		�u�����h�X�e�[�g�iID3D11BlendState*�j
// @return		�Ȃ�
===============================================================*/
void ObjectRenderer::SetSubtractive(ID3D11BlendState* blendState)
{
	// ���Z�`��p�̃u�����h�X�e�[�g���쐬
	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// �u�����h�X�e�[�g�̍쐬
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	if (FAILED(deviceResources.GetD3DDevice()->CreateBlendState(&desc, &blendState)))
	{
		OutputDebugString(L"Create blend state is failed.");
		assert(0);
	}
}

/*==============================================================
// @brief		�I�u�W�F�N�g�̃��C�e�B���O�𖳌��ɂ���
// @param		���f���iModel�j
// @return		�Ȃ�
===============================================================*/
void ObjectRenderer::DisableLighting(Model* model)
{
	if (model)
	{
		// ���f�����̑S���b�V������
		ModelMesh::Collection::const_iterator it_mesh = model->meshes.begin();
		for (; it_mesh != model->meshes.end(); it_mesh++)
		{
			ModelMesh* modelmesh = it_mesh->get();
			assert(modelmesh);

			// ���b�V�����̑S���b�V���p�[�c����
			std::vector<std::unique_ptr<ModelMeshPart>>::iterator it_meshpart = modelmesh->meshParts.begin();
			for (; it_meshpart != modelmesh->meshParts.end(); it_meshpart++)
			{
				ModelMeshPart* meshpart = it_meshpart->get();
				assert(meshpart);

				// ���b�V���p�[�c�ɃZ�b�g���ꂽ�G�t�F�N�g��BasicEffect�Ƃ��Ď擾
				std::shared_ptr<IEffect> ieff = meshpart->effect;
				BasicEffect* eff = dynamic_cast<BasicEffect*>(ieff.get());
				if (eff != nullptr)
				{
					// ���Ȕ������ő�l��
					eff->SetEmissiveColor(Vector3(1, 1, 1));

					// �G�t�F�N�g�Ɋ܂ޑS�Ă̕��s�������ɂ��ď�������
					for (int i = 0; i < BasicEffect::MaxDirectionalLights; i++)
					{
						// ���C�g�𖳌��ɂ���
						eff->SetLightEnabled(i, false);
					}
				}
			}
		}
	}
}

/*==============================================================
// @brief		�I�u�W�F�N�g�̐���
// @param		�t�@�C�����iwstring�j
// @return		�Ȃ�
===============================================================*/
unique_ptr<Object> ObjectFactory::CreateObjectFromFile(const wstring fileName)
{
	unique_ptr<Object> object = make_unique<Object>();

	// ���f���̊i�[�ɂ�����
	ModelCache& cache = ModelCache::GetInstance();

	// ���f���̓ǂݍ���
	Model* model = cache.LoadModel(fileName, object->GetEffectFactory());

	// ���f�����C�e�B���O�𖳌��ɂ���
	ObjectRenderer& objectRenderer_ = ObjectRenderer::GetInstance();
	objectRenderer_.DisableLighting(model);

	// �I�u�W�F�N�g�ɃZ�b�g
	object->SetModel(model);
	object->SetCamera(camera_);

	return std::move(object);
}