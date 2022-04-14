#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "windowsize.h"

void sizecheck(void)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int row = w.ws_row;
    int col = w.ws_col;

    while (row < 60 || col < 160) {
      if (col < 160) {
        printf("Your current window size could only contain %d columns. Please enlarge your window.\n\n", col);
        usleep(600000);
        while (col == w.ws_col) {
          ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        }
      }
      if (row < 60) {
        printf("Your current window size could only contain %d lines. Please enlarge your window.\n\n", row);
        usleep(600000);
        while (row == w.ws_row) {
          ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        }
      }
      row = w.ws_row;
      col = w.ws_col;
    }

    return;  
}
