//
//  CCCoverFlowTableView.h
//  CCCoverFlowTest
//
//  Created by 陶 然景 on 13-4-1.
//
//

#ifndef __CCCoverFlowTest__CCCoverFlowTableView__
#define __CCCoverFlowTest__CCCoverFlowTableView__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCCoverFlow;

class CCCoverFlowTableView: public CCTableView {
public:
    
    
    static CCCoverFlowTableView* create(CCCoverFlow* dataSource, CCSize size);
    
   // CCPoint maxContainerOffset();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};
#endif /* defined(__CCCoverFlowTest__CCCoverFlowTableView__) */
