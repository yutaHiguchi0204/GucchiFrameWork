/* =====================================================================
//! @param		�uInterpolater�v�w�b�_�i��ԃ��C�u�����j
//! @create		��� �T��
//! @date		17/11/09
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "../Common/SingletonDirector.h"
#include <d3d11_1.h>
#include <SimpleMath.h>

namespace GucchiLibrary
{
	// �N���X�̒�`
	class Interpolater : public SingletonDirector<Interpolater>
	{
	private:
		float startTime_;
		float nowTime_;
		bool isNowLerp_;

	private:
		friend class SingletonDirector<Interpolater>;

		Interpolater() {}

	public:
		// ���`���
		float LinearLerp(float start, float end, float time, float* objTimer);
		DirectX::SimpleMath::Vector2 LinearLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		DirectX::SimpleMath::Vector3 LinearLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		DirectX::SimpleMath::Vector4 LinearLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);

		// �񎟕�ԁi�オ�����j
		float EaseInLerp(float start, float end, float time, float* objTimer);
		DirectX::SimpleMath::Vector2 EaseInLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		DirectX::SimpleMath::Vector3 EaseInLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		DirectX::SimpleMath::Vector4 EaseInLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);

		// �񎟕�ԁi�悪�����j
		float EaseOutLerp(float start, float end, float time, float* objTimer);
		DirectX::SimpleMath::Vector2 EaseOutLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		DirectX::SimpleMath::Vector3 EaseOutLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		DirectX::SimpleMath::Vector4 EaseOutLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);

		// �O�����
		float EaseInOutLerp(float start, float end, float time, float* objTimer);
		DirectX::SimpleMath::Vector2 EaseInOutLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		DirectX::SimpleMath::Vector3 EaseInOutLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		DirectX::SimpleMath::Vector4 EaseInOutLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);
	};
}