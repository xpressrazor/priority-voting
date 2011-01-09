#include "voter.h"

Voter::Voter()
{
    name = new QString();
}

Voter::Voter(int iid, QString *sname)
{
    id = iid;
    name = sname;
}

int Voter::getId()
{
    return id;
}

QString &Voter::getName()
{
    return *name;
}

void Voter::setId(int iid)
{
    id = iid;
}

void Voter::setName(QString *sname)
{
    name = sname;
}


QString Voter::toString()
{
    return "Id: " + QString::number(id) + ", Name:" + *name;
}
