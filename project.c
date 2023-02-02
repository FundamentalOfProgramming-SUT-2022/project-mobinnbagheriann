#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <windows.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <conio.h>
#include <io.h>

#define MAX 1000
char clipboard[MAX];
char command[MAX];
char command_seprate[30][MAX];
char tp[100];
char c_str[1000];

void khark(int *a, int *b)
{
    *(a) = *(a) + 2;
    *(b) = *(b) + 1;
}
void reset()
{
    for (int i = 0; i < 20; i++)
    {
        memset(command_seprate[i], 0, MAX);
    }
    memset(command, 0, MAX);
}
int path_existance()
{
    struct stat dt;
    char direction[MAX];
    int len = strlen(command_seprate[2]);
    strncpy(direction, command_seprate[2], len);
    char check[1000];
    for (int i = 0; i < len; i++)
    {
        check[i] = command_seprate[2][i];

        if (check[i + 1] == '\\')
        {
            if (stat(check, &dt) == -1)
            {
                return 0;
            }
        }
    }
    return 1;
}
int file_exsistance()
{
    FILE *f;
    if (f = fopen(command_seprate[2], "r"))
    {
        fclose(f);
        return 1;
    }
    return 0;
}
void seprate()
{
    int i = 0, j = 0, k = 0;
    int *i_p = &i;
    int *k_p = &k;
    int *j_p = &j;
    while (1)
    {
        if (command[k] == '\0')
        {
            return;
        }
        else if (command[k] == '\\')
        {
            if (command[k + 1] == 'n')
            {

                command_seprate[i][j] = '\n';
                khark(k_p, j_p);
                continue;
            }
            else if (command[k + 1] == '\\')
            {
                command_seprate[i][j] = '\\';
                khark(k_p, j_p);
                continue;
            }
            else if (command[k + 1] == '"')
            {
                command_seprate[i][j] = '"';
                khark(k_p, j_p);
                continue;
            }
        }
        else if (command[k] == ' ')
        {
            if (command[k + 1] == '"')
            {
                khark(k_p, i_p);
                j = 0;
                while (1)
                {
                    if (command[k - 1] != '\\' && command[k] == '"')
                    {
                        break;
                    }
                    else if (command[k] == '\\')
                    {
                        if (command[k + 1] == 'n')
                        {

                            command_seprate[i][j] == '\n';
                            khark(k_p, j_p);
                            continue;
                        }
                        else if (command[k + 1] == '\\')
                        {
                            command_seprate[i][j] = '\\';
                            khark(k_p, j_p);
                            continue;
                        }
                        else if (command[k + 1] == '"')
                        {
                            command_seprate[i][j] = '"';
                            khark(k_p, j_p);
                            continue;
                        }
                    }

                    command_seprate[i][j] = command[k];
                    k = k + 1;
                    j = j + 1;
                }
                k = k + 1;
            }

            j = 0;
            i++;
            k++;
            continue;
        }
        command_seprate[i][j] = command[k];
        k = k + 1;
        j = j + 1;
    }
}
void createfile()
{
    char dir[1000];
    memset(dir, 0, 1000);
    int len = strlen(command_seprate[2]);
    if (access((command_seprate[2]), F_OK) == 0)
    {
        printf("you create this before!\n");
        return;
    }
    else
    {
        dir[0] = '.';
        dir[1] = '/';

        for (int i = 2; i < len; i++)
        {
            if (command_seprate[2][i] != '/')
            {
                dir[i] = command_seprate[2][i];
            }
            else
            {
                mkdir(dir);
                dir[i] = command_seprate[2][i];
            }
        }
    }
    FILE *new = fopen(dir, "w");
    fclose(new);
    printf("File has successfully made!\n");
}
void insertstr()
{
    if (!path_existance(command_seprate[2]))
    {
        printf("path is wrong!");
        return;
    }
    if (!file_exsistance(command_seprate[2]))
    {
        printf("file is wrong");
        return;
    }
    long int line;
    long int char_pos;
    long int current_char_pos = 0;

    char *end_line_ptr;
    char *end_char_ptr;
    char cp_dir[MAX];
    char t_arr[MAX];
    char direction[MAX];
    long int current_line = 1;
    memset(direction, 0, MAX);
    memset(t_arr, 0, MAX);
    memset(c_str, 0, MAX);
    memset(cp_dir, 0, MAX);
    line = strtol(command_seprate[6], &end_line_ptr, 10);
    char_pos = strtol(end_line_ptr + 1, &end_char_ptr, 10);
    strcat(direction, command_seprate[2]);
    strcat(t_arr, command_seprate[4]);
    strncpy(cp_dir, direction, strlen(direction) - 4);
    strcat(cp_dir, "_cp.txt");
    FILE *f = fopen(cp_dir, "w+");
    FILE *tpf = fopen(direction, "r");

    while (current_line < line)
    {
        fputs(fgets(t_arr, MAX + 1, tpf), f);
        current_line = current_line + 1;
    }
    while (current_char_pos < char_pos)
    {
        fputc(fgetc(tpf), f);
        current_char_pos++;
    }
    for (int i = 0; i < strlen(command_seprate[4]); i++)
    {
        fputc(command_seprate[4][i], f);
    }
    int flag = 1;
    while (flag)
    {
        if (fgets(t_arr, MAX + 1, tpf) == NULL)
        {
            flag = 0;
            continue;
        }
        fputs(t_arr, f);
    }
    fclose(tpf);
    fclose(f);
    tpf = fopen(direction, "w");
    f = fopen(cp_dir, "r");
    int flag2 = 1;
    while (flag2)
    {
        if (fgets(t_arr, MAX + 1, f) == NULL)
        {
            flag2 = 0;
            continue;
        }
        fputs(t_arr, tpf);
    }
    fclose(tpf);
    fclose(f);
    remove(cp_dir);
}
void cat()
{
    char content[MAX];
    if (!path_existance(command_seprate[2]))
    {
        printf("path is wrong!");
        return;
    }
    if (!file_exsistance(command_seprate[2]))
    {
        printf("file is wrong");
        return;
    }
    FILE *f = fopen(command_seprate[2], "r");
    int flag = 1;
    while (flag)
    {
        if (fgets(content, MAX, f) == NULL)
        {
            flag = 0;
            continue;
        }
        printf("%s", content);
    }
    fclose(f);
    return;
}
void removestr()
{
    char *end_line_ptr;
    char *end_char_ptr;
    char *size_ptr;

    long line = strtol(command_seprate[4], &end_line_ptr, 10);
    long char_pos = strtol(end_line_ptr + 1, &end_char_ptr, 10);

    if (!path_existance(command_seprate[2]))
    {
        printf("path is wrong!");
        return;
    }
    if (!file_exsistance(command_seprate[2]))
    {
        printf("file is wrong");
        return;
    }

    char content[MAX];
     int j = 0;
    char text[MAX];
    memset(text, 0, MAX);
    int linecnt = 1;
    long long int pos_cnt = 0;
    long long int tag_pos = 0;
    FILE *f = fopen(command_seprate[2], "r");
    int flag = 1;
    while (flag)
    {
        if (fgets(content, MAX + 10, f) == NULL)
        {
            flag = 0;
            break;
        }

        int len = strlen(content);
        for (int i = 0; i < len; i++)
        {
            text[j] = content[i];
            j++;
            if (linecnt == line && i == char_pos)
            {
                tag_pos = pos_cnt + i;
            }
        }
        linecnt++;
        pos_cnt = pos_cnt + len;
    }
    fclose(f);
    int start;
    int end;
    long size = strtol(command_seprate[6], &size_ptr, 10);

    if (command_seprate[7][1] == 'b')
    {
        start = tag_pos - size;
        end = tag_pos;
    }
    else
    {
        end = tag_pos + size;
        start = tag_pos;
    }
    
    f = fopen(command_seprate[2], "w");
    for (int i = 0; i < start; i++)
    {
        fputc(text[i], f);
    }
    for (int i = end; i < j; i++)
    {
        fputc(text[i], f);
    }
    fclose(f);
    return;
}
void copy()
{

     if (!path_existance(command_seprate[2]))
    {
        printf("path is wrong!");
        return;
    }
    if (!file_exsistance(command_seprate[2]))
    {
        printf("file is wrong");
        return;
    }
     char content[MAX];
     int j = 0;
    char text[MAX];
    memset(text, 0, MAX);
    int linecnt = 1;
     long int line;
    long int char_pos;
    long long int pos_cnt = 0;
    long long int tag_pos = 0;
     char *end_line_ptr;
    char *end_char_ptr;
    char *size_ptr;
     line = strtol(command_seprate[6], &end_line_ptr, 10);
    char_pos = strtol(end_line_ptr + 1, &end_char_ptr, 10);
    FILE *f = fopen(command_seprate[2], "r");
    int flag = 1;
    while (flag)
    {
        if (fgets(content, MAX + 10, f) == NULL)
        {
            flag = 0;
            break;
        }

        int len = strlen(content);
        for (int i = 0; i < len; i++)
        {
            text[j] = content[i];
            j++;
            if (linecnt == line && i == char_pos)
            {
                tag_pos = pos_cnt + i;
            }
        }
        linecnt++;
        pos_cnt = pos_cnt + len;
    }
    fclose(f);
    int start;
    int end;
    long size = strtol(command_seprate[6], &size_ptr, 10);


    if (command_seprate[7][1] == 'b')
    {
        start = tag_pos - size;
        end = tag_pos;
    }
    else
    {
        end = tag_pos + size;
        start = tag_pos;
    }
    for(int i=start;i<=end;i++)
    {
        clipboard[i]=text[i];
    }

}
void cut()
{
      if (!path_existance(command_seprate[2]))
    {
        printf("path is wrong!");
        return;
    }
    if (!file_exsistance(command_seprate[2]))
    {
        printf("file is wrong");
        return;
    }
    copy();
    removestr();

}
void paste()
{
     if (!path_existance(command_seprate[2]))
    {
        printf("path is wrong!");
        return;
    }
    if (!file_exsistance(command_seprate[2]))
    {
        printf("file is wrong");
        return;
    }
    int len=strlen(clipboard);
    for(int i=0;i<len;i++)
    {
        command_seprate[4][i]=clipboard[i];
    }
    insertstr();
}


void execute_f()
{
    if (strcmp(command_seprate[0], "createfile") == 0)
    {
        createfile();
    }

    else if (strcmp(command_seprate[0], "insertstr") == 0)
    {

        insertstr();
    }
    else if (strcmp(command_seprate[0], "cat") == 0)
    {
        cat();
    }
    else if (strcmp(command_seprate[0], "removestr") == 0)
    {
        removestr();
    }
    else if(strcmp(command_seprate[0],"copy")==0)
    {
        copy();
    }
}

int main()
{
    printf("enter your command!\n");
    while (strcmp(command, "exit"))
    {
        reset();
        gets(command);
        seprate();
        execute_f();
    }
}
