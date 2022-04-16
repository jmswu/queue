#include "gtest/gtest.h"
#include "../third-party/fff/fff.h"

namespace 
{
    class DummyTest : public::testing::Test
    {
    public:
    private:
        
    protected:
        DummyTest(){}

        virtual void SetUp()
        {

        }

        virtual void TearDown()
        {

        }
    };

    // testing CPP code
    TEST_F(DummyTest, pass)
    {
        ASSERT_TRUE(true);
    }
}
