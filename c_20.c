#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void PrintMap(int map[25][25]);
void Move(int map[25][25], int user_status[9], int itemBox[3], int *x, int *y, int *temp, int *walk, int *coin);
void OpenDoor(int map[25][25], int *walk);

int Fight(int *sta, int *partner, int *partner1_sta, int *partner2_sta, char *partner_name1, char *partner_name2, int *itemBoxchar, char *enemy_name, char *user_name, int monN, int *coin);
void attack(char *size, int *status, int partNum, int partnerSta1, int partenrSta2, char *partnerName, char *partnerName2, int attack1, char *enemy_name);
void attack_enemy(char *size, int *enemystatus, int enemyattack);
int MadePartner(int *partNum, int **partnerSta1, int **partnerSta2, char *partnerName, char *partnerName2, int *enemySta, char *enemy_name);
void S_attack(char *size, int *status, int partNum, int partnerSta1, int partnerSta2, char *partnerName, char *partnerName2, char *enemy_name);
void Item_Box(char *size, int *itembox, int *Bcount, int *status);
void Status_print(int *status, int *enemystatus, int *partnerNum, char *partnerName, char *partnerName2, int **partner1, int **partner2, char *enemyname, char *username);
int BossFight(int *sta, int *partner, int *partner1_sta, int *partner2_sta, char *partner_name1, char *partner_name2, int *itemBox, char *user_name);
int BossSpecial(void);
void Life_cure(char *size, int *status);
void Mana_cure(char *size, int *status);
void PrintDevmon(char *size, int monsterN);
void Sattack_enemy(char *size, int *enemystatus, char *enemy_name, int num);
void Shop(int *coin, int *status, int *itembox);
void printtext(char *size, int num);

void chapic(int n, int user_status[], char user_name[]);
void ShowPic(char *fp);
int QuizMon1(int score);
int QuizMon2(int score);
int QuizMon3(int score);
void Quiz(int score, int user_status[]);

int main(void)
{
    srand(time(NULL));
    int map[25][25] =
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 6, 6, 6, 6, 6, 1, 2, 2, 2, 2, 2, 1},
            {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 6, 6, 6, 6, 6, 1, 2, 2, 2, 2, 2, 1},
            {1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 6, 6, 1, 2, 2, 1, 2, 2, 1},
            {1, 2, 2, 2, 2, 2, 2, 2, 8, 1, 1, 1, 1, 6, 6, 6, 6, 6, 1, 2, 2, 1, 2, 2, 1},
            {1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 6, 6, 6, 6, 6, 1, 2, 2, 1, 2, 2, 1},
            {1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 2, 2, 1, 2, 2, 1},
            {1, 7, 7, 7, 7, 7, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1},
            {1, 7, 1, 1, 7, 7, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 8, 1, 2, 2, 1},
            {1, 7, 1, 11, 7, 7, 3, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1},
            {1, 7, 1, 1, 7, 7, 3, 2, 2, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1},
            {1, 7, 7, 7, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 10, 1, 0, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1},
            {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 9, 0, 0, 1, 1, 1, 1, 5, 5, 5, 5, 5, 1},
            {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 1, 2, 2, 3, 5, 5, 5, 5, 5, 1},
            {1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 5, 5, 5, 5, 5, 1},
            {1, 2, 2, 1, 8, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 1, 5, 5, 5, 5, 5, 1},
            {1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 1, 5, 5, 5, 5, 5, 1},
            {1, 2, 2, 1, 2, 2, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1},
            {1, 2, 2, 1, 2, 2, 1, 4, 4, 4, 4, 4, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
            {1, 2, 2, 1, 2, 2, 1, 4, 4, 4, 4, 4, 1, 1, 1, 1, 8, 2, 2, 2, 2, 2, 2, 2, 1},
            {1, 2, 2, 1, 2, 2, 1, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1},
            {1, 2, 2, 2, 2, 2, 1, 4, 4, 4, 4, 4, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
            {1, 2, 2, 2, 2, 2, 1, 4, 4, 4, 4, 4, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    char *place[8] = {"급식실", "벽", "복도", "문", "iot반", "드론융합실", "생산정보시스템실", "교수실"};
    char *monster[22] = {"현승몬", "규비몬", "수정몬", "수빈몬", "수연몬", "다능몬", "세정몬", "광선몬", "웅철몬", "인희몬", "하경몬", "민형몬", "병훈몬", "주현현몬", "용민몬", "홍균몬", "준호몬", "상호몬", "수철몬", "지우몬", "승범몬"};
    int user_status[9] = {1000, 50, 200, 270, 0, 000, 50, 1, 4};
    int itemBox[3] = {2, 2, 0};
    char *partner_name2 = " ";
    char *partner_name1 = " ";
    int partner = 0, partner1Sta = 1, partner2Sta = 1;
    char user_name[50];
    int coin = 100;
    char art[2000];

    int x = 12, y = 13;

    char input;
    int temp = 0;
    int walk = 0;
    int choose;

    int score = 0;
    int a;

    printtext(art, 7);
    printf("기본공격: 절반값~최대치까지 랜덤 공격\n특수공격: 고정값\n동료공격:1~최대치\n문은 50걸음 마다 열림(교수실은900)\n");
    printf("시작하시겠습니까? 1. 시작 2. 종료 ");
    scanf("%d", &a);
    system("clear");

    chapic(a, user_status, user_name);
    system("clear");

    while (1)
    {
        PrintMap(map);

        if (temp == 2 && (rand() % 100) < 15)
        {
            printf("야생의 개발몬이 튀어나왔다!\n");
            sleep(1);
            system("clear");
            int enemy = rand() % 21;
            char *enemy_name = monster[enemy];
            int Fc = Fight(user_status, &partner, &partner1Sta, &partner2Sta, partner_name1, partner_name2, itemBox, enemy_name, user_name, enemy, &coin);
            switch (Fc)
            {
            case 0:
            {
                user_status[0] = user_status[5];
                user_status[1] = user_status[6];
                map[y][x] = temp;
                temp = 0;
                x = 12, y = 13;
                map[y][x] = 9;
            }
            break;
            case 1:
                partner_name1 = enemy_name;
                break;
            case 2:
                partner_name2 = enemy_name;
            default:
                break;
            }
            system("clear");
            PrintMap(map);
        }
        else if (temp == 4 && rand() % 9 <= 0)
        {
            printf("iot반의 퀴즈단 리북녘이 승부를 걸어왔다!\n");
            sleep(1);
            system("clear");
            score = QuizMon1(score);
            Quiz(score, user_status);
            sleep(1);
            system("clear");
            PrintMap(map);
            if (score == 3 && map[22][12] == 3)
            {
                printf("쿠---쿵!!!\n");
                sleep(1);
                map[22][12] = 2;
                map[23][12] = 2;
                system("clear");
                PrintMap(map);
                printf("iot반의 문이 열렸다!\n");
                sleep(1);
            }
            system("clear");
            PrintMap(map);
            score = 0;
        }
        else if (temp == 5 && rand() % 9 <= 0)
        {
            printf("드론융합실의 퀴즈단 최하문이(가) 승부를 걸어왔다!\n");
            sleep(1);
            system("clear");
            score = QuizMon2(score);
            Quiz(score, user_status);
            sleep(1);
            system("clear");
            PrintMap(map);
            if (score == 3 && map[12][22] == 3)
            {
                printf("쿠---쿵!!!\n");
                sleep(1);
                map[12][22] = 2;
                map[12][23] = 2;
                system("clear");
                PrintMap(map);
                printf("드론융합실의 문이 열렸다!\n");
                sleep(1);
            }
            system("clear");
            PrintMap(map);
            score = 0;
        }
        else if (temp == 6 && rand() % 9 <= 0)
        {
            printf("생산정보시스팀실의 퀴즈단 류청걸이(가) 승부를 걸어왔다!\n");
            sleep(1);
            system("clear");
            score = QuizMon3(score);
            Quiz(score, user_status);
            sleep(1);
            system("clear");
            PrintMap(map);
            if (score == 3 && map[1][12] == 3)
            {
                printf("쿠---쿵!!!\n");
                sleep(1);
                map[1][12] = 2;
                map[2][12] = 2;
                system("clear");
                PrintMap(map);
                printf("생산정보시스템실의 문이 열렸다!\n");
                sleep(1);
            }
            system("clear");
            PrintMap(map);
            score = 0;
        }
        else if (temp == 11)
        {
            int BFc = BossFight(user_status, &partner, &partner1Sta, &partner2Sta, partner_name1, partner_name2, itemBox, user_name);
            switch (BFc)
            {
            case 0:
            {
                user_status[0] = user_status[5];
                user_status[1] = user_status[6];
                map[y][x] = 11;
                temp = 0;
                x = 12, y = 13;
                map[y][x] = 9;
            }
            case 10:
                system("clear");
                printtext(art, 8);
                printf("수료하였습니다!!!\n");
                break;
            default:
                break;
            }
            system("clear");
            PrintMap(map);
        }

        OpenDoor(map, &walk);

        printf("----------------------------------상태창-----------------------------------\n");
        printf("이름: %s    레벨: %d    경험치: %d/%d    걸음: %d     위치: %s\nHP: %d / %d    MP: %d / %d    공격력: %d    특수공격력: %d\n\n", user_name, user_status[7], user_status[4], user_status[8], walk / 2, place[temp], user_status[0], user_status[5], user_status[1], user_status[6], user_status[2], user_status[3]);
        printf("----------------------------------동료창-----------------------------------\n");
        printf("이름: %s    공격력: %d\n이름: %s    공격력: %d\n\n", partner_name1, partner1Sta, partner_name2, partner2Sta);
        printf("----------------------------------도구창-----------------------------------\n");
        printf("회복약: %d개    마나회복약: %d개    \n골드: %d\n\n", itemBox[0], itemBox[1], coin);
        printf("----------------------------------입력창-----------------------------------\n");
        printf("이동커맨드 'w':↑ , 'a':← , 's':↓ , 'd':→            *교실에서는 천천히*\n도구커맨드 'u':회복약, 'i':마나회복약\n'p': 상점\n\n입력: ");
        Move(map, user_status, itemBox, &x, &y, &temp, &walk, &coin);

        system("clear");
    }

    return 0;
}

void PrintMap(int map[25][25])
{
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            if (map[i][j] == 0)
                printf("   ");
            else if (map[i][j] == 1)
                printf("🟫 ");
            else if (map[i][j] == 2)
                printf("   ");
            else if (map[i][j] == 3)
                printf("🚪 ");
            else if (map[i][j] == 4)
                printf("   ");
            else if (map[i][j] == 5)
                printf("   ");
            else if (map[i][j] == 6)
                printf("   ");
            else if (map[i][j] == 7)
                printf("   ");
            else if (map[i][j] == 8)
                printf("🎁 ");
            else if (map[i][j] == 9)
                printf("🙅 ");
            else if (map[i][j] == 10)
                printf("👳 ");
            else if (map[i][j] == 11)
                printf("🤴 ");
        }
        printf("\n");
    }
}

void Move(int map[25][25], int user_status[9], int itemBox[3], int *x, int *y, int *temp, int *walk, int *coin)
{
    char input;
    scanf(" %c", &input);

    while (getchar() != '\n')
        ;

    map[*y][*x] = *temp;
    switch (input)
    {
    case 'w':
        if (map[*y - 1][*x] != 1 && map[*y - 1][*x] != 3)
        {
            (*y)--;
        }
        if (*walk < 300)
        {
            (*walk) += 2;
        }
        else
        {
            (*walk) += 8;
        }
        break;
    case 's':
        if (map[*y + 1][*x] != 1 && map[*y + 1][*x] != 3)
        {
            (*y)++;
        }
        if (*walk < 300)
        {
            (*walk) += 2;
        }
        else
        {
            (*walk) += 8;
        }
        break;
    case 'a':
        if (map[*y][*x - 1] != 1 && map[*y][*x - 1] != 3)
        {
            (*x)--;
        }
        if (*walk < 300)
        {
            (*walk) += 2;
        }
        else
        {
            (*walk) += 8;
        }
        break;
    case 'd':
        if (map[*y][*x + 1] != 1 && map[*y][*x + 1] != 3)
        {
            (*x)++;
        }
        if (*walk < 300)
        {
            (*walk) += 2;
        }
        else
        {
            (*walk) += 8;
        }
        break;
    case 'u':
        system("clear");
        map[*y][*x] = 9;
        PrintMap(map);
        map[*y][*x] = *temp;
        if (itemBox[0] >= 1)
        {
            user_status[0] += (user_status[5] / 2);
            if (user_status[0] > user_status[5])
            {
                user_status[0] = user_status[5];
            }
            itemBox[0] -= 1;
            printf("회복약을 사용했다!\n");
        }
        else
        {
            printf("회복약을 가지고 있지 않다!\n");
        }
        sleep(1);
        break;
    case 'i':
        system("clear");
        map[*y][*x] = 9;
        PrintMap(map);
        map[*y][*x] = *temp;
        if (itemBox[1] >= 1)
        {
            user_status[1] += (user_status[6] / 2);
            if (user_status[1] > user_status[6])
            {
                user_status[1] = user_status[6];
            }
            itemBox[1] -= 1;
            printf("마나회복약을 사용했다!\n");
        }
        else
        {
            printf("마나회복약을 가지고 있지 않다!\n");
        }
        sleep(1);
        break;
    case 'p':
        Shop(coin, user_status, itemBox);
        break;
    default:
        printf("올바른 입력이 아닙니다.\n");
    }

    *temp = map[*y][*x];

    if (*temp == 8)
    {
        system("clear");
        *temp = 2;
        map[*y][*x] = 9;
        PrintMap(map);
        int rand_item = rand() % 10;
        int rand_item2 = rand() % 10;
        if (rand_item == 0 || rand_item == 1 || rand_item == 2)
        {
            if (rand_item2 <= 2)
            {
                itemBox[0] += 1;
                printf("회복약 1개를 획득하였다!\n");
                sleep(1);
            }
            else if (rand_item2 >= 3 && rand_item2 <= 5)
            {
                itemBox[0] += 2;
                printf("회복약 2개를 획득하였다!\n");
                sleep(1);
            }
            else if (rand_item2 >= 6 && rand_item2 <= 7)
            {
                itemBox[0] += 3;
                printf("회복약 3개를 획득하였다!\n");
                sleep(1);
            }
            else if (rand_item == 8)
            {
                itemBox[0] += 4;
                printf("회복약 4개를 획득하였다!\n");
                sleep(1);
            }
            else
            {
                itemBox[0] += 5;
                printf("회복약 5개를 획득하였다!\n");
                sleep(1);
            }
        }
        else if (rand_item == 3 || rand_item == 4 || rand_item == 5)
        {
            if (rand_item2 <= 2)
            {
                itemBox[1] += 1;
                printf("마나회복약 1개를 획득하였다!\n");
                sleep(1);
            }
            else if (rand_item2 >= 3 && rand_item2 <= 5)
            {
                itemBox[1] += 2;
                printf("마나회복약 2개를 획득하였다!\n");
                sleep(1);
            }
            else if (rand_item2 >= 6 && rand_item2 <= 7)
            {
                itemBox[1] += 3;
                printf("마나회복약 3개를 획득하였다!\n");
                sleep(1);
            }
            else if (rand_item == 8)
            {
                itemBox[1] += 4;
                printf("마나회복약 4개를 획득하였다!\n");
                sleep(1);
            }
            else
            {
                itemBox[1] += 5;
                printf("마나회복약 5개를 획득하였다!\n");
                sleep(1);
            }
        }
        else
        {
            printf("아무것도 획득하지 못하였다!\n");
            sleep(1);
        }
        rand_item = 0;
        rand_item2 = 0;
        system("clear");
        PrintMap(map);
    }

    if (*temp == 10)
    {
        system("clear");
        user_status[0] = user_status[5];
        user_status[1] = user_status[6];
        (*y)++;
        *temp = 0;
        map[*y][*x] = 9;
        PrintMap(map);
        printf("회복되었습니다!\n");
        sleep(1);
        system("clear");
        PrintMap(map);
    }

    map[*y][*x] = 9;
}

void OpenDoor(int map[25][25], int *walk)
{
    switch (*walk)
    {
    case 100:
    {
        printf("쿠---쿵!!!\n");
        sleep(1);
        map[18][9] = 2;
        map[18][10] = 2;
        system("clear");
        PrintMap(map);
        printf("iot반의 문이 열렸다!\n");
        sleep(1);
        system("clear");
        PrintMap(map);
    }
    break;
    case 200:
    {
        printf("쿠---쿵!!!\n");
        sleep(1);
        map[14][18] = 2;
        map[15][18] = 2;
        system("clear");
        PrintMap(map);
        printf("드론융합실의 문이 열렸다!\n");
        sleep(1);
        system("clear");
        PrintMap(map);
    }
    break;
    case 300:
    {
        printf("쿠---쿵!!!\n");
        sleep(1);
        map[6][14] = 2;
        map[6][15] = 2;
        system("clear");
        PrintMap(map);
        printf("생산정보시스템실의 문이 열렸다!\n");
        printf("신비로운 힘에 의하여 걸음수가 1걸음당 4씩 올라간다!!!\n");
        sleep(1);
        system("clear");
        PrintMap(map);
    }
    break;
    case 1804:
    {
        printf("쿠---쿵!!!\n");
        sleep(1);
        map[9][6] = 2;
        map[10][6] = 2;
        system("clear");
        PrintMap(map);
        printf("교수실의 문이 열렸다!\n");
        sleep(1);
        system("clear");
        PrintMap(map);
    }
    break;
    }
}

int Fight(int *sta, int *partner, int *partner1_sta, int *partner2_sta, char *partner_name1, char *partner_name2, int *itemBox, char *enemy_name, char *user_name, int monN, int *coin) // 전투 메인 함수
{
    char *monster[22] = {"현승몬", "규비몬", "수정몬", "수빈몬", "수연몬", "다능몬", "세정몬", "광선몬", "웅철몬", "인희몬", "하경몬", "민형몬", "병훈몬", "주현몬", "용민몬", "홍균몬", "준호몬", "상호몬", "수철몬", "지우몬", "승범몬"};
    int turn = 1, run_turn = 0;
    char atk;
    int enemy_sta[4] = {200, 20, 20, 200};
    int enemyleveluphp = 0;
    int enemylevelupdmg = 0;
    char art[2000];
    // FILE *rfp;
    // FILE *rfp2;

    for (int i = 1; i <= sta[7]; i++)
    {
        if (i % 1 == 0)
        {
            enemyleveluphp += 1200;
            enemylevelupdmg += 100;
        }
    }

    enemy_sta[0] = rand() % 301 + 100 + enemyleveluphp;
    enemy_sta[1] = rand() % 51 + 80 + enemylevelupdmg;
    enemy_sta[2] = rand() % 71 + 80 + enemylevelupdmg;
    enemy_sta[3] = enemy_sta[0];

    while (1)
    {
        int attack_1 = -(rand() % (sta[2] - (sta[2] / 2))) + sta[2];
        int enemyattack = -(rand() % (enemy_sta[1] - (enemy_sta[1] / 2))) + enemy_sta[1];
        int partner1_attack = rand() % (*partner1_sta) + 1;
        int partner2_attack = rand() % (*partner2_sta) + 1;
        system("clear");
        int back_count = 0;
        PrintDevmon(art, monN);

        Status_print(sta, enemy_sta, partner, partner_name1, partner_name2, &partner1_sta, &partner2_sta, enemy_name, user_name);
        printf("1.공격 2.특수공격 3.도구상자 4.도망(10%%)\n번호를 입력하세요: ");
        scanf("%s", &atk);
        system("clear");
        if (atk == '1')
        { // 공격했을경우
            switch (*partner)
            {
            case 1:
                enemy_sta[0] = enemy_sta[0] - attack_1 - partner1_attack;
                break;
            case 2:
                enemy_sta[0] = enemy_sta[0] - attack_1 - partner1_attack - partner2_attack;
                break;
            default:
                enemy_sta[0] -= attack_1;
                break;
            }
            attack(art, sta, *partner, partner1_attack, partner2_attack, partner_name1, partner_name2, attack_1, enemy_name);
        }
        else if (atk == '2')
        { // 특수공격 햇을경우
            if (sta[1] > 9)
            {
                sta[1] -= 10;
                switch (*partner)
                {
                case 1:
                    enemy_sta[0] = enemy_sta[0] - sta[3] - partner1_attack;
                    break;
                case 2:
                    enemy_sta[0] = enemy_sta[0] - sta[3] - partner1_attack - partner2_attack;
                    break;
                default:
                    enemy_sta[0] -= sta[3];
                    break;
                }
                S_attack(art, sta, *partner, partner1_attack, partner2_attack, partner_name1, partner_name2, enemy_name);
            }
            else
            {
                printf("MP가 부족합니다. 특수공격을 사용할수 없습니다.\n");
                sleep(1);
                continue;
            }
        }
        else if (atk == '3')
        {
            Item_Box(art, itemBox, &back_count, sta);
            if (back_count != 0)
                continue;
        }
        else if (atk == '4')
        {
            if (run_turn == 0)
            {
                int run = rand() % 10;
                if (run == 1)
                {
                    printf("도망치는데 성공 했습니다.\n");
                    run_turn++;
                    sleep(1);
                    return 3;
                    break;
                }
                else
                {
                    printf("도망치치 못했습니다. 전투를 준비하세요...\n");
                    run_turn++;
                    sleep(1);
                    continue;
                }
            }
            else
            {
                printf("더이상 도망칠수 없습니다.\n");
                sleep(1);
                continue;
            }
        }
        else
            continue;

        if (enemy_sta[0] <= 0)
        {
            int made_p = MadePartner(partner, &partner1_sta, &partner2_sta, partner_name1, partner_name2, enemy_sta, enemy_name);
            system("clear");
            printtext(art, 1);
            printf("승리하였습니다!!!\n");
            printf("경험치를 획득했습니다.\n");
            int rand_coin = rand() % 6;
            printf("%d골드를 획득했다!!!\n", rand_coin);
            *coin += rand_coin;
            sta[4] += 1;
            sleep(1);
            if (sta[4] >= sta[8])
            {
                system("clear");
                sta[4] = 0;
                // sta[8]++;
                sta[7]++;
                sta[5] += rand() % 1501 + 400;
                // sta[6] += 10;
                sta[2] += rand() % 101 + 300;
                sta[3] += rand() % 201 + 500;
                sta[0] = sta[5];
                sta[1] = sta[6];
                printtext(art, 3);
                printf("레벨업!!!\n");
                sleep(1);
            }
            if (made_p == 0)
                return 1;
            else if (made_p == 1)
                return 2;
            else
                return 3;
            break;
        }

        PrintDevmon(art, monN);
        printf("---------------------------------------------------------------\n%s이 공격합니다...\n", enemy_name);
        sleep(1);
        system("clear");
        if (rand() % 3 == 0)
        { // 몬스터 공격
            Sattack_enemy(art, enemy_sta, enemy_name, monN);
            sta[0] -= enemy_sta[2];
        }
        else
        {
            sta[0] -= enemyattack;
            attack_enemy(art, enemy_sta, enemyattack);
        }

        if (sta[0] <= 0)
        {
            printtext(art, 2);
            printf("패배하였습니다!!!\n");
            sleep(1);
            return 0;
            break;
        }
    }
}

void attack(char *size, int *status, int partNum, int partnerSta1, int partnerSta2, char *partnerName, char *partnerName2, int attack1, char *enemy_name) // 기본 공격 컷씬
{
    FILE *rfp_attak_1;
    FILE *rfp_attack_2;
    char *attack_motion1, *attack_motion2;
    int randNum = rand() % 3;
    switch (randNum)
    {
    case 1:
        attack_motion1 = "attack_1", attack_motion2 = "attack_1.1";
        break;
    case 2:
        attack_motion1 = "attack_2", attack_motion2 = "attack_2.1";
        break;
    default:
        attack_motion1 = "attack_3", attack_motion2 = "attack_3.1";
        break;
    }
    int q = 0;
    while (q < 3)
    {
        rfp_attak_1 = fopen(attack_motion1, "rt");
        rfp_attack_2 = fopen(attack_motion2, "rt");
        while (fgets(size, 2000, rfp_attak_1) != NULL)
        {
            printf("%s", size);
        }
        puts("");

        fclose(rfp_attak_1);

        printf("\n");
        printf("%s에게 %d 만큼의 데미지를 입혔다!!!\n", enemy_name, attack1);
        switch (partNum)
        {
        case 1:
            printf("%s이 %s에게 %d 만큼의 데미지를 입혔다!!!\n", partnerName, enemy_name, partnerSta1);
            break;
        case 2:
            printf("%s이 %s에게 %d 만큼의 데미지를 입혔다!!!\n", partnerName, enemy_name, partnerSta1);
            printf("%s이 %s에게 %d 만큼의 데미지를 입혔다!!!\n", partnerName2, enemy_name, partnerSta2);
        default:
            break;
        }
        usleep(300000);
        system("clear");

        while (fgets(size, 2000, rfp_attack_2) != NULL)
        {
            printf("%s", size);
        }
        puts("");

        fclose(rfp_attack_2);
        printf("%s에게 %d 만큼의 데미지를 입혔다!!!\n", enemy_name, attack1);
        switch (partNum)
        {
        case 1:
            printf("%s이 %s에게 %d 만큼의 데미지를 입혔다!!!\n", partnerName, enemy_name, partnerSta1);
            break;
        case 2:
            printf("%s이 %s에게 %d 만큼의 데미지를 입혔다!!!\n", partnerName, enemy_name, partnerSta1);
            printf("%s이 %s에게 %d 만큼의 데미지를 입혔다!!!\n", partnerName2, enemy_name, partnerSta2);
        default:
            break;
        }
        usleep(300000);
        system("clear");
        q++;
    }
}
void attack_enemy(char *size, int *enemystatus, int enemyattack) // 적공격 컷씬
{
    FILE *rfp_e_attack1;
    FILE *rfp_e_attack2;
    int q = 0;
    while (q < 5)
    {
        rfp_e_attack1 = fopen("E1_attack_1", "rt");
        rfp_e_attack2 = fopen("E1_attack_1.1", "rt");
        while (fgets(size, 2000, rfp_e_attack1) != NULL)
        {
            printf("%s", size);
        }
        puts("");
        fclose(rfp_e_attack1);
        printf("%d 만큼의 데미지를 입었다!!!\n", enemyattack);
        usleep(200000);
        system("clear");
        while (fgets(size, 2000, rfp_e_attack2) != NULL)
        {
            printf("%s", size);
        }
        puts("");
        fclose(rfp_e_attack2);
        printf("%d 만큼의 데미지를 입었다!!!\n", enemyattack);
        usleep(200000);
        system("clear");
        q++;
    }
}

void Sattack_enemy(char *size, int *enemystatus, char *enemy_name, int num)
{
    char *enemySkill[3] = {"파이어브레스", "에너지볼트", "심판"};
    char *monN1;
    char *monN2;
    char *monN3;
    num = rand() % 3;
    switch (num)
    {
    case 0:
        monN1 = "1001", monN2 = "1002", monN3 = "1003";
        break;
    case 1:
        monN1 = "1011", monN2 = "1012", monN3 = "1013";
        break;
    default:
        monN1 = "1021", monN2 = "1022", monN3 = "1023";
        break;
    }
    int q = 0;
    while (q < 2)
    {
        FILE *E_satk_rfp1 = fopen(monN1, "rt");
        FILE *E_satk_rfp2 = fopen(monN2, "rt");
        FILE *E_satk_rfp3 = fopen(monN3, "rt");

        while (fgets(size, 2000, E_satk_rfp1) != NULL)
            printf("%s", size);
        printf("%s의 %s---\n %d만큼 데미지를 입었다.\n", enemy_name, enemySkill[num], enemystatus[2]);
        usleep(300000);
        fclose(E_satk_rfp1);
        system("clear");
        while (fgets(size, 2000, E_satk_rfp2) != NULL)
            printf("%s", size);
        printf("%s의 %s---\n %d만큼 데미지를 입었다.\n", enemy_name, enemySkill[num], enemystatus[2]);
        usleep(300000);
        fclose(E_satk_rfp2);
        system("clear");
        while (fgets(size, 2000, E_satk_rfp3) != NULL)
            printf("%s", size);
        printf("%s의 %s---\n %d만큼 데미지를 입었다.\n", enemy_name, enemySkill[num], enemystatus[2]);
        usleep(300000);
        fclose(E_satk_rfp3);
        system("clear");
        q++;
    }
}
void S_attack(char *size, int *status, int partNum, int partnerSta1, int partnerSta2, char *partnerName, char *partnerName2, char *enemy_name) // 특수공격 컷씬
{
    FILE *rfp_Sattack1;
    FILE *rfp_Sattack2;
    FILE *rfp_Sattack3;
    FILE *rfp_Sattack4;
    char *Sattack_motion1, *Sattack_motion2, *Sattack_motion3, *Sattack_motion4;
    int randNum = rand() % 3;
    switch (randNum)
    {
    case 1:
        Sattack_motion1 = "Sattack_2", Sattack_motion2 = "Sattack_2.1", Sattack_motion3 = "Sattack_2.2", Sattack_motion4 = "Sattack_2.3";
        break;
    case 2:
        Sattack_motion1 = "Sattack_3", Sattack_motion2 = "Sattack_3.1", Sattack_motion3 = "Sattack_3.2", Sattack_motion4 = "Sattack_3.3";
        break;
    default:
        Sattack_motion1 = "Sattack_1", Sattack_motion2 = "Sattack_1.1", Sattack_motion3 = "Sattack_1.2", Sattack_motion4 = "Sattack_1.3";
        break;
    }
    rfp_Sattack1 = fopen(Sattack_motion1, "rt");
    rfp_Sattack2 = fopen(Sattack_motion2, "rt");
    rfp_Sattack3 = fopen(Sattack_motion3, "rt");
    rfp_Sattack4 = fopen(Sattack_motion4, "rt");
    while (fgets(size, 2000, rfp_Sattack1) != NULL)
    {
        printf("%s", size);
    }
    puts("");
    fclose(rfp_Sattack1);
    printf("특수공격으로 %s에게 %d만큼 데미지를 입혔다.\n", enemy_name, status[3]);
    switch (partNum)
    {
    case 1:
        printf("%s이 %s에게 %d 만큼의 데미지를 입혔댜!!!\n", partnerName, enemy_name, partnerSta1);
        break;
    case 2:
        printf("%s이 %s에게 %d 만큼의 데미지를 입혔댜!!!\n", partnerName, enemy_name, partnerSta1);
        printf("%s이 %s에게 %d 만큼의 데미지를 입혔댜!!!\n", partnerName2, enemy_name, partnerSta2);
    default:
        break;
    }
    usleep(300000);
    system("clear");
    while (fgets(size, 2000, rfp_Sattack2) != NULL)
    {
        printf("%s", size);
    }
    puts("");
    fclose(rfp_Sattack2);
    printf("특수공격으로 %s에게 %d만큼 데미지를 입혔다.\n", enemy_name, status[3]);
    switch (partNum)
    {
    case 1:
        printf("%s이 %s에게 %d 만큼의 데미지를 입혔다!!!\n", partnerName, enemy_name, partnerSta1);
        break;
    case 2:
        printf("%s이 %s에게 %d 만큼의 데미지를 입혔다!!!\n", partnerName, enemy_name, partnerSta1);
        printf("%s이 %s에게 %d 만큼의 데미지를 입혔다!!!\n", partnerName2, enemy_name, partnerSta2);
    default:
        break;
    }
    usleep(300000);
    system("clear");
    while (fgets(size, 2000, rfp_Sattack3) != NULL)
    {
        printf("%s", size);
    }
    puts("");
    fclose(rfp_Sattack3);
    printf("특수공격으로 %s에게 %d만큼 데미지를 입혔다.\n", enemy_name, status[3]);
    switch (partNum)
    {
    case 1:
        printf("%s이 %s에게 %d 만큼의 데미지를 입혔다!!!\n", partnerName, enemy_name, partnerSta1);
        break;
    case 2:
        printf("%s이 %s에게 %d 만큼의 데미지를 입혔다!!!\n", partnerName, enemy_name, partnerSta1);
        printf("%s이 %s에게 %d 만큼의 데미지를 입혔다!!!\n", partnerName2, enemy_name, partnerSta2);
    default:
        break;
    }
    usleep(300000);
    system("clear");
    while (fgets(size, 2000, rfp_Sattack4) != NULL)
    {
        printf("%s", size);
    }
    puts("");
    fclose(rfp_Sattack4);
    printf("특수공격으로 %s에게 %d만큼 데미지를 입혔다.\n", enemy_name, status[3]);
    switch (partNum)
    {
    case 1:
        printf("%s이 %s에게 %d 만큼의 데미지를 입혔다!!!\n", partnerName, enemy_name, partnerSta1);
        break;
    case 2:
        printf("%s이 %s에게 %d 만큼의 데미지를 입혔다!!!\n", partnerName, enemy_name, partnerSta1);
        printf("%s이 %s에게 %d 만큼의 데미지를 입혔다!!!\n", partnerName2, enemy_name, partnerSta2);
    default:
        break;
    }
    sleep(1);
    system("clear");
}
int MadePartner(int *partNum, int **partnerSta1, int **partnerSta2, char *partnerName, char *partnerName2, int *enemySta, char *enemy_name) // 동료 만들기
{
    char *monster[22] = {"현승몬", "규비몬", "수정몬", "수빈몬", "수연몬", "다능몬", "세정몬", "광선몬", "웅철몬", "인희몬", "하경몬", "민형몬", "병훈몬", "주현몬", "용민몬", "홍균몬", "준호몬", "상호몬", "수철몬", "지우몬", "승범몬"};
    char n;
    switch (*partNum)
    {
    case 0:
        printf("이름 : %s\n공격력 : %d\n", enemy_name, enemySta[1]);
        printf("%s를 영입하겠습니까???\n1. 네  2,아니오: ", enemy_name);
        scanf("%s", &n);
        if (n == '1')
        {
            (*partNum)++;
            **partnerSta1 = enemySta[1];
            return 0;
        }
        break;
    case 1:
        printf("이름 : %s\n공격력 : %d\n", enemy_name, enemySta[1]);
        printf("%s를 영입하겠습니까???\n1. 네  2.아니오: ", enemy_name);
        scanf("%s", &n);
        if (n == '1')
        {
            (*partNum)++;
            **partnerSta2 = enemySta[1];
            return 1;
        }
        break;
    case 2:
        printf("이름 : %s\n공격력 : %d\n", enemy_name, enemySta[1]);
        printf("--------------------------------------------");
        printf("내 동료\n1.%s  공격력 %d\n2.%s  공격력 %d\n", partnerName, **partnerSta1, partnerName2, **partnerSta2);
        printf("%s를 영입하겠습니까???\n1. 네  2,아니오: ", enemy_name);
        scanf("%s", &n);
        if (n == '1')
        {
            printf("누구와 교체하시겠습니까??\n번호를 입력해주세요: ");
            scanf("%s", &n);
            if (n == '1')
            {
                **partnerSta1 = enemySta[1];
                return 0;
            }
            else if (n == '2')
            {
                **partnerSta2 = enemySta[1];
                return 1;
            }
        }
        break;
    default:
        break;
    }
}
void Item_Box(char *size, int *itembox, int *Bcount, int *status) // 도구상자
{
    int turn = 0;
    char select;
    while (select != '0')
    {
        system("clear");
        FILE *rfp_box;
        rfp_box = fopen("itembox", "rt");
        while (fgets(size, 2000, rfp_box) != NULL)
        {
            printf("%s", size);
        }
        puts("");
        fclose(rfp_box);
        printf("0. 뒤로가기\n1.회복약 = %d개\n2.마나회복약 = %d개\n사용하실 아이템의 번호를 입력해주세요: ", itembox[0], itembox[1]);
        scanf("%s", &select);
        switch (select)
        {
        case '0':
            *Bcount += 1;
            break;
        case '1':
            if (itembox[0] == 0)
            {
                printf("사용할 아이템이 없습니다.\n");
                sleep(1);
                break;
            }
            else
            {
                system("clear");
                Life_cure(size, status);
                status[0] += (status[5] / 2);
                if (status[0] > status[5])
                {
                    status[0] = status[5];
                }
                itembox[0] -= 1;
                turn++;
                break;
            }
        case '2':
            if (itembox[1] == 0)
            {
                printf("사용할 아이템이 없습니다.\n");
                sleep(1);
                break;
            }
            else
            {
                system("clear");
                Mana_cure(size, status);
                status[1] += (status[6] / 2);
                if (status[1] > status[6])
                    status[1] = status[6];
                itembox[1]--;
                turn++;
            }
        default:
            break;
        }
        if (turn != 0)
        {
            system("clear");
            break;
        }
    }
}

void Status_print(int *status, int *enemystatus, int *partnerNum, char *partnerName, char *partnerName2, int **partner1, int **partner2, char *enemyname, char *username) // 스텟 프린트
{
    printf("----------%s----------\n", username);
    printf("레벨: %d\nHP: %d / %d    MP: %d / %d    공격력: %d    특수공격력: %d\n", status[7], status[0], status[5], status[1], status[6], status[2], status[3]);
    if (*partnerNum == 1)
        printf("%s -- 공격력: %d\n", partnerName, **partner1);
    else if (*partnerNum == 2)
    {
        printf("%s -- 공격력: %d\n", partnerName, **partner1);
        printf("%s -- 공격력: %d\n", partnerName2, **partner2);
    }
    printf("----------%s----------\n", enemyname);
    printf("HP: %d / %d    공격력: %d    특수공격력: %d\n", enemystatus[0], enemystatus[3], enemystatus[1], enemystatus[2]);
    printf("*************************************************\n");
}

int BossFight(int *sta, int *partner, int *partner1_sta, int *partner2_sta, char *partner_name1, char *partner_name2, int *itemBox, char *user_name) // 보스 전투 메인 함수
{
    int turn = 1, run_turn = 0;
    char atk;
    int enemy_sta[4] = {50000, 2023, 3000, 50000};
    char art[2000];
    FILE *boss_rfp;

    while (1)
    {
        int attack_1 = -(rand() % (sta[2] - (sta[2] / 2))) + sta[2];
        int boss_attack = rand() % 1924 + 100;
        int partner1_attack = rand() % (*partner1_sta);
        int partner2_attack = rand() % (*partner2_sta);
        system("clear");
        int back_count = 0;
        boss_rfp = fopen("boss", "rt");

        while (fgets(art, 2000, boss_rfp) != NULL)
        { // 첫번째 턴
            printf("%s", art);
        }
        puts("");
        fclose(boss_rfp);
        Status_print(sta, enemy_sta, partner, partner_name1, partner_name2, &partner1_sta, &partner2_sta, "리상복", user_name);
        printf("1.공격 2.특수공격 3.도구상자 \n번호를 입력하세요: ");
        scanf("%s", &atk);
        system("clear");
        if (atk == '1')
        { // 공격했을경우
            switch (*partner)
            {
            case 1:
                enemy_sta[0] = enemy_sta[0] - attack_1 - partner1_attack;
                break;
            case 2:
                enemy_sta[0] = enemy_sta[0] - attack_1 - partner1_attack - partner2_attack;
                break;
            default:
                enemy_sta[0] -= attack_1;
                break;
            }
            attack(art, sta, *partner, partner1_attack, partner2_attack, partner_name1, partner_name2, attack_1, "리상복");
        }
        else if (atk == '2')
        { // 특수공격 햇을경우
            if (sta[1] > 0)
            {
                sta[1]--;
                switch (*partner)
                {
                case 1:
                    enemy_sta[0] = enemy_sta[0] - sta[3] - partner1_attack;
                    break;
                case 2:
                    enemy_sta[0] = enemy_sta[0] - sta[3] - partner1_attack - partner2_attack;
                    break;
                default:
                    enemy_sta[0] -= sta[3];
                    break;
                }
                S_attack(art, sta, *partner, partner1_attack, partner2_attack, partner_name1, partner_name2, "리상복");
            }
            else
            {
                printf("MP가 부족합니다. 특수공격을 사용할수 없습니다.\n");
                sleep(1);
                continue;
            }
        }
        else if (atk == '3')
        {
            Item_Box(art, itemBox, &back_count, sta);
            if (back_count != 0)
                continue;
        }
        else
            continue;

        if (enemy_sta[0] <= 0)
        { // 중간 결과
            break;
            return 10;
        }
        if (enemy_sta[0] < 5000)
        { // 보스 체력회복
            int iceTea = rand() % 10;
            if (iceTea == 0 || iceTea == 1 || iceTea == 2)
            {
                printf("보스가 아이스티를 마시고 피 5000을 회복했다./n");
                sleep(1);
                enemy_sta[0] += 5000;
            }
        }

        boss_rfp = fopen("poketmon_2", "rt"); // 세번째
        while (fgets(art, 2000, boss_rfp) != NULL)
        {
            printf("%s", art);
        }
        puts("");
        fclose(boss_rfp);
        printf("---------------------------------------------------------------\n리상복이 공격합니다...\n");
        sleep(1);
        system("clear");
        int BA;
        int BossAttack = rand() % 2; // 보스 특수공격
        if (BossAttack == 1)
        {
            printf("보스가 특수스킬을 사용했다!!!");
            BA = BossSpecial();
            if (BA == 1)
            {
                attack_enemy(art, enemy_sta, enemy_sta[2]);
                sta[0] -= enemy_sta[2];
            }
            else if (BA == 2)
            {
                attack_enemy(art, enemy_sta, enemy_sta[2]);
                sta[0] -= enemy_sta[2];
            }
            else
            {
                printf("공격을 방어했습니다.\n");
                sleep(1);
                system("clear");
            }
        }
        else
        { // 보스 일반공격
            sta[0] -= boss_attack;
            attack_enemy(art, enemy_sta, boss_attack);
        }
        if (sta[0] <= 0)
        { // 결과
            return 0;
            break;
        }
    }
}
int BossSpecial(void)
{
    int num = rand() % 2;
    switch (num)
    {
    case 0:
    {
        printf("가위바위보 대결!\n1.보스에게서 승리하면 공격을 막을수있다.\n2.보스에게서 패배하면 많은 데미지를 입는다.\n3.비기면 재대결\n");
        sleep(6);
        int G1_user, G1_pc;
        int G1_win = 0, G1_lose = 0;

        while (G1_lose == 0 && G1_win == 0)
        {
            system("clear");
            printf("바위는 1, 가위는 2,보는 3: ");
            scanf("%d", &G1_user);
            G1_pc = (rand() % 3) + 1;

            if (G1_user == 1)
            {
                switch (G1_pc)
                {
                case 1:
                    printf("당신은 바위 선택, 컴퓨터는 바위 선택, 비겼습니다!\n");
                    break;
                case 2:
                    printf("당신은 바위 선택, 컴퓨터는 가위 선택, 이겼습니다!\n");
                    sleep(1);
                    G1_win++;
                default:
                    printf("당신은 바위 선택, 컴퓨터는 보 선택, 졌습니다!\n");
                    G1_lose++;
                    sleep(1);
                    break;
                }
            }
            else if (G1_user == 2)
            {
                switch (G1_pc)
                {
                case 1:
                    printf("당신은 가위 선택, 컴퓨터는 바위 선택, 졌습니다!\n");
                    G1_lose++;
                    sleep(1);
                    break;
                case 2:
                    printf("당신은 가위 선택, 컴퓨터는 가위 선택, 비겼습니다!\n");
                default:
                    printf("당신은 가위 선택, 컴퓨터는 보 선택, 이겼습니다!\n");
                    G1_win++;
                    sleep(1);
                    break;
                }
            }
            else if (G1_user == 3)
            {
                switch (G1_pc)
                {
                case 1:
                    printf("당신은 보 선택, 컴퓨터는 바위 선택, 이겼습니다!\n");
                    G1_win++;
                    sleep(1);
                    break;
                case 2:
                    printf("당신은 보 선택, 컴퓨터는 가위 선택, 졌습니다!\n");
                    G1_lose++;
                    sleep(1);
                default:
                    printf("당신은 보 선택, 컴퓨터는 보 선택, 비겼습니다!\n");
                    break;
                }
            }
        }
        if (G1_win == 1)
            return 0;
        else
            return 1;
        break;
    }
    default:
        printf("강타!!!\n");
        sleep(1);
        system("clear");
        return 2;
        break;
    }
}

void Life_cure(char *size, int *status)
{
    FILE *life_rfp1;
    FILE *life_rfp2;
    FILE *life_rfp3;

    int q = 0;
    while (q < 2)
    {
        life_rfp1 = fopen("HP_recovery1", "rt");
        life_rfp2 = fopen("HP_recovery1.1", "rt");
        life_rfp3 = fopen("HP_recovery1.2", "rt");

        while (fgets(size, 2000, life_rfp1) != NULL)
        {
            printf("%s", size);
        }
        puts("");
        fclose(life_rfp1);
        printf("회복약을 사용하여 %d만큼 회복하였습니다.\n", status[5] / 2);
        usleep(300000);
        system("clear");
        while (fgets(size, 2000, life_rfp2) != NULL)
        {
            printf("%s", size);
        }
        puts("");
        fclose(life_rfp2);
        printf("회복약을 사용하여 %d만큼 회복하였습니다.\n", status[5] / 2);
        usleep(300000);
        system("clear");
        while (fgets(size, 2000, life_rfp3) != NULL)
        {
            printf("%s", size);
        }
        puts("");
        fclose(life_rfp3);
        printf("회복약을 사용하여 %d만큼 회복하였습니다.\n", status[5] / 2);
        usleep(300000);
        system("clear");
        q++;
    }
}

void Mana_cure(char *size, int *status)
{
    FILE *life_rfp1;
    FILE *life_rfp2;
    FILE *life_rfp3;

    int q = 0;
    while (q < 2)
    {
        life_rfp1 = fopen("HP_recovery1", "rt");
        life_rfp2 = fopen("HP_recovery1.1", "rt");
        life_rfp3 = fopen("HP_recovery1.2", "rt");

        while (fgets(size, 2000, life_rfp1) != NULL)
        {
            printf("%s", size);
        }
        puts("");
        fclose(life_rfp1);
        printf("회복약을 사용하여 %d만큼 회복하였습니다.\n", status[6] / 2);
        usleep(300000);
        system("clear");
        while (fgets(size, 2000, life_rfp2) != NULL)
        {
            printf("%s", size);
        }
        puts("");
        fclose(life_rfp2);
        printf("회복약을 사용하여 %d만큼 회복하였습니다.\n", status[6] / 2);
        usleep(300000);
        system("clear");
        while (fgets(size, 2000, life_rfp3) != NULL)
        {
            printf("%s", size);
        }
        puts("");
        fclose(life_rfp3);
        printf("회복약을 사용하여 %d만큼 회복하였습니다.\n", status[6] / 2);
        usleep(300000);
        system("clear");
        q++;
    }
}

void chapic(int n, int user_status[], char user_name[])
{
    if (n == 1)
        printf("캐릭터의 이름을 입력하세요(15자 이하로): ");
    else
        exit(1);

    scanf("%s", user_name);

    // printf("\n선택하신 캐릭터의 이름은 %s입니다. 스탯창을 띄워드립니다! \n", user_name);
    // printf("================================================================= \n");

    user_status[0] = rand() % 401 + 1800;
    user_status[2] = rand() % 201 + 400;
    user_status[3] = rand() % 401 + 500;

    // printf("hp : %d  mp : %d  공격력 : %d  특수 공격력 : %d  경험치 %d 레벨 %d \n", user_status[0], user_status[1], user_status[2], user_status[3], user_status[4], user_status[7]);
    user_status[5] = user_status[0];
    user_status[6] = user_status[1];
}

// void ShowPic(char *fn)
// {
//     FILE *fp; // 1. 파일 포인터 선언
//     char name[1000];
//     fp = fopen(fn, "r"); // 2. 파일 열기(읽기 모드)

//     while ((fgets(name, 50, fp) != NULL)) // 3. 파일 입출력 : 파일 끝에 도달할 때까지 읽기
//         printf("%s", name);               // 레코드의 끝에 이미 '\n'이 저장되어 있어 개행문자를 넣지 않아도 됨
//     fclose(fp);
// }

int QuizMon1(int score)
{
    char art[2000];
    system("clear");
    char st[50];
    // printtext(art, 4);
    printf("앗! iot 반에서 야생의 \"리북녁\" 퀴즈단을 만났다!\n");
    printf("퀴즈 하나당 경험치를 획득할 수 있고, 퀴즈를 모두 맞히면 hp를 풀로 충전해주겠다! 하지만 퀴즈를 모두 틀리면 hp는 50프로가 차감된다! \n");

    char *quiz1[7] = {"우리나라의 8.15 광복은 몇년도일까요?\n1. 1930 2. 1940 3. 1943 4. 1945 ", "빗살무늬토기는 어느 시대의 유물일까요? \n1. 석기 시대 2. 신석기 시대 3. 철기 시대 4. 청동기 시대 ", "신조어 분좋카의 뜻은?\n1. 분위기 좋은 카플 2.분말 좋은 카레 3. 분위기 좋은 카페 4. 분위기 좋게 나오는 카메라 ", "00은 게편 00에 들어갈 단어는?\n1. 조개 2. 황새 3. 가재 4. 소라 ", "흑인이 울면?\n1. 흑흑 2. 흑인은 울지 않는다. 3. 블랙 4. 흙흙 ", "투표를 영어로? \n1. Choice 2. Pick 3. Cast 4. Vote ", "주식에서 소액을 운용하는 일반 투자자를 뭐라고 부를까요? \n1.베짱이 2. 개미 3. 독수리 4. 바퀴벌레 "};
    int answer1[7] = {4, 2, 3, 3, 1, 4, 2};
    int a, b[3] = {10, 10, 10};

    printf("\n지금부터 퀴즈를 출제하겠다! \n");
    for (int i = 0; i < 3; i++)
    {
        char *c;
        printf("\n%d 번째 퀴즈! \n", i + 1);
        int n = rand() % 7;
        while (1)
        {
            if (n == b[0] || n == b[1])
                n = rand() % 7;
            else
                break;
        }
        printf("%s", quiz1[n]);
        scanf("%s", &c);
        a = (int)c;
        b[i] = a;
        if (b[i] == answer1[n])
            score++;
        if (n == 4)
            printf("틀렸습니다. 흑인도 울면 슬프죠.. 흑인은 흑흑하고 울지 않습니다. 인종차별주의자세요? \n");
    }
    system("clear");
    return score;
}
int QuizMon2(int score)
{
    system("clear");
    char art[2000];
    char st[50];
    printtext(art, 5);
    printf("앗! 드론융합실에서 야생의 \"최하문\" 퀴즈단을 만났다!\n");
    printf("퀴즈 하나당 경험치를 획득할 수 있고, 퀴즈를 모두 맞히면 hp를 풀로 충전해주겠다! 하지만 퀴즈를 모두 틀리면 hp는 50프로가 차감된다! \n");

    char *quiz2[8] = {"어린이보호구역에서 속도제한은 몇 km일까요? \n1. 40km 2. 35km 3. 45km 4. 30km ", "물티슈의 영어표기로 알맞은 것은? \n1. water tissue 2. hand tissue 3. wet tissue 4. wash tissue ", "국가의 3요소가 아닌 것은? \n1. 영토 2. 군주 3. 주권 4. 국민 ", "다음중 금관 악기가 아닌 것은?\n1. 오보에 2. 프렌치 호른 3. 튜바 ", "5천원권 지폐에 있는 과일은?\n1. 복숭아 2. 배 3. 포도 4. 수박 ", "다음중 \"뽀짝\"의 뜻은?\n 1. 가깝다. 2. 귀엽다 3. 마르다 4. 작다 ",
                      "다음 말의 올바른 뜻은? \"야 내가 왕년에 오락실에서 ~~찌까비~~ 좀 썼다지! \n1. 동전 2. 주먹 3. 꼼수 4. 실력 발휘 ", "다음중 택시 문을 너무 세게 닫고 탔을 경우 충청도 택시 기사님이 할 말은? \n1. 살살 좀 닫는건 워떠유~ 2. 뭔 화나는 일 있슈~? 3. 어디 가시길래 맘이 급하셔~? 4.아유 그렇게 해서 부서지겠슈~? "};
    int answer2[8] = {4, 3, 2, 1, 4, 1, 3, 4};
    int a, b[3];

    printf("\n지금부터 퀴즈를 출제하겠다! \n");
    for (int i = 0; i < 3; i++)
    {
        char *c;
        printf("\n%d 번째 퀴즈! \n", i + 1);
        int n = rand() % 7;
        while (1)
        {
            if (n == b[0] || n == b[1])
                n = rand() % 7;
            else
                break;
        }
        printf("%s", quiz2[n]);
        scanf("%s", &c);
        a = (int)c;
        b[i] = a;
        if (b[i] == answer2[n])
            score++;
    }
    system("clear");
    return score;
}

int QuizMon3(int score)
{
    char art[2000];
    printtext(art, 6);
    system("clear");
    char st[50];
    printtext(art, 6);
    printf("앗! 생산정보시스템실에서 야생의 \"류청걸\" 퀴즈단을 만났다!\n");
    printf("퀴즈 하나당 경험치를 획득할 수 있고, 퀴즈를 모두 맞히면 hp를 풀로 충전해주겠다! 하지만 퀴즈를 모두 틀리면 hp는 50프로가 차감된다! \n");

    char *quiz3[6] = {"군대 계급도를 맞춰보세요 1.\n1. 소위-중사-중령 2. 상사-소령-하사 3.하사-원사-대위 4. 준장-소장-소령 ", "다음중 뿌리식물(채소)가 아닌것은?\n1. 비트 2. 땅콩 3. 우엉 4. 생강 ", "다음중 동계 올림픽 종목이 아닌것은?\n1. 스키점프 2. 트라이애슬론 3. 스켈레톤 4. 노르딕 복합 ", "이번주 조병훈은 머리를 자르러 간다. 과연 조병훈이 해올 머리스타일은?\n1. 손흥민 머리 2. 삼묵컷 3. 홍균이형이 추천해준 머리 4. 아줌마 그냥 단정하게 해주세요. ",
                      "다음 중 이 말이 뜻하는 바는? \"가가 가가가?\"\n1. 그 애가 그 애니? 2. 그아이가 성이 가씨니? 3. 가라! 가서 가져가렴! ", "다음 중 화장품 이름이 아닌 것은?\n1. 품절대란 2. 심쿵유발 3. 감탄연발 4. 미모폭발 "};
    int answer3[6] = {3, 2, 2, 1, 2, 4};
    int a, b[3];

    printf("\n지금부터 퀴즈를 출제하겠다! \n");
    for (int i = 0; i < 3; i++)
    {
        char *c;
        printf("\n%d 번째 퀴즈! \n", i + 1);
        int n = rand() % 7;
        while (1)
        {
            if (n == b[0] || n == b[1])
                n = rand() % 7;
            else
                break;
        }
        printf("%s", quiz3[n]);
        scanf("%s", &c);
        a = (int)c;
        b[i] = a;
        if (b[i] == answer3[n])
            score++;
    }
    system("clear");
    return score;
}
void Quiz(int score, int user_status[])
{
    char art[2000];
    if (score > 0 && score < 3)
    {
        printf("\n%d 문제를 맞혔다. 경험치 일부 상승!\n", score);
        user_status[4] += score;
        if (user_status[4] >= user_status[8])
        {
            if (user_status[4] == user_status[8])
                user_status[4] = 0;
            else if (user_status[4] == user_status[8] + 1)
                user_status[4] = 1;
            else
                user_status[4] = 2;
            // user_status[8]++;
            user_status[7]++;
            user_status[5] += rand() % 1501 + 400;
            // user_status[6] += 10;
            user_status[2] += rand() % 101 + 300;
            user_status[3] += rand() % 201 + 500;
            user_status[0] = user_status[5];
            user_status[1] = user_status[6];
            printtext(art, 3);
            printf("레벨업!!!\n");
            sleep(1);
        }
    }
    else if (score == 3)
    {
        printf("\n모든 문제를 맞혔다! hp 풀충전!!!\n");
        user_status[0] = user_status[5];
        user_status[4] += score;
        if (user_status[4] >= user_status[8])
        {
            if (user_status[4] == user_status[8])
                user_status[4] = 0;
            else if (user_status[4] == user_status[8] + 1)
                user_status[4] = 1;
            else
                user_status[4] = 2;
            // user_status[8]++;
            user_status[7]++;
            user_status[5] += rand() % 1501 + 400;
            // user_status[6] += 10;
            user_status[2] += rand() % 101 + 300;
            user_status[3] += rand() % 201 + 500;
            user_status[0] = user_status[5];
            user_status[1] = user_status[6];
            printtext(art, 3);
            printf("레벨업!!!\n");
            sleep(1);
        }
    }
    else
    {
        printf("\n모든 문제를 틀렸다 멍충아! hp 깎았으니까 꺼지셈; \n");
        user_status[0] -= user_status[0] / 2;
    }

    printf("hp : %d  mp : %d  공격력 : %d  특수 공격력 : %d  경험치 %d 레벨 %d \n", user_status[0], user_status[1], user_status[2], user_status[3], user_status[4], user_status[7]);
}

void PrintDevmon(char *size, int monsterN)
{
    char *number;
    switch (monsterN)
    {
    case 1:
        number = "2";
        break;
    case 2:
        number = "3";
        break;
    case 3:
        number = "4";
        break;
    case 4:
        number = "5";
        break;
    case 5:
        number = "6";
        break;
    case 6:
        number = "7";
        break;
    case 7:
        number = "8";
        break;
    case 8:
        number = "9";
        break;
    case 9:
        number = "10";
        break;
    case 10:
        number = "11";
        break;
    case 11:
        number = "12";
        break;
    case 12:
        number = "13";
        break;
    case 13:
        number = "14";
        break;
    case 14:
        number = "15";
        break;
    case 15:
        number = "16";
        break;
    case 16:
        number = "17";
        break;
    case 17:
        number = "18";
        break;
    case 18:
        number = "19";
        break;
    case 19:
        number = "20";
        break;
    case 20:
        number = "21";
        break;
    default:
        number = "1";
        break;
    }
    FILE *devmon_rfp = fopen(number, "rt");

    while (fgets(size, 2000, devmon_rfp) != NULL)
        printf("%s", size);
    fclose(devmon_rfp);
}

void Shop(int *coin, int *status, int *itembox)
{
    system("clear");
    char num;
    printf("상점에 어서오세요~\n");
    while (num != '0')
    {
        printf("1.회복약 1개 구매(10골드)\n2.마나회복약 1개 구매(10골드)\n3.MaxMP 10 증가(30골드)\n4.S_Lotto(10골드)\n5.M_Lotto(50골드)\n6.L_Lotto(100골드)\n7.9999포션(9999골드)\n0.나가기\n");
        printf("-------------------------------------------\n");
        printf("소지중인 골드: %d\n", *coin);
        printf("이용할 번호를 입력해주세요.: ");
        scanf("%s", &num);

        switch (num)
        {
        case '1':
            if (*coin < 10)
            {
                printf("골드가 부족합니다!!!\n");
                sleep(1);
                system("clear");
            }
            else
            {
                printf("회복약 한개를 구매하셨습니다.\n");
                itembox[0] += 1;
                *coin -= 10;
                sleep(1);
                system("clear");
            }
            break;
        case '2':
            if (*coin < 10)
            {
                printf("골드가 부족합니다!!!\n");
                sleep(1);
                system("clear");
            }
            else
            {
                printf("마나회복약 한개를 구매하셨습니다.\n");
                itembox[1] += 1;
                *coin -= 10;
                sleep(1);
                system("clear");
            }
        case '3':
            if (*coin < 30)
            {
                printf("골드가 부족합니다!!!\n");
                sleep(1);
                system("clear");
            }
            else
            {
                status[6] += 10;
                status[1] += 10;
                *coin -= 30;
                printf("MaxMP가 10증가하여 MaxMp는%d이 되었습니다.\n", status[6]);
                sleep(1);
                system("clear");
            }
            break;
        case '4':
            if (*coin < 10)
            {
                printf("골드가 부족합니다!!!\n");
                sleep(1);
                system("clear");
            }
            else
            {
                *coin -= 10;
                int cash;
                cash = rand() % 21;
                *coin += cash;
                printf("축하합니다~~~~%d골드를 뽑았습니다!!!\n", cash);
                sleep(1);
                system("clear");
            }
            break;
        case '5':
            if (*coin < 50)
            {
                printf("골드가 부족합니다!!!\n");
                sleep(1);
                system("clear");
            }
            else
            {
                *coin -= 50;
                int cash;
                cash = rand() % 101;
                *coin += cash;
                printf("축하합니다~~~~%d골드를 뽑았습니다!!!\n", cash);
                sleep(1);
                system("clear");
            }
            break;
        case '6':
            if (*coin < 100)
            {
                printf("골드가 부족합니다!!!\n");
                sleep(1);
                system("clear");
            }
            else
            {
                *coin -= 100;
                int cash;
                cash = rand() % 201;
                *coin += cash;
                printf("축하합니다~~~~%d골드를 뽑았습니다!!!\n", cash);
                sleep(1);
                system("clear");
            }
            break;
        case '7':
            if (*coin < 9999)
            {
                printf("골드가 부족합니다!!!\n");
                sleep(1);
                system("clear");
            }
            else
            {
                *coin -= 9999;
                status[5] += 9999;
                status[2] += 9999;
                status[3] += 9999;
                status[0] = status[5];
                printf("체력,공격력,특수공격력이 9999만큼 올랐습니다!!!\n");
                sleep(1);
                system("clear");
            }
            break;

        default:
            break;
        }
    }
}

void printtext(char *size, int num)
{
    char *text;
    switch (num)
    {
    case 1:
        text = "win";
        break;
    case 2:
        text = "lose";
        break;
    case 3:
        text = "levelup";
        break;
    case 4:
        text = "Quizmon1";
        break;
    case 5:
        text = "Quizmon2";
        break;
    case 6:
        text = "Quizmon3";
        break;
    case 7:
        text = "main";
        break;
    case 8:
        text = "ending";
    default:
        break;
    }
    FILE *text_rfp = fopen(text, "rt");
    while (fgets(size, 2000, text_rfp) != NULL)
        printf("%s", size);
    fclose(text_rfp);
}
