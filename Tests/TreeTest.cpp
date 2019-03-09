//
// Created by max on 09.03.19.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../MyMap.h"
#include "../MyList.h"

using testing::Eq;

namespace {
    class ClassDeclaration : public testing::Test{
    public:
        MyMap<int,int> testExample;
        MyMap<char, char> testExampleChar;
        ClassDeclaration(){
            testExample;
            testExampleChar;
        }
    };
}

TEST_F(ClassDeclaration, InsertNormalWorkTest) {
    testExample.Insert(5, 7);
    testExample.Insert(10, 17);
    testExample.Insert(15, 27);

    int expectKeys[] = {5, 10, 15};
    int expectValue[] = {7, 17, 27};
    bool expectColor[] = {true, false, true};

    for (unsigned int i = 0; i < 3; ++i) {
        ASSERT_EQ(testExample.GetKeys().ToArr()[i], expectKeys[i]);
        ASSERT_EQ(testExample.GetValue().ToArr()[i], expectValue[i]);
        ASSERT_EQ(testExample.GetColor().ToArr()[i], expectColor[i]);
    }
}

TEST_F(ClassDeclaration, RemoveRootWorkTest) {
    testExample.Insert(5, 7);
    testExample.Insert(10, 17);
    testExample.Insert(15, 27);
    testExample.Remove(10);

    int expectKeys[] = {5, 15};
    int expectValue[] = {7, 27};
    bool expectColor[] = {true, false};

    for (unsigned int i = 0; i < 2; ++i) {
        ASSERT_EQ(testExample.GetKeys().ToArr()[i], expectKeys[i]);
        ASSERT_EQ(testExample.GetValue().ToArr()[i], expectValue[i]);
        ASSERT_EQ(testExample.GetColor().ToArr()[i], expectColor[i]);
    }
}

TEST_F(ClassDeclaration, RemoveLeftWorkTest) {
    testExample.Insert(5, 7);
    testExample.Insert(10, 17);
    testExample.Insert(15, 27);
    testExample.Remove(5);

    int expectKeys[] = {10, 15};
    int expectValue[] = {17, 27};
    bool expectColor[] = {false, true};

    for (unsigned int i = 0; i < 2; ++i) {
        ASSERT_EQ(testExample.GetKeys().ToArr()[i], expectKeys[i]);
        ASSERT_EQ(testExample.GetValue().ToArr()[i], expectValue[i]);
        ASSERT_EQ(testExample.GetColor().ToArr()[i], expectColor[i]);
    }
}

TEST_F(ClassDeclaration, RemoveRightWorkTest) {
    testExample.Insert(5, 7);
    testExample.Insert(10, 17);
    testExample.Insert(15, 27);
    testExample.Remove(15);

    int expectKeys[] = {5, 10};
    int expectValue[] = {7, 17};
    bool expectColor[] = {true, false};

    for (unsigned int i = 0; i < 2; ++i) {
        ASSERT_EQ(testExample.GetKeys().ToArr()[i], expectKeys[i]);
        ASSERT_EQ(testExample.GetValue().ToArr()[i], expectValue[i]);
        ASSERT_EQ(testExample.GetColor().ToArr()[i], expectColor[i]);
    }
}

TEST_F(ClassDeclaration, RemoveWrongArgumentWorkTest) {
    testExample.Insert(5, 7);
    testExample.Insert(10, 17);
    testExample.Insert(15, 27);
    ASSERT_THROW(testExample.Remove(7), invalid_argument);
}

TEST_F(ClassDeclaration, FindWrongArgumentWorkTest) {
    testExample.Insert(5, 7);
    testExample.Insert(10, 17);
    testExample.Insert(15, 27);
    ASSERT_THROW(testExample.Find(7), invalid_argument);
}

TEST_F(ClassDeclaration, FindNormalWorkTest) {
    testExample.Insert(5, 7);
    testExample.Insert(10, 17);
    testExample.Insert(15, 27);
    ASSERT_EQ(testExample.Find(10)->GetColor(), false);
    ASSERT_EQ(testExample.Find(10)->GetKey(), 10);
    ASSERT_EQ(testExample.Find(10)->GetValue(), 17);
}

TEST_F(ClassDeclaration, ClearNormalWorkTest) {
    testExample.Insert(5, 7);
    testExample.Insert(10, 17);
    testExample.Insert(15, 27);
    testExample.clear(testExample.GetRoot());
    ASSERT_EQ(testExample.GetRoot(), nullptr);
}