#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <signal.h>

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

int sock;

void abstract_File(const char *filename);
void selectRows(const char *filename, const char *newname, const char *search);
void error_handling(char *msg);
void send_file(int server_socket, const char *file_path);
void *client_thread(void *arg);

int main(int argc, char *argv[])
{
    argc = 3;
    argv[1] = "10.10.20.102";
    argv[2] = "10006";
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <IP> <PORT>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serv_addr;
    char number[MAX_BUFFER_SIZE] = "1";
    sock = socket(PF_INET, SOCK_STREAM, 0);

    int num[MAX_LINES] = {
        0,
    };
    int max = 0, min, sum = 0, average = 0;
    char lines[MAX_LINES][MAX_LINE_LENGTH];
    int line_count = 0;

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
    selectRows("output.txt", "aseoul.txt", "서울");

    // 서버에 파일 전송
    send_file(sock, "aseoul.txt");
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
                    // send(sock, str[i], strlen(str[i]), 0);
                    // send(sock, " ", 1, 0);
                    fprintf(fp1, "%s, ", str[i]);
                }
                ptr = strtok(NULL, ",");
            }
            else
            {
                break;
            }
        }
        // send(sock, "\n", 1, 0);
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

    int Aver = average * 1.1;
    char a[50];
    char b[50];
    char c[50];
    char d[50];

    sprintf(a, "max = %d", max);
    sprintf(b, "min = %d", min);
    sprintf(c, "average = %d ", average);
    sprintf(d, "Aver = %d", Aver);

    fprintf(fp3, "\n%s/", a);
    fprintf(fp3, " %s/", b);
    fprintf(fp3, " %s/", c);
    fprintf(fp3, " %s/\n", d);

    send(sock, a, strlen(a), 0);
    send(sock, "/", 1, 0);
    send(sock, b, strlen(b), 0);
    send(sock, "/", 1, 0);
    send(sock, c, strlen(c), 0);
    send(sock, "/", 1, 0);
    send(sock, d, strlen(d), 0);
    send(sock, "/", 1, 0);
    send(sock, "\n", 1, 0);

    fclose(fp3);
    printf("최대값: %s/ 최소값: %s/ 평균값: %s/ 예상값: %s\n", a, b, c, d);

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
        signal(SIGPIPE, SIG_IGN);
    }
    fclose(file_to_send);

    //-----------------------------------------------------------------------------------------------
    //  FILE fp2 = fopen("2022_output.txt","rt");
    // if (fp2 == NULL) {
    //     perror("Error opening file");
    //     return 0;
    //     }
    // char str_tmp1[BUF_SIZE];
    // charstr1[BUF_SIZE];
    // char arr1[BUF_SIZE];
    // int k=0;

    // while(fgets(str_tmp1,sizeof(str_tmp1),fp2)!=NULL) {
    //     charptr1=strtok(str_tmp1,",");
    //     for (int i=0;i<4;i++) {
    //         if (ptr1!=NULL) {
    //             str1[i]=ptr1;
    //             if (i==3) {
    //                 arr1[k]=malloc(strlen(str1[i]) + 1);
    //                 strcpy(arr1[k],str1[i]);
    //                 // printf("%s",arr1[k]);
    //             }
    //             ptr1=strtok(NULL,",");
    //         } else {
    //             break;
    //         }
    //     }
    //     k++;
    // }

    // int firstValue=atoi(arr1[0]);
    // int j=0;
    // char buf[BUF_SIZE+1];
    // int min_value=firstValue;
    // int max_value=firstValue;
    // int sum=firstValue;
    // int current_value=0;
    // for(j=1;j<k;j++) {
    //     current_value=atoi(arr1[j]);
    //     if(current_value>max_value) {
    //         max_value=current_value;
    //     }

    //     if(current_value<min_value) {
    //         min_value=current_value;
    //     }

    //     sum+=current_value;
    // }

    // double average_value=(double)sum / k;

    // printf("\nMax: %d\n",max_value);
    // printf("Min: %d\n",min_value);
    // printf("Average: %.0lf\n",average_value);

    // send(sock,(char)&max_value, sizeof(int),0);
    // send(sock,(char)&min_value, sizeof(int),0);
    // send(sock,(char*)&average_value, sizeof(int),0);

    // for (int i=0;i<k;i++) {
    //     free(arr1[i]);
    // }
    // fclose(fp2);
    //------------------------------------------------------------------------------------------------
    shutdown(sock, SHUT_WR);
    close(sock);
    return 0;
}

void send_file(int server_socket, const char *file_path)
{
    char buffer[MAX_BUFFER_SIZE];
    FILE *file_to_send = fopen(file_path, "rt");

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
    shutdown(sock, SHUT_WR);
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