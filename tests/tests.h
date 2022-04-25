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

TEST(load, suite1)
{
    text txt = create_text();
    load(txt, filename);
    std::ifstream f;
    std::string s;
    node *current = txt->begin;
    EXPECT_NE(txt->begin, nullptr);
    EXPECT_NE(txt->end, nullptr);
    while (std::getline(f, s))
    {
        EXPECT_EQ(current->contents, s);
        current = current->next;
    }
}

TEST(move_cursor, sute1)
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
}

TEST(move_cursor, sute2)
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
}

TEST(move_cursor, sute3)
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
}

TEST(move_cursor, sute4)
{
    text txt = create_text();
    load(txt, filename);
    move_cursor(txt, 2, -5);
    EXPECT_EQ(txt->cursor->position, 0);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line)
    {
        k++;
        current = current->next;
    }
    EXPECT_EQ(k, 2);
    remove_all(txt);
}

TEST(move_cursor, sute5)
{
    text txt = create_text();
    load(txt, filename);
    move_cursor(txt, 2, 30);
    EXPECT_EQ(txt->cursor->position, 30);
    int k = 1;
    node *current = txt->begin;
    while(current != txt->cursor->line)
    {
        k++;
        current = current->next;
    }
    EXPECT_EQ(k, 2);
    remove_all(txt);
}

TEST(mplb, sute1)
{
    text txt = create_text();
    load(txt, filename);
    node *prev = txt->cursor->line;
    mplb(txt);
    EXPECT_EQ(txt->cursor->position, 0);
    EXPECT_EQ(txt->cursor->line, prev->previous);
    remove_all(txt);
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
    remove_all(txt);
}

TEST(prev_paste, suite2)
{
    text txt = create_text();
    load(txt, filename);
    int prevSize = txt->length;
    prev_paste(txt, "test");
    EXPECT_EQ(txt->length - 1, prevSize);
    EXPECT_STREQ(txt->cursor->line->previous->contents, "test");
    remove_all(txt);
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
    remove_all(txt);
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
    remove_all(txt);
}

#endif // EQTEST_H
