#include "AgendaService.hpp"

/**
* constructor
*/
AgendaService::AgendaService() {}

/**
* destructor
*/
AgendaService::~AgendaService() {}

/**
* check if the username match password
* @param userName the username want to login
* @param password the password user enter
* @return if success, true will be returned
*/
bool AgendaService::userLogIn(const std::string userName,
                              const std::string password) {
  auto t_filter = [&](const User &t_user) {
    return t_user.getName() == userName;
  };
  std::list<User> t_list = m_storage->queryUser(t_filter);
  /**
  * If the user does not exist, it fails.
  */
  if (t_list.empty())
    return false;
  else
    return t_list.front().getPassword() == password;
}

/**
* regist a user
* @param userName new user's username
* @param password new user's password
* @param email new user's email
* @param phone new user's phone
* @return if success, true will be returned
*/
bool AgendaService::userRegister(const std::string userName,
                                 const std::string password,
                                 const std::string email,
                                 const std::string phone) {
  auto t_filter = [&](const User &t_user) {
    return t_user.getName() == userName;
  };
  std::list<User> t_list = m_storage->queryUser(t_filter);
  /**
  * If the user exists, it fails.
  */
  if (t_list.empty()) {
    m_storage->createUser(User(userName, password, email, phone));
    return true;
  } else {
    return false;
  }
}

/**
* delete a user
* @param userName user's username
* @param password user's password
* @return if success, true will be returned
*/
bool AgendaService::deleteUser(const std::string userName,
                               const std::string password) {
  auto t_filter_1 = [&](const User &t_user) {
    return t_user.getName() == userName;
  };
  /**
  * To get all meetings the user taken part in.
  */
  auto t_filter_2 = [&](const Meeting &t_meeting) {
    return t_meeting.getSponsor() == userName ||
           t_meeting.isParticipator(userName);
  };
  /**
  * Delete all meetings the user taken part in.
  */
  m_storage->deleteMeeting(t_filter_2);
  if (m_storage->deleteUser(t_filter_1) != 0)
    return true;
  else
    return false;
}

/**
* list all users from storage
* @return a user list result
*/
std::list<User> AgendaService::listAllUsers(void) const {
  auto t_filter = [&](const User &t_user) { return true; };
  return m_storage->queryUser(t_filter);
}

/**
* create a meeting
* @param userName the sponsor's userName
* @param title the meeting's title
* @param participator the meeting's participator
* @param startData the meeting's start date
* @param endData the meeting's end date
* @return if success, true will be returned
*/
bool AgendaService::createMeeting(const std::string userName,
                                  const std::string title,
                                  const std::string startDate,
                                  const std::string endDate,
                                  const std::vector<std::string> participator) {
  auto t_filter_1 = [&](const User &t_user) {
    return t_user.getName() == userName;
  };
  /**
  * If the user does not exist, it fails.
  */
  if (m_storage->queryUser(t_filter_1).empty())
    return false;

  auto t_filter_2 = [&](const Meeting &t_meeting) {
    return t_meeting.getTitle() == title;
  };
  /**
  * If there exists a title conflict, it fails.
  */
  if (!m_storage->queryMeeting(t_filter_2).empty())
    return false;

  Date t_start = Date::stringToDate(startDate);
  Date t_end = Date::stringToDate(endDate);
  /**
  * If any of the two dates is invalid
  * or start date is greater than end date, it fails.
  */
  if (!Date::isValid(t_start) || !Date::isValid(t_end) || t_start >= t_end)
    return false;
  auto t_filter_3 = [&](const Meeting &t_meeting) {
    return t_meeting.getSponsor() == userName ||
           t_meeting.isParticipator(userName);
  };
  /**
  * If there exists time conflict, it fails.
  */
  for (auto object : m_storage->queryMeeting(t_filter_3)) {
    if (t_start >= object.getStartDate() && t_start < object.getEndDate())
      return false;
    if (t_end > object.getStartDate() && t_end <= object.getEndDate())
      return false;
    if (t_start >= object.getStartDate() && t_end <= object.getEndDate())
      return false;
    if (t_start <= object.getStartDate() && t_end >= object.getEndDate())
      return false;
  }
  m_storage->createMeeting(
      Meeting(userName, participator, t_start, t_end, title));
  return true;
}

/**
* search a meeting by username and title
* @param uesrName the sponsor's userName
* @param title the meeting's title
* @return a meeting list result
*/
std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                               const std::string title) const {
  auto t_filter = [&](const Meeting &t_meeting) {
    return t_meeting.getSponsor() == userName && t_meeting.getTitle() == title;
  };
  return m_storage->queryMeeting(t_filter);
}

/**
* search a meeting by username, time interval
* @param uesrName the sponsor's userName
* @param startDate time interval's start date
* @param endDate time interval's end date
* @return a meeting list result
*/
std::list<Meeting>
AgendaService::meetingQuery(const std::string userName,
                            const std::string startDate,
                            const std::string endDate) const {
  Date t_start = Date::stringToDate(startDate);
  Date t_end = Date::stringToDate(endDate);
  if (!Date::isValid(t_start) || !Date::isValid(t_end) || t_start >= t_end)
    return std::list<Meeting>();
  auto t_filter = [&](const Meeting &t_meeting) {
    return t_meeting.getSponsor() == userName &&
           (t_meeting.getStartDate() >= t_start &&
            t_meeting.getEndDate() <= t_end);
  };
  return m_storage->queryMeeting(t_filter);
}

/**
* list all meetings the user take part in
* @param userName user's username
* @return a meeting list result
*/
std::list<Meeting>
AgendaService::listAllMeetings(const std::string userName) const {
  auto t_filter = [&](const Meeting &t_meeting) {
    return t_meeting.getSponsor() == userName ||
           t_meeting.isParticipator(userName);
  };
  return m_storage->queryMeeting(t_filter);
}

/**
* list all meetings the user sponsor
* @param userName user's username
* @return a meeting list result
*/
std::list<Meeting>
AgendaService::listAllSponsorMeetings(const std::string userName) const {
  auto t_filter = [&](const Meeting &t_meeting) {
    return t_meeting.getSponsor() == userName;
  };
  return m_storage->queryMeeting(t_filter);
}

/**
* list all meetings the user take part in and sponsor by other
* @param userName user's username
* @return a meeting list result
*/
std::list<Meeting>
AgendaService::listAllParticipateMeetings(const std::string userName) const {
  auto t_filter = [&](const Meeting &t_meeting) {
    return t_meeting.getSponsor() != userName &&
           t_meeting.isParticipator(userName);
  };
  return m_storage->queryMeeting(t_filter);
}

/**
* delete a meeting by title and its sponsor
* @param userName sponsor's username
* @param title meeting's title
* @return if success, true will be returned
*/
bool AgendaService::deleteMeeting(const std::string userName,
                                  const std::string title) {
  auto t_filter = [&](const Meeting &t_meeting) {
    return t_meeting.getSponsor() == userName && t_meeting.getTitle() == title;
  };
  return m_storage->deleteMeeting(t_filter);
}

/**
* delete all meetings by sponsor
* @param userName sponsor's username
* @return if success, true will be returned
*/
bool AgendaService::deleteAllMeetings(const std::string userName) {
  auto t_filter = [&](const Meeting &t_meeting) {
    return t_meeting.getSponsor() == userName;
  };
  return m_storage->deleteMeeting(t_filter);
}

/**
* start Agenda service and connect to storage
*/
void AgendaService::startAgenda(void) { m_storage = Storage::getInstance(); }

/**
* quit Agenda service
*/
void AgendaService::quitAgenda(void) { m_storage->sync(); }
