#include "gtest/gtest.h"
#include "../third-party/fff/fff.h"
#include "queue.h"

namespace
{
    class QueueTest : public ::testing::Test
    {
    public:
    private:
    protected:
        QueueTest() {}

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

    TEST_F(QueueTest, queueObj_nullObjShouldReturnFalse)
    {
        ASSERT_FALSE(queue_helper_isObjValid(NULL));
    }

    TEST_F(QueueTest, queueObj_zeroLengthShouldReturnFalse)
    {
        int data = 0;
        queue_obj_t obj = {
            .ptrData = &data,
            .len = 0};
        ASSERT_FALSE(queue_helper_isObjValid(&obj));
    }

    TEST_F(QueueTest, queueObj_nullDataPtrShouldReturnFalse)
    {
        queue_obj_t obj = {
            .ptrData = NULL,
            .len = 1};
        ASSERT_FALSE(queue_helper_isObjValid(&obj));
    }
}
