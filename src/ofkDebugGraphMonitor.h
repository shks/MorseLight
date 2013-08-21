//
//  ofkDebugGraphMonitor.h
//  ofkiOSsample
//
//  Created by Shunichi Kasahara on 2013/08/08.
//
//

#ifndef __ofkiOSsample__ofkDebugGraphMonitor__
#define __ofkiOSsample__ofkDebugGraphMonitor__

#include "ofMain.h"

class ofkDebugGraphMonitor
{
public:
    
    void render(int x, int y, int height, int width)
    {
        ofTranslate(x, y);
        for(int i = 0 ; i < GRAPHLENGTH ; i++)
        {
            ofSetColor(54,200,120);
            ofRect(
                   (float)i /  (float)GRAPHLENGTH * (float)width,
                   height,
                   (float)width / (float)GRAPHLENGTH,
                   mGraph[i] * -height);
        }
    }
    
    void update(float val){

        mGraph[0] = val;
        
        for(int i = GRAPHLENGTH - 1 ; i > 0 ; i--)
        {
            mGraph[i] = mGraph[i-1];
        }
    };


private:
    const static int GRAPHLENGTH = 512;
    float mGraph[GRAPHLENGTH];

};

#endif /* defined(__ofkiOSsample__ofkDebugGraphMonitor__) */
