#include <assert.h>
#include "gtest/gtest.h"
#include "../third-party/fff/fff.h"
#include "queue.h"

struct TestQueueObj
{
    TestQueueObj(std::string str, const size_t buffer_size)
    {
        assert(str.length() < buffer_size);

        buffer = (char *)malloc(buffer_size);
        std::sprintf(buffer, "%s", str.c_str());
        obj = {
            .ptrData = (void *)buffer,
            .len = buffer_size};
    }

    queue_obj_t getTestQueueObj()
    {
        return obj;
    }

    ~TestQueueObj()
    {
        free(buffer);
    }

private:
    char *buffer;
    queue_obj_t obj;
};

queue_obj_t helper_createTestQueueObj(const char *str, const size_t buffer_len)
{

    assert(str != NULL);

    char *buffer = (char *)malloc(buffer_len);
    sprintf(buffer, "%s", str);
    queue_obj_t obj = {
        .ptrData = (void *)buffer,
        .len = buffer_len};
    return obj;
}

void helper_freeTestQueueObj(queue_obj_t *const obj)
{
    assert(obj != NULL);
    free(obj->ptrData);
}

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

    TEST_F(QueueTest, pushDataShouldEquelPopData)
    {
        // create obj
        const int BUFF_SIZE = 32;
        TestQueueObj testObj{"Hello world", BUFF_SIZE};
        queue_obj_t push_obj = testObj.getTestQueueObj();

        // push and pop data
        queue_pushBack(handle, &push_obj);
        queue_obj_t pop_obj = queue_pop(handle);

        // test the data are the same
        ASSERT_EQ(BUFF_SIZE, pop_obj.len);
        ASSERT_EQ(0, memcmp(&push_obj, &pop_obj, sizeof(queue_obj_t)));
        ASSERT_EQ(0, memcmp(push_obj.ptrData, pop_obj.ptrData, BUFF_SIZE));
    }
}
