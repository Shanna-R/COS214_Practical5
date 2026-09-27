#include <iostream>
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
    // STATE PATTERN
    // =====================================================

    std::cout << BOLD_MAGENTA
              << "\n--- STATE PATTERN ---\n"
              << RESET;

    std::cout << YELLOW
              << "[*] Activating fire incident...\n"
              << RESET;

    fire.activate();

    std::cout << GREEN
              << "[+] Current state: "
              << fire.getStateName()
              << "\n"
              << RESET;


    // =====================================================
    // OBSERVER PATTERN
    // =====================================================

    std::cout << BOLD_MAGENTA
              << "\n--- OBSERVER PATTERN ---\n"
              << RESET;

    std::cout << CYAN
              << "[i] Response components are registered as observers "
              << "through the integrated system.\n"
              << RESET;


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


    // =====================================================
    // RESPONSE COMPONENTS
    // =====================================================

    std::cout << BOLD_MAGENTA
              << "\n--- RESPONSE TEAMS ---\n"
              << RESET;

    /*
     * Create the response components here using the
     * constructors defined in your current .h files.
     *
     * They should include:
     *
     * SecurityTeam
     * MedicalTeam
     * FacilitiesTeam
     * CommunicationService
     *
     * Then register them with the CampusMediator.
     */


    // =====================================================
    // COMMAND PATTERN
    // =====================================================

    std::cout << BOLD_MAGENTA
              << "\n--- COMMAND PATTERN ---\n"
              << RESET;

    /*
     * Create a CommandInvoker.
     *
     * Execute at least THREE concrete commands:
     *
     * 1. DispatchUnitCommand
     * 2. SecureAreaCommand
     * 3. EmergencyAlertCommand
     *
     * The exact constructor calls must match the current
     * command class headers.
     */


    // =====================================================
    // ADAPTER PATTERN
    // =====================================================

    std::cout << BOLD_MAGENTA
              << "\n--- ADAPTER PATTERN ---\n"
              << RESET;

    /*
     * Create the legacy access system.
     *
     * Create AccessControlAdapter using the legacy system.
     *
     * Then perform a real lock/unlock operation.
     *
     * Example flow:
     *
     * LegacyAccessSystem
     *        ↑
     * AccessControlAdapter
     *        ↑
     * EmergencyFacade / CampusGuard
     */


    // =====================================================
    // FACADE PATTERN
    // =====================================================

    std::cout << BOLD_MAGENTA
              << "\n--- FACADE PATTERN ---\n"
              << RESET;

    /*
     * EmergencyFacade should coordinate:
     *
     * DispatchService
     * BuildingAccessService
     * AlertService
     *
     * This should result in 3+ subsystem operations.
     */


    // =====================================================
    // INVALID OPERATION
    // =====================================================

    std::cout << BOLD_RED
              << "\n--- INVALID OPERATION TEST ---\n"
              << RESET;

    std::cout << RED
              << "[!] Attempting to activate a resolved incident...\n"
              << RESET;

    fire.resolve();

    fire.activate();


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


    // Activate second incident

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

    /*
     * Use the CommandInvoker and a concrete command to
     * dispatch/coordinate the medical response.
     */


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
