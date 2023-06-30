#include <stdio.h>
#include <stdlib.h>
#include "ini.c"
#include <windows.h>
#include <iostream>
#pragma warning(disable : 4996)
#define MAX_DEFINES 100

typedef struct
{
    char defineName[50];
    char commentPart[100];
    char arrowPart[100];
    char plusPart[30];
} DefineInfo;

int isSpaceChar(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

int parseDefines(const char *filename, DefineInfo **infoArray)
{
    FILE *fp;
    char line[1024];
    int count = 0;

    if (NULL == (fp = fopen(filename, "r")))
    {
        perror("fopen");
        return 0;
    }

    *infoArray = (DefineInfo *)malloc(MAX_DEFINES * sizeof(DefineInfo));
    if (*infoArray == NULL)
    {
        fclose(fp);
        return 0;
    }

    while (NULL != fgets(line, sizeof(line), fp))
    {
        if (strncmp("#define", line, 7) == 0)
        {
            DefineInfo *info = &((*infoArray)[count]);

            char *startPos = strchr(line, '[');
            char *endPos = strchr(line, ']');
            char *arrowPos = strstr(line, "->");
            if (startPos && endPos && startPos < endPos)
            {
                *endPos = '\0';
                char *definePos = line + 8;
                while (isSpaceChar(*definePos))
                {
                    definePos++;
                }
                char *spacePos = definePos;
                while (!isSpaceChar(*spacePos))
                {
                    spacePos++;
                }
                *spacePos = '\0';
                strcpy(info->defineName, definePos);
                strcpy(info->commentPart, startPos + 1);
            }
            else
            {
                continue; // Skip if comment part not found
            }

            if (arrowPos)
            {
                char *plusPos = strchr(arrowPos + 2, '+');
                char *minusPos = strchr(arrowPos + 2, '-');

                if (plusPos && (!minusPos || plusPos < minusPos))
                {
                    *plusPos = '\0';
                    strcpy(info->arrowPart, arrowPos + 2);
                    char *nonSpacePos = plusPos + 1;
                    while (isSpaceChar(*nonSpacePos))
                    {
                        nonSpacePos++;
                    }
                    if (*nonSpacePos != '\0')
                    {
                        strcpy(info->plusPart, nonSpacePos);
                    }
                    else
                    {
                        info->plusPart[0] = '\0';
                    }
                }
                else if (minusPos && (!plusPos || minusPos < plusPos))
                {
                    *minusPos = '\0';
                    strcpy(info->arrowPart, arrowPos + 2);
                    char *nonSpacePos = minusPos + 1;
                    while (isSpaceChar(*nonSpacePos))
                    {
                        nonSpacePos++;
                    }
                    if (*nonSpacePos != '\0')
                    {
                        strcpy(info->plusPart, nonSpacePos);
                        // Prepend "-" to the Plus Part
                        memmove(info->plusPart + 2, info->plusPart, strlen(info->plusPart) + 1);
                        info->plusPart[0] = '-';
                        info->plusPart[1] = ' ';
                    }
                    else
                    {
                        info->plusPart[0] = '\0';
                    }
                }
                else
                {
                    strcpy(info->arrowPart, arrowPos + 2);
                    info->plusPart[0] = '\0';
                }
            }
            else
            {
                info->arrowPart[0] = '\0';
                info->plusPart[0] = '\0';
            }

            // Remove newline character from Arrow Part if Plus Part is empty
            if (info->plusPart[0] == '\0' && strlen(info->arrowPart) > 0)
            {
                size_t arrowLength = strlen(info->arrowPart);
                if (info->arrowPart[arrowLength - 1] == '\n')
                {
                    info->arrowPart[arrowLength - 1] = '\0';
                }
            }

            count++;
            if (count >= MAX_DEFINES)
            {
                break;
            }
        }
    }

    fclose(fp);

    return count;
}

void freeDefineInfoArray(DefineInfo *infoArray)
{
    free(infoArray);
}

BOOL SetConsoleColor(WORD wAttributes)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE)
        return FALSE;

    return SetConsoleTextAttribute(hConsole, wAttributes);
}

void remove_last_space(char *str)
{
    int len = strlen(str);
    for (int i = len - 1; i >= 0; i--)
    {
        if (str[i] == ' ' || str[i] == '\n')
        {
            str[i] = '\0';
        }
        else
        {
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    char *ininame = "offsets.ini";
    if (argc < 2)
    {
        printf("ini needed.\n");
    }
    else
    {
        ininame = argv[1];
    }
    const char *filename = "offsets.h";
    const char *tempname = "temp.h";
    DefineInfo *infoArray;
    int count = parseDefines(filename, &infoArray);

    if (count > 0)
    {
        FILE *fp = fopen(tempname, "w");
        if (fp == NULL)
        {
            perror("fopen");
            return 1;
        }
        for (int i = 0; i < count; i++)
        {
            if (infoArray[i].commentPart[0] != '\0')
            {
                printf("--Define Name: %s\n", infoArray[i].defineName);
                printf("**Comment Part: %s\n", infoArray[i].commentPart);
                printf("**Arrow Part: %s\n", infoArray[i].arrowPart);
                remove_last_space(infoArray[i].commentPart);
                remove_last_space(infoArray[i].arrowPart);
                if (infoArray[i].plusPart[0] != '\0')
                {
                    remove_last_space(infoArray[i].plusPart);
                    if (infoArray[i].plusPart[0] != '-')
                    {
                        char plus[101] = "+ ";
                        strcat(plus, infoArray[i].plusPart);
                        strcpy(infoArray[i].plusPart, plus);
                    }
                    printf("**Plus Part: %s\n", infoArray[i].plusPart);
                }
                char buf[20] = {};
                int ok = GetIniKeyString(infoArray[i].commentPart, infoArray[i].arrowPart, ininame, buf);
                if (ok == 0)
                {
                    char offset[50];
                    strcpy(offset, buf);
                    strcat(offset, " ");
                    strcat(offset, infoArray[i].plusPart);
                    printf("[-!!-]value is: %s\n", buf);
                    // SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
                    // printf("#define %s\t%s %s\t// [%s]->%s %s\n", infoArray[i].defineName, buf, infoArray[i].plusPart, infoArray[i].commentPart, infoArray[i].arrowPart, infoArray[i].plusPart);
                    fprintf(fp, "#define %-25s\t%-20s\t\t// [%s]->%s %s\n", infoArray[i].defineName, offset, infoArray[i].commentPart, infoArray[i].arrowPart, infoArray[i].plusPart);
                    //  SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
                else
                {
                    char offset[10] = "err";
                    fprintf(fp, "#define %-25s\t%-20s\t\t// [%s]->%s %s\n", infoArray[i].defineName, offset, infoArray[i].commentPart, infoArray[i].arrowPart, infoArray[i].plusPart);
                }
            }

            printf("\n");
        }
        fclose(fp);
    }
    else
    {
        printf("No defined information found.\n");
    }
    freeDefineInfoArray(infoArray);
    getchar();
    return 0;
}
