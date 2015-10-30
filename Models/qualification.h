#ifndef QUALIFICATION_H
#define QUALIFICATION_H

class Qualification
{
public:
    Qualification();

    //overloaded == operator
    bool operator==(Qualification const);

    int value;
};

#endif // QUALIFICATION_H
