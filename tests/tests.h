#ifndef EQTEST_H
#define EQTEST_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <iostream>

extern "C"{
#include "text/text.h"
#include "text/_text.h"
#include "common.h"
}

TEST(cursor_pos, sute)
{
    text txt = create_text();
    load(txt, "input.txt");
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

#endif // EQTEST_H
