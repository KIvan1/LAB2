#include <stdio.h>
#include "common.h"
#include "_text.h"
#include "text.h"

void move_cursor(text txt, int line, int pos)
{
	int k = 1;
	node *current = txt->begin;
    if (pos >= 0)
    {
        txt->cursor->position = pos;
    }
    else
    {
        txt->cursor->position = 0;
    }

    if (line > 0)
    {
        int l = txt->length;
        if (line > l)
            line = l;

        while(current)
        {
            if (k == line)
            {
                txt->cursor->line = current;
                break;
            }
            current = current->next;
            k ++;
        }
    }
    else
    {
        txt->cursor->line = current;
    }
}
