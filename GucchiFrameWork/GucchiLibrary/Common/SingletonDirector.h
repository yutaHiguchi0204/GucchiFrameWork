/* =====================================================================
//! @param		�uSingletonDirector�v�w�b�_
//! @create		��� �T��
//! @date		17/10/09
===================================================================== */
#pragma once

namespace GucchiLibrary
{
	// �N���X�̒�`
	template <class T> class SingletonDirector
	{
	public:
		// �C���X�^���X�̐���
		static T& GetInstance()
		{
			static T object;
			return object;
		}

	protected:
		// �R���X�g���N�^
		SingletonDirector() {};

	private:
		// �R�s�[�Ƒ���h�~
		SingletonDirector(const SingletonDirector &) = delete;
		SingletonDirector& operator=(const SingletonDirector &) = delete;
		SingletonDirector(SingletonDirector &&) = delete;
		SingletonDirector& operator=(SingletonDirector &&) = delete;
	};
}