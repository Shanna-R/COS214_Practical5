CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g -I.
COVFLAGS = $(CXXFLAGS) --coverage -fprofile-arcs -ftest-coverage -O0

TARGET     = CampusGuard
COV_DIR    = coverage
COV_TARGET = $(COV_DIR)/CampusGuard_cov

SRCS = main.cpp \
       Incident.cpp \
       IncidentState.cpp \
       ReportedState.cpp \
       ActiveState.cpp \
       ResolvedState.cpp \
       IncidentObserver.cpp \
       IncidentSubject.cpp \
       Command.cpp \
       DispatchUnitCommand.cpp \
       SecureAreaCommand.cpp \
       EmergencyAlertCommand.cpp \
       CancelCommand.cpp \
       CommandInvoker.cpp \
       Mediator.cpp \
       CampusMediator.cpp \
       ResponseComponent.cpp \
       SecurityTeam.cpp \
       MedicalTeam.cpp \
       FacilitiesTeam.cpp \
       CommunicationService.cpp \
       AccessControl.cpp \
       LegacyAccessSystem.cpp \
       AccessControlAdapter.cpp \
       EmergencyFacade.cpp \
       DispatchService.cpp \
       AlertService.cpp \
       BuildingAccessService.cpp

OBJS     = $(SRCS:.cpp=.o)
COV_OBJS = $(addprefix $(COV_DIR)/,$(SRCS:.cpp=.o))

# ──────────────────────────────────────────
# Default build
# ──────────────────────────────────────────
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ──────────────────────────────────────────
# Run the engine
#   make run
# ──────────────────────────────────────────
run: $(TARGET)
	./$(TARGET)

# ──────────────────────────────────────────
# Valgrind — full memory-leak check
#   make valgrind
# ──────────────────────────────────────────
valgrind: $(TARGET)
	valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--error-exitcode=1 \
		./$(TARGET)

# ──────────────────────────────────────────
# Coverage build + HTML Report
#   make coverage
# ──────────────────────────────────────────
$(COV_DIR)/%.o: %.cpp
	@mkdir -p $(COV_DIR)
	$(CXX) $(COVFLAGS) -c $< -o $@

$(COV_TARGET): $(COV_OBJS)
	$(CXX) $(COVFLAGS) -o $(COV_TARGET) $(COV_OBJS)

coverage: $(COV_TARGET)
	./$(COV_TARGET)
	lcov --capture --directory $(COV_DIR) --output-file $(COV_DIR)/coverage.info --rc lcov_branch_coverage=1
	lcov --remove $(COV_DIR)/coverage.info '/usr/*' --output-file $(COV_DIR)/coverage.info
	genhtml $(COV_DIR)/coverage.info --output-directory $(COV_DIR) --branch-coverage
	@echo "----------------------------------------------------"
	@echo "Coverage report ready: open $(COV_DIR)/index.html"
	@echo "----------------------------------------------------"

coverage-html: coverage

# ──────────────────────────────────────────
# Generate Doxygen Documentation
#   make doc
# ──────────────────────────────────────────
doc:
	doxygen Doxyfile
	@echo "----------------------------------------------------"
	@echo "Documentation generated: open docs/html/index.html"
	@echo "----------------------------------------------------"

# ──────────────────────────────────────────
# Clean
# ──────────────────────────────────────────
clean:
	rm -f *.o $(TARGET)
	rm -rf $(COV_DIR)
	rm -rf docs/html docs/latex

.PHONY: all run valgrind coverage coverage-html doc clean