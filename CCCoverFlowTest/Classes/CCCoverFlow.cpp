//
//  CCCoverFlow.cpp
//  CCCoverFlowTest
//
//  Created by 陶 然景 on 13-4-1.
//
//

#include "CCCoverFlow.h"
#include "CCCoverFlowCell.h"

const float SLIDING_MENU_OFFSET = 270;
const float TABLE_VIEW_OFFSET = 91;
const float SCROLL_TOLERANCE = 10; //this is the tolerance for when a scroll will override a button press
const int TAG_FOR_SLIDE_MENU_ITEM = 200; //tag used to identify child
const float SLIDING_CELLS_TRANSITION_TIME = .1f;

CCCoverFlow::CCCoverFlow()
:m_pArrSlidingMenuItem(NULL)
,m_pTableView(NULL)
,m_pCurrentShownedIndex(0)
{
    
}

CCCoverFlow::~CCCoverFlow()
{
    CC_SAFE_RELEASE_NULL(m_pArrSlidingMenuItem);
    CC_SAFE_RELEASE_NULL(m_pTableView);
}

bool CCCoverFlow::init()
{
    //test
    m_pCurrentShownedIndex = 5;
    if (!CCLayer::init())
    {
        return false;
    }
    
    this->setSlidingItems(CCArray::create());
    
    this->setTableView(CCCoverFlowTableView::create(this, CCSize(480, 100)));
    this->getTableView()->setDirection(kCCScrollViewDirectionHorizontal);
    this->getTableView()->setDelegate(this);
    this->addChild(this->getTableView());
    
    for (int i = 0; i < 20; i ++)
    {
        CCCoverFlowCell *cell = CCCoverFlowCell::create(i);
        this->addCell(cell);
    }
    m_pTableView->reloadData();
    return true;
}

void CCCoverFlow::addCell(CCCoverFlowCell *cell)
{
    m_pArrSlidingMenuItem->addObject(cell);
    
    //m_pTableView->reloadData();
    //this->getContainer()->setPosition(ccp(0,m_tableView->getViewSize().height - sizeOfTable(m_tableView).height));
}

void CCCoverFlow::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

CCSize CCCoverFlow::cellSizeForTable(CCTableView *table)
{
    if (m_pArrSlidingMenuItem->count() > 0)
    {
        return CCSizeMake(((CCCoverFlowCell*)m_pArrSlidingMenuItem->objectAtIndex(0))->getContentSize().width / 2,
                          ((CCCoverFlowCell*)m_pArrSlidingMenuItem->objectAtIndex(0))->getContentSize().height);
    }
    else
    {
        return CCSizeMake(0, 0);
    }
}

CCTableViewCell* CCCoverFlow::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCCoverFlowCell *cell = (CCCoverFlowCell*)table->dequeueCell();
    if (!cell) {
        cell = new CCCoverFlowCell();
        cell->autorelease();
    }
    cell->setIdx(idx);
    if (((CCNode*)m_pArrSlidingMenuItem->objectAtIndex(idx))->getParent() != NULL)
    {
        ((CCNode*)m_pArrSlidingMenuItem->objectAtIndex(idx))->removeFromParentAndCleanup(false);
    }
    
    cell->removeAllChildrenWithCleanup(false);
    
    int zOrder = 0;
    zOrder = abs(m_pCurrentShownedIndex - cell->getIdx());
    
    cell->addChild((CCNode*)m_pArrSlidingMenuItem->objectAtIndex(idx),0 - zOrder,TAG_FOR_SLIDE_MENU_ITEM);
    cell->setZOrder(0 - zOrder);
    
    CCOrbitCamera *orbit;
    orbit = CCOrbitCamera::create(10, 1, 0, 0, 360, 0, 0);
    cell->runAction(CCSequence::create( orbit , NULL));

    return cell;
}

int CCCoverFlow::getCurrentAngel(int index)
{
    int delta = index - m_pCurrentShownedIndex;
    if (index == m_pCurrentShownedIndex) // cell is on the left.
    {
        return 0;
    }
    
    if (index == 6)
    {
        return 360;
    }
    
    return 0;
}

unsigned int CCCoverFlow::numberOfCellsInTableView(CCTableView *table)
{
    return m_pArrSlidingMenuItem->count();
}

void CCCoverFlow::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}
