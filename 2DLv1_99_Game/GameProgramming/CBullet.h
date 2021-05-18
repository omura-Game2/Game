#ifndef CBULLET_H
#define CBULLET_H

#include "CRectangle.h"

/*
CBullet
�e�N���X
CRectangle�N���X���p������
�e�FCRectangle�N���X
�q�FCBullet�N���X
*/
class CBullet : public CRectangle {
public:
	int mFx, mFy;	//�ړ���

	//�f�t�H���g�R���X�g���N�^
	CBullet();
	//�X�V����
	void Update();

	//�`�揈��
	void Render();

	void Collision(CRectangle *i, CRectangle *y);

};

#endif
