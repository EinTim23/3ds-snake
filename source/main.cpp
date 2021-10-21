#include "game.h"
#include "icon_bin.h"
#include <unistd.h>
#define FPS 10
bool gameover = false;
extern int dirr;
extern int score;
int sleep(int ms){
	return usleep(ms * 1000);
}
int main(int argc, char* argv[]) {
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	gfxSetDoubleBuffering(GFX_BOTTOM, false);
	u8* fb = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
	memcpy(fb, (u8*)icon_bin, icon_bin_size);
    game::initGrid(400, 240);
	while (aptMainLoop())
	{
		if(gameover)
			break;
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
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, C2D_Color32f(0.0, 0.0, 0.0, 1.0));
		C2D_SceneBegin(top);
		game::drawgrid();
		game::drawsnake();
		game::drawtarget();
		sleep(1000 / FPS);
		std::string lessgo = "Score: " + std::to_string(score) + "\r";
		printf(lessgo.c_str());
		C3D_FrameEnd(0);
	}
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	romfsExit();
	return 0;
}
