#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void show_pid(char *buffer)
{
    char *res;
    int idx = 0;
    int root = 0;
    while((res = strsep(&buffer, " ")) != NULL) {
        if (! strlen(res)) {
            continue;
        }
        if (idx == 2 && strcmp(res, "root") == 0)
            root = 1;
        if (idx == 3)
            break;
        idx++;
    }

    if (strlen(res) > 5)
        res = (res + (strlen(res) - 5));
    if (root == 0) {
        char str[80];
        sprintf(str, "kill %s", res);
        // printf("%d %s %s %d\n", root, res, str, strlen(res));
        FILE *fp;
        fp = popen(str, "r");
        pclose(fp);
    }
}

int main(int argc, char *argv[])
{
    FILE *fp;
    char buffer[4096];
    const char *b2g_ps = "b2g-ps";

    fp = popen(b2g_ps, "r");
    int i = 0;
    while(fgets(buffer, 4095, fp) != NULL) {
        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = 0;
        }
        if (i > 0)
          show_pid(buffer);
        i++;
    }
    pclose(fp);
    return 0;
}

