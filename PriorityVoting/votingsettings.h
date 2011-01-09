#ifndef VOTINGSETTINGS_H
#define VOTINGSETTINGS_H

#include "voting.h"
#include <QString>
#include <QList>
#include <QStringList>

/* Opening settings.txt many times is not good. So let's use singleton to do this.
   But here we don't use public Instance() method. Because it is internal to our getActive and
   getReference
*/
class VotingSettings
{
private:
    static VotingSettings * _instance;
    static VotingSettings & Instance();
    Voting active;
    Voting referene;
protected:
    VotingSettings();
public:
    static Voting &getActiveVoting();
    static Voting &getReferenceVoting();
};

#endif // VOTINGSETTINGS_H
