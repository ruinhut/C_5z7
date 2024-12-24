// #ifndef forbiddenHead_H
// #define forbiddenHead_H
//尚博珩的工程文件,请勿抄袭
#include <stdio.h>
#include <stdlib.h>

#define SIZE 15
#define CHARSIZE 2

struct singleInfo{
    int linkNum;
    int blockNum;
    //连子数和堵子�??
    //这是每个方向上的信息
};
//单点四向信息
struct singleScore{
    struct singleInfo info[4];
    //记录每个点的四个方向的信�??
    int score;
    //通过上面四个方向的信息获取这个点的分�??
};
//单点总得�??

// int mytop3[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
// //每个3元组第一个数字是分数，第二个数字是x坐标，第三个数字是y坐标
// int enemytop3[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
// //记录我方和敌方的�??高三个得分点

struct singleScore robotScoreBoard[SIZE][SIZE];
//这是机器人的得分数组
struct singleScore enemyScoreBoard[SIZE][SIZE];
//这是玩家的得分数组（也就是我们对手的的分数组�??

//首先，我们知道，原有的棋盘中是没有禁手的，如果说有，我们在上�??次禁手判断就已经是行不�?�的�??
//�??以说，我们只要审判我们新落得这个字他的周边是不是会产生禁手就可以�??
//我们将所有的禁手规则形成这样�??个文件，封装起来
//我将在本文档中详细说�??

//player: player是玩家的操作棋子�??1表示玩家先行，作为黑�??;2表示玩家后行,作为白棋
//x,y 表示我们目前落子的位�??
//board表示我们传进来的棋盘,当然这个棋盘可以是当前棋盘或者未来棋�??

//0 我们来看�??看�?�么判断冲还是活
//冲和活的区别在于冲之间存在一个空�??

//某点左右的连珠数�??
int rawNumber(int player, int x , int y , int board[SIZE][SIZE]){
    int left, right;
    int sumRaw = 0;
    //左侧的连�??
    for(left = y-1 ; left > -1 ; left--){
        if(board[x][left] != player){
            break;
        }else{
            sumRaw++;
        }
    } 
    //右侧的连�??
    for(right = y+1 ; right < SIZE ; right++){
        if(board[x][right] != player){
            break;
        }else{
            sumRaw++;
        }
    }
    return ++sumRaw;
    //返回连珠数量，因为有�??个自己所以要加上自己
}

//某点上下的连珠数�??
int colNumber(int player, int x , int y , int board[SIZE][SIZE]){
    int up,down;
    int sumCol = 0;
    //上面的连�??
    for(up = x - 1 ; up > -1 ; up--){
        if(board[up][y] != player){
            break;
        }else{
            sumCol++;
        }
    }
    //下面的连�??
    for(down = x + 1 ; down < SIZE ; down++){
        if(board[down][y] != player){
            break;
        }else{
            sumCol++;
        }
    }
    return ++sumCol;
    //返回连珠数量，因为有�??个自己所以要加上自己
}

//某点左上右下的连珠数�??
int luNumber(int player , int x , int y , int board[SIZE][SIZE]){
    int raw,col;
    int sumLU = 0;
    //左上的数�??
    for(raw = x - 1 , col = y - 1 ; raw > -1 && col > -1 ; raw--, col--){
        if(board[raw][col] != player){
            break;
        }else{
            sumLU++;
        }
    }
    //右下的数�??
    for(raw = x + 1 , col = y + 1 ; raw < SIZE && col < SIZE ; raw++ , col++){
        if(board[raw][col] != player){
            break;
        }else{
            sumLU++;
        }
    }
    return ++sumLU;
    //返回连珠数量，因为有�??个自己所以要加上自己
}

//某点右上左下连珠�??
int ruNumber(int player , int x , int y , int board[SIZE][SIZE]){
    int raw, col;
    int sumRU = 0; 
    //右上的数�??
    for(raw = x - 1 , col = y + 1 ; raw > -1 && col < SIZE ; raw--, col++){
        if(board[raw][col] != player){
            break;
        }else{
            sumRU++;
        }
    }
    //左下的数�??
    for(raw = x + 1 , col = y - 1 ; raw < SIZE && col > -1 ; raw++ , col--){
        if(board[raw][col] != player){
            break;
        }else{
            sumRU++;
        }
    }
    return ++sumRU;
    //返回连珠数量，因为有�??个自己所以要加上自己
}

//判断上下有几个堵(两端对方的棋子数�??,不跳过空�??)
int colBlock(int player, int x , int y , int board[SIZE][SIZE]){
    int up,down;
    int block = 0;
    //上面的堵
    if(x == 0){
        block++;
    }
    if(x == SIZE - 1){
        block++;
    }
    for(up = x - 1 ; up > -1 ; up--){
        if(board[up][y] != player){
            if(board[up][y] == 3-player){
                block++;
                //碰到真的堵住的再+1
            }
            break;
        }else{
            if(up == 0){
                block++;
            }
            //在遇到边界的时�?�也算是堵上�??
        }
    } 
    //下面的堵
    for(down = x + 1 ; down < SIZE ; down++){
        if(board[down][y] != player){
            if(board[down][y] == 3-player){
                block++;
                //碰到真的堵住的再+1
            }
            break;
        }else{
            if(down == SIZE - 1){
                block++;
            }
        }
    }
    return block;
    //返回两侧堵的数量
}

//判断左右有几个堵(两端对方的棋子数�??,不跳过空�??)
int rawBlock(int player, int x , int y , int board[SIZE][SIZE]){
    int left, right;
    int block = 0;
    if(y == 0){
        block++;
    }
    if(y == SIZE - 1){
        block++;
    }
    //算上边界条件
    //左侧的堵，遇到边界算�??个赌
    for(left = y-1 ; left > -1 ; left--){
        if(board[x][left] != player){    
            if(board[x][left] == 3-player){
                block++;
                //碰到真的堵住的再+1
            }
            break;
        }else{
            if(left == 0){
                block++;
            }
        }
    } 
    //右侧的堵
    for(right = y+1 ; right < SIZE ; right++){
        if(board[x][right] != 3-player){
            if(board[x][right] == 3-player){
                block++;
                //碰到真的堵住的再+1
            }
            break;
        }else{
            if(right == SIZE - 1){
                block++;
            }
        }
    }
    return block;
    //返回两侧堵的数量
}

//判断左上右下有几个堵(两端对方的棋子数�??,不跳过空�??)
int luBlock(int player , int x , int y , int board[SIZE][SIZE]){
    int raw,col;
    int block = 0;
    if(x == 0 || y == 0){
        block++;
    }
    if(x == SIZE - 1 || y == SIZE - 1){
        block++;
    }
    //左上的数�??
    for(raw = x - 1 , col = y - 1 ; raw > -1 && col > -1 ; raw--, col--){
        if(board[raw][col] != player){
            if(board[raw][col] == 3-player){
                block++;
                //碰到真的堵住的再+1
            }
            break;
        }else{
            if(raw == 0 || col == 0){
                block++;
            }
            //遇到边界算一个堵
        }
    }
    //右下的数�??
    for(raw = x + 1 , col = y + 1 ; raw < SIZE && col < SIZE ; raw++ , col++){
        if(board[raw][col] != player){
            if(board[raw][col] == 3-player){
                block++;
                //碰到真的堵住的再+1
            }
            break;
        }else{
            if(raw == SIZE - 1 || col == SIZE - 1){
                block++;
            }
            //遇到边界算一个堵
        }
    }
    return block;
    //返回两侧堵的数量
}

//判断左下右上有几个堵
int ruBlock(int player , int x , int y , int board[SIZE][SIZE]){
    int raw,col;
    int block = 0;
    if(x == SIZE - 1 || y == 0){
        block++;
    }
    if(x == 0 || y == SIZE - 1){
        block++;
    }
    //左上的数�??
    for(raw = x - 1 , col = y + 1 ; raw > -1 && col < SIZE -1 ; raw--, col++){
        if(board[raw][col] != player){
            if(board[raw][col] == 3-player){
                block++;
                //碰到真的堵住的再+1
            }
            break;
        }else{
            if(raw == 0 || col == SIZE - 1){
                block++;
            }
            //遇到边界算一个堵
        }
    }
    //右下的数�??
    for(raw = x + 1 , col = y - 1 ; raw < SIZE && col > -1 ; raw++ , col--){
        if(board[raw][col] != player){
            if(board[raw][col] == 3-player){
                block++;
                //碰到真的堵住的再+1
            }
            break;
        }else{
            if(raw == SIZE - 1 || col == 0){
                block++;
            }
            //遇到边界算一个堵
        }
    }
    return block;
    //返回两侧堵的数量
}

//1 长联
int longConection(int player, int x , int y , int board[SIZE][SIZE]){
    int sumRaw,sumCol,sumLU,sumRU;

    sumRaw = rawNumber(player , x , y , board);
    sumCol = colNumber(player , x , y , board);
    sumLU = luNumber(player , x , y , board);
    sumRU = ruNumber(player , x , y , board);

    if(sumRaw > 5 || sumCol > 5 || sumLU > 5 || sumRU > 5){
        return -1;
    }

    return 0;
}

//2 44禁手
//�??查落子之后是否会产生�??4
//�??4的判断条件是是否能成5
int double4(int player, int x , int y , int board[SIZE][SIZE]){
    int forbidden(int player, int x , int y , int board[SIZE][SIZE]);
    int rawNumber(int player, int x , int y , int board[SIZE][SIZE]);
    int colNumber(int player, int x , int y , int board[SIZE][SIZE]);
    int luNumber(int player , int x , int y , int board[SIZE][SIZE]);
    int ruNumber(int player , int x , int y , int board[SIZE][SIZE]);
    int rawBlock(int player, int x , int y , int board[SIZE][SIZE]);
    int colBlock(int player, int x , int y , int board[SIZE][SIZE]);
    int luBlock(int player , int x , int y , int board[SIZE][SIZE]);
    int ruBlock(int player , int x , int y , int board[SIZE][SIZE]);
    //声明�??要用到的�??有函�??

    //在判断是否能�??5时，�??查是否存在禁�??
    int numof4 = 0;
    //目前�??4的数量（也就是能�??5的四的数量）
    int i,j;
    //用于操作的操作头，i为横向，j为纵�??
    int connectNumber = 0;
    //连珠�??
    int tempX = 0;
    int tempY = 0;
    //用于记录暂时性的是否能落子来成活五的�??

    board[x][y] = player;
    //先将这个点落�??

    //首先是左右方向：
    connectNumber = rawNumber(player, x , y , board);
    if(connectNumber == 4){
        if(rawBlock(player, x , y , board) != 2){
            numof4++;
        }else{
            ;
        }
    }else if(connectNumber > 0 && connectNumber < 4){
        //先向右判断是不是活四�??
        //先判断是不是遇到空格�??
        for(i = y + 1 ; i < SIZE ; i++){
            if(board[x][i] == 0){
                if(i == SIZE - 1 || board[x][i+1] == 0){
                    break;
                    //如果遇到两个0则必定不�??
                }
                tempX = x;
                tempY = i;
                //如果遇到空格，记录位�??

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落�??
                    if(rawNumber(player, tempX , tempY , board) == 5){
                        //如果这点落完该方向能�??5
                        numof4++;
                    }else{
                        ;
                    }
                }

                break;
                //不再继续执行
            }else if(board[x][i] == 3-player){
                break;
                //遇到对方的棋子就跳出
            }else{
                ;
                //遇到自己的棋子就继续
            }
        }
        //判断这点是否能落�??

        tempX = 0;
        tempY = 0;
        //重新置零

        //再向左判断是不是活四�??
        for(i = y - 1 ; i > -1 ; i--){
            if(board[x][i] == 0){
                if(i == 0 || board[x][i-1] == 0){
                    break;
                    //如果遇到两个0绝对不行
                }
                tempX = x;
                tempY = i;
                //如果遇到空格，记录位�??

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落�??
                    if(rawNumber(player, tempX , tempY , board) == 5){
                        //如果这点落完该方向能�??5
                        numof4++;
                    }else{
                        ;
                    }
                }

                break;
                //不再继续执行

            }else if(board[x][i] == 3-player){
                break;
                //遇到对方的棋子就跳出
            }else{
                ;
                //遇到自己的棋子就继续
            }
        }

        tempX = 0;
        tempY = 0;
        //重新置零

    }

    //再是上下方向
    connectNumber = colNumber(player, x , y , board);
    if(connectNumber == 4 && connectNumber < 5){
        if(colBlock(player, x , y , board) != 2){
            numof4++;
        }else{
            ;
        }
    }else if(connectNumber > 0 && connectNumber < 4){
        //先向上判断是不是活四�??
        for(i = x - 1 ; i > -1 ; i--){
            if(board[i][y] == 0){
                if(i == 0 || board[i-1][y] == 0){
                    break;
                    //脱出
                }
                tempX = i;
                tempY = y;
                //如果遇到空格，记录位�??

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落�??
                    if(colNumber(player, tempX , tempY , board) == 5){
                        //如果这点落完该方向能�??5
                        numof4++;
                    }else{
                        ;
                    }
                }

                break;
                //不再继续执行
            }else if(board[i][y] == 3-player){
                break;
                //遇到对方的棋子就跳出
            }else{
                ;
                //遇到自己的棋子就继续
            }
        }

        tempX = 0;
        tempY = 0;
        //重新置零

        //再向下判断是不是活四�??
        for(i = x + 1 ; i < SIZE ; i++){
            if(board[i][y] == 0){
                if(i == SIZE - 1 || board[i+1][y] == 0){
                    break;
                }
                tempX = i;
                tempY = y;
                //如果遇到空格，记录位�??

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落�??
                    if(colNumber(player, tempX , tempY , board) == 5){
                        //如果这点落完该方向能�??5
                        numof4++;
                    }else{
                        ;
                    }
                }

                break;
                //不再继续执行
            }else if(board[i][y] == 3-player){
                break;
                //遇到对方的棋子就跳出
            }else{
                ;
                //遇到自己的棋子就继续
            }
        }

        tempX = 0;
        tempY = 0;
        //重新置零
    }

    //再是左上右下方向
    connectNumber = luNumber(player, x , y , board);
    if(connectNumber == 4 && connectNumber < 5){
        if(luBlock(player, x , y , board) != 2){
            numof4++;
        }else{
            ;
        }
    }else if(connectNumber > 0 && connectNumber < 4){
        //先向左上判断是不是活四了
        for(i = x - 1 , j = y - 1 ; i > -1 && j > -1 ; i--, j--){
            if(board[i][j] == 0){
                if(i == 0 || j == 0 || board[i-1][j-1] == 0){
                    break;
                }
                tempX = i;
                tempY = j;
                //如果遇到空格，记录位�??

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落�??
                    if(luNumber(player, tempX , tempY , board) == 5){
                        numof4++;
                    }else{
                        ;
                    }
                }

                break;
                //不再继续执行
            }else if(board[i][j] == 3-player){
                break;
                //遇到对方的棋子就跳出
            }else{
                ;
                //遇到自己的棋子就继续
            }
        }

        tempX = 0;
        tempY = 0;
        //重新置零

        //再向右下判断是不是活四了
        for(i = x + 1 , j = y + 1 ; i < SIZE && j < SIZE ; i++, j++){
            if(board[i][j] == 0){
                if(i == SIZE -1 || j == SIZE -1 || board[i+1][j+1] == 0){
                    break;
                }
                tempX = i;
                tempY = j;
                //如果遇到空格，记录位�??

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落�??
                    if(luNumber(player, tempX , tempY , board) == 5){
                        numof4++;
                    }else{
                        ;
                    }
                }

                break;
                //不再继续执行
            }else if(board[i][j] == 3-player){
                break;
                //遇到对方的棋子就跳出
            }else{
                ;
                //遇到自己的棋子就继续
            }
        }

        tempX = 0;
        tempY = 0;
        //重新置零
    }

    //�??后是右上左下方向
    connectNumber = ruNumber(player, x , y , board);
    if(connectNumber == 4 && connectNumber < 5){
        if(ruBlock(player, x , y , board) != 2){
            numof4++;
        }else{
            ;
        }
    }else if(connectNumber > 0 && connectNumber < 4){
        //先向右上判断是不是活四了
        for(i = x - 1 , j = y + 1 ; i > -1 && j < SIZE ; i--, j++){
            if(board[i][j] == 0){
                if(i == 0 || j == SIZE - 1 || board[i-1][j+1] == 0){
                    break;
                }
                tempX = i;
                tempY = j;
                //如果遇到空格，记录位�??

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落�??
                    if(ruNumber(player, tempX , tempY , board) == 5){
                        numof4++;
                    }else{
                        ;
                    }
                }

                break;
                //不再继续执行
            }else if(board[i][j] == 3-player){
                break;
                //遇到对方的棋子就跳出
            }else{
                ;
                //遇到自己的棋子就继续
            }
        }

        tempX = 0;
        tempY = 0;
        //重新置零

        //再向左下判断是不是活四了
        for(i = x + 1 , j = y - 1 ; i < SIZE && j > -1 ; i++, j--){
            if(board[i][j] == 0){
                if(i == SIZE - 1 || j == 0 || board[i+1][j-1] == 0){
                    break;
                }
                tempX = i;
                tempY = j;
                //如果遇到空格，记录位�??

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落�??
                    if(ruNumber(player, tempX , tempY , board) == 5){
                        numof4++;
                    }else{
                        ;
                    }
                }

                break;
                //不再继续执行
            }else if(board[i][j] == 3-player){
                break;
                //遇到对方的棋子就跳出
            }else{
                ;
                //遇到自己的棋子就继续
            }
        }

        tempX = 0;
        tempY = 0;
        //重新置零
    }

    board[x][y] = 0;
    //将这个点还原

    if(numof4 >= 2){
        return -1;
    }

    return 0;
}

//3 33禁手
int double3(int player, int x , int y , int board[SIZE][SIZE]){
    int forbidden(int player, int x , int y , int board[SIZE][SIZE]);
    int rawNumber(int player, int x , int y , int board[SIZE][SIZE]);
    int colNumber(int player, int x , int y , int board[SIZE][SIZE]);
    int luNumber(int player , int x , int y , int board[SIZE][SIZE]);
    int ruNumber(int player , int x , int y , int board[SIZE][SIZE]);
    int rawBlock(int player, int x , int y , int board[SIZE][SIZE]);
    int colBlock(int player, int x , int y , int board[SIZE][SIZE]);
    int luBlock(int player , int x , int y , int board[SIZE][SIZE]);
    int ruBlock(int player , int x , int y , int board[SIZE][SIZE]);
    //声明�??要用到的�??有函�??

    //在判断能成活四的时�?�属于是禁手
    int numof3 = 0;
    //目前�??3的数量（也就是能�??4的三的数量）
    int i,j;
    //用于操作的操作头，i为横向，j为纵�??
    int connectNumber = 0;
    //连珠�??
    int tempX = 0;
    int tempY = 0;
    //用于记录暂时性的是否能落子来成活四的�??

    board[x][y] = player;
    //先将这个点落�??

    //首先是左右方向：
    connectNumber = rawNumber(player, x , y , board);
    if(connectNumber == 3 && connectNumber < 4){
        if(rawBlock(player, x , y , board) == 0){
            numof3++;
        }else{
            ;
        }
    }else if(connectNumber > 0 && connectNumber < 3){
        //先向右判断是不是活三�??

        //先判断是不是遇到空格�??
        for(i = y + 1 ; i < SIZE ; i++){
            if(board[x][i] == 0){
                if(i == SIZE - 1 || board[x][i+1] == 0){
                    break;
                    //如果遇到两个0则必定不�??
                }
                tempX = x;
                tempY = i;
                //如果遇到空格，记录位�??

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落�??
                    if(rawNumber(player, tempX , tempY , board) == 4 
                    && rawBlock(player, tempX , tempY , board) == 0){
                        numof3++;
                    }else{
                        ;
                    }
                }

                break;
                //不再继续执行
            }else if(board[x][i] == 3-player){
                break;
                //遇到对方的棋子就跳出
            }else{
                ;
                //遇到自己的棋子就继续
            }
        }

        tempX = 0;
        tempY = 0;
        //重新置零

        //再向左判断是不是活三�??
        for(i = y - 1 ; i > -1 ; i--){
            if(board[x][i] == 0){
                if(i == 0 || board[x][i-1] == 0){
                    break;
                    //如果遇到两个0绝对不行
                }
                tempX = x;
                tempY = i;
                //如果遇到空格，记录位�??

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落�??
                    if(rawNumber(player, tempX , tempY , board) == 4 
                    && rawBlock(player, tempX , tempY , board) == 0){
                        //该点能成�??4，则算一�??
                        numof3++;
                    }else{
                        ;
                    }
                }

                break;
                //不再继续执行

            }else if(board[x][i] == 3-player){
                break;
                //遇到对方的棋子就跳出
            }else{
                ;
                //遇到自己的棋子就继续
            }
        }

        tempX = 0;
        tempY = 0;
        //重新置零
    }

    //再是上下方向
    connectNumber = colNumber(player, x , y , board);
    if(connectNumber == 3 && connectNumber < 4){
        if(colBlock(player, x , y , board) == 0){
            numof3++;
        }else{
            ;
        }
    }else if(connectNumber > 0 && connectNumber < 3){

        //先向上判断是不是活三�??
        for(i = x - 1 ; i > -1 ; i--){
            if(board[i][y] == 0){
                if(i == 0 || board[i-1][y] == 0){
                    break;
                    //脱出
                }
                tempX = i;
                tempY = y;
                //如果遇到空格，记录位�??

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落�??
                    if(colNumber(player, tempX , tempY , board) == 4 
                    && colBlock(player, tempX , tempY , board) == 0){
                        numof3++;
                    }else{
                        ;
                    }
                }

                break;
                //不再继续执行
            }else if(board[i][y] == 3-player){
                break;
                //遇到对方的棋子就跳出
            }else{
                ;
                //遇到自己的棋子就继续
            }
        }

        tempX = 0;
        tempY = 0;
        //重新置零

        //再向下判断是不是活三�??
        for(i = x + 1 ; i < SIZE ; i++){
            if(board[i][y] == 0){
                if(i == SIZE - 1 || board[i+1][y] == 0){
                    break;
                }
                tempX = i;
                tempY = y;
                //如果遇到空格，记录位�??

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落�??
                    if(colNumber(player, tempX , tempY , board) == 4 
                    && colBlock(player, tempX , tempY , board) == 0){
                        numof3++;
                    }else{
                        ;
                    }
                }

                break;
                //不再继续执行
            }else if(board[i][y] == 3-player){
                break;
                //遇到对方的棋子就跳出
            }else{
                ;
                //遇到自己的就继续
            }
        }

        tempX = 0;
        tempY = 0;
        //重新置零
    }

    //再是左上右下方向
    connectNumber = luNumber(player, x , y , board);
    if(connectNumber == 3 && connectNumber < 4){
        if(luBlock(player, x , y , board) == 0){
            numof3++;
        }else{
            ;
        }
    }else if(connectNumber > 0 && connectNumber < 3){
        //先向左上判断是不是活三了
        for(i = x - 1 , j = y - 1 ; i > -1 && j > -1 ; i--, j--){
            if(board[i][j] == 0){
                if(i == 0 || j == 0 || board[i-1][j-1] == 0){
                    break;
                }
                tempX = i;
                tempY = j;
                //如果遇到空格，记录位�??

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落�??
                    if(luNumber(player, tempX , tempY , board) == 4 
                    && luBlock(player, tempX , tempY , board) == 0){
                        numof3++;
                    }else{
                        ;
                    }
                }

                break;
                //不再继续执行
            }else if(board[i][j] == 3-player){
                break;
                //遇到对方的棋子就跳出
            }else{
                ;
                //遇到自己的棋子就继续
            }
        }

        tempX = 0;
        tempY = 0;
        //重新置零

        //再向右下判断是不是活三了
        for(i = x + 1 , j = y + 1 ; i < SIZE && j < SIZE ; i++, j++){
            if(board[i][j] == 0){
                if(i == SIZE -1 || j == SIZE -1 || board[i+1][j+1] == 0){
                    break;
                }
                tempX = i;
                tempY = j;
                //如果遇到空格，记录位�??

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落�??
                    if(luNumber(player, tempX , tempY , board) == 4 
                    && luBlock(player, tempX , tempY , board) == 0){
                        numof3++;
                    }else{
                        ;
                    }
                }

                break;
                //不再继续执行
            }else if(board[i][j] == 3-player){
                break;
                //遇到对方的棋子就跳出
            }else{
                ;
                //遇到自己的棋子就继续
            }
        }

        tempX = 0;
        tempY = 0;
        //重新置零

    }

    //�??后是右上左下方向
    connectNumber = ruNumber(player, x , y , board);
    if(connectNumber == 3 && connectNumber < 4){
        if(ruBlock(player, x , y , board) == 0){
            numof3++;
        }else{
            ;
        }
    }else if(connectNumber > 0 && connectNumber < 3){
        //先向右上判断是不是活三了
        for(i = x - 1 , j = y + 1 ; i > -1 && j < SIZE ; i--, j++){
            if(board[i][j] == 0){
                if(i == 0 || j == SIZE - 1 || board[i-1][j+1] == 0){
                    break;
                }
                tempX = i;
                tempY = j;
                //如果遇到空格，记录位�??

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落�??
                    if(ruNumber(player, tempX , tempY , board) == 4 
                    && ruBlock(player, tempX , tempY , board) == 0){
                        numof3++;
                    }else{
                        ;
                    }
                }

                break;
                //不再继续执行
            }else if(board[i][j] == 3-player){
                break;
                //遇到对方的棋子就跳出
            }else{
                ;
                //遇到自己的棋子就继续
            }
        }

        tempX = 0;
        tempY = 0;
        //重新置零

        //再向左下判断是不是活三了
        for(i = x + 1 , j = y - 1 ; i < SIZE && j > -1 ; i++, j--){
            if(board[i][j] == 0){
                if(i == SIZE - 1 || j == 0 || board[i+1][j-1] == 0){
                    break;
                }
                tempX = i;
                tempY = j;
                //如果遇到空格，记录位�??

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落�??
                    if(ruNumber(player, tempX , tempY , board) == 4 
                    && ruBlock(player, tempX , tempY , board) == 0){
                        numof3++;
                    }else{
                        ;
                    }
                }

                break;
                //不再继续执行
            }else if(board[i][j] == 3-player){
                break;
                //遇到对方的棋子就跳出
            }else{
                ;
                //遇到自己的棋子就继续
            }
        }

        tempX = 0;
        tempY = 0;
        //重新置零
    }

    board[x][y] = 0;
    //将这个点还原
    
    if(numof3 >= 2){
        return -1;
    }

    return 0;
}

//4 综合禁手
//注意，我们的禁手必须是下完再判断，所以说，我们所有的禁手判断都是在下完之后进行的
//也就是说，我们要想剪枝搜索，必须要弄出来下在那个地方的棋�??
//具体来说就是：我们试图深层搜索时候，要先把目前棋盘拷贝过来，然后再在拷贝的新棋盘上下棋，然后再判断这个棋盘是不是禁手
int forbidden(int player, int x , int y , int board[SIZE][SIZE]){
    int Islongconnection = longConection(player, x , y , board);
    if(Islongconnection == -1){
        return -1;
    }
    //保证了这点附件没有长�??

    int Isdouble4 = double4(player, x , y , board);
    if(Isdouble4 == -1){
        return -1;
    }
    //保证了这点不会成双活�??

    int Isdouble3 = double3(player, x , y , board);
    if(Isdouble3 == -1){
        return -1;
    }
    //保证了这点不会成双活�??

    return 0;
}

//判断胜利
//要是有任何一个方向五子连珠就胜利�??
int win(int player,int x,int y,int board[SIZE][SIZE]){
    int rawNumber(int player, int x , int y , int board[SIZE][SIZE]);
    int colNumber(int player, int x , int y , int board[SIZE][SIZE]);
    int luNumber(int player , int x , int y , int board[SIZE][SIZE]);
    int ruNumber(int player , int x , int y , int board[SIZE][SIZE]);
    //声明�??要用到的�??有函�??

    int sumRaw,sumCol,sumLU,sumRU;

    sumRaw = rawNumber(player , x , y , board);
    sumCol = colNumber(player , x , y , board);
    sumLU = luNumber(player , x , y , board);
    sumRU = ruNumber(player , x , y , board);

    if(sumRaw == 5 || sumCol == 5 || sumLU == 5 || sumRU == 5){
        return 1;
    }

    return 0;
}

//其次，我们需要写�??个判度胺落子在哪里的双层搜索，下面的代码主要是为了实现这个目�??

//1.打分函数
//5�??10000分，活四650，半活四500
//活三400，半活三200
//活二1750，半活二75
//活一25，半活一15
void score(int player , int board[SIZE][SIZE], struct singleScore scoreBoard[SIZE][SIZE]){
    //这个函数是用来更新分数board的，scoreboard 可以是robotScoreBoard 也可以是enemyScoreBoard
    //player是当前的玩家,是robot或�?�enemy
    //board是当前的棋盘

    int forbidden(int player, int x , int y , int board[SIZE][SIZE]);
    int rawNumber(int player, int x , int y , int board[SIZE][SIZE]);
    int colNumber(int player, int x , int y , int board[SIZE][SIZE]);
    int luNumber(int player , int x , int y , int board[SIZE][SIZE]);
    int ruNumber(int player , int x , int y , int board[SIZE][SIZE]);
    int rawBlock(int player, int x , int y , int board[SIZE][SIZE]);
    int colBlock(int player, int x , int y , int board[SIZE][SIZE]);
    int luBlock(int player , int x , int y , int board[SIZE][SIZE]);
    int ruBlock(int player , int x , int y , int board[SIZE][SIZE]);
    //声明�??要用到的�??有函�??

    int i,j,k;
    //用于操作的操作头，i为横向，j为纵�??,k是每个点的四个方�??

    for(i = 0; i < SIZE ; i++){
        for(j = 0 ; j < SIZE ; j++){
            if(board[i][j] == 0){
                //如果这个点是空的
                if(forbidden(player, i , j , board) == 0){
                    //如果这个点不是禁�??
                    scoreBoard[i][j].info[0].linkNum = rawNumber(player, i , j , board);
                    scoreBoard[i][j].info[0].blockNum = rawBlock(player, i , j , board);
                    //记录横向的信�??
                    scoreBoard[i][j].info[1].linkNum = colNumber(player, i , j , board);
                    scoreBoard[i][j].info[1].blockNum = colBlock(player, i , j , board);
                    //记录纵向的信�??
                    scoreBoard[i][j].info[2].linkNum = luNumber(player, i , j , board);
                    scoreBoard[i][j].info[2].blockNum = luBlock(player, i , j , board);
                    //记录左上右下的信�??
                    scoreBoard[i][j].info[3].linkNum = ruNumber(player, i , j , board);
                    scoreBoard[i][j].info[3].blockNum = ruBlock(player, i , j , board);
                    //记录右上左下的信�??
                    scoreBoard[i][j].score = 0;
                    //初始化分�??

                    for(k = 0 ; k < 4 ; k++){
                        if(scoreBoard[i][j].info[k].linkNum == 5){
                            scoreBoard[i][j].score += 30000;
                            //如果有一�??5连，则分�??+30000
                        }else if(scoreBoard[i][j].info[k].linkNum == 4){
                            if(scoreBoard[i][j].info[k].blockNum == 0){
                                scoreBoard[i][j].score += 12000;
                                //如果有一个活四，则分�??+12000
                            }else if(scoreBoard[i][j].info[k].blockNum == 1){
                                scoreBoard[i][j].score += 1500;
                                //如果有一个半活四，则分数+400
                            }else{
                                ;
                                //死四+0
                            }
                        }else if(scoreBoard[i][j].info[k].linkNum == 3){
                            if(scoreBoard[i][j].info[k].blockNum == 0){
                                scoreBoard[i][j].score += 2000;
                                //如果有一个活三，则分�??+400
                            }else if(scoreBoard[i][j].info[k].blockNum == 1){
                                scoreBoard[i][j].score += 1000;
                                //如果有一个半活三，则分数+200
                            }else{
                                ;
                                //死三+0
                            }
                        }else if(scoreBoard[i][j].info[k].linkNum == 2){
                            if(scoreBoard[i][j].info[k].blockNum == 0){
                                scoreBoard[i][j].score += 200;
                                //如果有一个活二，则分�??+125
                            }else if(scoreBoard[i][j].info[k].blockNum == 1){
                                scoreBoard[i][j].score += 50;
                                //如果有一个半活二，则分数+75
                            }else{
                                ;
                                //死二+0
                            }
                        }else if(scoreBoard[i][j].info[k].linkNum == 1){
                            if(scoreBoard[i][j].info[k].blockNum == 0){
                                scoreBoard[i][j].score += 25;
                                //如果有一个活�??，则分数+25
                            }else if(scoreBoard[i][j].info[k].blockNum == 1){
                                scoreBoard[i][j].score += 15;
                                //如果有一个半活一，则分数+15
                            }else{
                                ;
                                //死一+0
                            }
                        }
                    }

                }else{
                    scoreBoard[i][j].score = -1;
                    //如果是禁手，则分数为-1
                }
            }else{
                scoreBoard[i][j].score = -1;
                //如果这个点不是空的，则分数为-1
            }
        }
    }

}

//2.总分函数
//负责给出目前某个玩家的�?�分的函�??
int totalScore(int player , struct singleScore scoreBoard[SIZE][SIZE]){
    int i,j;
    int totalScore = 0;
    for(i = 0; i < SIZE ; i++){
        for(j = 0 ; j < SIZE ; j++){
            if(scoreBoard[i][j].score != -1){
                totalScore += scoreBoard[i][j].score;
            }
        }
    }
    return totalScore;
}

//3.找三个我方和敌方总分数和�??高的�??,并存入top3[][]
void findMax(int player , struct singleScore robotScoreBoard[SIZE][SIZE] , struct singleScore enemyScoreBoard[SIZE][SIZE] , int top3[3][3]){
    //player是当前的玩家,是robot或�?�enemy
    //robotScoreBoard是robot的分数表
    //enemyScoreBoard是enemy的分数表
    //top3是存放最高的三个点的坐标的数�??,不一定是robot�??

    int i,j;
    for(i = 0; i < SIZE ; i++){
        for(j = 0 ; j < SIZE ; j++){
            if(robotScoreBoard[i][j].score != -1 && enemyScoreBoard[i][j].score != -1){

                if(robotScoreBoard[i][j].score + enemyScoreBoard[i][j].score > top3[2][0]){

                    top3[0][1] = top3[1][1];
                    top3[0][2] = top3[1][2];
                    top3[0][0] = top3[1][0];
                    top3[1][1] = top3[2][1];
                    top3[1][2] = top3[2][2];
                    top3[1][0] = top3[2][0];
                    //把剩下最大的两个平移下去

                    top3[2][0] = robotScoreBoard[i][j].score + enemyScoreBoard[i][j].score;
                    top3[2][1] = i;
                    top3[2][2] = j;
                    //把当前的�??大的放进�??

                }else if(robotScoreBoard[i][j].score + enemyScoreBoard[i][j].score > top3[1][0]){

                    top3[0][1] = top3[1][1];
                    top3[0][2] = top3[1][2];
                    top3[0][0] = top3[1][0];
                    //把剩下最大的�??个平移下�??

                    top3[1][0] = robotScoreBoard[i][j].score + enemyScoreBoard[i][j].score;
                    top3[1][1] = i;
                    top3[1][2] = j;
                    //把当前的第二大的放进�??
                }else if(robotScoreBoard[i][j].score + enemyScoreBoard[i][j].score > top3[0][0]){
                    top3[0][0] = robotScoreBoard[i][j].score + enemyScoreBoard[i][j].score;
                    top3[0][1] = i;
                    top3[0][2] = j;
                    //把当前的第二大的放进�??
                }else{
                    ;
                }

            }
        }
    }
}

//4.机器人回合综合函数，先找到最高的三个点，然后尝试在这三个点落�??
//如果有一个点能赢，就直接�??
//如果没有，就根据分数表，模拟敌方思�?�，选择它的三个�??高分的点，然后让他尝试落�??
//它落完之后，我们再计算此时我方的分数表的总分
//�??后在�??有情况中找到我方�??后�?�分�??高的情况，这个情况对应的原始尝试落子点就是我们要的落子点
//注意要每次更新分数表，循环完了一边记得置零�??
// int robotTurn(int player , int board[SIZE][SIZE] , struct singleScore robotScoreBoard[SIZE][SIZE] , struct singleScore enemyScoreBoard[SIZE][SIZE]){
//     //返回值是是不是赢�??
//     //赢了返回1，没赢返�??0

//     int mytop3[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
//     int enemytop3[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
//     int i,j;
//     int maxScore[3] = {0,0,0};
//     int tempScore;
//     //声明�??要用到的�??有函�??

//     findMax(player , robotScoreBoard , enemyScoreBoard , mytop3);
//     //找到�??高的三个�??

//     for(i = 0; i < 3 ; i++){
//         if(board[mytop3[i][1]][mytop3[i][2]] == 0){
//             board[mytop3[i][1]][mytop3[i][2]] = player;
//             //如果这个点是空的，就尝试落子
//             if(win(player, mytop3[i][1] , mytop3[i][2] , board) == 1){
//                 //如果这个点能�??
//                 return 1;
//                 //直接�??
//             }else{
//                 //如果不能�??
//                 score(3-player , board , enemyScoreBoard);
//                 //更新敌方分数�??
//                 findMax(3-player , robotScoreBoard , enemyScoreBoard , enemytop3);
//                 //找到敌方的最高分数点
//                 for(j = 0; j < 3 ; j++){
//                     if(board[enemytop3[j][1]][enemytop3[j][2]] == 0){
//                         board[enemytop3[j][1]][enemytop3[j][2]] = 3-player;
//                         //如果这个点是空的，就尝试落子
//                         score(player , board , robotScoreBoard);
//                         //更新我方分数�??
//                         score(3-player , board , enemyScoreBoard);
//                         //更新敌方分数�??
//                         tempScore = totalScore(player, robotScoreBoard)-totalScore(3-player, enemyScoreBoard);
//                         //计算全部总分
//                         if(tempScore < 0 && -tempScore > maxScore[i]){
//                             maxScore[i] = tempScore;
//                             //如果我方-敌方总分更高也就是我方�?�分相对高，敌方相对低，则更新落子点
//                         }else if(tempScore > 0 && tempScore > maxScore[i]){
//                             maxScore[i] = tempScore;
//                             //如果我方-敌方总分更高也就是我方�?�分相对高，敌方相对低，则更新落子点
//                         }
//                         board[enemytop3[j][1]][enemytop3[j][2]] = 0;
//                         //还原这个�??
//                     }
//                 }
//             }
//             board[mytop3[i][1]][mytop3[i][2]] = 0;
//             //还原这个�??
//         }
//     }

//     if(maxScore[0] >= maxScore[1] && maxScore[0] >= maxScore[2]){
//         board[mytop3[0][1]][mytop3[0][2]] = player;
//         printf("robot:%d,%c\n",15-mytop3[0][1],'A'+mytop3[0][2]);
//         //如果第一个点�??好，就落�??
//     }else if(maxScore[1] >= maxScore[0] && maxScore[1] >= maxScore[2]){
//         board[mytop3[1][1]][mytop3[1][2]] = player;
//         printf("robot:%d,%c\n",15-mytop3[1][1],'A'+mytop3[1][2]);
//         //如果第二个点�??好，就落�??
//     }else{
//         board[mytop3[2][1]][mytop3[2][2]] = player;
//         printf("robot:%d,%c\n",15-mytop3[2][1],'A'+mytop3[2][2]);
//         //如果第三个点�??好，就落�??  
//     }

//     return 0;
// }



int robotTurn(int player, int board[SIZE][SIZE], struct singleScore robotScoreBoard[SIZE][SIZE], struct singleScore enemyScoreBoard[SIZE][SIZE]) {
    
    void score(int player, int board[SIZE][SIZE], struct singleScore scoreBoard[SIZE][SIZE]);
    void findMax(int player, struct singleScore robotScoreBoard[SIZE][SIZE], struct singleScore enemyScoreBoard[SIZE][SIZE], int top3[3][3]);
    int totalScore(int player, struct singleScore scoreBoard[SIZE][SIZE]);
    
    int mytop3[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    int enemytop3[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    int mytemptop3[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    int enemytemptop3[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    int maxScore[3] = {0, 0, 0 };
    int tempScore;
    int i, j, k, l;

    score(player, board, robotScoreBoard);
    findMax(player, robotScoreBoard, enemyScoreBoard, mytop3);

    for (i = 0; i < 3; i++) {
        if (board[mytop3[i][1]][mytop3[i][2]] == 0) {

            board[mytop3[i][1]][mytop3[i][2]] = player;
            score(3 - player, board, enemyScoreBoard);
            findMax(3 - player, robotScoreBoard, enemyScoreBoard, enemytop3);

            if(win(player, mytop3[i][1], mytop3[i][2], board) == 1) {
                board[mytop3[i][1]][mytop3[i][2]] = player;
                return 1;
            }

            for (j = 0; j < 3; j++) {
                if (board[enemytop3[j][1]][enemytop3[j][2]] == 0) {

                    board[enemytop3[j][1]][enemytop3[j][2]] = 3 - player;
                    score(player, board, robotScoreBoard);
                    score(3 - player, board, enemyScoreBoard);
                    findMax(player, robotScoreBoard, enemyScoreBoard, mytemptop3);

                    for (k = 0; k < 3; k++) {
                        if (board[mytemptop3[k][1]][mytemptop3[k][2]] == 0) {

                            board[mytemptop3[k][1]][mytemptop3[k][2]] = player;
                            score(3 - player, board, enemyScoreBoard);
                            findMax(3 - player, robotScoreBoard, enemyScoreBoard, enemytemptop3);

                            for (l = 0; l < 3; l++) {
                                if (board[enemytemptop3[l][1]][enemytemptop3[l][2]] == 0) {

                                    board[enemytemptop3[l][1]][enemytemptop3[l][2]] = 3 - player;
                                    score(player, board, robotScoreBoard);
                                    score(3 - player, board, enemyScoreBoard);

                                    tempScore = totalScore(player, robotScoreBoard) - totalScore(3 - player, enemyScoreBoard);
                                    if (tempScore < 0 && -tempScore > maxScore[i]) {
                                        maxScore[i] = tempScore;
                                    }else if(tempScore > 0 && tempScore > maxScore[i]) {
                                        maxScore[i] = tempScore;
                                    }

                                    board[enemytemptop3[l][1]][enemytemptop3[l][2]] = 0;
                                }
                            }

                            board[mytemptop3[k][1]][mytemptop3[k][2]] = 0;
                        }
                    }

                    board[enemytop3[j][1]][enemytop3[j][2]] = 0;
                }
            }

            board[mytop3[i][1]][mytop3[i][2]] = 0;
        }
    }

    if (maxScore[0] >= maxScore[1] && maxScore[0] >= maxScore[2]) {
        printf("robot:%d,%c\n",15-mytop3[0][1],'A'+mytop3[0][2]);
        board[mytop3[0][1]][mytop3[0][2]] = player;
    } else if (maxScore[1] >= maxScore[0] && maxScore[1] >= maxScore[2]) {
        printf("robot:%d,%c\n",15-mytop3[1][1],'A'+mytop3[1][2]);
        board[mytop3[1][1]][mytop3[1][2]] = player;
    } else {
         printf("robot:%d,%c\n",15-mytop3[2][1],'A'+mytop3[2][2]);
        board[mytop3[2][1]][mytop3[2][2]] = player;
    }

    return 0;
}









//5.人类回合函数
int humanTurn(int player, int realx, int realy, int board[SIZE][SIZE]){
    //-1重来�?-2禁手输了�?-3投降
    //1赢了 0正常

    int forbid = 0;
    int isWin = 0;


    if (realx < 0 || realx >= SIZE || realy < 0 || realy >= SIZE) {
        printf("λ�ò��Ϸ�\n");
        return -1;
    }

    if (board[realx][realy] == 0) {
        forbid = forbidden(player, realx, realy, board);
        if(forbid == -1){
            printf("����\n");
            return -2;
        }
        board[realx][realy] = player;
        isWin = win(player, realx, realy, board);
    } else {
        printf("λ��ռ��\n");
        return -1;
    }

    if (isWin == 1) {
        printf("��Ӯ��\n");
        return 1;
    }

    return 0;
}

//下面是ui界面生成区域

//1.初始化棋�??
void initBoard(int board[SIZE][SIZE]){
    int i,j;
    for(i = 0; i < SIZE ; i++){
        for(j = 0 ; j < SIZE ; j++){
            board[i][j] = 0;
        }
    }
}

//2.打印棋盘
void printBoard(int board[SIZE][SIZE]){
    int i,j;
    printf(" \t");
    for(i = 0; i < SIZE ; i++){
        printf("%c ",'A'+i);
    }
    printf("\n");
    for(i = 0; i < SIZE ; i++){
        printf("%d\t",15-i);
        for(j = 0 ; j < SIZE ; j++){
            if(board[i][j] == 0){
                printf("+ ");
            }else if(board[i][j] == 1){
                printf("X ");
            }else{
                printf("O ");
            }
        }
        printf("\n");
    }
    printf("\n");   
}



///////////////////////////////////////////////////////////////////////////////
//////////////////////上述是函数区�??////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int arrayForInnerBoardLayout[SIZE][SIZE];

int main(){

    initBoard(arrayForInnerBoardLayout);
    printf("��ʼ�����");

    int human,robot;
    printf("ѡ�����Ƿ�����\n");
    scanf("%d",&human);
    if(human == 1){
        robot = 2;
    }else{
        robot = 1;
    }

    int x;
    char y;
    int realx, realy;
    int isHumanwin = 0;
    int isRobotwin = 0;
    if(robot == 1){
        arrayForInnerBoardLayout[7][7] = 1;
        printBoard(arrayForInnerBoardLayout);
    }
    char quit;
    while(1){
        // printf("�Ƿ�����,��q\n");

        // scanf("%c",&quit);

        // if(quit == 'q'){
        //     printf("��Ͷ����\n");
        //     break;
        // }
        getchar();
        printf("�������������λ��\n");
        scanf("%d,%c",&x,&y);
        
        realx = 15-x;

        if(y >= 'a' && y <= 'z'){
            realy = y - 'a';
        }else if(y >= 'A' && y <= 'Z'){
            realy = y - 'A';
        }

        isHumanwin = humanTurn(human,realx,realy,arrayForInnerBoardLayout);
        if(isHumanwin == 1){

            break;
        }else if(isHumanwin == -2){

            break;
        }else if(isHumanwin == -1){

            continue;
        }else{
            ;
        }
        system("cls");
        printBoard(arrayForInnerBoardLayout);

        score(robot,arrayForInnerBoardLayout,robotScoreBoard);
        score(human,arrayForInnerBoardLayout,enemyScoreBoard);
        isRobotwin = robotTurn(robot,arrayForInnerBoardLayout,robotScoreBoard,enemyScoreBoard);
        if(isRobotwin == 1){
            break;
        }
        printBoard(arrayForInnerBoardLayout);
    }
    system("cls");
    if(isHumanwin == 1){
        printf("��Ӯ��\n");

    }else if(isHumanwin == -2){
        printf("���֣�������\n");

    }else if(isRobotwin == 1){
        printf("����ʤ��\n");
    }
    printBoard(arrayForInnerBoardLayout);
    return 0;
}