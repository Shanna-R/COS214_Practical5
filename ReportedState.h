#ifndef REPORTEDSTATE_H
#define REPORTEDSTATE_H

#include "IncidentState.h"

class ReportedState : public IncidentState
{
    public:
        void activate(Incident& incident) override;
        void resolve(Incident& incident) override;
        void cancel(Incident& incident) override;
        const char* getName() const override;
};

#endif