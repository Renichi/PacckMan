#include "LifeGameScene2.h"

USING_NS_CC;

LifeGameScene2::LifeGameScene2()
{
}

LifeGameScene2::~LifeGameScene2()
{
}

void LifeGameScene2::initialize()
{
	// レイヤーの作成
	auto *pLayer = GameLayer::create();
	this->addChild(pLayer);

	// タイトルの作成
	auto *pTitleLabel = Label::create("LifeGame2", "fonts/arial.ttf", 24);
	pTitleLabel->setAnchorPoint(Vec2(0, 1));
	pTitleLabel->setColor(Color3B(128, 128, 128));
	pTitleLabel->setPosition(100, RESOLUTION_HEIGHT-100);
	pTitleLabel->setZOrder(10);
	pLayer->addChild(pTitleLabel);

	//チップの配置
	int map[10][13] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,1,0,0,1,1,1,0,0,1},
  {1,0,0,0,1,0,0,0,0,1,0,0,1},
  {1,0,0,0,1,0,0,0,0,1,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1},
};

	// セル
	float beginX = 20;
	float beginY = RESOLUTION_HEIGHT - 25;
	float offsetX = 50;
	float offsetY = -50;
	int SELL_WIDTH = 5;
	int SELL_HEIGHT = 5;
	int count = 0;

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 13; x++)
		{
			_pSprite[ count ] = Sprite::create("LifeGame/common_base.png");

			switch( map[ y ][ x ] ) {
			case 0:
				beginX = 20;
				beginY = RESOLUTION_HEIGHT - 25;
				offsetX = 50;
				offsetY = -50;
				SELL_WIDTH = 5;
				SELL_HEIGHT = 5;
				break;
			case 1:
				beginX = 0;
				beginY = RESOLUTION_HEIGHT;
				offsetX = 50;
				offsetY = -50;
				SELL_WIDTH = 45;
				SELL_HEIGHT = 45;
				break;
			}
			_pSprite[ count ]->setPosition(beginX + offsetX*x, beginY + offsetY*y);
			_pSprite[ count ]->setAnchorPoint(Vec2(0, 1));
			_pSprite[ count ]->setScale(SELL_WIDTH, SELL_HEIGHT);
			pLayer->addChild(_pSprite[ count ]);
			_tips[ y ][ x ] = map[ y ][ x ]; 
		}
		count++;
	}

	//パックマン
	//初期位置
	_pPosiX = 100;
	_pPosiY = RESOLUTION_HEIGHT - 100;
	//移動方向
	_pMoveX = 1;
	_pMoveY = 0;
	_pStatus = 2;

	_pPacck = Sprite::create( "pacckman/pacck_1.png" );
	//座標
	_pPacck->setPosition(_pPosiX + offsetX, _pPosiY + offsetY);
	//画像の中心点
	_pPacck->setAnchorPoint(Vec2(0, 1));
	pLayer->addChild(_pPacck);
}

void LifeGameScene2::finalize()
{
}

void LifeGameScene2::enter()
{
}

void LifeGameScene2::leave()
{
}

bool LifeGameScene2::input()
{
	float offsetX = 50;
	float offsetY = -50;

	// キー判定
	const auto &key = GetKeyManager();
	if( key.isPressRepeatFast( KeyCode::KEY_UP_ARROW ) )
	{
		_pMoveX = 0;
		_pMoveY = 1;
		_pStatus = 0;
		return true;
	} else if( key.isPressRepeatFast( KeyCode::KEY_DOWN_ARROW ) )
	{
		_pMoveX = 0;
		_pMoveY = -1;
		_pStatus = 1;
		return true;
	} else if( key.isPressRepeatFast( KeyCode::KEY_RIGHT_ARROW ) ) {
		_pMoveX = 1;
		_pMoveY = 0;
		_pStatus = 2;
		return true;
	} else if( key.isPressRepeatFast( KeyCode::KEY_LEFT_ARROW ) ) {
		_pMoveX = -1;
		_pMoveY = 0;
		_pStatus = 3;
		return true;
	}

	return false;
}

void LifeGameScene2::process(float delta)
{
	_pPosiX += _pMoveX;
	_pPosiY += _pMoveY;
	this->collision( );
	_pPacck->setPosition(_pPosiX, _pPosiY);


}

void LifeGameScene2::collision( ) {
	int sPosiX = 0;
	int sPosiY = 0;
	int tipposiX = 0;
	int tipposiY = 0;

	switch( _pStatus ) {
	case 0:
		sPosiX = _pPosiX + 50;
		sPosiY = 480 - _pPosiY;
		tipposiX = sPosiX / 50;
		tipposiY = sPosiY / 50;
		if ( _tips[ tipposiY ][ tipposiX ] == 1 ) {
			_pPosiY = -sPosiY + 480;  
		}
		break;
	case 2:
		sPosiX = _pPosiX + 50;
		sPosiY = 480 - _pPosiY;
		tipposiX = sPosiX / 50;
		tipposiY = sPosiY / 50;
		if ( _tips[ tipposiY ][ tipposiX ] == 1 ) {
			_pPosiX = sPosiX - 51;
		}
		break;
	case 3:
		sPosiX = _pPosiX - 50;
		sPosiY = 480 - _pPosiY;
		tipposiX = sPosiX / 50;
		tipposiY = sPosiY / 50;
		if ( _tips[ tipposiY ][ tipposiX  ] == 1) {
			if ( ( tipposiX + 1 ) * 50 > _pPosiX  ) {
				_pPosiX = sPosiX + 51;
			}
		}
		break;
	}
}
