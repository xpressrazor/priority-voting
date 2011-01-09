#ifndef PRIORITYFIND_H
#define PRIORITYFIND_H
#include <QList>
#include <QString>
#include "voter.h"
#include "candidate.h"
#include "result.h"
#include "voting.h"
#include "result.h"
#include "vote.h"

class PriorityFind
{
private:    
    static QList<Vote> findInternalVotes(Voting voting, int priority, Candidate candidate);
public:
    PriorityFind();
    static QList<Voter> &findVoters();
    static QList<Candidate> &findCandidates();
    static QList<Result> &findResults();
    static QList<Vote> &findAllVotes();
    static QList<Voting> &findVotings();
    static Result &findResult(Voting &voting);
    static Voting &findVoting(int id);
    static Vote &findVote(int votingId, int voterId);
    static Candidate &findCandidate(int id);
    static Candidate &findCandidate(QString sname);
    static Candidate &findCandidate(Vote &vote, int priority);
    static Voter &findVoter(int id);
    static Vote &findVote(Voting &voting, Voter &voter);
    static QList<Vote> &findVotes(Voting &voting, int priority, Candidate &candidate);
    static QList<Vote> &findVotes(Voting &voting);
    static QList<Vote> &findVotes(int priority);
    static QList<Vote> &findVotes(Candidate &candidate);
    static QList<Vote> &findVotes(Voting &voting, int priority);
    static QList<Vote> &getTrimmedVotes(QList<Vote> &votes, int limit);
    static int getCandidateLimit(Voting *voting, Candidate *candidate);
    static int getCandidatePriority(Voting *voting, Candidate *candidate);
    static int getCandidatePriority(Vote *vote, Candidate *candidate);
    static int getCandidatesCount(Voting &voting);
};

#endif // PRIORITYFIND_H
