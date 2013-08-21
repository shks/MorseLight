#ifndef _decodeThread_h
#define _decodeThread_h

#include "ofMain.h"
#include "MorseCodec.h"

/**
 * Decode thread class
 *
 * This class has an instance of the Decoder, and decode input signal periodically.
 *
 * @code
 * // Usage
 * // iosApp.h
 * #include "decodeThread.h"
 *
 * class iosApp : ofkiosApp{
 *
 * public:
 *
 *    // override
 *    vritual void exit();
 *
 * private:
 *    // has a decodeThread
 *    decodeThread dec;
 * };
 *
 * // iosApp.mm
 * void iosApp::setup()
 * {
 *     ofkiosApp::setup();
 *
 *     // start the decode thread
 *     dec.start();
 * }
 *
 * void iosApp::exit()
 * {
 *     ofkiosApp::exit();
 *
 *     // stop the decode thread
 *     dec.stop();
 * }
 *
 * void iosApp::update() {
 *
 *     // process
 *     dec.process(isFound);
 *     string result = dec.popResult();
 *
 * }
 */

class decodeThread : public ofThread
{
public:
    decodeThread(){
        result.reserve(MAX_LENGTH);
    }

    void setOn(bool isOn){
        this->isOn = isOn;
    }
    
    string popResult(){
        lock();
        string r = result;
        result = "";
        unlock();
        return r;
    }
    
    void start(){
        startThread(true, false);
    }

    void stop(){
        stopThread();
    }

    void threadedFunction(){
        while (isThreadRunning() != 0){
            string s = decoder.process(isOn);
            lock();
            string snew = result + s;
            if (snew.size() <= MAX_LENGTH)
                result = snew;
            unlock();
            sleep(INTERVAL_MSEC);
            cout << "threadedFunction" << endl;
        }
    }

private:
    enum {
        INTERVAL_MSEC = 10,
        MAX_LENGTH = 2048
    };
    MorseCodec::Decoder decoder;
    string result;
    bool isOn;
};

#endif
