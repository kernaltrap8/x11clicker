// x11clicker Copyright (C) 2024 kernaltrap8
// This program comes with ABSOLUTELY NO WARRANTY
// This is free software, and you are welcome to redistribute it
// under certain conditions

/*
    x11clicker.c
*/

#include "x11clicker.h"
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int check_args(int argc, char *argv, char *arg) {
  if (argc > 1 && !strcmp(argv, arg)) {
    return 1;
  } else {
    return 0;
  }
}

// Function to simulate a mouse click and log it
void click_mouse(Display *display, int button, int click_count) {
  printf("Click %d: Simulating mouse button %d press\n", click_count, button);
  XTestFakeButtonEvent(display, button, True, CurrentTime); // Press button

  printf("Click %d: Simulating mouse button %d release\n", click_count, button);
  XTestFakeButtonEvent(display, button, False, CurrentTime); // Release button
  XFlush(display);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    puts(HELP_BANNER);
    return 1;
  }

  if (check_args(argc, argv[1], "-v") ||
      check_args(argc, argv[1], "--version")) {
    printf("x11clicker v%s\nLicensed under BSD-Clause-3\n", VERSION);
  } else if (check_args(argc, argv[1], "-h") ||
             check_args(argc, argv[1], "--help")) {
    puts(HELP_BANNER);
  }

  // Convert interval argument to an integer (click interval in milliseconds)
  int interval = atoi(argv[1]);
  if (interval <= 0) {
    printf("Please provide a valid interval greater than 0.\n");
    return 1;
  }

  // Open the display
  Display *display = XOpenDisplay(NULL);
  if (display == NULL) {
    fprintf(stderr, "Error: Unable to open X display\n");
    return 1;
  }

  printf("Autoclicker starting with an interval of %d milliseconds. Press "
         "Ctrl+C to stop.\n",
         interval);

  int click_count = 0; // Counter to keep track of number of clicks

  // Infinite loop to simulate mouse clicks
  while (1) {
    click_count++;
    click_mouse(display, 1,
                click_count); // Simulate left mouse button click (button 1)
    printf("Waiting for %d milliseconds before next click...\n", interval);
    usleep(interval * 1000); // Wait for the given interval in microseconds
  }

  XCloseDisplay(display);
  return 0;
}
