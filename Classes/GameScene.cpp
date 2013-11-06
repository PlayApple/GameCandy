//
//  GameScene.cpp
//  HelloCpp
//
//  Created by LiuYanghui on 13-11-1.
//
//

#include "GameScene.h"

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init()){
        return false;
    }
    initData();
    return true;
}

void GameScene::initData()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    auto mapBg = Sprite::create("map.png");
    mapBg->setPosition(Point(visibleSize.width * .5 + origin.x, visibleSize.height * .5 + origin.y));
    this->addChild(mapBg);
    
    
    
    auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    
    EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    
    
    m_box = new GameBox(Size(kBoxWidth, kBoxHeight));
    m_box->layer = this;
    m_box->setLock(true);
}

void GameScene::onEnterTransitionDidFinish()
{
    auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    
    EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(listener, this);
    
    m_box->check();
}

bool GameScene::onTouchBegan(Touch *touch, Event * event)
{
    operationTile(touch->getLocation());
    return true;
}
void GameScene::onTouchEnded(Touch *touch, Event * event){}
void GameScene::onTouchCancelled(Touch *touch, Event * event){}
void GameScene::onTouchMoved(Touch *touch, Event * event)
{
    operationTile(touch->getLocation());
}

void GameScene::operationTile(Point touchPos)
{
    if(m_box->isLocked()) return;
    
    int x = (touchPos.x -kStartX) / kTileSize;
	int y = (touchPos.y -kStartY) / kTileSize;
	
	if (m_selectedTile && m_selectedTile->x ==x && m_selectedTile->y == y) return;
    
    GameTile *tile = m_box->objectAtXandY(x, y);
    if(m_selectedTile && m_selectedTile->nearTile(tile)){
        m_box->setLock(true);
        this->changeWithTileABandSel(m_selectedTile, tile, callfuncND_selector(GameScene::checkSenderandData));
        m_selectedTile = NULL;
    }else{
        m_selectedTile = tile;
        this->afterOneShineTrun(tile->sprite);
    }
}

void GameScene::changeWithTileABandSel(GameTile* a,GameTile* b,SEL_CallFuncND sel)
{
    FiniteTimeAction* actionA = Sequence::create(MoveTo::create(kMoveTileTime, b->pixPosition()),
                                                     CCCallFuncND::create(this, sel, a),
                                                     NULL);
    FiniteTimeAction* actionB = Sequence::create(MoveTo::create(kMoveTileTime, a->pixPosition()),
                                                     CCCallFuncND::create(this, sel, b),
                                                     NULL);
    a->sprite->runAction(actionA);
    b->sprite->runAction(actionB);
    a->trade(b);
}

void GameScene::checkSenderandData(Node* sender,void* data)
{
	if(NULL == m_firstOne){
		m_firstOne = (GameTile*)data;
		return;
	}
	bool result = m_box->check();
	if (result){
        m_box->setLock(false);
    }
	else{
        changeWithTileABandSel((GameTile*)data, m_firstOne, callfuncND_selector(GameScene::backcheckSenderandData));
	}
    m_firstOne = NULL;
}

void GameScene::backcheckSenderandData(Node* sender, void* data)
{
    if(NULL == m_firstOne){
        m_firstOne = (GameTile*)data;
        return;
    }
    m_firstOne = NULL;
    m_box->setLock(false);
}

void GameScene::afterOneShineTrun(Node* sender)
{
    Sprite* asprite = (Sprite*)sender;
    if(m_selectedTile && asprite == m_selectedTile->sprite){
        Sprite* sprite = asprite;
        FiniteTimeAction* someAction =
        Sequence::create(ScaleTo::create(kMoveTileTime, 0.5f),
                           ScaleTo::create(kMoveTileTime, 1.0f),
                           CallFuncN::create(CC_CALLBACK_1(GameScene::afterOneShineTrun, this)),
                           NULL);
        sprite->runAction(someAction);
    }
}


