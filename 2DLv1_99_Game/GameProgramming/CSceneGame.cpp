#include "CSceneGame.h"
#include "CTexture.h"
#include "CMap.h"
#include "CKey.h"
#include "CRectangle.h"
#include "CBullet.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CText.h"
#include"CEnemyb.h"
#include"CEnemyr.h"

void CSceneGame::Init() {
	//シーンの設定
	mScene = EGAME;

	Texture.Load("Image.tga");
	//文字画像の読み込み
	CText::mFont.Load("font.tga");

	//クラスのメンバ変数への代入
	CPlayer *Player = new CPlayer();
	Player->x = 250;
	Player->y = -1500;
	Player->w = 25;
	Player->h = 25;
	Player->mEnabled = true;

	int map[20][9] =
	{
		{ 9, 1, 1, 1, 1, 1, 1, 1, 9 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 3, 0, 0, 0, 3, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 2, 0, 2, 0, 4, 0, 4, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 4, 0, 4, 0, 2, 0, 2, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 4, 0, 4, 0, 2, 0, 2, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	};
	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < 9; i++) {
			//mapの要素が1の時、四角形配置
			if (map[j][i] == 1) {
				CMap *Map = new CMap();
				//四角形に値を設定
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 350;
				Map->w = 50;
				Map->h = 50;
			}
			else if (map[j][i] == 2) {
				CEnemy *Enemy = new CEnemy();
				Enemy->x = i * 100 - 350;
				Enemy->y = j * -100 + 250;
				//右へ移動
				Enemy->mFx = -1;
				Enemy->mFy = 0;
			}
			else if (map[j][i] == 3){
				CEnemyb *Enemyb = new CEnemyb();
				Enemyb->x = i * 100 - 350;
				Enemyb->y = j * -100 + 250;
				//右へ移動
				Enemyb->mFx = -1;
				Enemyb->mFy = 0;
			}
			else if (map[j][i] == 4){
				CEnemyr*Enemyr = new CEnemyr();
				Enemyr->x = i * 100 - 350;
				Enemyr->y = j * -100 + 250;
				//左へ移動
				Enemyr->mFx = 1;
				Enemyr->mFy = 0;
			}
			else if (map[j][i] == 9){
				CMap *Map = new CMap();
				//四角形に値を設定
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 350;
				Map->w = 50;
				Map->h = 50;
				myMax = Map->y + Map->h;
			}
		}
	}
}

void CSceneGame::Update() {
	/*
	配列の要素分繰り返す
	配列名.size()
	配列の要素数を取得する
	*/
	for (int i = 0; i < VectorRect.size(); i++) {
		/*
		配列の参照
		配列名[添え字]
		通常の配列同様に添え字で要素にアクセスできる
		*/
		//更新処理
		VectorRect[i]->Update();
	}
	for (int i = 0; i < VectorRect.size() - 1; i++) {
		//衝突処理
		for (int j = i + 1; j < VectorRect.size(); j++) {
			VectorRect[i]->Collision(VectorRect[i], VectorRect[j]);
			VectorRect[j]->Collision(VectorRect[j], VectorRect[i]);
		}
	}

	//リストから削除する
	//イテレータの生成
	std::vector<CRectangle*>::iterator itr;
	//イテレータを先頭
	itr = VectorRect.begin();
	//最後まで繰り返し
	while (itr != VectorRect.end()) {
		if ((*itr)->mEnabled) {
			//次へ
			itr++;
		}
		else {
			//falseのインスタンスを削除
			delete *itr;
			//リストからも削除
			itr = VectorRect.erase(itr);
		}
	}
	//描画範囲変数の作成
	double mLeft = -400.0, mRight = 500.0, mBottm = -250.0, mTop = 250.0;
	//画面範囲下の設定
	mBottm = CPlayer::spInstance->y - 125.0;
	//画面範囲上の設定
	mTop = mBottm + 800.0f;
	if (mTop > myMax)
	{
		float sa = mTop - myMax;
		mTop -= sa;
		mBottm -= sa;
	}
	//画面投影範囲の変更
	//行列をプロジェクションモードへ変更
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();  //行列を初期化
	//2Dの画面を設定
	gluOrtho2D(mLeft, mRight, mBottm, mTop);
	//行列をモデルビューモードへ変更
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();   //行列を初期化

	for (int i = 0; i < VectorRect.size(); i++) {
		//描画処理
		VectorRect[i]->Render();
	}
}

//次のシーンの取得
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}

//デストラクタ
CSceneGame::~CSceneGame() {
	//全てのインスタンスを削除します
	for (int i = 0; i < VectorRect.size(); i++) {
		//インスタンスの削除
		delete VectorRect[i];
	}
	//可変長配列のクリア
	VectorRect.clear();
}
