#ifndef APP_H
#define APP_H

int mns_ShouldRun();

void mns_Init(int argc, char** argv);
void mns_Shutdown();

void mns_Update();

void mns_InitFrame();
void mns_RenderFrame();

void mns_PollEvents();


#endif
