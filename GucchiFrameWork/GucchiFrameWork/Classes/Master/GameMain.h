/* =====================================================================
//! @param		�uGameMain�v�w�b�_
//! @create		��� �T��
//! @date		17/10/12
===================================================================== */
#pragma once

// �N���X�̒�`
class GameMain
{
public:
	GameMain() {};
	virtual ~GameMain() {};

	void Initialize();			// ����������
	void Update();				// �X�V����
	void Render();				// �`�揈��
	void Finalize();			// �I������
};