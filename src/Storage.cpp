#include "Storage.hpp"
#include "Path.hpp"
#include <fstream>
#include <string>
#include <map>
#include <vector>

/**
 * The private part of class Storage
 */

Storage::Storage() { readFromFile(); }

/**
*   read file content into memory
*   @return if success, true will be returned
*/
bool Storage::readFromFile(void) {
    std::map<int, std::string> data;
    std::ifstream file_in;
    std::string relative_path = "../";

    /**
     * relative_path + Path::userPath is equivalent to
     * ../data/users.csv
     */
    file_in.open(relative_path + Path::userPath);

    if (!file_in.is_open())
        return false;

    for (int i = 0; !file_in.eof(); i++)
        std::getline(file_in, data[i], '\n');
    for (auto iterator = data.begin(); iterator != data.end(); ++iterator) {
        /**
         * Skip the first and last elements.
         * Because the first element is
         * "name","password","email","phone".
         * And the last element is
         * "" (nothing)
         */
        if (iterator == data.begin() || iterator == --data.end())
            continue;

        std::string t_str = iterator->second;
        int the_first_comma = t_str.find(',', 0);
        int the_second_comma = t_str.find(',', the_first_comma + 1);
        int the_third_comma = t_str.find(',', the_second_comma + 1);
        std::string name = t_str.substr(1, the_first_comma - 2);
        std::string password
        = t_str.substr(the_first_comma + 2,
          the_second_comma - the_first_comma - 3);
        std::string email
        = t_str.substr(the_second_comma + 2,
          the_third_comma - the_second_comma - 3);
        std::string phone
        = t_str.substr(the_third_comma + 2,
          t_str.size() - the_third_comma - 3);

         m_userList.push_back(User(name, password, email, phone));
    }
    file_in.close();

    file_in.clear();
    data.clear();

    /**
     * relative_path + Path::meetingPath is equivalent to
     * ../data/meetings.csv
     */
    file_in.open(relative_path + Path::meetingPath);

    if (!file_in.is_open())
        return false;

    for (int i = 0; !file_in.eof(); i++)
        std::getline(file_in, data[i], '\n');
    for (auto iterator = data.begin(); iterator != data.end(); ++iterator) {
        /**
         * Skip the first and last elements.
         * Because the first element is
         * "sponsor","participator","start date","end date","title".
         * And the last element is
         * "" (nothing)
         */
        if (iterator == data.begin() || iterator == --data.end())
            continue;

        std::string t_str = iterator->second;
        int the_first_comma = t_str.find(',', 0);
        int the_second_comma = t_str.find(',', the_first_comma + 1);
        int the_third_comma = t_str.find(',', the_second_comma + 1);
        int the_fourth_comma = t_str.find(',', the_third_comma + 1);
        std::string sponsor = t_str.substr(1, the_first_comma - 2);
        std::string participator = t_str.substr(the_first_comma + 2,
                                        the_second_comma - the_first_comma - 3);
        std::vector<std::string> all_participators;
        std::string temp = "";
        for (std::size_t i = 0; i < participator.size(); i++) {
            if (participator[i] == '&') {
                all_participators.push_back(temp);
                temp.clear();
                continue;
            }
            temp += participator[i];
            if (i == participator.size() - 1)
                all_participators.push_back(temp);
        }
        std::string startTime = t_str.substr(the_second_comma + 2,
                                        the_third_comma - the_second_comma - 3);
        std::string endTime = t_str.substr(the_third_comma + 2,
                                        the_fourth_comma - the_third_comma - 3);
        std::string title = t_str.substr(the_fourth_comma + 2,
										t_str.size() - the_fourth_comma - 3);

        m_meetingList.push_back(Meeting(sponsor, all_participators,
                                        Date::stringToDate(startTime),
                                        Date::stringToDate(endTime),
                                        title));
    }
    file_in.close();

    return true;
}

/**
*   write file content from memory
*   @return if success, true will be returned
*/
bool Storage::writeToFile(void) {
    std::ofstream file_out;
    std::string relative_path = "../";

    file_out.open(relative_path + Path::userPath);

    if (!file_out.is_open())
        return false;

    file_out << "\"name\",\"password\",\"email\",\"phone\"\n";
    for (auto object : m_userList) {
        file_out << "\"" << object.getName() << "\","
                 << "\"" << object.getPassword() << "\","
                 << "\"" << object.getEmail() << "\","
                 << "\"" << object.getPhone() << "\"\n";
    }
    file_out.close();

    file_out.clear();

    file_out.open(relative_path + Path::meetingPath);

    if (!file_out.is_open())
        return false;

    file_out << "\"sponsor\",\"participator\","
             << "\"start date\",\"end date\",\"title\"\n";
    for (auto object : m_meetingList) {
        file_out << "\"" << object.getSponsor() << "\",";
        file_out << "\"";
        std::vector<std::string> t_vec = object.getParticipator();
        for (auto iterator = t_vec.begin(); iterator != t_vec.end(); ++iterator) {
            /**
             * The variable judge labels the last element
             */
            auto judge = --t_vec.end();
            file_out << *iterator;
            if (iterator != judge)
                file_out << "&";
        }
        file_out << "\",";
        file_out << "\"" << Date::dateToString(object.getStartDate()) << "\","
                 << "\"" << Date::dateToString(object.getEndDate()) << "\","
                 << "\"" << object.getTitle() << "\"\n";
    }
    file_out.close();

    return true;
}

std::shared_ptr<Storage> Storage::m_instance(nullptr);

/**
* get Instance of storage
* @return the pointer of the instance
*/
std::shared_ptr<Storage> Storage::getInstance(void) {
    if (m_instance == nullptr)
        m_instance = std::shared_ptr<Storage>(new Storage);
    return m_instance;
}

/**
*   destructor
*   Destroy the instance.
*/
Storage::~Storage() { m_instance = std::shared_ptr<Storage>(nullptr); }

// CRUD for User & Meeting
// using C++11 Function Template and Lambda Expressions

/**
* create a user
* @param a user object
*/
void Storage::createUser(const User &t_user) { m_userList.push_back(t_user); }

/**
* query users
* @param a lambda function as the filter
* @return a list of fitted users
*/
std::list<User> Storage::queryUser(
                            std::function<bool(const User &)> filter) const {
    std::list<User> users_found;
    for (auto object : m_userList) {
        if (filter(object))
            users_found.push_back(object);
    }
    return users_found;
}

/**
* update users
* @param a lambda function as the filter
* @param a lambda function as the method to update the user
* @return the number of updated users
*/
int Storage::updateUser(std::function<bool(const User &)> filter,
                        std::function<void(User &)> switcher) {
    int counter = 0;
    for (auto object : m_userList) {
        if (filter(object)) {
            switcher(object);
            ++counter;
        }
    }
    return counter;
}

/**
* delete users
* @param a lambda function as the filter
* @return the number of deleted users
*/
int Storage::deleteUser(std::function<bool(const User &)> filter) {
    int counter = 0;
    auto iterator = m_userList.begin();
    while (iterator != m_userList.end()) {
        if (filter(*iterator)) {
            iterator = m_userList.erase(iterator);
            ++counter;
        } else {
            ++iterator;
        }
    }
    return counter;
}

/**
* create a meeting
* @param a meeting object
*/
void Storage::createMeeting(const Meeting &t_meeting) {
    m_meetingList.push_back(t_meeting);
}

/**
* query meetings
* @param a lambda function as the filter
* @return a list of fitted meetings
*/
std::list<Meeting> Storage::queryMeeting(
                        std::function<bool(const Meeting &)> filter) const {
    std::list<Meeting> meetings_found;
    for (auto object : m_meetingList) {
        if (filter(object))
            meetings_found.push_back(object);
    }
    return meetings_found;
}

/**
* update meetings
* @param a lambda function as the filter
* @param a lambda function as the method to update the meeting
* @return the number of updated meetings
*/
int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                           std::function<void(Meeting &)> switcher) {
    int counter = 0;
    for (auto object : m_meetingList) {
        if (filter(object)) {
            switcher(object);
            ++counter;
        }
    }
    return counter;
}

/**
* update meetings
* @param a lambda function as the filter
* @return the number of deleted meetings
*/
int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
    int counter = 0;
    auto iterator = m_meetingList.begin();
    while (iterator != m_meetingList.end()) {
        if (filter(*iterator)) {
            iterator = m_meetingList.erase(iterator);
            ++counter;
        } else {
            ++iterator;
        }
    }
    return counter;
}

/**
* sync with the file
*/
bool Storage::sync(void) { return writeToFile(); }
