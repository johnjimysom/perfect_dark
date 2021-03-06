#include <ultra64.h>
#include "constants.h"
#include "game/bondmove.h"
#include "game/bondwalk.h"
#include "game/cheats.h"
#include "game/chr/chraction.h"
#include "game/data/data_000000.h"
#include "game/data/data_0083d0.h"
#include "game/data/data_00e460.h"
#include "game/data/data_0160b0.h"
#include "game/data/data_01a3a0.h"
#include "game/data/data_020df0.h"
#include "game/data/data_02da90.h"
#include "game/debug.h"
#include "game/game_005fd0.h"
#include "game/chr/chr.h"
#include "game/game_0601b0.h"
#include "game/game_092610.h"
#include "game/game_095320.h"
#include "game/game_097ba0.h"
#include "game/game_0b63b0.h"
#include "game/game_111600.h"
#include "game/game_113220.h"
#include "game/game_127910.h"
#include "game/propobj.h"
#include "gvars/gvars.h"
#include "lib/lib_04790.h"
#include "lib/lib_0e9d0.h"
#include "lib/lib_12dc0.h"
#include "lib/lib_16110.h"
#include "lib/lib_1a500.h"
#include "lib/lib_233c0.h"
#include "lib/lib_4a360.h"
#include "types.h"

void currentPlayerWalkInit(void)
{
	u32 prevmode = g_Vars.currentplayer->bondmovemode;
	s32 i;

	g_Vars.currentplayer->bondmovemode = MOVEMODE_WALK;
	g_Vars.currentplayer->bondonground = 0;
	g_Vars.currentplayer->unk1aec = 0;
	g_Vars.currentplayer->unk1af0 = NULL;
	g_Vars.currentplayer->unk1af4 = 0;

	g_Vars.currentplayer->swaypos = 0;
	g_Vars.currentplayer->swayoffset = 0;
	g_Vars.currentplayer->swaytarget = 0;
	g_Vars.currentplayer->swayoffset0 = 0;
	g_Vars.currentplayer->swayoffset2 = 0;

	g_Vars.currentplayer->bdeltapos.x = 0;
	g_Vars.currentplayer->bdeltapos.y = -0.0001f;
	g_Vars.currentplayer->bdeltapos.z = 0;

	g_Vars.currentplayer->isfalling = false;
	g_Vars.currentplayer->fallstart = 0;

	g_Vars.currentplayer->gunextraaimx = 0;
	g_Vars.currentplayer->gunextraaimy = 0;

	g_Vars.currentplayer->bondforcespeed.x = 0;
	g_Vars.currentplayer->bondforcespeed.y = 0;
	g_Vars.currentplayer->bondforcespeed.z = 0;

	if (prevmode != MOVEMODE_WALK && prevmode != MOVEMODE_CUTSCENE) {
		g_Vars.currentplayer->sumcrouch = 0;
		g_Vars.currentplayer->crouchheight = 0;
		g_Vars.currentplayer->crouchtime240 = 0;
		g_Vars.currentplayer->crouchfall = 0;
		g_Vars.currentplayer->crouchpos = CROUCH_STAND;
		g_Vars.currentplayer->autocrouchpos = CROUCH_STAND;
		g_Vars.currentplayer->crouchspeed = 0;
		g_Vars.currentplayer->crouchoffset = 0;
		g_Vars.currentplayer->guncloseroffset = 0;
	}

	currentPlayerUpdateCrouchOffsetWalk();

	if (prevmode != MOVEMODE_GRAB && prevmode != MOVEMODE_WALK) {
		for (i = 0; i != 3; i++) {
			g_Vars.currentplayer->bondshotspeed[i] = 0;
		}

		g_Vars.currentplayer->speedsideways = 0;
		g_Vars.currentplayer->speedstrafe = 0;
		g_Vars.currentplayer->speedgo = 0;
		g_Vars.currentplayer->speedboost = 1;
		g_Vars.currentplayer->speedmaxtime60 = 0;
		g_Vars.currentplayer->speedforwards = 0;
		g_Vars.currentplayer->speedtheta = 0;
		g_Vars.currentplayer->speedthetacontrol = 0;
	}

	if (g_Vars.currentplayer->walkinitmove) {
		struct coord delta;
		func00016b58(g_Vars.currentplayer->walkinitmtx,
				0, 0, 0,
				-g_Vars.currentplayer->bond2.unk1c.x, -g_Vars.currentplayer->bond2.unk1c.y, -g_Vars.currentplayer->bond2.unk1c.z,
				g_Vars.currentplayer->bond2.unk28.x, g_Vars.currentplayer->bond2.unk28.y, g_Vars.currentplayer->bond2.unk28.z);
		g_Vars.currentplayer->walkinitt = 0;
		g_Vars.currentplayer->walkinitt2 = 0;
		g_Vars.currentplayer->walkinitstart.x = g_Vars.currentplayer->prop->pos.x;
		g_Vars.currentplayer->walkinitstart.y = g_Vars.currentplayer->prop->pos.y;
		g_Vars.currentplayer->walkinitstart.z = g_Vars.currentplayer->prop->pos.z;

		delta.x = g_Vars.currentplayer->walkinitpos.x - g_Vars.currentplayer->prop->pos.x;
		delta.y = 0;
		delta.z = g_Vars.currentplayer->walkinitpos.z - g_Vars.currentplayer->prop->pos.z;

		func0f064178(g_Vars.currentplayer->hoverbike, false);
		func0f0c4250(&delta, 0, 1, 0, 63);
		func0f064178(g_Vars.currentplayer->hoverbike, true);
	} else if (prevmode != MOVEMODE_GRAB && prevmode != MOVEMODE_WALK) {
		g_Vars.currentplayer->moveinitspeed.x = 0;
		g_Vars.currentplayer->moveinitspeed.y = 0;
		g_Vars.currentplayer->moveinitspeed.z = 0;
	}
}

void currentPlayerSetSwayTarget(s32 value)
{
	g_Vars.currentplayer->swaytarget = value * 75.0f;
}

void currentPlayerAdjustCrouchPos(s32 value)
{
	g_Vars.currentplayer->crouchpos += value;

	if (g_Vars.currentplayer->crouchpos < CROUCH_SQUAT) {
		g_Vars.currentplayer->crouchpos = CROUCH_SQUAT;
	} else if (g_Vars.currentplayer->crouchpos > CROUCH_STAND) {
		g_Vars.currentplayer->crouchpos = CROUCH_STAND;
	}
}

const char var7f1ad750[] = "bondwalk.c";

GLOBAL_ASM(
glabel func0f0c3b38
/*  f0c3b38:	27bdff90 */ 	addiu	$sp,$sp,-112
/*  f0c3b3c:	3c02800a */ 	lui	$v0,%hi(g_Vars+0x284)
/*  f0c3b40:	8c42a244 */ 	lw	$v0,%lo(g_Vars+0x284)($v0)
/*  f0c3b44:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f0c3b48:	afa40070 */ 	sw	$a0,0x70($sp)
/*  f0c3b4c:	afa50074 */ 	sw	$a1,0x74($sp)
/*  f0c3b50:	8c4f00bc */ 	lw	$t7,0xbc($v0)
/*  f0c3b54:	c4840000 */ 	lwc1	$f4,0x0($a0)
/*  f0c3b58:	3c077f1b */ 	lui	$a3,%hi(var7f1ad750)
/*  f0c3b5c:	c5e60008 */ 	lwc1	$f6,0x8($t7)
/*  f0c3b60:	24e7d750 */ 	addiu	$a3,$a3,%lo(var7f1ad750)
/*  f0c3b64:	27a50034 */ 	addiu	$a1,$sp,0x34
/*  f0c3b68:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f0c3b6c:	240600df */ 	addiu	$a2,$zero,0xdf
/*  f0c3b70:	e7a80028 */ 	swc1	$f8,0x28($sp)
/*  f0c3b74:	8c5800bc */ 	lw	$t8,0xbc($v0)
/*  f0c3b78:	c70a000c */ 	lwc1	$f10,0xc($t8)
/*  f0c3b7c:	e7aa002c */ 	swc1	$f10,0x2c($sp)
/*  f0c3b80:	8c5900bc */ 	lw	$t9,0xbc($v0)
/*  f0c3b84:	c4900008 */ 	lwc1	$f16,0x8($a0)
/*  f0c3b88:	27a40040 */ 	addiu	$a0,$sp,0x40
/*  f0c3b8c:	c7320010 */ 	lwc1	$f18,0x10($t9)
/*  f0c3b90:	46128100 */ 	add.s	$f4,$f16,$f18
/*  f0c3b94:	0c009393 */ 	jal	func00024e4c
/*  f0c3b98:	e7a40030 */ 	swc1	$f4,0x30($sp)
/*  f0c3b9c:	c7a6003c */ 	lwc1	$f6,0x3c($sp)
/*  f0c3ba0:	c7a80048 */ 	lwc1	$f8,0x48($sp)
/*  f0c3ba4:	44801000 */ 	mtc1	$zero,$f2
/*  f0c3ba8:	c7aa0040 */ 	lwc1	$f10,0x40($sp)
/*  f0c3bac:	46083001 */ 	sub.s	$f0,$f6,$f8
/*  f0c3bb0:	c7b00034 */ 	lwc1	$f16,0x34($sp)
/*  f0c3bb4:	27a40058 */ 	addiu	$a0,$sp,0x58
/*  f0c3bb8:	27a5005c */ 	addiu	$a1,$sp,0x5c
/*  f0c3bbc:	46001032 */ 	c.eq.s	$f2,$f0
/*  f0c3bc0:	e7a00058 */ 	swc1	$f0,0x58($sp)
/*  f0c3bc4:	46105481 */ 	sub.s	$f18,$f10,$f16
/*  f0c3bc8:	e7a2005c */ 	swc1	$f2,0x5c($sp)
/*  f0c3bcc:	45000005 */ 	bc1f	.L0f0c3be4
/*  f0c3bd0:	e7b20060 */ 	swc1	$f18,0x60($sp)
/*  f0c3bd4:	46121032 */ 	c.eq.s	$f2,$f18
/*  f0c3bd8:	3c013f80 */ 	lui	$at,0x3f80
/*  f0c3bdc:	45030006 */ 	bc1tl	.L0f0c3bf8
/*  f0c3be0:	44812000 */ 	mtc1	$at,$f4
.L0f0c3be4:
/*  f0c3be4:	0c0011e4 */ 	jal	scaleTo1
/*  f0c3be8:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f0c3bec:	10000005 */ 	beqz	$zero,.L0f0c3c04
/*  f0c3bf0:	27a80064 */ 	addiu	$t0,$sp,0x64
/*  f0c3bf4:	44812000 */ 	mtc1	$at,$f4
.L0f0c3bf8:
/*  f0c3bf8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c3bfc:	e7a40060 */ 	swc1	$f4,0x60($sp)
/*  f0c3c00:	27a80064 */ 	addiu	$t0,$sp,0x64
.L0f0c3c04:
/*  f0c3c04:	afa80010 */ 	sw	$t0,0x10($sp)
/*  f0c3c08:	27a40040 */ 	addiu	$a0,$sp,0x40
/*  f0c3c0c:	27a50034 */ 	addiu	$a1,$sp,0x34
/*  f0c3c10:	27a60028 */ 	addiu	$a2,$sp,0x28
/*  f0c3c14:	0fc0b8f7 */ 	jal	func0f02e3dc
/*  f0c3c18:	27a70058 */ 	addiu	$a3,$sp,0x58
/*  f0c3c1c:	3c03800a */ 	lui	$v1,%hi(g_Vars)
/*  f0c3c20:	24639fc0 */ 	addiu	$v1,$v1,%lo(g_Vars)
/*  f0c3c24:	8c620284 */ 	lw	$v0,0x284($v1)
/*  f0c3c28:	c7a60028 */ 	lwc1	$f6,0x28($sp)
/*  f0c3c2c:	c460004c */ 	lwc1	$f0,0x4c($v1)
/*  f0c3c30:	8c4900bc */ 	lw	$t1,0xbc($v0)
/*  f0c3c34:	44801000 */ 	mtc1	$zero,$f2
/*  f0c3c38:	c7b20030 */ 	lwc1	$f18,0x30($sp)
/*  f0c3c3c:	c5280008 */ 	lwc1	$f8,0x8($t1)
/*  f0c3c40:	e7a20050 */ 	swc1	$f2,0x50($sp)
/*  f0c3c44:	8fa40074 */ 	lw	$a0,0x74($sp)
/*  f0c3c48:	46083281 */ 	sub.s	$f10,$f6,$f8
/*  f0c3c4c:	27a50064 */ 	addiu	$a1,$sp,0x64
/*  f0c3c50:	27a60058 */ 	addiu	$a2,$sp,0x58
/*  f0c3c54:	27a7004c */ 	addiu	$a3,$sp,0x4c
/*  f0c3c58:	46005403 */ 	div.s	$f16,$f10,$f0
/*  f0c3c5c:	e7b0004c */ 	swc1	$f16,0x4c($sp)
/*  f0c3c60:	8c4a00bc */ 	lw	$t2,0xbc($v0)
/*  f0c3c64:	c5440010 */ 	lwc1	$f4,0x10($t2)
/*  f0c3c68:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f0c3c6c:	46049181 */ 	sub.s	$f6,$f18,$f4
/*  f0c3c70:	46003203 */ 	div.s	$f8,$f6,$f0
/*  f0c3c74:	0fc20ba1 */ 	jal	func0f082e84
/*  f0c3c78:	e7a80054 */ 	swc1	$f8,0x54($sp)
/*  f0c3c7c:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f0c3c80:	27bd0070 */ 	addiu	$sp,$sp,0x70
/*  f0c3c84:	03e00008 */ 	jr	$ra
/*  f0c3c88:	00000000 */ 	sll	$zero,$zero,0x0
);

// Mismatch because the operands are swapped for the vector != 0 checks
//void func0f0c3b38(struct coord *reltarget, struct defaultobj *obj)
//{
//	struct coord posunk;
//	struct coord vector;
//	struct coord tween;
//	struct coord globalthinga;
//	struct coord globalthingb;
//	struct coord abstarget;
//
//	abstarget.x = reltarget->x + g_Vars.currentplayer->prop->pos.x;
//	abstarget.y = g_Vars.currentplayer->prop->pos.y;
//	abstarget.z = reltarget->z + g_Vars.currentplayer->prop->pos.z;
//
//	func00024e4c(&globalthinga, &globalthingb, 0xdf, "bondwalk.c");
//
//	vector.x = globalthingb.z - globalthinga.z;
//	vector.y = 0;
//	vector.z = globalthinga.x - globalthingb.x;
//
//	if (vector.x != 0 || vector.z != 0) {
//		scaleTo1(&vector.x, &vector.y, &vector.z);
//	} else {
//		vector.z = 1;
//	}
//
//	func0f02e3dc(&globalthinga, &globalthingb, &abstarget, &vector, &posunk);
//
//	tween.x = (abstarget.x - g_Vars.currentplayer->prop->pos.x) / g_Vars.lvupdate240freal;
//	tween.y = 0;
//	tween.z = (abstarget.z - g_Vars.currentplayer->prop->pos.z) / g_Vars.lvupdate240freal;
//
//	func0f082e84(obj, &posunk, &vector, &tween, false);
//}

const char var7f1ad75c[] = "bondwalk.c";

bool currentPlayerHasGapToCeiling(f32 y)
{
	bool result;
	struct coord newpos;
	s16 rooms[8];
	u32 stack;
	u32 something;
	f32 ymax;
	f32 ymin;
	f32 width;

	if (g_Vars.currentplayer->floorflags & FLOORFLAG_0100) {
		g_Vars.unk00032c = false;
	} else {
		g_Vars.unk00032c = true;
	}

	newpos.x = g_Vars.currentplayer->prop->pos.x;
	newpos.y = g_Vars.currentplayer->prop->pos.y + y;
	newpos.z = g_Vars.currentplayer->prop->pos.z;

	something = g_Vars.unk000328 ? 63 : 32;

	propPlayerGetBbox(g_Vars.currentplayer->prop, &width, &ymax, &ymin);
	func0f065e74(&g_Vars.currentplayer->prop->pos, g_Vars.currentplayer->prop->rooms, &newpos, rooms);
	func0f0cb79c(g_Vars.currentplayer, &newpos, rooms);
	func0f064178(g_Vars.currentplayer->prop, false);

	ymin -= 0.1f;

	result = func0002a684(&newpos, width, rooms, something, 1,
			ymax - g_Vars.currentplayer->prop->pos.y,
			ymin - g_Vars.currentplayer->prop->pos.y);

	func0f064178(g_Vars.currentplayer->prop, true);

	if (result == true) {
		g_Vars.currentplayer->prop->pos.y = newpos.y;
		func0f065c44(g_Vars.currentplayer->prop);
		roomsCopy(rooms, g_Vars.currentplayer->prop->rooms);
	}

	g_Vars.unk00032c = true;

	return result;
}

GLOBAL_ASM(
glabel func0f0c3e14
.late_rodata
glabel var7f1ad788
.word 0x40c907a9
.text
/*  f0c3e14:	27bdff48 */ 	addiu	$sp,$sp,-184
/*  f0c3e18:	afb00030 */ 	sw	$s0,0x30($sp)
/*  f0c3e1c:	3c10800a */ 	lui	$s0,%hi(g_Vars)
/*  f0c3e20:	26109fc0 */ 	addiu	$s0,$s0,%lo(g_Vars)
/*  f0c3e24:	8e020284 */ 	lw	$v0,0x284($s0)
/*  f0c3e28:	afbf0034 */ 	sw	$ra,0x34($sp)
/*  f0c3e2c:	afa400b8 */ 	sw	$a0,0xb8($sp)
/*  f0c3e30:	afa500bc */ 	sw	$a1,0xbc($sp)
/*  f0c3e34:	afa600c0 */ 	sw	$a2,0xc0($sp)
/*  f0c3e38:	afa700c4 */ 	sw	$a3,0xc4($sp)
/*  f0c3e3c:	afa00090 */ 	sw	$zero,0x90($sp)
/*  f0c3e40:	944e161c */ 	lhu	$t6,0x161c($v0)
/*  f0c3e44:	00803825 */ 	or	$a3,$a0,$zero
/*  f0c3e48:	24030001 */ 	addiu	$v1,$zero,0x1
/*  f0c3e4c:	31cf0100 */ 	andi	$t7,$t6,0x100
/*  f0c3e50:	11e00003 */ 	beqz	$t7,.L0f0c3e60
/*  f0c3e54:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f0c3e58:	10000002 */ 	beqz	$zero,.L0f0c3e64
/*  f0c3e5c:	ae00032c */ 	sw	$zero,0x32c($s0)
.L0f0c3e60:
/*  f0c3e60:	ae18032c */ 	sw	$t8,0x32c($s0)
.L0f0c3e64:
/*  f0c3e64:	8c5900bc */ 	lw	$t9,0xbc($v0)
/*  f0c3e68:	44808000 */ 	mtc1	$zero,$f16
/*  f0c3e6c:	c7240008 */ 	lwc1	$f4,0x8($t9)
/*  f0c3e70:	e7a400a4 */ 	swc1	$f4,0xa4($sp)
/*  f0c3e74:	8c4800bc */ 	lw	$t0,0xbc($v0)
/*  f0c3e78:	c506000c */ 	lwc1	$f6,0xc($t0)
/*  f0c3e7c:	e7a600a8 */ 	swc1	$f6,0xa8($sp)
/*  f0c3e80:	8c4900bc */ 	lw	$t1,0xbc($v0)
/*  f0c3e84:	c5280010 */ 	lwc1	$f8,0x10($t1)
/*  f0c3e88:	e7a800ac */ 	swc1	$f8,0xac($sp)
/*  f0c3e8c:	c4ea0000 */ 	lwc1	$f10,0x0($a3)
/*  f0c3e90:	460a8032 */ 	c.eq.s	$f16,$f10
/*  f0c3e94:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c3e98:	4502000c */ 	bc1fl	.L0f0c3ecc
/*  f0c3e9c:	8c441aec */ 	lw	$a0,0x1aec($v0)
/*  f0c3ea0:	c4f20004 */ 	lwc1	$f18,0x4($a3)
/*  f0c3ea4:	46128032 */ 	c.eq.s	$f16,$f18
/*  f0c3ea8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c3eac:	45020007 */ 	bc1fl	.L0f0c3ecc
/*  f0c3eb0:	8c441aec */ 	lw	$a0,0x1aec($v0)
/*  f0c3eb4:	c4e40008 */ 	lwc1	$f4,0x8($a3)
/*  f0c3eb8:	46048032 */ 	c.eq.s	$f16,$f4
/*  f0c3ebc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c3ec0:	450300a3 */ 	bc1tl	.L0f0c4150
/*  f0c3ec4:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0c3ec8:	8c441aec */ 	lw	$a0,0x1aec($v0)
.L0f0c3ecc:
/*  f0c3ecc:	00002825 */ 	or	$a1,$zero,$zero
/*  f0c3ed0:	50800006 */ 	beqzl	$a0,.L0f0c3eec
/*  f0c3ed4:	8c4400bc */ 	lw	$a0,0xbc($v0)
/*  f0c3ed8:	0fc1905e */ 	jal	func0f064178
/*  f0c3edc:	afa700b8 */ 	sw	$a3,0xb8($sp)
/*  f0c3ee0:	8fa700b8 */ 	lw	$a3,0xb8($sp)
/*  f0c3ee4:	8e020284 */ 	lw	$v0,0x284($s0)
/*  f0c3ee8:	8c4400bc */ 	lw	$a0,0xbc($v0)
.L0f0c3eec:
/*  f0c3eec:	afa700b8 */ 	sw	$a3,0xb8($sp)
/*  f0c3ef0:	0fc1905e */ 	jal	func0f064178
/*  f0c3ef4:	00002825 */ 	or	$a1,$zero,$zero
/*  f0c3ef8:	8fa700b8 */ 	lw	$a3,0xb8($sp)
/*  f0c3efc:	c7a600a4 */ 	lwc1	$f6,0xa4($sp)
/*  f0c3f00:	c7b200a8 */ 	lwc1	$f18,0xa8($sp)
/*  f0c3f04:	c4e80000 */ 	lwc1	$f8,0x0($a3)
/*  f0c3f08:	8e0a0328 */ 	lw	$t2,0x328($s0)
/*  f0c3f0c:	240c0020 */ 	addiu	$t4,$zero,0x20
/*  f0c3f10:	46083280 */ 	add.s	$f10,$f6,$f8
/*  f0c3f14:	c7a800ac */ 	lwc1	$f8,0xac($sp)
/*  f0c3f18:	8fab00c8 */ 	lw	$t3,0xc8($sp)
/*  f0c3f1c:	27a50054 */ 	addiu	$a1,$sp,0x54
/*  f0c3f20:	e7aa00a4 */ 	swc1	$f10,0xa4($sp)
/*  f0c3f24:	c4e40004 */ 	lwc1	$f4,0x4($a3)
/*  f0c3f28:	27a6005c */ 	addiu	$a2,$sp,0x5c
/*  f0c3f2c:	46049180 */ 	add.s	$f6,$f18,$f4
/*  f0c3f30:	e7a600a8 */ 	swc1	$f6,0xa8($sp)
/*  f0c3f34:	c4ea0008 */ 	lwc1	$f10,0x8($a3)
/*  f0c3f38:	460a4480 */ 	add.s	$f18,$f8,$f10
/*  f0c3f3c:	11400003 */ 	beqz	$t2,.L0f0c3f4c
/*  f0c3f40:	e7b200ac */ 	swc1	$f18,0xac($sp)
/*  f0c3f44:	10000002 */ 	beqz	$zero,.L0f0c3f50
/*  f0c3f48:	afab0060 */ 	sw	$t3,0x60($sp)
.L0f0c3f4c:
/*  f0c3f4c:	afac0060 */ 	sw	$t4,0x60($sp)
.L0f0c3f50:
/*  f0c3f50:	8e0d0284 */ 	lw	$t5,0x284($s0)
/*  f0c3f54:	27a70058 */ 	addiu	$a3,$sp,0x58
/*  f0c3f58:	0fc3082e */ 	jal	propPlayerGetBbox
/*  f0c3f5c:	8da400bc */ 	lw	$a0,0xbc($t5)
/*  f0c3f60:	c7a40054 */ 	lwc1	$f4,0x54($sp)
/*  f0c3f64:	c7a600c4 */ 	lwc1	$f6,0xc4($sp)
/*  f0c3f68:	8e0e0284 */ 	lw	$t6,0x284($s0)
/*  f0c3f6c:	27af0064 */ 	addiu	$t7,$sp,0x64
/*  f0c3f70:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f0c3f74:	24180014 */ 	addiu	$t8,$zero,0x14
/*  f0c3f78:	27a600a4 */ 	addiu	$a2,$sp,0xa4
/*  f0c3f7c:	27a70094 */ 	addiu	$a3,$sp,0x94
/*  f0c3f80:	e7a80054 */ 	swc1	$f8,0x54($sp)
/*  f0c3f84:	8dc200bc */ 	lw	$v0,0xbc($t6)
/*  f0c3f88:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f0c3f8c:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f0c3f90:	24440008 */ 	addiu	$a0,$v0,0x8
/*  f0c3f94:	0fc1977f */ 	jal	func0f065dfc
/*  f0c3f98:	24450028 */ 	addiu	$a1,$v0,0x28
/*  f0c3f9c:	8e040284 */ 	lw	$a0,0x284($s0)
/*  f0c3fa0:	27a500a4 */ 	addiu	$a1,$sp,0xa4
/*  f0c3fa4:	0fc32de7 */ 	jal	func0f0cb79c
/*  f0c3fa8:	27a60094 */ 	addiu	$a2,$sp,0x94
/*  f0c3fac:	8e080284 */ 	lw	$t0,0x284($s0)
/*  f0c3fb0:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f0c3fb4:	afb90090 */ 	sw	$t9,0x90($sp)
/*  f0c3fb8:	8d0200bc */ 	lw	$v0,0xbc($t0)
/*  f0c3fbc:	c7aa00a4 */ 	lwc1	$f10,0xa4($sp)
/*  f0c3fc0:	3c013f00 */ 	lui	$at,0x3f00
/*  f0c3fc4:	c4520008 */ 	lwc1	$f18,0x8($v0)
/*  f0c3fc8:	c7a80054 */ 	lwc1	$f8,0x54($sp)
/*  f0c3fcc:	c7a400ac */ 	lwc1	$f4,0xac($sp)
/*  f0c3fd0:	46125081 */ 	sub.s	$f2,$f10,$f18
/*  f0c3fd4:	44815000 */ 	mtc1	$at,$f10
/*  f0c3fd8:	c4460010 */ 	lwc1	$f6,0x10($v0)
/*  f0c3fdc:	c7b20054 */ 	lwc1	$f18,0x54($sp)
/*  f0c3fe0:	460a4002 */ 	mul.s	$f0,$f8,$f10
/*  f0c3fe4:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f0c3fe8:	46062301 */ 	sub.s	$f12,$f4,$f6
/*  f0c3fec:	4602003c */ 	c.lt.s	$f0,$f2
/*  f0c3ff0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c3ff4:	45030010 */ 	bc1tl	.L0f0c4038
/*  f0c3ff8:	8fa90060 */ 	lw	$t1,0x60($sp)
/*  f0c3ffc:	460c003c */ 	c.lt.s	$f0,$f12
/*  f0c4000:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4004:	4503000c */ 	bc1tl	.L0f0c4038
/*  f0c4008:	8fa90060 */ 	lw	$t1,0x60($sp)
/*  f0c400c:	46000387 */ 	neg.s	$f14,$f0
/*  f0c4010:	460e103c */ 	c.lt.s	$f2,$f14
/*  f0c4014:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4018:	45030007 */ 	bc1tl	.L0f0c4038
/*  f0c401c:	8fa90060 */ 	lw	$t1,0x60($sp)
/*  f0c4020:	460e603c */ 	c.lt.s	$f12,$f14
/*  f0c4024:	8fae0060 */ 	lw	$t6,0x60($sp)
/*  f0c4028:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f0c402c:	45020029 */ 	bc1fl	.L0f0c40d4
/*  f0c4030:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f0c4034:	8fa90060 */ 	lw	$t1,0x60($sp)
.L0f0c4038:
/*  f0c4038:	e7b20010 */ 	swc1	$f18,0x10($sp)
/*  f0c403c:	afaa0018 */ 	sw	$t2,0x18($sp)
/*  f0c4040:	afa90014 */ 	sw	$t1,0x14($sp)
/*  f0c4044:	c440000c */ 	lwc1	$f0,0xc($v0)
/*  f0c4048:	c7a4005c */ 	lwc1	$f4,0x5c($sp)
/*  f0c404c:	c7a80058 */ 	lwc1	$f8,0x58($sp)
/*  f0c4050:	24440008 */ 	addiu	$a0,$v0,0x8
/*  f0c4054:	46002181 */ 	sub.s	$f6,$f4,$f0
/*  f0c4058:	24450028 */ 	addiu	$a1,$v0,0x28
/*  f0c405c:	27a600a4 */ 	addiu	$a2,$sp,0xa4
/*  f0c4060:	46004281 */ 	sub.s	$f10,$f8,$f0
/*  f0c4064:	e7a6001c */ 	swc1	$f6,0x1c($sp)
/*  f0c4068:	27a70094 */ 	addiu	$a3,$sp,0x94
/*  f0c406c:	0c00b657 */ 	jal	func0002d95c
/*  f0c4070:	e7aa0020 */ 	swc1	$f10,0x20($sp)
/*  f0c4074:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0c4078:	14410024 */ 	bne	$v0,$at,.L0f0c410c
/*  f0c407c:	00401825 */ 	or	$v1,$v0,$zero
/*  f0c4080:	8e0b0284 */ 	lw	$t3,0x284($s0)
/*  f0c4084:	8fac0060 */ 	lw	$t4,0x60($sp)
/*  f0c4088:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f0c408c:	8d6200bc */ 	lw	$v0,0xbc($t3)
/*  f0c4090:	afad0014 */ 	sw	$t5,0x14($sp)
/*  f0c4094:	afac0010 */ 	sw	$t4,0x10($sp)
/*  f0c4098:	c440000c */ 	lwc1	$f0,0xc($v0)
/*  f0c409c:	c7b2005c */ 	lwc1	$f18,0x5c($sp)
/*  f0c40a0:	c7a60058 */ 	lwc1	$f6,0x58($sp)
/*  f0c40a4:	27a500a4 */ 	addiu	$a1,$sp,0xa4
/*  f0c40a8:	46009101 */ 	sub.s	$f4,$f18,$f0
/*  f0c40ac:	8fa60054 */ 	lw	$a2,0x54($sp)
/*  f0c40b0:	27a70094 */ 	addiu	$a3,$sp,0x94
/*  f0c40b4:	46003201 */ 	sub.s	$f8,$f6,$f0
/*  f0c40b8:	e7a40018 */ 	swc1	$f4,0x18($sp)
/*  f0c40bc:	24440008 */ 	addiu	$a0,$v0,0x8
/*  f0c40c0:	0c00aa7c */ 	jal	func0002a9f0
/*  f0c40c4:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f0c40c8:	10000010 */ 	beqz	$zero,.L0f0c410c
/*  f0c40cc:	00401825 */ 	or	$v1,$v0,$zero
/*  f0c40d0:	afae0010 */ 	sw	$t6,0x10($sp)
.L0f0c40d4:
/*  f0c40d4:	afaf0014 */ 	sw	$t7,0x14($sp)
/*  f0c40d8:	c440000c */ 	lwc1	$f0,0xc($v0)
/*  f0c40dc:	c7aa005c */ 	lwc1	$f10,0x5c($sp)
/*  f0c40e0:	c7a40058 */ 	lwc1	$f4,0x58($sp)
/*  f0c40e4:	24440008 */ 	addiu	$a0,$v0,0x8
/*  f0c40e8:	46005481 */ 	sub.s	$f18,$f10,$f0
/*  f0c40ec:	27a500a4 */ 	addiu	$a1,$sp,0xa4
/*  f0c40f0:	8fa60054 */ 	lw	$a2,0x54($sp)
/*  f0c40f4:	46002181 */ 	sub.s	$f6,$f4,$f0
/*  f0c40f8:	e7b20018 */ 	swc1	$f18,0x18($sp)
/*  f0c40fc:	27a70064 */ 	addiu	$a3,$sp,0x64
/*  f0c4100:	0c00aa7c */ 	jal	func0002a9f0
/*  f0c4104:	e7a6001c */ 	swc1	$f6,0x1c($sp)
/*  f0c4108:	00401825 */ 	or	$v1,$v0,$zero
.L0f0c410c:
/*  f0c410c:	8e180284 */ 	lw	$t8,0x284($s0)
/*  f0c4110:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f0c4114:	8f0400bc */ 	lw	$a0,0xbc($t8)
/*  f0c4118:	0fc1905e */ 	jal	func0f064178
/*  f0c411c:	afa300b4 */ 	sw	$v1,0xb4($sp)
/*  f0c4120:	8e190284 */ 	lw	$t9,0x284($s0)
/*  f0c4124:	44808000 */ 	mtc1	$zero,$f16
/*  f0c4128:	8fa300b4 */ 	lw	$v1,0xb4($sp)
/*  f0c412c:	8f241aec */ 	lw	$a0,0x1aec($t9)
/*  f0c4130:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f0c4134:	50800006 */ 	beqzl	$a0,.L0f0c4150
/*  f0c4138:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0c413c:	0fc1905e */ 	jal	func0f064178
/*  f0c4140:	afa300b4 */ 	sw	$v1,0xb4($sp)
/*  f0c4144:	44808000 */ 	mtc1	$zero,$f16
/*  f0c4148:	8fa300b4 */ 	lw	$v1,0xb4($sp)
/*  f0c414c:	24010001 */ 	addiu	$at,$zero,0x1
.L0f0c4150:
/*  f0c4150:	14610038 */ 	bne	$v1,$at,.L0f0c4234
/*  f0c4154:	8fa800c0 */ 	lw	$t0,0xc0($sp)
/*  f0c4158:	11000036 */ 	beqz	$t0,.L0f0c4234
/*  f0c415c:	3c0143b4 */ 	lui	$at,0x43b4
/*  f0c4160:	44811000 */ 	mtc1	$at,$f2
/*  f0c4164:	c7a800bc */ 	lwc1	$f8,0xbc($sp)
/*  f0c4168:	3c017f1b */ 	lui	$at,%hi(var7f1ad788)
/*  f0c416c:	c432d788 */ 	lwc1	$f18,%lo(var7f1ad788)($at)
/*  f0c4170:	46024282 */ 	mul.s	$f10,$f8,$f2
/*  f0c4174:	8e020284 */ 	lw	$v0,0x284($s0)
/*  f0c4178:	c4460144 */ 	lwc1	$f6,0x144($v0)
/*  f0c417c:	46125103 */ 	div.s	$f4,$f10,$f18
/*  f0c4180:	46043000 */ 	add.s	$f0,$f6,$f4
/*  f0c4184:	4610003c */ 	c.lt.s	$f0,$f16
/*  f0c4188:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c418c:	45020007 */ 	bc1fl	.L0f0c41ac
/*  f0c4190:	4600103e */ 	c.le.s	$f2,$f0
/*  f0c4194:	46020000 */ 	add.s	$f0,$f0,$f2
.L0f0c4198:
/*  f0c4198:	4610003c */ 	c.lt.s	$f0,$f16
/*  f0c419c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c41a0:	4503fffd */ 	bc1tl	.L0f0c4198
/*  f0c41a4:	46020000 */ 	add.s	$f0,$f0,$f2
/*  f0c41a8:	4600103e */ 	c.le.s	$f2,$f0
.L0f0c41ac:
/*  f0c41ac:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c41b0:	45020007 */ 	bc1fl	.L0f0c41d0
/*  f0c41b4:	e4400144 */ 	swc1	$f0,0x144($v0)
/*  f0c41b8:	46020001 */ 	sub.s	$f0,$f0,$f2
.L0f0c41bc:
/*  f0c41bc:	4600103e */ 	c.le.s	$f2,$f0
/*  f0c41c0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c41c4:	4503fffd */ 	bc1tl	.L0f0c41bc
/*  f0c41c8:	46020001 */ 	sub.s	$f0,$f0,$f2
/*  f0c41cc:	e4400144 */ 	swc1	$f0,0x144($v0)
.L0f0c41d0:
/*  f0c41d0:	8e090284 */ 	lw	$t1,0x284($s0)
/*  f0c41d4:	c7a800a4 */ 	lwc1	$f8,0xa4($sp)
/*  f0c41d8:	8d2a00bc */ 	lw	$t2,0xbc($t1)
/*  f0c41dc:	e5480008 */ 	swc1	$f8,0x8($t2)
/*  f0c41e0:	8e0b0284 */ 	lw	$t3,0x284($s0)
/*  f0c41e4:	c7aa00a8 */ 	lwc1	$f10,0xa8($sp)
/*  f0c41e8:	8d6c00bc */ 	lw	$t4,0xbc($t3)
/*  f0c41ec:	e58a000c */ 	swc1	$f10,0xc($t4)
/*  f0c41f0:	8e0d0284 */ 	lw	$t5,0x284($s0)
/*  f0c41f4:	c7b200ac */ 	lwc1	$f18,0xac($sp)
/*  f0c41f8:	8dae00bc */ 	lw	$t6,0xbc($t5)
/*  f0c41fc:	e5d20010 */ 	swc1	$f18,0x10($t6)
/*  f0c4200:	8faf0090 */ 	lw	$t7,0x90($sp)
/*  f0c4204:	51e0000c */ 	beqzl	$t7,.L0f0c4238
/*  f0c4208:	8fbf0034 */ 	lw	$ra,0x34($sp)
/*  f0c420c:	8e180284 */ 	lw	$t8,0x284($s0)
/*  f0c4210:	8f0400bc */ 	lw	$a0,0xbc($t8)
/*  f0c4214:	0fc19711 */ 	jal	func0f065c44
/*  f0c4218:	afa300b4 */ 	sw	$v1,0xb4($sp)
/*  f0c421c:	8e190284 */ 	lw	$t9,0x284($s0)
/*  f0c4220:	27a40094 */ 	addiu	$a0,$sp,0x94
/*  f0c4224:	8f2500bc */ 	lw	$a1,0xbc($t9)
/*  f0c4228:	0fc195e9 */ 	jal	roomsCopy
/*  f0c422c:	24a50028 */ 	addiu	$a1,$a1,0x28
/*  f0c4230:	8fa300b4 */ 	lw	$v1,0xb4($sp)
.L0f0c4234:
/*  f0c4234:	8fbf0034 */ 	lw	$ra,0x34($sp)
.L0f0c4238:
/*  f0c4238:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f0c423c:	ae08032c */ 	sw	$t0,0x32c($s0)
/*  f0c4240:	8fb00030 */ 	lw	$s0,0x30($sp)
/*  f0c4244:	27bd00b8 */ 	addiu	$sp,$sp,0xb8
/*  f0c4248:	03e00008 */ 	jr	$ra
/*  f0c424c:	00601025 */ 	or	$v0,$v1,$zero
);

GLOBAL_ASM(
glabel func0f0c4250
/*  f0c4250:	27bdff58 */ 	addiu	$sp,$sp,-168
/*  f0c4254:	8fae00b8 */ 	lw	$t6,0xb8($sp)
/*  f0c4258:	afbf0024 */ 	sw	$ra,0x24($sp)
/*  f0c425c:	afa400a8 */ 	sw	$a0,0xa8($sp)
/*  f0c4260:	afa500ac */ 	sw	$a1,0xac($sp)
/*  f0c4264:	afa600b0 */ 	sw	$a2,0xb0($sp)
/*  f0c4268:	afa700b4 */ 	sw	$a3,0xb4($sp)
/*  f0c426c:	0fc30f85 */ 	jal	func0f0c3e14
/*  f0c4270:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f0c4274:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0c4278:	10410135 */ 	beq	$v0,$at,.L0f0c4750
/*  f0c427c:	afa200a4 */ 	sw	$v0,0xa4($sp)
/*  f0c4280:	0c0093ac */ 	jal	func00024eb0
/*  f0c4284:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4288:	10400131 */ 	beqz	$v0,.L0f0c4750
/*  f0c428c:	afa200a0 */ 	sw	$v0,0xa0($sp)
/*  f0c4290:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c4294:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c4298:	8d0f0034 */ 	lw	$t7,0x34($t0)
/*  f0c429c:	59e0012d */ 	blezl	$t7,.L0f0c4754
/*  f0c42a0:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f0c42a4:	90430000 */ 	lbu	$v1,0x0($v0)
/*  f0c42a8:	24010002 */ 	addiu	$at,$zero,0x2
/*  f0c42ac:	54610046 */ 	bnel	$v1,$at,.L0f0c43c8
/*  f0c42b0:	24010003 */ 	addiu	$at,$zero,0x3
/*  f0c42b4:	8c430004 */ 	lw	$v1,0x4($v0)
/*  f0c42b8:	94780070 */ 	lhu	$t8,0x70($v1)
/*  f0c42bc:	33190400 */ 	andi	$t9,$t8,0x400
/*  f0c42c0:	53200124 */ 	beqzl	$t9,.L0f0c4754
/*  f0c42c4:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f0c42c8:	8d090284 */ 	lw	$t1,0x284($t0)
/*  f0c42cc:	27a40084 */ 	addiu	$a0,$sp,0x84
/*  f0c42d0:	27a50078 */ 	addiu	$a1,$sp,0x78
/*  f0c42d4:	8d2a00d8 */ 	lw	$t2,0xd8($t1)
/*  f0c42d8:	240601d1 */ 	addiu	$a2,$zero,0x1d1
/*  f0c42dc:	3c077f1b */ 	lui	$a3,%hi(var7f1ad75c)
/*  f0c42e0:	5540011c */ 	bnezl	$t2,.L0f0c4754
/*  f0c42e4:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f0c42e8:	0c009393 */ 	jal	func00024e4c
/*  f0c42ec:	24e7d75c */ 	addiu	$a3,$a3,%lo(var7f1ad75c)
/*  f0c42f0:	c7a40080 */ 	lwc1	$f4,0x80($sp)
/*  f0c42f4:	c7a6008c */ 	lwc1	$f6,0x8c($sp)
/*  f0c42f8:	44801000 */ 	mtc1	$zero,$f2
/*  f0c42fc:	c7a80084 */ 	lwc1	$f8,0x84($sp)
/*  f0c4300:	46062001 */ 	sub.s	$f0,$f4,$f6
/*  f0c4304:	c7aa0078 */ 	lwc1	$f10,0x78($sp)
/*  f0c4308:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c430c:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c4310:	46001032 */ 	c.eq.s	$f2,$f0
/*  f0c4314:	e7a00090 */ 	swc1	$f0,0x90($sp)
/*  f0c4318:	460a4101 */ 	sub.s	$f4,$f8,$f10
/*  f0c431c:	27a40090 */ 	addiu	$a0,$sp,0x90
/*  f0c4320:	e7a20094 */ 	swc1	$f2,0x94($sp)
/*  f0c4324:	45000004 */ 	bc1f	.L0f0c4338
/*  f0c4328:	e7a40098 */ 	swc1	$f4,0x98($sp)
/*  f0c432c:	46041032 */ 	c.eq.s	$f2,$f4
/*  f0c4330:	3c013f80 */ 	lui	$at,0x3f80
/*  f0c4334:	45010006 */ 	bc1t	.L0f0c4350
.L0f0c4338:
/*  f0c4338:	27a50094 */ 	addiu	$a1,$sp,0x94
/*  f0c433c:	0c0011e4 */ 	jal	scaleTo1
/*  f0c4340:	27a60098 */ 	addiu	$a2,$sp,0x98
/*  f0c4344:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c4348:	10000004 */ 	beqz	$zero,.L0f0c435c
/*  f0c434c:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
.L0f0c4350:
/*  f0c4350:	44813000 */ 	mtc1	$at,$f6
/*  f0c4354:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4358:	e7a60098 */ 	swc1	$f6,0x98($sp)
.L0f0c435c:
/*  f0c435c:	8d0b0284 */ 	lw	$t3,0x284($t0)
/*  f0c4360:	3c053ecc */ 	lui	$a1,0x3ecc
/*  f0c4364:	34a5cccd */ 	ori	$a1,$a1,0xcccd
/*  f0c4368:	8d6200bc */ 	lw	$v0,0xbc($t3)
/*  f0c436c:	27a60090 */ 	addiu	$a2,$sp,0x90
/*  f0c4370:	00003825 */ 	or	$a3,$zero,$zero
/*  f0c4374:	8c440004 */ 	lw	$a0,0x4($v0)
/*  f0c4378:	0fc0d05f */ 	jal	func0f03417c
/*  f0c437c:	afa20010 */ 	sw	$v0,0x10($sp)
/*  f0c4380:	3c01bf80 */ 	lui	$at,0xbf80
/*  f0c4384:	44814000 */ 	mtc1	$at,$f8
/*  f0c4388:	3c048009 */ 	lui	$a0,%hi(var80095200)
/*  f0c438c:	240cffff */ 	addiu	$t4,$zero,-1
/*  f0c4390:	240dffff */ 	addiu	$t5,$zero,-1
/*  f0c4394:	240effff */ 	addiu	$t6,$zero,-1
/*  f0c4398:	afae001c */ 	sw	$t6,0x1c($sp)
/*  f0c439c:	afad0018 */ 	sw	$t5,0x18($sp)
/*  f0c43a0:	afac0010 */ 	sw	$t4,0x10($sp)
/*  f0c43a4:	8c845200 */ 	lw	$a0,%lo(var80095200)($a0)
/*  f0c43a8:	240500f2 */ 	addiu	$a1,$zero,0xf2
/*  f0c43ac:	00003025 */ 	or	$a2,$zero,$zero
/*  f0c43b0:	2407ffff */ 	addiu	$a3,$zero,-1
/*  f0c43b4:	0c004241 */ 	jal	func00010904
/*  f0c43b8:	e7a80014 */ 	swc1	$f8,0x14($sp)
/*  f0c43bc:	100000e5 */ 	beqz	$zero,.L0f0c4754
/*  f0c43c0:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f0c43c4:	24010003 */ 	addiu	$at,$zero,0x3
.L0f0c43c8:
/*  f0c43c8:	5461008b */ 	bnel	$v1,$at,.L0f0c45f8
/*  f0c43cc:	24010006 */ 	addiu	$at,$zero,0x6
/*  f0c43d0:	8d180318 */ 	lw	$t8,0x318($t0)
/*  f0c43d4:	8c4f0004 */ 	lw	$t7,0x4($v0)
/*  f0c43d8:	00001825 */ 	or	$v1,$zero,$zero
/*  f0c43dc:	1300000c */ 	beqz	$t8,.L0f0c4410
/*  f0c43e0:	afaf0074 */ 	sw	$t7,0x74($sp)
/*  f0c43e4:	8d190284 */ 	lw	$t9,0x284($t0)
/*  f0c43e8:	01e02825 */ 	or	$a1,$t7,$zero
/*  f0c43ec:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f0c43f0:	8f2900bc */ 	lw	$t1,0xbc($t9)
/*  f0c43f4:	8d240004 */ 	lw	$a0,0x4($t1)
/*  f0c43f8:	0fc12aa3 */ 	jal	chrCompareTeams
/*  f0c43fc:	afa00044 */ 	sw	$zero,0x44($sp)
/*  f0c4400:	10400014 */ 	beqz	$v0,.L0f0c4454
/*  f0c4404:	8fa30044 */ 	lw	$v1,0x44($sp)
/*  f0c4408:	10000012 */ 	beqz	$zero,.L0f0c4454
/*  f0c440c:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f0c4410:
/*  f0c4410:	8faa0074 */ 	lw	$t2,0x74($sp)
/*  f0c4414:	8d4b0018 */ 	lw	$t3,0x18($t2)
/*  f0c4418:	000b61c0 */ 	sll	$t4,$t3,0x7
/*  f0c441c:	0581000d */ 	bgez	$t4,.L0f0c4454
/*  f0c4420:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4424:	8d0d029c */ 	lw	$t5,0x29c($t0)
/*  f0c4428:	05a2000a */ 	bltzl	$t5,.L0f0c4454
/*  f0c442c:	24030001 */ 	addiu	$v1,$zero,0x1
/*  f0c4430:	8d0e02a8 */ 	lw	$t6,0x2a8($t0)
/*  f0c4434:	8d0f0284 */ 	lw	$t7,0x284($t0)
/*  f0c4438:	55cf0006 */ 	bnel	$t6,$t7,.L0f0c4454
/*  f0c443c:	24030001 */ 	addiu	$v1,$zero,0x1
/*  f0c4440:	8d580014 */ 	lw	$t8,0x14($t2)
/*  f0c4444:	0018c840 */ 	sll	$t9,$t8,0x1
/*  f0c4448:	07200002 */ 	bltz	$t9,.L0f0c4454
/*  f0c444c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4450:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f0c4454:
/*  f0c4454:	106000be */ 	beqz	$v1,.L0f0c4750
/*  f0c4458:	8fa200a8 */ 	lw	$v0,0xa8($sp)
/*  f0c445c:	c4400008 */ 	lwc1	$f0,0x8($v0)
/*  f0c4460:	c4420000 */ 	lwc1	$f2,0x0($v0)
/*  f0c4464:	46000282 */ 	mul.s	$f10,$f0,$f0
/*  f0c4468:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c446c:	46021102 */ 	mul.s	$f4,$f2,$f2
/*  f0c4470:	0c012974 */ 	jal	sqrtf
/*  f0c4474:	46045300 */ 	add.s	$f12,$f10,$f4
/*  f0c4478:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c447c:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c4480:	c5060044 */ 	lwc1	$f6,0x44($t0)
/*  f0c4484:	8d090284 */ 	lw	$t1,0x284($t0)
/*  f0c4488:	8fa300a0 */ 	lw	$v1,0xa0($sp)
/*  f0c448c:	46060203 */ 	div.s	$f8,$f0,$f6
/*  f0c4490:	44801000 */ 	mtc1	$zero,$f2
/*  f0c4494:	e7a80054 */ 	swc1	$f8,0x54($sp)
/*  f0c4498:	8d2200bc */ 	lw	$v0,0xbc($t1)
/*  f0c449c:	c46a0008 */ 	lwc1	$f10,0x8($v1)
/*  f0c44a0:	c4660010 */ 	lwc1	$f6,0x10($v1)
/*  f0c44a4:	c4440008 */ 	lwc1	$f4,0x8($v0)
/*  f0c44a8:	c4480010 */ 	lwc1	$f8,0x10($v0)
/*  f0c44ac:	46045381 */ 	sub.s	$f14,$f10,$f4
/*  f0c44b0:	46083401 */ 	sub.s	$f16,$f6,$f8
/*  f0c44b4:	46027032 */ 	c.eq.s	$f14,$f2
/*  f0c44b8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c44bc:	45000005 */ 	bc1f	.L0f0c44d4
/*  f0c44c0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c44c4:	46028032 */ 	c.eq.s	$f16,$f2
/*  f0c44c8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c44cc:	450300a1 */ 	bc1tl	.L0f0c4754
/*  f0c44d0:	8fbf0024 */ 	lw	$ra,0x24($sp)
.L0f0c44d4:
/*  f0c44d4:	460e7282 */ 	mul.s	$f10,$f14,$f14
/*  f0c44d8:	e7ae0050 */ 	swc1	$f14,0x50($sp)
/*  f0c44dc:	e7b0004c */ 	swc1	$f16,0x4c($sp)
/*  f0c44e0:	46108102 */ 	mul.s	$f4,$f16,$f16
/*  f0c44e4:	0c012974 */ 	jal	sqrtf
/*  f0c44e8:	46045300 */ 	add.s	$f12,$f10,$f4
/*  f0c44ec:	44801000 */ 	mtc1	$zero,$f2
/*  f0c44f0:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c44f4:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c44f8:	4600103c */ 	c.lt.s	$f2,$f0
/*  f0c44fc:	c7ae0050 */ 	lwc1	$f14,0x50($sp)
/*  f0c4500:	c7b0004c */ 	lwc1	$f16,0x4c($sp)
/*  f0c4504:	c7a60054 */ 	lwc1	$f6,0x54($sp)
/*  f0c4508:	45020092 */ 	bc1fl	.L0f0c4754
/*  f0c450c:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f0c4510:	46003303 */ 	div.s	$f12,$f6,$f0
/*  f0c4514:	3c013f00 */ 	lui	$at,0x3f00
/*  f0c4518:	44819000 */ 	mtc1	$at,$f18
/*  f0c451c:	8fa40074 */ 	lw	$a0,0x74($sp)
/*  f0c4520:	8fa200a0 */ 	lw	$v0,0xa0($sp)
/*  f0c4524:	27a50068 */ 	addiu	$a1,$sp,0x68
/*  f0c4528:	27a60058 */ 	addiu	$a2,$sp,0x58
/*  f0c452c:	00003825 */ 	or	$a3,$zero,$zero
/*  f0c4530:	460c7382 */ 	mul.s	$f14,$f14,$f12
/*  f0c4534:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4538:	460c8402 */ 	mul.s	$f16,$f16,$f12
/*  f0c453c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4540:	460e9082 */ 	mul.s	$f2,$f18,$f14
/*  f0c4544:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4548:	46109202 */ 	mul.s	$f8,$f18,$f16
/*  f0c454c:	e4820304 */ 	swc1	$f2,0x304($a0)
/*  f0c4550:	e4880308 */ 	swc1	$f8,0x308($a0)
/*  f0c4554:	c5000044 */ 	lwc1	$f0,0x44($t0)
/*  f0c4558:	c4440008 */ 	lwc1	$f4,0x8($v0)
/*  f0c455c:	46001282 */ 	mul.s	$f10,$f2,$f0
/*  f0c4560:	46045180 */ 	add.s	$f6,$f10,$f4
/*  f0c4564:	e7a60068 */ 	swc1	$f6,0x68($sp)
/*  f0c4568:	c448000c */ 	lwc1	$f8,0xc($v0)
/*  f0c456c:	e7a8006c */ 	swc1	$f8,0x6c($sp)
/*  f0c4570:	c48a0308 */ 	lwc1	$f10,0x308($a0)
/*  f0c4574:	c4460010 */ 	lwc1	$f6,0x10($v0)
/*  f0c4578:	46005102 */ 	mul.s	$f4,$f10,$f0
/*  f0c457c:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f0c4580:	0fc079fd */ 	jal	func0f01e7f4
/*  f0c4584:	e7a80070 */ 	swc1	$f8,0x70($sp)
/*  f0c4588:	8fa400a0 */ 	lw	$a0,0xa0($sp)
/*  f0c458c:	c7aa0068 */ 	lwc1	$f10,0x68($sp)
/*  f0c4590:	e48a0008 */ 	swc1	$f10,0x8($a0)
/*  f0c4594:	c7a4006c */ 	lwc1	$f4,0x6c($sp)
/*  f0c4598:	e484000c */ 	swc1	$f4,0xc($a0)
/*  f0c459c:	c7a60070 */ 	lwc1	$f6,0x70($sp)
/*  f0c45a0:	0fc19711 */ 	jal	func0f065c44
/*  f0c45a4:	e4860010 */ 	swc1	$f6,0x10($a0)
/*  f0c45a8:	8fa500a0 */ 	lw	$a1,0xa0($sp)
/*  f0c45ac:	27a40058 */ 	addiu	$a0,$sp,0x58
/*  f0c45b0:	0fc195e9 */ 	jal	roomsCopy
/*  f0c45b4:	24a50028 */ 	addiu	$a1,$a1,0x28
/*  f0c45b8:	0fc0882b */ 	jal	func0f0220ac
/*  f0c45bc:	8fa40074 */ 	lw	$a0,0x74($sp)
/*  f0c45c0:	8fab0074 */ 	lw	$t3,0x74($sp)
/*  f0c45c4:	27a50068 */ 	addiu	$a1,$sp,0x68
/*  f0c45c8:	0c006b4d */ 	jal	func0001ad34
/*  f0c45cc:	8d640020 */ 	lw	$a0,0x20($t3)
/*  f0c45d0:	8fac00b8 */ 	lw	$t4,0xb8($sp)
/*  f0c45d4:	8fa400a8 */ 	lw	$a0,0xa8($sp)
/*  f0c45d8:	8fa500ac */ 	lw	$a1,0xac($sp)
/*  f0c45dc:	8fa600b0 */ 	lw	$a2,0xb0($sp)
/*  f0c45e0:	8fa700b4 */ 	lw	$a3,0xb4($sp)
/*  f0c45e4:	0fc30f85 */ 	jal	func0f0c3e14
/*  f0c45e8:	afac0010 */ 	sw	$t4,0x10($sp)
/*  f0c45ec:	10000058 */ 	beqz	$zero,.L0f0c4750
/*  f0c45f0:	afa200a4 */ 	sw	$v0,0xa4($sp)
/*  f0c45f4:	24010006 */ 	addiu	$at,$zero,0x6
.L0f0c45f8:
/*  f0c45f8:	10610055 */ 	beq	$v1,$at,.L0f0c4750
/*  f0c45fc:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0c4600:	54610054 */ 	bnel	$v1,$at,.L0f0c4754
/*  f0c4604:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f0c4608:	8c460004 */ 	lw	$a2,0x4($v0)
/*  f0c460c:	8cc30040 */ 	lw	$v1,0x40($a2)
/*  f0c4610:	00036940 */ 	sll	$t5,$v1,0x5
/*  f0c4614:	05a0004e */ 	bltz	$t5,.L0f0c4750
/*  f0c4618:	00037100 */ 	sll	$t6,$v1,0x4
/*  f0c461c:	05c2004d */ 	bltzl	$t6,.L0f0c4754
/*  f0c4620:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f0c4624:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c4628:	8c6f1af0 */ 	lw	$t7,0x1af0($v1)
/*  f0c462c:	55e00008 */ 	bnezl	$t7,.L0f0c4650
/*  f0c4630:	8cd80010 */ 	lw	$t8,0x10($a2)
/*  f0c4634:	90ca0003 */ 	lbu	$t2,0x3($a2)
/*  f0c4638:	2401002d */ 	addiu	$at,$zero,0x2d
/*  f0c463c:	55410004 */ 	bnel	$t2,$at,.L0f0c4650
/*  f0c4640:	8cd80010 */ 	lw	$t8,0x10($a2)
/*  f0c4644:	10000042 */ 	beqz	$zero,.L0f0c4750
/*  f0c4648:	ac621aec */ 	sw	$v0,0x1aec($v1)
/*  f0c464c:	8cd80010 */ 	lw	$t8,0x10($a2)
.L0f0c4650:
/*  f0c4650:	33190001 */ 	andi	$t9,$t8,0x1
/*  f0c4654:	5320003f */ 	beqzl	$t9,.L0f0c4754
/*  f0c4658:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f0c465c:	ac600178 */ 	sw	$zero,0x178($v1)
/*  f0c4660:	8cc90040 */ 	lw	$t1,0x40($a2)
/*  f0c4664:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f0c4668:	8fa400a8 */ 	lw	$a0,0xa8($sp)
/*  f0c466c:	312b0080 */ 	andi	$t3,$t1,0x80
/*  f0c4670:	11600007 */ 	beqz	$t3,.L0f0c4690
/*  f0c4674:	00c02825 */ 	or	$a1,$a2,$zero
/*  f0c4678:	8ccc0048 */ 	lw	$t4,0x48($a2)
/*  f0c467c:	8d8d0000 */ 	lw	$t5,0x0($t4)
/*  f0c4680:	31ae1000 */ 	andi	$t6,$t5,0x1000
/*  f0c4684:	11c00002 */ 	beqz	$t6,.L0f0c4690
/*  f0c4688:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c468c:	00001025 */ 	or	$v0,$zero,$zero
.L0f0c4690:
/*  f0c4690:	50400030 */ 	beqzl	$v0,.L0f0c4754
/*  f0c4694:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f0c4698:	0fc30ece */ 	jal	func0f0c3b38
/*  f0c469c:	afa60040 */ 	sw	$a2,0x40($sp)
/*  f0c46a0:	8fa60040 */ 	lw	$a2,0x40($sp)
/*  f0c46a4:	8ccf0040 */ 	lw	$t7,0x40($a2)
/*  f0c46a8:	31ea0080 */ 	andi	$t2,$t7,0x80
/*  f0c46ac:	51400029 */ 	beqzl	$t2,.L0f0c4754
/*  f0c46b0:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f0c46b4:	8cd80048 */ 	lw	$t8,0x48($a2)
/*  f0c46b8:	00c02025 */ 	or	$a0,$a2,$zero
/*  f0c46bc:	27a50034 */ 	addiu	$a1,$sp,0x34
/*  f0c46c0:	8f190000 */ 	lw	$t9,0x0($t8)
/*  f0c46c4:	33290800 */ 	andi	$t1,$t9,0x800
/*  f0c46c8:	51200022 */ 	beqzl	$t1,.L0f0c4754
/*  f0c46cc:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f0c46d0:	afa00034 */ 	sw	$zero,0x34($sp)
/*  f0c46d4:	0fc1cf1b */ 	jal	func0f073c6c
/*  f0c46d8:	afa60040 */ 	sw	$a2,0x40($sp)
/*  f0c46dc:	8fa60040 */ 	lw	$a2,0x40($sp)
/*  f0c46e0:	8ccb0040 */ 	lw	$t3,0x40($a2)
/*  f0c46e4:	316c0080 */ 	andi	$t4,$t3,0x80
/*  f0c46e8:	11800010 */ 	beqz	$t4,.L0f0c472c
/*  f0c46ec:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c46f0:	8cc30048 */ 	lw	$v1,0x48($a2)
/*  f0c46f4:	8c6d0000 */ 	lw	$t5,0x0($v1)
/*  f0c46f8:	35ae1000 */ 	ori	$t6,$t5,0x1000
/*  f0c46fc:	10400006 */ 	beqz	$v0,.L0f0c4718
/*  f0c4700:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*  f0c4704:	8cc30048 */ 	lw	$v1,0x48($a2)
/*  f0c4708:	8c6f0000 */ 	lw	$t7,0x0($v1)
/*  f0c470c:	35ea2000 */ 	ori	$t2,$t7,0x2000
/*  f0c4710:	10000006 */ 	beqz	$zero,.L0f0c472c
/*  f0c4714:	ac6a0000 */ 	sw	$t2,0x0($v1)
.L0f0c4718:
/*  f0c4718:	8cc30048 */ 	lw	$v1,0x48($a2)
/*  f0c471c:	2401dfff */ 	addiu	$at,$zero,-8193
/*  f0c4720:	8c780000 */ 	lw	$t8,0x0($v1)
/*  f0c4724:	0301c824 */ 	and	$t9,$t8,$at
/*  f0c4728:	ac790000 */ 	sw	$t9,0x0($v1)
.L0f0c472c:
/*  f0c472c:	10400008 */ 	beqz	$v0,.L0f0c4750
/*  f0c4730:	8fa400a8 */ 	lw	$a0,0xa8($sp)
/*  f0c4734:	8fa900b8 */ 	lw	$t1,0xb8($sp)
/*  f0c4738:	8fa500ac */ 	lw	$a1,0xac($sp)
/*  f0c473c:	8fa600b0 */ 	lw	$a2,0xb0($sp)
/*  f0c4740:	8fa700b4 */ 	lw	$a3,0xb4($sp)
/*  f0c4744:	0fc30f85 */ 	jal	func0f0c3e14
/*  f0c4748:	afa90010 */ 	sw	$t1,0x10($sp)
/*  f0c474c:	afa200a4 */ 	sw	$v0,0xa4($sp)
.L0f0c4750:
/*  f0c4750:	8fbf0024 */ 	lw	$ra,0x24($sp)
.L0f0c4754:
/*  f0c4754:	8fa200a4 */ 	lw	$v0,0xa4($sp)
/*  f0c4758:	27bd00a8 */ 	addiu	$sp,$sp,0xa8
/*  f0c475c:	03e00008 */ 	jr	$ra
/*  f0c4760:	00000000 */ 	sll	$zero,$zero,0x0
);

bool func0f0c4764(struct coord *delta, struct coord *arg1, struct coord *arg2, s32 arg3)
{
	bool result = func0f0c4250(delta, 0, true, 0, arg3);

	if (!result) {
		func00024e4c(arg1, arg2, 0x25f, "bondwalk.c");
	}

	return result;
}

s32 func0f0c47d0(struct coord *a, struct coord *b, struct coord *c,
		struct coord *d, struct coord *e, s32 arg6)
{
	struct coord quarter;
	bool result;

	if (func00024ea4()) {
		f32 mult = func00024e98();
		quarter.x = a->x * mult * 0.25f;
		quarter.y = a->y * mult * 0.25f;
		quarter.z = a->z * mult * 0.25f;
		result = func0f0c4250(&quarter, 0, 1, 0, arg6);

		if (result == 1) {
			return 1;
		}

		if (result == 0) {
			func00024e4c(d, e, 0x27b, "bondwalk.c");

			if (b->x != d->x
					|| b->y != d->y
					|| b->z != d->z
					|| c->x != e->x
					|| c->y != e->y
					|| c->z != e->z) {
				return 0;
			}
		}
	}

	return -1;
}

GLOBAL_ASM(
glabel func0f0c494c
/*  f0c494c:	27bdffb8 */ 	addiu	$sp,$sp,-72
/*  f0c4950:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f0c4954:	afa40048 */ 	sw	$a0,0x48($sp)
/*  f0c4958:	afa70054 */ 	sw	$a3,0x54($sp)
/*  f0c495c:	c4c20000 */ 	lwc1	$f2,0x0($a2)
/*  f0c4960:	c4a00000 */ 	lwc1	$f0,0x0($a1)
/*  f0c4964:	46020032 */ 	c.eq.s	$f0,$f2
/*  f0c4968:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c496c:	45020009 */ 	bc1fl	.L0f0c4994
/*  f0c4970:	46001201 */ 	sub.s	$f8,$f2,$f0
/*  f0c4974:	c4a40008 */ 	lwc1	$f4,0x8($a1)
/*  f0c4978:	c4c60008 */ 	lwc1	$f6,0x8($a2)
/*  f0c497c:	2402ffff */ 	addiu	$v0,$zero,-1
/*  f0c4980:	46062032 */ 	c.eq.s	$f4,$f6
/*  f0c4984:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4988:	45010030 */ 	bc1t	.L0f0c4a4c
/*  f0c498c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4990:	46001201 */ 	sub.s	$f8,$f2,$f0
.L0f0c4994:
/*  f0c4994:	44807000 */ 	mtc1	$zero,$f14
/*  f0c4998:	e7a80038 */ 	swc1	$f8,0x38($sp)
/*  f0c499c:	e7ae003c */ 	swc1	$f14,0x3c($sp)
/*  f0c49a0:	c4b00008 */ 	lwc1	$f16,0x8($a1)
/*  f0c49a4:	c4ca0008 */ 	lwc1	$f10,0x8($a2)
/*  f0c49a8:	c7a80038 */ 	lwc1	$f8,0x38($sp)
/*  f0c49ac:	46105481 */ 	sub.s	$f18,$f10,$f16
/*  f0c49b0:	e7b20040 */ 	swc1	$f18,0x40($sp)
/*  f0c49b4:	c7a40040 */ 	lwc1	$f4,0x40($sp)
/*  f0c49b8:	46042182 */ 	mul.s	$f6,$f4,$f4
/*  f0c49bc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c49c0:	46084282 */ 	mul.s	$f10,$f8,$f8
/*  f0c49c4:	0c012974 */ 	jal	sqrtf
/*  f0c49c8:	460a3300 */ 	add.s	$f12,$f6,$f10
/*  f0c49cc:	3c013f80 */ 	lui	$at,0x3f80
/*  f0c49d0:	44818000 */ 	mtc1	$at,$f16
/*  f0c49d4:	c7b20038 */ 	lwc1	$f18,0x38($sp)
/*  f0c49d8:	c7a80040 */ 	lwc1	$f8,0x40($sp)
/*  f0c49dc:	46008083 */ 	div.s	$f2,$f16,$f0
/*  f0c49e0:	8fa20048 */ 	lw	$v0,0x48($sp)
/*  f0c49e4:	44807000 */ 	mtc1	$zero,$f14
/*  f0c49e8:	8fae0054 */ 	lw	$t6,0x54($sp)
/*  f0c49ec:	27a4002c */ 	addiu	$a0,$sp,0x2c
/*  f0c49f0:	44057000 */ 	mfc1	$a1,$f14
/*  f0c49f4:	44077000 */ 	mfc1	$a3,$f14
/*  f0c49f8:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f0c49fc:	46029102 */ 	mul.s	$f4,$f18,$f2
/*  f0c4a00:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4a04:	46024182 */ 	mul.s	$f6,$f8,$f2
/*  f0c4a08:	e7a40038 */ 	swc1	$f4,0x38($sp)
/*  f0c4a0c:	e7a60040 */ 	swc1	$f6,0x40($sp)
/*  f0c4a10:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f0c4a14:	c4520000 */ 	lwc1	$f18,0x0($v0)
/*  f0c4a18:	e7ae0030 */ 	swc1	$f14,0x30($sp)
/*  f0c4a1c:	460a3402 */ 	mul.s	$f16,$f6,$f10
/*  f0c4a20:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f0c4a24:	46049202 */ 	mul.s	$f8,$f18,$f4
/*  f0c4a28:	46088300 */ 	add.s	$f12,$f16,$f8
/*  f0c4a2c:	460c2282 */ 	mul.s	$f10,$f4,$f12
/*  f0c4a30:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4a34:	460c3482 */ 	mul.s	$f18,$f6,$f12
/*  f0c4a38:	e7aa002c */ 	swc1	$f10,0x2c($sp)
/*  f0c4a3c:	0fc31094 */ 	jal	func0f0c4250
/*  f0c4a40:	e7b20034 */ 	swc1	$f18,0x34($sp)
/*  f0c4a44:	10000002 */ 	beqz	$zero,.L0f0c4a50
/*  f0c4a48:	8fbf001c */ 	lw	$ra,0x1c($sp)
.L0f0c4a4c:
/*  f0c4a4c:	8fbf001c */ 	lw	$ra,0x1c($sp)
.L0f0c4a50:
/*  f0c4a50:	27bd0048 */ 	addiu	$sp,$sp,0x48
/*  f0c4a54:	03e00008 */ 	jr	$ra
/*  f0c4a58:	00000000 */ 	sll	$zero,$zero,0x0
);

GLOBAL_ASM(
glabel func0f0c4a5c
/*  f0c4a5c:	27bdffa0 */ 	addiu	$sp,$sp,-96
/*  f0c4a60:	3c0e800a */ 	lui	$t6,%hi(g_Vars+0x284)
/*  f0c4a64:	8dcea244 */ 	lw	$t6,%lo(g_Vars+0x284)($t6)
/*  f0c4a68:	afb20028 */ 	sw	$s2,0x28($sp)
/*  f0c4a6c:	afb10024 */ 	sw	$s1,0x24($sp)
/*  f0c4a70:	afb00020 */ 	sw	$s0,0x20($sp)
/*  f0c4a74:	00a08025 */ 	or	$s0,$a1,$zero
/*  f0c4a78:	00808825 */ 	or	$s1,$a0,$zero
/*  f0c4a7c:	00c09025 */ 	or	$s2,$a2,$zero
/*  f0c4a80:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f0c4a84:	afa7006c */ 	sw	$a3,0x6c($sp)
/*  f0c4a88:	27a70040 */ 	addiu	$a3,$sp,0x40
/*  f0c4a8c:	27a60044 */ 	addiu	$a2,$sp,0x44
/*  f0c4a90:	27a50038 */ 	addiu	$a1,$sp,0x38
/*  f0c4a94:	0fc3082e */ 	jal	propPlayerGetBbox
/*  f0c4a98:	8dc400bc */ 	lw	$a0,0xbc($t6)
/*  f0c4a9c:	3c03800a */ 	lui	$v1,%hi(g_Vars+0x284)
/*  f0c4aa0:	8c63a244 */ 	lw	$v1,%lo(g_Vars+0x284)($v1)
/*  f0c4aa4:	c6240000 */ 	lwc1	$f4,0x0($s1)
/*  f0c4aa8:	c60a0000 */ 	lwc1	$f10,0x0($s0)
/*  f0c4aac:	8c6f00bc */ 	lw	$t7,0xbc($v1)
/*  f0c4ab0:	c5e60008 */ 	lwc1	$f6,0x8($t7)
/*  f0c4ab4:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f0c4ab8:	46085401 */ 	sub.s	$f16,$f10,$f8
/*  f0c4abc:	e7b00054 */ 	swc1	$f16,0x54($sp)
/*  f0c4ac0:	8c7800bc */ 	lw	$t8,0xbc($v1)
/*  f0c4ac4:	c6320008 */ 	lwc1	$f18,0x8($s1)
/*  f0c4ac8:	c60a0008 */ 	lwc1	$f10,0x8($s0)
/*  f0c4acc:	c7040010 */ 	lwc1	$f4,0x10($t8)
/*  f0c4ad0:	c7b00038 */ 	lwc1	$f16,0x38($sp)
/*  f0c4ad4:	46049180 */ 	add.s	$f6,$f18,$f4
/*  f0c4ad8:	46108002 */ 	mul.s	$f0,$f16,$f16
/*  f0c4adc:	46065201 */ 	sub.s	$f8,$f10,$f6
/*  f0c4ae0:	c7aa0054 */ 	lwc1	$f10,0x54($sp)
/*  f0c4ae4:	e7a8005c */ 	swc1	$f8,0x5c($sp)
/*  f0c4ae8:	c7b2005c */ 	lwc1	$f18,0x5c($sp)
/*  f0c4aec:	46129102 */ 	mul.s	$f4,$f18,$f18
/*  f0c4af0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4af4:	460a5182 */ 	mul.s	$f6,$f10,$f10
/*  f0c4af8:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f0c4afc:	4600403e */ 	c.le.s	$f8,$f0
/*  f0c4b00:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4b04:	45000043 */ 	bc1f	.L0f0c4c14
/*  f0c4b08:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4b0c:	8c6200bc */ 	lw	$v0,0xbc($v1)
/*  f0c4b10:	c6100000 */ 	lwc1	$f16,0x0($s0)
/*  f0c4b14:	c4520008 */ 	lwc1	$f18,0x8($v0)
/*  f0c4b18:	46128032 */ 	c.eq.s	$f16,$f18
/*  f0c4b1c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4b20:	45020008 */ 	bc1fl	.L0f0c4b44
/*  f0c4b24:	c6060008 */ 	lwc1	$f6,0x8($s0)
/*  f0c4b28:	c60a0008 */ 	lwc1	$f10,0x8($s0)
/*  f0c4b2c:	c4440010 */ 	lwc1	$f4,0x10($v0)
/*  f0c4b30:	46045032 */ 	c.eq.s	$f10,$f4
/*  f0c4b34:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4b38:	45030091 */ 	bc1tl	.L0f0c4d80
/*  f0c4b3c:	00001025 */ 	or	$v0,$zero,$zero
/*  f0c4b40:	c6060008 */ 	lwc1	$f6,0x8($s0)
.L0f0c4b44:
/*  f0c4b44:	c4480010 */ 	lwc1	$f8,0x10($v0)
/*  f0c4b48:	44807000 */ 	mtc1	$zero,$f14
/*  f0c4b4c:	46083401 */ 	sub.s	$f16,$f6,$f8
/*  f0c4b50:	e7ae0058 */ 	swc1	$f14,0x58($sp)
/*  f0c4b54:	46008487 */ 	neg.s	$f18,$f16
/*  f0c4b58:	e7b20054 */ 	swc1	$f18,0x54($sp)
/*  f0c4b5c:	8c7900bc */ 	lw	$t9,0xbc($v1)
/*  f0c4b60:	c60a0000 */ 	lwc1	$f10,0x0($s0)
/*  f0c4b64:	46129202 */ 	mul.s	$f8,$f18,$f18
/*  f0c4b68:	c7240008 */ 	lwc1	$f4,0x8($t9)
/*  f0c4b6c:	46045181 */ 	sub.s	$f6,$f10,$f4
/*  f0c4b70:	e7a6005c */ 	swc1	$f6,0x5c($sp)
/*  f0c4b74:	c7b0005c */ 	lwc1	$f16,0x5c($sp)
/*  f0c4b78:	46108282 */ 	mul.s	$f10,$f16,$f16
/*  f0c4b7c:	0c012974 */ 	jal	sqrtf
/*  f0c4b80:	46085300 */ 	add.s	$f12,$f10,$f8
/*  f0c4b84:	3c013f80 */ 	lui	$at,0x3f80
/*  f0c4b88:	44812000 */ 	mtc1	$at,$f4
/*  f0c4b8c:	c7a60054 */ 	lwc1	$f6,0x54($sp)
/*  f0c4b90:	c7b0005c */ 	lwc1	$f16,0x5c($sp)
/*  f0c4b94:	46002083 */ 	div.s	$f2,$f4,$f0
/*  f0c4b98:	44807000 */ 	mtc1	$zero,$f14
/*  f0c4b9c:	8fa8006c */ 	lw	$t0,0x6c($sp)
/*  f0c4ba0:	27a40048 */ 	addiu	$a0,$sp,0x48
/*  f0c4ba4:	44057000 */ 	mfc1	$a1,$f14
/*  f0c4ba8:	44077000 */ 	mfc1	$a3,$f14
/*  f0c4bac:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f0c4bb0:	46023482 */ 	mul.s	$f18,$f6,$f2
/*  f0c4bb4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4bb8:	46028282 */ 	mul.s	$f10,$f16,$f2
/*  f0c4bbc:	e7b20054 */ 	swc1	$f18,0x54($sp)
/*  f0c4bc0:	e7aa005c */ 	swc1	$f10,0x5c($sp)
/*  f0c4bc4:	c6280008 */ 	lwc1	$f8,0x8($s1)
/*  f0c4bc8:	c6260000 */ 	lwc1	$f6,0x0($s1)
/*  f0c4bcc:	e7ae004c */ 	swc1	$f14,0x4c($sp)
/*  f0c4bd0:	46085102 */ 	mul.s	$f4,$f10,$f8
/*  f0c4bd4:	afa80010 */ 	sw	$t0,0x10($sp)
/*  f0c4bd8:	46123402 */ 	mul.s	$f16,$f6,$f18
/*  f0c4bdc:	46102300 */ 	add.s	$f12,$f4,$f16
/*  f0c4be0:	460c9202 */ 	mul.s	$f8,$f18,$f12
/*  f0c4be4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4be8:	460c5182 */ 	mul.s	$f6,$f10,$f12
/*  f0c4bec:	e7a80054 */ 	swc1	$f8,0x54($sp)
/*  f0c4bf0:	e7a80048 */ 	swc1	$f8,0x48($sp)
/*  f0c4bf4:	e7a6005c */ 	swc1	$f6,0x5c($sp)
/*  f0c4bf8:	0fc31094 */ 	jal	func0f0c4250
/*  f0c4bfc:	e7a60050 */ 	swc1	$f6,0x50($sp)
/*  f0c4c00:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0c4c04:	5441005e */ 	bnel	$v0,$at,.L0f0c4d80
/*  f0c4c08:	00001025 */ 	or	$v0,$zero,$zero
/*  f0c4c0c:	1000005c */ 	beqz	$zero,.L0f0c4d80
/*  f0c4c10:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f0c4c14:
/*  f0c4c14:	8c6900bc */ 	lw	$t1,0xbc($v1)
/*  f0c4c18:	c6240000 */ 	lwc1	$f4,0x0($s1)
/*  f0c4c1c:	c64a0000 */ 	lwc1	$f10,0x0($s2)
/*  f0c4c20:	c5300008 */ 	lwc1	$f16,0x8($t1)
/*  f0c4c24:	46102480 */ 	add.s	$f18,$f4,$f16
/*  f0c4c28:	46125201 */ 	sub.s	$f8,$f10,$f18
/*  f0c4c2c:	e7a80054 */ 	swc1	$f8,0x54($sp)
/*  f0c4c30:	8c6a00bc */ 	lw	$t2,0xbc($v1)
/*  f0c4c34:	c6260008 */ 	lwc1	$f6,0x8($s1)
/*  f0c4c38:	c64a0008 */ 	lwc1	$f10,0x8($s2)
/*  f0c4c3c:	c5440010 */ 	lwc1	$f4,0x10($t2)
/*  f0c4c40:	46043400 */ 	add.s	$f16,$f6,$f4
/*  f0c4c44:	c7a40054 */ 	lwc1	$f4,0x54($sp)
/*  f0c4c48:	46105481 */ 	sub.s	$f18,$f10,$f16
/*  f0c4c4c:	e7b2005c */ 	swc1	$f18,0x5c($sp)
/*  f0c4c50:	c7a8005c */ 	lwc1	$f8,0x5c($sp)
/*  f0c4c54:	46084182 */ 	mul.s	$f6,$f8,$f8
/*  f0c4c58:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4c5c:	46042282 */ 	mul.s	$f10,$f4,$f4
/*  f0c4c60:	460a3400 */ 	add.s	$f16,$f6,$f10
/*  f0c4c64:	4600803e */ 	c.le.s	$f16,$f0
/*  f0c4c68:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4c6c:	45000043 */ 	bc1f	.L0f0c4d7c
/*  f0c4c70:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4c74:	8c6200bc */ 	lw	$v0,0xbc($v1)
/*  f0c4c78:	c6520000 */ 	lwc1	$f18,0x0($s2)
/*  f0c4c7c:	c4480008 */ 	lwc1	$f8,0x8($v0)
/*  f0c4c80:	46089032 */ 	c.eq.s	$f18,$f8
/*  f0c4c84:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4c88:	45020008 */ 	bc1fl	.L0f0c4cac
/*  f0c4c8c:	c64a0008 */ 	lwc1	$f10,0x8($s2)
/*  f0c4c90:	c6440008 */ 	lwc1	$f4,0x8($s2)
/*  f0c4c94:	c4460010 */ 	lwc1	$f6,0x10($v0)
/*  f0c4c98:	46062032 */ 	c.eq.s	$f4,$f6
/*  f0c4c9c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4ca0:	45030037 */ 	bc1tl	.L0f0c4d80
/*  f0c4ca4:	00001025 */ 	or	$v0,$zero,$zero
/*  f0c4ca8:	c64a0008 */ 	lwc1	$f10,0x8($s2)
.L0f0c4cac:
/*  f0c4cac:	c4500010 */ 	lwc1	$f16,0x10($v0)
/*  f0c4cb0:	44807000 */ 	mtc1	$zero,$f14
/*  f0c4cb4:	46105481 */ 	sub.s	$f18,$f10,$f16
/*  f0c4cb8:	e7ae0058 */ 	swc1	$f14,0x58($sp)
/*  f0c4cbc:	46009207 */ 	neg.s	$f8,$f18
/*  f0c4cc0:	e7a80054 */ 	swc1	$f8,0x54($sp)
/*  f0c4cc4:	8c6b00bc */ 	lw	$t3,0xbc($v1)
/*  f0c4cc8:	c6440000 */ 	lwc1	$f4,0x0($s2)
/*  f0c4ccc:	46084402 */ 	mul.s	$f16,$f8,$f8
/*  f0c4cd0:	c5660008 */ 	lwc1	$f6,0x8($t3)
/*  f0c4cd4:	46062281 */ 	sub.s	$f10,$f4,$f6
/*  f0c4cd8:	e7aa005c */ 	swc1	$f10,0x5c($sp)
/*  f0c4cdc:	c7b2005c */ 	lwc1	$f18,0x5c($sp)
/*  f0c4ce0:	46129102 */ 	mul.s	$f4,$f18,$f18
/*  f0c4ce4:	0c012974 */ 	jal	sqrtf
/*  f0c4ce8:	46102300 */ 	add.s	$f12,$f4,$f16
/*  f0c4cec:	3c013f80 */ 	lui	$at,0x3f80
/*  f0c4cf0:	44813000 */ 	mtc1	$at,$f6
/*  f0c4cf4:	c7aa0054 */ 	lwc1	$f10,0x54($sp)
/*  f0c4cf8:	c7b2005c */ 	lwc1	$f18,0x5c($sp)
/*  f0c4cfc:	46003083 */ 	div.s	$f2,$f6,$f0
/*  f0c4d00:	44807000 */ 	mtc1	$zero,$f14
/*  f0c4d04:	8fac006c */ 	lw	$t4,0x6c($sp)
/*  f0c4d08:	27a40048 */ 	addiu	$a0,$sp,0x48
/*  f0c4d0c:	44057000 */ 	mfc1	$a1,$f14
/*  f0c4d10:	44077000 */ 	mfc1	$a3,$f14
/*  f0c4d14:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f0c4d18:	46025202 */ 	mul.s	$f8,$f10,$f2
/*  f0c4d1c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4d20:	46029102 */ 	mul.s	$f4,$f18,$f2
/*  f0c4d24:	e7a80054 */ 	swc1	$f8,0x54($sp)
/*  f0c4d28:	e7a4005c */ 	swc1	$f4,0x5c($sp)
/*  f0c4d2c:	c6300008 */ 	lwc1	$f16,0x8($s1)
/*  f0c4d30:	c62a0000 */ 	lwc1	$f10,0x0($s1)
/*  f0c4d34:	e7ae004c */ 	swc1	$f14,0x4c($sp)
/*  f0c4d38:	46102182 */ 	mul.s	$f6,$f4,$f16
/*  f0c4d3c:	afac0010 */ 	sw	$t4,0x10($sp)
/*  f0c4d40:	46085482 */ 	mul.s	$f18,$f10,$f8
/*  f0c4d44:	46123300 */ 	add.s	$f12,$f6,$f18
/*  f0c4d48:	460c4402 */ 	mul.s	$f16,$f8,$f12
/*  f0c4d4c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c4d50:	460c2282 */ 	mul.s	$f10,$f4,$f12
/*  f0c4d54:	e7b00054 */ 	swc1	$f16,0x54($sp)
/*  f0c4d58:	e7b00048 */ 	swc1	$f16,0x48($sp)
/*  f0c4d5c:	e7aa005c */ 	swc1	$f10,0x5c($sp)
/*  f0c4d60:	0fc31094 */ 	jal	func0f0c4250
/*  f0c4d64:	e7aa0050 */ 	swc1	$f10,0x50($sp)
/*  f0c4d68:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0c4d6c:	54410004 */ 	bnel	$v0,$at,.L0f0c4d80
/*  f0c4d70:	00001025 */ 	or	$v0,$zero,$zero
/*  f0c4d74:	10000002 */ 	beqz	$zero,.L0f0c4d80
/*  f0c4d78:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f0c4d7c:
/*  f0c4d7c:	00001025 */ 	or	$v0,$zero,$zero
.L0f0c4d80:
/*  f0c4d80:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f0c4d84:	8fb00020 */ 	lw	$s0,0x20($sp)
/*  f0c4d88:	8fb10024 */ 	lw	$s1,0x24($sp)
/*  f0c4d8c:	8fb20028 */ 	lw	$s2,0x28($sp)
/*  f0c4d90:	03e00008 */ 	jr	$ra
/*  f0c4d94:	27bd0060 */ 	addiu	$sp,$sp,0x60
);

void func0f0c4d98(void)
{
	// empty
}

void currentPlayerUpdateSpeedSidewaysWalk(f32 targetspeed, f32 accelspeed, s32 mult)
{
	if (g_Vars.normmplayerisrunning) {
		targetspeed = (g_MpPlayers[g_Vars.currentplayerstats->mpindex].base.unk1c + 25.0f) / 100 * targetspeed;
	}

	if (g_Vars.currentplayer->speedstrafe > targetspeed) {
		g_Vars.currentplayer->speedstrafe -= accelspeed * mult;

		if (g_Vars.currentplayer->speedstrafe < targetspeed) {
			g_Vars.currentplayer->speedstrafe = targetspeed;
		}
	} else if (g_Vars.currentplayer->speedstrafe < targetspeed) {
		g_Vars.currentplayer->speedstrafe += accelspeed * mult;

		if (g_Vars.currentplayer->speedstrafe > targetspeed) {
			g_Vars.currentplayer->speedstrafe = targetspeed;
		}
	}

	g_Vars.currentplayer->speedsideways = g_Vars.currentplayer->speedstrafe;
}

void currentPlayerUpdateSpeedForwardsWalk(f32 targetspeed, f32 accelspeed)
{
	if (g_Vars.normmplayerisrunning) {
		targetspeed = (g_MpPlayers[g_Vars.currentplayerstats->mpindex].base.unk1c + 25.0f) / 100 * targetspeed;
	}

	if (g_Vars.currentplayer->speedgo < targetspeed) {
		g_Vars.currentplayer->speedgo += accelspeed * g_Vars.lvupdate240freal;

		if (g_Vars.currentplayer->speedgo > targetspeed) {
			g_Vars.currentplayer->speedgo = targetspeed;
		}
	} else if (g_Vars.currentplayer->speedgo > targetspeed) {
		g_Vars.currentplayer->speedgo -= accelspeed * g_Vars.lvupdate240freal;

		if (g_Vars.currentplayer->speedgo < targetspeed) {
			g_Vars.currentplayer->speedgo = targetspeed;
		}
	}

	g_Vars.currentplayer->speedforwards = g_Vars.currentplayer->speedgo;
}

void currentPlayerUpdateVerticalMovement(void)
{
	s32 i;
	struct defaultobj *obj;
	f32 width;
	f32 ymax;
	f32 ymin;
	f32 ground;
	bool onladder;
	bool onladder2 = false;
	s16 rooms[8];
	struct coord testpos;
	struct coord newpos;
	s16 newrooms[8];
	s32 newinlift;
	struct prop *lift = NULL;
	f32 sumground;
	f32 moveamount;
	f32 clearance;
	f32 limit;
	f32 amount;
	f32 newmanground;
	f32 fallspeed;
	f32 multiplier;
	f32 newfallspeed;
	struct prop *prop;

	propPlayerGetBbox(g_Vars.currentplayer->prop, &width, &ymax, &ymin);

	// Maybe reset counter-op's width - not sure why
	// Maybe it gets set to 0 when they die?
	if (g_Vars.antiplayernum >= 0
			&& g_Vars.currentplayer == g_Vars.anti
			&& g_Vars.currentplayer->bond2.width != 30
			&& func0002a684(&g_Vars.currentplayer->prop->pos, 30, g_Vars.currentplayer->prop->rooms, 0x3f, 1, ymax - g_Vars.currentplayer->prop->pos.y, ymin - g_Vars.currentplayer->prop->pos.y)) {
		g_Vars.currentplayer->prop->chr->chrwidth = 30;
		g_Vars.currentplayer->bond2.width = 30;
		width = 30;
	}

	// Determine if player is on a ladder
	// If this comes up false, a second check is done... maybe checking if the
	// player is touching a ladder from a room which shares the same coordinate
	// space?
	onladder = func00029ffc(&g_Vars.currentplayer->prop->pos,
			width * 1.2f, ymax - g_Vars.currentplayer->prop->pos.y,
			g_Vars.currentplayer->vv_manground - g_Vars.currentplayer->prop->pos.y + 1,
			g_Vars.currentplayer->prop->rooms, 0x8040, &g_Vars.currentplayer->laddernormal);

	if (!onladder) {
		testpos.x = g_Vars.currentplayer->prop->pos.x;
		testpos.y = g_Vars.currentplayer->prop->pos.y - 10;
		testpos.z = g_Vars.currentplayer->prop->pos.z;
		roomsCopy(g_Vars.currentplayer->prop->rooms, rooms);
		func0f0cb79c(g_Vars.currentplayer, &testpos, rooms);
		onladder2 = func00029ffc(&g_Vars.currentplayer->prop->pos,
				width * 1.1f, ymax - g_Vars.currentplayer->prop->pos.y,
				g_Vars.currentplayer->vv_manground - g_Vars.currentplayer->prop->pos.y - 10,
				rooms, 0x8040, &g_Vars.currentplayer->laddernormal);
	}

	testpos.x = g_Vars.currentplayer->prop->pos.x;
	testpos.y = g_Vars.currentplayer->prop->pos.y;
	testpos.z = g_Vars.currentplayer->prop->pos.z;

	if (g_Vars.currentplayer->inlift) {
		testpos.y -= g_Vars.currentplayer->crouchheight + g_Vars.currentplayer->crouchoffsetrealsmall;
	}

	roomsCopy(g_Vars.currentplayer->prop->rooms, rooms);
	func0f0cb79c(g_Vars.currentplayer, &testpos, rooms);
	ground = coordFindGroundY(&testpos, g_Vars.currentplayer->bond2.width, rooms,
			&g_Vars.currentplayer->floorcol, &g_Vars.currentplayer->floortype,
			&g_Vars.currentplayer->floorflags, &g_Vars.currentplayer->floorroom,
			&newinlift, &lift);
	ground += g_Vars.currentplayer->bondonground;

	if (ground < -30000) {
		ground = -30000;
	}

	if (g_Vars.currentplayer->inlift && newinlift == false) {
		// Exiting a lift
		func0f082d74();
	}

	if (g_Vars.currentplayer->inlift && newinlift && g_Vars.currentplayer->onladder == false) {
		// Remaining in a lift
		moveamount = ground - g_Vars.currentplayer->vv_ground;

		if (moveamount != 0) {
			// The lift is moving
			if (g_Vars.currentplayer->isfalling == false && lift == g_Vars.currentplayer->lift) {
				clearance = g_Vars.currentplayer->liftground - g_Vars.currentplayer->vv_manground;

				if (clearance < 1.0f && clearance > -1.0f) {
					// It's actually moving, and not a floating point precision issue
					g_Vars.currentplayer->vv_ground += moveamount;

					if (moveamount > 0
							|| lift == NULL
							|| lift->obj == NULL
							|| (lift->obj->flags & OBJFLAG_INTERCEPTOR_DISABLED) == 0
							|| currentPlayerHasGapToCeiling(moveamount) == true) {
						// Going up
						g_Vars.currentplayer->vv_manground += moveamount;
						g_Vars.currentplayer->sumground = g_Vars.currentplayer->vv_manground / 0.045499980449677f;
					}
				}
			}

			if (g_Vars.currentplayer->walkinitmove) {
				g_Vars.currentplayer->walkinitstart.y += moveamount;
			}
		}
	} else {
		lift = NULL;
	}

	g_Vars.currentplayer->inlift = newinlift;

	if (newinlift) {
		g_Vars.currentplayer->liftground = ground;
	}

	g_Vars.currentplayer->lift = lift;

	// Ladders
	if (g_Vars.currentplayer->onladder) {
		if (g_Vars.currentplayer->ladderupdown >= 0 ||
				(ground <= g_Vars.currentplayer->vv_manground &&
				 ground <= g_Vars.currentplayer->vv_manground + g_Vars.currentplayer->ladderupdown)) {
			// Still on ladder
			if (currentPlayerHasGapToCeiling(g_Vars.currentplayer->ladderupdown) == true) {
				g_Vars.currentplayer->vv_manground += g_Vars.currentplayer->ladderupdown;
			}
		} else {
			if (currentPlayerHasGapToCeiling(ground - g_Vars.currentplayer->vv_manground) == true) {
				g_Vars.currentplayer->vv_manground = ground;
				onladder = false;
			}
		}
	}

	g_Vars.currentplayer->onladder = onladder;

	if (g_Vars.currentplayer->onladder) {
		g_Vars.currentplayer->vv_ground = g_Vars.currentplayer->vv_manground;
	} else if (onladder2 == false) {
		g_Vars.currentplayer->vv_ground = ground;
	}

	// Standing on flat ground, or going up stairs, ledges or ramps
	// In other words, not falling
	if (g_Vars.currentplayer->bdeltapos.y >= 0.0f
			|| g_Vars.currentplayer->vv_ground > g_Vars.currentplayer->vv_manground) {
		g_Vars.currentplayer->sumground = g_Vars.currentplayer->vv_manground / 0.045499980449677f;

		for (i = 0; i < g_Vars.lvupdate240; i++) {
			g_Vars.currentplayer->sumground =
				g_Vars.currentplayer->sumground * 0.9545f + g_Vars.currentplayer->vv_ground;
		}

		if (g_Vars.currentplayer->vv_manground < g_Vars.currentplayer->vv_ground) {
			// Feet are lower than the ground
			sumground = g_Vars.currentplayer->sumground * 0.045499980449677f;
			limit = g_Vars.currentplayer->vv_ground - 50;

			if (sumground < limit) {
				sumground = limit;
			}

			if (currentPlayerHasGapToCeiling(sumground - g_Vars.currentplayer->vv_manground) == true) {
				g_Vars.currentplayer->vv_manground = sumground;
			} else {
				// Not enough room above. If on a hoverbike, blow it up
				prop = func00024eb0();

				if (prop
						&& g_Vars.currentplayer->prop->pos.y < prop->pos.y
						&& prop->type == PROPTYPE_OBJ) {
					obj = prop->obj;

					if (obj->obj == MODEL_HOVBIKE) {
						amount = (obj->maxdamage - obj->damage + 1) / 250.0f;
						obj->flags &= ~OBJFLAG_INVINCIBLE;
						func0f0852ac(obj, amount, &obj->prop->pos, 0x22, -1);
					}
				}
			}
		}

		// Kill player if standing on tile with FLOORFLAG_DIE
		if ((g_Vars.currentplayer->floorflags & FLOORFLAG_DIE)
				&& g_Vars.currentplayer->vv_manground - 20.0f < g_Vars.currentplayer->vv_ground
				&& g_Vars.currentplayer->onladder == false
				&& onladder2 == false) {
			currentPlayerDie(true);
		}
	}

	if (g_Vars.currentplayer->vv_manground > g_Vars.currentplayer->vv_ground) {
		// Not standing on ground - probably falling, or on an object of some sort
		fallspeed = g_Vars.currentplayer->bdeltapos.y;
		newmanground = g_Vars.currentplayer->vv_manground;

		if (debugIsTurboModeEnabled()
				&& g_Vars.currentplayer->bondforcespeed.x == 0
				&& g_Vars.currentplayer->bondforcespeed.z == 0) {
			multiplier = 0.277777777f * 5;
		} else {
			multiplier = 0.277777777f;
		}

		newfallspeed = fallspeed - g_Vars.lvupdate240freal * multiplier;
		newmanground += g_Vars.lvupdate240freal * (fallspeed + newfallspeed) * 0.5f;
		fallspeed = newfallspeed;

		if (newmanground < g_Vars.currentplayer->vv_ground) {
			newfallspeed = g_Vars.currentplayer->vv_manground - g_Vars.currentplayer->vv_ground;
			newmanground = g_Vars.currentplayer->vv_ground;

			fallspeed = sqrtf(g_Vars.currentplayer->bdeltapos.y *
					g_Vars.currentplayer->bdeltapos.y +
					(((newfallspeed + newfallspeed) * 0.277777777f) / 60.0f) * 60.0f);
			fallspeed = -fallspeed;
		}

		if (currentPlayerHasGapToCeiling(newmanground - g_Vars.currentplayer->vv_manground) == true) {
			// Falling
			g_Vars.currentplayer->vv_manground = newmanground;
			g_Vars.currentplayer->bdeltapos.y = fallspeed;

			if (g_Vars.currentplayer->isfalling == false) {
				// Just started falling
				g_Vars.currentplayer->isfalling = true;
				g_Vars.currentplayer->fallstart = g_Vars.lvframe60;
			} else {
				if (g_Vars.lvframe60 - g_Vars.currentplayer->fallstart > 240) {
					// Have been falling for 4 seconds
					currentPlayerDie(true);
				}
			}
		} else {
			// Not falling
			if (g_Vars.normmplayerisrunning == false
					&& g_Vars.currentplayer->vv_ground < g_Vars.currentplayer->vv_manground - 30) {
				// Not falling - but still at least 30 units off the ground.
				// Must be something in the way...
				prop = func00024eb0();

				if (prop) {
					if (prop->type == PROPTYPE_CHR) {
						// Landed on top of a chr
						if (prop->chr->inlift) {
							func0f03323c(prop->chr, &g_Vars.currentplayer->prop->pos, 0);
						}
					} else if (prop->type == PROPTYPE_PLAYER) {
						// Landed on top of a player
						u32 prevplayernum = g_Vars.currentplayernum;
						setCurrentPlayerNum(propGetPlayerNum(prop));

						if (g_Vars.currentplayer->inlift) {
							currentPlayerDieByShooter(prevplayernum, true);
						}

						setCurrentPlayerNum(prevplayernum);
					}
				}
			}

			g_Vars.currentplayer->bdeltapos.y = 0.0f;

			if (g_Vars.currentplayer->isfalling) {
				g_Vars.currentplayer->isfalling = false;
			}

			if (g_Vars.currentplayer->vv_manground <= -30000) {
				currentPlayerDie(true);
			}
		}
	} else {
		// Not falling
		if (g_Vars.currentplayer->isfalling) {
			g_Vars.currentplayer->isfalling = false;
		}

		if (g_Vars.currentplayer->vv_manground <= -30000) {
			currentPlayerDie(true);
		}
	}

	if (g_Vars.currentplayer->bdeltapos.y < 0 &&
			g_Vars.currentplayer->vv_manground <= g_Vars.currentplayer->vv_ground) {
		// Landing after a fall
		if (g_Vars.currentplayer->isfalling) {
			g_Vars.currentplayer->isfalling = false;
		}

		// I suspect these crouch fields are related to the recovery during
		// landing. Eg. The faster the fall speed, the longer Jo will take to
		// stand back to full height again.
		if (g_Vars.currentplayer->bdeltapos.y < -13.333333f) {
			g_Vars.currentplayer->crouchtime240 = 60;
			g_Vars.currentplayer->crouchfall = -90;
		} else if (g_Vars.currentplayer->bdeltapos.y < -5.0f) {
			g_Vars.currentplayer->crouchtime240 = 60;
			g_Vars.currentplayer->crouchfall =
				(-5.0f - g_Vars.currentplayer->bdeltapos.y) * -90.0f / 8.333333f;
		}

		if (g_Vars.currentplayer->bdeltapos.y < -6.0f) {
			// Play footstep sounds
			s32 sound;
			struct chrdata *chr = g_Vars.currentplayer->prop->chr;
			chr->floortype = g_Vars.currentplayer->floortype;
			chr->footstep = 1;

			sound = chrChooseFootstepSound(chr, true);

			if (sound != -1) {
				if (sound != -1) {
					func0f0939f8(NULL, g_Vars.currentplayer->prop, sound,
							-1, -1, 0x8400, 0, 0, 0, -1, 0, -1, -1, -1, -1);
				}

				chr->footstep = 2;
				sound = chrChooseFootstepSound(chr, true);

				if (sound != -1) {
					func0f0939f8(NULL, g_Vars.currentplayer->prop, sound,
							-1, -1, 0x8400, 0, 0, 0, -1, 0, -1, -1, -1, -1);
				}
			}

			if (g_Vars.mplayerisrunning == false
					&& (chr->headnum == HEAD_DARK_COMBAT || chr->headnum == HEAD_DARK_FROCK)
					&& g_Vars.lvframe60 - g_Vars.currentplayer->fallstart > 40) {
				// Play Jo landing grunt
				s32 sounds[] = { 0x046f, 0x05b6, 0x05b7 };

				func0f0939f8(NULL, g_Vars.currentplayer->prop, sounds[random() % 3],
						-1, -1, 0x8400, 0, 0, 0, -1, 0, -1, -1, -1, -1);
			}
		}

		g_Vars.currentplayer->bdeltapos.y = 0;
	}

	// Decrease crouchtime240 for this tick.
	// If reached 0 and crouchfall is negative, start increasing
	// crouchfall over the next several ticks until it reaches 0.
	for (i = 0; i < g_Vars.lvupdate240; i++) {
		if (g_Vars.currentplayer->crouchtime240 > 0) {
			g_Vars.currentplayer->sumcrouch =
				g_Vars.currentplayer->sumcrouch * 0.9456f + g_Vars.currentplayer->crouchfall;
			g_Vars.currentplayer->crouchtime240--;
		} else {
			if (g_Vars.currentplayer->crouchfall < 0) {
				g_Vars.currentplayer->crouchfall -= -1.125f;

				if (g_Vars.currentplayer->crouchfall >= 0) {
					g_Vars.currentplayer->crouchfall = 0;
				}
			}

			g_Vars.currentplayer->sumcrouch =
				g_Vars.currentplayer->sumcrouch * 0.9456f + g_Vars.currentplayer->crouchfall;
		}
	}

	{
		f32 eyeheight;
		g_Vars.currentplayer->crouchheight = g_Vars.currentplayer->sumcrouch * 0.054400026798248f;
		g_Vars.currentplayer->vv_height =
			(g_Vars.currentplayer->headpos.y / g_Vars.currentplayer->standheight)
			* g_Vars.currentplayer->vv_eyeheight;

		eyeheight = g_Vars.currentplayer->vv_height +
			g_Vars.currentplayer->crouchoffsetrealsmall +
			g_Vars.currentplayer->crouchheight *
			g_Vars.currentplayer->vv_eyeheight * 0.0062893079593778f;

		if (eyeheight < 30) {
			eyeheight = 30;
		}

		newpos.x = g_Vars.currentplayer->prop->pos.x;
		newpos.y = g_Vars.currentplayer->vv_manground + eyeheight;
		newpos.z = g_Vars.currentplayer->prop->pos.z;
	}

	if (newpos.y < g_Vars.currentplayer->vv_ground + 10) {
		newpos.y = g_Vars.currentplayer->vv_ground + 10;
	}

	if (newpos.x != g_Vars.currentplayer->prop->pos.x
			|| newpos.y != g_Vars.currentplayer->prop->pos.y
			|| newpos.z != g_Vars.currentplayer->prop->pos.z) {
		func0f065e74(&g_Vars.currentplayer->prop->pos, g_Vars.currentplayer->prop->rooms, &newpos, newrooms);

		g_Vars.currentplayer->prop->pos.x = newpos.x;
		g_Vars.currentplayer->prop->pos.y = newpos.y;
		g_Vars.currentplayer->prop->pos.z = newpos.z;

		func0f065c44(g_Vars.currentplayer->prop);
		roomsCopy(newrooms, g_Vars.currentplayer->prop->rooms);
	}
}

void currentPlayerApplyCrouchSpeed(void)
{
	if (currentPlayerGetCrouchPos() == CROUCH_HALF) {
		g_Vars.currentplayer->speedforwards *= 0.5f;
		g_Vars.currentplayer->speedsideways *= 0.5f;
	} else if (currentPlayerGetCrouchPos() == CROUCH_SQUAT) {
		g_Vars.currentplayer->speedforwards *= 0.35f;
		g_Vars.currentplayer->speedsideways *= 0.35f;
	}
}

void currentPlayerUpdateCrouchOffsetWalk(void)
{
	if (g_Vars.currentplayer->vv_eyeheight + -90.0f * g_Vars.currentplayer->vv_eyeheight * (1.0f / 159.0f) < 69.0f) {
		g_Vars.currentplayer->crouchoffsetreal = g_Vars.currentplayer->crouchoffset * ((69.0f - g_Vars.currentplayer->vv_eyeheight) / -90.0f);
	} else {
		g_Vars.currentplayer->crouchoffsetreal = g_Vars.currentplayer->crouchoffset * g_Vars.currentplayer->vv_eyeheight * (1.0f / 159.0f);
	}

	if (cheatIsActive(CHEAT_SMALLJO)) {
		g_Vars.currentplayer->crouchoffsetsmall = 69.0f - g_Vars.currentplayer->vv_eyeheight;
		g_Vars.currentplayer->crouchoffsetrealsmall = 69.0f - g_Vars.currentplayer->vv_eyeheight;
	} else {
		g_Vars.currentplayer->crouchoffsetsmall = g_Vars.currentplayer->crouchoffset;
		g_Vars.currentplayer->crouchoffsetrealsmall = g_Vars.currentplayer->crouchoffsetreal;
	}
}

void func0f0c6180(void)
{
	f32 targetoffset = 0;

	if (currentPlayerGetCrouchPos() == CROUCH_SQUAT) {
		targetoffset = -90;
	} else if (currentPlayerGetCrouchPos() == CROUCH_HALF) {
		targetoffset = -45;
	} else if (currentPlayerGetCrouchPos() == CROUCH_STAND) {
		// empty
	}

	if (targetoffset != g_Vars.currentplayer->crouchoffset) {
		f32 prevcrouchoffset = g_Vars.currentplayer->crouchoffset;
		f32 prevcrouchoffsetreal = g_Vars.currentplayer->crouchoffsetreal;
		f32 prevcrouchoffsetsmall = g_Vars.currentplayer->crouchoffsetsmall;
		f32 prevcrouchoffsetrealsmall = g_Vars.currentplayer->crouchoffsetrealsmall;

		// f32 *frac, f32 maxfrac, f32 *fracspeed, f32 accel, f32 decel, f32 maxspeed
		func0f06d90c(&g_Vars.currentplayer->crouchoffset, targetoffset,
				&g_Vars.currentplayer->crouchspeed, 0.5, 0.5, 5);

		currentPlayerUpdateCrouchOffsetWalk();

		if (!currentPlayerHasGapToCeiling(0)) {
			// Crouch adjustment is blocked by ceiling
			g_Vars.currentplayer->crouchoffset = prevcrouchoffset;
			g_Vars.currentplayer->crouchoffsetreal = prevcrouchoffsetreal;
			g_Vars.currentplayer->crouchoffsetsmall = prevcrouchoffsetsmall;
			g_Vars.currentplayer->crouchoffsetrealsmall = prevcrouchoffsetrealsmall;
			g_Vars.currentplayer->crouchspeed = 0;
			currentPlayerAdjustCrouchPos(-1);
		}
	}

	if (targetoffset == g_Vars.currentplayer->crouchoffset) {
		g_Vars.currentplayer->crouchspeed = 0;
	}

	g_Vars.currentplayer->guncloseroffset = g_Vars.currentplayer->crouchoffset / -90;
}

void func0f0c6318(void)
{
	f32 thing1;
	f32 thing2;
	struct coord delta = {0, 0, 0};

	thing1 = 159.0f / g_Vars.currentplayer->vv_eyeheight;
	thing2 = g_Vars.currentplayer->speedtheta * thing1
		* g_Vars.lvupdate240freal * 0.0174505133f * 3.5f;

	func0f0c4250(&delta, thing2, 1, 0, 63);
}

u32 var80070e68 = 0x00000000;
u32 var80070e6c = 0x00000000;
u32 var80070e70 = 0x00000000;
u32 var80070e74 = 0x00000000;
u32 var80070e78 = 0x00000000;
u32 var80070e7c = 0x00000000;

void func0f0c63bc(struct coord *arg0, u32 arg1, s32 arg2)
{
	struct coord sp100;
	struct coord sp88;

	g_Vars.currentplayer->unk1af4 = 0;
	g_Vars.currentplayer->autocrouchpos = CROUCH_STAND;

	func0f0c4d98();

	if (func0f0c4764(arg0, &sp100, &sp88, arg2) == 0) {
		struct coord sp76;
		struct coord sp64;

		s32 lVar1 = func0f0c47d0(arg0, &sp100, &sp88, &sp76, &sp64, arg2);

		if (lVar1 > 0 || lVar1 < 0) {
			if (lVar1 > 0) {
				func0f0c4d98();
			}

			if (arg1
					&& func0f0c494c(arg0, &sp100, &sp88, arg2) < 1
					&& func0f0c4a5c(arg0, &sp100, &sp88, arg2) <= 0) {
				// empty
			}
		} else if (lVar1 == 0) {
			struct coord sp48;
			struct coord sp36;

			if (func0f0c47d0(arg0, &sp76, &sp64, &sp48, &sp36, arg2) > 0) {
				func0f0c4d98();
			}

			if (arg1
					&& func0f0c494c(arg0, &sp76, &sp64, arg2) < 1
					&& func0f0c494c(arg0, &sp100, &sp88, arg2) < 1
					&& func0f0c4a5c(arg0, &sp76, &sp64, arg2) < 1) {
				func0f0c4a5c(arg0, &sp100, &sp88, arg2);
			}
		}
	}

	func0f0c4d98();
}

void currentPlayerUpdatePrevPosWalk(void)
{
	g_Vars.currentplayer->bondprevpos.x = g_Vars.currentplayer->prop->pos.x;
	g_Vars.currentplayer->bondprevpos.y = g_Vars.currentplayer->prop->pos.y;
	g_Vars.currentplayer->bondprevpos.z = g_Vars.currentplayer->prop->pos.z;

	roomsCopy(g_Vars.currentplayer->prop->rooms, g_Vars.currentplayer->bondprevrooms);
}

void func0f0c65a8(void)
{
	if (g_Vars.currentplayer->walkinitmove) {
		g_Vars.currentplayer->unk00d0 = 0;
	}
}

void currentPlayerUpdateSpeedWalk(struct movedata *data)
{
	if (g_Vars.currentplayer->walkinitmove == false) {
		// Sideways
		if (data->stepleft) {
			currentPlayerUpdateSpeedSidewaysWalk(-1, 0.2f, data->stepleft);
		} else if (data->stepright) {
			currentPlayerUpdateSpeedSidewaysWalk(1, 0.2f, data->stepright);
		} else if (data->unk14 == false) {
			currentPlayerUpdateSpeedSidewaysWalk(0, 0.2f, g_Vars.lvupdate240_60);
		}

		if (data->unk14) {
			currentPlayerUpdateSpeedSidewaysWalk(data->unka4 * 0.014285714365542f, 0.2f, g_Vars.lvupdate240_60);
		}

		// Forward/back
		if (data->stepforward) {
			currentPlayerUpdateSpeedForwardsWalk(1, 1);
			g_Vars.currentplayer->speedmaxtime60 += g_Vars.lvupdate240_60;
		} else if (data->stepback) {
			currentPlayerUpdateSpeedForwardsWalk(-1, 1);
		} else if (data->unk10 == false) {
			currentPlayerUpdateSpeedForwardsWalk(0, 1);
		}

		if (data->unk10) {
			currentPlayerUpdateSpeedForwardsWalk(data->unka8 * 0.014285714365542f, 1);

			if (data->unka8 > 60) {
				g_Vars.currentplayer->speedmaxtime60 += g_Vars.lvupdate240_60;
			} else {
				g_Vars.currentplayer->speedmaxtime60 = 0;
			}
		}

		// Force speeds to range -1 to 1
		if (g_Vars.currentplayer->speedforwards > 1) {
			g_Vars.currentplayer->speedforwards = 1;
		}

		if (g_Vars.currentplayer->speedforwards < -1) {
			g_Vars.currentplayer->speedforwards = -1;
		}

		if (g_Vars.currentplayer->speedsideways > 1) {
			g_Vars.currentplayer->speedsideways = 1;
		}

		if (g_Vars.currentplayer->speedsideways < -1) {
			g_Vars.currentplayer->speedsideways = -1;
		}

		g_Vars.currentplayer->speedforwards *= 1.08f;
		g_Vars.currentplayer->speedforwards *= g_Vars.currentplayer->speedboost;

		if ((data->unk10 == 0 && data->stepforward == 0) ||
				currentPlayerGetCrouchPos() != CROUCH_STAND) {
			g_Vars.currentplayer->speedmaxtime60 = 0;
		}

		if (data->swaynegative) {
			currentPlayerSetSwayTarget(-1);
		} else if (data->swaypositive) {
			currentPlayerSetSwayTarget(1);
		} else {
			currentPlayerSetSwayTarget(0);
		}

		while (data->crouchdown-- > 0) {
			currentPlayerAdjustCrouchPos(-1);
		}

		while (data->crouchup-- > 0) {
			currentPlayerAdjustCrouchPos(1);
		}

		g_Vars.currentplayer->eyesshut = data->eyesshut;
	}
}

void currentPlayerApplyCrouchSpeedTheta(void)
{
	if (currentPlayerGetCrouchPos() == CROUCH_SQUAT) {
		g_Vars.currentplayer->speedtheta *= 0.5f;
	} else if (currentPlayerGetCrouchPos() == CROUCH_HALF) {
		g_Vars.currentplayer->speedtheta *= 0.75f;
	}
}

GLOBAL_ASM(
glabel func0f0c69b8
.late_rodata
glabel var7f1ad7fc
.word 0xc27e6668
glabel var7f1ad800
.word 0x43b0aaaa
glabel var7f1ad804
.word 0x3ecccccd
glabel var7f1ad808
.word 0x3c888889
glabel var7f1ad80c
.word 0x404907a9
glabel var7f1ad810
.word 0x3eb33333
glabel var7f1ad814
.word 0x3eb33333
glabel var7f1ad818
.word 0x3dcccccd
glabel var7f1ad81c
.word 0x3dcccccd
glabel var7f1ad820
.word 0x3eb33333
glabel var7f1ad824
.word 0x3f4ccccd
glabel var7f1ad828
.word 0x3f4ccccd
glabel var7f1ad82c
.word 0x3f4ccccd
glabel var7f1ad830
.word 0x4528c000
glabel var7f1ad834
.word 0x3ecccccd
glabel var7f1ad838
.word 0x3ecccccd
glabel var7f1ad83c
.word 0x3e99999a
glabel var7f1ad840
.word 0x3f8ccccd
glabel var7f1ad844
.word 0x3e99999a
glabel var7f1ad848
.word 0x3e99999a
glabel var7f1ad84c
.word 0x3f333333
glabel var7f1ad850
.word 0x3f99999a
glabel var7f1ad854
.word 0x3c8ef461
.text
/*  f0c69b8:	27bdff18 */ 	addiu	$sp,$sp,-232
/*  f0c69bc:	3c0f8007 */ 	lui	$t7,%hi(var80070e68)
/*  f0c69c0:	afbf0024 */ 	sw	$ra,0x24($sp)
/*  f0c69c4:	f7b40018 */ 	sdc1	$f20,0x18($sp)
/*  f0c69c8:	25ef0e68 */ 	addiu	$t7,$t7,%lo(var80070e68)
/*  f0c69cc:	8de10000 */ 	lw	$at,0x0($t7)
/*  f0c69d0:	27ae00cc */ 	addiu	$t6,$sp,0xcc
/*  f0c69d4:	8de90004 */ 	lw	$t1,0x4($t7)
/*  f0c69d8:	adc10000 */ 	sw	$at,0x0($t6)
/*  f0c69dc:	8de10008 */ 	lw	$at,0x8($t7)
/*  f0c69e0:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c69e4:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c69e8:	adc90004 */ 	sw	$t1,0x4($t6)
/*  f0c69ec:	adc10008 */ 	sw	$at,0x8($t6)
/*  f0c69f0:	8d0a0284 */ 	lw	$t2,0x284($t0)
/*  f0c69f4:	3c01431f */ 	lui	$at,0x431f
/*  f0c69f8:	44813000 */ 	mtc1	$at,$f6
/*  f0c69fc:	c54419c4 */ 	lwc1	$f4,0x19c4($t2)
/*  f0c6a00:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f0c6a04:	0fc44a11 */ 	jal	currentPlayerHasBriefcase
/*  f0c6a08:	e7a800c0 */ 	swc1	$f8,0xc0($sp)
/*  f0c6a0c:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c6a10:	1040000a */ 	beqz	$v0,.L0f0c6a3c
/*  f0c6a14:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c6a18:	3c02800b */ 	lui	$v0,%hi(g_MpSetup+0x10)
/*  f0c6a1c:	9042cb98 */ 	lbu	$v0,%lo(g_MpSetup+0x10)($v0)
/*  f0c6a20:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0c6a24:	10410002 */ 	beq	$v0,$at,.L0f0c6a30
/*  f0c6a28:	24010005 */ 	addiu	$at,$zero,0x5
/*  f0c6a2c:	14410003 */ 	bne	$v0,$at,.L0f0c6a3c
.L0f0c6a30:
/*  f0c6a30:	3c017f1b */ 	lui	$at,%hi(var7f1ad7fc)
/*  f0c6a34:	c420d7fc */ 	lwc1	$f0,%lo(var7f1ad7fc)($at)
/*  f0c6a38:	e7a000c0 */ 	swc1	$f0,0xc0($sp)
.L0f0c6a3c:
/*  f0c6a3c:	3c017f1b */ 	lui	$at,%hi(var7f1ad800)
/*  f0c6a40:	c7a000c0 */ 	lwc1	$f0,0xc0($sp)
/*  f0c6a44:	c42ad800 */ 	lwc1	$f10,%lo(var7f1ad800)($at)
/*  f0c6a48:	8d0b0318 */ 	lw	$t3,0x318($t0)
/*  f0c6a4c:	3c013f80 */ 	lui	$at,0x3f80
/*  f0c6a50:	460a0103 */ 	div.s	$f4,$f0,$f10
/*  f0c6a54:	44813000 */ 	mtc1	$at,$f6
/*  f0c6a58:	3c0c800b */ 	lui	$t4,%hi(g_MpSetup+0xc)
/*  f0c6a5c:	2404000a */ 	addiu	$a0,$zero,0xa
/*  f0c6a60:	1160000a */ 	beqz	$t3,.L0f0c6a8c
/*  f0c6a64:	46062000 */ 	add.s	$f0,$f4,$f6
/*  f0c6a68:	8d8ccb94 */ 	lw	$t4,%lo(g_MpSetup+0xc)($t4)
/*  f0c6a6c:	3c013fa0 */ 	lui	$at,0x3fa0
/*  f0c6a70:	318d0100 */ 	andi	$t5,$t4,0x100
/*  f0c6a74:	11a00005 */ 	beqz	$t5,.L0f0c6a8c
/*  f0c6a78:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6a7c:	44814000 */ 	mtc1	$at,$f8
/*  f0c6a80:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6a84:	46080002 */ 	mul.s	$f0,$f0,$f8
/*  f0c6a88:	00000000 */ 	sll	$zero,$zero,0x0
.L0f0c6a8c:
/*  f0c6a8c:	0fc41b99 */ 	jal	cheatIsActive
/*  f0c6a90:	e7a000c0 */ 	swc1	$f0,0xc0($sp)
/*  f0c6a94:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c6a98:	10400006 */ 	beqz	$v0,.L0f0c6ab4
/*  f0c6a9c:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c6aa0:	3c017f1b */ 	lui	$at,%hi(var7f1ad804)
/*  f0c6aa4:	c424d804 */ 	lwc1	$f4,%lo(var7f1ad804)($at)
/*  f0c6aa8:	c7aa00c0 */ 	lwc1	$f10,0xc0($sp)
/*  f0c6aac:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f0c6ab0:	e7a600c0 */ 	swc1	$f6,0xc0($sp)
.L0f0c6ab4:
/*  f0c6ab4:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c6ab8:	8c791af8 */ 	lw	$t9,0x1af8($v1)
/*  f0c6abc:	1320003f */ 	beqz	$t9,.L0f0c6bbc
/*  f0c6ac0:	3c013f80 */ 	lui	$at,0x3f80
/*  f0c6ac4:	44811000 */ 	mtc1	$at,$f2
/*  f0c6ac8:	3c017f1b */ 	lui	$at,%hi(var7f1ad808)
/*  f0c6acc:	c42ad808 */ 	lwc1	$f10,%lo(var7f1ad808)($at)
/*  f0c6ad0:	c508004c */ 	lwc1	$f8,0x4c($t0)
/*  f0c6ad4:	c4661b48 */ 	lwc1	$f6,0x1b48($v1)
/*  f0c6ad8:	3c017f1b */ 	lui	$at,%hi(var7f1ad80c)
/*  f0c6adc:	460a4102 */ 	mul.s	$f4,$f8,$f10
/*  f0c6ae0:	46043200 */ 	add.s	$f8,$f6,$f4
/*  f0c6ae4:	e4681b48 */ 	swc1	$f8,0x1b48($v1)
/*  f0c6ae8:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c6aec:	c4601b48 */ 	lwc1	$f0,0x1b48($v1)
/*  f0c6af0:	4600103e */ 	c.le.s	$f2,$f0
/*  f0c6af4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6af8:	45000006 */ 	bc1f	.L0f0c6b14
/*  f0c6afc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6b00:	e4621b48 */ 	swc1	$f2,0x1b48($v1)
/*  f0c6b04:	8d180284 */ 	lw	$t8,0x284($t0)
/*  f0c6b08:	af001af8 */ 	sw	$zero,0x1af8($t8)
/*  f0c6b0c:	8d0e0284 */ 	lw	$t6,0x284($t0)
/*  f0c6b10:	c5c01b48 */ 	lwc1	$f0,0x1b48($t6)
.L0f0c6b14:
/*  f0c6b14:	c42ad80c */ 	lwc1	$f10,%lo(var7f1ad80c)($at)
/*  f0c6b18:	460a0302 */ 	mul.s	$f12,$f0,$f10
/*  f0c6b1c:	0c0068f4 */ 	jal	cosf
/*  f0c6b20:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6b24:	3c013f80 */ 	lui	$at,0x3f80
/*  f0c6b28:	44811000 */ 	mtc1	$at,$f2
/*  f0c6b2c:	3c013f00 */ 	lui	$at,0x3f00
/*  f0c6b30:	44812000 */ 	mtc1	$at,$f4
/*  f0c6b34:	46020180 */ 	add.s	$f6,$f0,$f2
/*  f0c6b38:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c6b3c:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c6b40:	8d0f0284 */ 	lw	$t7,0x284($t0)
/*  f0c6b44:	46043202 */ 	mul.s	$f8,$f6,$f4
/*  f0c6b48:	4480a000 */ 	mtc1	$zero,$f20
/*  f0c6b4c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6b50:	4406a000 */ 	mfc1	$a2,$f20
/*  f0c6b54:	4600a306 */ 	mov.s	$f12,$f20
/*  f0c6b58:	4600a386 */ 	mov.s	$f14,$f20
/*  f0c6b5c:	46081281 */ 	sub.s	$f10,$f2,$f8
/*  f0c6b60:	e5ea1b4c */ 	swc1	$f10,0x1b4c($t7)
/*  f0c6b64:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c6b68:	c4661b4c */ 	lwc1	$f6,0x1b4c($v1)
/*  f0c6b6c:	24671b08 */ 	addiu	$a3,$v1,0x1b08
/*  f0c6b70:	46061101 */ 	sub.s	$f4,$f2,$f6
/*  f0c6b74:	0fc330ee */ 	jal	func0f0cc3b8
/*  f0c6b78:	e7a40010 */ 	swc1	$f4,0x10($sp)
/*  f0c6b7c:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c6b80:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c6b84:	8d090284 */ 	lw	$t1,0x284($t0)
/*  f0c6b88:	27a400cc */ 	addiu	$a0,$sp,0xcc
/*  f0c6b8c:	0fc32ed2 */ 	jal	currentPlayerUpdateMoveInitSpeed
/*  f0c6b90:	e53400cc */ 	swc1	$f20,0xcc($t1)
/*  f0c6b94:	4405a000 */ 	mfc1	$a1,$f20
/*  f0c6b98:	4407a000 */ 	mfc1	$a3,$f20
/*  f0c6b9c:	240a003f */ 	addiu	$t2,$zero,0x3f
/*  f0c6ba0:	afaa0010 */ 	sw	$t2,0x10($sp)
/*  f0c6ba4:	27a400cc */ 	addiu	$a0,$sp,0xcc
/*  f0c6ba8:	0fc31094 */ 	jal	func0f0c4250
/*  f0c6bac:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f0c6bb0:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c6bb4:	100002ea */ 	beqz	$zero,.L0f0c7760
/*  f0c6bb8:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
.L0f0c6bbc:
/*  f0c6bbc:	0fc317fa */ 	jal	currentPlayerApplyCrouchSpeed
/*  f0c6bc0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6bc4:	0fc31860 */ 	jal	func0f0c6180
/*  f0c6bc8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6bcc:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c6bd0:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c6bd4:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c6bd8:	27a400c8 */ 	addiu	$a0,$sp,0xc8
/*  f0c6bdc:	27a500c4 */ 	addiu	$a1,$sp,0xc4
/*  f0c6be0:	c468014c */ 	lwc1	$f8,0x14c($v1)
/*  f0c6be4:	8c670150 */ 	lw	$a3,0x150($v1)
/*  f0c6be8:	2466017c */ 	addiu	$a2,$v1,0x17c
/*  f0c6bec:	0fc32ea2 */ 	jal	func0f0cba88
/*  f0c6bf0:	e7a80010 */ 	swc1	$f8,0x10($sp)
/*  f0c6bf4:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c6bf8:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c6bfc:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c6c00:	3c01c234 */ 	lui	$at,0xc234
/*  f0c6c04:	c7a800c0 */ 	lwc1	$f8,0xc0($sp)
/*  f0c6c08:	c46c00a0 */ 	lwc1	$f12,0xa0($v1)
/*  f0c6c0c:	c46a0374 */ 	lwc1	$f10,0x374($v1)
/*  f0c6c10:	c464036c */ 	lwc1	$f4,0x36c($v1)
/*  f0c6c14:	46006187 */ 	neg.s	$f6,$f12
/*  f0c6c18:	c47000b4 */ 	lwc1	$f16,0xb4($v1)
/*  f0c6c1c:	46065002 */ 	mul.s	$f0,$f10,$f6
/*  f0c6c20:	44815000 */ 	mtc1	$at,$f10
/*  f0c6c24:	4480a000 */ 	mtc1	$zero,$f20
/*  f0c6c28:	460c2382 */ 	mul.s	$f14,$f4,$f12
/*  f0c6c2c:	460a803c */ 	c.lt.s	$f16,$f10
/*  f0c6c30:	4600a086 */ 	mov.s	$f2,$f20
/*  f0c6c34:	46080002 */ 	mul.s	$f0,$f0,$f8
/*  f0c6c38:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6c3c:	46087382 */ 	mul.s	$f14,$f14,$f8
/*  f0c6c40:	4500000a */ 	bc1f	.L0f0c6c6c
/*  f0c6c44:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6c48:	3c017f1b */ 	lui	$at,%hi(var7f1ad810)
/*  f0c6c4c:	c426d810 */ 	lwc1	$f6,%lo(var7f1ad810)($at)
/*  f0c6c50:	3c017f1b */ 	lui	$at,%hi(var7f1ad814)
/*  f0c6c54:	c424d814 */ 	lwc1	$f4,%lo(var7f1ad814)($at)
/*  f0c6c58:	46060002 */ 	mul.s	$f0,$f0,$f6
/*  f0c6c5c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6c60:	46047382 */ 	mul.s	$f14,$f14,$f4
/*  f0c6c64:	1000000b */ 	beqz	$zero,.L0f0c6c94
/*  f0c6c68:	00000000 */ 	sll	$zero,$zero,0x0
.L0f0c6c6c:
/*  f0c6c6c:	4614803c */ 	c.lt.s	$f16,$f20
/*  f0c6c70:	3c013f00 */ 	lui	$at,0x3f00
/*  f0c6c74:	45020008 */ 	bc1fl	.L0f0c6c98
/*  f0c6c78:	c46600a4 */ 	lwc1	$f6,0xa4($v1)
/*  f0c6c7c:	44814000 */ 	mtc1	$at,$f8
/*  f0c6c80:	44815000 */ 	mtc1	$at,$f10
/*  f0c6c84:	46080002 */ 	mul.s	$f0,$f0,$f8
/*  f0c6c88:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6c8c:	460a7382 */ 	mul.s	$f14,$f14,$f10
/*  f0c6c90:	00000000 */ 	sll	$zero,$zero,0x0
.L0f0c6c94:
/*  f0c6c94:	c46600a4 */ 	lwc1	$f6,0xa4($v1)
.L0f0c6c98:
/*  f0c6c98:	c46400a8 */ 	lwc1	$f4,0xa8($v1)
/*  f0c6c9c:	e7a200a8 */ 	swc1	$f2,0xa8($sp)
/*  f0c6ca0:	46060401 */ 	sub.s	$f16,$f0,$f6
/*  f0c6ca4:	46047481 */ 	sub.s	$f18,$f14,$f4
/*  f0c6ca8:	46108202 */ 	mul.s	$f8,$f16,$f16
/*  f0c6cac:	e7b000b4 */ 	swc1	$f16,0xb4($sp)
/*  f0c6cb0:	46129282 */ 	mul.s	$f10,$f18,$f18
/*  f0c6cb4:	e7b200b0 */ 	swc1	$f18,0xb0($sp)
/*  f0c6cb8:	0c012974 */ 	jal	sqrtf
/*  f0c6cbc:	460a4300 */ 	add.s	$f12,$f8,$f10
/*  f0c6cc0:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c6cc4:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c6cc8:	3c014080 */ 	lui	$at,0x4080
/*  f0c6ccc:	44817000 */ 	mtc1	$at,$f14
/*  f0c6cd0:	c512004c */ 	lwc1	$f18,0x4c($t0)
/*  f0c6cd4:	c7a200a8 */ 	lwc1	$f2,0xa8($sp)
/*  f0c6cd8:	4612703c */ 	c.lt.s	$f14,$f18
/*  f0c6cdc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6ce0:	45020005 */ 	bc1fl	.L0f0c6cf8
/*  f0c6ce4:	46009306 */ 	mov.s	$f12,$f18
/*  f0c6ce8:	46007306 */ 	mov.s	$f12,$f14
/*  f0c6cec:	10000003 */ 	beqz	$zero,.L0f0c6cfc
/*  f0c6cf0:	24030004 */ 	addiu	$v1,$zero,0x4
/*  f0c6cf4:	46009306 */ 	mov.s	$f12,$f18
.L0f0c6cf8:
/*  f0c6cf8:	8d030038 */ 	lw	$v1,0x38($t0)
.L0f0c6cfc:
/*  f0c6cfc:	18600008 */ 	blez	$v1,.L0f0c6d20
/*  f0c6d00:	00001025 */ 	or	$v0,$zero,$zero
/*  f0c6d04:	3c017f1b */ 	lui	$at,%hi(var7f1ad818)
/*  f0c6d08:	c42ed818 */ 	lwc1	$f14,%lo(var7f1ad818)($at)
.L0f0c6d0c:
/*  f0c6d0c:	46020181 */ 	sub.s	$f6,$f0,$f2
/*  f0c6d10:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f0c6d14:	460e3102 */ 	mul.s	$f4,$f6,$f14
/*  f0c6d18:	1443fffc */ 	bne	$v0,$v1,.L0f0c6d0c
/*  f0c6d1c:	46041080 */ 	add.s	$f2,$f2,$f4
.L0f0c6d20:
/*  f0c6d20:	3c017f1b */ 	lui	$at,%hi(var7f1ad81c)
/*  f0c6d24:	c42ed81c */ 	lwc1	$f14,%lo(var7f1ad81c)($at)
/*  f0c6d28:	3c014070 */ 	lui	$at,0x4070
/*  f0c6d2c:	44814000 */ 	mtc1	$at,$f8
/*  f0c6d30:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c6d34:	3c01c234 */ 	lui	$at,0xc234
/*  f0c6d38:	44813000 */ 	mtc1	$at,$f6
/*  f0c6d3c:	c47000b4 */ 	lwc1	$f16,0xb4($v1)
/*  f0c6d40:	460c4282 */ 	mul.s	$f10,$f8,$f12
/*  f0c6d44:	4606803c */ 	c.lt.s	$f16,$f6
/*  f0c6d48:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6d4c:	45000006 */ 	bc1f	.L0f0c6d68
/*  f0c6d50:	460a1080 */ 	add.s	$f2,$f2,$f10
/*  f0c6d54:	3c017f1b */ 	lui	$at,%hi(var7f1ad820)
/*  f0c6d58:	c424d820 */ 	lwc1	$f4,%lo(var7f1ad820)($at)
/*  f0c6d5c:	46041082 */ 	mul.s	$f2,$f2,$f4
/*  f0c6d60:	1000000a */ 	beqz	$zero,.L0f0c6d8c
/*  f0c6d64:	4600103c */ 	c.lt.s	$f2,$f0
.L0f0c6d68:
/*  f0c6d68:	4614803c */ 	c.lt.s	$f16,$f20
/*  f0c6d6c:	3c013f00 */ 	lui	$at,0x3f00
/*  f0c6d70:	45020006 */ 	bc1fl	.L0f0c6d8c
/*  f0c6d74:	4600103c */ 	c.lt.s	$f2,$f0
/*  f0c6d78:	44814000 */ 	mtc1	$at,$f8
/*  f0c6d7c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6d80:	46081082 */ 	mul.s	$f2,$f2,$f8
/*  f0c6d84:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6d88:	4600103c */ 	c.lt.s	$f2,$f0
.L0f0c6d8c:
/*  f0c6d8c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6d90:	4502000a */ 	bc1fl	.L0f0c6dbc
/*  f0c6d94:	c46a0168 */ 	lwc1	$f10,0x168($v1)
/*  f0c6d98:	46001083 */ 	div.s	$f2,$f2,$f0
/*  f0c6d9c:	c7aa00b4 */ 	lwc1	$f10,0xb4($sp)
/*  f0c6da0:	c7a400b0 */ 	lwc1	$f4,0xb0($sp)
/*  f0c6da4:	46025182 */ 	mul.s	$f6,$f10,$f2
/*  f0c6da8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6dac:	46022202 */ 	mul.s	$f8,$f4,$f2
/*  f0c6db0:	e7a600b4 */ 	swc1	$f6,0xb4($sp)
/*  f0c6db4:	e7a800b0 */ 	swc1	$f8,0xb0($sp)
/*  f0c6db8:	c46a0168 */ 	lwc1	$f10,0x168($v1)
.L0f0c6dbc:
/*  f0c6dbc:	c7a600c4 */ 	lwc1	$f6,0xc4($sp)
/*  f0c6dc0:	3c017f1b */ 	lui	$at,%hi(var7f1ad824)
/*  f0c6dc4:	c428d824 */ 	lwc1	$f8,%lo(var7f1ad824)($at)
/*  f0c6dc8:	46065100 */ 	add.s	$f4,$f10,$f6
/*  f0c6dcc:	3c017f1b */ 	lui	$at,%hi(var7f1ad828)
/*  f0c6dd0:	c7a600c8 */ 	lwc1	$f6,0xc8($sp)
/*  f0c6dd4:	c46a0170 */ 	lwc1	$f10,0x170($v1)
/*  f0c6dd8:	46082082 */ 	mul.s	$f2,$f4,$f8
/*  f0c6ddc:	c428d828 */ 	lwc1	$f8,%lo(var7f1ad828)($at)
/*  f0c6de0:	c4640148 */ 	lwc1	$f4,0x148($v1)
/*  f0c6de4:	46082402 */ 	mul.s	$f16,$f4,$f8
/*  f0c6de8:	46065300 */ 	add.s	$f12,$f10,$f6
/*  f0c6dec:	4614103c */ 	c.lt.s	$f2,$f20
/*  f0c6df0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6df4:	45020003 */ 	bc1fl	.L0f0c6e04
/*  f0c6df8:	4614603c */ 	c.lt.s	$f12,$f20
/*  f0c6dfc:	46001087 */ 	neg.s	$f2,$f2
/*  f0c6e00:	4614603c */ 	c.lt.s	$f12,$f20
.L0f0c6e04:
/*  f0c6e04:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6e08:	45020003 */ 	bc1fl	.L0f0c6e18
/*  f0c6e0c:	4614803c */ 	c.lt.s	$f16,$f20
/*  f0c6e10:	46006307 */ 	neg.s	$f12,$f12
/*  f0c6e14:	4614803c */ 	c.lt.s	$f16,$f20
.L0f0c6e18:
/*  f0c6e18:	e7b0007c */ 	swc1	$f16,0x7c($sp)
/*  f0c6e1c:	45020004 */ 	bc1fl	.L0f0c6e30
/*  f0c6e20:	4602603c */ 	c.lt.s	$f12,$f2
/*  f0c6e24:	46008407 */ 	neg.s	$f16,$f16
/*  f0c6e28:	e7b0007c */ 	swc1	$f16,0x7c($sp)
/*  f0c6e2c:	4602603c */ 	c.lt.s	$f12,$f2
.L0f0c6e30:
/*  f0c6e30:	46006406 */ 	mov.s	$f16,$f12
/*  f0c6e34:	45020003 */ 	bc1fl	.L0f0c6e44
/*  f0c6e38:	c7a2007c */ 	lwc1	$f2,0x7c($sp)
/*  f0c6e3c:	46001406 */ 	mov.s	$f16,$f2
/*  f0c6e40:	c7a2007c */ 	lwc1	$f2,0x7c($sp)
.L0f0c6e44:
/*  f0c6e44:	4602803c */ 	c.lt.s	$f16,$f2
/*  f0c6e48:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6e4c:	45020003 */ 	bc1fl	.L0f0c6e5c
/*  f0c6e50:	4600703e */ 	c.le.s	$f14,$f0
/*  f0c6e54:	46001406 */ 	mov.s	$f16,$f2
/*  f0c6e58:	4600703e */ 	c.le.s	$f14,$f0
.L0f0c6e5c:
/*  f0c6e5c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6e60:	45000007 */ 	bc1f	.L0f0c6e80
/*  f0c6e64:	3c017f1b */ 	lui	$at,%hi(var7f1ad82c)
/*  f0c6e68:	c420d82c */ 	lwc1	$f0,%lo(var7f1ad82c)($at)
/*  f0c6e6c:	4600803c */ 	c.lt.s	$f16,$f0
/*  f0c6e70:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6e74:	45020003 */ 	bc1fl	.L0f0c6e84
/*  f0c6e78:	3c013f40 */ 	lui	$at,0x3f40
/*  f0c6e7c:	46000406 */ 	mov.s	$f16,$f0
.L0f0c6e80:
/*  f0c6e80:	3c013f40 */ 	lui	$at,0x3f40
.L0f0c6e84:
/*  f0c6e84:	44810000 */ 	mtc1	$at,$f0
/*  f0c6e88:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6e8c:	4610003e */ 	c.le.s	$f0,$f16
/*  f0c6e90:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6e94:	4502000b */ 	bc1fl	.L0f0c6ec4
/*  f0c6e98:	46100101 */ 	sub.s	$f4,$f0,$f16
/*  f0c6e9c:	46008281 */ 	sub.s	$f10,$f16,$f0
/*  f0c6ea0:	3c014461 */ 	lui	$at,0x4461
/*  f0c6ea4:	44812000 */ 	mtc1	$at,$f4
/*  f0c6ea8:	46125182 */ 	mul.s	$f6,$f10,$f18
/*  f0c6eac:	c46a0198 */ 	lwc1	$f10,0x198($v1)
/*  f0c6eb0:	46043203 */ 	div.s	$f8,$f6,$f4
/*  f0c6eb4:	46085180 */ 	add.s	$f6,$f10,$f8
/*  f0c6eb8:	10000009 */ 	beqz	$zero,.L0f0c6ee0
/*  f0c6ebc:	e4660198 */ 	swc1	$f6,0x198($v1)
/*  f0c6ec0:	46100101 */ 	sub.s	$f4,$f0,$f16
.L0f0c6ec4:
/*  f0c6ec4:	3c017f1b */ 	lui	$at,%hi(var7f1ad830)
/*  f0c6ec8:	c428d830 */ 	lwc1	$f8,%lo(var7f1ad830)($at)
/*  f0c6ecc:	46122282 */ 	mul.s	$f10,$f4,$f18
/*  f0c6ed0:	c4640198 */ 	lwc1	$f4,0x198($v1)
/*  f0c6ed4:	46085183 */ 	div.s	$f6,$f10,$f8
/*  f0c6ed8:	46062281 */ 	sub.s	$f10,$f4,$f6
/*  f0c6edc:	e46a0198 */ 	swc1	$f10,0x198($v1)
.L0f0c6ee0:
/*  f0c6ee0:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c6ee4:	c4600198 */ 	lwc1	$f0,0x198($v1)
/*  f0c6ee8:	4614003c */ 	c.lt.s	$f0,$f20
/*  f0c6eec:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6ef0:	45020005 */ 	bc1fl	.L0f0c6f08
/*  f0c6ef4:	3c013f80 */ 	lui	$at,0x3f80
/*  f0c6ef8:	e4740198 */ 	swc1	$f20,0x198($v1)
/*  f0c6efc:	1000000c */ 	beqz	$zero,.L0f0c6f30
/*  f0c6f00:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c6f04:	3c013f80 */ 	lui	$at,0x3f80
.L0f0c6f08:
/*  f0c6f08:	44814000 */ 	mtc1	$at,$f8
/*  f0c6f0c:	3c013f80 */ 	lui	$at,0x3f80
/*  f0c6f10:	4600403c */ 	c.lt.s	$f8,$f0
/*  f0c6f14:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6f18:	45000005 */ 	bc1f	.L0f0c6f30
/*  f0c6f1c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6f20:	44812000 */ 	mtc1	$at,$f4
/*  f0c6f24:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c6f28:	e4640198 */ 	swc1	$f4,0x198($v1)
/*  f0c6f2c:	8d030284 */ 	lw	$v1,0x284($t0)
.L0f0c6f30:
/*  f0c6f30:	3c018007 */ 	lui	$at,0x8007
/*  f0c6f34:	c4265c24 */ 	lwc1	$f6,0x5c24($at)
/*  f0c6f38:	3c013f00 */ 	lui	$at,0x3f00
/*  f0c6f3c:	44815000 */ 	mtc1	$at,$f10
/*  f0c6f40:	c504004c */ 	lwc1	$f4,0x4c($t0)
/*  f0c6f44:	2404000a */ 	addiu	$a0,$zero,0xa
/*  f0c6f48:	460a3202 */ 	mul.s	$f8,$f6,$f10
/*  f0c6f4c:	c7aa00c0 */ 	lwc1	$f10,0xc0($sp)
/*  f0c6f50:	c4660168 */ 	lwc1	$f6,0x168($v1)
/*  f0c6f54:	e7b00078 */ 	swc1	$f16,0x78($sp)
/*  f0c6f58:	46044002 */ 	mul.s	$f0,$f8,$f4
/*  f0c6f5c:	c7a400c4 */ 	lwc1	$f4,0xc4($sp)
/*  f0c6f60:	460a3202 */ 	mul.s	$f8,$f6,$f10
/*  f0c6f64:	46044180 */ 	add.s	$f6,$f8,$f4
/*  f0c6f68:	46003082 */ 	mul.s	$f2,$f6,$f0
/*  f0c6f6c:	0fc41b99 */ 	jal	cheatIsActive
/*  f0c6f70:	e7a200e0 */ 	swc1	$f2,0xe0($sp)
/*  f0c6f74:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c6f78:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c6f7c:	10400004 */ 	beqz	$v0,.L0f0c6f90
/*  f0c6f80:	c7a200e0 */ 	lwc1	$f2,0xe0($sp)
/*  f0c6f84:	3c017f1b */ 	lui	$at,%hi(var7f1ad834)
/*  f0c6f88:	c42ad834 */ 	lwc1	$f10,%lo(var7f1ad834)($at)
/*  f0c6f8c:	460a1083 */ 	div.s	$f2,$f2,$f10
.L0f0c6f90:
/*  f0c6f90:	8d0b0284 */ 	lw	$t3,0x284($t0)
/*  f0c6f94:	c7a400c0 */ 	lwc1	$f4,0xc0($sp)
/*  f0c6f98:	c7aa00c8 */ 	lwc1	$f10,0xc8($sp)
/*  f0c6f9c:	c5680170 */ 	lwc1	$f8,0x170($t3)
/*  f0c6fa0:	44061000 */ 	mfc1	$a2,$f2
/*  f0c6fa4:	c7ac0078 */ 	lwc1	$f12,0x78($sp)
/*  f0c6fa8:	46044182 */ 	mul.s	$f6,$f8,$f4
/*  f0c6fac:	0fc33195 */ 	jal	func0f0cc654
/*  f0c6fb0:	460a3380 */ 	add.s	$f14,$f6,$f10
/*  f0c6fb4:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c6fb8:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c6fbc:	8d0c0284 */ 	lw	$t4,0x284($t0)
/*  f0c6fc0:	c7a80078 */ 	lwc1	$f8,0x78($sp)
/*  f0c6fc4:	2404000a */ 	addiu	$a0,$zero,0xa
/*  f0c6fc8:	e58800cc */ 	swc1	$f8,0xcc($t4)
/*  f0c6fcc:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c6fd0:	c46003c0 */ 	lwc1	$f0,0x3c0($v1)
/*  f0c6fd4:	c46203c8 */ 	lwc1	$f2,0x3c8($v1)
/*  f0c6fd8:	e7a000dc */ 	swc1	$f0,0xdc($sp)
/*  f0c6fdc:	0fc41b99 */ 	jal	cheatIsActive
/*  f0c6fe0:	e7a200d8 */ 	swc1	$f2,0xd8($sp)
/*  f0c6fe4:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c6fe8:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c6fec:	c7a000dc */ 	lwc1	$f0,0xdc($sp)
/*  f0c6ff0:	10400005 */ 	beqz	$v0,.L0f0c7008
/*  f0c6ff4:	c7a200d8 */ 	lwc1	$f2,0xd8($sp)
/*  f0c6ff8:	3c017f1b */ 	lui	$at,%hi(var7f1ad838)
/*  f0c6ffc:	c424d838 */ 	lwc1	$f4,%lo(var7f1ad838)($at)
/*  f0c7000:	46040002 */ 	mul.s	$f0,$f0,$f4
/*  f0c7004:	00000000 */ 	sll	$zero,$zero,0x0
.L0f0c7008:
/*  f0c7008:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c700c:	c512004c */ 	lwc1	$f18,0x4c($t0)
/*  f0c7010:	27a400cc */ 	addiu	$a0,$sp,0xcc
/*  f0c7014:	c466036c */ 	lwc1	$f6,0x36c($v1)
/*  f0c7018:	c4680374 */ 	lwc1	$f8,0x374($v1)
/*  f0c701c:	46061282 */ 	mul.s	$f10,$f2,$f6
/*  f0c7020:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7024:	46080102 */ 	mul.s	$f4,$f0,$f8
/*  f0c7028:	46045181 */ 	sub.s	$f6,$f10,$f4
/*  f0c702c:	c7aa00cc */ 	lwc1	$f10,0xcc($sp)
/*  f0c7030:	46123202 */ 	mul.s	$f8,$f6,$f18
/*  f0c7034:	46085100 */ 	add.s	$f4,$f10,$f8
/*  f0c7038:	e7a400cc */ 	swc1	$f4,0xcc($sp)
/*  f0c703c:	c4660374 */ 	lwc1	$f6,0x374($v1)
/*  f0c7040:	c468036c */ 	lwc1	$f8,0x36c($v1)
/*  f0c7044:	46061282 */ 	mul.s	$f10,$f2,$f6
/*  f0c7048:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c704c:	46080182 */ 	mul.s	$f6,$f0,$f8
/*  f0c7050:	46065200 */ 	add.s	$f8,$f10,$f6
/*  f0c7054:	c7a600d4 */ 	lwc1	$f6,0xd4($sp)
/*  f0c7058:	46124282 */ 	mul.s	$f10,$f8,$f18
/*  f0c705c:	460a3200 */ 	add.s	$f8,$f6,$f10
/*  f0c7060:	c7a600b4 */ 	lwc1	$f6,0xb4($sp)
/*  f0c7064:	46062280 */ 	add.s	$f10,$f4,$f6
/*  f0c7068:	c7a400b0 */ 	lwc1	$f4,0xb0($sp)
/*  f0c706c:	e7a800d4 */ 	swc1	$f8,0xd4($sp)
/*  f0c7070:	46044180 */ 	add.s	$f6,$f8,$f4
/*  f0c7074:	e7aa00cc */ 	swc1	$f10,0xcc($sp)
/*  f0c7078:	0fc32ed2 */ 	jal	currentPlayerUpdateMoveInitSpeed
/*  f0c707c:	e7a600d4 */ 	swc1	$f6,0xd4($sp)
/*  f0c7080:	0fc47b82 */ 	jal	debugIsTurboModeEnabled
/*  f0c7084:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7088:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c708c:	1040001f */ 	beqz	$v0,.L0f0c710c
/*  f0c7090:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c7094:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c7098:	c512004c */ 	lwc1	$f18,0x4c($t0)
/*  f0c709c:	3c014120 */ 	lui	$at,0x4120
/*  f0c70a0:	c46a036c */ 	lwc1	$f10,0x36c($v1)
/*  f0c70a4:	c4680170 */ 	lwc1	$f8,0x170($v1)
/*  f0c70a8:	c4660374 */ 	lwc1	$f6,0x374($v1)
/*  f0c70ac:	44810000 */ 	mtc1	$at,$f0
/*  f0c70b0:	46085102 */ 	mul.s	$f4,$f10,$f8
/*  f0c70b4:	c46a0168 */ 	lwc1	$f10,0x168($v1)
/*  f0c70b8:	460a3202 */ 	mul.s	$f8,$f6,$f10
/*  f0c70bc:	46082181 */ 	sub.s	$f6,$f4,$f8
/*  f0c70c0:	c7a800cc */ 	lwc1	$f8,0xcc($sp)
/*  f0c70c4:	46123282 */ 	mul.s	$f10,$f6,$f18
/*  f0c70c8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c70cc:	46005102 */ 	mul.s	$f4,$f10,$f0
/*  f0c70d0:	46044180 */ 	add.s	$f6,$f8,$f4
/*  f0c70d4:	e7a600cc */ 	swc1	$f6,0xcc($sp)
/*  f0c70d8:	c4680170 */ 	lwc1	$f8,0x170($v1)
/*  f0c70dc:	c46a0374 */ 	lwc1	$f10,0x374($v1)
/*  f0c70e0:	c466036c */ 	lwc1	$f6,0x36c($v1)
/*  f0c70e4:	46085102 */ 	mul.s	$f4,$f10,$f8
/*  f0c70e8:	c46a0168 */ 	lwc1	$f10,0x168($v1)
/*  f0c70ec:	460a3202 */ 	mul.s	$f8,$f6,$f10
/*  f0c70f0:	46082180 */ 	add.s	$f6,$f4,$f8
/*  f0c70f4:	c7a800d4 */ 	lwc1	$f8,0xd4($sp)
/*  f0c70f8:	46123282 */ 	mul.s	$f10,$f6,$f18
/*  f0c70fc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7100:	46005102 */ 	mul.s	$f4,$f10,$f0
/*  f0c7104:	46044180 */ 	add.s	$f6,$f8,$f4
/*  f0c7108:	e7a600d4 */ 	swc1	$f6,0xd4($sp)
.L0f0c710c:
/*  f0c710c:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c7110:	c4601b6c */ 	lwc1	$f0,0x1b6c($v1)
/*  f0c7114:	4600a032 */ 	c.eq.s	$f20,$f0
/*  f0c7118:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c711c:	45020007 */ 	bc1fl	.L0f0c713c
/*  f0c7120:	c512004c */ 	lwc1	$f18,0x4c($t0)
/*  f0c7124:	c46a1b74 */ 	lwc1	$f10,0x1b74($v1)
/*  f0c7128:	460aa032 */ 	c.eq.s	$f20,$f10
/*  f0c712c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7130:	4503000c */ 	bc1tl	.L0f0c7164
/*  f0c7134:	8c6d02ac */ 	lw	$t5,0x2ac($v1)
/*  f0c7138:	c512004c */ 	lwc1	$f18,0x4c($t0)
.L0f0c713c:
/*  f0c713c:	c7a800cc */ 	lwc1	$f8,0xcc($sp)
/*  f0c7140:	c7aa00d4 */ 	lwc1	$f10,0xd4($sp)
/*  f0c7144:	46120102 */ 	mul.s	$f4,$f0,$f18
/*  f0c7148:	46044180 */ 	add.s	$f6,$f8,$f4
/*  f0c714c:	e7a600cc */ 	swc1	$f6,0xcc($sp)
/*  f0c7150:	c4681b74 */ 	lwc1	$f8,0x1b74($v1)
/*  f0c7154:	46124102 */ 	mul.s	$f4,$f8,$f18
/*  f0c7158:	46045180 */ 	add.s	$f6,$f10,$f4
/*  f0c715c:	e7a600d4 */ 	swc1	$f6,0xd4($sp)
/*  f0c7160:	8c6d02ac */ 	lw	$t5,0x2ac($v1)
.L0f0c7164:
/*  f0c7164:	246402a0 */ 	addiu	$a0,$v1,0x2a0
/*  f0c7168:	246502a4 */ 	addiu	$a1,$v1,0x2a4
/*  f0c716c:	51a0006a */ 	beqzl	$t5,.L0f0c7318
/*  f0c7170:	8c640298 */ 	lw	$a0,0x298($v1)
/*  f0c7174:	0c0011e4 */ 	jal	scaleTo1
/*  f0c7178:	246602a8 */ 	addiu	$a2,$v1,0x2a8
/*  f0c717c:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c7180:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c7184:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c7188:	c7aa00d4 */ 	lwc1	$f10,0xd4($sp)
/*  f0c718c:	c7a600cc */ 	lwc1	$f6,0xcc($sp)
/*  f0c7190:	c46802a8 */ 	lwc1	$f8,0x2a8($v1)
/*  f0c7194:	c46202a0 */ 	lwc1	$f2,0x2a0($v1)
/*  f0c7198:	3c01c080 */ 	lui	$at,0xc080
/*  f0c719c:	460a4102 */ 	mul.s	$f4,$f8,$f10
/*  f0c71a0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c71a4:	46023202 */ 	mul.s	$f8,$f6,$f2
/*  f0c71a8:	46082000 */ 	add.s	$f0,$f4,$f8
/*  f0c71ac:	c508004c */ 	lwc1	$f8,0x4c($t0)
/*  f0c71b0:	44812000 */ 	mtc1	$at,$f4
/*  f0c71b4:	46000007 */ 	neg.s	$f0,$f0
/*  f0c71b8:	46082102 */ 	mul.s	$f4,$f4,$f8
/*  f0c71bc:	4600203c */ 	c.lt.s	$f4,$f0
/*  f0c71c0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c71c4:	45000051 */ 	bc1f	.L0f0c730c
/*  f0c71c8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c71cc:	4614003c */ 	c.lt.s	$f0,$f20
/*  f0c71d0:	27a50070 */ 	addiu	$a1,$sp,0x70
/*  f0c71d4:	27a6006c */ 	addiu	$a2,$sp,0x6c
/*  f0c71d8:	27a70068 */ 	addiu	$a3,$sp,0x68
/*  f0c71dc:	4502000e */ 	bc1fl	.L0f0c7218
/*  f0c71e0:	8c6400bc */ 	lw	$a0,0xbc($v1)
/*  f0c71e4:	46020202 */ 	mul.s	$f8,$f0,$f2
/*  f0c71e8:	3c017f1b */ 	lui	$at,%hi(var7f1ad83c)
/*  f0c71ec:	c42cd83c */ 	lwc1	$f12,%lo(var7f1ad83c)($at)
/*  f0c71f0:	46083100 */ 	add.s	$f4,$f6,$f8
/*  f0c71f4:	e7a400cc */ 	swc1	$f4,0xcc($sp)
/*  f0c71f8:	c46602a8 */ 	lwc1	$f6,0x2a8($v1)
/*  f0c71fc:	46060202 */ 	mul.s	$f8,$f0,$f6
/*  f0c7200:	46085100 */ 	add.s	$f4,$f10,$f8
/*  f0c7204:	460c0182 */ 	mul.s	$f6,$f0,$f12
/*  f0c7208:	e7a400d4 */ 	swc1	$f4,0xd4($sp)
/*  f0c720c:	10000036 */ 	beqz	$zero,.L0f0c72e8
/*  f0c7210:	e466029c */ 	swc1	$f6,0x29c($v1)
/*  f0c7214:	8c6400bc */ 	lw	$a0,0xbc($v1)
.L0f0c7218:
/*  f0c7218:	0fc3082e */ 	jal	propPlayerGetBbox
/*  f0c721c:	e7a00074 */ 	swc1	$f0,0x74($sp)
/*  f0c7220:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c7224:	3c017f1b */ 	lui	$at,%hi(var7f1ad840)
/*  f0c7228:	c428d840 */ 	lwc1	$f8,%lo(var7f1ad840)($at)
/*  f0c722c:	c7aa0070 */ 	lwc1	$f10,0x70($sp)
/*  f0c7230:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c7234:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c7238:	46085102 */ 	mul.s	$f4,$f10,$f8
/*  f0c723c:	c7a6006c */ 	lwc1	$f6,0x6c($sp)
/*  f0c7240:	8c6200bc */ 	lw	$v0,0xbc($v1)
/*  f0c7244:	c4680074 */ 	lwc1	$f8,0x74($v1)
/*  f0c7248:	3c013f80 */ 	lui	$at,0x3f80
/*  f0c724c:	c442000c */ 	lwc1	$f2,0xc($v0)
/*  f0c7250:	34188040 */ 	dli	$t8,0x8040
/*  f0c7254:	44052000 */ 	mfc1	$a1,$f4
/*  f0c7258:	46023281 */ 	sub.s	$f10,$f6,$f2
/*  f0c725c:	44813000 */ 	mtc1	$at,$f6
/*  f0c7260:	24590028 */ 	addiu	$t9,$v0,0x28
/*  f0c7264:	46024101 */ 	sub.s	$f4,$f8,$f2
/*  f0c7268:	44065000 */ 	mfc1	$a2,$f10
/*  f0c726c:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f0c7270:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f0c7274:	46062280 */ 	add.s	$f10,$f4,$f6
/*  f0c7278:	24440008 */ 	addiu	$a0,$v0,0x8
/*  f0c727c:	44075000 */ 	mfc1	$a3,$f10
/*  f0c7280:	0c00a84f */ 	jal	func0002a13c
/*  f0c7284:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7288:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c728c:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c7290:	14400006 */ 	bnez	$v0,.L0f0c72ac
/*  f0c7294:	c7a00074 */ 	lwc1	$f0,0x74($sp)
/*  f0c7298:	8d0e0284 */ 	lw	$t6,0x284($t0)
/*  f0c729c:	3c017f1b */ 	lui	$at,%hi(var7f1ad844)
/*  f0c72a0:	e5d4029c */ 	swc1	$f20,0x29c($t6)
/*  f0c72a4:	10000010 */ 	beqz	$zero,.L0f0c72e8
/*  f0c72a8:	c42cd844 */ 	lwc1	$f12,%lo(var7f1ad844)($at)
.L0f0c72ac:
/*  f0c72ac:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c72b0:	c7a800cc */ 	lwc1	$f8,0xcc($sp)
/*  f0c72b4:	3c017f1b */ 	lui	$at,%hi(var7f1ad848)
/*  f0c72b8:	c46402a0 */ 	lwc1	$f4,0x2a0($v1)
/*  f0c72bc:	c42cd848 */ 	lwc1	$f12,%lo(var7f1ad848)($at)
/*  f0c72c0:	46040182 */ 	mul.s	$f6,$f0,$f4
/*  f0c72c4:	c7a400d4 */ 	lwc1	$f4,0xd4($sp)
/*  f0c72c8:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f0c72cc:	e7aa00cc */ 	swc1	$f10,0xcc($sp)
/*  f0c72d0:	c46802a8 */ 	lwc1	$f8,0x2a8($v1)
/*  f0c72d4:	46080182 */ 	mul.s	$f6,$f0,$f8
/*  f0c72d8:	46062280 */ 	add.s	$f10,$f4,$f6
/*  f0c72dc:	460c0202 */ 	mul.s	$f8,$f0,$f12
/*  f0c72e0:	e7aa00d4 */ 	swc1	$f10,0xd4($sp)
/*  f0c72e4:	e468029c */ 	swc1	$f8,0x29c($v1)
.L0f0c72e8:
/*  f0c72e8:	c7a400cc */ 	lwc1	$f4,0xcc($sp)
/*  f0c72ec:	c7aa00d4 */ 	lwc1	$f10,0xd4($sp)
/*  f0c72f0:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c72f4:	460c2182 */ 	mul.s	$f6,$f4,$f12
/*  f0c72f8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c72fc:	460c5202 */ 	mul.s	$f8,$f10,$f12
/*  f0c7300:	e7a600cc */ 	swc1	$f6,0xcc($sp)
/*  f0c7304:	10000003 */ 	beqz	$zero,.L0f0c7314
/*  f0c7308:	e7a800d4 */ 	swc1	$f8,0xd4($sp)
.L0f0c730c:
/*  f0c730c:	e474029c */ 	swc1	$f20,0x29c($v1)
/*  f0c7310:	8d030284 */ 	lw	$v1,0x284($t0)
.L0f0c7314:
/*  f0c7314:	8c640298 */ 	lw	$a0,0x298($v1)
.L0f0c7318:
/*  f0c7318:	50800015 */ 	beqzl	$a0,.L0f0c7370
/*  f0c731c:	8c6200bc */ 	lw	$v0,0xbc($v1)
/*  f0c7320:	8c820004 */ 	lw	$v0,0x4($a0)
/*  f0c7324:	2401003b */ 	addiu	$at,$zero,0x3b
/*  f0c7328:	904f0003 */ 	lbu	$t7,0x3($v0)
/*  f0c732c:	55e10010 */ 	bnel	$t7,$at,.L0f0c7370
/*  f0c7330:	8c6200bc */ 	lw	$v0,0xbc($v1)
/*  f0c7334:	8c490014 */ 	lw	$t1,0x14($v0)
/*  f0c7338:	c4460060 */ 	lwc1	$f6,0x60($v0)
/*  f0c733c:	c7a800cc */ 	lwc1	$f8,0xcc($sp)
/*  f0c7340:	c5240008 */ 	lwc1	$f4,0x8($t1)
/*  f0c7344:	46062281 */ 	sub.s	$f10,$f4,$f6
/*  f0c7348:	460a4100 */ 	add.s	$f4,$f8,$f10
/*  f0c734c:	e7a400cc */ 	swc1	$f4,0xcc($sp)
/*  f0c7350:	8c4a0014 */ 	lw	$t2,0x14($v0)
/*  f0c7354:	c4480068 */ 	lwc1	$f8,0x68($v0)
/*  f0c7358:	c7a400d4 */ 	lwc1	$f4,0xd4($sp)
/*  f0c735c:	c5460010 */ 	lwc1	$f6,0x10($t2)
/*  f0c7360:	46083281 */ 	sub.s	$f10,$f6,$f8
/*  f0c7364:	460a2180 */ 	add.s	$f6,$f4,$f10
/*  f0c7368:	e7a600d4 */ 	swc1	$f6,0xd4($sp)
/*  f0c736c:	8c6200bc */ 	lw	$v0,0xbc($v1)
.L0f0c7370:
/*  f0c7370:	27a400cc */ 	addiu	$a0,$sp,0xcc
/*  f0c7374:	00002825 */ 	or	$a1,$zero,$zero
/*  f0c7378:	c4480008 */ 	lwc1	$f8,0x8($v0)
/*  f0c737c:	e7a8008c */ 	swc1	$f8,0x8c($sp)
/*  f0c7380:	c4440010 */ 	lwc1	$f4,0x10($v0)
/*  f0c7384:	e7a40088 */ 	swc1	$f4,0x88($sp)
/*  f0c7388:	c46a00a0 */ 	lwc1	$f10,0xa0($v1)
/*  f0c738c:	460aa032 */ 	c.eq.s	$f20,$f10
/*  f0c7390:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7394:	45000002 */ 	bc1f	.L0f0c73a0
/*  f0c7398:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c739c:	24050001 */ 	addiu	$a1,$zero,0x1
.L0f0c73a0:
/*  f0c73a0:	0fc318ef */ 	jal	func0f0c63bc
/*  f0c73a4:	2406003f */ 	addiu	$a2,$zero,0x3f
/*  f0c73a8:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c73ac:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c73b0:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c73b4:	8c6200bc */ 	lw	$v0,0xbc($v1)
/*  f0c73b8:	c46a0318 */ 	lwc1	$f10,0x318($v1)
/*  f0c73bc:	c4680310 */ 	lwc1	$f8,0x310($v1)
/*  f0c73c0:	c4440010 */ 	lwc1	$f4,0x10($v0)
/*  f0c73c4:	c4460008 */ 	lwc1	$f6,0x8($v0)
/*  f0c73c8:	c462036c */ 	lwc1	$f2,0x36c($v1)
/*  f0c73cc:	460a2381 */ 	sub.s	$f14,$f4,$f10
/*  f0c73d0:	c4600374 */ 	lwc1	$f0,0x374($v1)
/*  f0c73d4:	46083301 */ 	sub.s	$f12,$f6,$f8
/*  f0c73d8:	460e1182 */ 	mul.s	$f6,$f2,$f14
/*  f0c73dc:	46006207 */ 	neg.s	$f8,$f12
/*  f0c73e0:	46004102 */ 	mul.s	$f4,$f8,$f0
/*  f0c73e4:	460ca03e */ 	c.le.s	$f20,$f12
/*  f0c73e8:	460e0282 */ 	mul.s	$f10,$f0,$f14
/*  f0c73ec:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c73f0:	46026202 */ 	mul.s	$f8,$f12,$f2
/*  f0c73f4:	46043400 */ 	add.s	$f16,$f6,$f4
/*  f0c73f8:	c7a600d4 */ 	lwc1	$f6,0xd4($sp)
/*  f0c73fc:	46061102 */ 	mul.s	$f4,$f2,$f6
/*  f0c7400:	46085480 */ 	add.s	$f18,$f10,$f8
/*  f0c7404:	c7aa00cc */ 	lwc1	$f10,0xcc($sp)
/*  f0c7408:	46005207 */ 	neg.s	$f8,$f10
/*  f0c740c:	46004202 */ 	mul.s	$f8,$f8,$f0
/*  f0c7410:	46082100 */ 	add.s	$f4,$f4,$f8
/*  f0c7414:	46060202 */ 	mul.s	$f8,$f0,$f6
/*  f0c7418:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c741c:	46025182 */ 	mul.s	$f6,$f10,$f2
/*  f0c7420:	e7a4004c */ 	swc1	$f4,0x4c($sp)
/*  f0c7424:	46064200 */ 	add.s	$f8,$f8,$f6
/*  f0c7428:	4500001c */ 	bc1f	.L0f0c749c
/*  f0c742c:	e7a80048 */ 	swc1	$f8,0x48($sp)
/*  f0c7430:	c460017c */ 	lwc1	$f0,0x17c($v1)
/*  f0c7434:	46002086 */ 	mov.s	$f2,$f4
/*  f0c7438:	c7a400cc */ 	lwc1	$f4,0xcc($sp)
/*  f0c743c:	4600a03c */ 	c.lt.s	$f20,$f0
/*  f0c7440:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7444:	4502000f */ 	bc1fl	.L0f0c7484
/*  f0c7448:	4614203c */ 	c.lt.s	$f4,$f20
/*  f0c744c:	460aa03e */ 	c.le.s	$f20,$f10
/*  f0c7450:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7454:	4502002c */ 	bc1fl	.L0f0c7508
/*  f0c7458:	460ea03e */ 	c.le.s	$f20,$f14
/*  f0c745c:	460a603c */ 	c.lt.s	$f12,$f10
/*  f0c7460:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7464:	45020028 */ 	bc1fl	.L0f0c7508
/*  f0c7468:	460ea03e */ 	c.le.s	$f20,$f14
/*  f0c746c:	460a6183 */ 	div.s	$f6,$f12,$f10
/*  f0c7470:	46060202 */ 	mul.s	$f8,$f0,$f6
/*  f0c7474:	e468017c */ 	swc1	$f8,0x17c($v1)
/*  f0c7478:	10000022 */ 	beqz	$zero,.L0f0c7504
/*  f0c747c:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c7480:	4614203c */ 	c.lt.s	$f4,$f20
.L0f0c7484:
/*  f0c7484:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7488:	4502001f */ 	bc1fl	.L0f0c7508
/*  f0c748c:	460ea03e */ 	c.le.s	$f20,$f14
/*  f0c7490:	e474017c */ 	swc1	$f20,0x17c($v1)
/*  f0c7494:	1000001b */ 	beqz	$zero,.L0f0c7504
/*  f0c7498:	8d030284 */ 	lw	$v1,0x284($t0)
.L0f0c749c:
/*  f0c749c:	c460017c */ 	lwc1	$f0,0x17c($v1)
/*  f0c74a0:	c7a2004c */ 	lwc1	$f2,0x4c($sp)
/*  f0c74a4:	c7aa00cc */ 	lwc1	$f10,0xcc($sp)
/*  f0c74a8:	4614003c */ 	c.lt.s	$f0,$f20
/*  f0c74ac:	c7a400cc */ 	lwc1	$f4,0xcc($sp)
/*  f0c74b0:	4502000f */ 	bc1fl	.L0f0c74f0
/*  f0c74b4:	4604a03c */ 	c.lt.s	$f20,$f4
/*  f0c74b8:	4614503e */ 	c.le.s	$f10,$f20
/*  f0c74bc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c74c0:	45020011 */ 	bc1fl	.L0f0c7508
/*  f0c74c4:	460ea03e */ 	c.le.s	$f20,$f14
/*  f0c74c8:	460c503c */ 	c.lt.s	$f10,$f12
/*  f0c74cc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c74d0:	4502000d */ 	bc1fl	.L0f0c7508
/*  f0c74d4:	460ea03e */ 	c.le.s	$f20,$f14
/*  f0c74d8:	460a6183 */ 	div.s	$f6,$f12,$f10
/*  f0c74dc:	46060202 */ 	mul.s	$f8,$f0,$f6
/*  f0c74e0:	e468017c */ 	swc1	$f8,0x17c($v1)
/*  f0c74e4:	10000007 */ 	beqz	$zero,.L0f0c7504
/*  f0c74e8:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c74ec:	4604a03c */ 	c.lt.s	$f20,$f4
.L0f0c74f0:
/*  f0c74f0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c74f4:	45020004 */ 	bc1fl	.L0f0c7508
/*  f0c74f8:	460ea03e */ 	c.le.s	$f20,$f14
/*  f0c74fc:	e474017c */ 	swc1	$f20,0x17c($v1)
/*  f0c7500:	8d030284 */ 	lw	$v1,0x284($t0)
.L0f0c7504:
/*  f0c7504:	460ea03e */ 	c.le.s	$f20,$f14
.L0f0c7508:
/*  f0c7508:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c750c:	4502001d */ 	bc1fl	.L0f0c7584
/*  f0c7510:	c4600184 */ 	lwc1	$f0,0x184($v1)
/*  f0c7514:	c4600184 */ 	lwc1	$f0,0x184($v1)
/*  f0c7518:	c7aa00d4 */ 	lwc1	$f10,0xd4($sp)
/*  f0c751c:	c7a400d4 */ 	lwc1	$f4,0xd4($sp)
/*  f0c7520:	4600a03c */ 	c.lt.s	$f20,$f0
/*  f0c7524:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7528:	4502000f */ 	bc1fl	.L0f0c7568
/*  f0c752c:	4614203c */ 	c.lt.s	$f4,$f20
/*  f0c7530:	460aa03e */ 	c.le.s	$f20,$f10
/*  f0c7534:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7538:	4502002c */ 	bc1fl	.L0f0c75ec
/*  f0c753c:	46141032 */ 	c.eq.s	$f2,$f20
/*  f0c7540:	460a703c */ 	c.lt.s	$f14,$f10
/*  f0c7544:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7548:	45020028 */ 	bc1fl	.L0f0c75ec
/*  f0c754c:	46141032 */ 	c.eq.s	$f2,$f20
/*  f0c7550:	460a7183 */ 	div.s	$f6,$f14,$f10
/*  f0c7554:	46060202 */ 	mul.s	$f8,$f0,$f6
/*  f0c7558:	e4680184 */ 	swc1	$f8,0x184($v1)
/*  f0c755c:	10000022 */ 	beqz	$zero,.L0f0c75e8
/*  f0c7560:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c7564:	4614203c */ 	c.lt.s	$f4,$f20
.L0f0c7568:
/*  f0c7568:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c756c:	4502001f */ 	bc1fl	.L0f0c75ec
/*  f0c7570:	46141032 */ 	c.eq.s	$f2,$f20
/*  f0c7574:	e4740184 */ 	swc1	$f20,0x184($v1)
/*  f0c7578:	1000001b */ 	beqz	$zero,.L0f0c75e8
/*  f0c757c:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c7580:	c4600184 */ 	lwc1	$f0,0x184($v1)
.L0f0c7584:
/*  f0c7584:	c7aa00d4 */ 	lwc1	$f10,0xd4($sp)
/*  f0c7588:	c7a400d4 */ 	lwc1	$f4,0xd4($sp)
/*  f0c758c:	4614003c */ 	c.lt.s	$f0,$f20
/*  f0c7590:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7594:	4502000f */ 	bc1fl	.L0f0c75d4
/*  f0c7598:	4604a03c */ 	c.lt.s	$f20,$f4
/*  f0c759c:	4614503e */ 	c.le.s	$f10,$f20
/*  f0c75a0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c75a4:	45020011 */ 	bc1fl	.L0f0c75ec
/*  f0c75a8:	46141032 */ 	c.eq.s	$f2,$f20
/*  f0c75ac:	460e503c */ 	c.lt.s	$f10,$f14
/*  f0c75b0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c75b4:	4502000d */ 	bc1fl	.L0f0c75ec
/*  f0c75b8:	46141032 */ 	c.eq.s	$f2,$f20
/*  f0c75bc:	460a7183 */ 	div.s	$f6,$f14,$f10
/*  f0c75c0:	46060202 */ 	mul.s	$f8,$f0,$f6
/*  f0c75c4:	e4680184 */ 	swc1	$f8,0x184($v1)
/*  f0c75c8:	10000007 */ 	beqz	$zero,.L0f0c75e8
/*  f0c75cc:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c75d0:	4604a03c */ 	c.lt.s	$f20,$f4
.L0f0c75d4:
/*  f0c75d4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c75d8:	45020004 */ 	bc1fl	.L0f0c75ec
/*  f0c75dc:	46141032 */ 	c.eq.s	$f2,$f20
/*  f0c75e0:	e4740184 */ 	swc1	$f20,0x184($v1)
/*  f0c75e4:	8d030284 */ 	lw	$v1,0x284($t0)
.L0f0c75e8:
/*  f0c75e8:	46141032 */ 	c.eq.s	$f2,$f20
.L0f0c75ec:
/*  f0c75ec:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c75f0:	4503001a */ 	bc1tl	.L0f0c765c
/*  f0c75f4:	c7a20048 */ 	lwc1	$f2,0x48($sp)
/*  f0c75f8:	c460016c */ 	lwc1	$f0,0x16c($v1)
/*  f0c75fc:	46020282 */ 	mul.s	$f10,$f0,$f2
/*  f0c7600:	460aa03c */ 	c.lt.s	$f20,$f10
/*  f0c7604:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7608:	45020014 */ 	bc1fl	.L0f0c765c
/*  f0c760c:	c7a20048 */ 	lwc1	$f2,0x48($sp)
/*  f0c7610:	46028403 */ 	div.s	$f16,$f16,$f2
/*  f0c7614:	3c013f80 */ 	lui	$at,0x3f80
/*  f0c7618:	4614803e */ 	c.le.s	$f16,$f20
/*  f0c761c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7620:	45020005 */ 	bc1fl	.L0f0c7638
/*  f0c7624:	44813000 */ 	mtc1	$at,$f6
/*  f0c7628:	e474016c */ 	swc1	$f20,0x16c($v1)
/*  f0c762c:	1000000a */ 	beqz	$zero,.L0f0c7658
/*  f0c7630:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c7634:	44813000 */ 	mtc1	$at,$f6
.L0f0c7638:
/*  f0c7638:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c763c:	4606803c */ 	c.lt.s	$f16,$f6
/*  f0c7640:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7644:	45020005 */ 	bc1fl	.L0f0c765c
/*  f0c7648:	c7a20048 */ 	lwc1	$f2,0x48($sp)
/*  f0c764c:	46100202 */ 	mul.s	$f8,$f0,$f16
/*  f0c7650:	e468016c */ 	swc1	$f8,0x16c($v1)
/*  f0c7654:	8d030284 */ 	lw	$v1,0x284($t0)
.L0f0c7658:
/*  f0c7658:	c7a20048 */ 	lwc1	$f2,0x48($sp)
.L0f0c765c:
/*  f0c765c:	46141032 */ 	c.eq.s	$f2,$f20
/*  f0c7660:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7664:	4503001a */ 	bc1tl	.L0f0c76d0
/*  f0c7668:	8c6200bc */ 	lw	$v0,0xbc($v1)
/*  f0c766c:	c46019a4 */ 	lwc1	$f0,0x19a4($v1)
/*  f0c7670:	46020102 */ 	mul.s	$f4,$f0,$f2
/*  f0c7674:	4604a03c */ 	c.lt.s	$f20,$f4
/*  f0c7678:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c767c:	45020014 */ 	bc1fl	.L0f0c76d0
/*  f0c7680:	8c6200bc */ 	lw	$v0,0xbc($v1)
/*  f0c7684:	46029483 */ 	div.s	$f18,$f18,$f2
/*  f0c7688:	3c013f80 */ 	lui	$at,0x3f80
/*  f0c768c:	4614903e */ 	c.le.s	$f18,$f20
/*  f0c7690:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7694:	45020005 */ 	bc1fl	.L0f0c76ac
/*  f0c7698:	44815000 */ 	mtc1	$at,$f10
/*  f0c769c:	e47419a4 */ 	swc1	$f20,0x19a4($v1)
/*  f0c76a0:	1000000a */ 	beqz	$zero,.L0f0c76cc
/*  f0c76a4:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c76a8:	44815000 */ 	mtc1	$at,$f10
.L0f0c76ac:
/*  f0c76ac:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c76b0:	460a903c */ 	c.lt.s	$f18,$f10
/*  f0c76b4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c76b8:	45020005 */ 	bc1fl	.L0f0c76d0
/*  f0c76bc:	8c6200bc */ 	lw	$v0,0xbc($v1)
/*  f0c76c0:	46120182 */ 	mul.s	$f6,$f0,$f18
/*  f0c76c4:	e46619a4 */ 	swc1	$f6,0x19a4($v1)
/*  f0c76c8:	8d030284 */ 	lw	$v1,0x284($t0)
.L0f0c76cc:
/*  f0c76cc:	8c6200bc */ 	lw	$v0,0xbc($v1)
.L0f0c76d0:
/*  f0c76d0:	c7a4008c */ 	lwc1	$f4,0x8c($sp)
/*  f0c76d4:	c7a60088 */ 	lwc1	$f6,0x88($sp)
/*  f0c76d8:	c4480008 */ 	lwc1	$f8,0x8($v0)
/*  f0c76dc:	c44a0010 */ 	lwc1	$f10,0x10($v0)
/*  f0c76e0:	46044001 */ 	sub.s	$f0,$f8,$f4
/*  f0c76e4:	c7a800d4 */ 	lwc1	$f8,0xd4($sp)
/*  f0c76e8:	46065081 */ 	sub.s	$f2,$f10,$f6
/*  f0c76ec:	46084102 */ 	mul.s	$f4,$f8,$f8
/*  f0c76f0:	c7aa00cc */ 	lwc1	$f10,0xcc($sp)
/*  f0c76f4:	460a5182 */ 	mul.s	$f6,$f10,$f10
/*  f0c76f8:	46062380 */ 	add.s	$f14,$f4,$f6
/*  f0c76fc:	46147032 */ 	c.eq.s	$f14,$f20
/*  f0c7700:	46007306 */ 	mov.s	$f12,$f14
/*  f0c7704:	45010006 */ 	bc1t	.L0f0c7720
/*  f0c7708:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c770c:	46000202 */ 	mul.s	$f8,$f0,$f0
/*  f0c7710:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7714:	46021282 */ 	mul.s	$f10,$f2,$f2
/*  f0c7718:	460a4100 */ 	add.s	$f4,$f8,$f10
/*  f0c771c:	460e2303 */ 	div.s	$f12,$f4,$f14
.L0f0c7720:
/*  f0c7720:	0c012974 */ 	jal	sqrtf
/*  f0c7724:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7728:	c7a800b4 */ 	lwc1	$f8,0xb4($sp)
/*  f0c772c:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c7730:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c7734:	46080282 */ 	mul.s	$f10,$f0,$f8
/*  f0c7738:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c773c:	c46600a4 */ 	lwc1	$f6,0xa4($v1)
/*  f0c7740:	460a3100 */ 	add.s	$f4,$f6,$f10
/*  f0c7744:	e46400a4 */ 	swc1	$f4,0xa4($v1)
/*  f0c7748:	c7a600b0 */ 	lwc1	$f6,0xb0($sp)
/*  f0c774c:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c7750:	46060282 */ 	mul.s	$f10,$f0,$f6
/*  f0c7754:	c46800a8 */ 	lwc1	$f8,0xa8($v1)
/*  f0c7758:	460a4100 */ 	add.s	$f4,$f8,$f10
/*  f0c775c:	e46400a8 */ 	swc1	$f4,0xa8($v1)
.L0f0c7760:
/*  f0c7760:	8d030284 */ 	lw	$v1,0x284($t0)
/*  f0c7764:	3c017f1b */ 	lui	$at,%hi(var7f1ad84c)
/*  f0c7768:	c42ad84c */ 	lwc1	$f10,%lo(var7f1ad84c)($at)
/*  f0c776c:	c4660148 */ 	lwc1	$f6,0x148($v1)
/*  f0c7770:	3c0140a0 */ 	lui	$at,0x40a0
/*  f0c7774:	e7a60044 */ 	swc1	$f6,0x44($sp)
/*  f0c7778:	c468015c */ 	lwc1	$f8,0x15c($v1)
/*  f0c777c:	c46600b8 */ 	lwc1	$f6,0xb8($v1)
/*  f0c7780:	460a4103 */ 	div.s	$f4,$f8,$f10
/*  f0c7784:	44814000 */ 	mtc1	$at,$f8
/*  f0c7788:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c778c:	46083283 */ 	div.s	$f10,$f6,$f8
/*  f0c7790:	c46600cc */ 	lwc1	$f6,0xcc($v1)
/*  f0c7794:	e7a6003c */ 	swc1	$f6,0x3c($sp)
/*  f0c7798:	460a2080 */ 	add.s	$f2,$f4,$f10
/*  f0c779c:	0fc4505b */ 	jal	func0f11416c
/*  f0c77a0:	e7a20040 */ 	swc1	$f2,0x40($sp)
/*  f0c77a4:	3c013f80 */ 	lui	$at,0x3f80
/*  f0c77a8:	44817000 */ 	mtc1	$at,$f14
/*  f0c77ac:	c7a20040 */ 	lwc1	$f2,0x40($sp)
/*  f0c77b0:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c77b4:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c77b8:	4602703c */ 	c.lt.s	$f14,$f2
/*  f0c77bc:	46000306 */ 	mov.s	$f12,$f0
/*  f0c77c0:	3c01bf80 */ 	lui	$at,0xbf80
/*  f0c77c4:	8fa70044 */ 	lw	$a3,0x44($sp)
/*  f0c77c8:	45020004 */ 	bc1fl	.L0f0c77dc
/*  f0c77cc:	44817000 */ 	mtc1	$at,$f14
/*  f0c77d0:	10000008 */ 	beqz	$zero,.L0f0c77f4
/*  f0c77d4:	46007086 */ 	mov.s	$f2,$f14
/*  f0c77d8:	44817000 */ 	mtc1	$at,$f14
.L0f0c77dc:
/*  f0c77dc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c77e0:	460e103c */ 	c.lt.s	$f2,$f14
/*  f0c77e4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c77e8:	45020003 */ 	bc1fl	.L0f0c77f8
/*  f0c77ec:	8d0b0284 */ 	lw	$t3,0x284($t0)
/*  f0c77f0:	46007086 */ 	mov.s	$f2,$f14
.L0f0c77f4:
/*  f0c77f4:	8d0b0284 */ 	lw	$t3,0x284($t0)
.L0f0c77f8:
/*  f0c77f8:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0c77fc:	44061000 */ 	mfc1	$a2,$f2
/*  f0c7800:	8d6c03ac */ 	lw	$t4,0x3ac($t3)
/*  f0c7804:	c7ae003c */ 	lwc1	$f14,0x3c($sp)
/*  f0c7808:	15810004 */ 	bne	$t4,$at,.L0f0c781c
/*  f0c780c:	3c017f1b */ 	lui	$at,%hi(var7f1ad850)
/*  f0c7810:	c428d850 */ 	lwc1	$f8,%lo(var7f1ad850)($at)
/*  f0c7814:	46080302 */ 	mul.s	$f12,$f0,$f8
/*  f0c7818:	00000000 */ 	sll	$zero,$zero,0x0
.L0f0c781c:
/*  f0c781c:	0fc27637 */ 	jal	func0f09d8dc
/*  f0c7820:	e7b40010 */ 	swc1	$f20,0x10($sp)
/*  f0c7824:	3c08800a */ 	lui	$t0,%hi(g_Vars)
/*  f0c7828:	25089fc0 */ 	addiu	$t0,$t0,%lo(g_Vars)
/*  f0c782c:	8d0d0284 */ 	lw	$t5,0x284($t0)
/*  f0c7830:	3c017f1b */ 	lui	$at,%hi(var7f1ad854)
/*  f0c7834:	c42ad854 */ 	lwc1	$f10,%lo(var7f1ad854)($at)
/*  f0c7838:	c5a40158 */ 	lwc1	$f4,0x158($t5)
/*  f0c783c:	460a2302 */ 	mul.s	$f12,$f4,$f10
/*  f0c7840:	0fc288a4 */ 	jal	func0f0a2290
/*  f0c7844:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0c7848:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f0c784c:	d7b40018 */ 	ldc1	$f20,0x18($sp)
/*  f0c7850:	27bd00e8 */ 	addiu	$sp,$sp,0xe8
/*  f0c7854:	03e00008 */ 	jr	$ra
/*  f0c7858:	00000000 */ 	sll	$zero,$zero,0x0
);

void func0f0c785c(void)
{
	s32 i;
	struct coord sStack16;

	currentPlayerUpdatePrevPosWalk();
	func0f0c6318();
	func0f0cbf50();
	func0f0c69b8();
	currentPlayerUpdateVerticalMovement();

	for (i = 0; g_Vars.currentplayer->prop->rooms[i] != -1; i++) {
		if (g_Vars.currentplayer->floorroom == g_Vars.currentplayer->prop->rooms[i]) {
			func0f065c44(g_Vars.currentplayer->prop);
			g_Vars.currentplayer->prop->rooms[0] = g_Vars.currentplayer->floorroom;
			g_Vars.currentplayer->prop->rooms[1] = -1;
			break;
		}
	}

	func0f0cb8c4(g_Vars.currentplayer);
	objectiveCheckRoomEntered(g_Vars.currentplayer->prop->rooms[0]);

	if (g_Vars.currentplayer->walkinitmove) {
		sStack16.x = (g_Vars.currentplayer->walkinitstart.x - g_Vars.currentplayer->walkinitpos.x)
			* (1.0f - g_Vars.currentplayer->walkinitt2) + g_Vars.currentplayer->prop->pos.x;

		sStack16.y = (g_Vars.currentplayer->walkinitstart.y - g_Vars.currentplayer->prop->pos.y)
			* (1.0f - g_Vars.currentplayer->walkinitt2) + g_Vars.currentplayer->prop->pos.y;

		sStack16.z = (g_Vars.currentplayer->walkinitstart.z - g_Vars.currentplayer->walkinitpos.z)
			* (1.0f - g_Vars.currentplayer->walkinitt2) + g_Vars.currentplayer->prop->pos.z;

		func0f0cc19c(&sStack16);
	} else {
		func0f0cc19c(&g_Vars.currentplayer->prop->pos);
	}

	func0f0c1ff4();
	func0f08c190();
}
