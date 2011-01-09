#ifndef VOTING_H
#define VOTING_H

#include <QString>
#include <QMap>
#include "candidate.h"


class Voting
{
public:
    Voting();

    void setTitle(QString &stitle);
    void setId(int iid);

    int getId();
    QString &getTitle();

    void addCandiateLimit(int candidateId, int ilimit);
    QMap<int, int> &getCandidatesLimit();
    QString toString();

private:
    int id;
    QString *title;
    QMap<int, int > *candidateLimits;
};

#endif // VOTING_H
