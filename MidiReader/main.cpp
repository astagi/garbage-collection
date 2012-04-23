//
// Programmer:    Andrea Stagi <stagi.andrea@gmail.com>
// Creation Date: Thu Mar 04 23:05:42 PST 2010
// Last Modified: Thu Mar 04 15:10:29 PST 2010
// Syntax:        C++
//

#include <unistd.h>
#include <stdio.h>

#include "MidiInfo.h"

#ifndef TESTBOX_H
#define TESTBOX_H

class TestBox : public InfoReceiver{

    public:
        void getInfo(int tick,unsigned char* inf)
            {printf("\nat tick %d info %c",tick,inf[0]);}

};

#endif

int main(int argc, char** argv) {

    TestBox t;
    MidiInfo minf("midifiles/Cisei.kar"); //open file (open initialize also ticklength of file, resolution.....)

    if(minf.isValid())
        minf.readInfo(&t); //if you have a valid midi, read all info filling t
    else
        return ERR_NOTMIDI;

    minf.readInfo(); //now try to call readInfo without parameters. What happens? Nothing special but..

    Tick* inf = minf.getInfo();//you can use defaul struct Tick

    Info *n = inf[22320].info;

    unsigned char* buf;

    while((n != NULL) && (buf = n->nextInfo()))
        printf("\nInfo :%s", buf);

    printf("\n\nNumber of ticks: %d Resolution: %dtpb Length: %dsec.\n", minf.getTickLength(), minf.getResolution(), minf.getSecondLenght());

    return 0;
}


