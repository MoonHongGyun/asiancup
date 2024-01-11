#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>

#define PORT 12345
#define MAX_BUFFER_SIZE 1024
#define MAX_CLIENTS 10

void error_handling(char *message);

void *handle_client(void *arg);

int main() {
    int serv_sock;
    struct sockaddr_in serv_addr;
    pthread_t threads[MAX_CLIENTS];
    int client_socks[MAX_CLIENTS];
    int client_count = 0;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    while (1) {
        struct sockaddr_in clnt_addr;
        socklen_t clnt_addr_size = sizeof(clnt_addr);

        // 클라이언트의 접속을 기다림
        int clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        if (clnt_sock == -1)
            error_handling("accept() error");

        client_socks[client_count] = clnt_sock;

        // 클라이언트를 처리할 스레드 생성
        pthread_create(&threads[client_count], NULL, handle_client, (void *)&client_socks[client_count]);

        client_count++;
        if (client_count >= MAX_CLIENTS) {
            fprintf(stderr, "Maximum number of clients reached. No more connections will be accepted.\n");
            break;
        }
    }

    // 모든 스레드가 종료될 때까지 대기
    for (int i = 0; i < client_count; ++i) {
        pthread_join(threads[i], NULL);
    }

    // 소켓 닫기
    close(serv_sock);
    return 0;
}

// 클라이언트를 처리할 스레드 함수
void *handle_client(void *arg) {
    int clnt_sock = *((int *)arg);

    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_received;

    // 클라이언트로부터 데이터를 읽어오기
    while ((bytes_received = recv(clnt_sock, buffer, sizeof(buffer), 0)) > 0) {
        // 받은 데이터를 화면에 출력
        write(1, buffer, bytes_received);
    }

    close(clnt_sock);  // 클라이언트 소켓 닫기
    pthread_exit(NULL);
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
