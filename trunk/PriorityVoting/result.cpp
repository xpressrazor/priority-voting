#include "result.h"

Result::Result()
{
   voting = new Voting();
   voteCandidates = new QMap<Vote *, Candidate *>();
}

void Result::addVoteCandidate(Vote vote, Candidate candidate)
{
  voteCandidates->insert(&vote, &candidate);
}


QMap<Vote *, Candidate *> *Result::getVoteCandidates()
{
  return this->voteCandidates;
}
       
Voting &Result::getVoting()
{
  return *voting;
}

void Result::setVoting(Voting vvoting)
{
    voting = &vvoting;
}

