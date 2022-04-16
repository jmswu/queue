#include "gtest/gtest.h"
#include "../third-party/fff/fff.h"
#include "queue.h"

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

    TEST_F(QueueTest, queueObj_nullShouldReturnFalse)
    {
        queue_obj_t *obj = NULL;
        ASSERT_FALSE(queue_helper_isObjValid(obj));
    }
}
