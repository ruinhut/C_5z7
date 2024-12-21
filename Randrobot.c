#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



/////////////////////////////////////////////////////////////////////
///////////////////������ͷ�ļ���̬�����������////////////////////////
/////////////////////////////////////////////////////////////////////



#define SIZE 15
#define CHARSIZE 2

void initRecordBoard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);
int judgewin(int x, int y, int palyer);
int generaterand(void);
void robotRanddo(int player);
int playerdo(int player);

//����ʹ�õ���GBK���룬ÿһ�������ַ�ռ��2���ֽڡ�

//������ģ�� 
char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1] = 
{
    "���өөөөөөөөөөөөө�",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "���۩۩۩۩۩۩۩۩۩۩۩۩۩�"
};
//������洢������ʾ������ 
char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[] = "��"; //������
char play1CurrentPic[] = "��"; 

char play2Pic[] = "��"; //������
char play2CurrentPic[] = "��";

//���������ڼ�¼��ǰ�����̵ĸ�� 
int arrayForInnerBoardLayout[SIZE][SIZE];
int judge;




/////////////////////////////////////////////////////////////////////
//////////////////////�˴�������ȫ�ֱ���������////////////////////////
/////////////////////////////////////////////////////////////////////



int main() {

    int c;
    int x;
    char y;
    int numy;
    int reinput = 0;
    int player = 1;
    initRecordBoard();    
    //��ʼ��һ��������
    
    if((rand()%2) == 1){
        printf("player 1 is black\n");
        printf("robot is white\n");
        player = 1;
    }else{
        printf("player 1 is white\n");
        printf("robot is black\n");
        player = 2;
    }
    //�ж�˭����

    displayBoard(); 

    if(player == 2){
        robotRanddo(3-player);
        //������������ߣ����������
        displayBoard(); 
        judge = judgewin(15-x,numy,3 - player);
        if(judge == 1){
            printf("robot win!!!\n");
            return 0;
        }
    }

    while (1) {
        printf("q to quit & otherletters = continue\n");

        if ((c = getchar()) == 'q') {
            printf("quit, player loss\n");
            break;
        }
        playerdo(player);
        displayBoard(); 
        getchar();
    }

    return 0;

}

//��ʼ��һ�������̸�� 
void initRecordBoard(void) {
    //ͨ��˫��ѭ������arrayForInnerBoardLayout��0
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            arrayForInnerBoardLayout[i][j] = 0;
        }
    }
}

//��arrayForInnerBoardLayout�м�¼������λ�ã�ת����arrayForDisplayBoard��
void innerLayoutToDisplayArray(void) {
    //��һ������arrayForEmptyBoard�м�¼�Ŀ����̣����Ƶ�arrayForDisplayBoard��
    int i, j;
    for (i = 0; i < SIZE; i++) {
        strcpy(arrayForDisplayBoard[i], arrayForEmptyBoard[i]);
    }

    //�ڶ�����ɨ��arrayForInnerBoardLayout����������0��Ԫ�أ�������ߡ��Ƶ�arrayForDisplayBoard����Ӧλ����
    //ע�⣺arrayForDisplayBoard����¼���ַ��������ַ���ÿ���ַ�ռ2���ֽڡ���͡�Ҳ�������ַ���ÿ��Ҳռ2���ֽڡ�
    for (i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++){
            if(arrayForInnerBoardLayout[i][j] == 1){
                arrayForDisplayBoard[i][j * 2] = play1Pic[0];
                arrayForDisplayBoard[i][j * 2 + 1] = play1Pic[1];
            } else if (arrayForInnerBoardLayout[i][j] == 2) {
                arrayForDisplayBoard[i][j * 2] = play2Pic[0];
                arrayForDisplayBoard[i][j * 2 + 1] = play2Pic[1];
            }
        }
    }
}

//��ʾ���̸�� 
void displayBoard(void) {
    int i;
    //��һ��������
    system("clear");   //����  
    //�ڶ�������arrayForDisplayBoard�������Ļ��
    for (i = 0; i < SIZE; i++) {
        printf("%3d %s\n", SIZE - i, arrayForDisplayBoard[i]);
    }

    //������������������һ����ĸA B .... 
    printf("    ");
    for (i = 0; i < SIZE; i++) {
        printf("%c", 'A' + i);
    }
    printf("\n");
}

//�ж���Ӯ
int judgewin(int x, int y, int player){
    int numberjudge;
    if(player == 1){
        numberjudge = 1;
    }else{
        numberjudge = 2;
    }

    int i, j;
    int sumRaw, sumCol, sumltop, sumrtop;
    sumRaw = sumCol = sumltop = sumrtop = 0;

    for(i = x-1; i > -1 ; i--){
        if(arrayForInnerBoardLayout[i][y] != numberjudge){
            break;
        }else{
            sumRaw++;
        }
    }
    for(j = x+1 ; j < SIZE ; j++){
        if(arrayForInnerBoardLayout[j][y] != numberjudge){
            break;
        }else{
            sumRaw++;
        }
    }

    for(i = y-1; i > -1 ; i--){
        if(arrayForInnerBoardLayout[x][i] != numberjudge){
            break;
        }else{
            sumCol++;
        }
    }
    for(j = y+1 ; j < SIZE ; j++){
        if(arrayForInnerBoardLayout[x][j] != numberjudge){
            break;
        }else{
            sumCol++;
        }
    }

    for(i = x-1, j = y-1; i > -1 && j > -1; i--,j--){
        if(arrayForInnerBoardLayout[i][j] != numberjudge){
            break;
        }else{
            sumltop++;
        }
    }
    for(i = x+1, j = y+1 ; j < SIZE && i < SIZE; i++, j++){
        if(arrayForInnerBoardLayout[i][j] != numberjudge){
            break;
        }else{
            sumltop++;
        }
    }

    for(i = x+1, j = y-1; i < SIZE && j > -1; i++, j--){
        if(arrayForInnerBoardLayout[i][j] != numberjudge){
            break;
        }else{
            sumrtop++;
        }
    }
    for(i = x-1, j = y+1 ; j < SIZE && i > -1; i--, j++){
        if(arrayForInnerBoardLayout[i][j] != numberjudge){
            break;
        }else{
            sumrtop++;
        }
    }

    if(sumRaw >= 4 || sumCol >= 4 || sumltop >= 4 || sumrtop >= 4){
        return 1;
    }
   return 0;
}

int generaterand(void){
    return rand()%15;
}

void robotRanddo(int player){
    int x = generaterand();
    int y = generaterand();
    while(arrayForInnerBoardLayout[15-x][y] != 0){
        x = generaterand();
        y = generaterand();
    }
    arrayForInnerBoardLayout[15 - x][y] = 2;
    innerLayoutToDisplayArray();
    arrayForDisplayBoard[15-x][y * 2] = play2CurrentPic[0];
    arrayForDisplayBoard[15-x][y * 2 + 1] = play2CurrentPic[1];
}

int playerdo(int player){
    void displayBoard(void);
    void innerLayoutToDisplayArray(void);

    int x;
    char y;
    int numy;
    scanf("%d %c", &x, &y);

    y = toupper(y); 
    // ��������ַ�ת��Ϊ��д��ĸ

    numy = y - 'A';

    if (x < 0 || x >= SIZE || numy < 0 || numy >= SIZE) {
            printf("The position is out of the board\n");
            return 1;
    } else {
        system("clear"); 
        // �� Windows ������
    
        if(arrayForInnerBoardLayout[15-x][numy] == 1 || arrayForInnerBoardLayout[15-x][numy] == 2){
            printf("There has been a chess\n");
            return 1;
        }else{                
            arrayForInnerBoardLayout[15 - x][numy] = player;
            innerLayoutToDisplayArray();
            if(player == 1){
                arrayForDisplayBoard[15-x][numy * 2] = play1CurrentPic[0];
                arrayForDisplayBoard[15-x][numy * 2 + 1] = play1CurrentPic[1];
            }else{
                arrayForDisplayBoard[15-x][numy * 2] = play2CurrentPic[0];
                arrayForDisplayBoard[15-x][numy * 2 + 1] = play2CurrentPic[1];
            }
        }
    }
    return 0;
}