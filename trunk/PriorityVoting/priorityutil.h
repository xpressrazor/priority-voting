#ifndef PRIORITYUTIL_H
#define PRIORITYUTIL_H

#include <QtGlobal>
#include <QTime>
#include <QMap>
#include "vote.h"
#include "candidate.h"

class PriorityUtil
{
public:    
    int randInt(int low, int high);
    static QMap<int, QString> &calculateResult();    
    PriorityUtil();

};

#endif // PRIORITYUTIL_H
