#pragma once
#include "common.h"

class DotEaterScene : public GameScene {

	typedef GameScene super;

public:

	// 生成関数
	CREATE_FUNC(DotEaterScene);

public:

	DotEaterScene();
	~DotEaterScene();

	virtual void initialize() override;
	virtual void finalize() override;
	virtual void enter() override;
	virtual void leave() override;
	virtual bool input() override;
	virtual void process(float delta) override;
	//パックマンの更新
	bool collision( );
	void getDot( );

private:
	cocos2d::Sprite *_pPacck;
	cocos2d::Sprite *_pSprite[ 130 ];
	int _tips[10][ 13 ];
	int _pPosiX;
	int _pPosiY;
	int _pStatus;
	int _pMoveX;
	int _pMoveY;
	int _reserveX;
	int _reserveY;
	int _reserveStatus;
	int _moveCount;
};
