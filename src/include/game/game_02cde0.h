#ifndef _IN_GAME_GAME_02CDE0_H
#define _IN_GAME_GAME_02CDE0_H
#include <ultra64.h>
#include "types.h"

u32 bodyGetRace(s32 bodynum);
bool bodyLoad(u32 bodynum);
u32 func0f02ce8c(void);
u32 func0f02d338(void);
struct animdata *func0f02d36c(u32 bodynum, u32 arg1, u32 arg2);
u32 func0f02d3f8(void);
u32 bodyGetHead(u32 bodynum);
u32 func0f02d4fc(void);
struct prop *propAllocateEyespy(struct pad *pad, s16 room);
u32 func0f02ddbc(void);

#endif
