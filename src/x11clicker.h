// x11clicker Copyright (C) 2024 kernaltrap8
// This program comes with ABSOLUTELY NO WARRANTY
// This is free software, and you are welcome to redistribute it
// under certain conditions

/*
        x11clicker.h
*/

/*
        required defines
*/

#define VERSION "0.2"
#define HELP_BANNER "Usage: x11clicker <interval_in_milliseconds>"

/*
    function prototypes
*/

void click_mouse(Display *display, int button, int click_count);
int main(int argc, char *argv[]);
