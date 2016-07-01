#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *input_lines[5000];
char line_holder[500000];
char *linep = line_holder;

char * alloc(int x)
{
    linep += x;
    return (linep - x);
}

void tail_extractor(char * lineptr[], int tail_length)
{
    char *p;
    int c, char_count = 0, position = 0, line_counter = 0, input_lines_index = 0;
    while((c = getchar()) != '\0' && c != EOF)
    {
        if(c == '\n')
        {
            if(char_count == 0)
            {
                line_holder[position++] = c;
                line_holder[position] = '\0';
            }
            else
                line_holder[position] = '\0';
            p = (char_count == 0)? alloc(1):alloc(char_count);
//            printf((char_count == 0)? "char_count is: 0\n":"char_count is: %d\n", char_count);
            strcpy(p, line_holder);
            lineptr[input_lines_index] = p;
//            printf("%s\n", *lineptr++);
            char_count = 0;
            position = 0;
            ++input_lines_index;
            ++line_counter;
        }
        else
        {
            line_holder[position++] = c;
            ++char_count;
        }
    }
    position = 0;
    while(tail_length > 0)
    {
        printf("%s\n", lineptr[input_lines_index - (tail_length--)]);
        printf("printed.\n");
    }
//    while(tail_length-- > 0)
//    {
//        *--lineptr;
//    }
//    while(tail_length_copy-- > 0)
//    {
//        printf("%s\n", *lineptr++);
//    }
}

int main(int argc, char * argv[])
{
    if(argc == 2)
    {
        int lines_to_tail = 0, c = 0;
        while(--argc > 0 && (*++argv)[0] == '-')
        {
            while(c = *++argv[0])
            {
                if(isdigit(c))
                    lines_to_tail = lines_to_tail * 10 + (c - '0');
                else
                {
                    break;
                }
            }
        }
//        printf("lines_to_tail is: %d\n", lines_to_tail);
        (lines_to_tail == 0)? tail_extractor(input_lines, 10): tail_extractor(input_lines, lines_to_tail);
    }
    else
    {
        tail_extractor(input_lines, 10);
    }
    return 0;
}
