#include "CPlayer.h"
#include "CKey.h"
#include "CBullet.h"
#define ANICNT 30  //アニメーションの切り替え
CPlayer*CPlayer::spInstance = 0;
//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;

CPlayer::CPlayer()
: mFx(1.0f), mFy(0.0f)
, FireCount(0)
, mAniCnt(0)
{
	mTag = EPLAYER;
	spInstance = this;
}

void CPlayer::Update() {

	//staticメソッドはどこからでも呼べる
	if (CKey::Push('A')) {
		x -= 3;
		mFx = -1;
		mFy = 0;
	}
	if (CKey::Push('D')) {
		x += 3;
		mFx = 1;
		mFy = 0;
	}
	if (CKey::Push('W')) {
		y += 3;
		mFx = 0;
		mFy = 1;
		}

	if (CKey::Push('S')) {
		y -= 2;
		mFx = 0;
		mFy = -1;
	}

	//スペースキーで弾発射
	//0より大きいとき1減算する
	if (FireCount > 0) {
		FireCount--;
	}
	//FireContが0で、かつ、スペースキーで弾発射
	else if( CKey::Once(' ')) {
		CBullet *Bullet = new CBullet();
		//発射位置の設定
		Bullet->x = x;
		Bullet->y = y;
		//移動の値を設定
		Bullet->mFx = mFx * 4;
		Bullet->mFy = mFy * 4;
		//有効にする
		Bullet->mEnabled = true;
		//プレイヤーの弾を設定
		Bullet->mTag = CRectangle::EPLAYERBULLET;
		FireCount = 40;
	}
}

void CPlayer::Render() {
	mAniCnt++;
	mAniCnt %= ANICNT;
	if (mAniCnt < ANICNT / 2)
	{
		if (mFx >= 0)
		{
			CRectangle::Render(Texture, 130, 162, 162, 130);
		}
		else
		{
			CRectangle::Render(Texture, 162, 130, 162, 130);
		}
	}
	else
	{
		if (mFx >= 0)
		{
			CRectangle::Render(Texture, 162, 194, 162, 130);
		}
		else
		{
			CRectangle::Render(Texture, 194, 162, 162, 130);
		}
	}
}


void CPlayer::Collision(CRectangle *ri, CRectangle *ry) {
	if (ry->mTag == EBLOCK) {
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			//abs(x) xの絶対値を求める
			//移動量が少ない方向だけ移動させる
			if (abs(mx) < abs(my)) {
				//Rectをxだけ移動する
				x += mx;
			}
			else {
				//Rectをyだけ移動する
				y += my;
			}
		}
	}
}
