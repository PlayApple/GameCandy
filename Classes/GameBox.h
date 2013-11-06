//
//  GameBox.h
//  HelloCpp
//
//  Created by LiuYanghui on 13-11-1.
//
//

#ifndef __HelloCpp__GameBox__
#define __HelloCpp__GameBox__

#include "GameTile.h"
#include "GameDefine.h"

USING_NS_CC;

class GameBox: public Node
{
public:
    Layer* layer;
    
private:
    bool m_lock;
    GameTile* m_firstTile;
    GameTile* m_secondTile;
    Size m_size;
    Array* m_content;
    Array* m_readyToRemoveTiles;
    GameTile* m_outBorderTile;
    
public:
	GameBox(Size asize);
    GameTile* objectAtXandY(int posX,int posY);
    void useCombo(int posX, int posY, int comboValue);
    void checkWith(Orientation orient);
    bool check();
    void removeSprite(Node* sender);
    void afterAllMoveDone();
    bool haveMore();
    int repair();
    int repairSingleColumn(int columnIndex);
    
    inline void setLock(bool lock){m_lock = lock;}
    inline bool isLocked(){return m_lock;}
};

#endif /* defined(__HelloCpp__GameBox__) */
