#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__

#include <string>

class EventLoop {

public:
    static void start(int argc, char **argv);

private:
    static void on_display();
    static void on_reshape(int width, int height);
    static void on_keyboard(unsigned char key, int x, int y);
    static void on_mouse(int button, int state, int x, int y);
    static void on_special(int key, int x, int y);
};

#endif
