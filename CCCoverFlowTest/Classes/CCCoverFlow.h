//
//  CCCoverFlow.h
//  CCCoverFlowTest
//
//  Created by 陶 然景 on 13-4-1.
//
//

#ifndef __CCCoverFlowTest__CCCoverFlow__
#define __CCCoverFlowTest__CCCoverFlow__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCCoverFlowCell.h"
#include "CCCoverFlowTableView.h"

USING_NS_CC;
USING_NS_CC_EXT;


class CCCoverFlow:public CCLayer,  public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
public:
    CCCoverFlow();
    ~CCCoverFlow();
    
    CREATE_FUNC(CCCoverFlow);
    
    virtual bool init();
    
    void addCell(CCCoverFlowCell* cell);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    CC_SYNTHESIZE(unsigned int, m_pCurrentShownedIndex, CurrentShownedIndex);
    
    CC_SYNTHESIZE_RETAIN(CCArray*, m_pArrSlidingMenuItem, SlidingItems);
    CC_SYNTHESIZE_RETAIN(CCCoverFlowTableView*, m_pTableView, TableView);
    
private:
    int getCurrentAngel(int index);
    float getCurrentScale(int index);
    int getCurrentAlpha(int index);
    void update(float dt);
    
protected:
    CCPoint offsetFromIndex(int index);
    int indexFromOffset(CCPoint point);
};



#endif /* defined(__CCCoverFlowTest__CCCoverFlow__) */
