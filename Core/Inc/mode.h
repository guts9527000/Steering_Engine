//
// Created by 24547 on 2026/6/2.
//

#ifndef STEERING_ENGINE_MODE_H
#define STEERING_ENGINE_MODE_H

typedef enum {
    Manual,
    Middle,
    Scan
}Mode;

typedef void (*ModeHandler)(void);

typedef struct {
    Mode mode;
    ModeHandler handler;
}ModeHandlerMap;

void Mode_Process(void);

extern Mode mode;

#endif //STEERING_ENGINE_MODE_H
