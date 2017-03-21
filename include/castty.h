#ifndef CASTTY_H
#define CASTTY_H

#include <sys/ioctl.h>

#include <stddef.h>
#include <stdio.h>

#include <signal.h>
#include <termios.h>

enum control_command {
	CMD_NONE,
	CMD_CTRL_A,
	CMD_MUTE,
	CMD_PAUSE,
};

struct outargs {
	int start_paused;
	int controlfd;
	int masterfd;
	int rows;
	int cols;

	const char *cmd;
	const char *env;
	const char *title;
	const char *outfn;
	const char *devid;
	const char *audioout;
};

void inputproc(int, int);
void outputproc(struct outargs *oa);
void shellproc(const char *, const char *, struct winsize *, int);

double audio_clock_ms(void);
void audio_exit(void);
void audio_list(void);
void audio_mute(void);
void audio_init(const char *devid, const char *outfile);
void audio_start(void);
void audio_stop(void);
void audio_toggle_mp3(void);
void audio_toggle_mute(void);
void audio_toggle_pause(void);

int record_main(int, char **);

void setup_sighandlers(void);

void xclose(int);
int xdup2(int, int);
void xfclose(FILE *);
FILE *xfopen(const char *, const char *);
void xsigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
void xtcsetattr(int, int, const struct termios *);
size_t xwrite(int, void *, size_t);

#ifndef MIN
#define MIN(a, b) ((a < b) ? a : b)
#endif

#endif
