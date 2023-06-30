/*ini.c*/
#include <stdio.h>
#include <string.h>
/*
 * 函数名：         GetIniKeyString
 * 入口参数：        title
 *                      配置文件中一组数据的标识
 *                  key
 *                      这组数据中要读出的值的标识
 *                  filename
 *                      要读取的文件路径
 * 返回值：         找到需要查的值则返回正确结果 0
 *                  否则返回-1
 */
int GetIniKeyString(char *title, char *key, char *filename, char *buf)
{
    FILE *fp;
    int flag = 0;
    char sTitle[64], *wTmp;
    char sLine[1024];
    sprintf(sTitle, "[%s]", title);

    if (NULL == (fp = fopen(filename, "r")))
    {
        perror("fopen");
        return -1;
    }
    while (NULL != fgets(sLine, 1024, fp))
    {
        // 这是注释行
        if (0 == strncmp("//", sLine, 2))
            continue;
        if ('#' == sLine[0])
            continue;
        wTmp = strchr(sLine, '=');
        if ((NULL != wTmp) && (1 == flag))
        {
            if (0 == strncmp(key, sLine, strlen(key)))
            { // 长度依文件读取的为准
                sLine[strlen(sLine) - 1] = '\0';
                fclose(fp);
                while (*(wTmp + 1) == ' ')
                {
                    wTmp++;
                }
                strcpy(buf, wTmp + 1);
                return 0;
            }
        }
        else
        {
            if (0 == strncmp(sTitle, sLine, strlen(sTitle)))
            {             // 长度依文件读取的为准
                flag = 1; // 找到标题位置
            }
        }
    }
    fclose(fp);
    return -1;
}

/*
 * 函数名：         PutIniKeyString
 * 入口参数：        title
 *                      配置文件中一组数据的标识
 *                  key
 *                      这组数据中要读出的值的标识
 *                  val
 *                      更改后的值
 *                  filename
 *                      要读取的文件路径
 * 返回值：         成功返回  0
 *                  否则返回 -1
 */
int PutIniKeyString(char *title, char *key, char *val, char *filename)
{
    FILE *fpr, *fpw;
    int flag = 0;
    char sLine[1024], sTitle[32], *wTmp;
    sprintf(sTitle, "[%s]", title);
    if (NULL == (fpr = fopen(filename, "r")))
        return -1; // 读取原文件
    sprintf(sLine, "%s.tmp", filename);
    if (NULL == (fpw = fopen(sLine, "w")))
        return -1; // 写入临时文件
    while (NULL != fgets(sLine, 1024, fpr))
    {
        if (2 != flag)
        { // 如果找到要修改的那一行，则不会执行内部的操作
            wTmp = strchr(sLine, '=');
            if ((NULL != wTmp) && (1 == flag))
            {
                if (0 == strncmp(key, sLine, strlen(key)))
                {             // 长度依文件读取的为准
                    flag = 2; // 更改值，方便写入文件
                    sprintf(wTmp + 1, " %s\n", val);
                }
            }
            else
            {
                if (0 == strncmp(sTitle, sLine, strlen(sTitle)))
                {             // 长度依文件读取的为准
                    flag = 1; // 找到标题位置
                }
            }
        }
        fputs(sLine, fpw); // 写入临时文件
    }
    fclose(fpr);
    fclose(fpw);
    sprintf(sLine, "%s.tmp", filename);
    return rename(sLine, filename); // 将临时文件更新到原文件
}
