#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define PORT 10001
#define BUF_SIZE 100000
#define CLNT_MAX 11

#define TRUE 1
#define FALSE 0

int clnt_cnt = 0;
int clnt_socks[CLNT_MAX];

void error_handling(char *messeage);
void ReadToFile(const char *filename, const char *data);
void c_2022(void);
void python_2022(void);

pthread_mutex_t mutx;

void ReadToFile(const char *filename, const char *data)
{
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    if (fprintf(file, "%s", data) < 0)
    {
        perror("Error writing to file");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    // printf("%s", data);

    fclose(file);
}

void c_2022(void)
{
    char received_2022[BUF_SIZE];
    ssize_t recv2022_len;

    FILE *file = fopen("2022_item.txt", "w"); // 텍스트 파일을 쓰기 모드로 열기

    if (file == NULL)
    {
        error_handling("Error opening file");
    }

    while ((recv2022_len = recv(clnt_socks[0], received_2022, sizeof(received_2022), 0)) > 0)
    {
        received_2022[recv2022_len] = '\0';
        fprintf(file, "%s", received_2022);
        // printf("Received data from client: %s\n", received_2022);
    }
}

void python_2022(void)
{
    FILE *out_file;
    FILE *fp;
    fp = fopen("2022_item.txt", "rt"); // 파이썬 클라이언트한테 보내는 로직
    char buffer1[100000];
    char item[100000];
    while (fgets(buffer1, sizeof(buffer1), fp) != NULL)
    {
        strcat(item, buffer1);
    }

    fclose(fp);
    int item_len = strlen(item);
    int sent_len = send(clnt_socks[1], item, item_len, 0);
    if (sent_len != item_len)
    {
        error_handling("send() error");
    }
}

void *handle_c_clnt(void *arg)
{

    int clnt_sock = *((int *)arg);

    char buff[BUF_SIZE]; // 클라이언트의 데이터를 저장할 버퍼 설정
    ssize_t received;    // received라는 변수에 데이터의 크기를 저장

    while ((received = recv(clnt_sock, buff, sizeof(buff), 0)) > 0)
    {                          // 데이터가 0보다 클동안 계속 읽어옴
        buff[received] = '\0'; // 마지막 문자열에 널문자 추가
        pthread_mutex_init(&mutx, NULL);
        pthread_mutex_lock(&mutx);
        switch (clnt_cnt - 1)
        {
        case 0:
            ReadToFile("ASeoul.txt", buff); // received_file.txt 파일 생성
            break;
        case 1:
            ReadToFile("AGyeonggi.txt", buff); // received_file.txt 파일 생성
            break;
        case 2:
            ReadToFile("AGangwon.txt", buff); // received_file.txt 파일 생성
            break;
        case 3:
            ReadToFile("AGyeongbuk.txt", buff); // received_file.txt 파일 생성
            break;
        case 4:
            ReadToFile("AGyeongnam.txt", buff); // received_file.txt 파일 생성
            break;
        case 5:
            ReadToFile("AChungnam.txt", buff); // received_file.txt 파일 생성
            break;
        case 6:
            ReadToFile("AChungbuk.txt", buff); // received_file.txt 파일 생성
            break;
        case 7:
            ReadToFile("AJeonnam.txt", buff); // received_file.txt 파일 생성
            break;
        case 8:
            ReadToFile("AJeonbuk.txt", buff); // received_file.txt 파일 생성
            break;
        case 9:
            ReadToFile("AJeju.txt", buff); // received_file.txt 파일 생성
            break;

        default:
            break;
        }
        pthread_mutex_unlock(&mutx);
    }
}

int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;
    char message1[BUF_SIZE];
    char message2[BUF_SIZE];
    char message3[BUF_SIZE];
    char *arr[3];
    char *msgtxt, *fmsgtxt;
    int str_len;
    int j = 0;

    char where[BUF_SIZE];
    int i = 0;
    int optlen, option;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr1, clnt_addr2;
    socklen_t clnt_addr_size1, clnt_addr_size2;
    pthread_t t_idc, t_idp;

    argc = 2;
    argv[1] = "10000"; // 포트번호

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    pthread_mutex_init(&mutx, NULL);

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");

    optlen = sizeof(option);
    option = TRUE;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (void *)&option, optlen);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        error_handling("포트번호 바꾸라고!!");
    }

    if (listen(serv_sock, 2) == -1)
    {
        error_handling("listen() error");
    }
    else
    {
        printf("드루와 드루와\n");
    }
    while (1)
    {
        clnt_addr_size1 = sizeof(clnt_addr1);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr1, &clnt_addr_size1);
        if (clnt_sock == -1)
        {
            perror("accept() error");
        }
        pthread_mutex_lock(&mutx);
        clnt_socks[clnt_cnt] = clnt_sock;
        read(clnt_socks[clnt_cnt++], where, BUF_SIZE);
        pthread_mutex_unlock(&mutx);
        printf("%c", where[0]);

        switch (where[0])
        {
        case '1':
            printf("Connected client %d", clnt_cnt);
            pthread_create(&t_idc, NULL, handle_c_clnt, (void *)&clnt_sock);
            pthread_detach(t_idc);
            break;

        default:
            str_len = recv(clnt_sock, message1, BUF_SIZE, 0);
            message1[str_len] = 0;
            arr[0] = message1;
            str_len = recv(clnt_sock, message2, BUF_SIZE, 0);
            message2[str_len] = 0;
            arr[1] = message2;
            str_len = recv(clnt_sock, message3, BUF_SIZE, 0);
            message3[str_len] = 0;
            arr[2] = message3;

            // for(int j = 0 ; j < 3 ; j++)
            // {
            //     printf("%s", arr[j]);
            // }

            if (*arr[0] == '1')
            {
                switch (*arr[1])
                {
                case '0':
                    while (j < 3)
                    {
                        send(clnt_socks[0], arr[j], strlen(arr[j]), 0);
                        j++;
                        usleep(300000);
                    }
                    break;
                case '1':
                    while (j < 3)
                    {
                        send(clnt_socks[1], arr[j], strlen(arr[j]), 0);
                        j++;
                        sleep(1);
                    }
                    break;
                case '2':
                    while (j < 3)
                    {
                        send(clnt_socks[2], arr[j], strlen(arr[j]), 0);
                        j++;
                        sleep(1);
                    }
                    break;
                case '3':
                    while (j < 3)
                    {
                        send(clnt_socks[3], arr[j], strlen(arr[j]), 0);
                        j++;
                        sleep(1);
                    }
                    break;
                case '4':
                    while (j < 3)
                    {
                        send(clnt_socks[4], arr[j], strlen(arr[j]), 0);
                        j++;
                        sleep(1);
                    }
                    break;
                case '5':
                    while (j < 3)
                    {
                        send(clnt_socks[5], arr[j], strlen(arr[j]), 0);
                        j++;
                        sleep(1);
                    }
                    break;
                case '6':
                    while (j < 3)
                    {
                        send(clnt_socks[6], arr[j], strlen(arr[j]), 0);
                        j++;
                        sleep(1);
                    }
                    break;
                case '7':
                    while (j < 3)
                    {
                        send(clnt_socks[7], arr[j], strlen(arr[j]), 0);
                        j++;
                        sleep(1);
                    }
                    break;
                case '8':
                    while (j < 3)
                    {
                        send(clnt_socks[8], arr[j], strlen(arr[j]), 0);
                        j++;
                        sleep(1);
                    }
                    break;
                case '9':
                    while (j < 3)
                    {
                        send(clnt_socks[9], arr[j], strlen(arr[j]), 0);
                        j++;
                        sleep(1);
                    }
                    break;
                default:
                    break;
                }
                c_2022();
                python_2022();
            }
            else
            {
                switch (*arr[1])
                {
                case '0':
                    msgtxt = "ASeoul.txt";
                    fmsgtxt = "seoul_file_item.txt";
                    break;
                case '1':
                    msgtxt = "AGyeonggi.txt";
                    fmsgtxt = "gyeonggi_file_item.txt";
                    break;
                case '2':
                    msgtxt = "AGangwon.txt";
                    fmsgtxt = "gangwon_file_item.txt";
                    break;
                case '3':
                    msgtxt = "AGyeongbuk.txt";
                    fmsgtxt = "gyeongbuk_file_item.txt";
                    break;
                case '4':
                    msgtxt = "AGyeongnam.txt";
                    fmsgtxt = "gyeongnam_file_item.txt";
                    break;
                case '5':
                    msgtxt = "AChungnam.txt";
                    fmsgtxt = "chungnam_file_item.txt";
                    break;
                case '6':
                    msgtxt = "AChungbuk.txt";
                    fmsgtxt = "chungbuk_file_item.txt";
                    break;
                case '7':
                    msgtxt = "AJeonnam.txt";
                    fmsgtxt = "jeonnam_file_item.txt";
                    break;
                case '8':
                    msgtxt = "AJeonbuk.txt";
                    fmsgtxt = "jeonbuk_file_item.txt";
                    break;
                case '9':
                    msgtxt = "AJeju.txt";
                    fmsgtxt = "jeju_file_item.txt";
                    break;

                default:
                    break;
                }

                FILE *in_file = fopen(msgtxt, "r");
                FILE *seoul_file = fopen(fmsgtxt, "a");

                if (in_file == NULL || seoul_file == NULL)
                {
                    perror("파일 열기 오류");
                    if (in_file != NULL)
                        fclose(in_file);
                    if (seoul_file != NULL)
                        fclose(seoul_file);
                    exit(EXIT_FAILURE);
                }

                char buffer[1024];
                while (fgets(buffer, sizeof(buffer), in_file) != NULL) // received_file에서 단어 추출하는 로직
                {
                    if (strstr(buffer, arr[0]) != NULL && strstr(buffer, arr[2]) != NULL)
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

                FILE *fp = fopen(fmsgtxt, "rt"); // 보내는 로직
                char buffer1[1000000];
                char item[1000000];
                while (fgets(buffer1, sizeof(buffer1), fp) != NULL)
                {
                    strcat(item, buffer1);
                }

                fclose(fp);

                int item_len = strlen(item);
                int sent_len = send(clnt_sock, item, item_len, 0);
                if (sent_len != item_len)
                {
                    error_handling("send() error");
                }
                // int max_value, min_value;
                // double average_value;

                // recv(clnt_sock, (char *)&max_value, sizeof(int), 0);
                // recv(clnt_sock, (char *)&min_value, sizeof(int), 0);
                // recv(clnt_sock, (char *)&average_value, sizeof(double), 0);

                // printf("\nReceived from client:\n");
                // printf("Max: %d\n", max_value);
                // printf("Min: %d\n", min_value);
                // printf("Average: %.0lf\n", average_value);

                shutdown(clnt_sock, SHUT_WR);
                close(clnt_sock);
                remove(fmsgtxt);
                // break;
            }
        }
    }

    return 0;
}

void error_handling(char *messeage)
{
    fputs(messeage, stderr);
    fputc('\n', stderr);
    exit(1);
}