#include "Incident.h"

#include <iostream>

// =========================================================
// ANSI COLOR ESCAPE CODES FOR TERMINAL FORMATTING
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
#define BOLD_YELLOW    "\033[1;33m"
#define BOLD_BLUE      "\033[1;34m"
#define BOLD_MAGENTA   "\033[1;35m"
#define BOLD_CYAN      "\033[1;36m"


// =========================================================
// MAIN
// =========================================================

int main()
{
    std::cout << BOLD_BLUE
              << "========================================\n"
              << "       CAMPUSGUARD EMERGENCY SYSTEM\n"
              << "========================================\n"
              << RESET;


    // CREATE INCIDENT
    std::cout << BOLD_CYAN
              << "\n===== CREATING INCIDENT =====\n"
              << RESET;

    Incident fire(
        101,
        "Fire",
        "Engineering Building",
        "Fire reported on the second floor"
    );

    std::cout << GREEN
              << "[+] Incident 101 created successfully.\n"
              << RESET;

    std::cout << BOLD
              << "Incident Type: "
              << RESET
              << fire.getType()
              << std::endl;

    std::cout << BOLD
              << "Location: "
              << RESET
              << fire.getLocation()
              << std::endl;

    std::cout << BOLD
              << "Initial State: "
              << RESET
              << YELLOW
              << fire.getStateName()
              << RESET
              << std::endl;



    // STATE PATTERN TEST
    std::cout << BOLD_MAGENTA
              << "\n========================================\n"
              << "        STATE PATTERN TEST\n"
              << "========================================\n"
              << RESET;


    // INVALID: REPORTED -> RESOLVED
    std::cout << BOLD_RED
              << "\n--- Invalid State Transition ---\n"
              << RESET;

    std::cout << RED
              << "Attempting to resolve a REPORTED incident...\n"
              << RESET;

    fire.resolve();


    // VALID: REPORTED -> ACTIVE
    std::cout << BOLD_YELLOW
              << "\n--- Activating Incident ---\n"
              << RESET;

    fire.activate();

    std::cout << GREEN
              << "[+] Incident is now "
              << fire.getStateName()
              << ".\n"
              << RESET;


    // VALID: ACTIVE -> RESOLVED
    std::cout << BOLD_YELLOW
              << "\n--- Resolving Incident ---\n"
              << RESET;

    fire.resolve();

    std::cout << GREEN
              << "[+] Incident is now "
              << fire.getStateName()
              << ".\n"
              << RESET;


    // INVALID: RESOLVED -> ACTIVE
    std::cout << BOLD_RED
              << "\n--- Invalid State Transition ---\n"
              << RESET;

    std::cout << RED
              << "Attempting to activate a RESOLVED incident...\n"
              << RESET;

    fire.activate();


    // SECOND INCIDENT
    std::cout << BOLD_CYAN
              << "\n========================================\n"
              << "        SECOND INCIDENT TEST\n"
              << "========================================\n"
              << RESET;

    Incident medical(
        102,
        "Medical Emergency",
        "Student Centre",
        "Student requires immediate medical assistance"
    );

    std::cout << GREEN
              << "[+] Incident 102 created successfully.\n"
              << RESET;

    std::cout << BOLD
              << "Initial State: "
              << RESET
              << YELLOW
              << medical.getStateName()
              << RESET
              << std::endl;

    medical.activate();

    std::cout << GREEN
              << "[+] Medical incident activated.\n"
              << RESET;

    medical.resolve();

    std::cout << GREEN
              << "[+] Medical incident resolved.\n"
              << RESET;


    // OBSERVER PATTERN NOTE
    std::cout << BOLD_MAGENTA
              << "\n========================================\n"
              << "       OBSERVER PATTERN READY\n"
              << "========================================\n"
              << RESET;

    std::cout << CYAN
              << "[i] Incident supports Observer registration.\n"
              << "[i] Response teams can attach as observers.\n"
              << "[i] State changes automatically notify observers.\n"
              << RESET;


    // FINAL SUMMARY
    std::cout << BOLD_GREEN
              << "\n========================================\n"
              << "       PERSON 1 TEST COMPLETE\n"
              << "========================================\n"
              << RESET;

    std::cout << GREEN
              << "[+] Incident class tested\n"
              << "[+] State Pattern tested\n"
              << "[+] Valid transitions tested\n"
              << "[+] Invalid transitions tested\n"
              << "[+] Multiple incidents tested\n"
              << "[+] Observer structure ready for integration\n"
              << RESET;

    return 0;
}