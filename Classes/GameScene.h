//
//  GameScene.h
//  HelloCpp
//
//  Created by LiuYanghui on 13-11-1.
//
//

#ifndef __HelloCpp__GameScene__
#define __HelloCpp__GameScene__

#include "cocos2d.h"
#include "GameBox.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    void changeWithTileABandSel(GameTile* a, GameTile* b, SEL_CallFuncND sel);
    void checkSenderandData(Node* sender, void* data);
    void backcheckSenderandData(Node* sender, void* data);
    void onEnterTransitionDidFinish();
    void afterOneShineTrun(Node* sprite);
    
    virtual bool onTouchBegan(Touch *touch, Event * event);
    virtual void onTouchEnded(Touch *touch, Event * event);
    virtual void onTouchCancelled(Touch *touch, Event * event);
    virtual void onTouchMoved(Touch *touch, Event * event);
    
private:
	GameBox* m_box;
	GameTile* m_selectedTile;
	GameTile* m_firstOne;
private:
    void initData();
    void operationTile(Point touchPos);
};


#endif /* defined(__HelloCpp__GameScene__) */
