/**
 * show.c -- реализует команду вывода хранимого текста на экран
 *
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "text/text.h"
#include "text/_text.h"


static void show_line(int index, char *contents, int cursor, void *data);

/**
 * Выводит содержимое указанного файла на экран
 */
void show(text txt)
{
    /* Применяем функцию show_line к каждой строке текста */
    process_forward(txt, show_line, NULL);
}


void showevenbeforodd(text txt)
{
    if (txt == NULL || txt->length == 0)
    {
        fprintf(stderr, "There are already no any lines in the text!\n");
        return;
    }
    assert(txt->begin != NULL && txt->end != NULL);

    node *prev = txt->begin;
    node *current = prev->next;
    int cursor_position = -1;

    while (current)
    {
        if (txt->cursor->line == current)
            cursor_position = txt->cursor->position;
        else
            cursor_position = -1;

        if (prev != current)
        {
            show_line(0, current->contents, cursor_position, NULL);
            current = prev;
        }
        else
        {
            if (prev->next != txt->end)
            {
                prev = prev->next->next;
            }
            else
            {
                prev = prev->next;
            }
            show_line(0, current->contents, cursor_position, NULL);
            current = prev->next;
        }
    }
    if (txt->length % 2 == 1)
    {
        if (txt->cursor->line == prev)
            cursor_position = txt->cursor->position;
        else
            cursor_position = -1;
        show_line(0, prev->contents, cursor_position, NULL);
    }
}

/**
 * Выводит содержимое указанного файла на экран
 */
static void show_line(int index, char *contents, int cursor, void *data)
{
    /* Функция обработчик всегда получает существующую строку */
    assert(contents != NULL);
    
    /* Декларируем неиспользуемые параметры */
    UNUSED(index);
    UNUSED(data);

    int data_len = strlen(contents) - 1;
    int len = data_len > cursor ? data_len : cursor;

    if (cursor != -1)
    {
        for (int i = 0; i <= len; i++)
        {
            if (i == cursor)
            {
                printf("|");
            }
            if (i <= data_len)
            {
                printf("%c", contents[i]);
            }
            else if (i < len)
            { 
                printf(" ");
            }
        }
    }
    else
    {
        /* Выводим строку на экран */
        printf("%s", contents);
    }
    printf("\n");
}
