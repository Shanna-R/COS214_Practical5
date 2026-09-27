#ifndef SECURITYTEAM_H
#define SECURITYTEAM_H

#include "ResponseComponent.h"

class SecurityTeam : public ResponseComponent {
public:
    explicit SecurityTeam(const std::string& name = "Campus Security");
    ~SecurityTeam() override;
    ComponentRole role() const override;
    void receive(const CampusEvent& event) override;
};

#endif
