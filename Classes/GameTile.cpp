//
//  GameTile.cpp
//  HelloCpp
//
//  Created by LiuYanghui on 13-11-1.
//
//

#include "GameTile.h"
#include <math.h>

GameTile::GameTile(int ax,int ay)
{
    x = ax;
    y = ay;
    comboValue = 0;
}

GameTile::~GameTile(void)
{
    sprite = NULL;
}

bool GameTile::nearTile(GameTile* othertile)
{
	return (x == othertile->x && abs(y - othertile->y) == 1) ||
           (y == othertile->y && abs(x - othertile->x) == 1);
}

void GameTile::trade(GameTile* othertile)
{
    Sprite* tempSprite = sprite;
	int tempValue = value;
    int tempComboValue = comboValue;
    
	sprite = othertile->sprite;
	value = othertile->value;
    comboValue = othertile->comboValue;
    
	othertile->sprite = tempSprite;
	othertile->value = tempValue;
    othertile->comboValue = tempComboValue;
    
    tempSprite = NULL;
}

void GameTile::changeComboTile(int orient)
{
    if (!sprite) return;
    
    String* name;
    if (orient == OrientationHori) {
        comboValue = 1;
        name = String::createWithFormat("%d_2.png", value);
    }else{
        comboValue = 2;
        name = String::createWithFormat("%d_3.png", value);
    }
    sprite->setDisplayFrame(SpriteFrame::create(name->getCString(), Rect(0, 0, 90, 90)));
}

Point GameTile::pixPosition()
{
	return Point(kStartX + x * kTileSize +kTileSize/2.0f,kStartY + y * kTileSize +kTileSize/2.0f);
}

void GameTile::refreshDebugInfo()
{
    if (true or !sprite) return;
    sprite->removeAllChildrenWithCleanup(true);
    
    auto labValue = LabelTTF::create(String::createWithFormat("%d-%d", value, comboValue)->getCString(), "Arial", 40);
    labValue->setColor(Color3B(255, 0, 0));
    labValue->setPosition(Point(kTileSize * .5, kTileSize * .5));
    sprite->addChild(labValue);
}