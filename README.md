# COS214_Practical5

## CampusGuard

CampusGuard is an integrated emergency-response coordination platform. The platform models a campus safety management ecosystem, allowing security teams, medical responders, facilities staff, and legacy access systems to respond dynamically to critical campus events. It supports incident lifecycle management, operator command execution, response team coordination, and legacy integration through an automated workflow.

The project is implemented in C++11 and demonstrates six Gang of Four (GoF) design patterns:
* **State** 
* **Observer** 
* **Command** 
* **Mediator** 
* **Adapter** 
* **Facade** 

---

## Team Members

* **Shanna Reinecke** 
* **Conrad Botha** 
* **Livhuwani Munyai** 

---

## Course Information

* **Module:** COS 214
* **Practical:** Practical 5
* **Project:** CampusGuard - Emergency Response Coordination
* **Language:** C++11

---

## Project Features

CampusGuard demonstrates:
* Incident reporting, tracking, and lifecycle management across valid/invalid states.
* Event notification mechanisms to alert response components upon incident state changes.
* Operator command execution with support for dispatch, area security, emergency alerts, and cancellations.
* Centralized communication and coordination between response teams via a Mediator.
* Seamless translation between modern campus protocol and legacy access-control hardware interfaces.
* High-level, multi-step emergency workflows abstracted behind an intuitive Facade interface.
* Safe polymorphic object destruction, clean memory management, and leak-free execution.
* Multi-container environment and deployment fully automated using Docker and Docker Compose.

---

## Design Patterns

### State
Controls the lifecycle of an incident (`ReportedState`, `ActiveState`, `ResolvedState`). The behaviour of an incident depends on its current state, and invalid state transitions (e.g., directly moving from Resolved to Active) are safely intercepted and prevented by the system.

### Observer
Notifies registered response components and dispatch services whenever an incident undergoes a state or priority change, decoupling incident logic from external notification workflows.

### Command
Encapsulates operator actions (such as `DispatchUnitCommand`, `SecureAreaCommand`, `EmergencyAlertCommand`, and `CancelCommand`) into discrete objects that can be executed, queued, logged, or revoked dynamically by a `CommandInvoker`.

### Mediator
Coordinates communication among response teams (`SecurityTeam`, `MedicalTeam`, `FacilitiesTeam`, `CommunicationService`) through a central `CampusMediator`, eliminating direct many-to-many dependencies between individual teams.

### Adapter
Translates modern high-level commands into the incompatible parameter interfaces expected by legacy systems, integrating `LegacyAccessSystem` into the `AccessControl` interface.

### Facade
Provides a unified, simplified entry point (`EmergencyFacade`) that orchestrates complex multi-subsystem workflows—activating incidents, dispatching teams, locking down facilities, and broadcasting alerts—with a single method call.

---

## Repository Structure

```text
214-Prac-5-group1/
|-- *.gitignore
|-- *.cpp                     C++ source files
|-- *.h                       C++ header files
|-- main.cpp                  Program entry point
|-- Makefile                  Project build instructions
|-- Dockerfile                Docker environment
|-- README.md                 Project documentation
|-- State diagram.jpg
|-- Mediator sequence diagram.jpg
|-- Command sequence diagram.jpg
|-- Facade sequence diagram.jpg
|-- Adapter sequence diagram.jpg
|-- Prac5.vpp
|-- Cos_214 PracDocument.docx
|-- Debugging Evidence.png
|-- GDB Evidence.png
|-- Valgrind Evidence.png


## Building the Project

The final executable is named:

```bash
CampusGuard
```

The project can be compiled using:

```bash
make run
```

To remove generated object files and the executable:

```bash
make clean
```

To rebuild the complete project:

```bash
make clean
make
```

## Running CampusGuard

After compiling the project:

```bash
./CampusGuard
```

## Docker

The project includes a Docker environment containing the tools required to compile, run and debug CampusGuard.

The Docker environment includes:

```text
g++
make
gdb
valgrind
lcov
doxygen
graphviz
```

No project-specific development tools need to be installed directly on the host computer.

### Build the Docker Image

From the root directory of the repository run:

```bash
docker build -t CampusGuard .
```

### Open the Docker Environment

Run:

```bash
docker run --rm -it --entrypoint /bin/bash campusguard
```

Once inside the container, compile the project using:

```bash
make
```

Then run CampusGuard using:

```bash
./CampusGuard
```

## GDB
To debug CampusGuard using GDB inside the Docker container, start the container with debugging permissions:
```bash
sudo docker run --rm -it --cap-add=SYS_PTRACE --security-opt seccomp=unconfined --entrypoint /bin/bash campusguard
```
compile the project :
```bash
make clean && make
```


To debug CampusGuard using GDB inside the Docker container:

```bash
gdb ./CampusGuard
```

Example useful GDB commands:

```text
break main
run
next
step
print fire
continue
quit
```

## Valgrind

To check the program for memory leaks and memory errors:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./CampusGuard
```

The final implementation should contain no definitely-lost memory originating from the project code.

## UML Documentation

The `docs/` directory contains the UML documentation for the project.

The project includes:

* UML Class Diagram
* UML State Diagram
* Three UML Sequence Diagrams

The diagrams reflect the final C++ implementation and the runtime behaviour of CampusGuard.


