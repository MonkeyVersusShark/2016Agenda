CC := g++
FLAGS := -std=c++11 -w
INC_DIR := ../include
SRC_DIR := ../src
INCLUDE := -I $(INC_DIR)
GTEST := -lgtest -lpthread

test : test.o Date.o DateTest.o User.o UserTest.o Meeting.o MeetingTest.o Storage.o StorageTest.o
	$(CC) $(FLAGS) $(INCLUDE) -o test test.o \
								Date.o DateTest.o \
								User.o UserTest.o \
								Meeting.o MeetingTest.o \
								Storage.o StorageTest.o $(GTEST)
	@-rm -f *.o

test.o : test.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c test.cpp

Date.o : $(INC_DIR)/Date.hpp $(SRC_DIR)/Date.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c  $(SRC_DIR)/Date.cpp

DateTest.o : $(INC_DIR)/Date.hpp DateTest.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c DateTest.cpp

User.o : $(INC_DIR)/User.hpp $(SRC_DIR)/User.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c  $(SRC_DIR)/User.cpp

UserTest.o : $(INC_DIR)/User.hpp UserTest.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c UserTest.cpp

Meeting.o : $(INC_DIR)/Date.hpp $(INC_DIR)/Meeting.hpp $(SRC_DIR)/Meeting.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c  $(SRC_DIR)/Meeting.cpp

MeetingTest.o : $(INC_DIR)/Meeting.hpp MeetingTest.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c MeetingTest.cpp

Storage.o : $(INC_DIR)/User.hpp $(INC_DIR)/Meeting.hpp $(INC_DIR)/Storage.hpp $(SRC_DIR)/Storage.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c $(SRC_DIR)/Storage.cpp

StorageTest.o : $(INC_DIR)/Storage.hpp StorageTest.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c StorageTest.cpp

.PHONY:	clean
clean:
	-rm -f test
