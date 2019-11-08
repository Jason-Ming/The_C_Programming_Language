#include "CppUTest/TestHarness.h"
#include <string.h>
#include "s_type.h"
#include "s_mem.h"
#include "s_print.h"
#include "s_cproc.h"
#include <iostream>

using namespace std;

TEST_GROUP(S_CC)
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

TEST(S_CC, test0)
{
    //s_print_types();
    const _S8 *file_name[] = {
        //"test_files/func.input",
        "test_files/i.input",
        //"test_files/s.input",
        //"test_files/main.input"};
        //,
        //"test_files/s.input"
        };
    ENUM_RETURN ret_val;
    for(size_t i = 0; i < SIZE_OF_ARRAY(file_name); i++)
    {
        ret_val = s_cc(file_name[i], NULL, NULL);
        CHECK_EQUAL(RETURN_SUCCESS, ret_val);
    }
}

