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
        queue_handle_t handle = NULL;
        QueueTest() {}

        virtual void SetUp()
        {
            handle = queue_create();
        }

        virtual void TearDown()
        {
            queue_destroy(handle);
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

    TEST_F(QueueTest, handleShouldNotBeNull)
    {
        // if creater and destroy is working
        // handle should not be NULL
        ASSERT_NE(handle, (queue_handle_t)NULL);
    }
}
