#ifndef PACEMAN_H
#define PACEMAN_H


class Paceman
{
public:
    Paceman();
     Paceman(int i,int j);
    int x;
    int y;
    int face;
    int isdead;
    bool operator ==(const Paceman P){

        return P.x==x&&P.y==y;
    }
};

#endif // PACEMAN_H
