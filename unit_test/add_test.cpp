#include "gtest/gtest.h"
#include "../third-party/fff/fff.h"
#include "add.hpp"
#include "add.h"

DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC(int, cb_operation, int, int);

namespace 
{
    class AddTest : public::testing::Test
    {
    public:
    private:
        
    protected:
        AddTest(){}

        virtual void SetUp()
        {

        }

        virtual void TearDown()
        {

        }
    };

    // testing CPP code
    TEST_F(AddTest, positiveNumber_cpp)
    {
        ASSERT_EQ(100, add(10, 90));
        ASSERT_EQ(123, add(100, 23));
    }

    // testing C code
    TEST_F(AddTest, positiveNumber_c)
    {
        ASSERT_EQ(100, add_c_code(10, 90));
        ASSERT_EQ(123, add_c_code(100, 23));
    }

    // testing C code with fake function
    TEST_F(AddTest, test_fakeFUnctionReturnValue_T1)
    {
        cb_operation_fake.return_val = 2;
        ASSERT_EQ(2, cb_operation(1, 1));
    }

    // testing C code with fake function 
    TEST_F(AddTest, test_fakeFUnctionReturnValue_T2)
    {
        cb_operation_fake.return_val = 2;
        ASSERT_EQ(2, add_with_cb(1, 1, cb_operation));
    }
}
