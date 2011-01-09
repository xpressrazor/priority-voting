#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <QString>

class Candidate
{
private:
    QString name;
    int id;
public:
    Candidate();
    Candidate(QString sname, int iid);
    QString getName();
    int getId();
    void setName(QString sname);
    void setId(int iid);
    QString toString();
};

#endif // CANDIDATE_H
