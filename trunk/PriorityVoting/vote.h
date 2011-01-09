#ifndef VOTE_H
#define VOTE_H

#include "voter.h"
#include "candidate.h"
#include "voting.h"
#include "QMap"

/*
 Holds vote of individual voter. In a voting session it is associated with a voting.
 Voters choose candidates based on priority on each vote.
*/

class Vote
{
private:
    Voter *voter;
    Voting *voting;
    QMap<int, int> *candidatesPriority;
public:
    Vote();
    void addCandidatePriority(Candidate &candidate, int priority);
    void setVoting(Voting &vvoting);
    void setVoter(Voter &voter);
    Voter &getVoter();
    Voting &getVoting();
    QMap<int, int> &getCandidatesPriority();

};

#endif // VOTE_H
