#ifndef RESULT_H
#define RESULT_H

#include <QMap>
#include <QString>
#include "vote.h"
#include "candidate.h"
#include "voting.h"


class Result
{
private:
    Voting *voting;
    QMap<Vote *, Candidate *> *voteCandidates;
public:
    Result();
    QMap<Vote *, Candidate *> *getVoteCandidates();
    void addVoteCandidate(Vote vote, Candidate candidate);
    Voting &getVoting();
    void setVoting(Voting vvoting);

};

#endif // RESULT_H
