#include <iostream>
#include <memory>
#include <string>

#include "Incident.h"

// State / Observer
#include "IncidentObserver.h"

// Command
#include "Command.h"
#include "CommandInvoker.h"
#include "DispatchUnitCommand.h"
#include "SecureAreaCommand.h"
#include "EmergencyAlertCommand.h"
#include "CancelCommand.h"

// Mediator / Response Components
#include "Mediator.h"
#include "CampusMediator.h"
#include "ResponseComponent.h"
#include "SecurityTeam.h"
#include "MedicalTeam.h"
#include "FacilitiesTeam.h"
#include "CommunicationService.h"

// Adapter
#include "AccessControl.h"
#include "LegacyAccessSystem.h"
#include "AccessControlAdapter.h"

// Facade
#include "EmergencyFacade.h"


// =========================================================
// ANSI COLOURS
// =========================================================

#define RESET          "\033[0m"
#define BOLD           "\033[1m"

#define RED            "\033[31m"
#define GREEN          "\033[32m"
#define YELLOW         "\033[33m"
#define BLUE           "\033[34m"
#define MAGENTA        "\033[35m"
#define CYAN           "\033[36m"

#define BOLD_RED       "\033[1;31m"
#define BOLD_GREEN     "\033[1;32m"
#define BOLD_YELLOW   "\033[1;33m"
#define BOLD_BLUE     "\033[1;34m"
#define BOLD_MAGENTA  "\033[1;35m"
#define BOLD_CYAN     "\033[1;36m"


// =========================================================
// HELPER
// =========================================================

void printSection(const std::string& title)
{
    std::cout << BOLD_BLUE
              << "\n========================================\n"
              << "        " << title << "\n"
              << "========================================\n"
              << RESET;
}


// =========================================================
// MAIN
// =========================================================

int main()
{
    std::cout << BOLD_BLUE
              << "========================================\n"
              << "       CAMPUSGUARD EMERGENCY SYSTEM\n"
              << "       INTEGRATED TESTING MAIN\n"
              << "========================================\n"
              << RESET;


    // =====================================================
    // SCENARIO 1
    // FIRE EMERGENCY
    // =====================================================

    printSection("SCENARIO 1: FIRE EMERGENCY");

    Incident fire(
        101,
        "Fire",
        "Engineering Building",
        "Fire reported on the second floor"
    );

    std::cout << GREEN
              << "[+] Incident 101 created.\n"
              << RESET;

    std::cout << "Type: "
              << fire.getType()
              << "\n";

    std::cout << "Location: "
              << fire.getLocation()
              << "\n";

    std::cout << "Initial State: "
              << fire.getStateName()
              << "\n";


    // =====================================================
    // RESPONSE COMPONENTS
    // (created early so they can also observe the incident)
    // =====================================================

    std::cout << BOLD_MAGENTA
              << "\n--- RESPONSE TEAMS ---\n"
              << RESET;

    SecurityTeam security("Campus Security");
    MedicalTeam medicalTeam("Medical Response");
    FacilitiesTeam facilities("Facilities Team");
    CommunicationService comms("Communication Service");

    std::cout << GREEN
              << "[+] Created SecurityTeam, MedicalTeam, FacilitiesTeam, CommunicationService.\n"
              << RESET;


    // =====================================================
    // OBSERVER PATTERN
    // =====================================================

    std::cout << BOLD_MAGENTA
              << "\n--- OBSERVER PATTERN ---\n"
              << RESET;

    std::cout << CYAN
              << "[i] Registering response components as observers of Incident 101...\n"
              << RESET;

    fire.attach(&security);
    fire.attach(&medicalTeam);
    fire.attach(&facilities);
    fire.attach(&comms);

    // Detaching one observer so the "erase" branch of detach() is exercised too.
    fire.detach(&comms);
    fire.attach(&comms);


    // =====================================================
    // STATE PATTERN
    // =====================================================

    std::cout << BOLD_MAGENTA
              << "\n--- STATE PATTERN ---\n"
              << RESET;

    std::cout << YELLOW
              << "[*] Activating fire incident (this will also notify observers)...\n"
              << RESET;

    fire.activate();

    std::cout << GREEN
              << "[+] Current state: "
              << fire.getStateName()
              << "\n"
              << RESET;

    std::cout << YELLOW
              << "[*] Activating an already-active incident (invalid transition)...\n"
              << RESET;

    fire.activate();


    // =====================================================
    // MEDIATOR
    // =====================================================

    std::cout << BOLD_MAGENTA
              << "\n--- MEDIATOR PATTERN ---\n"
              << RESET;

    CampusMediator mediator;

    std::cout << GREEN
              << "[+] CampusMediator created.\n"
              << RESET;

    mediator.registerComponent(&security);
    mediator.registerComponent(&medicalTeam);
    mediator.registerComponent(&facilities);
    mediator.registerComponent(&comms);

    // Invalid registrations, exercised deliberately for coverage:
    mediator.registerComponent(nullptr);                 // null component
    mediator.registerComponent(&security);                // duplicate role

    // A second, unregistered security team, wired to the same mediator
    // by hand, to exercise the "rejected / unregistered sender" path.
    SecurityTeam rogueSecurity("Rogue Security Unit");
    rogueSecurity.setMediator(&mediator);


    // =====================================================
    // ADAPTER PATTERN
    // =====================================================

    std::cout << BOLD_MAGENTA
              << "\n--- ADAPTER PATTERN ---\n"
              << RESET;

    LegacyAccessSystem legacySystem;
    AccessControlAdapter accessAdapter(&legacySystem);

    std::cout << GREEN
              << "[+] LegacyAccessSystem wrapped by AccessControlAdapter.\n"
              << RESET;

    facilities.setAccessControl(&accessAdapter);


    // =====================================================
    // COMMAND PATTERN
    // =====================================================

    std::cout << BOLD_MAGENTA
              << "\n--- COMMAND PATTERN ---\n"
              << RESET;

    CommandInvoker invoker;

    // Rejecting a null command (invalid path).
    invoker.execute(std::unique_ptr<Command>(nullptr));

    // 1. Dispatch security to the fire.
    invoker.execute(std::unique_ptr<Command>(
        new DispatchUnitCommand(&security, 101, "Engineering Building")));

    // 2. Secure the affected area (goes through the Adapter -> Legacy system).
    invoker.execute(std::unique_ptr<Command>(
        new SecureAreaCommand(&facilities, 101, "Engineering Building")));

    // 3. Issue an emergency alert.
    invoker.execute(std::unique_ptr<Command>(
        new EmergencyAlertCommand(&comms, 101, "Engineering Building",
                                   "Evacuate the building immediately")));

    invoker.printHistory();

    std::cout << YELLOW
              << "\n[*] Repeating the same operations to trigger invalid-operation checks...\n"
              << RESET;

    // Already deployed / already secured / already alerted -> all fail and
    // are therefore never added to the invoker's history.
    invoker.execute(std::unique_ptr<Command>(
        new DispatchUnitCommand(&security, 101, "Engineering Building")));
    invoker.execute(std::unique_ptr<Command>(
        new SecureAreaCommand(&facilities, 101, "Engineering Building")));
    invoker.execute(std::unique_ptr<Command>(
        new EmergencyAlertCommand(&comms, 101, "Engineering Building",
                                   "Evacuate the building immediately")));

    // The rogue (unregistered) security unit reports independently -> the
    // mediator should reject it.
    rogueSecurity.dispatch(101, "North Car Park");

    std::cout << YELLOW
              << "\n[*] Cancelling commands via the invoker...\n"
              << RESET;

    invoker.cancelLast();      // undoes the emergency alert (clearAlert)
    invoker.cancel(1);         // undoes the secure-area command (reopenArea)
    invoker.cancel(1);         // area already reopened -> invalid, nothing to cancel
    invoker.cancel(0);         // undoes the dispatch command (recall)
    invoker.cancel(999);       // out-of-range index -> invalid

    invoker.printHistory();

    std::cout << "[i] Last dispatch command executed? "
              << std::boolalpha << security.isDeployed() << "\n";


    // =====================================================
    // FACADE PATTERN
    // =====================================================

    std::cout << BOLD_MAGENTA
              << "\n--- FACADE PATTERN ---\n"
              << RESET;

    EmergencyFacade facade(&accessAdapter);
    facade.handleSevereEmergency("Science Block", "Fire");


    // =====================================================
    // DIRECT SUBSYSTEM / EDGE-CASE COVERAGE
    // =====================================================

    std::cout << BOLD_MAGENTA
              << "\n--- ADDITIONAL EDGE CASES ---\n"
              << RESET;

    // Dispatching with an empty location (invalid).
    security.dispatch(101, "");

    // Recalling a unit that was never dispatched (invalid).
    medicalTeam.recall();

    // CommunicationService cannot itself be dispatched as a field unit.
    comms.dispatch(101, "Engineering Building");

    // Clearing an alert that was never issued (invalid).
    comms.clearAlert(101, "Student Centre");

    // Reopening an area that was never secured (invalid).
    facilities.reopenArea(101, "Student Centre");

    // A response component that is never wired to a mediator: announcing
    // still works, it just has nobody to notify.
    SecurityTeam standaloneUnit("Standby Unit");
    standaloneUnit.dispatch(150, "Remote Sports Field");


    // =====================================================
    // SCENARIO 2
    // MEDICAL EMERGENCY
    // =====================================================

    printSection("SCENARIO 2: MEDICAL EMERGENCY");

    Incident medical(
        102,
        "Medical Emergency",
        "Student Centre",
        "Student requires immediate medical assistance"
    );

    std::cout << GREEN
              << "[+] Incident 102 created.\n"
              << RESET;

    std::cout << "Type: "
              << medical.getType()
              << "\n";

    std::cout << "Location: "
              << medical.getLocation()
              << "\n";

    std::cout << "Initial State: "
              << medical.getStateName()
              << "\n";

    medical.attach(&medicalTeam);
    medical.attach(&security);

    std::cout << YELLOW
              << "\n[*] Activating medical incident...\n"
              << RESET;

    medical.activate();

    std::cout << GREEN
              << "[+] Medical incident state: "
              << medical.getStateName()
              << "\n"
              << RESET;


    // =====================================================
    // SECOND COMMAND SCENARIO
    // =====================================================

    std::cout << BOLD_MAGENTA
              << "\n--- MEDICAL RESPONSE COMMAND ---\n"
              << RESET;

    CommandInvoker medicalInvoker;

    // Cancelling with an empty history (invalid).
    medicalInvoker.cancelLast();

    medicalInvoker.execute(std::unique_ptr<Command>(
        new DispatchUnitCommand(&medicalTeam, 102, "Student Centre")));

    medicalInvoker.execute(std::unique_ptr<Command>(
        new EmergencyAlertCommand(&comms, 102, "Student Centre",
                                   "Medical response in progress")));

    medicalInvoker.printHistory();


    // =====================================================
    // RESOLVE
    // =====================================================

    std::cout << YELLOW
              << "\n[*] Resolving medical incident...\n"
              << RESET;

    medical.resolve();

    std::cout << GREEN
              << "[+] Medical incident state: "
              << medical.getStateName()
              << "\n"
              << RESET;

    std::cout << YELLOW
              << "[*] Resolving an already-resolved incident (invalid)...\n"
              << RESET;

    medical.resolve();

    std::cout << YELLOW
              << "[*] Cancelling an already-resolved incident (invalid)...\n"
              << RESET;

    medical.cancel();


    // =====================================================
    // FINAL SUMMARY
    // =====================================================

    printSection("INTEGRATED TEST COMPLETE");

    std::cout << GREEN
              << "[+] Incident tested\n"
              << "[+] State Pattern tested\n"
              << "[+] Observer Pattern integrated\n"
              << "[+] Command Pattern integrated\n"
              << "[+] Multiple Commands executed\n"
              << "[+] Mediator integrated\n"
              << "[+] Response teams integrated\n"
              << "[+] Adapter integrated\n"
              << "[+] Legacy access system integrated\n"
              << "[+] Facade integrated\n"
              << "[+] Two incident scenarios tested\n"
              << "[+] Invalid operation tested\n"
              << RESET;

    std::cout << BOLD_GREEN
              << "\n========================================\n"
              << "       CAMPUSGUARD TEST COMPLETE\n"
              << "========================================\n"
              << RESET;

    return 0;
}