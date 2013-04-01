//
//  CCCoverFlowCell.cpp
//  CCCoverFlowTest
//
//  Created by 陶 然景 on 13-4-1.
//
//

#include "CCCoverFlowCell.h"

CCCoverFlowCell::CCCoverFlowCell()
{
    
}

CCCoverFlowCell::~CCCoverFlowCell()
{
    
}

CCCoverFlowCell *CCCoverFlowCell::create(int index)
{
    CCCoverFlowCell *cell = new CCCoverFlowCell();
    cell->setIdx(index);
    
    CCSprite* pSprite = CCSprite::create("Icon@2x.png");
    
    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(pSprite->getContentSize().width/2, pSprite->getContentSize().height/2) );
    cell->setContentSize(pSprite->getContentSize());
    
    // add the sprite as a child to this layer
    cell->addChild(pSprite, 0);
    
    return cell;

}