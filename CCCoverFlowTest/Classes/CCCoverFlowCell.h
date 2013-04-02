//
//  CCCoverFlowCell.h
//  CCCoverFlowTest
//
//  Created by 陶 然景 on 13-4-1.
//
//

#ifndef __CCCoverFlowTest__CCCoverFlowCell__
#define __CCCoverFlowTest__CCCoverFlowCell__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCCoverFlowCell: public CCTableViewCell {
public:
    CCCoverFlowCell();
    ~CCCoverFlowCell();

    static CCCoverFlowCell *create(int index);
    
    void setAlphaAndScale(GLubyte opacity, float scale);
};

#endif /* defined(__CCCoverFlowTest__CCCoverFlowCell__) */
