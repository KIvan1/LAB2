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
    remove_all(txt);
}

/*TEST(prev_paste, suite1)
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
//}*/

TEST (save, suite1)
{
    text txt = create_text();
    testing::internal::CaptureStderr();
    save(txt, "test_save.txt");
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "The text doesn't exist\n");
    remove_all(txt);
}

TEST (save, suite2)
{
    text txt = create_text();
    load(txt, filename1);
    testing::internal::CaptureStderr();
    save(txt, "input/test_open.txt");
    std::string output = testing::internal::GetCapturedStderr();
    //EXPECT_EQ(output, "File input/test_open.txt can't be opened\n");
    remove_all(txt);
}

TEST(show, suite1)
{
    text txt = create_text();
    load(txt, filename1);
    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();
    int i = 0;
    node *current = txt->begin;
    while(current)
    {
        for (int j = 0; j < strlen(current->contents); j++)
        {
            EXPECT_EQ(output[i], current->contents[j]);
            i++;
        }
        if (output[i] == '\n')
            i++;
        current = current->next;
    }
    EXPECT_EQ(output[i], '|');
    remove_all(txt);
}

TEST(show, suite2)
{
    text txt = create_text();
    load(txt, filename1);
    move_cursor(txt, 1, 2);
    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();
    int i = 0;
    node *current = txt->begin;
    while(current)
    {
        for (int j = 0; j < strlen(current->contents); j++)
        {
            if (current == txt->cursor->line
                   && j == txt->cursor->position)
            {
                EXPECT_EQ(output[i], '|');
                i++;
            }
            EXPECT_EQ(output[i], current->contents[j]);
            i++;
        }
        if (output[i] == '\n')
            i++;
        current = current->next;
    }
    remove_all(txt);
}

TEST(showevenbeforodd, suite1)
{
    text txt = create_text();
    load(txt, filename1);
    testing::internal::CaptureStdout();
    showevenbeforodd(txt);
    std::string output = testing::internal::GetCapturedStdout();
    std::ifstream f;
    f.open("input/test_sweb.txt");
    std::string s;
    int i = 0;
    while(std::getline(f, s))
    {
        std::string cur_s;
        while(output[i] != '\n')
        {
            cur_s += output[i];
            i++;
        }
        i++;
        EXPECT_EQ(cur_s, s);
    }
    remove_all(txt);
}


TEST(showevenbeforodd, suite2)
{
    text txt = create_text();
    load(txt, "input/input_odd.txt");
    testing::internal::CaptureStdout();
    showevenbeforodd(txt);
    std::string output = testing::internal::GetCapturedStdout();
    std::ifstream f;
    f.open("input/test_sweb_odd.txt");
    std::string s;
    int i = 0;
    while(std::getline(f, s))
    {
        std::string cur_s;
        while(output[i] != '\n')
        {
            cur_s += output[i];
            i++;
        }
        i++;
        EXPECT_EQ(cur_s, s);
    }
    remove_all(txt);
}

TEST(showevenbeforodd, suite3)
{
    text txt = create_text();
    testing::internal::CaptureStderr();
    showevenbeforodd(txt);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "There are already no any lines in the text!\n");
    remove_all(txt);
}

#endif // TESTS_OUT_H
