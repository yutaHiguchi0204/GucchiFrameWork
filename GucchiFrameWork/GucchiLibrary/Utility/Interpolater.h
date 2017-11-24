/* =====================================================================
//! @param		�uInterpolater�v�w�b�_�i��ԃ��C�u�����j
//! @create		��� �T��
//! @date		17/11/09
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <SimpleMath.h>

namespace GucchiLibrary
{
	/*
	// @class		Interpolater �N���X
	// @content		��ԃ��C�u����
	*/
	class Interpolater
	{
	private:
		static float startTime_;
		static float nowTime_;
		static bool isNowLerp_;

	public:
		// ���`���
		static float LinearLerp(float start, float end, float time, float* objTimer);
		static DirectX::SimpleMath::Vector2 LinearLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		static DirectX::SimpleMath::Vector3 LinearLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		static DirectX::SimpleMath::Vector4 LinearLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);

		// �񎟕�ԁi�オ�����j
		static float EaseInLerp(float start, float end, float time, float* objTimer);
		static DirectX::SimpleMath::Vector2 EaseInLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		static DirectX::SimpleMath::Vector3 EaseInLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		static DirectX::SimpleMath::Vector4 EaseInLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);

		// �񎟕�ԁi�悪�����j
		static float EaseOutLerp(float start, float end, float time, float* objTimer);
		static DirectX::SimpleMath::Vector2 EaseOutLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		static DirectX::SimpleMath::Vector3 EaseOutLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		static DirectX::SimpleMath::Vector4 EaseOutLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);

		// �O�����
		static float EaseInOutLerp(float start, float end, float time, float* objTimer);
		static DirectX::SimpleMath::Vector2 EaseInOutLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		static DirectX::SimpleMath::Vector3 EaseInOutLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		static DirectX::SimpleMath::Vector4 EaseInOutLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);
	};
}