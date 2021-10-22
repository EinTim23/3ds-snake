
#include <3ds.h>
#include <stdio.h>
#include <string.h>

void audio_play(const char *audio){
	void* buffer;
	FILE *file = fopen(audio, "rb");
	fseek(file, 0, SEEK_END);
	off_t size = ftell(file);
	fseek(file, 0, SEEK_SET);
	buffer = linearAlloc(size);
	fread(buffer, 1, size, file);
	fclose(file);
	csndPlaySound(8, SOUND_FORMAT_16BIT, 48000, 1, 0, buffer, buffer, size);
	linearFree(buffer);
}
void audio_load(const char *audio){
	void* buffer;
	FILE *file = fopen(audio, "rb");
	fseek(file, 0, SEEK_END);
	off_t size = ftell(file);
	fseek(file, 0, SEEK_SET);
	buffer = linearAlloc(size);
	fread(buffer, 1, size, file);
	fclose(file);
	csndPlaySound(8, SOUND_FORMAT_16BIT | SOUND_REPEAT, 48000, 1, 0, buffer, buffer, size);
	linearFree(buffer);
}
void audio_stop(void){
	csndExecCmds(true);
	CSND_SetPlayState(0x8, 0);
}