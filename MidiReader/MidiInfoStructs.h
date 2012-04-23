#ifndef MIDIINFOSTRUCTS_H
#define MIDIINFOSTRUCTS_H

#include <cstdio>
#define ENDINFO 0

struct Info{

    unsigned char* info;
    Info* next;
    Info* aux;

    Info(unsigned char* info)
    {
        this->info=info;
        this->aux=this;
    }

    unsigned char* nextInfo()
    {
        if(aux==NULL)
        {
            aux=this;
            return ENDINFO;
        }

        unsigned char* buf=aux->info;

        aux=aux->next;
        return buf;
    }
};

struct Tick{

    Info* info;
    Tick(){info=NULL;}
    void add(unsigned char* inf)
    {
        if(info==NULL)
        {
            info=new Info(inf);
            return;
        }
        Info* n=info;
        while(n->next!=NULL)
            n=n->next;
        n->next=new Info(inf);
    }

};

struct TempoNode{

    unsigned int tick;
    unsigned int tempo;
    TempoNode* next;

    TempoNode(int tick,int tempo)
    {
        this->tick=tick;
        this->tempo=tempo;
    }

};

struct TempoList{

    TempoNode* t;
    void add(TempoNode* tinf)
    {
        if(t==NULL)
        {
            t=tinf;
            return;
        }

        TempoNode* n=t;
        while(n->next!=NULL)
            n=n->next;
        n->next=tinf;

    }

};

#endif
