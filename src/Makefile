Agenda:	Agenda.o AgendaUI.o AgendaService.o Storage.o Meeting.o User.o Date.o
		g++ -o Agenda -std=c++11 Agenda.o AgendaUI.o AgendaService.o Storage.o Meeting.o User.o Date.o
		mv Agenda ../bin/
		mv *.o ../build/
Agenda.o: Agenda.cpp ../include/AgendaUI.hpp
		g++ -c -std=c++11 -I ../include/ Agenda.cpp
AgendaUI.o:	AgendaUI.cpp ../include/AgendaUI.hpp ../include/AgendaService.hpp
		g++ -c -std=c++11 -I ../include/ AgendaUI.cpp
AgendaService.o: ../include/Storage.hpp AgendaService.cpp ../include/AgendaService.hpp
		g++ -c -std=c++11 -I ../include/ AgendaService.cpp
Storage.o: ../include/Meeting.hpp ../include/User.hpp Storage.cpp ../include/Storage.hpp ../include/Path.hpp
		g++ -c -std=c++11 -I ../include/ Storage.cpp
Meeting.o: ../include/Date.hpp Meeting.cpp ../include/Meeting.hpp
		g++ -c -std=c++11 -I ../include/ Meeting.cpp
User.o: User.cpp ../include/User.hpp
		g++ -c -std=c++11 -I ../include/ User.cpp
Date.o: Date.cpp ../include/Date.hpp
		g++ -c -std=c++11 -I ../include/ Date.cpp
.PHONY:	clean
clean:
		-rm -f ../build/*.o ../bin/Agenda
