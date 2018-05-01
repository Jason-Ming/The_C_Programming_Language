#include "CppUTest/TestHarness.h"
#include "1_5_4.h"

#include <iostream>

using namespace std;

TEST_GROUP(CALCULATE_WORDS)
{
    void setup()
    {
    	//设置自己的测试准备
        //cout << "Test start ......" << endl;
    }

    void teardown()
    {
    	//清理测试设置
        //cout << "Test end ......" << endl;
    }
};

TEST(CALCULATE_WORDS, test0)
{
   CHECK_EQUAL(calculate_words("test0"), 0);
}

TEST(CALCULATE_WORDS, test1)
{
   CHECK_EQUAL(calculate_words("test1"), 1);
}

TEST(CALCULATE_WORDS, test2)
{
   CHECK_EQUAL(calculate_words("test2"), 0);
}

TEST(CALCULATE_WORDS, test3)
{
   CHECK_EQUAL(calculate_words("test3"), 0);
}

TEST(CALCULATE_WORDS, test4)
{
   CHECK_EQUAL(calculate_words("test4"), 2);
}

TEST(CALCULATE_WORDS, test5)
{
   CHECK_EQUAL(calculate_words("test5"), 66000);
}

TEST(CALCULATE_WORDS, test6)
{
   CHECK_EQUAL(calculate_words("test6"), 66000);
}

