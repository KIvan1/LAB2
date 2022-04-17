#include <stdio.h>
#include "common.h"
#include "text/_text.h"
#include "text/text.h"

void move_cursor(text txt, int line, int pos)
{
	int k = 1;
	node *current = txt->begin;
	txt->cursor->position = pos;
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