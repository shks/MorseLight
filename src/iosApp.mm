//
//  iosApp.cpp
//  Metronms
//
//  Created by Shunichi Kasahara on 2013/06/30.
//
//

#include "iosApp.h"

#define Default_MORSE_INTERVAL (100)

void iosApp::setup()
{
    ofkiosApp::setup();
    
    //// ------------------- ofxiPhoneKeyboard  -------------------////
    
    keyboard = new ofxiPhoneKeyboard(0,ofGetHeight() * 0.1,320,60);
	keyboard->setVisible(true);
	keyboard->setBgColor(255, 255, 255, 50);
	keyboard->setFontColor(250,24,129, 255);
	keyboard->setFontSize(45);
    
    //// ------------------- ofxiPhoneTorch  -------------------////
    flashlight.toggle(false);  //set torch to off

    //// ------------------- Common GUI setup  -------------------////
    changeWidgetState(WidgetOpened);
    
    label = guiCanvas->addLabel("Signal", "MORSE SIGNAL",OFX_UI_FONT_SMALL);

    guiCanvas->addWidgetDown(new ofxUILabelButton("Flash", OFX_UI_FONT_LARGE));
    guiCanvas->addSpacer(300, 1);
    
    decodedlabel = guiCanvas->addLabel("decoded", "String",OFX_UI_FONT_SMALL);
    
    guiCanvas->addWidgetDown(new ofxUILabelButton("Clear Decoded Str", OFX_UI_FONT_LARGE));
    guiCanvas->addFPS();
    guiCanvas->addSlider("MorseInterval", 50.0, 500.0, &mMorseInterval , ofGetWidth() * 0.6, 100.0f);
    
    ofAddListener(guiCanvas->newGUIEvent, this, &iosApp::guiEvent);

    //// ------------------- prepare signal  -------------------////
    morseSignal.push_back(0);
    morseSignal.push_back(0);
    morseSignal.push_back(0);

    //// ------------------- for signal control  -------------------////
    signalCounter = 0;
    lastCheckedTime = 0;
    mMorseInterval = Default_MORSE_INTERVAL;

    //// ------------------- Image Processing  -------------------////
    grabber.initGrabber(480, 360);
    VIDEO_WIDTH = grabber.getWidth();
    VIDEO_HEIGHT = grabber.getHeight();
    
    ROIWindowSizeRate = 0.2;
    ROIimageSize = (int)(VIDEO_WIDTH * ROIWindowSizeRate);
    
    mPixel.allocate(VIDEO_WIDTH, VIDEO_HEIGHT, OF_PIXELS_RGB);
    mPixelCropped.allocate(ROIimageSize, ROIimageSize, OF_PIXELS_RGB);
    
    TY = VIDEO_HEIGHT / 2 - ROIimageSize/2;
    BY = VIDEO_HEIGHT / 2 + ROIimageSize/2;
    RX = VIDEO_WIDTH / 2 - ROIimageSize/2;
    LX = VIDEO_WIDTH / 2 + ROIimageSize/2;
    
    grayImage.allocate(ROIimageSize, ROIimageSize);
    cvImage.allocate(ROIimageSize, ROIimageSize);
    
    isFound = false;
    
    //// ------------------- Camera Settings-------------------////
    // Select device
    AVCaptureDevice *videoCaptureDevice = nil;
	NSArray *cameraArray = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
	for (AVCaptureDevice *camera in cameraArray) {
		if (camera.position == AVCaptureDevicePositionBack) {
			videoCaptureDevice = camera;
		}
	}
    
    NSError *error = nil;
    if ([videoCaptureDevice lockForConfiguration:&error]) {
        
        // Exposure
        if ([videoCaptureDevice isExposureModeSupported:AVCaptureExposureModeContinuousAutoExposure]) {
            videoCaptureDevice.exposureMode = AVCaptureExposureModeLocked;
        }
        
        // White balance
        if ([videoCaptureDevice isWhiteBalanceModeSupported:AVCaptureWhiteBalanceModeContinuousAutoWhiteBalance]) {
            videoCaptureDevice.whiteBalanceMode = AVCaptureWhiteBalanceModeLocked;
		}
        
        //Locking config
        [videoCaptureDevice unlockForConfiguration];
    }else {
        NSLog(@"ERROR:%@", error);
    }
 
    // start the decode thread
    dec.start();
}


//--------------------------------------------------------------
void iosApp::update(){
    ofkiosApp::update();
    
    grabber.update();
    bool bNewFrame = grabber.isFrameNew();
	if (bNewFrame){
        if( grabber.getPixels() != NULL ){
            
            CaptureInterval = ofGetElapsedTimeMillis() - exCaptureTime;
            exCaptureTime = ofGetElapsedTimeMillis();
            
            if(mPixel.isAllocated())
            {
                mPixel.setFromPixels(grabber.getPixels(),VIDEO_WIDTH, VIDEO_HEIGHT, OF_IMAGE_COLOR);
                
                mPixel.cropTo(mPixelCropped, RX, TY, ROIimageSize, ROIimageSize);
                cvImage.setFromPixels(mPixelCropped);
                grayImage = cvImage;
                grayImage.threshold(230);       //TODO 
                
                contourFinder.findContours(grayImage, (ROIimageSize*ROIimageSize) * 0.25, (ROIimageSize*ROIimageSize), 1, false);
                if (contourFinder.nBlobs)
                {
                    isFound = true;
                }else
                {
                    isFound = false;
                }
            }
        }
    }
    
    dec.setOn(isFound);
    decodedStr += dec.popResult();
    decodedlabel->setLabel(decodedStr);

    if(text != keyboard->getText())
    {
        if("" != keyboard->getText())
        {
            text = keyboard->getText();
            
        }else{
            text = " ";            
        }
    }
    
    ///// **************** Playing Morse Signal ***********************///
    //// ------------------- Morse Signal to Torch-------------------////
    if((int)ofGetElapsedTimeMillis() - lastCheckedTime > mMorseInterval)
    {
        signalCounter = (signalCounter + 1) % morseSignal.size();        
        lastCheckedTime = ofGetElapsedTimeMillis();
    }
        
    if(1 == morseSignal.at(signalCounter))
    {
        flashlight.toggle(true);  //set torch to off
    }else
    {
        flashlight.toggle(false);  //set torch to off
    }
    
    //// ------------------- Monitoring -------------------////
    
    debugMonitor.update( (isFound)? 1.0 : 0.0 );
}

//--------------------------------------------------------------
void iosApp::draw(){

    glPushMatrix();
    glTranslatef(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f, 0.0);
    
    float videoW = ofGetHeight();
    float videoH = videoW * ((float)VIDEO_WIDTH / (float)VIDEO_HEIGHT);
    
    grabber.draw(-videoH / 2, -videoW/2, videoH, videoW);
    glPopMatrix();
    
    cvImage.draw(0, 50);
    grayImage.draw(0, 50 + cvImage.getHeight());
    
    ofPushStyle();
    ofNoFill();
    ofSetColor(255, 23, 120, 200);
    glPushMatrix();
    glTranslatef(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f, 0.0);
    
    float size = ofGetWidth() * ROIWindowSizeRate;
    ofRect(-size/2, -size/2, size, size);
    size += 4.0f;
    ofRect(-size/2, -size/2, size, size);
    
    if(isFound)
    {
        ofDrawBitmapString("Found!!", size, size);
        
        ofSetColor(20, 230, 255, 200);
        
        size += 4.0f;
        ofRect(-size/2, -size/2, size, size);
        size += 4.0f;
        ofRect(-size/2, -size/2, size, size);
    }
    
    renderIndicator();
    
    glPopMatrix();
    ofPopStyle();
    
    //CaptureInterval
    ofSetColor(255, 255, 255, 200);
    ofDrawBitmapString("CaptureInterval :" + ofToString(CaptureInterval) + "ms, " + ofToString(1000 / CaptureInterval) + "FPS", 0, ofGetHeight() - 50);

    ofDrawBitmapString("decodedStr :" + decodedStr , 0, ofGetHeight() - 100);

    debugMonitor.render(0, 50, 50, ofGetWidth());
    ofkiosApp::draw();
}

void iosApp::exit()
{
    ofkiosApp::exit();
    dec.stop();
}

void iosApp::renderIndicator()
{
    static float reaction = 0.0;
    
    float size = ofGetWidth() * ROIWindowSizeRate;
    ofSetCircleResolution(60);
    ofPushStyle();
    ofSetLineWidth(4.0);
    ofSetColor(255, 255, 255, 200);
    ofCircle(ofPoint(0), size);
    
    reaction += (isFound)? (100.0 - reaction) * 0.2 : -reaction;
    
    cout << reaction << endl;
    ofSetColor(255, 255, 255, (100 - reaction) * 2);
    
    ofCircle(ofPoint(0), size + reaction);
    
    ofPopStyle();
}

void iosApp::touchDown(ofTouchEventArgs & touch)
{
    ofkiosApp::touchDown(touch);
    
    if (touch.id == 1){
		
		if(!keyboard->isKeyboardShowing()){
			keyboard->openKeyboard();
			keyboard->setVisible(true);
		} else{
			keyboard->setVisible(false);
		}
	}    
}

void iosApp::touchUp(ofTouchEventArgs & touch)
{
    ofkiosApp::touchUp(touch);
}

void iosApp::guiEvent(ofxUIEventArgs &e)
{
    if(e.widget->getName() == "Flash")
    {
		ofxUIButton *button = (ofxUIButton *) e.widget;
        if(button->getValue())
        {
            assignMessage(text);
        }
    }else if(e.widget->getName() == "Clear Decoded Str")
    {
		ofxUIButton *button = (ofxUIButton *) e.widget;
        if(button->getValue())
        {
            decodedStr = "";
        }
    }
}

void iosApp::assignMessage(string str)
{
    
    ///// **************** Making Morse Signal ***********************///
    morseSignal = MorseCodec::encode(str);
    
    string signalStr;
    for(int i = 0 ; i < morseSignal.size() ; i++){
        signalStr += ofToString(morseSignal.at(i));
    }
    
    label->setLabel("MORSE : " + signalStr);
}

void iosApp::startSignal()
{
    signalCounter = 0;
    
    
    
}

