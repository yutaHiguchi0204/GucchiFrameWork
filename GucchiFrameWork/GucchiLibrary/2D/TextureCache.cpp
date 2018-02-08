/* =====================================================================
//! @param		�uTextureCache�v�\�[�X
//! @create		��� �T��
//! @date		17/10/17
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "TextureCache.h"
#include <cassert>
#include <WICTextureLoader.h>
#include "../Common/Constant.h"
#include "../Common/DeviceResources.h"
#include "../System/DebugSystem.h"

// ���O���
using namespace DirectX;
using namespace GucchiLibrary;
using namespace Microsoft::WRL;
using namespace std;

// �����o�֐��̒�`

/*==============================================================
// @brief		�e�N�X�`���ǂݍ���
// @param		�t�@�C�����iwstring�j
// @return		�e�N�X�`���iTexture*�j
===============================================================*/
Texture* TextureCache::LoadTexture(const wstring fileName)
{
	// ���łɓǂݍ��ݍς݂Ȃ�ǂݍ��܂Ȃ�
	if (textures_.count(fileName) == 0)
	{
		// �G���[�����p
		HRESULT res;

		// �f�o�C�X����
		DeviceResources& deviceResources = DeviceResources::GetInstance();

		// �e�N�X�`���֘A
		ComPtr<ID3D11ShaderResourceView> shaderResourceView;
		ComPtr<ID3D11Resource> resource;
		ComPtr<ID3D11Texture2D> resourceTexture;

		// �t���p�X�쐬
		wstring fullPath = FILE_PATH_SPRITE + fileName + EXT_PNG;

		// �e�N�X�`���̍쐬
		res = CreateWICTextureFromFile(deviceResources.GetD3DDevice(), fullPath.c_str(), resource.GetAddressOf(), shaderResourceView.ReleaseAndGetAddressOf());

		// �G���[����
		if (FAILED(res))
		{
			DebugSystem::DebugLog(L"Texture loading failed.", true);
			assert(false);
		}

		// ���\�[�X���e�N�X�`���Ƃ��ĉ��߂���
		res = resource.As(&resourceTexture);

		// �G���[����
		if (FAILED(res))
		{
			DebugSystem::DebugLog(L"This resource is not texture.", true);
			assert(false);
		}

		// �e�N�X�`�����擾
		CD3D11_TEXTURE2D_DESC desc;
		resourceTexture->GetDesc(&desc);

		// �ǂݍ��񂾏����i�[
		unique_ptr<Texture> texture = make_unique<Texture>();
		texture->SetDesc(desc);
		texture->SetShaderResourceView(shaderResourceView.Get());

		textures_[fileName] = move(texture);
	}

	return textures_[fileName].get();
}