#include <stdio.h>
#include <string.h>
#include "common.h"
#include "text/text.h"
#include "text/_text.h"

void prev_paste(text txt, const char *str_for_input)
{
    assert(str_for_input != NULL);

    node *nd;

    if ((nd = (node *) malloc(sizeof(node))) == NULL) {
        fprintf(stderr, "Not enough memory!\n");
        exit(EXIT_FAILURE);
    }

    if (strlen(str_for_input) > MAXLINE) {
        fprintf(stderr, "Too long line!\n");
        exit(EXIT_FAILURE);
    }

    strncpy(nd->contents, str_for_input, MAXLINE);
    nd->contents[MAXLINE] = '\0';

    nd->next = txt->cursor->line;
    node * prev = txt->cursor->line->previous;
    txt->cursor->line->previous = nd;
    if (txt->cursor->line != txt->begin)
    {
        nd->previous = prev;
        prev->next = nd;
    }
    else
    {
        txt->begin = nd;
    }
    printf("%s\n", txt->cursor->line->previous->next->contents);
    txt->length++;
}
