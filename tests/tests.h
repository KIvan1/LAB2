#ifndef EQTEST_H
#define EQTEST_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include<fstream>
#include<string>

char* filename = "./input/input.txt";

extern "C"{
#include "text/text.h"
#include "text/_text.h"
#include "common.h"
}

TEST(cursor_pos, sute1)
{
    text txt = create_text();
    load(txt, filename);
    move_cursor(txt, 2, 3);
    EXPECT_EQ(txt->cursor->position, 3);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line)
    {
        k++;
        current = current->next;
    }
    EXPECT_EQ(k, 2);
    remove_all(txt);
    move_cursor(txt, 2, 3);
}

TEST(cursor_pos, sute2)
{
    text txt = create_text();
    load(txt, filename);
    move_cursor(txt, -3, 0);
    EXPECT_EQ(txt->cursor->position, 0);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line)
    {
        k++;
        current = current->next;
    }
    EXPECT_EQ(k, 1);
    remove_all(txt);
    move_cursor(txt, 2, 3);
}

TEST(cursor_pos, sute3)
{
    text txt = create_text();
    load(txt, filename);
    move_cursor(txt, 15, 0);
    EXPECT_EQ(txt->cursor->position, 0);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line)
    {
        k++;
        current = current->next;
    }
    EXPECT_EQ(k, txt->length);
    remove_all(txt);
    move_cursor(txt, 2, 3);
}

TEST(mplb, sute1)
{
    text txt = create_text();
    load(txt, filename);
    node *prev = txt->cursor->line;
    mplb(txt);
    EXPECT_EQ(txt->cursor->position, 0);
    EXPECT_EQ(txt->cursor->line, prev->previous);
}

TEST(mplb, sute2)
{
    text txt = create_text();
    load(txt, filename);
    txt->cursor->line = txt->begin;
    node *prev = txt->cursor->line;
    mplb(txt);
    EXPECT_EQ(txt->cursor->position, 0);
    EXPECT_EQ(txt->cursor->line, prev);
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

TEST(prev_pos, suite1)
{
    text txt = create_text();
    load(txt, filename);
    prev_paste(txt, "test");
}

#endif // EQTEST_H
