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
    
    this->setTableView(CCCoverFlowTableView::create(this, CCSize(960, 300)));
    this->getTableView()->setDirection(kCCScrollViewDirectionHorizontal);
    this->getTableView()->setDelegate(this);
    this->addChild(this->getTableView());
    
    for (int i = 0; i < 1000; i ++)
    {
        CCCoverFlowCell *cell = CCCoverFlowCell::create(i);
        this->addCell(cell);
    }
    m_pTableView->reloadData();
    
//    this->scheduleUpdate();
    
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
        return CCSizeMake(((CCCoverFlowCell*)m_pArrSlidingMenuItem->objectAtIndex(0))->getContentSize().width,
                          ((CCCoverFlowCell*)m_pArrSlidingMenuItem->objectAtIndex(0))->getContentSize().height);
    }
    else
    {
        return CCSizeMake(0, 0);
    }
}

CCTableViewCell* CCCoverFlow::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
//    CCCoverFlowCell *cell = (CCCoverFlowCell*)table->dequeueCell();
//    if (!cell) {
//        cell = CCCoverFlowCell::create(idx);
//        cell->autorelease();
//    }
//    cell->setIdx(idx);
    CCCoverFlowCell *cell = (CCCoverFlowCell*)m_pArrSlidingMenuItem->objectAtIndex(idx);
    
    int zOrder = 0;
    zOrder = abs(m_pCurrentShownedIndex - cell->getIdx());    
    
    cell->setZOrder(0 - zOrder);
    
    cell->setAlphaAndScale(getCurrentAlpha(idx), getCurrentScale(idx));
    return cell;
}

int CCCoverFlow::getCurrentAngel(int index)
{
    int delta = index - m_pCurrentShownedIndex;
    if (index == m_pCurrentShownedIndex) // cell is on the left.
    {
        return 0;
    }
//    
//    if (index == 6)
//    {
//        return 360;
//    }
//    
    return 90;
}

float CCCoverFlow::getCurrentScale(int index)
{
    if (abs(index - this->getCurrentShownedIndex()) > 5)
    {
        return 0.0f;
    }
    
    float contentX = this->m_pTableView->getContainer()->getPosition().x;
    float currentX = contentX + cellSizeForTable(m_pTableView).width * index;
    float mid = this->cellSizeForTable(m_pTableView).width * 5;
    if (currentX <= mid)
    {
        return 1.0f / mid * currentX;
    }
    else
    {
        float max = mid * 2;
        float k = -1.0f / (max - mid);
        return k * currentX - k * max;
    }
}

int CCCoverFlow::getCurrentAlpha(int index)
{
    float contentX = this->m_pTableView->getContainer()->getPosition().x;
    float currentX = contentX + cellSizeForTable(m_pTableView).width * index;
    float mid = this->cellSizeForTable(m_pTableView).width * 5;
    if (currentX <= mid)
    {
        return 255 / mid * currentX;
    }
    else
    {
        float max = mid * 2;
        float k = -255 / (max - mid);
        return k * currentX - k * max;
    }
}

CCPoint CCCoverFlow::offsetFromIndex(int index)
{
    CCPoint offset = CCPointZero;
    CCCoverFlowCell* slidingMenuItem;
    
    //calculate the offset up to the cell number indicated by index
    for (int i = 0; i < index; ++i)
    {
        slidingMenuItem = (CCCoverFlowCell*)m_pArrSlidingMenuItem->objectAtIndex(i);
        switch (this->getTableView()->getDirection())
        {
            case kCCScrollViewDirectionHorizontal:
                offset = CCPointMake(offset.x + slidingMenuItem->getContentSize().width, 0);
                break;
            default:
                offset = CCPointMake(0, offset.y + slidingMenuItem->getContentSize().height);
                break;
        }
    }
    return offset;
}

int CCCoverFlow::indexFromOffset(CCPoint point)
{
    //iterating through cells of the table and searching for the location of the point
    
    int index = 0; //keeps track of the current index
    float offsetAtIndex = 0; //keeps track of the offset at index
        
    switch (m_pTableView->getDirection())
    {
        case kCCScrollViewDirectionHorizontal:
            
            //the search for the index that point.x falls within.
            while (point.x > offsetAtIndex)
            {
                offsetAtIndex += ((CCNode*)m_pArrSlidingMenuItem->objectAtIndex(index))->getContentSize().width;
                ++index;
                
                if (index >= m_pArrSlidingMenuItem->count())
                    break;
            }
            break;
        default:
            //the search for the index that point.y falls within.
            while (point.y > offsetAtIndex)
            {
                offsetAtIndex += ((CCNode*)m_pArrSlidingMenuItem->objectAtIndex(index))->getContentSize().height;
                ++index;
                
                if (index >= m_pArrSlidingMenuItem->count())
                    break;
            }
            break;
    }
    --index;
    
    index = MAX(0, index);
    index = MIN(index, m_pArrSlidingMenuItem->count()-1);
    
    return index;
}

unsigned int CCCoverFlow::numberOfCellsInTableView(CCTableView *table)
{
    return m_pArrSlidingMenuItem->count();
}

void CCCoverFlow::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    float contentX = this->getTableView()->getContainer()->getPosition().x;
    
    CCCoverFlowCell *cell = (CCCoverFlowCell*)m_pArrSlidingMenuItem->objectAtIndex(0);
    m_pCurrentShownedIndex = indexFromOffset(ccp((cell->getContentSize().width * 5) - contentX, 0));
    m_pTableView->reloadData();
    
}

void CCCoverFlow::update(float dt)
{

   
}
