/* =====================================================================
//! @param		�uModelCache�v�w�b�_
//! @create		��� �T��
//! @date		17/11/15
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <CommonStates.h>
#include <Effects.h>
#include <map>
#include <Model.h>
#include <string>
#include "../Common/SingletonDirector.h"

namespace GucchiLibrary
{
	// �N���X�̒�`
	class ModelCache : public SingletonDirector<ModelCache>
	{
	private:
		std::map<std::wstring, std::unique_ptr<DirectX::Model>> models_;
		DirectX::EffectFactory* factory_;

	private:
		friend class SingletonDirector<ModelCache>;

		ModelCache() {}

	public:
		DirectX::Model* LoadModel(const std::wstring cmoFileName, DirectX::EffectFactory* factory);
	};
}