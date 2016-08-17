#include "AgendaUI.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

AgendaUI::AgendaUI() { }

void AgendaUI::OperationLoop(void) {
    startAgenda();
    while (true) {
        std::cout << "\n--------------------------Agenda--------------------------\n";
        std::cout << "Action :" << std::endl;
        std::cout << "l   - log in Agenda by user name and password"<< std::endl;
        std::cout << "r   - register an Agenda account" << std::endl;
        std::cout << "q   - quit Agenda" << std::endl;
        std::cout << "----------------------------------------------------------\n\n";
        std::cout << "Agenda : ~$ ";
        std::string t_operation = getOperation();
        while (t_operation != "l" && t_operation != "r" && t_operation != "q") {
            std::cout << "Operation not found!" << std::endl;
            std::cout << "Agenda : ~$ ";
            t_operation = getOperation();
        }
        if (!executeOperation(t_operation))
            break;
    }
}

/**
 * constructor
 */
void AgendaUI::startAgenda(void) { m_agendaService.startAgenda(); }

/**
 * catch user's operation
 * @return the operation
 */
std::string AgendaUI::getOperation() {
    std::string t_operation;
    std::cin >> t_operation;
    return t_operation;
}

/**
 * execute the operation
 * @return if the operationloop continue
 */
bool AgendaUI::executeOperation(std::string t_operation) {
    if (t_operation == "l") {
        userLogIn();
        return true;
    } else if (t_operation == "r") {
        userRegister();
        return true;
    } else if (t_operation == "q") {
        quitAgenda();
        return false;
    } else if (t_operation == "o") {
        userLogOut();
        return false;
    } else if (t_operation == "dc") {
        deleteUser();
        return false;
    } else if (t_operation == "lu") {
        listAllUsers();
        return true;
    } else if (t_operation == "cm") {
        createMeeting();
        return true;
    } else if (t_operation == "la") {
        listAllMeetings();
        return true;
    } else if (t_operation == "las") {
        listAllSponsorMeetings();
        return true;
    } else if (t_operation == "lap") {
        listAllParticipateMeetings();
        return true;
    } else if (t_operation == "qm") {
        queryMeetingByTitle();
        return true;
    } else if (t_operation == "qt") {
        queryMeetingByTimeInterval();
        return true;
    } else if (t_operation == "dm") {
        deleteMeetingByTitle();
        return true;
    } else if (t_operation == "da") {
        deleteAllMeetings();
        return true;
    } else {
        return false;
    }
}

/**
 * user Login
 */
void AgendaUI::userLogIn(void) {
    std::string username, password;
    std::cout << "\n[log in] [username] [password]\n";
    std::cout << "[log in] ";
    std::cin >> username >> password;
    if (!m_agendaService.userLogIn(username, password)) {
        std::cout << "[error] log in fail!\n";
        return;
    }
    m_userName = username;
    m_userPassword = password;
    std::cout << "o   - log out Agenda\n";
    std::cout << "dc  - delete Agenda account\n";
    std::cout << "lu  - list all Agenda user\n";
    std::cout << "cm  - creat a meeting\n";
    std::cout << "la  - list all meetings\n";
    std::cout << "las - list all sponsor meetings\n";
    std::cout << "lap - list all participate meetings\n";
    std::cout << "qm  - query meetings by title\n";
    std::cout << "qt  - query meetings by time interval\n";
    std::cout << "dm  - delete meetings by title\n";
    std::cout << "da  - delete all meetings\n";
    std::cout << "----------------------------------------------------------\n";
    auto isValid = [](std::string operation) {
        if (operation != "o" && operation != "dc" && operation != "lu"
            && operation != "cm" && operation != "la" && operation != "las"
            && operation != "lap" && operation != "qm" && operation != "qt"
            && operation != "dm" && operation != "da" && operation != "help")
            return false;
        else
            return true;
    };
    while (true) {
        std::string temp("\nAgenda@" + m_userName + ": # ");
        std::cout << temp;
        std::string t_operation = getOperation();
        while (!isValid(t_operation)) {
            std::cout << "Operation not found!\n";
            std::cout << temp;
            t_operation = getOperation();
        }
        if (!executeOperation(t_operation))
            break;
    }
}

/**
 * user regist
 */
void AgendaUI::userRegister(void) {
    std::cout << "\n[register] [user name] [password] [email] [phone]\n[register] ";
    std::string information;
    std::string username, password, email, phone;
	std::cin.get();
    std::getline(std::cin, information);
    char *temp = new char[information.size() + 1];
    strcpy(temp, information.c_str());
    username = std::strtok(temp, " ");
    password = std::strtok(NULL, " ");
    email = std::strtok(NULL, " ");
    phone = std::strtok(NULL, " ");
    delete[] temp;
    if (username == "" || password == "" || email == "" || phone == "") {
        std::cout << "[error] register fail!\n";
    } else {
        if (m_agendaService.userRegister(username, password, email, phone)) {
            std::cout << "[register] succeed!\n";
        } else {
            std::cout << "[error] register fail!\n";
        }
    }
}

/**
 * quit the Agenda
 */
void AgendaUI::quitAgenda(void) { m_agendaService.quitAgenda(); }

/**
 * user logout
 */
void AgendaUI::userLogOut(void) { }

/**
 * delete a user from storage
 */
void AgendaUI::deleteUser(void) {
    if (m_agendaService.deleteUser(m_userName, m_userPassword))
        std::cout << "\n[delete agenda account] succeed!\n";
	else
        std::cout << "\n[error] delete fail!\n";
}

/**
 * list all users from storage
 */
void AgendaUI::listAllUsers(void) {
    std::cout << "\n[list all users]\n\n";
	std::cout.setf(std::ios::left);
	std::cout << std::setw(16) << "name" << std::setw(16) << "email" << "phone\n";
	std::list<User> t_list = m_agendaService.listAllUsers();
	for (auto object : t_list) {
        std::cout << std::setw(16) << object.getName()
                  << std::setw(16) << object.getEmail()
                  << std::setw(16) << object.getPhone() << std::endl;
    }
}

/**
 * user create a meeting with someone else
 */
void AgendaUI::createMeeting(void) {
    std::cout << "\n[create meeting] [the number of participators]\n"
              << "[create meeting] ";
    std::vector<std::string> t_participators;
    int number_of_participators;
    std::cin >> number_of_participators;
    for (int i = 0; i < number_of_participators; i++) {
        std::cout << "[create meeting] [please enter the participator "
                  << i + 1 << " ]";
        std::cout << "\n[create meeting] ";
        std::string name;
        std::cin >> name;
        t_participators.push_back(name);
    }
    std::cout << "[create meeting] [title] "
              << "[start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]";
    std::cout << "\n[create meeting] ";
    std::string t_title, t_startTime, t_endTime;
    std::cin >> t_title >> t_startTime >> t_endTime;
    if (m_agendaService.createMeeting(m_userName, t_title,
                                      t_startTime, t_endTime, t_participators))
        std::cout << "[create meeting] succeed!\n";
    else
        std::cout << "[create meeting] error!\n";
}

/**
 * list all meetings from storage
 */
void AgendaUI::listAllMeetings(void) {
    std::cout << "\n[list all meetings]\n\n";
	std::cout.setf(std::ios::left);
	printMeetings(m_agendaService.listAllMeetings(m_userName));
}

/**
 * list all meetings that this user sponsored
 */
void AgendaUI::listAllSponsorMeetings(void) {
    std::cout << "\n[list all sponsor meetings]\n\n";
	std::cout.setf(std::ios::left);
    printMeetings(m_agendaService.listAllSponsorMeetings(m_userName));
}

/**
 * list all meetings that this user take part in
 */
void AgendaUI::listAllParticipateMeetings(void) {
    std::cout << "\n[list all participate meetings]\n\n";
	std::cout.setf(std::ios::left);
    printMeetings(m_agendaService.listAllParticipateMeetings(m_userName));
}

/**
 * search meetings by title from storage
 */
void AgendaUI::queryMeetingByTitle(void) {
    std::cout << "\n[list all meeting meetings] [title]:\n[list all meeting meetings] ";
	std::string title;
	std::cin >> title;
	std::cout.setf(std::ios::left);
    printMeetings(m_agendaService.meetingQuery(m_userName, title));
}

/**
 * search meetings by timeinterval from storage
 */
void AgendaUI::queryMeetingByTimeInterval(void) {
    std::cout << "\n[query meetings] [start time(yyyy-mm-dd/hh:mm)]"
              << "[end time(yyyy-mm-dd/hh:mm)]\n[query meetings] ";
    std::string start_time, end_time;
    std::cin >> start_time >> end_time;
    if (!Date::isValid(Date::stringToDate(start_time))
        || !Date::isValid(Date::stringToDate(end_time)))
        std::cout << "\n[error] query meetings fail!\n";
    else
        printMeetings(m_agendaService.meetingQuery(m_userName,
                                                   start_time, end_time));
}

/**
 * delete meetings by title from storage
 */
void AgendaUI::deleteMeetingByTitle(void) {
    std::cout << "\n[delete meeting] [title]\n[delete meeting] ";
	std::string title;
	std::cin >> title;
	if (m_agendaService.deleteMeeting(m_userName, title))
		std::cout << "\n[delete meeting by title] succeed!";
	else
        std::cout << "\n[error] delete meeting fail!\n";
}

/**
 * delete all meetings that this user sponsored
 */
void AgendaUI::deleteAllMeetings(void) {
    m_agendaService.deleteAllMeetings(m_userName);
	std::cout << "\n[delete all meetings] succeed!\n";
}

/**
 * show the meetings in the screen
 */
void AgendaUI::printMeetings(std::list<Meeting> t_meetings) {
    std::cout << std::endl;
	std::cout.setf(std::ios::left);
	std::cout << std::setw(16) << "title" << std::setw(16) << "sponsor";
	std::cout << std::setw(18) << "start time" << std::setw(18) << "end time";
    std::cout << std::setw(16) << "participator";
    std::cout << std::endl;
	for (auto object : t_meetings) {
        std::cout.setf(std::ios::left);
		std::cout << std::left << std::setw(16) << object.getTitle()
                  << std::setw(16) << object.getSponsor();
		std::cout << std::setw(18) << Date::dateToString(object.getStartDate())
                  << std::setw(18) << Date::dateToString(object.getEndDate());
        std::vector<std::string> t_vec = object.getParticipator();
        for (std::size_t i = 0; i < t_vec.size(); i++) {
            std::cout << t_vec[i];
            if (i == t_vec.size() - 1)
                break;
            std::cout << ',';
        }
        std::cout << std::endl;
	}
    std::cout << std::endl;
}
