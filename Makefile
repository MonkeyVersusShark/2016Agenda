CC := g++
FLAGS := -std=c++11 -w
INC_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
INCLUDE := -I ./$(INC_DIR)

$(BIN_DIR)/Agenda : $(BUILD_DIR)/AgendaUI.o $(BUILD_DIR)/AgendaService.o \
					$(BUILD_DIR)/Storage.o $(BUILD_DIR)/Meeting.o \
					$(BUILD_DIR)/Date.o $(BUILD_DIR)/User.o \
					$(SRC_DIR)/Agenda.cpp $(INC_DIR)/AgendaUI.hpp
	$(CC) $(FLAGS) $(INCLUDE) -o $(BIN_DIR)/Agenda \
					$(BUILD_DIR)/AgendaUI.o $(BUILD_DIR)/AgendaService.o \
					$(BUILD_DIR)/Storage.o $(BUILD_DIR)/Meeting.o \
					$(BUILD_DIR)/Date.o $(BUILD_DIR)/User.o \
					$(SRC_DIR)/Agenda.cpp

$(BUILD_DIR)/AgendaUI.o : $(INC_DIR)/AgendaService.hpp $(INC_DIR)/AgendaUI.hpp $(SRC_DIR)/AgendaUI.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c $(SRC_DIR)/AgendaUI.cpp -o $(BUILD_DIR)/AgendaUI.o

$(BUILD_DIR)/AgendaService.o : $(INC_DIR)/Storage.hpp $(INC_DIR)/AgendaService.hpp $(SRC_DIR)/AgendaService.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c $(SRC_DIR)/AgendaService.cpp -o $(BUILD_DIR)/AgendaService.o

$(BUILD_DIR)/Storage.o : $(INC_DIR)/User.hpp $(INC_DIR)/Meeting.hpp $(INC_DIR)/Storage.hpp $(SRC_DIR)/Storage.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c $(SRC_DIR)/Storage.cpp -o $(BUILD_DIR)/Storage.o

$(BUILD_DIR)/Meeting.o : $(INC_DIR)/Date.hpp $(INC_DIR)/Meeting.hpp $(SRC_DIR)/Meeting.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c $(SRC_DIR)/Meeting.cpp -o $(BUILD_DIR)/Meeting.o

$(BUILD_DIR)/Date.o : $(INC_DIR)/Date.hpp $(SRC_DIR)/Date.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c $(SRC_DIR)/Date.cpp -o $(BUILD_DIR)/Date.o

$(BUILD_DIR)/User.o : $(INC_DIR)/User.hpp $(SRC_DIR)/User.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c $(SRC_DIR)/User.cpp -o $(BUILD_DIR)/User.o

.PHONY:	clean
clean:
	-rm -f $(BUILD_DIR)/*.o $(BIN_DIR)/Agenda
