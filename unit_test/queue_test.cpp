#include "gtest/gtest.h"
#include "../third-party/fff/fff.h"

namespace 
{
    class QueueTest : public::testing::Test
    {
    public:
    private:
        
    protected:
        QueueTest(){}

        virtual void SetUp()
        {

        }

        virtual void TearDown()
        {

        }
    };

    TEST_F(QueueTest, pass)
    {
        ASSERT_TRUE(true);
    }
}
