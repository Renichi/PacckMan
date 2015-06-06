#include "DotEaterScene.h"

USING_NS_CC;

DotEaterScene::DotEaterScene()
{
	_reserveX = 1;
	_reserveY = 0;
	_reserveStatus = 2;
	_moveCount = 0;
}

DotEaterScene::~DotEaterScene()
{
}

void DotEaterScene::initialize()
{
	// レイヤーの作成
	auto *pLayer = GameLayer::create();
	this->addChild(pLayer);

	// タイトルの作成
	/*auto *pTitleLabel = Label::create("DotEaterScene", "fonts/arial.ttf", 24);
	pTitleLabel->setAnchorPoint(Vec2(0, 1));
	pTitleLabel->setColor(Color3B(128, 128, 128));
	pTitleLabel->setPosition(100, RESOLUTION_HEIGHT-100);
	pTitleLabel->setZOrder(10);
	pLayer->addChild(pTitleLabel);*/

	//チップの配置
	int map[10][13] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,1,1,0,0,1,1,1,0,0,1},
  {1,0,1,0,1,0,0,0,0,1,0,0,1},
  {1,0,1,0,1,0,0,0,0,1,0,0,1},
  {1,0,1,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,0,0,0,1,1,1,1,1,1,1},
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
			count++;
		}
	}

	//パックマン
	//初期位置
	_pPosiX = 150;
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

void DotEaterScene::finalize()
{
}

void DotEaterScene::enter()
{
}

void DotEaterScene::leave()
{
}

bool DotEaterScene::input()
{
	// キー判定
	const auto &key = GetKeyManager();
	if( key.isPressRepeatFast( KeyCode::KEY_UP_ARROW ) )
	{
		_reserveX = 0;
		_reserveY = 1;
		_reserveStatus = 0;
		return true;
	} else if( key.isPressRepeatFast( KeyCode::KEY_DOWN_ARROW ) )
	{
		_reserveX = 0;
		_reserveY = -1;
		_reserveStatus = 1;
		return true;
	} else if( key.isPressRepeatFast( KeyCode::KEY_RIGHT_ARROW ) ) {
		_reserveX = 1;
		_reserveY = 0;
		_reserveStatus = 2;
		return true;
	} else if( key.isPressRepeatFast( KeyCode::KEY_LEFT_ARROW ) ) {
		_reserveX = -1;
		_reserveY = 0;
		_reserveStatus = 3;
		return true;
	}

	return false;
}

void DotEaterScene::process(float delta)
{
	_moveCount++;
	//自動方向転換(仮)
	while ( this->collision( ) ) {
		int pattern = rand( ) % 4;
		if ( pattern == _pStatus ) continue;

		switch ( pattern ) {
		case 0:
			_reserveX = 0;
			_reserveY = 1;
			_reserveStatus = 0;
			break;
		case 1:
			_reserveX = 0;
			_reserveY = -1;
			_reserveStatus = 1;
			break;
		case 2:
			_reserveX = 1;
			_reserveY = 0;
			_reserveStatus = 2;
			break;
		case 3:
			_reserveX = -1;
			_reserveY = 0;
			_reserveStatus = 3;
			break;
		}
	}
	if ( _moveCount >= 50 ) {
		_pMoveX = _reserveX;
		_pMoveY = _reserveY;
		_pStatus = _reserveStatus;
		_moveCount = 0;
	}
	this->getDot( );
	_pPosiX += _pMoveX;
	_pPosiY += _pMoveY;
	_pPacck->setPosition(_pPosiX, _pPosiY);


}

//壁のあたり判定
bool DotEaterScene::collision( ) {
	int sPosiX = 0;
	int sPosiY = 0;
	float beginY = RESOLUTION_HEIGHT - 25;
	float offsetY = -50;
	int tipposiX = 0;
	int tipposiY = 0;

	switch( _pStatus ) {
	//↑
	case 0:
		sPosiX = _pPosiX;
		sPosiY = 480 - _pPosiY;
		tipposiX = sPosiX / 50;
		tipposiY = sPosiY / 50;
		if ( _tips[ tipposiY ][ tipposiX ] == 1 ) {
			_pPosiY = beginY + offsetY * tipposiY - 25;  
			return true;
		}
		break;
	//↓
	case 1:
		sPosiX = _pPosiX;
		sPosiY = 480 - _pPosiY;
		tipposiX = sPosiX / 50;
		tipposiY = sPosiY / 50 + 1;
		if ( _tips[ tipposiY ][ tipposiX ] == 1 ) {
			_pPosiY = beginY + offsetY * tipposiY + 76;
			return true;
		}
		break;
	//→
	case 2:
		sPosiX = _pPosiX + 50;
		sPosiY = RESOLUTION_HEIGHT - _pPosiY;
		tipposiX = sPosiX / 50;
		tipposiY = (sPosiY + 1 ) / 50;
		if ( _tips[ tipposiY ][ tipposiX ] == 1 ) {
			_pPosiX = sPosiX - 51;
			return true;
		}
		break;
	//←
	case 3:
		sPosiX = _pPosiX - 1;
		sPosiY = RESOLUTION_HEIGHT - _pPosiY;
		tipposiX = sPosiX / 50;
		tipposiY = (sPosiY + 1 ) / 50;
		if ( _tips[ tipposiY ][ tipposiX  ] == 1) {
			_pPosiX = sPosiX + 2;
			return true;
		}
		break;
	}
	return false;
}

//ドットの取得
void DotEaterScene::getDot( ) {
	// レイヤーの作成
	int sPosiX = 0;
	int sPosiY = 0;
	float beginY = RESOLUTION_HEIGHT - 25;
	float offsetY = -50;
	int tipposiX = 0;
	int tipposiY = 0;

	switch( _pStatus ) {
	//↑
	case 0:
		sPosiX = _pPosiX;
		sPosiY = 480 - _pPosiY;
		tipposiX = sPosiX / 50;
		tipposiY = sPosiY / 50;
		if ( _tips[ tipposiY ][ tipposiX ] == 0 ) {
			if ( sPosiY == ( tipposiY * 50 ) ) {
				int position = 13 * tipposiY + tipposiX + 1;
				_pSprite[ position ]->setPosition( 1000, 1000 );
			}
		}
		break;
	//↓
	case 1:
		sPosiX = _pPosiX;
		sPosiY = 480 - _pPosiY;
		tipposiX = sPosiX / 50;
		tipposiY = sPosiY / 50;
		if ( _tips[ tipposiY ][ tipposiX ] == 0 ) {
			if ( sPosiY == ( tipposiY * 50 ) ) {
				int position = 13 * tipposiY + tipposiX;
				_pSprite[ position ]->setPosition( 1000, 1000 );
			}
		}
		break;
	//→
	case 2:
		sPosiX = _pPosiX + 50;
		sPosiY = RESOLUTION_HEIGHT - _pPosiY;
		tipposiX = sPosiX / 50;
		tipposiY = (sPosiY + 1 ) / 50;
		if ( _tips[ tipposiY ][ tipposiX ] == 0 ) {
			if ( sPosiX == ( tipposiX * 50 ) + 25 ) {
				int position = 13 * tipposiY + tipposiX;
				_pSprite[ position ]->setPosition( 1000, 1000 );
			}
		}
		break;
	//←
	case 3:
		sPosiX = _pPosiX - 1;
		sPosiY = RESOLUTION_HEIGHT - _pPosiY;
		tipposiX = sPosiX / 50;
		tipposiY = (sPosiY + 1 ) / 50;
		if ( _tips[ tipposiY ][ tipposiX  ] == 0 ) {
			if ( sPosiX == ( tipposiX * 50 ) ) {
				int position = 13 * tipposiY + tipposiX;
				_pSprite[ position ]->setPosition( 1000, 1000 );
			}
		}
		break;
	}
}
