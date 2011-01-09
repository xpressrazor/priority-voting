#ifndef VOTER_H
#define VOTER_H
#include <QString>

class Voter
{
private:
    int id;
    QString *name;

public:
    Voter();
    Voter(int iid, QString *sname);
    int getId();
    QString &getName();
    void setId(int iid);
    void setName(QString *sname);
    QString toString();
};

#endif // VOTER_H
