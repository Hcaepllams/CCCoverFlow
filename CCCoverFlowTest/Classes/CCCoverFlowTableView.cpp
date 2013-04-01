//
//  CCCoverFlowTableView.cpp
//  CCCoverFlowTest
//
//  Created by 陶 然景 on 13-4-1.
//
//

#include "CCCoverFlowTableView.h"
#include "CCCoverFlow.h"

CCCoverFlowTableView* CCCoverFlowTableView::create(CCCoverFlow* dataSource, CCSize size)
{
    CCCoverFlowTableView *table = new CCCoverFlowTableView();
    table->initWithViewSize(size, NULL);
    table->autorelease();
    table->setDataSource(dataSource);
    table->_updateContentSize();
    
    return table;

}

CCPoint CCCoverFlowTableView::maxContainerOffset()
{
    if (m_tViewSize.height <= m_pContainer->getContentSize().height)
    {
        return ccp(0.0f, 0.0f);
    }
    else
    {
        return ccp(m_tViewSize.width - m_pContainer->getContentSize().width*m_pContainer->getScaleX(),
                   m_tViewSize.height - m_pContainer->getContentSize().height*m_pContainer->getScaleY());
    }
}

bool CCCoverFlowTableView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return CCTableView::ccTouchBegan(pTouch, pEvent);
}

void CCCoverFlowTableView::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCTableView::ccTouchMoved(pTouch, pEvent);
    ((CCCoverFlow*)this->getDelegate())->ccTouchMoved(pTouch, pEvent);
}

void CCCoverFlowTableView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCTableView::ccTouchEnded(pTouch, pEvent);
}