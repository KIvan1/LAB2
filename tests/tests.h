#ifndef EQTEST_H
#define EQTEST_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <string>
#include <fstream>

char* filename = "input.txt";

extern "C"{
#include "text.h"
#include "_text.h"
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

TEST(prev_paste, suite2)
{
    text txt = create_text();
    load(txt, filename);
    int prevSize = txt->length;
    prev_paste(txt, "test");
    EXPECT_EQ(txt->length - 1, prevSize);
    EXPECT_STREQ(txt->cursor->line->previous->contents, "test");
}

TEST(prev_paste, suite3)
{
    text txt = create_text();
    load(txt, filename);
    int prevSize = txt->length;
    move_cursor(txt, 1, 0);
    prev_paste(txt, "test");
    EXPECT_EQ(txt->length - 1, prevSize);
    EXPECT_STREQ(txt->begin->contents, "test");
}

TEST(save, suite3)
{
    text txt = create_text();
    load(txt, filename);
    save(txt, "result.txt");
    std::ifstream f;
    f.open(filename);
    std::ifstream cur_f;
    cur_f.open("result.txt");
    std::string s;
    std::string cur_s;
    while(std::getline(f, s) && std::getline(cur_f, cur_s))
    {
        EXPECT_EQ(s, cur_s);
    }
    EXPECT_TRUE(std::getline(f, s) || std::getline(cur_f, cur_s));
    f.close();
    cur_f.close();
}

TEST(show, suite1)
{

}

#endif // EQTEST_H
