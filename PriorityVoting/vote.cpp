#include "vote.h"
#include "priorityconsole.h"

Vote::Vote()
{
    voter = new Voter();
    voting = new Voting();
    candidatesPriority = new QMap<int, int>();
}

void Vote::addCandidatePriority(Candidate &candidate, int priority)
{
    candidatesPriority->insert(candidate.getId(), priority);
}

void Vote::setVoting(Voting &vvoting)
{
    voting = &vvoting;
}

void Vote::setVoter(Voter &vvoter)
{
    voter = &vvoter;
}

Voter &Vote::getVoter()
{
    return *voter;
}

Voting &Vote::getVoting()
{
    return *voting;
}


QMap<int, int> &Vote::getCandidatesPriority()
{
    return *candidatesPriority;
}
