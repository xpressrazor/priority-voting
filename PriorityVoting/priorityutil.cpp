#include "priorityutil.h"
#include "priorityconsole.h"
#include "votingsettings.h"
#include "priorityfind.h"
#include "qset.h"

PriorityUtil::PriorityUtil()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}


int PriorityUtil::randInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

// Algorithm
// Favorable (For now we are using only single calculation
//    so we don't refer to any previous votes for simplicity)
// 0. foreach priority/foreach catagory
// if results.size() for this priority == catagory.limit continue
/*
        1. find each element who voted for this priority
        2. find each element who voted for this priority previously
        3. find each element who got this element for this priority previously
        4. find each element matching 1, 2, 3
        5. foreach element of 4
            addElementsToResult {
                if elements.size() > this_catagory.limit :
                    elements = trim(elements)
                AddToResult(elements)
            }
        6. find each element matching 1, 2
        7. foreach element of 6
                addElementsToResult
        8. foreach element of 1
                addElementsToResult

 */
/*
 Simplified version for only one calculation
    1. Find all votes by active voting. Randomize votes to give fair chance
    2. Find limit for each candidates
    3. Initialize a counter to count already assigned candidates count

    4. Foreach priority
        find candidate for this vote at this priority
        if found a candidate, check to see if vote has already been registered for this vote(voter)
            if our limit for this candidate has not exceeded candidateLimit
                register this vote(voter) and his/her candidate
                increment no. of this candidate register by one.
            else
                continue
    5. return container

 */



QMap<int, QString> &PriorityUtil::calculateResult()
{
    Voting *activeVoting = &VotingSettings::getActiveVoting();

    QMap<int, int> *candidatesLimit = &activeVoting->getCandidatesLimit();
    QMap<int, int> candidateCounter;


    // The votes are randomized in findVotes(Voting &)
    // Each one get's a fair change if the count of their priority exceeds the candidatesLimit
    QList<Vote> *allVotesByVoting = &PriorityFind::findVotes(*activeVoting);

    // Let's create a storage
    // voterId, candidateId
    QMap<int, QString> *candidatesVote = new QMap<int, QString>();

    // Size of candidatesLimit is our priority
    for(int i = 0; i < candidatesLimit->size(); i++) {
        for(int j = 0; j < allVotesByVoting->size(); j++) {
            Vote *vote = new Vote();
            *vote = allVotesByVoting->at(j);

            Candidate *candidate = new Candidate();
            *candidate = PriorityFind::findCandidate(*vote, i+1);
            Voter *voter = &vote->getVoter();
            int candidateId = candidate->getId();
            int candidateLimit = candidatesLimit->value(candidateId);
            int candidateCounterCount = candidateCounter[candidateId];

            if((candidate!=NULL)
                && (!candidatesVote->contains(voter->getId()))
                && (candidateCounterCount < candidateLimit) ) {

                // (voterId), (candidateId,priority)
                candidatesVote->insert(voter->getId(), QString::number(candidateId) + ","
                                       + QString::number(i+1));

                candidateCounter[candidateId]++;
            }

            if(candidateCounter[candidateId] == 3)
                continue;
        }
    }

    return *candidatesVote;
}
