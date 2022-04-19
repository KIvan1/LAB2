#include <stdio.h>
#include "common.h"
#include "text/text.h"
#include "text/_text.h"

void mplb(text txt)
{
    if (txt->cursor->line == txt->begin)
    {
        txt->cursor->position = 0;
        return;
    }

    if (txt == NULL || txt->length == 0)
    {
        fprintf(stderr, "There are already no any lines in the text!\n");
        return;
    }

    txt->cursor->position = 0;
    txt->cursor->line = txt->cursor->line->previous;
}

