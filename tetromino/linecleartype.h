#ifndef LINECLEARTYPE_H
#define LINECLEARTYPE_H


class LineClearType
{
private:
    int tetroType;
    int clearNum;
    bool spin;
public:
    LineClearType(int t,int num,bool spin);

    bool operator<(const LineClearType& cl){
        return  this->clearNum < cl.clearNum;
    }
};

#endif // LINECLEARTYPE_H
