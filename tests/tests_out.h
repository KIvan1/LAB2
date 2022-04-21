#ifndef TESTS_OUT_H
#define TESTS_OUT_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include<fstream>
#include<string>

char* filename1 = "input.txt";

extern "C"{
#include "text.h"
#include "_text.h"
#include "common.h"
}

TEST(mplb, sute3)
{
    text txt = create_text();
    txt->cursor->line = txt->begin;
    node *prev = txt->cursor->line;
    testing::internal::CaptureStderr();
    mplb(txt);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "There are already no any lines in the text!\n");
}

//TEST(prev_paste, suite1)
//{
//    text txt = create_text();
//    load(txt, filename1);
//    char *s;
//    for (int i = 0; i < MAXLINE + 1; i++)
//    {
//        strcat(s, "t");
//    }
//    testing::internal::CaptureStderr();
//    prev_paste(txt, s);
//    std::string output = testing::internal::GetCapturedStderr();
//    std::cout << output << std::endl;
//    EXPECT_EQ(output, "Too long line!\n");
//}

TEST (save, suite1)
{
    text txt = create_text();
    testing::internal::CaptureStderr();
    save(txt, "test_save.txt");
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "The text doesn't exist\n");
}

TEST (save, suite2)
{
    text txt = create_text();
    load(txt, filename1);
    testing::internal::CaptureStderr();
    save(txt, "test_open.txt");
    std::string output = testing::internal::GetCapturedStderr();
    //EXPECT_EQ(output, "File test_open.txt can't be opened\n");
}

#endif // TESTS_OUT_H
