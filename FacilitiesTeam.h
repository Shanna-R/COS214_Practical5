#ifndef FACILITIESTEAM_H
#define FACILITIESTEAM_H

#include <set>
#include "ResponseComponent.h"

class AccessControl;

class FacilitiesTeam : public ResponseComponent {
public:
    explicit FacilitiesTeam(const std::string& name = "Facilities Team");
    ~FacilitiesTeam() override;

    void setAccessControl(AccessControl* access);
    ComponentRole role() const override;

    bool secureArea(int incidentId, const std::string& area);
    bool reopenArea(int incidentId, const std::string& area);
    bool isSecured(const std::string& area) const;

    void receive(const CampusEvent& event) override;

private:
    AccessControl* access_;
    std::set<std::string> secured_;
};

#endif
