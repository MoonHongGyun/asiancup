#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>
#include <fcntl.h>

// #define MAX_BUFFER_SIZE 1024
// #define MAX_LINE_SIZE 256
#define MAX_THREADS 10
#define MAX_BUFFER_SIZE 100000
#define MAX_LINE_SIZE 256
#define BUF_SIZE 100000
#define REGION_SIZE 20
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 100
#define MAX_LINES 1000
#define MAX_LINE_LENGTH 100

void abstract_File(const char *filename);
void selectRows(const char *filename, const char *newname, const char *search);
void error_handling(char *msg);
void send_file(int server_socket, const char *file_path);
void *client_thread(void *arg);

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
    char number[MAX_BUFFER_SIZE] = "1";
    sock = socket(PF_INET, SOCK_STREAM, 0);

    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error");

    write(sock, number, sizeof(number));

    abstract_File("201301.txt");
    selectRows("output.txt", "agyeongnam.txt", "경남");

    // 서버에 파일 전송
    send_file(sock, "agyeongnam.txt");
    remove("output.txt");
    //-------------------------------------------------------------------------------------------
    // 22년 데이터 찾기 및 최대 최소 평균값 보내는 로직
    // recv 서버에게 요청이 들어오면 데이터 찾아서 파일만들어서 데이터 넣고 파일로 서버에게 송신sand

    // 서버 요청사항(유저가 요청한)
    char message1[BUF_SIZE]; // 년도
    char message2[BUF_SIZE]; // 지역
    char message3[BUF_SIZE]; // 상품
    int str_len;             //
    char *arr[3];            // 년도, 지역, 상품 순으로
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

    // printf("%s", arr[0]);
    // printf("%s", arr[1]);
    // printf("%s", arr[2]);

    // 22년 파일열고
    FILE *in_file = fopen("202201.txt", "r");
    // 22년 요청사항 데이터 넣을 파일 만들고
    FILE *seoul_file = fopen("2022_item.txt", "w");
    if (in_file == NULL || seoul_file == NULL)
    {
        perror("파일 열기 오류");
        exit(EXIT_FAILURE);
    }
    switch (*arr[1])
    {
    case '0':
        arr[1] = "서울";
        break;
    case '1':
        arr[1] = "경기";
        break;
    case '2':
        arr[1] = "강원";
        break;
    case '3':
        arr[1] = "경북";
        break;
    case '4':
        arr[1] = "경남";
        break;
    case '5':
        arr[1] = "충남";
        break;
    case '6':
        arr[1] = "충북";
        break;
    case '7':
        arr[1] = "전남";
        break;
    case '8':
        arr[1] = "전북";
        break;
    case '9':
        arr[1] = "제주";
        break;

    default:
        break;
    }
    char buffer[BUF_SIZE];
    while (fgets(buffer, sizeof(buffer), in_file) != NULL)
    {
        if (strstr(buffer, arr[0]) != NULL && strstr(buffer, arr[1]) != NULL && strstr(buffer, arr[2]) != NULL)
        {
            if (fprintf(seoul_file, "%s", buffer) < 0)
            {
                perror("Error writing to file");
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

    // int read_size;
    // char str_tmp[BUF_SIZE];
    // char *str[BUF_SIZE];

    char str_tmp[BUF_SIZE];
    char str[15][BUF_SIZE];

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
                strcpy(str[i], ptr);
                if (i == 0 || i == 1 || i == 10 || i == 12)
                {
                    send(sock, str[i], strlen(str[i]), 0);
                    send(sock, " ", 1, 0);
                    fprintf(fp1, "%s,", str[i]);
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

    FILE *fp2 = fopen("2022_output.txt", "rt");
    FILE *outputFile2 = fopen("2022_price.txt", "a");

    if (fp2 == NULL || outputFile2 == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    char str_tmp1[BUF_SIZE];
    char *str1[BUF_SIZE];
    char *value5 = 0; // 단위
    char *value6 = 0; // 가격
    int value7 = 0;   // 평균

    while (fgets(str_tmp1, sizeof(str_tmp1), fp2) != NULL)
    {
        char *ptr1 = strtok(str_tmp1, ",");
        for (int i = 0; i < 5; i++)
        {
            str1[i] = ptr1;
            ptr1 = strtok(NULL, ",");
            if (i == 3)
                value5 = str1[i];
            if (i == 4)
            {
                value6 = str1[i];
                value7 = atoi(value6) / atoi(value5);
            }

            fprintf(outputFile2, "%d, ", value7);
        }
    }
    fclose(fp2);
    fclose(outputFile2);

    FILE *fp3 = fopen("2022_price.txt", "rt");

    if (fp3 == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    char buffer1[BUF_SIZE];

    if (fgets(buffer1, sizeof(buffer1), fp3) != NULL)
    {
        int firstValue = atoi(buffer1);
        int maxPrice = firstValue;
        int minPrice = firstValue;
        int sum = firstValue;
        int valueCount = 1;
        int result_values[4];
        double averagePrice;

        while (fgets(buffer1, sizeof(buffer1), fp3) != NULL)
        {
            int value = atoi(buffer1);

            if (value > maxPrice)
            {
                maxPrice = value;
            }

            if (value < minPrice)
            {
                minPrice = value;
            }
            sum += value;
            valueCount++;
        }

        fclose(fp3);

        if (valueCount > 0)
        {
            averagePrice = (double)sum / valueCount;
        }
        else
        {
            printf("오류\n");
        }
        FILE *fp5 = fopen("2022_output.txt", "a");
        if (fp5 == NULL)
        {
            perror("Error opening file");
            return 1;
        }
        // 수철이가 파일 보내줄 때(년도,지역,상품,가격만 있는 파일) 같이 보내달라해서 (최소,최대,평균,예상)파일에 씀
        fprintf(fp5, "\n%d/", maxPrice);
        fprintf(fp5, "%d/", minPrice);
        fprintf(fp5, "%.0f/", averagePrice);
        fprintf(fp5, "%.0f/", (averagePrice * 1.1));

        fclose(fp5);
    }
    else
        printf("오류.\n");

    // 파일에 썼으니 보내줌줌
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

    //-----------------------------------------------------------------------------------------------
    // }
    close(sock);
    return 0;
}

void send_file(int server_socket, const char *file_path)
{
    char buffer[MAX_BUFFER_SIZE];
    FILE *file_to_send = fopen(file_path, "rb");

    if (!file_to_send)
    {
        perror("Error opening file for reading");
        return;
    }

    ssize_t bytes_read;
    while ((bytes_read = fread(buffer, 1, MAX_BUFFER_SIZE, file_to_send)) > 0)
    {
        send(server_socket, buffer, bytes_read, 0);
    }
    fclose(file_to_send);
}

void abstract_File(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen("output.txt", "a"); // "output.txt" 파일을 쓰기 모드로 열기

    if (outputFile == NULL)
    {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_SIZE];
    char *token;
    int count = 0; // Comma 개수 세는 count

    while (fgets(line, sizeof(line), file) != NULL)
    {                              // line 읽음
        token = strtok(line, ","); // comma에 의해 분리된 token 추출

        while (token != NULL)
        {
            count++;

            // 1(날짜), 2(지역), 6(품목명), 7(품목코드), 15(가격)
            if (count == 1 || count == 2 || count == 6 || count == 7 || count == 15)
            {

                fprintf(outputFile, "%s, ", token); // 토큰 값을 파일에 쓰기
            }
            token = strtok(NULL, ",");
        }

        fprintf(outputFile, "\n"); // 한 줄 끝에 개행 추가
        count = 0;
    }

    fclose(file);
    fclose(outputFile);
}

void selectRows(const char *filename, const char *newname, const char *search)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen(newname, "a"); // "seoul_data.txt" 파일을 쓰기 모드로 열기

    if (outputFile == NULL)
    {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (strstr(buffer, search) != NULL)
        {
            if (fprintf(outputFile, "%s", buffer) < 0)
            {
                perror("파일쓰기오류");
                fclose(file);
                fclose(outputFile);
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(file);
    fclose(outputFile);
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
