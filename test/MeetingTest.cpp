#include "Meeting.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

TEST(MeetingTest, SetAndGet) {
  Meeting meeting;
  meeting.setSponsor("Clown");
  EXPECT_STREQ("Clown", meeting.getSponsor().c_str());
  std::vector<std::string> vec;
  for (int i = 0; i < 100; i++) {
    char ch = i + '0';
    std::string temp = "participator";
    temp += ch;
    vec.push_back(temp);
  }
  meeting.setParticipator(vec);
  EXPECT_EQ(vec, meeting.getParticipator());
  Date t_start = Date::stringToDate("2016-8-19/00:00");
  meeting.setStartDate(t_start);
  EXPECT_EQ(t_start, meeting.getStartDate());
  Date t_end = Date::stringToDate("2016-8-23/23:59");
  meeting.setEndDate(t_end);
  EXPECT_EQ(t_end, meeting.getEndDate());
  meeting.setTitle("Boring");
  EXPECT_STREQ("Boring", meeting.getTitle().c_str());
}
