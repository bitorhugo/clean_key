#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>

struct termios orig_termios;
void disable_raw_mode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_mode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disable_raw_mode);
  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int buf_sz = 4096;

int main (void) {
	enable_raw_mode();

	char buffer[buf_sz];
	char c;
	while (1) {
		read(STDIN_FILENO, &c, sizeof(char));
	}

	disable_raw_mode();
	exit(EXIT_SUCCESS);
}

