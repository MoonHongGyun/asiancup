#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>

#define MAX_BUFFER_SIZE 100000
#define MAX_LINE_SIZE 256
#define BUF_SIZE 100000
#define REGION_SIZE 20
#define MAX_LEN 100
#define MAX_LINES 1000
#define MAX_LINE_LENGTH 100
#define MAX_ELEMENTS 10000

// void abstract_File(const char *filename);
// void selectRows(int sock,const char *filename, const char *newname, char *search);
void error_handling(char *msg);

int main(int argc, char *argv[])
{

    argc = 3;
    argv[1] = "10.10.20.102";
    argv[2] = "10000";
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <IP> <PORT>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int sock;
    struct sockaddr_in serv_addr;
    char str[MAX_LEN];
    int num[MAX_LINES] = {
        0,
    };
    char number[MAX_BUFFER_SIZE] = "1";
    int max = 0, min, sum = 0, average = 0;
    char lines[MAX_LINES][MAX_LINE_LENGTH];
    int line_count = 0;

    sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error");

    write(sock, number, sizeof(number));

    // 광역시 안 함
    //  abstract_File("201301.txt");
    //  selectRows(sock,"output.txt","2013Seoul.txt","서울");

    char message1[BUF_SIZE];
    char message2[BUF_SIZE];
    char message3[BUF_SIZE];
    int str_len;
    char *arr[3];
    int i = 0;

    str_len = recv(sock, message1, BUF_SIZE, 0);
    message1[str_len] = 0;
    arr[0] = message1;

    str_len = recv(sock, message2, BUF_SIZE, 0);
    message2[str_len] = 0;
    arr[1] = message2;

    str_len = recv(sock, message3, BUF_SIZE, 0);
    message3[str_len] = 0;
    arr[2] = message3;

    printf("%s", arr[0]);
    printf("%s", arr[1]);
    printf("%s", arr[2]);

    FILE *in_file = fopen("202201.txt", "r");
    FILE *seoul_file = fopen("2022_item.txt", "w");

    if (in_file == NULL || seoul_file == NULL)
    {
        perror("파일 열기 오류");

        exit(EXIT_FAILURE);
    }

    char buffer[BUF_SIZE];
    while (fgets(buffer, sizeof(buffer), in_file) != NULL)
    {

        if (strstr(buffer, arr[0]) != NULL && strstr(buffer, arr[1]) != NULL && strstr(buffer, arr[2]) != NULL)
        {
            if (fprintf(seoul_file, "%s", buffer) < 0)
            {
                perror("Error writing to seoul_file");
                fclose(in_file);
                fclose(seoul_file);
                break;
            }
        }
    }
    fclose(in_file);
    fclose(seoul_file);

    FILE *fp = fopen("2022_item.txt", "rt");
    FILE *fp1 = fopen("2022_output.txt", "wt");

    char str_tmp[BUF_SIZE];
    char str1[15][BUF_SIZE];

    if (fp == NULL || fp1 == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    while (fgets(str_tmp, sizeof(str_tmp), fp) != NULL)
    {
        char *ptr = strtok(str_tmp, ",");
        for (int i = 0; i < 15; i++)
        {
            if (ptr != NULL)
            {
                strcpy(str1[i], ptr);
                if (i == 0 || i == 1 || i == 10 || i == 12)
                {
                    send(sock, str1[i], strlen(str1[i]), 0);
                    send(sock, " ", 1, 0);
                    fprintf(fp1, "%s,", str1[i]);
                }
                ptr = strtok(NULL, ",");
            }
            else
            {
                break;
            }
        }
        send(sock, "\n", 1, 0);
        fprintf(fp1, "\n");
    }

    fclose(fp);
    fclose(fp1);

    FILE *fp3 = fopen("2022_output.txt", "r");
    if (fp3 == NULL)
    {
        fprintf(stderr, "Error\n");
        exit(1);
    }

    while (fgets(lines[line_count], MAX_LINE_LENGTH, fp3) != NULL)
    {
        if (line_count < MAX_LINES - 1)
        {
            line_count++;
        }
        else
        {
            fprintf(stderr, "Error\n");
            break;
        }
    }
    for (int i = 0; i < line_count; i++)
    {
        char *token = strtok(lines[i], ",");
        int count = 0;

        while (token != NULL)
        {
            if (count == 3)
            {
                num[i] = atoi(token);
            }
            token = strtok(NULL, ",");
            count++;
        }
    }
    max = num[0];
    for (int i = 1; i < line_count; i++)
    {
        if (num[i] > max)
        {
            max = num[i];
        }
    }
    min = num[0];
    for (int i = 1; i < line_count; i++)
    {
        if (num[i] < min)
        {
            min = num[i];
        }
    }

    for (int i = 0; i < line_count; i++)
    {
        sum += num[i];
    }
    if (line_count > 0)
    {
        average = sum / line_count;
    }
    printf("최대값: %d/ 최소값: %d/ 평균값: %d\n", max, min, average);

    FILE *file_to_send = fopen("2022_output.txt", "rb");
    if (file_to_send == NULL)
    {
        perror("Error opening file for reading");
        return 1;
    }
    char buffer3[BUF_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer3, 1, sizeof(buffer3), file_to_send)) > 0)
    {
        send(sock, buffer3, bytes_read, 0);
    }
    fclose(file_to_send);
    close(sock);
    return 0;
}

// FILE *file_to_send = fopen("2022_output.txt", "rb");
// if (file_to_send == NULL) {
//     perror("Error opening file for reading");
//     return 1;
// }
// char buffer3[BUF_SIZE];
// size_t bytes_read;
// while ((bytes_read = fread(buffer3, 1, sizeof(buffer3), file_to_send)) > 0) {
//     send(sock, buffer3, bytes_read, 0);
// }
// fclose(file_to_send);
// close(sock);
// return 0;
// }

// void selectRows(int sock,const char *filename,const char *newname,char *search) {
//     FILE *file = fopen(filename, "r");
//     if (file == NULL) {
//         perror("Error opening file");
//         exit(EXIT_FAILURE);
//     }

//     FILE *outputFile = fopen(newname, "a");  // "seoul_data.txt" 파일을 쓰기 모드로 열기

//     if (outputFile == NULL) {
//         perror("Error opening output file");
//         exit(EXIT_FAILURE);
//     }
//     char buffer[BUF_SIZE];

//     while (fgets(buffer, sizeof(buffer), file) != NULL)

//     {
//         if (strstr(buffer, search) != NULL)
//         {
//             if (send(sock, buffer, strlen(buffer), 0) == -1) {
//                 perror("Send error");
//                 fclose(file);
//                 close(sock);
//                 exit(EXIT_FAILURE);
//             }
//         }
//     }

//     fclose(file);
//     fclose(outputFile);
// }

// // 날짜, 지역, 농수산식품, 가격 열을 추출한 후 새로운 파일(output.txt)로 저장
// void abstract_File(const char *filename) {
//     FILE *file = fopen(filename, "r");
//     if (file == NULL) {
//         perror("Error opening file");
//         exit(EXIT_FAILURE);
//     }

//     FILE *outputFile = fopen("output.txt", "w");  // "output.txt" 파일을 쓰기 모드로 열기

//     if (outputFile == NULL) {
//         perror("Error opening output file");
//         exit(EXIT_FAILURE);
//     }

//     char line[MAX_LINE_SIZE];
//     char *token;
//     int count = 0;  // Comma 개수 세는 count

//     while (fgets(line, sizeof(line), file) != NULL) {  // line 읽음
//         token = strtok(line, ",");  // comma에 의해 분리된 token 추출

//         while (token != NULL) {
//             count++;

//             // 1(날짜), 2(지역), 6(품목명), 7(품목코드), 15(가격)
//             if (count == 1 || count == 2 || count == 6 || count == 7 || count == 15) {

//                 fprintf(outputFile, "%s, ", token);  // 토큰 값을 파일에 쓰기
//             }
//             token = strtok(NULL, ",");
//         }

//         fprintf(outputFile, "\n");  // 한 줄 끝에 개행 추가
//         count = 0;

//     }

//     fclose(file);
//     fclose(outputFile);

// }

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}