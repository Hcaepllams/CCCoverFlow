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
    cell->setContentSize(pSprite->getContentSize());
    cell->setAnchorPoint(ccp(0.5f, 0.5f));
    
    // add the sprite as a child to this layer
    cell->addChild(pSprite, 0);
    
    CCString *string = CCString::createWithFormat("%d", index);
    CCLog ("%d", index);
    CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
    label->setPosition(CCPointZero);
    label->setAnchorPoint(CCPointZero);
    label->setTag(123);
    cell->addChild(label);
    
    return cell;
}

void CCCoverFlowCell::setAlphaAndScale(GLubyte opacity, float scale)
{
    CCObject *child = NULL;
    CCARRAY_FOREACH(this->getChildren(), child)
    {
        if (dynamic_cast<CCSprite*>(child))
        {
            CCSprite *sprite = (CCSprite*)child;
            sprite->setOpacity(opacity);
            sprite->setScale(scale);
        }
    }
    CCTableViewCell::setScale(scale);
    
}