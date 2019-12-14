#ifndef AGE_H
#define AGE_H

#include "../destinLib/carac.h"

class Age : public Carac
{
public:
    Age(int ageMois);

    virtual bool AfficherValeur();
};

#endif // AGE_H
