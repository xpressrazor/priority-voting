#include "voting.h"
#include "priorityfind.h"

Voting::Voting()
{    
    candidateLimits = new QMap<int, int>();
    title = new QString();
}

void Voting::setTitle(QString &stitle)
{
    *title  = stitle;
}

void Voting::setId(int iid)
{
    id = iid;
}

int Voting::getId()
{
    return id;
}

QString &Voting::getTitle()
{
    return *title;
}

void Voting::addCandiateLimit(int candidateId, int ilimit)
{    
    candidateLimits->insert(candidateId, ilimit);
}


QMap<int, int> &Voting::getCandidatesLimit()
{
    // No key here
    return *candidateLimits;
}


QString Voting::toString()
{
    return "Id: " +QString::number(id) + ", Title: " + *title;
}
