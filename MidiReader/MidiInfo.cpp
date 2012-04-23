#include "MidiInfo.h"

#include <cmath>
#include <cstdio>

MidiInfo::MidiInfo(const char* fileName)
{

    maxTick = 0;
    valid = false;
    curTick = 0;
    cur = 0;
    dim = 0;
    seclength = 0;

    tl = new TempoList();
    this->fileName = fileName;

    readFile(1);
}

MidiInfo::~MidiInfo()
{
    delete [] il;
}

void MidiInfo::readFile(int mode)
{

    cur = 0;

    if((mf = fopen(fileName, "rb")) == NULL) //Try open file
        return;

    fseek(mf, 0L, SEEK_END);

    dim = ftell(mf); //Get file dim.

    //Start copy file in memory

    by = new unsigned char[dim]; 

    rewind(mf);

    fread(by, sizeof(unsigned char), dim, mf);

    unsigned char cs;
    unsigned char* info;
    unsigned char dims,type;

    //Check if it's a midi file

    if(by[(cur)] == 0x4d && by[(cur + 1)] == 0x54 && 
        by[(cur) + 2] == 0x68 && by[(cur) + 3] == 0x64)
        valid=true;
    else
        return;

    while(by[(++cur)] != 0x4d){}

    if(mode == 1)
    {
        unsigned char* bres = new unsigned char[2];
        bres[0] = by[cur-2];
        bres[1] = by[cur-1];
        resolution=Utilities::convertResolution(bres);
    }

    this->mode = mode;

    if(mode == 0)
        il = new Tick[maxTick + 1];

    //Start fetching file

    while(cur < dim){


        if(by[(cur)] == 0x4d && by[(cur + 1)] == 0x54 
            && by[(cur) + 2] == 0x72 && by[(cur) + 3] == 0x6b)
        {
                curTick=0;
                cur+=8;
        }

        getTick();

        cs=by[cur] & 0xf0;

        switch(cs){

                case 0xf0:

                  if(by[cur]==0xff)
                  {
                        type=by[++cur];
                        dims=by[++cur];

                        if(mode!=1){
                            info=new unsigned char[dims+3];
                            info[0]=0xff;
                            info[1]=type;
                            info[2]=dims;
                        }

                        for(int i=0;i<dims;i++)
                        {
                            if(mode!=1)
                                info[i+3]=by[++cur];
                            else
                                ++cur;
                        }

                        if(mode==1 && type==0x51)
                            tl->add(new TempoNode(curTick,Utilities::convertTempo(by+(cur-dims+1))));

                        cur++;

                        if(mode==0)il[curTick].add(info);
                        if(mode==2)ir->getInfo(curTick,info);
                  }

                  else if(by[cur]==0xf0)
                  {
                        dims=by[++cur];

                        if(mode!=1){
                            info=new unsigned char[dims+2];
                            info[0]=0xf0;
                            info[1]=dims;
                        }

                        for(int i=0;i<dims;i++)
                        {
                            if(mode!=1)
                                info[i+2]=by[++cur];
                            else
                                ++cur;
                        }

                        cur++;

                        if(mode==0)il[curTick].add(info);
                        if(mode==2)ir->getInfo(curTick,info);
                  }

                  break;

                case 0x80:
                  get3ByteInfo();
                  break;

                case 0x90:
                  get3ByteInfo();
                  break;

                case 0xB0:
                  get3ByteInfo();
                  break;

                case 0xC0:
                  get2ByteInfo();
                  break;

                case 0xE0:
                  get3ByteInfo();
                  break;

                case 0xA0:
                  get3ByteInfo();
                  break;

                case 0xD0:
                  get3ByteInfo();
                  break;

        }

        if(mode==1 && curTick>maxTick)
            maxTick=curTick;

    }

    if(mode==1){
        unsigned int ticksecond,nextick;
        TempoNode* t=tl->t;

        do{

            if((t->next)==NULL)
                nextick=maxTick;
            else
                nextick=(t->next)->tick;

            nextick=nextick-(t->tick);
            ticksecond=(unsigned int)(((t->tempo)*resolution)/60);
            seclength+=(unsigned int)(nextick/ticksecond);
            t=(t->next);

        }while(t!=NULL);

        fclose(mf);
    }


    if(mode==1)
        delete []by;

}

Tick* MidiInfo::getInfo()
{
    return il;
}

void MidiInfo::readInfo()
{
    readFile(0);
}

void MidiInfo::readInfo(InfoReceiver* ir)
{
    if(ir!=NULL)
        this->ir=ir;

    readFile(2);
}

int MidiInfo::getTickLength()
{
    return maxTick;
}

int MidiInfo::getResolution()
{
    return resolution;
}

bool MidiInfo::isValid()
{
    return valid;
}

unsigned int MidiInfo::getSecondLenght()
{
    return seclength;
}

int MidiInfo::getTick()
{

    int tick=0,i=0,steps=0;

    while(by[cur+i]>=0x80){i++;}

    while(by[cur]>=0x80)
    {
        steps++;

        tick+=pow(128,i)*(by[cur]-0x80);
        --i;
        ++(cur);

    }

    tick+=by[cur];

    ++steps;

    curTick+=tick;

    ++(cur);

    return steps;

}

void MidiInfo::get3ByteInfo()
{

    unsigned char actmsg;
    unsigned char* info;

    if(mode!=1){
        info=new unsigned char[3];
        actmsg=info[0]=by[cur++];
        info[1]=by[cur++];
        info[2]=by[cur++];
        if(mode==0)il[curTick].add(info);
        if(mode==2)ir->getInfo(curTick,info);
    }

    else
        cur+=3;

    int steps,exit=0,tickAux;

    while(exit==0){
        tickAux=curTick;
        steps=getTick();

        if(by[cur]<0x80){
            if(mode!=1){
                info=new unsigned char[3];
                info[0]=actmsg;
                info[1]=by[cur++];
                info[2]=by[cur++];
                if(mode==0)il[curTick].add(info);
                if(mode==2)ir->getInfo(curTick,info);
            }
            else
                cur+=2;

        }else{
            curTick=tickAux;
            cur=cur-(steps);
            exit=1;
        }
    }
}

void MidiInfo::get2ByteInfo()
{

    unsigned char actmsg;
    unsigned char* info;

    if(mode!=1){
        info=new unsigned char[2];
        actmsg=info[0]=by[cur++];
        info[1]=by[cur++];
        if(mode==0)il[curTick].add(info);
        if(mode==2)ir->getInfo(curTick,info);
    }
    else
        cur+=2;

    int steps,exit=0,tickAux;;

    while(exit==0){

        tickAux=curTick;
        steps=getTick();

        if(by[cur]<0x80){

            if(mode!=1){
                info=new unsigned char[2];
                info[0]=actmsg;
                info[1]=by[cur++];
                if(mode==0)il[curTick].add(info);
                if(mode==2)ir->getInfo(curTick,info);
            }
            else
                cur++;

        }else{
            curTick=tickAux;
            cur=cur-(steps);
            exit=1;
        }
    }
}

void MidiInfo::reset(){}






