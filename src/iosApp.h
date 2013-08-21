//
//  iosApp.h
//  application code
//  Created by Shunichi Kasahara on 2013/06/30.
//
//

#ifndef __Metronms__iosApp__
#define __Metronms__iosApp__

#include "ofkiosApp.h"
#include "ofxMorse.h"
#include "ofxiPhoneTorch.h"

//ON IPHONE NOTE INCLUDE THIS BEFORE ANYTHING ELSE
#include "ofxOpenCv.h"

// 
#include "MorseCodec.h"
#include "ofkDebugGraphMonitor.h"

//import Thread Decoding
#include "decodeThread.h"

class iosApp : public ofkiosApp
{
    virtual void setup();
    virtual void update();
    virtual void draw();
    virtual void exit();
	
    virtual void touchDown(ofTouchEventArgs & touch);
    //virtual void touchMoved(ofTouchEventArgs & touch);
    virtual void touchUp(ofTouchEventArgs & touch);
    //virtual void touchDoubleTap(ofTouchEventArgs & touch);
    //virtual void touchCancelled(ofTouchEventArgs & touch);
    
    //virtual void lostFocus();
    //virtual void gotFocus();
    //virtual void gotMemoryWarning();
    //virtual void deviceOrientationChanged(int newOrientation);
    //virtual void touchTwoFinger ( ofkMultiTouchEventArgs &touch );
    
    
public:
    
    void renderIndicator();
    virtual void guiEvent(ofxUIEventArgs &e);
    
    ofxUILabel *label;
    ofxUILabel *decodedlabel;
    
    ofxiPhoneKeyboard * keyboard;
    ofxiPhoneTorch flashlight;
    string text;
    
    void assignMessage(string str);
    void startSignal();
    
    vector<int> morseSignal;
    int signalCounter;
    int lastCheckedTime;
    
    ofVideoGrabber grabber;
    int VIDEO_WIDTH = 480;
    int VIDEO_HEIGHT = 360;
    
    //------------
    ofPixels mPixel;
    ofPixels mPixelCropped;
    
    ofxCvColorImage cvImage;
    ofxCvGrayscaleImage grayImage;
    ofxCvContourFinder contourFinder;
    
    bool isFound;
    
    float ROIWindowSizeRate;
    float ROIimageSize;
    
    int TY, BY, RX, LX;
    
    int exCaptureTime;
    int CaptureInterval;
    
    string decodedChar;
    string decodedStr;
    
    
private:
    float mMorseInterval;
 //   MorseCodec::Decoder dec;
    decodeThread dec;
    ofkDebugGraphMonitor debugMonitor;
    
    
};


#endif /* defined(__Metronms__iosApp__) */
