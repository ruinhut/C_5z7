// #ifndef forbiddenHead_H

// #define forbiddenHead_H
//尚博珩的工程文件,请勿抄袭
#include <stdio.h>
#include <stdlib.h>

#define SIZE 15
#define CHARSIZE 2
//首先，我们知道，原有的棋盘中是没有禁手的，如果说有，我们在上一次禁手判断就已经是行不通的了
//所以说，我们只要审判我们新落得这个字他的周边是不是会产生禁手就可以了
//我们将所有的禁手规则形成这样一个文件，封装起来
//我将在本文档中详细说明

//player: player是玩家的操作棋子，1表示玩家先行，作为黑棋;2表示玩家后行,作为白棋
//x,y 表示我们目前落子的位置
//board表示我们传进来的棋盘,当然这个棋盘可以是当前棋盘或者未来棋盘

//0 我们来看一看怎么判断冲还是活
//冲和活的区别在于冲之间存在一个空格

//某点左右的连珠数量
int rawNumber(int player, int x , int y , int board[SIZE][SIZE]){
    int left, right;
    int sumRaw = 0;
    //左侧的连珠
    for(left = y-1 ; left > -1 ; left--){
        if(board[x][left] != player){
            break;
        }else{
            sumRaw++;
        }
    } 
    //右侧的连珠
    for(right = y+1 ; right < SIZE ; right++){
        if(board[x][right] != player){
            break;
        }else{
            sumRaw++;
        }
    }
    return ++sumRaw;
    //返回连珠数量，因为有一个自己所以要加上自己
}

//某点上下的连珠数量
int colNumber(int player, int x , int y , int board[SIZE][SIZE]){
    int up,down;
    int sumCol = 0;
    //上面的连珠
    for(up = x - 1 ; up > -1 ; up--){
        if(board[up][y] != player){
            break;
        }else{
            sumCol++;
        }
    }
    //下面的连珠
    for(down = x + 1 ; down < SIZE ; down++){
        if(board[down][y] != player){
            break;
        }else{
            sumCol++;
        }
    }
    return ++sumCol;
    //返回连珠数量，因为有一个自己所以要加上自己
}

//某点左上右下的连珠数量
int luNumber(int player , int x , int y , int board[SIZE][SIZE]){
    int raw,col;
    int sumLU = 0;
    //左上的数量
    for(raw = x - 1 , col = y - 1 ; raw > -1 && col > -1 ; raw--, col--){
        if(board[raw][col] != player){
            break;
        }else{
            sumLU++;
        }
    }
    //右下的数量
    for(raw = x + 1 , col = y + 1 ; raw < SIZE && col < SIZE ; raw++ , col++){
        if(board[raw][col] != player){
            break;
        }else{
            sumLU++;
        }
    }
    return ++sumLU;
    //返回连珠数量，因为有一个自己所以要加上自己
}

//某点右上左下连珠数
int ruNumber(int player , int x , int y , int board[SIZE][SIZE]){
    int raw, col;
    int sumRU = 0; 
    //右上的数量
    for(raw = x - 1 , col = y + 1 ; raw > -1 && col < SIZE ; raw--, col++){
        if(board[raw][col] != player){
            break;
        }else{
            sumRU++;
        }
    }
    //左下的数量
    for(raw = x + 1 , col = y - 1 ; raw < SIZE && col > -1 ; raw++ , col--){
        if(board[raw][col] != player){
            break;
        }else{
            sumRU++;
        }
    }
    return ++sumRU;
    //返回连珠数量，因为有一个自己所以要加上自己
}

//判断上下有几个堵(两端对方的棋子数量,不跳过空格)
int colBlock(int player, int x , int y , int board[SIZE][SIZE]){
    int up,down;
    int block = 0;
    //上面的堵
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
            //在遇到边界的时候也算是堵上了
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

//判断左右有几个堵(两端对方的棋子数量,跳过空格)
int rawBlock(int player, int x , int y , int board[SIZE][SIZE]){
    int left, right;
    int block = 0;
    //左侧的堵，遇到边界算一个赌
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
        if(board[x][right] == 3-player){
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

//判断左上右下有几个堵(两端对方的棋子数量,跳过空格)
int luBlock(int player , int x , int y , int board[SIZE][SIZE]){
    int raw,col;
    int block = 0;
    //左上的数量
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
    //右下的数量
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
    //左上的数量
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
    //右下的数量
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
//检查落子之后是否会产生双4
//双4的判断条件是是否能成5
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
    //声明需要用到的所有函数

    //在判断是否能成5时，检查是否存在禁手
    int numof4 = 0;
    //目前为4的数量（也就是能成5的四的数量）
    int i,j;
    //用于操作的操作头，i为横向，j为纵向
    int connectNumber = 0;
    //连珠数
    int tempX = 0;
    int tempY = 0;
    //用于记录暂时性的是否能落子来成活五的点

    board[x][y] = player;
    //先将这个点落子

    //首先是左右方向：
    connectNumber = rawNumber(player, x , y , board);
    if(connectNumber == 4){
        if(rawBlock(player, x , y , board) != 2){
            numof4++;
        }else{
            ;
        }
    }else if(connectNumber > 0 && connectNumber < 4){
        //先向右判断是不是活四了
        //先判断是不是遇到空格了
        for(i = y + 1 ; i < SIZE ; i++){
            if(board[x][i] == 0){
                if(i == SIZE - 1 || board[x][i+1] == 0){
                    break;
                    //如果遇到两个0则必定不行
                }
                tempX = x;
                tempY = i;
                //如果遇到空格，记录位置

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落子
                    if(rawNumber(player, tempX , tempY , board) == 5){
                        //如果这点落完该方向能成5
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
        //判断这点是否能落子

        tempX = 0;
        tempY = 0;
        //重新置零

        //再向左判断是不是活四了
        for(i = y - 1 ; i > -1 ; i--){
            if(board[x][i] == 0){
                if(i == 0 || board[x][i-1] == 0){
                    break;
                    //如果遇到两个0绝对不行
                }
                tempX = x;
                tempY = i;
                //如果遇到空格，记录位置

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落子
                    if(rawNumber(player, tempX , tempY , board) == 5){
                        //如果这点落完该方向能成5
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
        //先向上判断是不是活四了
        for(i = x - 1 ; i > -1 ; i--){
            if(board[i][y] == 0){
                if(i == 0 || board[i-1][y] == 0){
                    break;
                    //脱出
                }
                tempX = i;
                tempY = y;
                //如果遇到空格，记录位置

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落子
                    if(colNumber(player, tempX , tempY , board) == 5){
                        //如果这点落完该方向能成5
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

        //再向下判断是不是活四了
        for(i = x + 1 ; i < SIZE ; i++){
            if(board[i][y] == 0){
                if(i == SIZE - 1 || board[i+1][y] == 0){
                    break;
                }
                tempX = i;
                tempY = y;
                //如果遇到空格，记录位置

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落子
                    if(colNumber(player, tempX , tempY , board) == 5){
                        //如果这点落完该方向能成5
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
                //如果遇到空格，记录位置

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落子
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
                //如果遇到空格，记录位置

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落子
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

    //最后是右上左下方向
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
                //如果遇到空格，记录位置

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落子
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
                //如果遇到空格，记录位置

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落子
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
    //声明需要用到的所有函数

    //在判断能成活四的时候属于是禁手
    int numof3 = 0;
    //目前为3的数量（也就是能成4的三的数量）
    int i,j;
    //用于操作的操作头，i为横向，j为纵向
    int connectNumber = 0;
    //连珠数
    int tempX = 0;
    int tempY = 0;
    //用于记录暂时性的是否能落子来成活四的点

    board[x][y] = player;
    //先将这个点落子

    //首先是左右方向：
    connectNumber = rawNumber(player, x , y , board);
    if(connectNumber == 3 && connectNumber < 4){
        if(rawBlock(player, x , y , board) == 0){
            numof3++;
        }else{
            ;
        }
    }else if(connectNumber > 0 && connectNumber < 3){
        //先向右判断是不是活三了

        //先判断是不是遇到空格了
        for(i = y + 1 ; i < SIZE ; i++){
            if(board[x][i] == 0){
                if(i == SIZE - 1 || board[x][i+1] == 0){
                    break;
                    //如果遇到两个0则必定不行
                }
                tempX = x;
                tempY = i;
                //如果遇到空格，记录位置

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落子
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

        //再向左判断是不是活三了
        for(i = y - 1 ; i > -1 ; i--){
            if(board[x][i] == 0){
                if(i == 0 || board[x][i-1] == 0){
                    break;
                    //如果遇到两个0绝对不行
                }
                tempX = x;
                tempY = i;
                //如果遇到空格，记录位置

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落子
                    if(rawNumber(player, tempX , tempY , board) == 4 
                    && rawBlock(player, tempX , tempY , board) == 0){
                        //该点能成活4，则算一个
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

        //先向上判断是不是活三了
        for(i = x - 1 ; i > -1 ; i--){
            if(board[i][y] == 0){
                if(i == 0 || board[i-1][y] == 0){
                    break;
                    //脱出
                }
                tempX = i;
                tempY = y;
                //如果遇到空格，记录位置

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落子
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

        //再向下判断是不是活三了
        for(i = x + 1 ; i < SIZE ; i++){
            if(board[i][y] == 0){
                if(i == SIZE - 1 || board[i+1][y] == 0){
                    break;
                }
                tempX = i;
                tempY = y;
                //如果遇到空格，记录位置

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落子
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
                //如果遇到空格，记录位置

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落子
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
                //如果遇到空格，记录位置

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落子
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

    //最后是右上左下方向
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
                //如果遇到空格，记录位置

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落子
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
                //如果遇到空格，记录位置

                if(forbidden(player, tempX , tempY , board) == 0){
                    //如果这点能落子
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
//也就是说，我们要想剪枝搜索，必须要弄出来下在那个地方的棋盘
//具体来说就是：我们试图深层搜索时候，要先把目前棋盘拷贝过来，然后再在拷贝的新棋盘上下棋，然后再判断这个棋盘是不是禁手
int forbidden(int player, int x , int y , int board[SIZE][SIZE]){
    int Islongconnection = longConection(player, x , y , board);
    if(Islongconnection == -1){
        return -1;
    }
    //保证了这点附件没有长联

    int Isdouble4 = double4(player, x , y , board);
    if(Isdouble4 == -1){
        return -1;
    }
    //保证了这点不会成双活四

    int Isdouble3 = double3(player, x , y , board);
    if(Isdouble3 == -1){
        return -1;
    }
    //保证了这点不会成双活三

    return 0;
}

int main(){
    int arrayForInnerBoardLayout[SIZE][SIZE];
    int num = 0;
    int i, j;
    for(j = 3 ; j < 10 ; j++){
        if(j == 4 || j == 8 ){
            arrayForInnerBoardLayout[j][j] = 0;
        }
        else{
            arrayForInnerBoardLayout[j][j] = 1;
        }
    }
    for(i = 4 ; i < 10 ; i++){
        arrayForInnerBoardLayout[8][i] = 1;

    }
    arrayForInnerBoardLayout[8][8] = 0;

    if(longConection(1,5,5,arrayForInnerBoardLayout)){
        printf("fuck error\n");
    }

    for(i=0;i<SIZE;i++){
        for(j = 0; j < SIZE ; j++){
            if(arrayForInnerBoardLayout[i][j] != 1){
                arrayForInnerBoardLayout[i][j] = 0;
            }
            printf("%d ",arrayForInnerBoardLayout[i][j]);
        }
        printf("\n");
    }
    printf("禁收吗：%d\n",forbidden(1,8,8,arrayForInnerBoardLayout));
    // printf("%d\n",colBlock(1,5,5,arrayForInnerBoardLayout));
    // printf("%d\n",luBlock(1,5,5,arrayForInnerBoardLayout));
    // printf("%d\n",ruBlock(1,5,5,arrayForInnerBoardLayout));

    return 0;
}