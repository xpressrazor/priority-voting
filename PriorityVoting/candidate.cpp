#include "candidate.h"

Candidate::Candidate()
{
}

Candidate::Candidate(QString sname, int iid)
{
    name = sname;
    id = iid;
}

QString Candidate::getName()
{
    return name;
}

int Candidate::getId()
{
    return id;
}

void Candidate::setName(QString sname)
{
    name = sname;
}

void Candidate::setId(int iid)
{
    id = iid;
}

QString Candidate::toString()
{
    return "Id: " + QString::number(id) + ", Name: " + name;
}
