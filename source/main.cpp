#include "game.h"
#include "icon_bin.h"
#include <unistd.h>
#include "audio.h"
#define FPS 10
bool gameover = false;
extern int snakeX[MAXLENGTH];
extern int snakeY[MAXLENGTH];
extern int dirr;
extern int dirr2;
extern int score2;
extern int score;
extern bool twoplayermode;

int sleep(int ms){
	return usleep(ms * 1000);
}
int main(int argc, char* argv[]) {
	gfxInitDefault();
	csndInit();
	romfsInit();
	audio_load("romfs:/templeos.bin");
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	gfxSetDoubleBuffering(GFX_BOTTOM, false);
	u8* fb = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
	memcpy(fb, (u8*)icon_bin, icon_bin_size);
    game::initGrid(400, 240);
	bool shutdown = false;
	bool firststart = true;
	while (aptMainLoop())
	{
		if(firststart){
			printf("->3ds Snake<- | Press a for one player mode or b for twoplayer mode.");
			while(true){
				hidScanInput();
				u32 kDownmenu = hidKeysDown();
				if(kDownmenu & KEY_A){
					printf("\e[1;1H\e[2J");
					memcpy(fb, (u8*)icon_bin, icon_bin_size);
					firststart = false;
					twoplayermode = false;
					break;
				}
				if(kDownmenu & KEY_B){
					printf("\e[1;1H\e[2J");
					memcpy(fb, (u8*)icon_bin, icon_bin_size);
					firststart = false;
					twoplayermode = true;
					break;
				}
			}
		}
		if(gameover){
			if(!twoplayermode)
				printf(std::string("Game Over. Score: " + std::to_string(score) + ". Press a for one player mode, b for two player mode or start to exit. \r").c_str());
			else
				printf(std::string("Game Over. Score1: " + std::to_string(score) + " Score2: " + std::to_string(score2) + " Press a for one player mode, b for two player mode or start to exit. \r").c_str());
			while(true){
				hidScanInput();
				u32 kDownmenu = hidKeysDown();
				if(kDownmenu & KEY_A){
					twoplayermode = false;
					game::reset();
					memcpy(fb, (u8*)icon_bin, icon_bin_size);
					break;
				}
				if(kDownmenu & KEY_START){
					shutdown = true;
					break;
				}
				if(kDownmenu & KEY_B){
					twoplayermode = true;
					game::reset();
					memcpy(fb, (u8*)icon_bin, icon_bin_size);
					break;
				}
			}
			if(shutdown)
				break;
		}
		hidScanInput();
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; 
		if(kDown & KEY_DDOWN){
			if(dirr != UP)
                dirr = DOWN;
		}
		if(kDown & KEY_DUP){
			if(dirr != DOWN)
                dirr = UP;
		}
		if(kDown & KEY_DLEFT){
			if(dirr != RIGHT)
                dirr = LEFT;
		}
		if(kDown & KEY_DRIGHT){
			if(dirr != LEFT)
                dirr = RIGHT;
		}
		if(kDown & KEY_B){
			if(dirr2 != UP)
                dirr2 = DOWN;
		}
		if(kDown & KEY_X){
			if(dirr2 != DOWN)
                dirr2 = UP;
		}
		if(kDown & KEY_Y){
			if(dirr2 != RIGHT)
                dirr2 = LEFT;
		}
		if(kDown & KEY_A){
			if(dirr2 != LEFT)
                dirr2 = RIGHT;
		}
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, C2D_Color32f(0.0, 0.0, 0.0, 1.0));
		C2D_SceneBegin(top);
		game::drawgrid();
		game::drawsnake();
		if(twoplayermode)
			game::drawsnake2();
		game::drawtarget();
		sleep(1000 / FPS);
		if(!twoplayermode)
			printf(std::string("Score: " + std::to_string(score) + "\r").c_str());
		else
			printf(std::string("Score1: " + std::to_string(score) + " Score2: " + std::to_string(score2) + "\r").c_str());
		C3D_FrameEnd(0);
	}
	audio_stop();
	csndExit();
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	romfsExit();
	return 0;
}
