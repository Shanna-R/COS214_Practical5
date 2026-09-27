#ifndef MEDICALTEAM_H
#define MEDICALTEAM_H

#include "ResponseComponent.h"

class MedicalTeam : public ResponseComponent {
public:
    explicit MedicalTeam(const std::string& name = "Medical Response");
    ~MedicalTeam() override;
    ComponentRole role() const override;
    void receive(const CampusEvent& event) override;
};

#endif
