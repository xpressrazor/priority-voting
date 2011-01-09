#include "priorityfind.h"
#include "priorityfile.h"
#include "priorityconsole.h"
#include "priorityutil.h"
#include "candidate.h"
#include <iostream>
#include <algorithm>
#include <QMap>

#include <QStringList>

using namespace std;

PriorityFind::PriorityFind()
{
}

QList<Voter> &PriorityFind::findVoters()
{
    // Read voters.txt, construct Voter list and return
    QList<QString> voters= PriorityFile::readFile("voters.txt");
    QList<Voter> *voterList = new QList<Voter>();
    Voter *voter = new Voter();

    for(int i=0; i<voters.size(); i++) {        
        QStringList list = voters.at(i).split(":");
        voter->setId(list.at(0).toInt());
        QString *name = new QString();
        *name = list.at(1); // 0 contains id 1 contains name
        voter->setName(name);
        voterList->append(*voter);

        // Print
        //PriorityConsole::print(voter.toString());
    }

    return *voterList;
}

QList<Candidate> &PriorityFind::findCandidates()
{
    // Read candidates.txt, construct Candidate list and return
    QList<QString> candidates= PriorityFile::readFile("catagories.txt");
    QList<Candidate> *candidateList = new QList<Candidate>();

    for(int i=0; i<candidates.size(); i++) {
        Candidate candidate;
        QStringList list = candidates.at(i).split(":");

        QString idStr;
        QString candiateName;
        if(list.size()>1) {
            idStr= list.at(0);
            candidate.setId(idStr.toInt());
            candiateName = list.at(1);
            candidate.setName(candiateName);


            candidateList->append(candidate);
        }

        // print
        //PriorityConsole::print(candidate.toString());
    }

    return *candidateList;
}

QList<Result> &PriorityFind::findResults()
{
    // Read results.txt, construct Result list and return
    QList<QString> results = PriorityFile::readFile("results.txt");
    QList<Result> *resultList = new QList<Result>();
    //PriorityConsole::print("I reached here");

    for(int i=0; i< results.size(); i++) {
        Result result;
        //PriorityConsole::print("I reached here");
        QStringList list = results.at(i).split(",");
        QString votingIdStr = list.at(0);
        int votingId = votingIdStr.toInt();

        //PriorityConsole::print("I reached here");
        Voting voting = findVoting(votingId);
        PriorityConsole::print(voting.getTitle() + " not reached");
        result.setVoting(voting);

        QStringList voteCandidateList;
        if(list.size()>1 && i > 0) {
            QString tempList = list.at(i);
            voteCandidateList = tempList.split(":");
            if(voteCandidateList.size()>1) {
                QString voterIdStr = voteCandidateList.at(0);
                int voterId = voterIdStr.toInt();
                Voter voter = findVoter(voterId);

                Vote vote = findVote(voting, voter);

                QString candidateStr = voteCandidateList.at(1);
                int candidateId = candidateStr.toInt();
                Candidate candidate = findCandidate(candidateId);

                result.addVoteCandidate(vote, candidate);
            }
        }

        resultList->append(result);
    }
    return *resultList;
}

QList<Vote> &PriorityFind::findAllVotes()
{
    // Read votes.txt, construct Vote list and return
    QList<QString> votes = PriorityFile::readFile("votes.txt");
    QList<Vote> *voteList = new QList<Vote>();

    //QMap<int, int> *candidatePriority = new QMap<int, int>();

    //PriorityConsole::print("findVotes() reached");

    for(int i=0; i< votes.size(); i++) {

        QStringList list = votes.at(i).split(",");        
        QStringList priorityCandidateList;

        if(list.size()>1) {            
            Voter *voter = new Voter();
            Voting *voting = new Voting();
            Vote *vote = new Vote();

            /* If we don't have different voterId, then our collection of map is in trouble */
            QString voterIdStr = list.at(0);
            int voterId = voterIdStr.toInt();
            *voter = findVoter(voterId);
            vote->setVoter(*voter);

            QString votingIdStr = list.at(1);
            int votingId = votingIdStr.toInt();
            *voting = findVoting(votingId);
            vote->setVoting(*voting);

            for(int j=2; j<list.size(); j++) {
                QString tempList = list.at(j);
                priorityCandidateList = tempList.split(":");

                if(priorityCandidateList.size()>1) {
                    QString priorityIdStr = priorityCandidateList.at(0);
                    int priority = priorityIdStr.toInt();

                    QString candidateStr = priorityCandidateList.at(1);
                    int candidateId = candidateStr.toInt();
                    Candidate *candidate = new Candidate();
                    *candidate = findCandidate(candidateId);

                    vote->addCandidatePriority(*candidate, priority);
                }
            }

            //PriorityConsole::print("Let's print what the vote is");
            //PriorityConsole::print("Voter: " +vote->getVoter().getName());

            voteList->append(*vote);
        }
        // Vote approaching here
    }       

    return *voteList;
}

QList<Voting> &PriorityFind::findVotings()
{
    // Read votings.txt, construct Voting list and return
    QList<QString> votings = PriorityFile::readFile("votings.txt");
    QList<Voting> *votingList = new QList<Voting>();

    for(int i=0; i<votings.size(); i++) {
        Voting voting;
        QStringList candidateLimitList;

        QStringList list = votings.at(i).split(",");

        if(list.size()>2) {
            QString votingIdStr = list.at(0);
            //list.removeAt(0);
            int votingId = votingIdStr.toInt();
            voting.setId(votingId);

            QString votingTitle = list.at(1);
            //list.removeAt(1);
            voting.setTitle(votingTitle);

            for(int j=2; j<list.size(); j++ ) {
                QString tempList = list.at(j);
                candidateLimitList = tempList.split(":");

                if(candidateLimitList.size() > 1) {
                    QString candidateStr = candidateLimitList.at(0);
                    int candidateId = candidateStr.toInt();

                    /* Pass */
                    QString limitStr = candidateLimitList.at(1);
                    int limit = limitStr.toInt();

                    voting.addCandiateLimit(candidateId, limit);
                }
            }
        }
        /* voting is fine but votingList may have bug */
        /* Voting list has bug */
        //PriorityConsole::print("I am the buggy");
        votingList->append(voting);
    }


    return *votingList;
}


Result &PriorityFind::findResult(Voting &voting)
{
    QList<Result> results = findResults();
    Result *result = new Result();
    for(int i=0; i<results.size(); i++) {
        Result tempResult = results.at(i);

        /* Should have compared objects, but let it be */
        if(tempResult.getVoting().getId() == voting.getId())
            *result = results.at(i);
    }

    return *result;
}

/* See findCandidate(int id) comment for why generic names were choosen */
Voter &PriorityFind::findVoter(int id)
{
    QList<Voter> *lists = new QList<Voter>();
    *lists= findVoters();
    Voter *voter = new Voter();

    for(int i=0; i<lists->size(); i++) {                
        *voter = lists->at(i);
        if(voter->getId() == id) {
            break;
        }
    }
    return *voter;
}

Voting &PriorityFind::findVoting(int id)
{
    QList<Voting> lists = findVotings();
    Voting *item = new Voting();

    for(int i=0; i<lists.size(); i++) {
        Voting tempItem = lists.at(i);

        if(tempItem.getId() == id)
            *item = lists.at(i);
    }
    //PriorityConsole::print("findVoting(int id) is also fine");
    return *item;
}

Vote &PriorityFind::findVote(int votingId, int voterId)
{
    QList<Vote> lists = findAllVotes();
    Vote *item = new Vote();

    for(int i=0; i<lists.size(); i++) {
        Vote tempItem = lists.at(i);

        if((tempItem.getVoting().getId() == votingId) &&
           (tempItem.getVoter().getId() == voterId)) {
            *item = lists.at(i);
        }
    }
    return *item;
}

Candidate &PriorityFind::findCandidate(int id)
{
    /* To make easy for copy paste generic names were choosen */
    /* Specificially we would name as follows
       lists = candidateLists;
       item candidate;
       tempItem tempCandidate
    */
    QList<Candidate> lists = findCandidates();
    Candidate *item = new Candidate();

    for(int i=0; i<lists.size(); i++) {
        Candidate tempItem = lists.at(i);

        if(tempItem.getId() == id) {
            *item = lists.at(i);
            break;
        }
    }
    return *item;
}

Candidate &PriorityFind::findCandidate(QString sname)
{
    /* To make easy for copy paste generic names were choosen */
    /* Specificially we would name as follows
       lists = candidateLists;
       item candidate;
       tempItem tempCandidate
    */
    QList<Candidate> lists = findCandidates();
    Candidate *item = new Candidate();

    for(int i=0; i<lists.size(); i++) {
        Candidate tempItem = lists.at(i);

        if(tempItem.getName().compare(sname)==0)
            *item = lists.at(i);
    }
    return *item;
}

Candidate &PriorityFind::findCandidate(Vote &vote, int priority)
{
    QMapIterator<int, int>itr(vote.getCandidatesPriority());
    Candidate *candidate = new Candidate();

    while(itr.hasNext()) {
        itr.next();

        int ppriority = itr.value();
        if(ppriority == priority) {
            int candidateId = itr.key();
            *candidate = findCandidate(candidateId);
            if(candidate!=NULL)
                return *candidate;
        }
    }

    return *candidate;
}


Vote &PriorityFind::findVote(Voting &voting, Voter &voter)
{
    return findVote(voting.getId(), voter.getId());
}

/* If priority=0 all votes to be returned for this candiate */
QList<Vote> &PriorityFind::findVotes(Voting &voting, int priority, Candidate &candidate)
{    
    QList<Vote> *allVotes = new QList<Vote>();

    Voting *votingF = new Voting();
    *votingF = voting;

    Candidate *candidateF = new Candidate();
    *candidateF = candidate;


    /* findALLVotes() returns 9 votes but with only single voter */
    *allVotes = findAllVotes();

    int limit = getCandidateLimit(votingF, candidateF);


    QList<Vote> *allVotesForThisVoting = new QList<Vote>();

    for(int i=0; i<allVotes->size(); i++) {
        Voting *tmpVoting = new Voting();
        Vote *tmpVote = new Vote();
        *tmpVote = allVotes->at(i);
        *tmpVoting = tmpVote->getVoting();

        if(tmpVoting->getId() == voting.getId()) {
            allVotesForThisVoting->append(*tmpVote);
        }
    }


    QList<Vote> *allVotesForThisPriority = new QList<Vote>();

    for(int i=0; i< allVotesForThisVoting->size(); i++) {
        Vote *tmpVote = new Vote();
        *tmpVote = allVotesForThisVoting->at(i);

        /* Let's get all priorities and iterate */
        QMapIterator<int, int> itr(tmpVote->getCandidatesPriority());
        while(itr.hasNext()) {
            itr.next();
            int candidateId = itr.key();
            int tmpPriority = itr.value();

            /* If we found the matching priority and candidate add \
                to our allVotesForThisPriority list */
            if(priority!=0) {
                if(candidateId == candidate.getId() && tmpPriority == priority) {
                    allVotesForThisPriority->append(*tmpVote);
                }
            } else {
                if(candidateId == candidate.getId()) {
                    allVotesForThisPriority->append(*tmpVote);
                }
            }

        }
    }


    QList<Vote> *trimmedVotes = new QList<Vote>();


    if(allVotesForThisPriority->size()>limit) {
        *trimmedVotes = getTrimmedVotes(*allVotesForThisPriority, limit);
    } else {
        trimmedVotes = allVotesForThisPriority;
    }

    return *trimmedVotes;

}

QList<Vote> &PriorityFind::findVotes(Voting &voting)
{
    QList<Vote> *votes = &PriorityFind::findAllVotes();
    /* Let's randomize it */
    std::random_shuffle(votes->begin(), votes->end());

    QList<Vote> *formattedVotes = new QList<Vote>();

    for(int i=0; i<votes->size(); i++) {
        Vote *vote = new Vote();
        *vote = votes->at(i);
        Voting *vvoting = &vote->getVoting();

        if(vvoting->getId()==voting.getId()) {
            formattedVotes->append(votes->at(i));
        }
    }
    return *formattedVotes;
}

QList<Vote> &PriorityFind::findVotes(Voting &voting, int priority)
{
    QList<Vote> *votes = &PriorityFind::findVotes(voting);


    QList<Vote> *formattedVotes = new QList<Vote>();

    for(int i=0; i<votes->size(); i++) {
        // candidateId, priority
        QMap<int, int> *candidatesPriority = new QMap<int, int>();
        Vote *vote = new Vote();
        *vote = votes->at(i);

        *candidatesPriority = vote->getCandidatesPriority();
        QMapIterator<int, int>itr(*candidatesPriority);

        while(itr.hasNext()) {
            itr.next();
            int ppriority = itr.value();
            /* One candidatesPriority should have only one priority.
                So append should only append one vote */
            if(ppriority == priority) {
                formattedVotes->append(*vote);                
            }
        }
    }

    return *formattedVotes;


}


QList<Vote> &PriorityFind::findVotes(int priority)
{
    QList<Vote> *votes = &PriorityFind::findAllVotes();
    QList<Vote> *formattedVotes = new QList<Vote>();

    for(int i=0; i<votes->size(); i++) {
        // candidateId, priority
        QMap<int, int> *candidatesPriority = new QMap<int, int>();
        Vote *vote = new Vote();
        *vote = votes->at(i);

        *candidatesPriority = vote->getCandidatesPriority();
        QMapIterator<int, int>itr(*candidatesPriority);

        while(itr.hasNext()) {
            itr.next();
            int ppriority = itr.value();
            /* One candidatesPriority should have only one priority.
                So append should only append one vote */
            if(ppriority == priority) {
                formattedVotes->append(*vote);
            }
        }
    }

    return *formattedVotes;
}

static QList<Vote> &findVotes(Candidate &candidate)
{
    QList<Vote> *votes = &PriorityFind::findAllVotes();
    QList<Vote> *formattedVotes = new QList<Vote>();

    for(int i=0; i<votes->size(); i++) {
        // candidateId, priority
        QMap<int, int> *candidatesPriority = new QMap<int, int>();
        Vote *vote = new Vote();
        *vote = votes->at(i);

        *candidatesPriority = vote->getCandidatesPriority();
        QMapIterator<int, int>itr(*candidatesPriority);

        while(itr.hasNext()) {
            itr.next();
            int candidateId = itr.key();

            /* One candidatesPriority should have only one candidate.
                So append should only append one vote */
            if(candidateId == candidate.getId()) {
                formattedVotes->append(*vote);
            }
        }
    }

    return *formattedVotes;
}


QList<Vote> &PriorityFind::getTrimmedVotes(QList<Vote> &votes, int limit)
{
    QList<Vote> *allVotes = new QList<Vote>();
    QList<Vote> *trimmedVotes = new QList<Vote>();

    /* Get all votes first */
    *allVotes = findAllVotes();

    // If there is a doubt on shuffle uncomment these three blocks to see the shuffle
    /*
    for(int i=0; i<allVotes->size(); i++) {
        Vote *vote = new Vote();
        *vote = allVotes->at(i);
        PriorityConsole::print("Voter: " + vote->getVoter().getName());
    }
    */
    std::random_shuffle(allVotes->begin(), allVotes->end());

    // Since we have shuffled it is fair to include only first votes under the limit

    /*
    PriorityConsole::print("After shuffle");

    for(int i=0; i<allVotes->size(); i++) {
        Vote *vote = new Vote();
        *vote = allVotes->at(i);
        PriorityConsole::print("Voter: " + vote->getVoter().getName());
    }
    */


    for(int i=0; i<limit; i++) {
        /* There might be some method to add a block. Must see later.
            It is slower to append one at a time, when we have a block */
        trimmedVotes->append(allVotes->at(i));
    }
    return *trimmedVotes;
}

int PriorityFind::getCandidateLimit(Voting *voting, Candidate *candidate)
{

    /* From all votings match above voting.
     From all candidates of that voting match map of <Candidate, limit> return limit  */

    QMap<int, int> *candidateLimits = new QMap<int, int>();
    *candidateLimits = voting->getCandidatesLimit();

    //Candidate *ccandidate = new Candidate();
    int limit;

    QMapIterator<int, int> itr(*candidateLimits);

    while(itr.hasNext()) {
        itr.next();
        int candidateId = itr.key();
        if(candidateId == candidate->getId()) {
            limit = itr.value();
            break;
        }
    }

    return limit;
}

int PriorityFind::getCandidatePriority(Voting *voting, Candidate *candidate)
{
    QList<Vote> *zeroPriorityVotes = &findVotes(*voting, 0, *candidate);

    int candidatePriority;

    for(int i = 0; i < zeroPriorityVotes->size(); i++) {
        Vote *vote = new Vote();
        *vote = zeroPriorityVotes->at(i);

        QMapIterator<int, int>itr(vote->getCandidatesPriority());

        while(itr.hasNext()) {
            itr.next();
            int candidateId = itr.key();
            if(candidateId==candidate->getId()) {
                candidatePriority = itr.key();
                break;
            }
        }
    }

    return candidatePriority;

}

int PriorityFind::getCandidatePriority(Vote *vote, Candidate *candidate)
{
    int candidatePriority;
    QMapIterator<int, int>itr(vote->getCandidatesPriority());
    while(itr.hasNext()) {
        itr.next();
        int candidateId = itr.key();
        if(candidateId==candidate->getId()) {
            return itr.key();
        }
    }
    return candidatePriority;
}

int PriorityFind::getCandidatesCount(Voting &voting)
{
    QList<Candidate> *candidates = &findCandidates();
    int candidatesLimit = 0;
    for(int i=0; i<candidates->size(); i++) {
        Candidate *candidate = new Candidate();
        candidatesLimit+= getCandidateLimit(&voting, candidate);
    }

    return candidatesLimit;

}


QList<Vote> PriorityFind::findInternalVotes(Voting voting, int priority, Candidate candidate)
{
    QList<Vote> votes = findAllVotes();


    /* Cool up to here */

    QList<Vote> formattedVotes;
    QMap<int, int> *candidatesPriority = new QMap<int, int>();

    for(int i=0; i<votes.size(); i++) {
        Vote vote = votes.at(i);
        Voting vvoting = vote.getVoting();

        if(voting.getId() == vvoting.getId()) {

            /* Culprit */

            /* We might never have candidates up to this point */
            /* We have not got anything from file to fill candidates priority. So how do we get that */

            //PriorityConsole::print("findVotes()");
            *candidatesPriority = vote.getCandidatesPriority();
            // Candidate above could not get value so int had to be used.

            //PriorityConsole::print("findVotes() map");

            QMapIterator<int, int> itr(*candidatesPriority);
            while(itr.hasNext()) {
                //PriorityConsole::print("Start");
                itr.next();

                /* Key does not give candidate */
                /* The main problem is with traversing with QMap */
                int candidateId = itr.key();

                int ppriority = itr.value();

                if((candidateId == candidate.getId()) && (
                        priority == ppriority))
                    formattedVotes.append(votes.at(i));
            }
        }

    }

    //PriorityConsole::print("Reached end");

    return formattedVotes;

}


