Licence is GPL v3

This is a project of choosing candidates based on each voter's priority. Here i assume candidates are limited. This project is dedicated to Qwati9 group(I remember you guys). 

This project is written in c++ with some Qt classes for GUI, String and iterators (I think stl was better solution). 

Think of this as a situation where there are 2 managerial posts and there are 4 voters for that post. Lets expand this one step further. Say there are 2 posts and first can accommodate 4 members and second can accommodate 5 members. There may be many elligible candidates for these posts and any of them can take any one. If you can't decide what to give to whom. The software randomizes each people if their numbes clash. If their number come under limit they get the vote. In our example if only one people voted for 2nd catagory as his first priority he gets it. But if 50 people voted for 1st catagory as their first priority and 2nd catagory as their 2nd priority, and since we have only 5 member limit on first. Only 5 people among 50 gets the first priority randomly and one among remaining 45 will get 2nd catagory as their 2nd priority.



I have choosen text file to put data.

1. catagories.txt inputs catagories on each line as
Id:Catagory name
E.g
1:Apple
2:Orange
3:Pear

These are the names and id of catagories. Say each post, each type of work, each type of goods to carry to a picnic, each type of place one can visit etc.

2. settings.txt
It is not complete yet. It contains following format of text
F/I,Active Voting Number,Reference Voting Number
E.g f,2,1

For this release reference voting is not used so the format is simplified as
f,1

Still f has no meaning for this release.

3. voters.txt
It is simple. It contains each voter who is voting for particular voting
Id:Name

4. votings.txt
There will be sevaral votings you want to do. Settings.txt will choose which voting you want to select as active.

Voting Id, Voting Name, Candidate Id:Limit

E.g
1,My First Voting,1:3,2:3,3:3
2,My Second Voting,1:3,2:3,3:3
3,My Third Voting,1:2,2:4,3:3
4,My Fourth Voting,1:5,2:3,3:1

Every catagory of catagories.txt is expected to get a limit here.
Here limit is the limit of each candidate. 5 people can vote for a catagory but only limited people will get that candidate.

5. votes.txt
This is where the votes will be registered. You can enter votes from gui. But still validation is not used to select unique vote for each voting.

Voter Id, Voting Id, Priority:Candidate Id

If you don't have entry here for particular voting then no result will come.
Here voter id should be unique but only for a particular voting Id.

E.g f,1 in settings.txt indicate our active voting is 1 I.e(1, My First Voting, 1:3, 2:3, 3:3)

So we should have in votes.txt entries for Voting Id 1

E.g
1,1,1:3,2:1,3:2
2,1,1:1,2:2,3:3

refer voter with id(1) for voting id(1) selected catagory 3 as his first priority, catagory 1 as his second priority and catagory 2 as his third priority. And so on for other voters for this voting. This file will append all the votes for other votings too.

For programmers see PriorityUtil::calculateResult() method of priorityutil.cpp and PriorityFind::findVotes(voting)
 

Thank You 

  Pramod Nepal
