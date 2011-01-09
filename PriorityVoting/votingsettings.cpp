#include "votingsettings.h"
#include "priorityfile.h"
#include "priorityfind.h"

VotingSettings* VotingSettings::_instance = 0;
VotingSettings::VotingSettings()
{
}

VotingSettings &VotingSettings::Instance()
{
    if(_instance == 0) {
        _instance = new VotingSettings;

        // Let's open settings.txt and set active and reference
        QList<QString> list = PriorityFile::readFile("settings.txt");
        QString line = list.at(0);
        QList<QString> items = line.split(",");
        QString sactive;
        QString sreference;
        if(items.size()>1) {
            sactive = items.at(1);
            _instance->active = PriorityFind::findVoting(sactive.toInt());
        }
        if(items.size()>2) {
            sreference = items.at(2);
            _instance->referene = PriorityFind::findVoting(sreference.toInt());
        }
    }
    return *_instance;
}

Voting &VotingSettings::getActiveVoting()
{
    VotingSettings *votingSettings = new VotingSettings();
    votingSettings = &VotingSettings::Instance();
    Voting *voting = new Voting();
    *voting = votingSettings->active;
    return *voting;
}

Voting &VotingSettings::getReferenceVoting()
{
    VotingSettings *votingSettings = &VotingSettings::Instance();
    Voting *voting = new Voting();
    *voting = votingSettings->referene;
    return *voting;
}
