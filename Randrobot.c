#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



/////////////////////////////////////////////////////////////////////
///////////////////以上是头文件静态库的引用区域////////////////////////
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

//棋盘使用的是GBK编码，每一个中文字符占用2个字节。

//空棋盘模板 
char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1] = 
{
    "┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"
};
//此数组存储用于显示的棋盘 
char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[] = "●"; //黑棋子
char play1CurrentPic[] = "▲"; 

char play2Pic[] = "◎"; //白棋子
char play2CurrentPic[] = "△";

//此数组用于记录当前的棋盘的格局 
int arrayForInnerBoardLayout[SIZE][SIZE];
int judge;




/////////////////////////////////////////////////////////////////////
//////////////////////此处是所有全局变量的声明////////////////////////
/////////////////////////////////////////////////////////////////////



int main() {

    int c;
    int x;
    char y;
    int numy;
    int reinput = 0;
    int player = 1;
    initRecordBoard();    
    //初始化一个空棋盘
    
    if((rand()%2) == 1){
        printf("player 1 is black\n");
        printf("robot is white\n");
        player = 1;
    }else{
        printf("player 1 is white\n");
        printf("robot is black\n");
        player = 2;
    }
    //判断谁先走

    displayBoard(); 

    if(player == 2){
        robotRanddo(3-player);
        //如果机器人先走，则随机落子
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

//初始化一个空棋盘格局 
void initRecordBoard(void) {
    //通过双重循环，将arrayForInnerBoardLayout清0
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            arrayForInnerBoardLayout[i][j] = 0;
        }
    }
}

//将arrayForInnerBoardLayout中记录的棋子位置，转化到arrayForDisplayBoard中
void innerLayoutToDisplayArray(void) {
    //第一步：将arrayForEmptyBoard中记录的空棋盘，复制到arrayForDisplayBoard中
    int i, j;
    for (i = 0; i < SIZE; i++) {
        strcpy(arrayForDisplayBoard[i], arrayForEmptyBoard[i]);
    }

    //第二步：扫描arrayForInnerBoardLayout，当遇到非0的元素，将●或者◎复制到arrayForDisplayBoard的相应位置上
    //注意：arrayForDisplayBoard所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
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

//显示棋盘格局 
void displayBoard(void) {
    int i;
    //第一步：清屏
    system("clear");   //清屏  
    //第二步：将arrayForDisplayBoard输出到屏幕上
    for (i = 0; i < SIZE; i++) {
        printf("%3d %s\n", SIZE - i, arrayForDisplayBoard[i]);
    }

    //第三步：输出最下面的一行字母A B .... 
    printf("    ");
    for (i = 0; i < SIZE; i++) {
        printf("%c", 'A' + i);
    }
    printf("\n");
}

//判断输赢
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
    // 将输入的字符转换为大写字母

    numy = y - 'A';

    if (x < 0 || x >= SIZE || numy < 0 || numy >= SIZE) {
            printf("The position is out of the board\n");
            return 1;
    } else {
        system("clear"); 
        // 在 Windows 上清屏
    
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