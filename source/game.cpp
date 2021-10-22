#include "game.h"
#include "audio.h"
int gridX, gridY;
int snakelength = 5;
int score = 0;
int snakeX[MAXLENGTH]={gridsize, gridsize, gridsize, gridsize, gridsize}, snakeY[MAXLENGTH]={gridsize, gridsize - 1, gridsize - 2, gridsize - 3, gridsize - 4};
int dirr = RIGHT;
int targetX, targetY;
bool target = true;
extern bool gameover;
void game::reset(){
    printf("\e[1;1H\e[2J");
    snakelength = 5;
    score = 0;
    dirr = RIGHT;
	snakeX[0] = gridsize;
    snakeX[1] = gridsize;
    snakeX[2] = gridsize;
    snakeX[3] = gridsize;
    snakeX[4] = gridsize;
	snakeY[0] = gridsize;
    snakeY[1] = gridsize - 1;
    snakeY[2] = gridsize - 1;
    snakeY[3] = gridsize - 1;
    snakeY[4] = gridsize - 1;
	gameover = false;
}
void game::initGrid(int x, int y){
    gridX = x;
    gridY = y;
}
void game::drawgrid(){
    for(int x =0; x< gridX; x+=gridsize){
        for(int y=0; y<gridY; y+=gridsize){
            drawunit(x, y);
        }
    }
}
void game::drawsnake(){
    for(int i = snakelength -1; i > 0;i--){
        snakeX[i] = snakeX[i-1];
        snakeY[i] = snakeY[i-1];
    }
    if(dirr == UP)
        snakeY[0] -=gridsize;
    else if(dirr == DOWN)
        snakeY[0]+=gridsize;
    else if(dirr == RIGHT)
        snakeX[0]+=gridsize;
    else if(dirr == LEFT)
        snakeX[0]-=gridsize;
    for(int i = 0; i < snakelength; i++){
        if(i == 0)
            C2D_DrawRectSolid(snakeX[i], snakeY[i],0, gridsize, gridsize, C2D_Color32f(0.0, 0.0, 1.0, 1.0));
        else
            C2D_DrawRectSolid(snakeX[i], snakeY[i],0, gridsize, gridsize, C2D_Color32f(0.0, 1.0, 0.0, 1.0));
    }
    if(snakeX[0] ==0 || snakeX[0] == gridX-gridsize || snakeY[0] == 0 || snakeY[0] == gridY-gridsize)
        gameover = true;
    if(snakeX[0] == targetX && snakeY[0] == targetY){
        snakelength++;
        score++;
        audio_play("romfs:/pickup.bin");
        if(snakelength > MAXLENGTH)
            snakelength = MAXLENGTH;
        target = true;
    }
    for(int j=1;j<snakelength;j++)
    {
        if(snakeX[j]==snakeX[0] && snakeY[j]==snakeY[0])
            gameover=true;
    }
        
}
int round(int n)
{
    int a = (n / gridsize) * gridsize;
    int b = a + gridsize;
    int res = (n - a > b - n)? b : a;
    return res;
}
void game::random(int &x, int &y){
    int maxX = gridX - gridsize *2;
    int maxY = gridY- gridsize *2;
    int min = gridsize;
    srand(time(NULL));
    int t1 = min + rand() %(maxX -min);
    int t2 = min + rand() %(maxY -min);
    x = round(t1);
    y = round(t2);
}
void game::drawtarget(){
    if(target)
        random(targetX, targetY);
    target = false;
    C2D_DrawRectSolid(targetX, targetY,0, gridsize, gridsize, C2D_Color32f(1.0, 0.0, 0.0, 1.0));
}
void game::drawunit(int x, int y){
    if(x==0 || y==0 || x==gridX-gridsize || y==gridY-gridsize){
        C2D_DrawLine(x, y, C2D_Color32f(1.0, 0.0, 0.0, 1.0), x+gridsize, y, C2D_Color32f(1.0, 0.0, 0.0, 1.0), 2, 0);
        C2D_DrawLine(x+gridsize, y, C2D_Color32f(1.0, 0.0, 0.0, 1.0), x+gridsize, y+gridsize, C2D_Color32f(1.0, 0.0, 0.0, 1.0), 2, 0);
        C2D_DrawLine(x+gridsize, y+gridsize, C2D_Color32f(1.0, 0.0, 0.0, 1.0), x, y+gridsize, C2D_Color32f(1.0, 0.0, 0.0, 1.0), 2, 0);
        C2D_DrawLine(x, y+gridsize, C2D_Color32f(1.0, 0.0, 0.0, 1.0), x, y, C2D_Color32f(1.0, 0.0, 0.0, 1.0), 2, 0);
    }else{
        C2D_DrawLine(x, y, C2D_Color32f(1.0, 1.0, 1.0, 1.0), x+gridsize, y, C2D_Color32f(1.0, 1.0, 1.0, 1.0), 1, 0);
        C2D_DrawLine(x+gridsize, y, C2D_Color32f(1.0, 1.0, 1.0, 1.0), x+gridsize, y+gridsize, C2D_Color32f(1.0, 1.0, 1.0, 1.0), 1, 0);
        C2D_DrawLine(x+gridsize, y+gridsize, C2D_Color32f(1.0, 1.0, 1.0, 1.0), x, y+gridsize, C2D_Color32f(1.0, 1.0, 1.0, 1.0), 1, 0);
        C2D_DrawLine(x, y+gridsize, C2D_Color32f(1.0, 1.0, 1.0, 1.0), x, y, C2D_Color32f(1.0, 1.0, 1.0, 1.0), 1, 0);
    }
    
}