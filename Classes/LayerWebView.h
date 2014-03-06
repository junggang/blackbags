//
//  LayerWebView.h
//  MyApp1
//
//  Created by DAC-TOAN HO on 11-10-10.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __CC_UIWEBVIEW_H__
#define __CC_UIWEBVIEW_H__


//#include "CCCommon.h"
#include "cocos2d.h"
#include "config.h"

class LayerWebView : public cocos2d::CCLayer
{
public:
	virtual bool init();
    
    void webViewDidFinishLoad(std::string newToken);
    void close();
    
	// implement the "static node()" method manually
    CREATE_FUNC(LayerWebView);
};
    

#endif