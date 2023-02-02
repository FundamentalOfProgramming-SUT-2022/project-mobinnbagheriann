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
char dir[100];
int grep_LINE=0;
int filen(char*dir)
{
    int len=1;
    FILE*f=fopen(dir,"r");
    char c;
    c=fgetc(f);
    while(c!=EOF)
    {
        if(c=='\n')
        {
            len++;
        }
        c=fgetc(f);

    }
    return len;
}
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
void createfile(int flagu)
{
    char dir[1000];
    memset(dir, 0, 1000);
    int len = strlen(command_seprate[2]);
   
    
    
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
    
    FILE *new = fopen(dir, "w");
    fclose(new);
    if(!flagu)
    {
    printf("File has successfully made!\n");
    }
}
void insertstr()
{
   int save_charc[MAX];
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
    
    char content[MAX];
     int j = 0;
     int test;
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
        save_charc[linecnt]=len;
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
    if(line>linecnt)
    {
        printf("you cant do this");
        return;
    }
    else if(save_charc[line]<char_pos)
    {
        
        
            printf("you cant do this");

            return;
        
    }
    f = fopen(cp_dir, "w+");
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
    int flag11 = 1;
    while (flag11)
    {
        if (fgets(t_arr, MAX + 1, tpf) == NULL)
        {
            flag11 = 0;
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

   
     char content[MAX];
     int j = 0;
    char text[MAX];
    memset(text, 0, MAX);
    int linecnt = 1;
     int line;
     int char_pos;
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
     

}
void paste()
{
    
    int len=strlen(clipboard);
    for(int i=0;i<len;i++)
    {
        command_seprate[4][i]=clipboard[i];
    }
    insertstr();
}
void slash_deleter(char *string_find)
{
    for(int i=0;i<strlen(string_find);i++)
    {
        if(string_find[i]=='\\' && string_find[i+1]=='*')
        {
            string_find[i]='*';
        }
        
    }
}
void star_deleter(char *string_find)
{
    for(int i=0;i<strlen(string_find);i++)
    {
        if(string_find[i]=='*')
        {
            string_find[i]=string_find[i+1];
        }
    }
}
void string_seprate(const char string[],char seprate_string[][MAX])
{
    int i=0;
    int j=0;
    int k=0;
    while (1)
    {
        if(string[k]=='\0')
        {
            return;
        }
        else if(string[i]==' ' || string[i]=='\n' )
        {   
            seprate_string[i][j]='\0';
            k++;
            i++;
            j=0;
        }
        seprate_string[i][j]=string[k];
        j++;
        k++;
    

    }
}
void swap(char *first, char *seccond)
{
    char temp;
    for (int i = 0; i < MAX; i++)
    {
        temp = *(first + i);
        *(first + i) = *(seccond + i);
        *(seccond + i) = temp;
    }
}
void find()
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


    int begin_wild=0;
    int wild_word_pos=1;
    int wildcard=0;
    char string_seprate_find[20][MAX];
    char atext_seprate[20][MAX];
    char atext[MAX];
    int repeat[MAX];
    int repeatw[MAX];
    int counter=0;
    int pbc=0;
    int pbw=1;
    for(int i=0;i<20;i++)
    {
        memset(string_seprate_find[i],0,MAX);
        memset(atext_seprate[i],0,MAX);
    }
    FILE*f=fopen(command_seprate[2],"r");
    char string_find[MAX];
     strcat(string_find,command_seprate[4]);
     for(int i=0;i<strlen(string_find);i++)
     {
        if(string_find[i]=='*' && i==0)
        {
            wildcard=1;
            break;
        }
        else if(string_find[i]=='*' && string_find[i-1] !='\\')
        {
            wildcard=1;
            break;
        }
     }
     if(wildcard)
     {
        for(int i=0;i<strlen(string_find);i++)
        {
            if(string_find[i]=='*')
            {
                break;
            }
            if(string_find[i]==' ')
            {
                wild_word_pos++;
            }
        }
        for(int i=0;i<strlen(string_find);i++)
        {
            if(string_find[i]=='*')
            {
                if(string_find[i-1]==' ' || string_find[i-1]=='\n' || i==0)
                {
                    begin_wild=1;
                    break;
                }
            }
        }



     }
     
     else
     {
        slash_deleter(string_find);
     }
     star_deleter(string_find);
     char c=fgetc(f);
     for(int i=0;c!=EOF;i++)
     {
        atext[i]=c;
        c=fgetc(f);
     }
     string_seprate(atext,atext_seprate);
     string_seprate(string_find,string_seprate_find);
     int pwd=1;
     int wps=1;
     int wpt=1;
     int find_result=1;
     if(wildcard)
     {
        while(atext_seprate[pwd-1][0]!='\0')
        {
            while(string_seprate_find[wps-1][0]!='\0')
            {
                if(wps==wild_word_pos)
                {
                    if(strlen(atext_seprate[wpt-1])<strlen(string_seprate_find[wps-1]))
                    {
                        find_result=0;
                        break;
                    }
                    if(begin_wild)
                    {
                        for(int i=1;i<strlen(string_seprate_find[wps-1]);i++)
                        {
                            char b1;
                            b1=atext_seprate[wpt-1][strlen(atext_seprate[wpt-1])-i];
                            char b2;
                            b2=string_seprate_find[wps-1][strlen(string_seprate_find[wps-1])-i];
                            if(b1!=b2)
                            {
                                find_result=0;
                                break;
                            }

                        }
                    }
                    else
                    {
                        for(int i=0;i<strlen(string_seprate_find[wps-1]);i++)
                        {
                            if(atext_seprate[wpt-1][i] != string_seprate_find[wps-1][i])
                            {
                                find_result=0;
                                break;
                            }
                        }
                    }
                    
                }
                else
                {
                    if(strcmp(atext_seprate[wpt-1],string_seprate_find[wps-1]) != 0)
                    {
                        find_result=0;
                        break;
                    }
                    
                }
                wps++;
                    wpt++;

            }
            if(find_result)
            {
                repeat[counter]=pbc;
                repeatw[counter]=pbw;
                counter++;
            }
            find_result=1;
            pbc=pbc+1+strlen(atext_seprate[pbw-1]);
            pbw++;
            wps=1;
            wpt=pbw;
        }
     }
    
   

     
     else
     {
        
        fclose(f);
        f=fopen(command_seprate[2],"r");
        int i=0;
        int counter=0,wcounter=1,p=0,z,k;
      char c=fgetc(f);
      find_result=0;
      int t=1;
      int len=strlen(string_find);
      while(c!=EOF)
      {
      while(c!=EOF && c==string_find[i] && ++i<len)
      {
        c=fgetc(f);
        if(i==1)
        {
            k=wcounter;
            z=p;
        }
        if(c==' ' || c=='\n' )
        {
            wcounter++;
            p++;
        }
      }
      if(i==len)
      {
        if(len==1)
        {
        repeat[counter]=p-1;
        repeatw[counter]=wcounter;
        }
        else
        {
            repeat[counter]=z-1;
            repeatw[counter]=k;

        }
        counter++;
        find_result=1;
      }
      i=0;
      c=fgetc(f);
      if(c==' ' && c== '\n')
      {
        wcounter++;
        p++;
      }

      }

}
fclose(f);
  if ((strcmp(command_seprate[6], "-at") == 0 && strcmp(command_seprate[5], "-byword") == 0) || (strcmp(command_seprate[7], "-byword") == 0 && strcmp(command_seprate[5], "-at") == 0))
    {
        long atpos;
        char *end_of_at_index;

        if (strcmp(command_seprate[6], "-at") == 0)
        {
            atpos = strtol(command_seprate[7], &end_of_at_index, 10);
        }

        else
        {
            atpos = strtol(command_seprate[6], &end_of_at_index, 10);
        }

        if (repeatw[atpos - 1] == -1)
        {
            printf("\"find\" returned \"-1\"\n");
            return;
        }

        else
        {
            printf("The \"%d\" index of repeatation byword is \"%d\".\n", atpos, repeatw[atpos - 1]);
            return;
        }
    }

    else if ((strcmp(command_seprate[6], "-all") == 0 && strcmp(command_seprate[5], "-byword") == 0) || (strcmp(command_seprate[6], "-byword") == 0 && strcmp(command_seprate[5], "-all") == 0))
    {
        if (repeatw[0] == -1)
        {
            printf(" the \"find\" returned \"-1\"\n");
            return;
        }

        else
        {
            printf("All values of repeatation (byword index):\n");
            for (int i = 0; repeatw[i] != -1; i++)
            {
                printf("%d ", repeatw[i]);
            }
            printf("\n");
        }
    }

    
    else if (command_seprate[5][0] == '\0')
    {
        if (repeatw[0] == -1)
        {
            printf("The value hasn't been repeated at all, and the \"find\" returned \"-1\"\n");
            return;
        }

        else
        {
            printf("The first repeatation is in \"%d\" char.\n", repeat[0]);
            return;
        }
    }

    else if (strcmp(command_seprate[5], "-at") == 0 && command_seprate[7][0] == '\0')
    {
        long atpos;
        char *end_of_at_index;

        atpos = strtol(command_seprate[6], &end_of_at_index, 10);

        if (repeatw[atpos - 1] == -1)
        {
            printf(" the \"find\" returned \"-1\"\n");
            return;
        }

        else
        {
            printf("The \"%d\" index of repeatation byword is \"%d\".\n", atpos, repeatw[atpos - 1]);
            return;
        }
    }

    else if (strcmp(command_seprate[5], "-byword") == 0 && command_seprate[6][0] == '\0')
    {
        if (repeatw[0] == -1)
        {
            printf(" the \"find\" returned \"-1\".\n");
            return;
        }


        else
        {
            printf("The first repeat was in \"%d\"th word.\n", repeatw[0]);
        }
    }

    else if (strcmp(command_seprate[5], "-count") == 0 && command_seprate[6][0] == '\0')
    {
        int rc= 0;
        int i = 0;

        while (repeat[i] != -1)
        {
            rc++;
            i++;
        }

        printf("The count of repeatation is \"%d\".\n", rc);
        return;
    }

    else if (strcmp(command_seprate[5], "-all") == 0 && command_seprate[6][0] == '\0')
    {
        if (repeat[0] == -1)
        {
            printf(" the \"find\" returned \"-1\"\n");
            return;
        }

        else
        {
            printf("All values of repeatation:\n");

            for (int i = 0; repeat[i] != -1; i++)
            {
                printf("%d ", repeat[i]);
            }

            printf("\n");

            return;
        }
    }

    else
    {
        printf("Not a accessable combination!\n");
        return;
    }
}
void grep(int option)
{
    char copy[MAX];
    FILE*f=fopen(command_seprate[2],"r");
    while(!feof(f))
    {
        
        fgets(copy,MAX,f);
        if(strstr(copy,command_seprate[4])!=NULL)
        {
            if(option==0)
            {
            grep_LINE++;
            }
            else if(option==1)
            {
                printf("%s: %s ",command_seprate[2],copy);
                if(copy[strlen(copy)-1] !='\n')
                {
                    printf("\n");
                }
            }
            else if(option==2)
            {
                printf("%s\n",command_seprate[2]);
            }


        }

    }
    fclose(f);
}
void a_tree(char*rootdir,int root)
{
    int i;
    char path[MAX];
    struct dirent *dead;
    DIR*dir=opendir(rootdir);
    if(!dir)
    {
        return;
    }
    while((dead=readdir(dir)) != NULL)
    {
        if(strcmp(dead->d_name,".") !=0 && strcmp(dead->d_name,"..") !=0 )
        {
            for(i=0;i<root;i++)
            {
                if(i%2==0 || i==0)
                {
                    printf("%c",179);
                }
                else
                {
                    printf(" ");
                }
            }
            printf("%c%c%s\n",195,196,dead->d_name);
            strcpy(path,rootdir);
            strcat(path,"/");
            strcat(path,dead->d_name);
            a_tree(path,root+2);
        }
    }
}
void tree_specific_depth(char*rootdir,int root,int depth)
{
   int i;
    char path[MAX];
    struct dirent *dead;
    DIR*dir=opendir(rootdir);
    if(!dir || root==2*depth)
    {
        return;
    }
    while((dead=readdir(dir)) != NULL)
    {
        if(strcmp(dead->d_name,".") !=0 && strcmp(dead->d_name,"..") !=0 )
        {
            for(i=0;i<root;i++)
            {
                if(i%2==0 || i==0)
                {
                    printf("%c",179);
                }
                else
                {
                    printf(" ");
                }
            }
            printf("%c%c%s\n",195,196,dead->d_name);
            strcpy(path,rootdir);
            strcat(path,"/");
            strcat(path,dead->d_name);
            tree_specific_depth(path,root+2,depth);
        }
    } 
}
void undoexe()
{
    char atext[MAX*MAX];
    char toundo[MAX];
    char c;
    memset(atext,0,MAX*MAX);
    memset(toundo,0,MAX);
    strcat(toundo,command_seprate[2]);

    char name[4]={'u','n','d','o'};
    for(int i=2;i<2+4;i++)
    {
        toundo[i]=name[i-2];

    }
    FILE*f=fopen(command_seprate[2],"r");
    FILE*backup=fopen(toundo,"w");
    c=fgetc(f);
    while(c!=EOF)
    {
        fputc(c,backup);
        c=fgetc(f);
    }
    fclose(f);
    fclose(backup);

}
void undo()
{
    if (!path_existance(command_seprate[2]))
    {
        printf("path is wrong\n!");
        return;
    }
    if (!file_exsistance(command_seprate[2]))
    {
        printf("file is wrong\n");
        return;
    }

     char atext[MAX*MAX];
    char toundo[MAX];
    char c;
    memset(atext,0,MAX*MAX);
    memset(toundo,0,MAX);
    strcat(toundo,command_seprate[2]);

  char name[4]={'u','n','d','o'};
    for(int i=2;i<2+(4);i++)
    {
        toundo[i]=name[i-2];

    }
    FILE*f=fopen(command_seprate[2],"w");
    FILE*backup=fopen(toundo,"r");
    c=fgetc(backup);
    while(c!=EOF)
    {
        fputc(c,f);
        c=fgetc(backup);
    }
    fclose(f);
    fclose(backup);
    printf("undone!\n");

}
void compare(int filen1,int filen2)
{
    FILE*f1=fopen(command_seprate[1],"r");
    FILE*f2=fopen(command_seprate[2],"r");
    char exe_f1[MAX];
    char exe_f2[MAX];
    int linecount=1;
    int flag=1;
    while(flag)
    {
        if(fgets(exe_f1,MAX+10,f1)==NULL || fgets(exe_f2,MAX+10,f2)==NULL)
        {
            flag=0;
            continue;
        }
        if(strcmp(exe_f1,exe_f2))
        {
            printf("============ #%d ============\n",linecount);

        
        if(linecount!=filen1 && linecount!=filen2)
        {
            printf("%s%s",exe_f1,exe_f2);
        }
        else if(linecount==filen1)
        {
            printf("%s\n%s",exe_f1,exe_f2);
        }
        else if(linecount==filen2)
        {
            printf("%s%s\n");
        }
        }
        linecount++;


    }
    int max;
    max=filen1-filen2;
    if(max>0)
    {
        printf("<<<<<<<<<<<< #%d - #%d >>>>>>>>>>>>\n",linecount,filen1);
        while(1)
        {
            printf("%s",exe_f1);
            if(fgets(exe_f1,MAX+10,f1)==NULL)
            {
                break;
            }
        }
        printf("\n");
    }
    else if(max<0)
    {
        printf(">>>>>>>>>>>> #%d - #%d <<<<<<<<<<<<\n",linecount,filen2);
        while(1)
        {
            if(fgets(exe_f2,MAX+10,f2)==NULL)
            {
                break;
            }
            printf("%s",exe_f2);
        }
        printf("\n");
    }
    fclose(f1);
    fclose(f2);


}
void auto_indent()
{
    FILE*f=fopen(command_seprate[1],"r");
    
    char ai[MAX];
    memset(ai,0,MAX);
    strncpy(ai,command_seprate[1],strlen(command_seprate[1])-4);
    strcat(ai,"ai.txt");
    FILE*aif=fopen(ai,"w+");
    int tab=0,space=0,nspace=0,copen=0;
    char c;
    printf("passed");
    while((c=fgetc(f)) != EOF)
    {
        
        
        if(c!='}' && c!='{' && c!=' ' )
        {
            if(copen==1)
            {
                for(int i=0;i<tab;i++)
                {
                    fputc("\t",aif);
                }

            }
            copen=0;
            if(nspace==1)
            {
                for(int i=0;i<space;i++)
                {
                    fputc(" ",aif);
                }
            }
            nspace=1;
            fputc(c,aif);
            space=0;

        }
        if(c==' ')
        {
            space++;
        }
        if(c=='{')
        {
            if(nspace==0)
            {
                for(int i=0;i<tab;i++)
                {
                    fputc("\t",aif);
                }
            }
            tab=tab+1;
            space=0;
            if(nspace==1)
            {
                fputc(' ',aif);
            }
                fputs("{\n",aif);

            
            nspace=0;
            copen=1;




        }
        if(c=='}')
        {
            tab=tab-1;
            space=0;
            if(nspace==1)
            {
                fputc("\n",aif);
            }
            for(int i=0;i<tab;i++)
            {
                fputc("\t",aif);
            }
            fputs('}\n',aif);
            nspace=0;
        }


    }
    printf("rad");
    fclose(f);
    fclose(aif);
   f = fopen(command_seprate[1], "w");
    aif = fopen(ai, "r");
   char a;
   printf("passed1");
   a=fgetc(aif);
   while(a!=EOF)
   {
    fputc(a,f);
    a=fgetc(aif);
}
printf("passed2");
   fclose(f);
   fclose(aif);
   


   
}

void execute_f()
{
    if (strcmp(command_seprate[0], "createfile") == 0)
    {
    char name[4]={'u','n','d','o'};
    int flagu;
         if (access((command_seprate[2]), F_OK) == 0)
    {
        printf("you create this before!\n");
       
        for(int i=2;i<2+4;i++)
        {
            command_seprate[2][i]=name[i-2];
        }
        flagu=1;
        createfile(flagu);
        return;
        
    }
       flagu=0;
        createfile(flagu);
       
        for(int i=2;i<2+4;i++)
        {
            command_seprate[2][i]=name[i-2];
        }
        flagu=1;
        createfile(flagu);
        
    }

    else if (strcmp(command_seprate[0], "insertstr") == 0)
    {
         if (!path_existance(command_seprate[2]))
    {
        printf("path is wrong\n!");
        return;
    }
    if (!file_exsistance(command_seprate[2]))
    {
        printf("file is wrong\n");
        return;
    }
        undoexe();
        insertstr();
    }
    else if (strcmp(command_seprate[0], "cat") == 0)
    {
         if (!path_existance(command_seprate[2]))
    {
        printf("path is wrong\n!");
        return;
    }
    if (!file_exsistance(command_seprate[2]))
    {
        printf("file is wrong\n");
        return;
    }
        undoexe();
        cat();
    }
    else if (strcmp(command_seprate[0], "removestr") == 0)
    {
         if (!path_existance(command_seprate[2]))
    {
        printf("path is wrong\n!");
        return;
    }
    if (!file_exsistance(command_seprate[2]))
    {
        printf("file is wrong\n");
        return;
    }
        undoexe();
        removestr();
    }
    else if(strcmp(command_seprate[0],"copy")==0)
    {
         if (!path_existance(command_seprate[2]))
    {
        printf("path is wrong!\n");
        return;
    }
    if (!file_exsistance(command_seprate[2]))
    {
        printf("file is wrong\n");
        return;
    }
        undoexe();
        copy();
    }
    else if(strcmp(command_seprate[0],"find")==0)
    {
        swap(command_seprate[1], command_seprate[3]);
        swap(command_seprate[2], command_seprate[4]);
        find();
    }
    else if(strcmp(command_seprate[0],"grep")==0)
    {

        int option;
        int start_file;
        
        if(strcmp(command_seprate[1],"--str")==0)
        {
            start_file=4;
            option=0;
             swap(command_seprate[1], command_seprate[3]);
            
        }
        else if(strcmp(command_seprate[1],"-c")==0)
        {
            start_file=5;
            option=1;
             memset(command_seprate[1], 0, MAX);
            swap(command_seprate[4], command_seprate[1]);
            swap(command_seprate[3], command_seprate[4]);
            swap(command_seprate[2], command_seprate[3]);
            
        }
        else if(strcmp(command_seprate[1],"-l")==0)
        {
            start_file=5;
            option=2;
            memset(command_seprate[1], 0, MAX);
            swap(command_seprate[4], command_seprate[1]);
            swap(command_seprate[3], command_seprate[4]);
            swap(command_seprate[2], command_seprate[3]);
            
        }
        while(command_seprate[start_file][0]!=0)
        {
            swap(command_seprate[2],command_seprate[start_file]);
            if (!path_existance(command_seprate[2]))
    {
        printf("path is wrong\n!");
        return;
    }
    if (!file_exsistance(command_seprate[2]))
    {
        printf("file is wrong\n");
        return;
    }
        
        grep(option);
        start_file++;

        }
        if(option==0)
        {
            printf("%d",grep_LINE);
        }
    }
    else if(strcmp(command_seprate[0],"tree")==0)
    {
        long depth;
        char *edepth;
        depth=strtol(command_seprate[1],&edepth,10);
        if(depth<-1)
        {
            printf("invalid depth");
        }
        else if(depth==0)
        {
            printf("\n");
            return;
        }
        else if(depth==-1)
        {
            a_tree("./root",0);
        }
        
        else
        {
            tree_specific_depth("./root",0,depth);
        }
    }
    else if(strcmp(command_seprate[0],"undo")==0)
    {
         if (!path_existance(command_seprate[2]))
    {
        printf("path is wrong\n!");
        return;
    }
    if (!file_exsistance(command_seprate[2]))
    {
        printf("file is wrong\n");
        return;
    }
        
        undo();

    }
    else if(strcmp(command_seprate[0],"compare")==0)
    {
             if (!path_existance(command_seprate[1]))
    {
        printf("path1 is wrong\n!");
        return;
    }
    if (!file_exsistance(command_seprate[1]))
    {
        printf("file1 is wrong\n");
        return;
    }
              if (!path_existance(command_seprate[2]))
    {
        printf("path2 is wrong\n!");
        return;
    }
    if (!file_exsistance(command_seprate[2]))
    {
        printf("file2 is wrong\n");
        return;
    }
        compare(filen(command_seprate[1]),filen(command_seprate[2]));


    }
    else if(strcmp(command_seprate[0],"auto-indent")==0)
    {
       
       for(int i=0;i<strlen(command_seprate[1]);i++)
       {
        command_seprate[2][i]=command_seprate[1][i];
       }
               if (!path_existance())
    {
        printf("path1 is wrong\n!");
        return;
    }
    if (!file_exsistance())
    {
        printf("file1 is wrong\n");
        return;
    }
        auto_indent();
        printf("autoindented");
    }
    


    else 
    {
        printf("invalid command\n");
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
