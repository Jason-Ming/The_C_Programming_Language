#include "CppUTest/TestHarness.h"
#include <string.h>
#include "s_text.h"
#include "s_type.h"
#include <iostream>

using namespace std;

TEST_GROUP(TEXT)
{
    void setup()
    {
    	//�����Լ��Ĳ���׼��
        //cout << "Test start ......" << endl;
    }

    void teardown()
    {
    	//�����������
        //cout << "Test end ......" << endl;
    }
};

TEST(TEXT, test0)
{
    _S8 s1[] = "abcd 123";
    _S8 s2[] = "cd 1";
    _S8 s[] = "ab23";
    squeeze(s1, s2);
    CHECK_EQUAL(strcmp(s1, s), 0);
}

TEST(TEXT, test1)
{
    _S8 s1[] = "abcd 123";
    _S8 s2[] = "cd 1";
    _S8 s[] = "cd 123";
    _S8 *p = any(s1, s2);
    CHECK_EQUAL(strcmp(p, s), 0);
}

