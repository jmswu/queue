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

    TEST_F(QueueTest, popAnEmptyQueueShouldReturnNull)
    {
        queue_obj_t pop_obj = queue_pop(handle);
        ASSERT_EQ(0, pop_obj.len);
        ASSERT_EQ(NULL, pop_obj.ptrData);
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

    TEST_F(QueueTest, pushOneAndPopTwo_secondOneShouldBeNull)
    {
        // create obj
        const int BUFF_SIZE = 32;
        TestQueueObj testObj{"Hello world", BUFF_SIZE};
        queue_obj_t push_obj = testObj.getTestQueueObj();

        // push and pop data
        queue_pushBack(handle, &push_obj);
        queue_obj_t pop_obj_1 = queue_pop(handle);
        queue_obj_t pop_obj_2 = queue_pop(handle);

        // test the data are the same
        ASSERT_EQ(BUFF_SIZE, pop_obj_1.len);
        ASSERT_EQ(0, memcmp(&push_obj, &pop_obj_1, sizeof(queue_obj_t)));
        ASSERT_EQ(0, memcmp(push_obj.ptrData, pop_obj_1.ptrData, BUFF_SIZE));

        // second one should be NULL
        ASSERT_EQ(0, pop_obj_2.len);
        ASSERT_EQ(NULL, pop_obj_2.ptrData);
    }

    TEST_F(QueueTest, pushOneAndPopThree_secondAndThridOneShouldBeNull)
    {
        // create obj
        const int BUFF_SIZE = 32;
        TestQueueObj testObj{"Hello world", BUFF_SIZE};
        queue_obj_t push_obj = testObj.getTestQueueObj();

        // push and pop data
        queue_pushBack(handle, &push_obj);
        queue_obj_t pop_obj_1 = queue_pop(handle);
        queue_obj_t pop_obj_2 = queue_pop(handle);
        queue_obj_t pop_obj_3 = queue_pop(handle);

        // test the data are the same
        ASSERT_EQ(BUFF_SIZE, pop_obj_1.len);
        ASSERT_EQ(0, memcmp(&push_obj, &pop_obj_1, sizeof(queue_obj_t)));
        ASSERT_EQ(0, memcmp(push_obj.ptrData, pop_obj_1.ptrData, BUFF_SIZE));

        // second and thrid should be NULL
        ASSERT_EQ(0, pop_obj_2.len);
        ASSERT_EQ(NULL, pop_obj_2.ptrData);

        ASSERT_EQ(0, pop_obj_3.len);
        ASSERT_EQ(NULL, pop_obj_3.ptrData);
    }

    TEST_F(QueueTest, pushTwoAndPopThree_thridOneShouldBeNull)
    {
        // create obj
        const int BUFF_SIZE = 32;
        TestQueueObj testObj{"Hello world", BUFF_SIZE};
        queue_obj_t push_obj = testObj.getTestQueueObj();

        // push and pop data
        queue_pushBack(handle, &push_obj);
        queue_obj_t pop_obj_1 = queue_pop(handle);
        queue_obj_t pop_obj_2 = queue_pop(handle);
        queue_obj_t pop_obj_3 = queue_pop(handle);

        // test the data are the same
        ASSERT_EQ(BUFF_SIZE, pop_obj_1.len);
        ASSERT_EQ(0, memcmp(&push_obj, &pop_obj_1, sizeof(queue_obj_t)));
        ASSERT_EQ(0, memcmp(push_obj.ptrData, pop_obj_1.ptrData, BUFF_SIZE));

        // second and thrid should be NULL
        ASSERT_EQ(0, pop_obj_2.len);
        ASSERT_EQ(NULL, pop_obj_2.ptrData);

        ASSERT_EQ(0, pop_obj_3.len);
        ASSERT_EQ(NULL, pop_obj_3.ptrData);
    }

    TEST_F(QueueTest, pushDataShouldEquelPopDataTwoObjs)
    {
        // create obj
        const int BUFF_SIZE_1 = 32;
        const int BUFF_SIZE_2 = 64;
        TestQueueObj testObj_1{"1.Hello world one", BUFF_SIZE_1};
        TestQueueObj testObj_2{"2.Hello world two", BUFF_SIZE_2};
        queue_obj_t push_obj_1 = testObj_1.getTestQueueObj();
        queue_obj_t push_obj_2 = testObj_2.getTestQueueObj();

        // push and pop data
        queue_pushBack(handle, &push_obj_1);
        queue_pushBack(handle, &push_obj_2);
        queue_obj_t pop_obj_1 = queue_pop(handle);
        queue_obj_t pop_obj_2 = queue_pop(handle);

        // test the data are the same
        ASSERT_EQ(BUFF_SIZE_1, pop_obj_1.len);
        ASSERT_EQ(0, memcmp(&push_obj_1, &pop_obj_1, sizeof(queue_obj_t)));
        ASSERT_EQ(0, memcmp(push_obj_1.ptrData, pop_obj_1.ptrData, BUFF_SIZE_1));

        ASSERT_EQ(BUFF_SIZE_2, pop_obj_2.len);
        ASSERT_EQ(0, memcmp(&push_obj_2, &pop_obj_2, sizeof(queue_obj_t)));
        ASSERT_EQ(0, memcmp(push_obj_2.ptrData, pop_obj_2.ptrData, BUFF_SIZE_1));
    }

    TEST_F(QueueTest, pushDataShouldEquelPopDataThreeObjs)
    {
        // create obj
        const int BUFF_SIZE_1 = 32;
        const int BUFF_SIZE_2 = 64;
        const int BUFF_SIZE_3 = 64;
        TestQueueObj testObj_1{"1.Hello world one", BUFF_SIZE_1};
        TestQueueObj testObj_2{"2.Hello world two", BUFF_SIZE_2};
        TestQueueObj testObj_3{"3.Hello world three", BUFF_SIZE_3};
        queue_obj_t push_obj_1 = testObj_1.getTestQueueObj();
        queue_obj_t push_obj_2 = testObj_2.getTestQueueObj();
        queue_obj_t push_obj_3 = testObj_3.getTestQueueObj();

        // push and pop data
        queue_pushBack(handle, &push_obj_1);
        queue_pushBack(handle, &push_obj_2);
        queue_pushBack(handle, &push_obj_3);
        queue_obj_t pop_obj_1 = queue_pop(handle);
        queue_obj_t pop_obj_2 = queue_pop(handle);
        queue_obj_t pop_obj_3 = queue_pop(handle);

        // test the data are the same
        ASSERT_EQ(BUFF_SIZE_1, pop_obj_1.len);
        ASSERT_EQ(0, memcmp(&push_obj_1, &pop_obj_1, sizeof(queue_obj_t)));
        ASSERT_EQ(0, memcmp(push_obj_1.ptrData, pop_obj_1.ptrData, BUFF_SIZE_1));

        ASSERT_EQ(BUFF_SIZE_2, pop_obj_2.len);
        ASSERT_EQ(0, memcmp(&push_obj_2, &pop_obj_2, sizeof(queue_obj_t)));
        ASSERT_EQ(0, memcmp(push_obj_2.ptrData, pop_obj_2.ptrData, BUFF_SIZE_2));

        ASSERT_EQ(BUFF_SIZE_3, pop_obj_3.len);
        ASSERT_EQ(0, memcmp(&push_obj_3, &pop_obj_3, sizeof(queue_obj_t)));
        ASSERT_EQ(0, memcmp(push_obj_3.ptrData, pop_obj_3.ptrData, BUFF_SIZE_3));
    }

    TEST_F(QueueTest, itemCountShouldBeZero)
    {
        ASSERT_EQ(0, queue_getItemCount(handle));
    }

    TEST_F(QueueTest, itemCountShouldBeOne)
    {
        // create obj
        const int BUFF_SIZE_1 = 32;
        TestQueueObj testObj_1{"1.Hello world one", BUFF_SIZE_1};
        queue_obj_t push_obj_1 = testObj_1.getTestQueueObj();

        queue_pushBack(handle, &push_obj_1);

        ASSERT_EQ(1, queue_getItemCount(handle));
    }

    TEST_F(QueueTest, itemCountShouldBeTwo)
    {
        // create obj
        const int BUFF_SIZE_1 = 32;
        const int BUFF_SIZE_2 = 64;
        TestQueueObj testObj_1{"1.Hello world one", BUFF_SIZE_1};
        TestQueueObj testObj_2{"2.Hello world two", BUFF_SIZE_2};
        queue_obj_t push_obj_1 = testObj_1.getTestQueueObj();
        queue_obj_t push_obj_2 = testObj_2.getTestQueueObj();

        queue_pushBack(handle, &push_obj_1);
        queue_pushBack(handle, &push_obj_2);

        ASSERT_EQ(2, queue_getItemCount(handle));
    }

    TEST_F(QueueTest, itemCountShouldBeThree)
    {
        // create obj
        const int BUFF_SIZE_1 = 32;
        const int BUFF_SIZE_2 = 64;
        const int BUFF_SIZE_3 = 64;
        TestQueueObj testObj_1{"1.Hello world one", BUFF_SIZE_1};
        TestQueueObj testObj_2{"2.Hello world two", BUFF_SIZE_2};
        TestQueueObj testObj_3{"3.Hello world three", BUFF_SIZE_3};
        queue_obj_t push_obj_1 = testObj_1.getTestQueueObj();
        queue_obj_t push_obj_2 = testObj_2.getTestQueueObj();
        queue_obj_t push_obj_3 = testObj_3.getTestQueueObj();

        queue_pushBack(handle, &push_obj_1);
        queue_pushBack(handle, &push_obj_2);
        queue_pushBack(handle, &push_obj_3);

        ASSERT_EQ(3, queue_getItemCount(handle));
    }

    TEST_F(QueueTest, itemCountShouldBeZero_onePushAndPop)
    {
        // create obj
        const int BUFF_SIZE_1 = 32;
        TestQueueObj testObj_1{"1.Hello world one", BUFF_SIZE_1};
        queue_obj_t push_obj_1 = testObj_1.getTestQueueObj();

        queue_pushBack(handle, &push_obj_1);
        queue_pop(handle);

        ASSERT_EQ(0, queue_getItemCount(handle));
    }

    TEST_F(QueueTest, itemCountShouldBeZero_onePushAndTwoPop)
    {
        // create obj
        const int BUFF_SIZE_1 = 32;
        TestQueueObj testObj_1{"1.Hello world one", BUFF_SIZE_1};
        queue_obj_t push_obj_1 = testObj_1.getTestQueueObj();

        queue_pushBack(handle, &push_obj_1);
        queue_pop(handle);
        queue_pop(handle);

        ASSERT_EQ(0, queue_getItemCount(handle));
    }

    TEST_F(QueueTest, itemCountShouldBeZero_twoPushAndTwoPop)
    {
        // create obj
        const int BUFF_SIZE_1 = 32;
        const int BUFF_SIZE_2 = 64;
        TestQueueObj testObj_1{"1.Hello world one", BUFF_SIZE_1};
        TestQueueObj testObj_2{"2.Hello world two", BUFF_SIZE_2};
        queue_obj_t push_obj_1 = testObj_1.getTestQueueObj();
        queue_obj_t push_obj_2 = testObj_2.getTestQueueObj();

        queue_pushBack(handle, &push_obj_1);
        queue_pushBack(handle, &push_obj_2);
        queue_pop(handle);
        queue_pop(handle);

        ASSERT_EQ(0, queue_getItemCount(handle));
    }

    TEST_F(QueueTest, itemCountShouldBeOne_twoPushAndOnePop)
    {
        // create obj
        const int BUFF_SIZE_1 = 32;
        const int BUFF_SIZE_2 = 64;
        TestQueueObj testObj_1{"1.Hello world one", BUFF_SIZE_1};
        TestQueueObj testObj_2{"2.Hello world two", BUFF_SIZE_2};
        queue_obj_t push_obj_1 = testObj_1.getTestQueueObj();
        queue_obj_t push_obj_2 = testObj_2.getTestQueueObj();

        queue_pushBack(handle, &push_obj_1);
        queue_pushBack(handle, &push_obj_2);
        queue_pop(handle);

        ASSERT_EQ(1, queue_getItemCount(handle));
    }
}
