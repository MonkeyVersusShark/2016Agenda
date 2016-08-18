#include "Date.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(DateTest, isValid) {
    Date date1(2015, 8, 19, 20, 10);
    Date date2(2016, 2, 30, 1, 12);
    EXPECT_TRUE(Date::isValid(date1));
    EXPECT_FALSE(Date::isValid(date2));
}

TEST(DateTest, overloadedOperator) {
    Date blankDate;
    Date date1(2015, 8, 19, 20, 10);
    Date date2(2016, 2, 30, 1, 12);
    Date date3(2016, 7, 19, 9, 1);
    Date date4(date3);
    Date date5(1984, 3, 20, 1, 59);
    EXPECT_EQ(blankDate, Date::stringToDate("16-08-19/00:00"));
    EXPECT_EQ(date3, date4);
    EXPECT_LT(date1, date4);
    EXPECT_LE(date1, date4);
    EXPECT_LE(date3, date4);
    EXPECT_GT(date3, date5);
    EXPECT_GE(date3, date5);
    EXPECT_GE(date3, date4);
}

TEST(DateTest, dateToString) {
    Date date(2016, 7, 19, 9, 1);
    EXPECT_STREQ("2016-07-19/09:01", Date::dateToString(date).c_str());
}

TEST(DateTest, stringToDate) {
    Date date(1984, 3, 20, 1, 59);
    EXPECT_EQ(date, Date::stringToDate("1984-03-20/01:59"));
}
