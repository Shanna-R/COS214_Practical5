#ifndef RESOLVEDSTATE_H
#define RESOLVEDSTATE_H

#include "IncidentState.h"

class ResolvedState : public IncidentState
{
    public:
        void activate(Incident& incident) override;
        void resolve(Incident& incident) override;
        void cancel(Incident& incident) override;
        const char* getName() const override;
};

#endif