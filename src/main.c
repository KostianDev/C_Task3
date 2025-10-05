#include <stdio.h>
#include <stdlib.h>

char *read_line(int *out_had_newline);
void ascii_to_upper(char *s);

int main(void) {
    printf("Enter a line (ASCII only), then press Enter:\n");

    int had_newline = 0;
    char *s = read_line(&had_newline);
    if (!s) {
        return 0;
    }

    ascii_to_upper(s);

    printf("Here is the string in uppercase:\n%s\n", s);

    free(s);
    return 0;
}

char *read_line(int *out_had_newline) {
    size_t cap = 128;
    size_t len = 0;
    char *s = malloc(cap);
    if (!s) return NULL;

    int ch;
    int had_newline = 0;
    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            had_newline = 1;
            break;
        }
        if (len + 1 >= cap) {
            cap *= 2;
            char *tmp = realloc(s, cap);
            if (!tmp) {
                free(s);
                return NULL;
            }
            s = tmp;
        }
        s[len++] = (char)ch;
    }

    if (len == 0 && ch == EOF && !had_newline) {
        free(s);
        return NULL;
    }

    s[len] = '\0';
    if (out_had_newline) *out_had_newline = had_newline;
    return s;
}

void ascii_to_upper(char *s) {
    if (!s) return;
    for (size_t i = 0; s[i] != '\0'; ++i) {
        unsigned char c = (unsigned char)s[i];
        if (c >= 'a' && c <= 'z') {
            s[i] = (char)(c - 'a' + 'A');
        }
    }
}