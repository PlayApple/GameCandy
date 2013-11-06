//
//  GameTile.h
//  HelloCpp
//
//  Created by LiuYanghui on 13-11-1.
//
//

#ifndef __HelloCpp__GameTile__
#define __HelloCpp__GameTile__

#include "cocos2d.h"
#include "GameDefine.h"

USING_NS_CC;

class GameTile: public Node
{
public:
    int x;
    int y;
    int value; // 1 - 6 all kind of candy
    int comboValue; // 1:orientationHori combo candy, 2:orientationVert combo candy
    Sprite* sprite;
    
public:
	GameTile(int ax,int ay);
	~GameTile();
    bool nearTile(GameTile* othertile);
    void trade(GameTile* othertile);
    void changeComboTile(int orient);
    Point pixPosition();
    void refreshDebugInfo();
};

#endif /* defined(__HelloCpp__GameTile__) */
