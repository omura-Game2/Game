#ifndef CPLAYER_H
#define CPLAYER_H

#include "CRectangle.h"

class CPlayer : public CRectangle {
public:
	int mFx, mFy;
	int FireCount;
	CPlayer();
	void Update();
	int mAniCnt; //�A�j���[�V�����p�J�E���^
	void Render();
	static CPlayer*spInstance;

	void Collision(CRectangle *i, CRectangle *y);
	
};

#endif
