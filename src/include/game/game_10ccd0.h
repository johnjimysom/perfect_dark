#ifndef IN_GAME_GAME_10CCD0_H
#define IN_GAME_GAME_10CCD0_H
#include <ultra64.h>
#include "types.h"

void menudialogRetryMission(u32 operation, struct menu_dialog *dialog, struct menuthing **thingptr);
s32 menudialog0010dd28(u32, u32, u32 *);
s32 menudialog0010de58(u32, u32, u32 *);
s32 menuhandlerDeclineMission(u32 operation, struct menu_item *item, s32 *value);
s32 menuhandler0010e064(u32, u32, u32 *);
s32 menuhandlerContinueMission(u32 operation, struct menu_item *item, s32 *value);
s32 menuhandlerReplayLastLevel(u32 operation, struct menu_item *item, s32 *value);
s32 menuhandlerReplayPreviousMission(u32 operation, struct menu_item *item, s32 *value);
u32 func0f10ce74(void);
u32 func0f10cf2c(void);
char *soloMenuTextNumKills(struct menu_item *item);
char *soloMenuTextNumShots(struct menu_item *item);
char *soloMenuTextNumHeadShots(struct menu_item *item);
char *soloMenuTextNumBodyShots(struct menu_item *item);
char *soloMenuTextNumLimbShots(struct menu_item *item);
char *soloMenuTextNumOtherShots(struct menu_item *item);
char *soloMenuTextAccuracy(struct menu_item *item);
char *soloMenuTextMissionStatus(struct menu_item *item);
char *soloMenuTextAgentStatus(struct menu_item *item);
u32 func0f10d588(void);
u32 func0f10d61c(void);
u32 func0f10d678(void);
char *soloMenuTextMissionTime(struct menu_item *item);
u32 func0f10d730(void);
void func0f10d770(void);
void func0f10d910(s32 arg0);
char *soloMenuTextCheatName(struct menu_item *item);
char *soloMenuTextCheatName2(struct menu_item *item);
char *soloMenuTextTargetTime(struct menu_item *item);
u32 func0f10e588(void);
u32 func0f10e620(void);
u32 func0f10ecb4(void);
u32 func0f10ee40(void);
u32 func0f10ef10(void);

#endif
