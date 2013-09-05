#ifndef _MORSECODE_H
#define _MORSECODE_H

#include <map>
#include <string>
#include <vector>

#include <tr1/cstdint>

class MorseCodec {

public:
    static std::vector<int> encode(const std::string& str);

    class Decoder {
    private:
        int64_t upstrokeTime;
        int64_t downstrokeTime;
        int64_t minimum; 
        int64_t maximum;
        bool hlPrev;
        std::vector<int64_t> queue;
        static const float TOLERANCE;
        static const int64_t MINIMUM_RESOLUTION;
        static const int64_t MAXIMUM_RESOLUTION;
        static const std::vector<int64_t>::size_type QUEUE_SIZE_MAX;
    public:
        Decoder();

        /**
         * Decode morse coded signal
         *
         * Application should call this method continuously.
         *
         * @param isHigh indicates whether the input signal is HIGH or LOW
         * @return a string representation of decoded result, null otherwise.
         */
        std::string process(bool isHigh);
    };

private:
    struct Entry {
        const int* array;
        size_t length;
        Entry() : array(0), length(0) {}
        Entry(const int* a, size_t l) : array(a), length(l) {}
    };

    static const int A[];
    static const int B[];
    static const int C[];
    static const int D[];
    static const int E[];
    static const int F[];
    static const int G[];
    static const int H[];
    static const int I[];
    static const int J[];
    static const int K[];
    static const int L[];
    static const int M[];
    static const int N[];
    static const int O[];
    static const int P[];
    static const int Q[];
    static const int R[];
    static const int S[];
    static const int T[];
    static const int U[];
    static const int V[];
    static const int W[];
    static const int X[];
    static const int Y[];
    static const int Z[];

    static const int _1[];
    static const int _2[];
    static const int _3[];
    static const int _4[];
    static const int _5[];
    static const int _6[];
    static const int _7[];
    static const int _8[];
    static const int _9[];
    static const int _0[];

    static const int PERIOD[];
    static const int COMMA[];
    static const int QUESTION_MARK[];
    static const int APOSTROPHE[];
    static const int EXCLAMATION_MARK[];
    static const int HYPHEN[];
    static const int SLASH[];
    static const int AT_SIGN[];
    static const int PARENTHESIS_OPEN[];
    static const int PARENTHESIS_CLOSE[];
    static const int AMPERSAND[];
    static const int COLON[];
    static const int SEMICOLON[];
    static const int DOUBLE_DASH[];
    static const int PLUS[];
    static const int UNDERSCODE[];
    static const int QUOTATION_MARK[];
    static const int DOLLAR_SIGN[];
    
    static const int SPACE[];

    static std::map<char, Entry> dictionary;

    static void initializeDictionary();

    static char getCharacter(const int* a, size_t len);

    static const int* getPattern(char c, size_t* length);
};

#endif // _MORSECODE_H

