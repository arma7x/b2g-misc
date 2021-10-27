#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void reverse(char *strng) {
    int len = strlen(strng);
    for (int x=0;x<len/2;x++) {
      char t = strng[x];
      strng[x] = strng[len - 1 - x];
      strng[len - 1 - x] = t; 
    }
}

void show_pid(char *buffer)
{
    reverse(buffer);
    char *res;
    int idx = 0;
    int root = 0;
    char *pid;
    while((res = strsep(&buffer, " ")) != NULL) {
        if (! strlen(res))
        {
            continue;
        }
        if (idx == 8)
        {
          if (strcmp(res, "toor") == 0)
            root = 1;
          break;
        }
        if (idx == 7)
            pid = res;
        idx++;
    }

    if (root == 0)
    {
        char str[80];
        reverse(pid);
        sprintf(str, "kill %s", pid);
        // printf("%d %s %s %d\n", root, pid, str, strlen(pid));
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

