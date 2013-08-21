//
//  ofxMorse.h
//  ofkiOSsample
//
//  Created by Shunichi Kasahara on 7/6/13.
//
//

#ifndef ofkiOSsample_ofxMorse_h
#define ofkiOSsample_ofxMorse_h

#include "ofMain.h"

class ofxMorseSignal
{
public:
    ofxMorseSignal(int s0 = 0, int s1 = 0,int s2 = 0,int s3 = 0,int s4 = 0,int s5 = 0, int s6 = 0)
    {
        signal[0] = s0;
        signal[1] = s1;
        signal[2] = s2;
        signal[3] = s3;
        signal[4] = s4;
        signal[5] = s5;
        signal[6] = s6;
    }
    
    static const int SignalSize = 7;
    int signal[SignalSize];
    
};

static const ofxMorseSignal A(1,3);
static const ofxMorseSignal B(3, 1, 1, 1);
static const ofxMorseSignal C(3, 1, 3, 1);
static const ofxMorseSignal D(3, 1, 1);
static const ofxMorseSignal E(1);
static const ofxMorseSignal F(1, 1, 3, 1);
static const ofxMorseSignal G(3, 3, 1);
static const ofxMorseSignal H(1, 1, 1, 1);
static const ofxMorseSignal I(1, 1);
static const ofxMorseSignal J(1, 3, 3, 3);
static const ofxMorseSignal K(3, 1, 3);
static const ofxMorseSignal L(1, 3, 1, 1);
static const ofxMorseSignal M(3, 3);
static const ofxMorseSignal N(3, 1);
static const ofxMorseSignal O(3, 3, 3);
static const ofxMorseSignal P(1, 3, 3, 1);
static const ofxMorseSignal Q(3, 3, 1, 3);
static const ofxMorseSignal R(1, 3, 1);
static const ofxMorseSignal S(1, 1, 1);
static const ofxMorseSignal T(3);
static const ofxMorseSignal U(1, 1, 3);
static const ofxMorseSignal V(1, 1, 1, 3);
static const ofxMorseSignal W(1, 3, 3);
static const ofxMorseSignal X(3, 1, 1, 3);
static const ofxMorseSignal Y(3, 1, 3, 3);
static const ofxMorseSignal Z(3, 3, 1, 1);

static const ofxMorseSignal _1(1, 3, 3, 3, 3);
static const ofxMorseSignal _2(1, 1, 3, 3, 3);
static const ofxMorseSignal _3(1, 1, 1, 3, 3);
static const ofxMorseSignal _4(1, 1, 1, 1, 3);
static const ofxMorseSignal _5(1, 1, 1, 1, 1);
static const ofxMorseSignal _6(3, 1, 1, 1, 1);
static const ofxMorseSignal _7(3, 3, 1, 1, 1);
static const ofxMorseSignal _8(3, 3, 3, 1, 1);
static const ofxMorseSignal _9(3, 3, 3, 3, 1);
static const ofxMorseSignal _0(3, 3, 3, 3, 3);

static const ofxMorseSignal PERIOD(1, 3, 1, 3, 1, 3);
static const ofxMorseSignal COMMA(3, 3, 1, 1, 3, 3);
static const ofxMorseSignal QUESTION(1, 1, 3, 3, 1, 1);
static const ofxMorseSignal EXCLAMATION(3, 1, 3, 1, 3, 3);
static const ofxMorseSignal HYPHEN(3, 1, 1, 1, 1, 3);
static const ofxMorseSignal SLASH(3, 1, 1, 3, 1);
static const ofxMorseSignal AT(1, 3, 3, 1, 3, 1);
static const ofxMorseSignal OPEN_BLACKET(3, 1, 3, 3, 1);
static const ofxMorseSignal CLOSE_BLACKET(3, 1, 3, 3, 1, 3);

static const ofxMorseSignal SPACE(1, 1, 1, 1, 1, 1);

class ofxMorse {
public:
    
    static ofxMorseSignal getPattern(char c) {
        switch (c) {
            case 'A':
                return A;
            case 'B':
                return B;
            case 'C':
                return C;
            case 'D':
                return D;
            case 'E':
                return E;
            case 'F':
                return F;
            case 'G':
                return G;
            case 'H':
                return H;
            case 'I':
                return I;
            case 'J':
                return J;
            case 'K':
                return K;
            case 'L':
                return L;
            case 'M':
                return M;
            case 'N':
                return N;
            case 'O':
                return O;
            case 'P':
                return P;
            case 'Q':
                return Q;
            case 'R':
                return R;
            case 'S':
                return S;
            case 'T':
                return T;
            case 'U':
                return U;
            case 'V':
                return V;
            case 'W':
                return W;
            case 'X':
                return X;
            case 'Y':
                return Y;
            case 'Z':
                return Z;
                
            case '1':
                return _1;
            case '2':
                return _2;
            case '3':
                return _3;
            case '4':
                return _4;
            case '5':
                return _5;
            case '6':
                return _6;
            case '7':
                return _7;
            case '8':
                return _8;
            case '9':
                return _9;
            case '0':
                return _0;
            case '.':
                return PERIOD;
            case ':':
                return COMMA;
            case '?':
                return QUESTION;
            case '!':
                return EXCLAMATION;
            case '-':
                return HYPHEN;
            case '/':
                return SLASH;
            case '@': 
                return AT;
            case '(': 
                return OPEN_BLACKET;
            case ')': 
                return CLOSE_BLACKET;
            case ' ': 
                return SPACE;
            default:
                return ofxMorseSignal();
        }
    }
    

    //
    static vector<int> encode(string s) {

        string UpperStr = ofToUpper(s);
        vector<int> c;// = new ArrayList();
        
        const char *chStr = UpperStr.c_str();
        for (int i = 0; i < UpperStr.length(); i++) {
            
            char ch = chStr[i];
            //println(ch);
            //int[]
            ofxMorseSignal code = getPattern(ch);
            if (code.signal[0] == 0)
                continue;
            
            //code.signal[j] 
            for (int j = 0; j < ofxMorseSignal::SignalSize; j++)
            {
                int n = code.signal[j];
                if(0 != n){
                    for (int k = 0; k < n; k++) {
                        c.push_back(1);
                    }
                    c.push_back(0);
                }
            }
        c.push_back(0);
        c.push_back(0);
        c.push_back(0);
 
        }
        return c;
    }
    
    /*
    static class Decoder {
        int dotLen;
        boolean hlPrev;
        ArrayList beforePrediction;
        Decoder() {
            dotLen = 0;
            hlPrev = false;
        }
        
        // decoding is highly adaptive, context-dependent and dynamic process.
        void process(boolean hl) {
            // TODO To be implemented.
            if (!hlPrev && hl) {
                // HIGH
            } else if (hlPrev && !hl) {
                // LOW
            }
            hlPrev = hl;
        }
    }*/
    
};



#endif
