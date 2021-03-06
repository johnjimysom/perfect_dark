#ifndef _IN_GAME_GAME_177E00_H
#define _IN_GAME_GAME_177E00_H
#include <ultra64.h>
#include "types.h"

s32 menuhandler00177e00(u32, u32, u32 *);
char *mpMenuTextInGameLimit(struct menu_item *item);
char *menutextPauseOrUnpause(s32 arg0);
char *menutextMatchTime(s32 arg0);
char *mpMenuTextWeaponDescription(struct menu_item *item);
u32 func0f1783a0(void);
char *mpMenuTextWeaponOfChoiceName(struct menu_item *item);
char *mpMenuTextAward1(struct menu_item *item);
char *mpMenuTextAward2(struct menu_item *item);
char *mpMenuTextPlacementWithSuffix(struct menu_item *item);
s32 menuhandler001785c4(u32, u32, u32 *);
s32 menuhandler001786d8(u32, u32, u32 *);
s32 menuhandler00178a94(u32, u32, u32 *);
char *mpMenuTextPlayerTitle(s32 arg0);
s32 menuhandler00178bf4(u32, u32, u32 *);
void mpPushPauseDialog(void);
void mpPushEndscreenDialog(u32 arg0, u32 playernum);
s32 menuhandlerMpEndGame(u32 operation, struct menu_item *item, s32 *value);
s32 menuhandler00178018(u32 operation, struct menu_item *item, s32 *value);
s32 menuhandlerMpInGameLimitLabel(u32 operation, struct menu_item *item, s32 *value);
s32 menuhandlerMpPause(u32 operation, struct menu_item *item, s32 *value);

#endif
