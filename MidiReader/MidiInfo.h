#ifndef MIDIINFO_H
#define MIDIINFO_H

#include "MidiInfoStructs.h"
#include "InfoReceiver.h"

#define ERR_NOTMIDI 1

using namespace std;

class MidiInfo{

    private:

        Tick *il;
        FILE *mf;
        InfoReceiver* ir;
        TempoList* tl;

    public:

        MidiInfo(const char* fileName);
        ~MidiInfo();
        Tick* getInfo();
        int getTickLength();
        unsigned int getSecondLenght();
        int getResolution();
        void readInfo();
        void readInfo(InfoReceiver* ir);
        bool isValid();

        void fillStruct(InfoReceiver* str);

        class Utilities
        {
            public:

                static unsigned int convertTempo(unsigned char *b)
                {
                    return (unsigned int)60000000.0 / ((b[0] << 16) | (b[1] << 8) | (b[2]));
                }

                static unsigned int convertResolution(unsigned char *b)
                {
                    unsigned int res = 0;
                    res = b[0];
                    res = res << 8;
                    res = res + b[1];
                    return res;
                }
        };

    private:

        bool valid;
        int mode;
        int maxTick;
        int curTick;
        int cur;
        unsigned int seclength;
        int dim;
        int resolution;
        unsigned char *by;
        const char* fileName;

        int getTick();
        int getTime();
        void get2ByteInfo();
        void get3ByteInfo();
        void readFile(int mode);
        void reset();
};

#endif
