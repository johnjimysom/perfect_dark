#ifndef IN_GAME_BONDGRAB_H
#define IN_GAME_BONDGRAB_H
#include <ultra64.h>
#include "types.h"

void currentPlayerGrabInit(void);
void currentPlayerUpdateGrabbedPropForRelease(void);
u32 func0f0ccbf0(void);
bool func0f0cd05c(f32 y);
u32 func0f0cd1a4(void);
bool func0f0cd970(struct coord *delta, f32 arg1, bool arg2);
u32 func0f0cdb04(void);
u32 func0f0cdb68(void);
u32 func0f0cdef0(void);
bool func0f0cdf64(struct coord *delta, struct coord *arg1, struct coord *arg2);
u32 func0f0cdfbc(void);
u32 func0f0ce0bc(void);
void currentPlayerUpdatePrevPosGrab(void);
void func0f0ce178(void);
void func0f0ce1ac(void);
void func0f0ce450(void);
void currentPlayerUpdateSpeedSidewaysGrab(f32 targetspeed, f32 accelspeed, s32 mult);
void currentPlayerUpdateSpeedForwardsGrab(f32 target, f32 speed);
void currentPlayerUpdateSpeedGrab(struct movedata *data);
void currentPlayerUpdateSpeedThetaGrab(void);
u32 func0f0ce924(void);
void func0f0ceec4(void);

#endif
