#include <ultra64.h>
#include "constants.h"
#include "game/camdraw.h"
#include "game/cheats.h"
#include "game/data/data_000000.h"
#include "game/data/data_0083d0.h"
#include "game/data/data_00e460.h"
#include "game/data/data_0160b0.h"
#include "game/data/data_01a3a0.h"
#include "game/data/data_020df0.h"
#include "game/game_0b63b0.h"
#include "game/game_0d4690.h"
#include "game/game_10ccd0.h"
#include "game/gamefile.h"
#include "game/game_157db0.h"
#include "game/game_19aa80.h"
#include "game/game_19c990.h"
#include "game/mplayer.h"
#include "game/pak/pak.h"
#include "game/pdoptions.h"
#include "game/utils.h"
#include "gvars/gvars.h"
#include "lib/lib_0bfb0.h"
#include "lib/lib_0e9d0.h"
#include "lib/lib_126b0.h"
#include "lib/lib_13130.h"
#include "lib/lib_13900.h"
#include "lib/lib_4b170.h"
#include "types.h"

const char var7f1b39d0[] = "Rebuilding pakWad %d:\n";

const u32 var7f1b39e8[] = {0x00000080};
const u32 var7f1b39ec[] = {0x00000040};
const u32 var7f1b39f0[] = {0x00000020};
const u32 var7f1b39f4[] = {0x00000008};
const u32 var7f1b39f8[] = {0x04000102};
const u32 var7f1b39fc[] = {0x03000000};
const u32 var7f1b3a00[] = {0x01020304};
const u32 var7f1b3a04[] = {0x00000000};

const char var7f1b3a08[] = "tc != NULL";
const char var7f1b3a14[] = "gamefile.c";

u32 *savefileGetFlags(void)
{
	return &g_SoloSaveFile.flags;
}

void savefileSetFlag(u32 value)
{
	func0f11e530(value, &g_SoloSaveFile.flags, true);
}

void savefileUnsetFlag(u32 value)
{
	func0f11e530(value, &g_SoloSaveFile.flags, false);
}

u32 savefileHasFlag(u32 value)
{
	return func0f11e584(value, &g_SoloSaveFile.flags);
}

GLOBAL_ASM(
glabel func0f10f1b0
/*  f10f1b0:	27bdffd8 */ 	addiu	$sp,$sp,-40
/*  f10f1b4:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f10f1b8:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f10f1bc:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f10f1c0:	3c11800a */ 	lui	$s1,%hi(g_SoloSaveFile+0x14)
/*  f10f1c4:	afbf0024 */ 	sw	$ra,0x24($sp)
/*  f10f1c8:	26312214 */ 	addiu	$s1,$s1,%lo(g_SoloSaveFile+0x14)
/*  f10f1cc:	24100023 */ 	addiu	$s0,$zero,0x23
/*  f10f1d0:	2412004f */ 	addiu	$s2,$zero,0x4f
/*  f10f1d4:	02002025 */ 	or	$a0,$s0,$zero
.L0f10f1d8:
/*  f10f1d8:	0fc47961 */ 	jal	func0f11e584
/*  f10f1dc:	02202825 */ 	or	$a1,$s1,$zero
/*  f10f1e0:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f10f1e4:	5612fffc */ 	bnel	$s0,$s2,.L0f10f1d8
/*  f10f1e8:	02002025 */ 	or	$a0,$s0,$zero
/*  f10f1ec:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f10f1f0:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f10f1f4:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f10f1f8:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f10f1fc:	03e00008 */ 	jr	$ra
/*  f10f200:	27bd0028 */ 	addiu	$sp,$sp,0x28
);

GLOBAL_ASM(
glabel func0f10f204
/*  f10f204:	3c03800a */ 	lui	$v1,%hi(g_Vars)
/*  f10f208:	24639fc0 */ 	addiu	$v1,$v1,%lo(g_Vars)
/*  f10f20c:	8c620298 */ 	lw	$v0,0x298($v1)
/*  f10f210:	27bdffd8 */ 	addiu	$sp,$sp,-40
/*  f10f214:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f10f218:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f10f21c:	04410005 */ 	bgez	$v0,.L0f10f234
/*  f10f220:	00803025 */ 	or	$a2,$a0,$zero
/*  f10f224:	8c6e029c */ 	lw	$t6,0x29c($v1)
/*  f10f228:	240f0004 */ 	addiu	$t7,$zero,0x4
/*  f10f22c:	05c20004 */ 	bltzl	$t6,.L0f10f240
/*  f10f230:	afaf0024 */ 	sw	$t7,0x24($sp)
.L0f10f234:
/*  f10f234:	10000002 */ 	beqz	$zero,.L0f10f240
/*  f10f238:	afa00024 */ 	sw	$zero,0x24($sp)
/*  f10f23c:	afaf0024 */ 	sw	$t7,0x24($sp)
.L0f10f240:
/*  f10f240:	04410004 */ 	bgez	$v0,.L0f10f254
/*  f10f244:	00002025 */ 	or	$a0,$zero,$zero
/*  f10f248:	8c78029c */ 	lw	$t8,0x29c($v1)
/*  f10f24c:	24080005 */ 	addiu	$t0,$zero,0x5
/*  f10f250:	07000003 */ 	bltz	$t8,.L0f10f260
.L0f10f254:
/*  f10f254:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f10f258:	10000002 */ 	beqz	$zero,.L0f10f264
/*  f10f25c:	afb90020 */ 	sw	$t9,0x20($sp)
.L0f10f260:
/*  f10f260:	afa80020 */ 	sw	$t0,0x20($sp)
.L0f10f264:
/*  f10f264:	24d00014 */ 	addiu	$s0,$a2,0x14
/*  f10f268:	0fc47961 */ 	jal	func0f11e584
/*  f10f26c:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f270:	8fa40024 */ 	lw	$a0,0x24($sp)
/*  f10f274:	0fc54a52 */ 	jal	optionsSetForwardPitch
/*  f10f278:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f27c:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f10f280:	0fc47961 */ 	jal	func0f11e584
/*  f10f284:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f288:	8fa40024 */ 	lw	$a0,0x24($sp)
/*  f10f28c:	0fc54a68 */ 	jal	optionsSetAutoAim
/*  f10f290:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f294:	24040002 */ 	addiu	$a0,$zero,0x2
/*  f10f298:	0fc47961 */ 	jal	func0f11e584
/*  f10f29c:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f2a0:	8fa40024 */ 	lw	$a0,0x24($sp)
/*  f10f2a4:	0fc54a94 */ 	jal	optionsSetAimControl
/*  f10f2a8:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f2ac:	24040003 */ 	addiu	$a0,$zero,0x3
/*  f10f2b0:	0fc47961 */ 	jal	func0f11e584
/*  f10f2b4:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f2b8:	8fa40024 */ 	lw	$a0,0x24($sp)
/*  f10f2bc:	0fc54aaa */ 	jal	optionsSetSightOnScreen
/*  f10f2c0:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f2c4:	24040004 */ 	addiu	$a0,$zero,0x4
/*  f10f2c8:	0fc47961 */ 	jal	func0f11e584
/*  f10f2cc:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f2d0:	8fa40024 */ 	lw	$a0,0x24($sp)
/*  f10f2d4:	0fc54a7e */ 	jal	optionsSetLookAhead
/*  f10f2d8:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f2dc:	24040005 */ 	addiu	$a0,$zero,0x5
/*  f10f2e0:	0fc47961 */ 	jal	func0f11e584
/*  f10f2e4:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f2e8:	8fa40024 */ 	lw	$a0,0x24($sp)
/*  f10f2ec:	0fc54ac0 */ 	jal	optionsSetAmmoOnScreen
/*  f10f2f0:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f2f4:	24040009 */ 	addiu	$a0,$zero,0x9
/*  f10f2f8:	0fc47961 */ 	jal	func0f11e584
/*  f10f2fc:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f300:	8fa40024 */ 	lw	$a0,0x24($sp)
/*  f10f304:	0fc54b4a */ 	jal	optionsSetHeadRoll
/*  f10f308:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f30c:	2404000a */ 	addiu	$a0,$zero,0xa
/*  f10f310:	0fc47961 */ 	jal	func0f11e584
/*  f10f314:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f318:	8fa40024 */ 	lw	$a0,0x24($sp)
/*  f10f31c:	0fc54ad6 */ 	jal	optionsSetShowGunFunction
/*  f10f320:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f324:	24040015 */ 	addiu	$a0,$zero,0x15
/*  f10f328:	0fc47961 */ 	jal	func0f11e584
/*  f10f32c:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f330:	8fa40024 */ 	lw	$a0,0x24($sp)
/*  f10f334:	0fc54aec */ 	jal	optionsSetAlwaysShowTarget
/*  f10f338:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f33c:	24040017 */ 	addiu	$a0,$zero,0x17
/*  f10f340:	0fc47961 */ 	jal	func0f11e584
/*  f10f344:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f348:	8fa40024 */ 	lw	$a0,0x24($sp)
/*  f10f34c:	0fc54b02 */ 	jal	optionsSetShowZoomRange
/*  f10f350:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f354:	2404001a */ 	addiu	$a0,$zero,0x1a
/*  f10f358:	0fc47961 */ 	jal	func0f11e584
/*  f10f35c:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f360:	8fa40024 */ 	lw	$a0,0x24($sp)
/*  f10f364:	0fc54b2e */ 	jal	optionsSetShowMissionTime
/*  f10f368:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f36c:	24040020 */ 	addiu	$a0,$zero,0x20
/*  f10f370:	0fc47961 */ 	jal	func0f11e584
/*  f10f374:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f378:	8fa40024 */ 	lw	$a0,0x24($sp)
/*  f10f37c:	0fc54b18 */ 	jal	optionsSetPaintball
/*  f10f380:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f384:	2404000c */ 	addiu	$a0,$zero,0xc
/*  f10f388:	0fc47961 */ 	jal	func0f11e584
/*  f10f38c:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f390:	8fa40020 */ 	lw	$a0,0x20($sp)
/*  f10f394:	0fc54a52 */ 	jal	optionsSetForwardPitch
/*  f10f398:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f39c:	2404000d */ 	addiu	$a0,$zero,0xd
/*  f10f3a0:	0fc47961 */ 	jal	func0f11e584
/*  f10f3a4:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f3a8:	8fa40020 */ 	lw	$a0,0x20($sp)
/*  f10f3ac:	0fc54a68 */ 	jal	optionsSetAutoAim
/*  f10f3b0:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f3b4:	2404000e */ 	addiu	$a0,$zero,0xe
/*  f10f3b8:	0fc47961 */ 	jal	func0f11e584
/*  f10f3bc:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f3c0:	8fa40020 */ 	lw	$a0,0x20($sp)
/*  f10f3c4:	0fc54a94 */ 	jal	optionsSetAimControl
/*  f10f3c8:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f3cc:	2404000f */ 	addiu	$a0,$zero,0xf
/*  f10f3d0:	0fc47961 */ 	jal	func0f11e584
/*  f10f3d4:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f3d8:	8fa40020 */ 	lw	$a0,0x20($sp)
/*  f10f3dc:	0fc54aaa */ 	jal	optionsSetSightOnScreen
/*  f10f3e0:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f3e4:	24040010 */ 	addiu	$a0,$zero,0x10
/*  f10f3e8:	0fc47961 */ 	jal	func0f11e584
/*  f10f3ec:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f3f0:	8fa40020 */ 	lw	$a0,0x20($sp)
/*  f10f3f4:	0fc54a7e */ 	jal	optionsSetLookAhead
/*  f10f3f8:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f3fc:	24040011 */ 	addiu	$a0,$zero,0x11
/*  f10f400:	0fc47961 */ 	jal	func0f11e584
/*  f10f404:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f408:	8fa40020 */ 	lw	$a0,0x20($sp)
/*  f10f40c:	0fc54ac0 */ 	jal	optionsSetAmmoOnScreen
/*  f10f410:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f414:	24040012 */ 	addiu	$a0,$zero,0x12
/*  f10f418:	0fc47961 */ 	jal	func0f11e584
/*  f10f41c:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f420:	8fa40020 */ 	lw	$a0,0x20($sp)
/*  f10f424:	0fc54b4a */ 	jal	optionsSetHeadRoll
/*  f10f428:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f42c:	24040013 */ 	addiu	$a0,$zero,0x13
/*  f10f430:	0fc47961 */ 	jal	func0f11e584
/*  f10f434:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f438:	8fa40020 */ 	lw	$a0,0x20($sp)
/*  f10f43c:	0fc54ad6 */ 	jal	optionsSetShowGunFunction
/*  f10f440:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f444:	24040016 */ 	addiu	$a0,$zero,0x16
/*  f10f448:	0fc47961 */ 	jal	func0f11e584
/*  f10f44c:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f450:	8fa40020 */ 	lw	$a0,0x20($sp)
/*  f10f454:	0fc54aec */ 	jal	optionsSetAlwaysShowTarget
/*  f10f458:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f45c:	24040018 */ 	addiu	$a0,$zero,0x18
/*  f10f460:	0fc47961 */ 	jal	func0f11e584
/*  f10f464:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f468:	8fa40020 */ 	lw	$a0,0x20($sp)
/*  f10f46c:	0fc54b02 */ 	jal	optionsSetShowZoomRange
/*  f10f470:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f474:	2404001b */ 	addiu	$a0,$zero,0x1b
/*  f10f478:	0fc47961 */ 	jal	func0f11e584
/*  f10f47c:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f480:	8fa40020 */ 	lw	$a0,0x20($sp)
/*  f10f484:	0fc54b2e */ 	jal	optionsSetShowMissionTime
/*  f10f488:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f48c:	24040021 */ 	addiu	$a0,$zero,0x21
/*  f10f490:	0fc47961 */ 	jal	func0f11e584
/*  f10f494:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f498:	8fa40020 */ 	lw	$a0,0x20($sp)
/*  f10f49c:	0fc54b18 */ 	jal	optionsSetPaintball
/*  f10f4a0:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f4a4:	2404000b */ 	addiu	$a0,$zero,0xb
/*  f10f4a8:	0fc47961 */ 	jal	func0f11e584
/*  f10f4ac:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f4b0:	0fc54b44 */ 	jal	optionsSetInGameSubtitles
/*  f10f4b4:	00402025 */ 	or	$a0,$v0,$zero
/*  f10f4b8:	24040014 */ 	addiu	$a0,$zero,0x14
/*  f10f4bc:	0fc47961 */ 	jal	func0f11e584
/*  f10f4c0:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f4c4:	0fc54b47 */ 	jal	optionsSetCutsceneSubtitles
/*  f10f4c8:	00402025 */ 	or	$a0,$v0,$zero
/*  f10f4cc:	24040021 */ 	addiu	$a0,$zero,0x21
/*  f10f4d0:	0fc47961 */ 	jal	func0f11e584
/*  f10f4d4:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f4d8:	8fa40020 */ 	lw	$a0,0x20($sp)
/*  f10f4dc:	0fc54b18 */ 	jal	optionsSetPaintball
/*  f10f4e0:	00402825 */ 	or	$a1,$v0,$zero
/*  f10f4e4:	24040040 */ 	addiu	$a0,$zero,0x40
/*  f10f4e8:	0fc47961 */ 	jal	func0f11e584
/*  f10f4ec:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f4f0:	3c01800a */ 	lui	$at,%hi(g_Vars+0x4e3)
/*  f10f4f4:	a022a4a3 */ 	sb	$v0,%lo(g_Vars+0x4e3)($at)
/*  f10f4f8:	24040022 */ 	addiu	$a0,$zero,0x22
/*  f10f4fc:	0fc47961 */ 	jal	func0f11e584
/*  f10f500:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f504:	1040000d */ 	beqz	$v0,.L0f10f53c
/*  f10f508:	3c098009 */ 	lui	$t1,%hi(g_Is4Mb)
/*  f10f50c:	91290af0 */ 	lbu	$t1,%lo(g_Is4Mb)($t1)
/*  f10f510:	24010001 */ 	addiu	$at,$zero,0x1
/*  f10f514:	15210005 */ 	bne	$t1,$at,.L0f10f52c
/*  f10f518:	00000000 */ 	sll	$zero,$zero,0x0
/*  f10f51c:	0fc2f110 */ 	jal	optionsSetHiRes
/*  f10f520:	00002025 */ 	or	$a0,$zero,$zero
/*  f10f524:	10000007 */ 	beqz	$zero,.L0f10f544
/*  f10f528:	00000000 */ 	sll	$zero,$zero,0x0
.L0f10f52c:
/*  f10f52c:	0fc2f110 */ 	jal	optionsSetHiRes
/*  f10f530:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f10f534:	10000003 */ 	beqz	$zero,.L0f10f544
/*  f10f538:	00000000 */ 	sll	$zero,$zero,0x0
.L0f10f53c:
/*  f10f53c:	0fc2f110 */ 	jal	optionsSetHiRes
/*  f10f540:	00002025 */ 	or	$a0,$zero,$zero
.L0f10f544:
/*  f10f544:	3c0a8009 */ 	lui	$t2,%hi(g_Is4Mb)
/*  f10f548:	914a0af0 */ 	lbu	$t2,%lo(g_Is4Mb)($t2)
/*  f10f54c:	24010001 */ 	addiu	$at,$zero,0x1
/*  f10f550:	55410008 */ 	bnel	$t2,$at,.L0f10f574
/*  f10f554:	24040019 */ 	addiu	$a0,$zero,0x19
/*  f10f558:	0fc54bd0 */ 	jal	optionsSetScreenSplit
/*  f10f55c:	00002025 */ 	or	$a0,$zero,$zero
/*  f10f560:	0fc54bca */ 	jal	optionsSetScreenRatio
/*  f10f564:	00002025 */ 	or	$a0,$zero,$zero
/*  f10f568:	1000000c */ 	beqz	$zero,.L0f10f59c
/*  f10f56c:	24040008 */ 	addiu	$a0,$zero,0x8
/*  f10f570:	24040019 */ 	addiu	$a0,$zero,0x19
.L0f10f574:
/*  f10f574:	0fc47961 */ 	jal	func0f11e584
/*  f10f578:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f57c:	0fc54bd0 */ 	jal	optionsSetScreenSplit
/*  f10f580:	304400ff */ 	andi	$a0,$v0,0xff
/*  f10f584:	24040007 */ 	addiu	$a0,$zero,0x7
/*  f10f588:	0fc47961 */ 	jal	func0f11e584
/*  f10f58c:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f590:	0fc54bca */ 	jal	optionsSetScreenRatio
/*  f10f594:	00402025 */ 	or	$a0,$v0,$zero
/*  f10f598:	24040008 */ 	addiu	$a0,$zero,0x8
.L0f10f59c:
/*  f10f59c:	0fc47961 */ 	jal	func0f11e584
/*  f10f5a0:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f5a4:	10400005 */ 	beqz	$v0,.L0f10f5bc
/*  f10f5a8:	24040006 */ 	addiu	$a0,$zero,0x6
/*  f10f5ac:	0fc54bc4 */ 	jal	optionsSetScreenSize
/*  f10f5b0:	24040002 */ 	addiu	$a0,$zero,0x2
/*  f10f5b4:	1000000c */ 	beqz	$zero,.L0f10f5e8
/*  f10f5b8:	2404001f */ 	addiu	$a0,$zero,0x1f
.L0f10f5bc:
/*  f10f5bc:	0fc47961 */ 	jal	func0f11e584
/*  f10f5c0:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f5c4:	10400005 */ 	beqz	$v0,.L0f10f5dc
/*  f10f5c8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f10f5cc:	0fc54bc4 */ 	jal	optionsSetScreenSize
/*  f10f5d0:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f10f5d4:	10000004 */ 	beqz	$zero,.L0f10f5e8
/*  f10f5d8:	2404001f */ 	addiu	$a0,$zero,0x1f
.L0f10f5dc:
/*  f10f5dc:	0fc54bc4 */ 	jal	optionsSetScreenSize
/*  f10f5e0:	00002025 */ 	or	$a0,$zero,$zero
/*  f10f5e4:	2404001f */ 	addiu	$a0,$zero,0x1f
.L0f10f5e8:
/*  f10f5e8:	0fc47961 */ 	jal	func0f11e584
/*  f10f5ec:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f5f0:	10400005 */ 	beqz	$v0,.L0f10f608
/*  f10f5f4:	2404001c */ 	addiu	$a0,$zero,0x1c
/*  f10f5f8:	240b0001 */ 	addiu	$t3,$zero,0x1
/*  f10f5fc:	3c01800a */ 	lui	$at,%hi(g_Vars+0x450)
/*  f10f600:	10000003 */ 	beqz	$zero,.L0f10f610
/*  f10f604:	ac2ba410 */ 	sw	$t3,%lo(g_Vars+0x450)($at)
.L0f10f608:
/*  f10f608:	3c01800a */ 	lui	$at,%hi(g_Vars+0x450)
/*  f10f60c:	ac20a410 */ 	sw	$zero,%lo(g_Vars+0x450)($at)
.L0f10f610:
/*  f10f610:	0fc47961 */ 	jal	func0f11e584
/*  f10f614:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f618:	10400005 */ 	beqz	$v0,.L0f10f630
/*  f10f61c:	2404001d */ 	addiu	$a0,$zero,0x1d
/*  f10f620:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f10f624:	3c01800a */ 	lui	$at,%hi(g_Vars+0x448)
/*  f10f628:	10000003 */ 	beqz	$zero,.L0f10f638
/*  f10f62c:	ac2ca408 */ 	sw	$t4,%lo(g_Vars+0x448)($at)
.L0f10f630:
/*  f10f630:	3c01800a */ 	lui	$at,%hi(g_Vars+0x448)
/*  f10f634:	ac20a408 */ 	sw	$zero,%lo(g_Vars+0x448)($at)
.L0f10f638:
/*  f10f638:	0fc47961 */ 	jal	func0f11e584
/*  f10f63c:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f640:	10400005 */ 	beqz	$v0,.L0f10f658
/*  f10f644:	2404001e */ 	addiu	$a0,$zero,0x1e
/*  f10f648:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f10f64c:	3c01800a */ 	lui	$at,%hi(g_Vars+0x454)
/*  f10f650:	10000003 */ 	beqz	$zero,.L0f10f660
/*  f10f654:	ac2da414 */ 	sw	$t5,%lo(g_Vars+0x454)($at)
.L0f10f658:
/*  f10f658:	3c01800a */ 	lui	$at,%hi(g_Vars+0x454)
/*  f10f65c:	ac20a414 */ 	sw	$zero,%lo(g_Vars+0x454)($at)
.L0f10f660:
/*  f10f660:	0fc47961 */ 	jal	func0f11e584
/*  f10f664:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f668:	10400005 */ 	beqz	$v0,.L0f10f680
/*  f10f66c:	3c01800a */ 	lui	$at,%hi(g_Vars+0x44c)
/*  f10f670:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f10f674:	3c01800a */ 	lui	$at,%hi(g_Vars+0x44c)
/*  f10f678:	10000002 */ 	beqz	$zero,.L0f10f684
/*  f10f67c:	ac2ea40c */ 	sw	$t6,%lo(g_Vars+0x44c)($at)
.L0f10f680:
/*  f10f680:	ac20a40c */ 	sw	$zero,%lo(g_Vars+0x44c)($at)
.L0f10f684:
/*  f10f684:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f10f688:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f10f68c:	27bd0028 */ 	addiu	$sp,$sp,0x28
/*  f10f690:	03e00008 */ 	jr	$ra
/*  f10f694:	00000000 */ 	sll	$zero,$zero,0x0
);

GLOBAL_ASM(
glabel func0f10f698
/*  f10f698:	3c03800a */ 	lui	$v1,%hi(g_Vars)
/*  f10f69c:	24639fc0 */ 	addiu	$v1,$v1,%lo(g_Vars)
/*  f10f6a0:	27bdffd8 */ 	addiu	$sp,$sp,-40
/*  f10f6a4:	8c620298 */ 	lw	$v0,0x298($v1)
/*  f10f6a8:	afbf0024 */ 	sw	$ra,0x24($sp)
/*  f10f6ac:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f10f6b0:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f10f6b4:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f10f6b8:	04410005 */ 	bgez	$v0,.L0f10f6d0
/*  f10f6bc:	afa40028 */ 	sw	$a0,0x28($sp)
/*  f10f6c0:	8c6e029c */ 	lw	$t6,0x29c($v1)
/*  f10f6c4:	24110004 */ 	addiu	$s1,$zero,0x4
/*  f10f6c8:	05c00003 */ 	bltz	$t6,.L0f10f6d8
/*  f10f6cc:	00000000 */ 	sll	$zero,$zero,0x0
.L0f10f6d0:
/*  f10f6d0:	10000001 */ 	beqz	$zero,.L0f10f6d8
/*  f10f6d4:	00008825 */ 	or	$s1,$zero,$zero
.L0f10f6d8:
/*  f10f6d8:	04410005 */ 	bgez	$v0,.L0f10f6f0
/*  f10f6dc:	8fa40028 */ 	lw	$a0,0x28($sp)
/*  f10f6e0:	8c6f029c */ 	lw	$t7,0x29c($v1)
/*  f10f6e4:	24100005 */ 	addiu	$s0,$zero,0x5
/*  f10f6e8:	05e00003 */ 	bltz	$t7,.L0f10f6f8
/*  f10f6ec:	00000000 */ 	sll	$zero,$zero,0x0
.L0f10f6f0:
/*  f10f6f0:	10000001 */ 	beqz	$zero,.L0f10f6f8
/*  f10f6f4:	24100001 */ 	addiu	$s0,$zero,0x1
.L0f10f6f8:
/*  f10f6f8:	3c057f1b */ 	lui	$a1,%hi(var7f1b38e0)
/*  f10f6fc:	0c004c4c */ 	jal	strcpy
/*  f10f700:	24a538e0 */ 	addiu	$a1,$a1,%lo(var7f1b38e0)
/*  f10f704:	8fa20028 */ 	lw	$v0,0x28($sp)
/*  f10f708:	24045000 */ 	addiu	$a0,$zero,0x5000
/*  f10f70c:	9058000b */ 	lbu	$t8,0xb($v0)
/*  f10f710:	a040000c */ 	sb	$zero,0xc($v0)
/*  f10f714:	ac400010 */ 	sw	$zero,0x10($v0)
/*  f10f718:	3308ff07 */ 	andi	$t0,$t8,0xff07
/*  f10f71c:	310900f8 */ 	andi	$t1,$t0,0xf8
/*  f10f720:	a048000b */ 	sb	$t0,0xb($v0)
/*  f10f724:	0c003a87 */ 	jal	audioSetSfxVolume
/*  f10f728:	a049000b */ 	sb	$t1,0xb($v0)
/*  f10f72c:	0fc54bdc */ 	jal	optionsSetMusicVolume
/*  f10f730:	24045000 */ 	addiu	$a0,$zero,0x5000
/*  f10f734:	0c003ce3 */ 	jal	audioSetSoundMode
/*  f10f738:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f10f73c:	02202025 */ 	or	$a0,$s1,$zero
/*  f10f740:	0fc549cb */ 	jal	optionsSetControlMode
/*  f10f744:	00002825 */ 	or	$a1,$zero,$zero
/*  f10f748:	02002025 */ 	or	$a0,$s0,$zero
/*  f10f74c:	0fc549cb */ 	jal	optionsSetControlMode
/*  f10f750:	00002825 */ 	or	$a1,$zero,$zero
/*  f10f754:	8fb00028 */ 	lw	$s0,0x28($sp)
/*  f10f758:	26100014 */ 	addiu	$s0,$s0,0x14
/*  f10f75c:	0fc4796f */ 	jal	func0f11e5bc
/*  f10f760:	02002025 */ 	or	$a0,$s0,$zero
/*  f10f764:	00002025 */ 	or	$a0,$zero,$zero
/*  f10f768:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f76c:	0fc4794c */ 	jal	func0f11e530
/*  f10f770:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f774:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f10f778:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f77c:	0fc4794c */ 	jal	func0f11e530
/*  f10f780:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f784:	24040002 */ 	addiu	$a0,$zero,0x2
/*  f10f788:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f78c:	0fc4794c */ 	jal	func0f11e530
/*  f10f790:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f794:	24040003 */ 	addiu	$a0,$zero,0x3
/*  f10f798:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f79c:	0fc4794c */ 	jal	func0f11e530
/*  f10f7a0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f7a4:	24040004 */ 	addiu	$a0,$zero,0x4
/*  f10f7a8:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f7ac:	0fc4794c */ 	jal	func0f11e530
/*  f10f7b0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f7b4:	24040005 */ 	addiu	$a0,$zero,0x5
/*  f10f7b8:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f7bc:	0fc4794c */ 	jal	func0f11e530
/*  f10f7c0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f7c4:	24040009 */ 	addiu	$a0,$zero,0x9
/*  f10f7c8:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f7cc:	0fc4794c */ 	jal	func0f11e530
/*  f10f7d0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f7d4:	2404000a */ 	addiu	$a0,$zero,0xa
/*  f10f7d8:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f7dc:	0fc4794c */ 	jal	func0f11e530
/*  f10f7e0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f7e4:	2404000b */ 	addiu	$a0,$zero,0xb
/*  f10f7e8:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f7ec:	0fc4794c */ 	jal	func0f11e530
/*  f10f7f0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f7f4:	24040015 */ 	addiu	$a0,$zero,0x15
/*  f10f7f8:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f7fc:	0fc4794c */ 	jal	func0f11e530
/*  f10f800:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f804:	24040017 */ 	addiu	$a0,$zero,0x17
/*  f10f808:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f80c:	0fc4794c */ 	jal	func0f11e530
/*  f10f810:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f814:	2404001a */ 	addiu	$a0,$zero,0x1a
/*  f10f818:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f81c:	0fc4794c */ 	jal	func0f11e530
/*  f10f820:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f824:	24040020 */ 	addiu	$a0,$zero,0x20
/*  f10f828:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f82c:	0fc4794c */ 	jal	func0f11e530
/*  f10f830:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f834:	2404000c */ 	addiu	$a0,$zero,0xc
/*  f10f838:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f83c:	0fc4794c */ 	jal	func0f11e530
/*  f10f840:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f844:	2404000d */ 	addiu	$a0,$zero,0xd
/*  f10f848:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f84c:	0fc4794c */ 	jal	func0f11e530
/*  f10f850:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f854:	2404000e */ 	addiu	$a0,$zero,0xe
/*  f10f858:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f85c:	0fc4794c */ 	jal	func0f11e530
/*  f10f860:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f864:	2404000f */ 	addiu	$a0,$zero,0xf
/*  f10f868:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f86c:	0fc4794c */ 	jal	func0f11e530
/*  f10f870:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f874:	24040010 */ 	addiu	$a0,$zero,0x10
/*  f10f878:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f87c:	0fc4794c */ 	jal	func0f11e530
/*  f10f880:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f884:	24040011 */ 	addiu	$a0,$zero,0x11
/*  f10f888:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f88c:	0fc4794c */ 	jal	func0f11e530
/*  f10f890:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f894:	24040012 */ 	addiu	$a0,$zero,0x12
/*  f10f898:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f89c:	0fc4794c */ 	jal	func0f11e530
/*  f10f8a0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f8a4:	24040013 */ 	addiu	$a0,$zero,0x13
/*  f10f8a8:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f8ac:	0fc4794c */ 	jal	func0f11e530
/*  f10f8b0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f8b4:	24040014 */ 	addiu	$a0,$zero,0x14
/*  f10f8b8:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f8bc:	0fc4794c */ 	jal	func0f11e530
/*  f10f8c0:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f8c4:	24040016 */ 	addiu	$a0,$zero,0x16
/*  f10f8c8:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f8cc:	0fc4794c */ 	jal	func0f11e530
/*  f10f8d0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f8d4:	24040018 */ 	addiu	$a0,$zero,0x18
/*  f10f8d8:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f8dc:	0fc4794c */ 	jal	func0f11e530
/*  f10f8e0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f8e4:	2404001b */ 	addiu	$a0,$zero,0x1b
/*  f10f8e8:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f8ec:	0fc4794c */ 	jal	func0f11e530
/*  f10f8f0:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f8f4:	24040021 */ 	addiu	$a0,$zero,0x21
/*  f10f8f8:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f8fc:	0fc4794c */ 	jal	func0f11e530
/*  f10f900:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f904:	24040019 */ 	addiu	$a0,$zero,0x19
/*  f10f908:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f90c:	0fc4794c */ 	jal	func0f11e530
/*  f10f910:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f914:	24040007 */ 	addiu	$a0,$zero,0x7
/*  f10f918:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f91c:	0fc4794c */ 	jal	func0f11e530
/*  f10f920:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f924:	24040008 */ 	addiu	$a0,$zero,0x8
/*  f10f928:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f92c:	0fc4794c */ 	jal	func0f11e530
/*  f10f930:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f934:	24040006 */ 	addiu	$a0,$zero,0x6
/*  f10f938:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f93c:	0fc4794c */ 	jal	func0f11e530
/*  f10f940:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f944:	24040022 */ 	addiu	$a0,$zero,0x22
/*  f10f948:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f94c:	0fc4794c */ 	jal	func0f11e530
/*  f10f950:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f954:	24040040 */ 	addiu	$a0,$zero,0x40
/*  f10f958:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f95c:	0fc4794c */ 	jal	func0f11e530
/*  f10f960:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f964:	24040041 */ 	addiu	$a0,$zero,0x41
/*  f10f968:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f96c:	0fc4794c */ 	jal	func0f11e530
/*  f10f970:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f974:	24040042 */ 	addiu	$a0,$zero,0x42
/*  f10f978:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f97c:	0fc4794c */ 	jal	func0f11e530
/*  f10f980:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f984:	24040043 */ 	addiu	$a0,$zero,0x43
/*  f10f988:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f98c:	0fc4794c */ 	jal	func0f11e530
/*  f10f990:	00003025 */ 	or	$a2,$zero,$zero
/*  f10f994:	2404001c */ 	addiu	$a0,$zero,0x1c
/*  f10f998:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f99c:	0fc4794c */ 	jal	func0f11e530
/*  f10f9a0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f9a4:	2404001d */ 	addiu	$a0,$zero,0x1d
/*  f10f9a8:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f9ac:	0fc4794c */ 	jal	func0f11e530
/*  f10f9b0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f9b4:	2404001e */ 	addiu	$a0,$zero,0x1e
/*  f10f9b8:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f9bc:	0fc4794c */ 	jal	func0f11e530
/*  f10f9c0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f9c4:	2404001f */ 	addiu	$a0,$zero,0x1f
/*  f10f9c8:	02002825 */ 	or	$a1,$s0,$zero
/*  f10f9cc:	0fc4794c */ 	jal	func0f11e530
/*  f10f9d0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f10f9d4:	8fa40028 */ 	lw	$a0,0x28($sp)
/*  f10f9d8:	00009025 */ 	or	$s2,$zero,$zero
/*  f10f9dc:	24030003 */ 	addiu	$v1,$zero,0x3
/*  f10f9e0:	a480001e */ 	sh	$zero,0x1e($a0)
.L0f10f9e4:
/*  f10f9e4:	00008025 */ 	or	$s0,$zero,$zero
/*  f10f9e8:	00801025 */ 	or	$v0,$a0,$zero
.L0f10f9ec:
/*  f10f9ec:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f10f9f0:	24420002 */ 	addiu	$v0,$v0,0x2
/*  f10f9f4:	1603fffd */ 	bne	$s0,$v1,.L0f10f9ec
/*  f10f9f8:	a440001e */ 	sh	$zero,0x1e($v0)
/*  f10f9fc:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f10fa00:	2a410015 */ 	slti	$at,$s2,0x15
/*  f10fa04:	1420fff7 */ 	bnez	$at,.L0f10f9e4
/*  f10fa08:	24840006 */ 	addiu	$a0,$a0,0x6
/*  f10fa0c:	00009025 */ 	or	$s2,$zero,$zero
/*  f10fa10:	24110005 */ 	addiu	$s1,$zero,0x5
/*  f10fa14:	24100001 */ 	addiu	$s0,$zero,0x1
.L0f10fa18:
/*  f10fa18:	02402025 */ 	or	$a0,$s2,$zero
.L0f10fa1c:
/*  f10fa1c:	02002825 */ 	or	$a1,$s0,$zero
/*  f10fa20:	0fc67103 */ 	jal	mpSetChallengeCompletedByAnyChrWithNumPlayers
/*  f10fa24:	00003025 */ 	or	$a2,$zero,$zero
/*  f10fa28:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f10fa2c:	5611fffb */ 	bnel	$s0,$s1,.L0f10fa1c
/*  f10fa30:	02402025 */ 	or	$a0,$s2,$zero
/*  f10fa34:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f10fa38:	2a41001e */ 	slti	$at,$s2,0x1e
/*  f10fa3c:	5420fff6 */ 	bnezl	$at,.L0f10fa18
/*  f10fa40:	24100001 */ 	addiu	$s0,$zero,0x1
/*  f10fa44:	0fc66bf7 */ 	jal	func0f19afdc
/*  f10fa48:	00000000 */ 	sll	$zero,$zero,0x0
/*  f10fa4c:	3c02800a */ 	lui	$v0,%hi(g_SoloSaveFile)
/*  f10fa50:	3c03800a */ 	lui	$v1,%hi(g_SoloSaveFile+0xc)
/*  f10fa54:	2463220c */ 	addiu	$v1,$v1,%lo(g_SoloSaveFile+0xc)
/*  f10fa58:	24422200 */ 	addiu	$v0,$v0,%lo(g_SoloSaveFile)
.L0f10fa5c:
/*  f10fa5c:	24420004 */ 	addiu	$v0,$v0,0x4
/*  f10fa60:	0043082b */ 	sltu	$at,$v0,$v1
/*  f10fa64:	1420fffd */ 	bnez	$at,.L0f10fa5c
/*  f10fa68:	ac40009c */ 	sw	$zero,0x9c($v0)
/*  f10fa6c:	3c02800a */ 	lui	$v0,%hi(g_SoloSaveFile)
/*  f10fa70:	3c03800a */ 	lui	$v1,%hi(g_SoloSaveFile+0x9)
/*  f10fa74:	24632209 */ 	addiu	$v1,$v1,%lo(g_SoloSaveFile+0x9)
/*  f10fa78:	24422200 */ 	addiu	$v0,$v0,%lo(g_SoloSaveFile)
.L0f10fa7c:
/*  f10fa7c:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f10fa80:	0043082b */ 	sltu	$at,$v0,$v1
/*  f10fa84:	1420fffd */ 	bnez	$at,.L0f10fa7c
/*  f10fa88:	a04000ab */ 	sb	$zero,0xab($v0)
/*  f10fa8c:	3c02800a */ 	lui	$v0,%hi(g_SoloSaveFile)
/*  f10fa90:	3c03800a */ 	lui	$v1,%hi(g_SoloSaveFile+0x6)
/*  f10fa94:	24632206 */ 	addiu	$v1,$v1,%lo(g_SoloSaveFile+0x6)
/*  f10fa98:	24422200 */ 	addiu	$v0,$v0,%lo(g_SoloSaveFile)
.L0f10fa9c:
/*  f10fa9c:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f10faa0:	1443fffe */ 	bne	$v0,$v1,.L0f10fa9c
/*  f10faa4:	a04000b4 */ 	sb	$zero,0xb4($v0)
/*  f10faa8:	0fc43c81 */ 	jal	func0f10f204
/*  f10faac:	8fa40028 */ 	lw	$a0,0x28($sp)
/*  f10fab0:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f10fab4:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f10fab8:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f10fabc:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f10fac0:	03e00008 */ 	jr	$ra
/*  f10fac4:	27bd0028 */ 	addiu	$sp,$sp,0x28
);

GLOBAL_ASM(
glabel func0f10fac8
/*  f10fac8:	27bdfec0 */ 	addiu	$sp,$sp,-320
/*  f10facc:	3c03800a */ 	lui	$v1,%hi(g_Vars)
/*  f10fad0:	24639fc0 */ 	addiu	$v1,$v1,%lo(g_Vars)
/*  f10fad4:	8c620298 */ 	lw	$v0,0x298($v1)
/*  f10fad8:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f10fadc:	00808025 */ 	or	$s0,$a0,$zero
/*  f10fae0:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f10fae4:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f10fae8:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f10faec:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f10faf0:	04410005 */ 	bgez	$v0,.L0f10fb08
/*  f10faf4:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f10faf8:	8c6e029c */ 	lw	$t6,0x29c($v1)
/*  f10fafc:	24110004 */ 	addiu	$s1,$zero,0x4
/*  f10fb00:	05c00003 */ 	bltz	$t6,.L0f10fb10
/*  f10fb04:	00000000 */ 	sll	$zero,$zero,0x0
.L0f10fb08:
/*  f10fb08:	10000001 */ 	beqz	$zero,.L0f10fb10
/*  f10fb0c:	00008825 */ 	or	$s1,$zero,$zero
.L0f10fb10:
/*  f10fb10:	04410005 */ 	bgez	$v0,.L0f10fb28
/*  f10fb14:	27b4004c */ 	addiu	$s4,$sp,0x4c
/*  f10fb18:	8c6f029c */ 	lw	$t7,0x29c($v1)
/*  f10fb1c:	24120005 */ 	addiu	$s2,$zero,0x5
/*  f10fb20:	05e00003 */ 	bltz	$t7,.L0f10fb30
/*  f10fb24:	00000000 */ 	sll	$zero,$zero,0x0
.L0f10fb28:
/*  f10fb28:	10000001 */ 	beqz	$zero,.L0f10fb30
/*  f10fb2c:	24120001 */ 	addiu	$s2,$zero,0x1
.L0f10fb30:
/*  f10fb30:	060000d6 */ 	bltz	$s0,.L0f10fe8c
/*  f10fb34:	2402ffff */ 	addiu	$v0,$zero,-1
/*  f10fb38:	0fc35517 */ 	jal	func0f0d545c
/*  f10fb3c:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fb40:	00102600 */ 	sll	$a0,$s0,0x18
/*  f10fb44:	0004c603 */ 	sra	$t8,$a0,0x18
/*  f10fb48:	3c05800a */ 	lui	$a1,%hi(var800a22c0)
/*  f10fb4c:	8ca522c0 */ 	lw	$a1,%lo(var800a22c0)($a1)
/*  f10fb50:	03002025 */ 	or	$a0,$t8,$zero
/*  f10fb54:	27a60050 */ 	addiu	$a2,$sp,0x50
/*  f10fb58:	0fc45a00 */ 	jal	func0f116800
/*  f10fb5c:	00003825 */ 	or	$a3,$zero,$zero
/*  f10fb60:	3c01800a */ 	lui	$at,%hi(var800a21f8)
/*  f10fb64:	144000c7 */ 	bnez	$v0,.L0f10fe84
/*  f10fb68:	ac2221f8 */ 	sw	$v0,%lo(var800a21f8)($at)
/*  f10fb6c:	0fc41d3b */ 	jal	cheatsDisableAll
/*  f10fb70:	00000000 */ 	sll	$zero,$zero,0x0
/*  f10fb74:	3c05800a */ 	lui	$a1,%hi(g_SoloSaveFile)
/*  f10fb78:	24a52200 */ 	addiu	$a1,$a1,%lo(g_SoloSaveFile)
/*  f10fb7c:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fb80:	0fc35539 */ 	jal	func0f0d54e4
/*  f10fb84:	00003025 */ 	or	$a2,$zero,$zero
/*  f10fb88:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fb8c:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f10fb90:	24050005 */ 	addiu	$a1,$zero,0x5
/*  f10fb94:	3c03800a */ 	lui	$v1,%hi(g_SoloSaveFile)
/*  f10fb98:	24632200 */ 	addiu	$v1,$v1,%lo(g_SoloSaveFile)
/*  f10fb9c:	906a000b */ 	lbu	$t2,0xb($v1)
/*  f10fba0:	000248c0 */ 	sll	$t1,$v0,0x3
/*  f10fba4:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fba8:	314bff07 */ 	andi	$t3,$t2,0xff07
/*  f10fbac:	012b6025 */ 	or	$t4,$t1,$t3
/*  f10fbb0:	a06c000b */ 	sb	$t4,0xb($v1)
/*  f10fbb4:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f10fbb8:	24050020 */ 	addiu	$a1,$zero,0x20
/*  f10fbbc:	3c01800a */ 	lui	$at,%hi(g_SoloSaveFile+0x10)
/*  f10fbc0:	ac222210 */ 	sw	$v0,%lo(g_SoloSaveFile+0x10)($at)
/*  f10fbc4:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fbc8:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f10fbcc:	24050002 */ 	addiu	$a1,$zero,0x2
/*  f10fbd0:	3c03800a */ 	lui	$v1,%hi(g_SoloSaveFile)
/*  f10fbd4:	24632200 */ 	addiu	$v1,$v1,%lo(g_SoloSaveFile)
/*  f10fbd8:	906f000b */ 	lbu	$t7,0xb($v1)
/*  f10fbdc:	304e0007 */ 	andi	$t6,$v0,0x7
/*  f10fbe0:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fbe4:	31f8fff8 */ 	andi	$t8,$t7,0xfff8
/*  f10fbe8:	01d8c825 */ 	or	$t9,$t6,$t8
/*  f10fbec:	a079000b */ 	sb	$t9,0xb($v1)
/*  f10fbf0:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f10fbf4:	24050005 */ 	addiu	$a1,$zero,0x5
/*  f10fbf8:	3c01800a */ 	lui	$at,%hi(g_SoloSaveFile+0xc)
/*  f10fbfc:	a022220c */ 	sb	$v0,%lo(g_SoloSaveFile+0xc)($at)
/*  f10fc00:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fc04:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f10fc08:	24050006 */ 	addiu	$a1,$zero,0x6
/*  f10fc0c:	00022880 */ 	sll	$a1,$v0,0x2
/*  f10fc10:	2ca100fc */ 	sltiu	$at,$a1,0xfc
/*  f10fc14:	54200003 */ 	bnezl	$at,.L0f10fc24
/*  f10fc18:	00a02025 */ 	or	$a0,$a1,$zero
/*  f10fc1c:	240500ff */ 	addiu	$a1,$zero,0xff
/*  f10fc20:	00a02025 */ 	or	$a0,$a1,$zero
.L0f10fc24:
/*  f10fc24:	000441c0 */ 	sll	$t0,$a0,0x7
/*  f10fc28:	0c003a87 */ 	jal	audioSetSfxVolume
/*  f10fc2c:	3104ffff */ 	andi	$a0,$t0,0xffff
/*  f10fc30:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fc34:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f10fc38:	24050006 */ 	addiu	$a1,$zero,0x6
/*  f10fc3c:	00022880 */ 	sll	$a1,$v0,0x2
/*  f10fc40:	2ca100fc */ 	sltiu	$at,$a1,0xfc
/*  f10fc44:	54200003 */ 	bnezl	$at,.L0f10fc54
/*  f10fc48:	00a02025 */ 	or	$a0,$a1,$zero
/*  f10fc4c:	240500ff */ 	addiu	$a1,$zero,0xff
/*  f10fc50:	00a02025 */ 	or	$a0,$a1,$zero
.L0f10fc54:
/*  f10fc54:	000449c0 */ 	sll	$t1,$a0,0x7
/*  f10fc58:	0fc54bdc */ 	jal	optionsSetMusicVolume
/*  f10fc5c:	3124ffff */ 	andi	$a0,$t1,0xffff
/*  f10fc60:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fc64:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f10fc68:	24050002 */ 	addiu	$a1,$zero,0x2
/*  f10fc6c:	0c003ce3 */ 	jal	audioSetSoundMode
/*  f10fc70:	00402025 */ 	or	$a0,$v0,$zero
/*  f10fc74:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fc78:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f10fc7c:	24050003 */ 	addiu	$a1,$zero,0x3
/*  f10fc80:	02202025 */ 	or	$a0,$s1,$zero
/*  f10fc84:	0fc549cb */ 	jal	optionsSetControlMode
/*  f10fc88:	00402825 */ 	or	$a1,$v0,$zero
/*  f10fc8c:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fc90:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f10fc94:	24050003 */ 	addiu	$a1,$zero,0x3
/*  f10fc98:	02402025 */ 	or	$a0,$s2,$zero
/*  f10fc9c:	0fc549cb */ 	jal	optionsSetControlMode
/*  f10fca0:	00402825 */ 	or	$a1,$v0,$zero
/*  f10fca4:	3c10800a */ 	lui	$s0,%hi(g_SoloSaveFile)
/*  f10fca8:	3c11800a */ 	lui	$s1,%hi(g_SoloSaveFile+0xa)
/*  f10fcac:	2631220a */ 	addiu	$s1,$s1,%lo(g_SoloSaveFile+0xa)
/*  f10fcb0:	26102200 */ 	addiu	$s0,$s0,%lo(g_SoloSaveFile)
.L0f10fcb4:
/*  f10fcb4:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fcb8:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f10fcbc:	24050008 */ 	addiu	$a1,$zero,0x8
/*  f10fcc0:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f10fcc4:	0211082b */ 	sltu	$at,$s0,$s1
/*  f10fcc8:	1420fffa */ 	bnez	$at,.L0f10fcb4
/*  f10fccc:	a2020013 */ 	sb	$v0,0x13($s0)
/*  f10fcd0:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fcd4:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f10fcd8:	24050010 */ 	addiu	$a1,$zero,0x10
/*  f10fcdc:	3c01800a */ 	lui	$at,%hi(g_SoloSaveFile+0x1e)
/*  f10fce0:	3c13800a */ 	lui	$s3,%hi(g_SoloSaveFile)
/*  f10fce4:	a422221e */ 	sh	$v0,%lo(g_SoloSaveFile+0x1e)($at)
/*  f10fce8:	26732200 */ 	addiu	$s3,$s3,%lo(g_SoloSaveFile)
/*  f10fcec:	24120003 */ 	addiu	$s2,$zero,0x3
/*  f10fcf0:	00008025 */ 	or	$s0,$zero,$zero
.L0f10fcf4:
/*  f10fcf4:	02608825 */ 	or	$s1,$s3,$zero
.L0f10fcf8:
/*  f10fcf8:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fcfc:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f10fd00:	2405000c */ 	addiu	$a1,$zero,0xc
/*  f10fd04:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f10fd08:	26310002 */ 	addiu	$s1,$s1,0x2
/*  f10fd0c:	1612fffa */ 	bne	$s0,$s2,.L0f10fcf8
/*  f10fd10:	a622001e */ 	sh	$v0,0x1e($s1)
/*  f10fd14:	3c0c800a */ 	lui	$t4,%hi(g_SoloSaveFile+0x7e)
/*  f10fd18:	258c227e */ 	addiu	$t4,$t4,%lo(g_SoloSaveFile+0x7e)
/*  f10fd1c:	26730006 */ 	addiu	$s3,$s3,0x6
/*  f10fd20:	026c082b */ 	sltu	$at,$s3,$t4
/*  f10fd24:	5420fff3 */ 	bnezl	$at,.L0f10fcf4
/*  f10fd28:	00008025 */ 	or	$s0,$zero,$zero
/*  f10fd2c:	00008825 */ 	or	$s1,$zero,$zero
/*  f10fd30:	24120005 */ 	addiu	$s2,$zero,0x5
/*  f10fd34:	24100001 */ 	addiu	$s0,$zero,0x1
.L0f10fd38:
/*  f10fd38:	02802025 */ 	or	$a0,$s4,$zero
.L0f10fd3c:
/*  f10fd3c:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f10fd40:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f10fd44:	02202025 */ 	or	$a0,$s1,$zero
/*  f10fd48:	02002825 */ 	or	$a1,$s0,$zero
/*  f10fd4c:	0fc67103 */ 	jal	mpSetChallengeCompletedByAnyChrWithNumPlayers
/*  f10fd50:	00403025 */ 	or	$a2,$v0,$zero
/*  f10fd54:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f10fd58:	5612fff8 */ 	bnel	$s0,$s2,.L0f10fd3c
/*  f10fd5c:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fd60:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f10fd64:	2a21001e */ 	slti	$at,$s1,0x1e
/*  f10fd68:	5420fff3 */ 	bnezl	$at,.L0f10fd38
/*  f10fd6c:	24100001 */ 	addiu	$s0,$zero,0x1
/*  f10fd70:	0fc66bf7 */ 	jal	func0f19afdc
/*  f10fd74:	00000000 */ 	sll	$zero,$zero,0x0
/*  f10fd78:	3c10800a */ 	lui	$s0,%hi(g_SoloSaveFile)
/*  f10fd7c:	3c11800a */ 	lui	$s1,%hi(g_SoloSaveFile+0xc)
/*  f10fd80:	2631220c */ 	addiu	$s1,$s1,%lo(g_SoloSaveFile+0xc)
/*  f10fd84:	26102200 */ 	addiu	$s0,$s0,%lo(g_SoloSaveFile)
.L0f10fd88:
/*  f10fd88:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fd8c:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f10fd90:	24050015 */ 	addiu	$a1,$zero,0x15
/*  f10fd94:	26100004 */ 	addiu	$s0,$s0,0x4
/*  f10fd98:	0211082b */ 	sltu	$at,$s0,$s1
/*  f10fd9c:	1420fffa */ 	bnez	$at,.L0f10fd88
/*  f10fda0:	ae02009c */ 	sw	$v0,0x9c($s0)
/*  f10fda4:	3c10800a */ 	lui	$s0,%hi(g_SoloSaveFile)
/*  f10fda8:	3c12800a */ 	lui	$s2,%hi(g_SoloSaveFile+0x9)
/*  f10fdac:	3c11800a */ 	lui	$s1,%hi(g_SoloSaveFile+0x8)
/*  f10fdb0:	26312208 */ 	addiu	$s1,$s1,%lo(g_SoloSaveFile+0x8)
/*  f10fdb4:	26522209 */ 	addiu	$s2,$s2,%lo(g_SoloSaveFile+0x9)
/*  f10fdb8:	26102200 */ 	addiu	$s0,$s0,%lo(g_SoloSaveFile)
.L0f10fdbc:
/*  f10fdbc:	16110003 */ 	bne	$s0,$s1,.L0f10fdcc
/*  f10fdc0:	24050008 */ 	addiu	$a1,$zero,0x8
/*  f10fdc4:	10000001 */ 	beqz	$zero,.L0f10fdcc
/*  f10fdc8:	24050002 */ 	addiu	$a1,$zero,0x2
.L0f10fdcc:
/*  f10fdcc:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f10fdd0:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fdd4:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f10fdd8:	0212082b */ 	sltu	$at,$s0,$s2
/*  f10fddc:	1420fff7 */ 	bnez	$at,.L0f10fdbc
/*  f10fde0:	a20200ab */ 	sb	$v0,0xab($s0)
/*  f10fde4:	3c10800a */ 	lui	$s0,%hi(g_SoloSaveFile)
/*  f10fde8:	3c11800a */ 	lui	$s1,%hi(g_SoloSaveFile+0x4)
/*  f10fdec:	26312204 */ 	addiu	$s1,$s1,%lo(g_SoloSaveFile+0x4)
/*  f10fdf0:	26102200 */ 	addiu	$s0,$s0,%lo(g_SoloSaveFile)
.L0f10fdf4:
/*  f10fdf4:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fdf8:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f10fdfc:	24050008 */ 	addiu	$a1,$zero,0x8
/*  f10fe00:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f10fe04:	1611fffb */ 	bne	$s0,$s1,.L0f10fdf4
/*  f10fe08:	a20200b4 */ 	sb	$v0,0xb4($s0)
/*  f10fe0c:	3c10800a */ 	lui	$s0,%hi(g_SoloSaveFile+0x14)
/*  f10fe10:	26102214 */ 	addiu	$s0,$s0,%lo(g_SoloSaveFile+0x14)
/*  f10fe14:	02002825 */ 	or	$a1,$s0,$zero
/*  f10fe18:	0fc47961 */ 	jal	func0f11e584
/*  f10fe1c:	24040041 */ 	addiu	$a0,$zero,0x41
/*  f10fe20:	50400004 */ 	beqzl	$v0,.L0f10fe34
/*  f10fe24:	24040042 */ 	addiu	$a0,$zero,0x42
/*  f10fe28:	0fc672ce */ 	jal	func0f19cb38
/*  f10fe2c:	24040020 */ 	addiu	$a0,$zero,0x20
/*  f10fe30:	24040042 */ 	addiu	$a0,$zero,0x42
.L0f10fe34:
/*  f10fe34:	0fc47961 */ 	jal	func0f11e584
/*  f10fe38:	02002825 */ 	or	$a1,$s0,$zero
/*  f10fe3c:	50400004 */ 	beqzl	$v0,.L0f10fe50
/*  f10fe40:	24040043 */ 	addiu	$a0,$zero,0x43
/*  f10fe44:	0fc672ce */ 	jal	func0f19cb38
/*  f10fe48:	24040021 */ 	addiu	$a0,$zero,0x21
/*  f10fe4c:	24040043 */ 	addiu	$a0,$zero,0x43
.L0f10fe50:
/*  f10fe50:	0fc47961 */ 	jal	func0f11e584
/*  f10fe54:	02002825 */ 	or	$a1,$s0,$zero
/*  f10fe58:	10400003 */ 	beqz	$v0,.L0f10fe68
/*  f10fe5c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f10fe60:	0fc672ce */ 	jal	func0f19cb38
/*  f10fe64:	24040022 */ 	addiu	$a0,$zero,0x22
.L0f10fe68:
/*  f10fe68:	0fc35531 */ 	jal	func0f0d54c4
/*  f10fe6c:	02802025 */ 	or	$a0,$s4,$zero
/*  f10fe70:	3c04800a */ 	lui	$a0,%hi(g_SoloSaveFile)
/*  f10fe74:	0fc43c81 */ 	jal	func0f10f204
/*  f10fe78:	24842200 */ 	addiu	$a0,$a0,%lo(g_SoloSaveFile)
/*  f10fe7c:	10000003 */ 	beqz	$zero,.L0f10fe8c
/*  f10fe80:	00001025 */ 	or	$v0,$zero,$zero
.L0f10fe84:
/*  f10fe84:	10000001 */ 	beqz	$zero,.L0f10fe8c
/*  f10fe88:	2402ffff */ 	addiu	$v0,$zero,-1
.L0f10fe8c:
/*  f10fe8c:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f10fe90:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f10fe94:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f10fe98:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f10fe9c:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f10fea0:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f10fea4:	03e00008 */ 	jr	$ra
/*  f10fea8:	27bd0140 */ 	addiu	$sp,$sp,0x140
);

GLOBAL_ASM(
glabel func0f10feac
/*  f10feac:	27bdfeb8 */ 	addiu	$sp,$sp,-328
/*  f10feb0:	afb4002c */ 	sw	$s4,0x2c($sp)
/*  f10feb4:	3c14800a */ 	lui	$s4,%hi(g_Vars)
/*  f10feb8:	26949fc0 */ 	addiu	$s4,$s4,%lo(g_Vars)
/*  f10febc:	8e820298 */ 	lw	$v0,0x298($s4)
/*  f10fec0:	afbf0034 */ 	sw	$ra,0x34($sp)
/*  f10fec4:	afb50030 */ 	sw	$s5,0x30($sp)
/*  f10fec8:	afb30028 */ 	sw	$s3,0x28($sp)
/*  f10fecc:	afb20024 */ 	sw	$s2,0x24($sp)
/*  f10fed0:	afb10020 */ 	sw	$s1,0x20($sp)
/*  f10fed4:	afb0001c */ 	sw	$s0,0x1c($sp)
/*  f10fed8:	afa40148 */ 	sw	$a0,0x148($sp)
/*  f10fedc:	afa5014c */ 	sw	$a1,0x14c($sp)
/*  f10fee0:	04410005 */ 	bgez	$v0,.L0f10fef8
/*  f10fee4:	afa60150 */ 	sw	$a2,0x150($sp)
/*  f10fee8:	8e8e029c */ 	lw	$t6,0x29c($s4)
/*  f10feec:	24130004 */ 	addiu	$s3,$zero,0x4
/*  f10fef0:	05c00003 */ 	bltz	$t6,.L0f10ff00
/*  f10fef4:	00000000 */ 	sll	$zero,$zero,0x0
.L0f10fef8:
/*  f10fef8:	10000001 */ 	beqz	$zero,.L0f10ff00
/*  f10fefc:	00009825 */ 	or	$s3,$zero,$zero
.L0f10ff00:
/*  f10ff00:	04410005 */ 	bgez	$v0,.L0f10ff18
/*  f10ff04:	24120001 */ 	addiu	$s2,$zero,0x1
/*  f10ff08:	8e8f029c */ 	lw	$t7,0x29c($s4)
/*  f10ff0c:	24110005 */ 	addiu	$s1,$zero,0x5
/*  f10ff10:	05e00003 */ 	bltz	$t7,.L0f10ff20
/*  f10ff14:	00000000 */ 	sll	$zero,$zero,0x0
.L0f10ff18:
/*  f10ff18:	10000001 */ 	beqz	$zero,.L0f10ff20
/*  f10ff1c:	24110001 */ 	addiu	$s1,$zero,0x1
.L0f10ff20:
/*  f10ff20:	3c018007 */ 	lui	$at,%hi(var80075bd0)
/*  f10ff24:	ac325bd0 */ 	sw	$s2,%lo(var80075bd0)($at)
/*  f10ff28:	0fc549e0 */ 	jal	optionsGetForwardPitch
/*  f10ff2c:	02602025 */ 	or	$a0,$s3,$zero
/*  f10ff30:	3c10800a */ 	lui	$s0,%hi(g_SoloSaveFile+0x14)
/*  f10ff34:	26102214 */ 	addiu	$s0,$s0,%lo(g_SoloSaveFile+0x14)
/*  f10ff38:	02002825 */ 	or	$a1,$s0,$zero
/*  f10ff3c:	00002025 */ 	or	$a0,$zero,$zero
/*  f10ff40:	0fc4794c */ 	jal	func0f11e530
/*  f10ff44:	00403025 */ 	or	$a2,$v0,$zero
/*  f10ff48:	0fc549e9 */ 	jal	optionsGetAutoAim
/*  f10ff4c:	02602025 */ 	or	$a0,$s3,$zero
/*  f10ff50:	02402025 */ 	or	$a0,$s2,$zero
/*  f10ff54:	02002825 */ 	or	$a1,$s0,$zero
/*  f10ff58:	0fc4794c */ 	jal	func0f11e530
/*  f10ff5c:	00403025 */ 	or	$a2,$v0,$zero
/*  f10ff60:	0fc549fb */ 	jal	optionsGetAimControl
/*  f10ff64:	02602025 */ 	or	$a0,$s3,$zero
/*  f10ff68:	24040002 */ 	addiu	$a0,$zero,0x2
/*  f10ff6c:	02002825 */ 	or	$a1,$s0,$zero
/*  f10ff70:	0fc4794c */ 	jal	func0f11e530
/*  f10ff74:	00403025 */ 	or	$a2,$v0,$zero
/*  f10ff78:	0fc54a04 */ 	jal	optionsGetSightOnScreen
/*  f10ff7c:	02602025 */ 	or	$a0,$s3,$zero
/*  f10ff80:	24040003 */ 	addiu	$a0,$zero,0x3
/*  f10ff84:	02002825 */ 	or	$a1,$s0,$zero
/*  f10ff88:	0fc4794c */ 	jal	func0f11e530
/*  f10ff8c:	00403025 */ 	or	$a2,$v0,$zero
/*  f10ff90:	0fc549f2 */ 	jal	optionsGetLookAhead
/*  f10ff94:	02602025 */ 	or	$a0,$s3,$zero
/*  f10ff98:	24040004 */ 	addiu	$a0,$zero,0x4
/*  f10ff9c:	02002825 */ 	or	$a1,$s0,$zero
/*  f10ffa0:	0fc4794c */ 	jal	func0f11e530
/*  f10ffa4:	00403025 */ 	or	$a2,$v0,$zero
/*  f10ffa8:	0fc54a0d */ 	jal	optionsGetAmmoOnScreen
/*  f10ffac:	02602025 */ 	or	$a0,$s3,$zero
/*  f10ffb0:	24040005 */ 	addiu	$a0,$zero,0x5
/*  f10ffb4:	02002825 */ 	or	$a1,$s0,$zero
/*  f10ffb8:	0fc4794c */ 	jal	func0f11e530
/*  f10ffbc:	00403025 */ 	or	$a2,$v0,$zero
/*  f10ffc0:	0fc54a49 */ 	jal	optionsGetHeadRoll
/*  f10ffc4:	02602025 */ 	or	$a0,$s3,$zero
/*  f10ffc8:	24040009 */ 	addiu	$a0,$zero,0x9
/*  f10ffcc:	02002825 */ 	or	$a1,$s0,$zero
/*  f10ffd0:	0fc4794c */ 	jal	func0f11e530
/*  f10ffd4:	00403025 */ 	or	$a2,$v0,$zero
/*  f10ffd8:	0fc54a16 */ 	jal	optionsGetShowGunFunction
/*  f10ffdc:	02602025 */ 	or	$a0,$s3,$zero
/*  f10ffe0:	2404000a */ 	addiu	$a0,$zero,0xa
/*  f10ffe4:	02002825 */ 	or	$a1,$s0,$zero
/*  f10ffe8:	0fc4794c */ 	jal	func0f11e530
/*  f10ffec:	00403025 */ 	or	$a2,$v0,$zero
/*  f10fff0:	0fc54a1f */ 	jal	optionsGetAlwaysShowTarget
/*  f10fff4:	02602025 */ 	or	$a0,$s3,$zero
/*  f10fff8:	24040015 */ 	addiu	$a0,$zero,0x15
/*  f10fffc:	02002825 */ 	or	$a1,$s0,$zero
/*  f110000:	0fc4794c */ 	jal	func0f11e530
/*  f110004:	00403025 */ 	or	$a2,$v0,$zero
/*  f110008:	0fc54a28 */ 	jal	optionsGetShowZoomRange
/*  f11000c:	02602025 */ 	or	$a0,$s3,$zero
/*  f110010:	24040017 */ 	addiu	$a0,$zero,0x17
/*  f110014:	02002825 */ 	or	$a1,$s0,$zero
/*  f110018:	0fc4794c */ 	jal	func0f11e530
/*  f11001c:	00403025 */ 	or	$a2,$v0,$zero
/*  f110020:	0fc54a3a */ 	jal	optionsGetShowMissionTime
/*  f110024:	02602025 */ 	or	$a0,$s3,$zero
/*  f110028:	2404001a */ 	addiu	$a0,$zero,0x1a
/*  f11002c:	02002825 */ 	or	$a1,$s0,$zero
/*  f110030:	0fc4794c */ 	jal	func0f11e530
/*  f110034:	00403025 */ 	or	$a2,$v0,$zero
/*  f110038:	0fc54a31 */ 	jal	optionsGetPaintball
/*  f11003c:	02602025 */ 	or	$a0,$s3,$zero
/*  f110040:	24040020 */ 	addiu	$a0,$zero,0x20
/*  f110044:	02002825 */ 	or	$a1,$s0,$zero
/*  f110048:	0fc4794c */ 	jal	func0f11e530
/*  f11004c:	00403025 */ 	or	$a2,$v0,$zero
/*  f110050:	0fc549e0 */ 	jal	optionsGetForwardPitch
/*  f110054:	02202025 */ 	or	$a0,$s1,$zero
/*  f110058:	2404000c */ 	addiu	$a0,$zero,0xc
/*  f11005c:	02002825 */ 	or	$a1,$s0,$zero
/*  f110060:	0fc4794c */ 	jal	func0f11e530
/*  f110064:	00403025 */ 	or	$a2,$v0,$zero
/*  f110068:	0fc549e9 */ 	jal	optionsGetAutoAim
/*  f11006c:	02202025 */ 	or	$a0,$s1,$zero
/*  f110070:	2404000d */ 	addiu	$a0,$zero,0xd
/*  f110074:	02002825 */ 	or	$a1,$s0,$zero
/*  f110078:	0fc4794c */ 	jal	func0f11e530
/*  f11007c:	00403025 */ 	or	$a2,$v0,$zero
/*  f110080:	0fc549fb */ 	jal	optionsGetAimControl
/*  f110084:	02202025 */ 	or	$a0,$s1,$zero
/*  f110088:	2404000e */ 	addiu	$a0,$zero,0xe
/*  f11008c:	02002825 */ 	or	$a1,$s0,$zero
/*  f110090:	0fc4794c */ 	jal	func0f11e530
/*  f110094:	00403025 */ 	or	$a2,$v0,$zero
/*  f110098:	0fc54a04 */ 	jal	optionsGetSightOnScreen
/*  f11009c:	02202025 */ 	or	$a0,$s1,$zero
/*  f1100a0:	2404000f */ 	addiu	$a0,$zero,0xf
/*  f1100a4:	02002825 */ 	or	$a1,$s0,$zero
/*  f1100a8:	0fc4794c */ 	jal	func0f11e530
/*  f1100ac:	00403025 */ 	or	$a2,$v0,$zero
/*  f1100b0:	0fc549f2 */ 	jal	optionsGetLookAhead
/*  f1100b4:	02202025 */ 	or	$a0,$s1,$zero
/*  f1100b8:	24040010 */ 	addiu	$a0,$zero,0x10
/*  f1100bc:	02002825 */ 	or	$a1,$s0,$zero
/*  f1100c0:	0fc4794c */ 	jal	func0f11e530
/*  f1100c4:	00403025 */ 	or	$a2,$v0,$zero
/*  f1100c8:	0fc54a0d */ 	jal	optionsGetAmmoOnScreen
/*  f1100cc:	02202025 */ 	or	$a0,$s1,$zero
/*  f1100d0:	24040011 */ 	addiu	$a0,$zero,0x11
/*  f1100d4:	02002825 */ 	or	$a1,$s0,$zero
/*  f1100d8:	0fc4794c */ 	jal	func0f11e530
/*  f1100dc:	00403025 */ 	or	$a2,$v0,$zero
/*  f1100e0:	0fc54a49 */ 	jal	optionsGetHeadRoll
/*  f1100e4:	02202025 */ 	or	$a0,$s1,$zero
/*  f1100e8:	24040012 */ 	addiu	$a0,$zero,0x12
/*  f1100ec:	02002825 */ 	or	$a1,$s0,$zero
/*  f1100f0:	0fc4794c */ 	jal	func0f11e530
/*  f1100f4:	00403025 */ 	or	$a2,$v0,$zero
/*  f1100f8:	0fc54a16 */ 	jal	optionsGetShowGunFunction
/*  f1100fc:	02202025 */ 	or	$a0,$s1,$zero
/*  f110100:	24040013 */ 	addiu	$a0,$zero,0x13
/*  f110104:	02002825 */ 	or	$a1,$s0,$zero
/*  f110108:	0fc4794c */ 	jal	func0f11e530
/*  f11010c:	00403025 */ 	or	$a2,$v0,$zero
/*  f110110:	0fc54a1f */ 	jal	optionsGetAlwaysShowTarget
/*  f110114:	02202025 */ 	or	$a0,$s1,$zero
/*  f110118:	24040016 */ 	addiu	$a0,$zero,0x16
/*  f11011c:	02002825 */ 	or	$a1,$s0,$zero
/*  f110120:	0fc4794c */ 	jal	func0f11e530
/*  f110124:	00403025 */ 	or	$a2,$v0,$zero
/*  f110128:	0fc54a28 */ 	jal	optionsGetShowZoomRange
/*  f11012c:	02202025 */ 	or	$a0,$s1,$zero
/*  f110130:	24040018 */ 	addiu	$a0,$zero,0x18
/*  f110134:	02002825 */ 	or	$a1,$s0,$zero
/*  f110138:	0fc4794c */ 	jal	func0f11e530
/*  f11013c:	00403025 */ 	or	$a2,$v0,$zero
/*  f110140:	0fc54a3a */ 	jal	optionsGetShowMissionTime
/*  f110144:	02202025 */ 	or	$a0,$s1,$zero
/*  f110148:	2404001b */ 	addiu	$a0,$zero,0x1b
/*  f11014c:	02002825 */ 	or	$a1,$s0,$zero
/*  f110150:	0fc4794c */ 	jal	func0f11e530
/*  f110154:	00403025 */ 	or	$a2,$v0,$zero
/*  f110158:	0fc54a31 */ 	jal	optionsGetPaintball
/*  f11015c:	02202025 */ 	or	$a0,$s1,$zero
/*  f110160:	24040021 */ 	addiu	$a0,$zero,0x21
/*  f110164:	02002825 */ 	or	$a1,$s0,$zero
/*  f110168:	0fc4794c */ 	jal	func0f11e530
/*  f11016c:	00403025 */ 	or	$a2,$v0,$zero
/*  f110170:	0fc54bcd */ 	jal	optionsGetScreenSplit
/*  f110174:	00000000 */ 	sll	$zero,$zero,0x0
/*  f110178:	24040019 */ 	addiu	$a0,$zero,0x19
/*  f11017c:	02002825 */ 	or	$a1,$s0,$zero
/*  f110180:	0fc4794c */ 	jal	func0f11e530
/*  f110184:	00403025 */ 	or	$a2,$v0,$zero
/*  f110188:	0fc54bc7 */ 	jal	optionsGetScreenRatio
/*  f11018c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f110190:	24040007 */ 	addiu	$a0,$zero,0x7
/*  f110194:	02002825 */ 	or	$a1,$s0,$zero
/*  f110198:	0fc4794c */ 	jal	func0f11e530
/*  f11019c:	00403025 */ 	or	$a2,$v0,$zero
/*  f1101a0:	0fc54bc1 */ 	jal	optionsGetScreenSize
/*  f1101a4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1101a8:	00523026 */ 	xor	$a2,$v0,$s2
/*  f1101ac:	2cc60001 */ 	sltiu	$a2,$a2,0x1
/*  f1101b0:	24040006 */ 	addiu	$a0,$zero,0x6
/*  f1101b4:	0fc4794c */ 	jal	func0f11e530
/*  f1101b8:	02002825 */ 	or	$a1,$s0,$zero
/*  f1101bc:	0fc54bc1 */ 	jal	optionsGetScreenSize
/*  f1101c0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1101c4:	24150002 */ 	addiu	$s5,$zero,0x2
/*  f1101c8:	00553026 */ 	xor	$a2,$v0,$s5
/*  f1101cc:	2cc60001 */ 	sltiu	$a2,$a2,0x1
/*  f1101d0:	24040008 */ 	addiu	$a0,$zero,0x8
/*  f1101d4:	0fc4794c */ 	jal	func0f11e530
/*  f1101d8:	02002825 */ 	or	$a1,$s0,$zero
/*  f1101dc:	3c188007 */ 	lui	$t8,%hi(var800706c8)
/*  f1101e0:	8f1806c8 */ 	lw	$t8,%lo(var800706c8)($t8)
/*  f1101e4:	24040022 */ 	addiu	$a0,$zero,0x22
/*  f1101e8:	02002825 */ 	or	$a1,$s0,$zero
/*  f1101ec:	02583026 */ 	xor	$a2,$s2,$t8
/*  f1101f0:	0fc4794c */ 	jal	func0f11e530
/*  f1101f4:	2cc60001 */ 	sltiu	$a2,$a2,0x1
/*  f1101f8:	0fc54a43 */ 	jal	optionsGetInGameSubtitles
/*  f1101fc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f110200:	2404000b */ 	addiu	$a0,$zero,0xb
/*  f110204:	02002825 */ 	or	$a1,$s0,$zero
/*  f110208:	0fc4794c */ 	jal	func0f11e530
/*  f11020c:	00403025 */ 	or	$a2,$v0,$zero
/*  f110210:	0fc54a46 */ 	jal	optionsGetCutsceneSubtitles
/*  f110214:	00000000 */ 	sll	$zero,$zero,0x0
/*  f110218:	24040014 */ 	addiu	$a0,$zero,0x14
/*  f11021c:	02002825 */ 	or	$a1,$s0,$zero
/*  f110220:	0fc4794c */ 	jal	func0f11e530
/*  f110224:	00403025 */ 	or	$a2,$v0,$zero
/*  f110228:	24040040 */ 	addiu	$a0,$zero,0x40
/*  f11022c:	02002825 */ 	or	$a1,$s0,$zero
/*  f110230:	0fc4794c */ 	jal	func0f11e530
/*  f110234:	928604e3 */ 	lbu	$a2,0x4e3($s4)
/*  f110238:	0fc672b5 */ 	jal	func0f19cad4
/*  f11023c:	24040020 */ 	addiu	$a0,$zero,0x20
/*  f110240:	24040041 */ 	addiu	$a0,$zero,0x41
/*  f110244:	02002825 */ 	or	$a1,$s0,$zero
/*  f110248:	0fc4794c */ 	jal	func0f11e530
/*  f11024c:	00403025 */ 	or	$a2,$v0,$zero
/*  f110250:	0fc672b5 */ 	jal	func0f19cad4
/*  f110254:	24040021 */ 	addiu	$a0,$zero,0x21
/*  f110258:	24040042 */ 	addiu	$a0,$zero,0x42
/*  f11025c:	02002825 */ 	or	$a1,$s0,$zero
/*  f110260:	0fc4794c */ 	jal	func0f11e530
/*  f110264:	00403025 */ 	or	$a2,$v0,$zero
/*  f110268:	0fc672b5 */ 	jal	func0f19cad4
/*  f11026c:	24040022 */ 	addiu	$a0,$zero,0x22
/*  f110270:	24040043 */ 	addiu	$a0,$zero,0x43
/*  f110274:	02002825 */ 	or	$a1,$s0,$zero
/*  f110278:	0fc4794c */ 	jal	func0f11e530
/*  f11027c:	00403025 */ 	or	$a2,$v0,$zero
/*  f110280:	0fc54bc1 */ 	jal	optionsGetScreenSize
/*  f110284:	00000000 */ 	sll	$zero,$zero,0x0
/*  f110288:	50400002 */ 	beqzl	$v0,.L0f110294
/*  f11028c:	8e990450 */ 	lw	$t9,0x450($s4)
/*  f110290:	8e990450 */ 	lw	$t9,0x450($s4)
.L0f110294:
/*  f110294:	2404001f */ 	addiu	$a0,$zero,0x1f
/*  f110298:	02002825 */ 	or	$a1,$s0,$zero
/*  f11029c:	02593026 */ 	xor	$a2,$s2,$t9
/*  f1102a0:	0fc4794c */ 	jal	func0f11e530
/*  f1102a4:	2cc60001 */ 	sltiu	$a2,$a2,0x1
/*  f1102a8:	8e880448 */ 	lw	$t0,0x448($s4)
/*  f1102ac:	2404001c */ 	addiu	$a0,$zero,0x1c
/*  f1102b0:	02002825 */ 	or	$a1,$s0,$zero
/*  f1102b4:	02483026 */ 	xor	$a2,$s2,$t0
/*  f1102b8:	0fc4794c */ 	jal	func0f11e530
/*  f1102bc:	2cc60001 */ 	sltiu	$a2,$a2,0x1
/*  f1102c0:	8e890454 */ 	lw	$t1,0x454($s4)
/*  f1102c4:	2404001d */ 	addiu	$a0,$zero,0x1d
/*  f1102c8:	02002825 */ 	or	$a1,$s0,$zero
/*  f1102cc:	02493026 */ 	xor	$a2,$s2,$t1
/*  f1102d0:	0fc4794c */ 	jal	func0f11e530
/*  f1102d4:	2cc60001 */ 	sltiu	$a2,$a2,0x1
/*  f1102d8:	8e8a044c */ 	lw	$t2,0x44c($s4)
/*  f1102dc:	2404001e */ 	addiu	$a0,$zero,0x1e
/*  f1102e0:	02002825 */ 	or	$a1,$s0,$zero
/*  f1102e4:	024a3026 */ 	xor	$a2,$s2,$t2
/*  f1102e8:	0fc4794c */ 	jal	func0f11e530
/*  f1102ec:	2cc60001 */ 	sltiu	$a2,$a2,0x1
/*  f1102f0:	8fab0148 */ 	lw	$t3,0x148($sp)
/*  f1102f4:	27b4004c */ 	addiu	$s4,$sp,0x4c
/*  f1102f8:	2402ffff */ 	addiu	$v0,$zero,-1
/*  f1102fc:	056000b6 */ 	bltz	$t3,.L0f1105d8
/*  f110300:	00000000 */ 	sll	$zero,$zero,0x0
/*  f110304:	0fc35517 */ 	jal	func0f0d545c
/*  f110308:	02802025 */ 	or	$a0,$s4,$zero
/*  f11030c:	3c12800a */ 	lui	$s2,%hi(g_SoloSaveFile)
/*  f110310:	26522200 */ 	addiu	$s2,$s2,%lo(g_SoloSaveFile)
/*  f110314:	02402825 */ 	or	$a1,$s2,$zero
/*  f110318:	0fc35569 */ 	jal	func0f0d55a4
/*  f11031c:	02802025 */ 	or	$a0,$s4,$zero
/*  f110320:	9245000b */ 	lbu	$a1,0xb($s2)
/*  f110324:	02802025 */ 	or	$a0,$s4,$zero
/*  f110328:	24060005 */ 	addiu	$a2,$zero,0x5
/*  f11032c:	000560c2 */ 	srl	$t4,$a1,0x3
/*  f110330:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f110334:	01802825 */ 	or	$a1,$t4,$zero
/*  f110338:	02802025 */ 	or	$a0,$s4,$zero
/*  f11033c:	8e450010 */ 	lw	$a1,0x10($s2)
/*  f110340:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f110344:	24060020 */ 	addiu	$a2,$zero,0x20
/*  f110348:	8e450008 */ 	lw	$a1,0x8($s2)
/*  f11034c:	02802025 */ 	or	$a0,$s4,$zero
/*  f110350:	24060002 */ 	addiu	$a2,$zero,0x2
/*  f110354:	30ad0007 */ 	andi	$t5,$a1,0x7
/*  f110358:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f11035c:	01a02825 */ 	or	$a1,$t5,$zero
/*  f110360:	02802025 */ 	or	$a0,$s4,$zero
/*  f110364:	9245000c */ 	lbu	$a1,0xc($s2)
/*  f110368:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f11036c:	24060005 */ 	addiu	$a2,$zero,0x5
/*  f110370:	3c028006 */ 	lui	$v0,%hi(g_SfxVolume)
/*  f110374:	9442ddc8 */ 	lhu	$v0,%lo(g_SfxVolume)($v0)
/*  f110378:	02802025 */ 	or	$a0,$s4,$zero
/*  f11037c:	24060006 */ 	addiu	$a2,$zero,0x6
/*  f110380:	28415001 */ 	slti	$at,$v0,0x5001
/*  f110384:	54200004 */ 	bnezl	$at,.L0f110398
/*  f110388:	00403825 */ 	or	$a3,$v0,$zero
/*  f11038c:	10000002 */ 	beqz	$zero,.L0f110398
/*  f110390:	24075000 */ 	addiu	$a3,$zero,0x5000
/*  f110394:	00403825 */ 	or	$a3,$v0,$zero
.L0f110398:
/*  f110398:	000729c3 */ 	sra	$a1,$a3,0x7
/*  f11039c:	00057082 */ 	srl	$t6,$a1,0x2
/*  f1103a0:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f1103a4:	01c02825 */ 	or	$a1,$t6,$zero
/*  f1103a8:	0fc54bd4 */ 	jal	optionsGetMusicVolume
/*  f1103ac:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1103b0:	000229c3 */ 	sra	$a1,$v0,0x7
/*  f1103b4:	00057882 */ 	srl	$t7,$a1,0x2
/*  f1103b8:	01e02825 */ 	or	$a1,$t7,$zero
/*  f1103bc:	02802025 */ 	or	$a0,$s4,$zero
/*  f1103c0:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f1103c4:	24060006 */ 	addiu	$a2,$zero,0x6
/*  f1103c8:	3c058006 */ 	lui	$a1,%hi(g_SoundMode)
/*  f1103cc:	8ca5ddcc */ 	lw	$a1,%lo(g_SoundMode)($a1)
/*  f1103d0:	02802025 */ 	or	$a0,$s4,$zero
/*  f1103d4:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f1103d8:	24060002 */ 	addiu	$a2,$zero,0x2
/*  f1103dc:	0fc549c4 */ 	jal	optionsGetControlMode
/*  f1103e0:	02602025 */ 	or	$a0,$s3,$zero
/*  f1103e4:	02802025 */ 	or	$a0,$s4,$zero
/*  f1103e8:	00402825 */ 	or	$a1,$v0,$zero
/*  f1103ec:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f1103f0:	24060003 */ 	addiu	$a2,$zero,0x3
/*  f1103f4:	0fc549c4 */ 	jal	optionsGetControlMode
/*  f1103f8:	02202025 */ 	or	$a0,$s1,$zero
/*  f1103fc:	02802025 */ 	or	$a0,$s4,$zero
/*  f110400:	00402825 */ 	or	$a1,$v0,$zero
/*  f110404:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f110408:	24060003 */ 	addiu	$a2,$zero,0x3
/*  f11040c:	3c10800a */ 	lui	$s0,%hi(g_SoloSaveFile)
/*  f110410:	3c11800a */ 	lui	$s1,%hi(g_SoloSaveFile+0xa)
/*  f110414:	2631220a */ 	addiu	$s1,$s1,%lo(g_SoloSaveFile+0xa)
/*  f110418:	26102200 */ 	addiu	$s0,$s0,%lo(g_SoloSaveFile)
/*  f11041c:	02802025 */ 	or	$a0,$s4,$zero
.L0f110420:
/*  f110420:	92050014 */ 	lbu	$a1,0x14($s0)
/*  f110424:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f110428:	24060008 */ 	addiu	$a2,$zero,0x8
/*  f11042c:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f110430:	0211082b */ 	sltu	$at,$s0,$s1
/*  f110434:	5420fffa */ 	bnezl	$at,.L0f110420
/*  f110438:	02802025 */ 	or	$a0,$s4,$zero
/*  f11043c:	02802025 */ 	or	$a0,$s4,$zero
/*  f110440:	9645001e */ 	lhu	$a1,0x1e($s2)
/*  f110444:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f110448:	24060010 */ 	addiu	$a2,$zero,0x10
/*  f11044c:	3c15800a */ 	lui	$s5,%hi(g_SoloSaveFile)
/*  f110450:	26b52200 */ 	addiu	$s5,$s5,%lo(g_SoloSaveFile)
/*  f110454:	24130006 */ 	addiu	$s3,$zero,0x6
/*  f110458:	00008825 */ 	or	$s1,$zero,$zero
.L0f11045c:
/*  f11045c:	02a09025 */ 	or	$s2,$s5,$zero
.L0f110460:
/*  f110460:	02802025 */ 	or	$a0,$s4,$zero
/*  f110464:	96450020 */ 	lhu	$a1,0x20($s2)
/*  f110468:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f11046c:	2406000c */ 	addiu	$a2,$zero,0xc
/*  f110470:	26310002 */ 	addiu	$s1,$s1,0x2
/*  f110474:	1633fffa */ 	bne	$s1,$s3,.L0f110460
/*  f110478:	26520002 */ 	addiu	$s2,$s2,0x2
/*  f11047c:	3c18800a */ 	lui	$t8,%hi(g_SoloSaveFile+0x7e)
/*  f110480:	2718227e */ 	addiu	$t8,$t8,%lo(g_SoloSaveFile+0x7e)
/*  f110484:	26b50006 */ 	addiu	$s5,$s5,0x6
/*  f110488:	02b8082b */ 	sltu	$at,$s5,$t8
/*  f11048c:	5420fff3 */ 	bnezl	$at,.L0f11045c
/*  f110490:	00008825 */ 	or	$s1,$zero,$zero
/*  f110494:	00008825 */ 	or	$s1,$zero,$zero
/*  f110498:	24120005 */ 	addiu	$s2,$zero,0x5
/*  f11049c:	24100001 */ 	addiu	$s0,$zero,0x1
.L0f1104a0:
/*  f1104a0:	02202025 */ 	or	$a0,$s1,$zero
.L0f1104a4:
/*  f1104a4:	0fc670f7 */ 	jal	mpIsChallengeCompletedByAnyChrWithNumPlayers
/*  f1104a8:	02002825 */ 	or	$a1,$s0,$zero
/*  f1104ac:	02802025 */ 	or	$a0,$s4,$zero
/*  f1104b0:	00402825 */ 	or	$a1,$v0,$zero
/*  f1104b4:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f1104b8:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f1104bc:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f1104c0:	5612fff8 */ 	bnel	$s0,$s2,.L0f1104a4
/*  f1104c4:	02202025 */ 	or	$a0,$s1,$zero
/*  f1104c8:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f1104cc:	2a21001e */ 	slti	$at,$s1,0x1e
/*  f1104d0:	5420fff3 */ 	bnezl	$at,.L0f1104a0
/*  f1104d4:	24100001 */ 	addiu	$s0,$zero,0x1
/*  f1104d8:	3c10800a */ 	lui	$s0,%hi(g_SoloSaveFile)
/*  f1104dc:	3c11800a */ 	lui	$s1,%hi(g_SoloSaveFile+0xc)
/*  f1104e0:	2631220c */ 	addiu	$s1,$s1,%lo(g_SoloSaveFile+0xc)
/*  f1104e4:	26102200 */ 	addiu	$s0,$s0,%lo(g_SoloSaveFile)
/*  f1104e8:	02802025 */ 	or	$a0,$s4,$zero
.L0f1104ec:
/*  f1104ec:	8e0500a0 */ 	lw	$a1,0xa0($s0)
/*  f1104f0:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f1104f4:	24060015 */ 	addiu	$a2,$zero,0x15
/*  f1104f8:	26100004 */ 	addiu	$s0,$s0,0x4
/*  f1104fc:	0211082b */ 	sltu	$at,$s0,$s1
/*  f110500:	5420fffa */ 	bnezl	$at,.L0f1104ec
/*  f110504:	02802025 */ 	or	$a0,$s4,$zero
/*  f110508:	3c10800a */ 	lui	$s0,%hi(g_SoloSaveFile)
/*  f11050c:	3c12800a */ 	lui	$s2,%hi(g_SoloSaveFile+0x9)
/*  f110510:	3c11800a */ 	lui	$s1,%hi(g_SoloSaveFile+0x8)
/*  f110514:	26312208 */ 	addiu	$s1,$s1,%lo(g_SoloSaveFile+0x8)
/*  f110518:	26522209 */ 	addiu	$s2,$s2,%lo(g_SoloSaveFile+0x9)
/*  f11051c:	26102200 */ 	addiu	$s0,$s0,%lo(g_SoloSaveFile)
.L0f110520:
/*  f110520:	16110003 */ 	bne	$s0,$s1,.L0f110530
/*  f110524:	02802025 */ 	or	$a0,$s4,$zero
/*  f110528:	10000002 */ 	beqz	$zero,.L0f110534
/*  f11052c:	24070002 */ 	addiu	$a3,$zero,0x2
.L0f110530:
/*  f110530:	24070008 */ 	addiu	$a3,$zero,0x8
.L0f110534:
/*  f110534:	920500ac */ 	lbu	$a1,0xac($s0)
/*  f110538:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f11053c:	00e03025 */ 	or	$a2,$a3,$zero
/*  f110540:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f110544:	0212082b */ 	sltu	$at,$s0,$s2
/*  f110548:	1420fff5 */ 	bnez	$at,.L0f110520
/*  f11054c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f110550:	3c10800a */ 	lui	$s0,%hi(g_SoloSaveFile)
/*  f110554:	3c11800a */ 	lui	$s1,%hi(g_SoloSaveFile+0x4)
/*  f110558:	26312204 */ 	addiu	$s1,$s1,%lo(g_SoloSaveFile+0x4)
/*  f11055c:	26102200 */ 	addiu	$s0,$s0,%lo(g_SoloSaveFile)
/*  f110560:	02802025 */ 	or	$a0,$s4,$zero
.L0f110564:
/*  f110564:	920500b5 */ 	lbu	$a1,0xb5($s0)
/*  f110568:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f11056c:	24060008 */ 	addiu	$a2,$zero,0x8
/*  f110570:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f110574:	5611fffb */ 	bnel	$s0,$s1,.L0f110564
/*  f110578:	02802025 */ 	or	$a0,$s4,$zero
/*  f11057c:	0fc35531 */ 	jal	func0f0d54c4
/*  f110580:	02802025 */ 	or	$a0,$s4,$zero
/*  f110584:	27b90140 */ 	addiu	$t9,$sp,0x140
/*  f110588:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f11058c:	83a4014b */ 	lb	$a0,0x14b($sp)
/*  f110590:	8fa5014c */ 	lw	$a1,0x14c($sp)
/*  f110594:	24060080 */ 	addiu	$a2,$zero,0x80
/*  f110598:	27a70050 */ 	addiu	$a3,$sp,0x50
/*  f11059c:	0fc45a0a */ 	jal	func0f116828
/*  f1105a0:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f1105a4:	3c01800a */ 	lui	$at,%hi(var800a21f8)
/*  f1105a8:	14400009 */ 	bnez	$v0,.L0f1105d0
/*  f1105ac:	ac2221f8 */ 	sw	$v0,%lo(var800a21f8)($at)
/*  f1105b0:	8fa80140 */ 	lw	$t0,0x140($sp)
/*  f1105b4:	97a90152 */ 	lhu	$t1,0x152($sp)
/*  f1105b8:	3c03800a */ 	lui	$v1,%hi(var800a22c0)
/*  f1105bc:	246322c0 */ 	addiu	$v1,$v1,%lo(var800a22c0)
/*  f1105c0:	00001025 */ 	or	$v0,$zero,$zero
/*  f1105c4:	ac680000 */ 	sw	$t0,0x0($v1)
/*  f1105c8:	10000003 */ 	beqz	$zero,.L0f1105d8
/*  f1105cc:	a4690004 */ 	sh	$t1,0x4($v1)
.L0f1105d0:
/*  f1105d0:	10000001 */ 	beqz	$zero,.L0f1105d8
/*  f1105d4:	2402ffff */ 	addiu	$v0,$zero,-1
.L0f1105d8:
/*  f1105d8:	8fbf0034 */ 	lw	$ra,0x34($sp)
/*  f1105dc:	8fb0001c */ 	lw	$s0,0x1c($sp)
/*  f1105e0:	8fb10020 */ 	lw	$s1,0x20($sp)
/*  f1105e4:	8fb20024 */ 	lw	$s2,0x24($sp)
/*  f1105e8:	8fb30028 */ 	lw	$s3,0x28($sp)
/*  f1105ec:	8fb4002c */ 	lw	$s4,0x2c($sp)
/*  f1105f0:	8fb50030 */ 	lw	$s5,0x30($sp)
/*  f1105f4:	03e00008 */ 	jr	$ra
/*  f1105f8:	27bd0148 */ 	addiu	$sp,$sp,0x148
);

GLOBAL_ASM(
glabel func0f1105fc
/*  f1105fc:	27bdff08 */ 	addiu	$sp,$sp,-248
/*  f110600:	afa500fc */ 	sw	$a1,0xfc($sp)
/*  f110604:	00802825 */ 	or	$a1,$a0,$zero
/*  f110608:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f11060c:	afa400f8 */ 	sw	$a0,0xf8($sp)
/*  f110610:	afa60100 */ 	sw	$a2,0x100($sp)
/*  f110614:	afa70104 */ 	sw	$a3,0x104($sp)
/*  f110618:	2406000f */ 	addiu	$a2,$zero,0xf
/*  f11061c:	0fc35521 */ 	jal	func0f0d5484
/*  f110620:	27a40018 */ 	addiu	$a0,$sp,0x18
/*  f110624:	27a40018 */ 	addiu	$a0,$sp,0x18
/*  f110628:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f11062c:	0fc35539 */ 	jal	func0f0d54e4
/*  f110630:	00003025 */ 	or	$a2,$zero,$zero
/*  f110634:	27a40018 */ 	addiu	$a0,$sp,0x18
/*  f110638:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f11063c:	24050005 */ 	addiu	$a1,$zero,0x5
/*  f110640:	8fae0100 */ 	lw	$t6,0x100($sp)
/*  f110644:	27a40018 */ 	addiu	$a0,$sp,0x18
/*  f110648:	24050020 */ 	addiu	$a1,$zero,0x20
/*  f11064c:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f110650:	a1c20000 */ 	sb	$v0,0x0($t6)
/*  f110654:	8faf0108 */ 	lw	$t7,0x108($sp)
/*  f110658:	27a40018 */ 	addiu	$a0,$sp,0x18
/*  f11065c:	24050002 */ 	addiu	$a1,$zero,0x2
/*  f110660:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f110664:	ade20000 */ 	sw	$v0,0x0($t7)
/*  f110668:	8fb80104 */ 	lw	$t8,0x104($sp)
/*  f11066c:	a3020000 */ 	sb	$v0,0x0($t8)
/*  f110670:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f110674:	27bd00f8 */ 	addiu	$sp,$sp,0xf8
/*  f110678:	03e00008 */ 	jr	$ra
/*  f11067c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f110680:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*  f110684:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f110688:	0fc442da */ 	jal	func0f110b68
/*  f11068c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f110690:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f110694:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*  f110698:	03e00008 */ 	jr	$ra
/*  f11069c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1106a0:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*  f1106a4:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f1106a8:	0fc442da */ 	jal	func0f110b68
/*  f1106ac:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1106b0:	0fc44270 */ 	jal	func0f1109c0
/*  f1106b4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1106b8:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f1106bc:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*  f1106c0:	03e00008 */ 	jr	$ra
/*  f1106c4:	00000000 */ 	sll	$zero,$zero,0x0
);

GLOBAL_ASM(
glabel func0f1106c8
/*  f1106c8:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*  f1106cc:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f1106d0:	0fc44203 */ 	jal	func0f11080c
/*  f1106d4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1106d8:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f1106dc:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*  f1106e0:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f1106e4:	03e00008 */ 	jr	$ra
/*  f1106e8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1106ec:	03e00008 */ 	jr	$ra
/*  f1106f0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1106f4:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*  f1106f8:	00802825 */ 	or	$a1,$a0,$zero
/*  f1106fc:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f110700:	3c04800a */ 	lui	$a0,%hi(var800a22d0)
/*  f110704:	248422d0 */ 	addiu	$a0,$a0,%lo(var800a22d0)
/*  f110708:	0c012c5c */ 	jal	func0004b170
/*  f11070c:	2406005b */ 	addiu	$a2,$zero,0x5b
/*  f110710:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f110714:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*  f110718:	03e00008 */ 	jr	$ra
/*  f11071c:	00000000 */ 	sll	$zero,$zero,0x0
);

GLOBAL_ASM(
glabel func0f110720
/*  f110720:	27bdf7b0 */ 	addiu	$sp,$sp,-2128
/*  f110724:	afbf0024 */ 	sw	$ra,0x24($sp)
/*  f110728:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f11072c:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f110730:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f110734:	afa00038 */ 	sw	$zero,0x38($sp)
/*  f110738:	27a6003c */ 	addiu	$a2,$sp,0x3c
/*  f11073c:	24040004 */ 	addiu	$a0,$zero,0x4
/*  f110740:	0fc459ec */ 	jal	func0f1167b0
/*  f110744:	24050010 */ 	addiu	$a1,$zero,0x10
/*  f110748:	14400029 */ 	bnez	$v0,.L0f1107f0
/*  f11074c:	8fae003c */ 	lw	$t6,0x3c($sp)
/*  f110750:	11c00013 */ 	beqz	$t6,.L0f1107a0
/*  f110754:	00008825 */ 	or	$s1,$zero,$zero
/*  f110758:	27b0003c */ 	addiu	$s0,$sp,0x3c
/*  f11075c:	8e050000 */ 	lw	$a1,0x0($s0)
/*  f110760:	27b20840 */ 	addiu	$s2,$sp,0x840
/*  f110764:	24040004 */ 	addiu	$a0,$zero,0x4
.L0f110768:
/*  f110768:	0fc464da */ 	jal	func0f119368
/*  f11076c:	02403025 */ 	or	$a2,$s2,$zero
/*  f110770:	8fb8084c */ 	lw	$t8,0x84c($sp)
/*  f110774:	00184740 */ 	sll	$t0,$t8,0x1d
/*  f110778:	05020005 */ 	bltzl	$t0,.L0f110790
/*  f11077c:	8e050004 */ 	lw	$a1,0x4($s0)
/*  f110780:	8e090000 */ 	lw	$t1,0x0($s0)
/*  f110784:	10000006 */ 	beqz	$zero,.L0f1107a0
/*  f110788:	afa90038 */ 	sw	$t1,0x38($sp)
/*  f11078c:	8e050004 */ 	lw	$a1,0x4($s0)
.L0f110790:
/*  f110790:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f110794:	26100004 */ 	addiu	$s0,$s0,0x4
/*  f110798:	54a0fff3 */ 	bnezl	$a1,.L0f110768
/*  f11079c:	24040004 */ 	addiu	$a0,$zero,0x4
.L0f1107a0:
/*  f1107a0:	8faa003c */ 	lw	$t2,0x3c($sp)
/*  f1107a4:	27b20840 */ 	addiu	$s2,$sp,0x840
/*  f1107a8:	27b0003c */ 	addiu	$s0,$sp,0x3c
/*  f1107ac:	51400011 */ 	beqzl	$t2,.L0f1107f4
/*  f1107b0:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f1107b4:	8e050000 */ 	lw	$a1,0x0($s0)
/*  f1107b8:	24040004 */ 	addiu	$a0,$zero,0x4
.L0f1107bc:
/*  f1107bc:	0fc464da */ 	jal	func0f119368
/*  f1107c0:	02403025 */ 	or	$a2,$s2,$zero
/*  f1107c4:	8fac084c */ 	lw	$t4,0x84c($sp)
/*  f1107c8:	000c7740 */ 	sll	$t6,$t4,0x1d
/*  f1107cc:	05c30005 */ 	bgezl	$t6,.L0f1107e4
/*  f1107d0:	8e050004 */ 	lw	$a1,0x4($s0)
/*  f1107d4:	8e0f0000 */ 	lw	$t7,0x0($s0)
/*  f1107d8:	10000005 */ 	beqz	$zero,.L0f1107f0
/*  f1107dc:	afaf0038 */ 	sw	$t7,0x38($sp)
/*  f1107e0:	8e050004 */ 	lw	$a1,0x4($s0)
.L0f1107e4:
/*  f1107e4:	26100004 */ 	addiu	$s0,$s0,0x4
/*  f1107e8:	54a0fff4 */ 	bnezl	$a1,.L0f1107bc
/*  f1107ec:	24040004 */ 	addiu	$a0,$zero,0x4
.L0f1107f0:
/*  f1107f0:	8fbf0024 */ 	lw	$ra,0x24($sp)
.L0f1107f4:
/*  f1107f4:	8fa20038 */ 	lw	$v0,0x38($sp)
/*  f1107f8:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f1107fc:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f110800:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f110804:	03e00008 */ 	jr	$ra
/*  f110808:	27bd0850 */ 	addiu	$sp,$sp,0x850
);

GLOBAL_ASM(
glabel func0f11080c
/*  f11080c:	27bdfed8 */ 	addiu	$sp,$sp,-296
/*  f110810:	afbf0024 */ 	sw	$ra,0x24($sp)
/*  f110814:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f110818:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f11081c:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f110820:	0fc441c8 */ 	jal	func0f110720
/*  f110824:	afa00124 */ 	sw	$zero,0x124($sp)
/*  f110828:	14400005 */ 	bnez	$v0,.L0f110840
/*  f11082c:	00408025 */ 	or	$s0,$v0,$zero
/*  f110830:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f110834:	afae0124 */ 	sw	$t6,0x124($sp)
/*  f110838:	1000000c */ 	beqz	$zero,.L0f11086c
/*  f11083c:	27b20044 */ 	addiu	$s2,$sp,0x44
.L0f110840:
/*  f110840:	27b20044 */ 	addiu	$s2,$sp,0x44
/*  f110844:	0fc35517 */ 	jal	func0f0d545c
/*  f110848:	02402025 */ 	or	$a0,$s2,$zero
/*  f11084c:	24040004 */ 	addiu	$a0,$zero,0x4
/*  f110850:	02002825 */ 	or	$a1,$s0,$zero
/*  f110854:	27a60048 */ 	addiu	$a2,$sp,0x48
/*  f110858:	0fc45a00 */ 	jal	func0f116800
/*  f11085c:	00003825 */ 	or	$a3,$zero,$zero
/*  f110860:	10400002 */ 	beqz	$v0,.L0f11086c
/*  f110864:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f110868:	afaf0124 */ 	sw	$t7,0x124($sp)
.L0f11086c:
/*  f11086c:	8fb80124 */ 	lw	$t8,0x124($sp)
/*  f110870:	02402025 */ 	or	$a0,$s2,$zero
/*  f110874:	57000046 */ 	bnezl	$t8,.L0f110990
/*  f110878:	8faa0124 */ 	lw	$t2,0x124($sp)
/*  f11087c:	0fc355e7 */ 	jal	func0f0d579c
/*  f110880:	27a50034 */ 	addiu	$a1,$sp,0x34
/*  f110884:	8fb90034 */ 	lw	$t9,0x34($sp)
/*  f110888:	97a80038 */ 	lhu	$t0,0x38($sp)
/*  f11088c:	3c11800a */ 	lui	$s1,%hi(g_Vars)
/*  f110890:	26319fc0 */ 	addiu	$s1,$s1,%lo(g_Vars)
/*  f110894:	02402025 */ 	or	$a0,$s2,$zero
/*  f110898:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f11089c:	ae39047c */ 	sw	$t9,0x47c($s1)
/*  f1108a0:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f1108a4:	a6280480 */ 	sh	$t0,0x480($s1)
/*  f1108a8:	3c01800b */ 	lui	$at,%hi(g_MpSetup+0x89)
/*  f1108ac:	a022cc11 */ 	sb	$v0,%lo(g_MpSetup+0x89)($at)
/*  f1108b0:	02402025 */ 	or	$a0,$s2,$zero
/*  f1108b4:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f1108b8:	24050004 */ 	addiu	$a1,$zero,0x4
/*  f1108bc:	a6220482 */ 	sh	$v0,0x482($s1)
/*  f1108c0:	3c11800b */ 	lui	$s1,%hi(g_MpSetup+0x88)
/*  f1108c4:	3c10800b */ 	lui	$s0,%hi(g_MpSetup+0x28)
/*  f1108c8:	2610cbb0 */ 	addiu	$s0,$s0,%lo(g_MpSetup+0x28)
/*  f1108cc:	2631cc10 */ 	addiu	$s1,$s1,%lo(g_MpSetup+0x88)
/*  f1108d0:	02402025 */ 	or	$a0,$s2,$zero
.L0f1108d4:
/*  f1108d4:	02002825 */ 	or	$a1,$s0,$zero
/*  f1108d8:	0fc35539 */ 	jal	func0f0d54e4
/*  f1108dc:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f1108e0:	2610000c */ 	addiu	$s0,$s0,0xc
/*  f1108e4:	0211082b */ 	sltu	$at,$s0,$s1
/*  f1108e8:	5420fffa */ 	bnezl	$at,.L0f1108d4
/*  f1108ec:	02402025 */ 	or	$a0,$s2,$zero
/*  f1108f0:	02402025 */ 	or	$a0,$s2,$zero
/*  f1108f4:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f1108f8:	24050008 */ 	addiu	$a1,$zero,0x8
/*  f1108fc:	304300ff */ 	andi	$v1,$v0,0xff
/*  f110900:	240100ff */ 	addiu	$at,$zero,0xff
/*  f110904:	14610005 */ 	bne	$v1,$at,.L0f11091c
/*  f110908:	3c10800b */ 	lui	$s0,%hi(g_MpSetup+0x28)
/*  f11090c:	2409ffff */ 	addiu	$t1,$zero,-1
/*  f110910:	3c01800b */ 	lui	$at,%hi(var800acc14)
/*  f110914:	10000003 */ 	beqz	$zero,.L0f110924
/*  f110918:	a029cc14 */ 	sb	$t1,%lo(var800acc14)($at)
.L0f11091c:
/*  f11091c:	3c01800b */ 	lui	$at,%hi(var800acc14)
/*  f110920:	a023cc14 */ 	sb	$v1,%lo(var800acc14)($at)
.L0f110924:
/*  f110924:	3c11800b */ 	lui	$s1,%hi(g_MpSetup+0x2e)
/*  f110928:	2631cbb6 */ 	addiu	$s1,$s1,%lo(g_MpSetup+0x2e)
/*  f11092c:	2610cbb0 */ 	addiu	$s0,$s0,%lo(g_MpSetup+0x28)
.L0f110930:
/*  f110930:	02402025 */ 	or	$a0,$s2,$zero
/*  f110934:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f110938:	24050008 */ 	addiu	$a1,$zero,0x8
/*  f11093c:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f110940:	1611fffb */ 	bne	$s0,$s1,.L0f110930
/*  f110944:	a2020064 */ 	sb	$v0,0x64($s0)
/*  f110948:	02402025 */ 	or	$a0,$s2,$zero
/*  f11094c:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f110950:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f110954:	3c01800b */ 	lui	$at,%hi(g_MpSetup+0x8a)
/*  f110958:	a022cc12 */ 	sb	$v0,%lo(g_MpSetup+0x8a)($at)
/*  f11095c:	02402025 */ 	or	$a0,$s2,$zero
/*  f110960:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f110964:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f110968:	3c01800a */ 	lui	$at,%hi(var800a2328+0x3)
/*  f11096c:	a022232b */ 	sb	$v0,%lo(var800a2328+0x3)($at)
/*  f110970:	02402025 */ 	or	$a0,$s2,$zero
/*  f110974:	0fc354fe */ 	jal	scenarioDefaultCallback40
/*  f110978:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f11097c:	3c01800a */ 	lui	$at,%hi(g_AltTitle)
/*  f110980:	a022232c */ 	sb	$v0,%lo(g_AltTitle)($at)
/*  f110984:	0fc35531 */ 	jal	func0f0d54c4
/*  f110988:	02402025 */ 	or	$a0,$s2,$zero
/*  f11098c:	8faa0124 */ 	lw	$t2,0x124($sp)
.L0f110990:
/*  f110990:	51400006 */ 	beqzl	$t2,.L0f1109ac
/*  f110994:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f110998:	0fc442da */ 	jal	func0f110b68
/*  f11099c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1109a0:	0fc44270 */ 	jal	func0f1109c0
/*  f1109a4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1109a8:	8fbf0024 */ 	lw	$ra,0x24($sp)
.L0f1109ac:
/*  f1109ac:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f1109b0:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f1109b4:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f1109b8:	03e00008 */ 	jr	$ra
/*  f1109bc:	27bd0128 */ 	addiu	$sp,$sp,0x128
);

GLOBAL_ASM(
glabel func0f1109c0
/*  f1109c0:	27bdfed0 */ 	addiu	$sp,$sp,-304
/*  f1109c4:	afb20028 */ 	sw	$s2,0x28($sp)
/*  f1109c8:	27b2004c */ 	addiu	$s2,$sp,0x4c
/*  f1109cc:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f1109d0:	afb10024 */ 	sw	$s1,0x24($sp)
/*  f1109d4:	afb00020 */ 	sw	$s0,0x20($sp)
/*  f1109d8:	afa0012c */ 	sw	$zero,0x12c($sp)
/*  f1109dc:	0fc35517 */ 	jal	func0f0d545c
/*  f1109e0:	02402025 */ 	or	$a0,$s2,$zero
/*  f1109e4:	3c10800a */ 	lui	$s0,%hi(g_Vars)
/*  f1109e8:	26109fc0 */ 	addiu	$s0,$s0,%lo(g_Vars)
/*  f1109ec:	8e0e047c */ 	lw	$t6,0x47c($s0)
/*  f1109f0:	960f0480 */ 	lhu	$t7,0x480($s0)
/*  f1109f4:	02402025 */ 	or	$a0,$s2,$zero
/*  f1109f8:	27a50044 */ 	addiu	$a1,$sp,0x44
/*  f1109fc:	afae0044 */ 	sw	$t6,0x44($sp)
/*  f110a00:	0fc355d7 */ 	jal	func0f0d575c
/*  f110a04:	a7af0048 */ 	sh	$t7,0x48($sp)
/*  f110a08:	3c05800b */ 	lui	$a1,%hi(g_MpSetup+0x89)
/*  f110a0c:	90a5cc11 */ 	lbu	$a1,%lo(g_MpSetup+0x89)($a1)
/*  f110a10:	02402025 */ 	or	$a0,$s2,$zero
/*  f110a14:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f110a18:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f110a1c:	02402025 */ 	or	$a0,$s2,$zero
/*  f110a20:	96050482 */ 	lhu	$a1,0x482($s0)
/*  f110a24:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f110a28:	24060004 */ 	addiu	$a2,$zero,0x4
/*  f110a2c:	3c10800b */ 	lui	$s0,%hi(g_MpSetup+0x28)
/*  f110a30:	3c11800b */ 	lui	$s1,%hi(g_MpSetup+0x88)
/*  f110a34:	2631cc10 */ 	addiu	$s1,$s1,%lo(g_MpSetup+0x88)
/*  f110a38:	2610cbb0 */ 	addiu	$s0,$s0,%lo(g_MpSetup+0x28)
/*  f110a3c:	02402025 */ 	or	$a0,$s2,$zero
.L0f110a40:
/*  f110a40:	0fc35569 */ 	jal	func0f0d55a4
/*  f110a44:	02002825 */ 	or	$a1,$s0,$zero
/*  f110a48:	2610000c */ 	addiu	$s0,$s0,0xc
/*  f110a4c:	0211082b */ 	sltu	$at,$s0,$s1
/*  f110a50:	5420fffb */ 	bnezl	$at,.L0f110a40
/*  f110a54:	02402025 */ 	or	$a0,$s2,$zero
/*  f110a58:	3c02800b */ 	lui	$v0,%hi(var800acc14)
/*  f110a5c:	8042cc14 */ 	lb	$v0,%lo(var800acc14)($v0)
/*  f110a60:	2401ffff */ 	addiu	$at,$zero,-1
/*  f110a64:	02402025 */ 	or	$a0,$s2,$zero
/*  f110a68:	14410007 */ 	bne	$v0,$at,.L0f110a88
/*  f110a6c:	00402825 */ 	or	$a1,$v0,$zero
/*  f110a70:	02402025 */ 	or	$a0,$s2,$zero
/*  f110a74:	240500ff */ 	addiu	$a1,$zero,0xff
/*  f110a78:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f110a7c:	24060008 */ 	addiu	$a2,$zero,0x8
/*  f110a80:	10000003 */ 	beqz	$zero,.L0f110a90
/*  f110a84:	00000000 */ 	sll	$zero,$zero,0x0
.L0f110a88:
/*  f110a88:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f110a8c:	24060008 */ 	addiu	$a2,$zero,0x8
.L0f110a90:
/*  f110a90:	3c10800b */ 	lui	$s0,%hi(g_MpSetup+0x28)
/*  f110a94:	3c11800b */ 	lui	$s1,%hi(g_MpSetup+0x2e)
/*  f110a98:	2631cbb6 */ 	addiu	$s1,$s1,%lo(g_MpSetup+0x2e)
/*  f110a9c:	2610cbb0 */ 	addiu	$s0,$s0,%lo(g_MpSetup+0x28)
/*  f110aa0:	02402025 */ 	or	$a0,$s2,$zero
.L0f110aa4:
/*  f110aa4:	92050065 */ 	lbu	$a1,0x65($s0)
/*  f110aa8:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f110aac:	24060008 */ 	addiu	$a2,$zero,0x8
/*  f110ab0:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f110ab4:	5611fffb */ 	bnel	$s0,$s1,.L0f110aa4
/*  f110ab8:	02402025 */ 	or	$a0,$s2,$zero
/*  f110abc:	3c05800b */ 	lui	$a1,%hi(g_MpSetup+0x8a)
/*  f110ac0:	90a5cc12 */ 	lbu	$a1,%lo(g_MpSetup+0x8a)($a1)
/*  f110ac4:	02402025 */ 	or	$a0,$s2,$zero
/*  f110ac8:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f110acc:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f110ad0:	3c05800a */ 	lui	$a1,%hi(var800a2328+0x3)
/*  f110ad4:	90a5232b */ 	lbu	$a1,%lo(var800a2328+0x3)($a1)
/*  f110ad8:	02402025 */ 	or	$a0,$s2,$zero
/*  f110adc:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f110ae0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f110ae4:	3c05800a */ 	lui	$a1,%hi(g_AltTitle)
/*  f110ae8:	90a5232c */ 	lbu	$a1,%lo(g_AltTitle)($a1)
/*  f110aec:	02402025 */ 	or	$a0,$s2,$zero
/*  f110af0:	0fc354be */ 	jal	scenarioDefaultCallback44
/*  f110af4:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f110af8:	0fc35531 */ 	jal	func0f0d54c4
/*  f110afc:	02402025 */ 	or	$a0,$s2,$zero
/*  f110b00:	0fc441c8 */ 	jal	func0f110720
/*  f110b04:	00000000 */ 	sll	$zero,$zero,0x0
/*  f110b08:	14400007 */ 	bnez	$v0,.L0f110b28
/*  f110b0c:	00408025 */ 	or	$s0,$v0,$zero
/*  f110b10:	3c047f1b */ 	lui	$a0,%hi(var7f1b39b0)
/*  f110b14:	3c057f1b */ 	lui	$a1,%hi(var7f1b39bc)
/*  f110b18:	24a539bc */ 	addiu	$a1,$a1,%lo(var7f1b39bc)
/*  f110b1c:	248439b0 */ 	addiu	$a0,$a0,%lo(var7f1b39b0)
/*  f110b20:	0c002ff4 */ 	jal	func0000bfd0
/*  f110b24:	24060177 */ 	addiu	$a2,$zero,0x177
.L0f110b28:
/*  f110b28:	24040004 */ 	addiu	$a0,$zero,0x4
/*  f110b2c:	02002825 */ 	or	$a1,$s0,$zero
/*  f110b30:	24060010 */ 	addiu	$a2,$zero,0x10
/*  f110b34:	27a70050 */ 	addiu	$a3,$sp,0x50
/*  f110b38:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f110b3c:	0fc45a0a */ 	jal	func0f116828
/*  f110b40:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f110b44:	10400002 */ 	beqz	$v0,.L0f110b50
/*  f110b48:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f110b4c:	afb8012c */ 	sw	$t8,0x12c($sp)
.L0f110b50:
/*  f110b50:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f110b54:	8fb00020 */ 	lw	$s0,0x20($sp)
/*  f110b58:	8fb10024 */ 	lw	$s1,0x24($sp)
/*  f110b5c:	8fb20028 */ 	lw	$s2,0x28($sp)
/*  f110b60:	03e00008 */ 	jr	$ra
/*  f110b64:	27bd0130 */ 	addiu	$sp,$sp,0x130
);

GLOBAL_ASM(
glabel func0f110b68
/*  f110b68:	3c02800b */ 	lui	$v0,%hi(g_MpSetup+0x28)
/*  f110b6c:	2442cbb0 */ 	addiu	$v0,$v0,%lo(g_MpSetup+0x28)
/*  f110b70:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*  f110b74:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f110b78:	240effff */ 	addiu	$t6,$zero,-1
/*  f110b7c:	a0400000 */ 	sb	$zero,0x0($v0)
/*  f110b80:	a040000c */ 	sb	$zero,0xc($v0)
/*  f110b84:	a0400018 */ 	sb	$zero,0x18($v0)
/*  f110b88:	a0400024 */ 	sb	$zero,0x24($v0)
/*  f110b8c:	a0400030 */ 	sb	$zero,0x30($v0)
/*  f110b90:	a040003c */ 	sb	$zero,0x3c($v0)
/*  f110b94:	a0400048 */ 	sb	$zero,0x48($v0)
/*  f110b98:	a0400054 */ 	sb	$zero,0x54($v0)
/*  f110b9c:	0fc630f9 */ 	jal	func0f18c3e4
/*  f110ba0:	a04e0064 */ 	sb	$t6,0x64($v0)
/*  f110ba4:	3c02800b */ 	lui	$v0,%hi(g_MpSetup+0x28)
/*  f110ba8:	3c03800a */ 	lui	$v1,%hi(g_Vars)
/*  f110bac:	24639fc0 */ 	addiu	$v1,$v1,%lo(g_Vars)
/*  f110bb0:	2442cbb0 */ 	addiu	$v0,$v0,%lo(g_MpSetup+0x28)
/*  f110bb4:	a0400062 */ 	sb	$zero,0x62($v0)
/*  f110bb8:	a0400061 */ 	sb	$zero,0x61($v0)
/*  f110bbc:	a0400060 */ 	sb	$zero,0x60($v0)
/*  f110bc0:	ac60047c */ 	sw	$zero,0x47c($v1)
/*  f110bc4:	a4600480 */ 	sh	$zero,0x480($v1)
/*  f110bc8:	a4600482 */ 	sh	$zero,0x482($v1)
/*  f110bcc:	3c01800a */ 	lui	$at,%hi(var800a2328+0x3)
/*  f110bd0:	a020232b */ 	sb	$zero,%lo(var800a2328+0x3)($at)
/*  f110bd4:	3c01800a */ 	lui	$at,%hi(g_AltTitle)
/*  f110bd8:	0fc44270 */ 	jal	func0f1109c0
/*  f110bdc:	a020232c */ 	sb	$zero,%lo(g_AltTitle)($at)
/*  f110be0:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f110be4:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*  f110be8:	03e00008 */ 	jr	$ra
/*  f110bec:	00000000 */ 	sll	$zero,$zero,0x0
);

void func0f110bf0(void)
{
	// empty
}

GLOBAL_ASM(
glabel func0f110bf8
/*  f110bf8:	27bdffe0 */ 	addiu	$sp,$sp,-32
/*  f110bfc:	afb10018 */ 	sw	$s1,0x18($sp)
/*  f110c00:	afb00014 */ 	sw	$s0,0x14($sp)
/*  f110c04:	3c108007 */ 	lui	$s0,%hi(g_SaveLocations)
/*  f110c08:	3c118007 */ 	lui	$s1,%hi(var80075bd0)
/*  f110c0c:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f110c10:	26315bd0 */ 	addiu	$s1,$s1,%lo(var80075bd0)
/*  f110c14:	26105bc0 */ 	addiu	$s0,$s0,%lo(g_SaveLocations)
/*  f110c18:	8e0e0000 */ 	lw	$t6,0x0($s0)
.L0f110c1c:
/*  f110c1c:	51c00008 */ 	beqzl	$t6,.L0f110c40
/*  f110c20:	26100004 */ 	addiu	$s0,$s0,0x4
/*  f110c24:	0fc5db69 */ 	jal	func0f176da4
/*  f110c28:	24040310 */ 	addiu	$a0,$zero,0x310
/*  f110c2c:	8e040000 */ 	lw	$a0,0x0($s0)
/*  f110c30:	0c004b2d */ 	jal	func00012cb4
/*  f110c34:	00402825 */ 	or	$a1,$v0,$zero
/*  f110c38:	ae000000 */ 	sw	$zero,0x0($s0)
/*  f110c3c:	26100004 */ 	addiu	$s0,$s0,0x4
.L0f110c40:
/*  f110c40:	5611fff6 */ 	bnel	$s0,$s1,.L0f110c1c
/*  f110c44:	8e0e0000 */ 	lw	$t6,0x0($s0)
/*  f110c48:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f110c4c:	8fb00014 */ 	lw	$s0,0x14($sp)
/*  f110c50:	8fb10018 */ 	lw	$s1,0x18($sp)
/*  f110c54:	03e00008 */ 	jr	$ra
/*  f110c58:	27bd0020 */ 	addiu	$sp,$sp,0x20
);

GLOBAL_ASM(
glabel func0f110c5c
/*  f110c5c:	3c0f8007 */ 	lui	$t7,%hi(g_SaveLocations)
/*  f110c60:	25ef5bc0 */ 	addiu	$t7,$t7,%lo(g_SaveLocations)
/*  f110c64:	00047080 */ 	sll	$t6,$a0,0x2
/*  f110c68:	01cf3021 */ 	addu	$a2,$t6,$t7
/*  f110c6c:	8cc30000 */ 	lw	$v1,0x0($a2)
/*  f110c70:	27bdffe0 */ 	addiu	$sp,$sp,-32
/*  f110c74:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f110c78:	1460000e */ 	bnez	$v1,.L0f110cb4
/*  f110c7c:	afa50024 */ 	sw	$a1,0x24($sp)
/*  f110c80:	24040310 */ 	addiu	$a0,$zero,0x310
/*  f110c84:	0fc5db69 */ 	jal	func0f176da4
/*  f110c88:	afa60018 */ 	sw	$a2,0x18($sp)
/*  f110c8c:	00402025 */ 	or	$a0,$v0,$zero
/*  f110c90:	0fc5796e */ 	jal	func0f15e5b8
/*  f110c94:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f110c98:	0fc5db69 */ 	jal	func0f176da4
/*  f110c9c:	24040310 */ 	addiu	$a0,$zero,0x310
/*  f110ca0:	0c004aac */ 	jal	func00012ab0
/*  f110ca4:	00402025 */ 	or	$a0,$v0,$zero
/*  f110ca8:	8fa60018 */ 	lw	$a2,0x18($sp)
/*  f110cac:	00401825 */ 	or	$v1,$v0,$zero
/*  f110cb0:	acc20000 */ 	sw	$v0,0x0($a2)
.L0f110cb4:
/*  f110cb4:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f110cb8:	a078030c */ 	sb	$t8,0x30c($v1)
/*  f110cbc:	8cc80000 */ 	lw	$t0,0x0($a2)
/*  f110cc0:	93b90027 */ 	lbu	$t9,0x27($sp)
/*  f110cc4:	3c098006 */ 	lui	$t1,%hi(var80062944)
/*  f110cc8:	a119030b */ 	sb	$t9,0x30b($t0)
/*  f110ccc:	91292944 */ 	lbu	$t1,%lo(var80062944)($t1)
/*  f110cd0:	55200004 */ 	bnezl	$t1,.L0f110ce4
/*  f110cd4:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f110cd8:	0c004e63 */ 	jal	func0001398c
/*  f110cdc:	24040003 */ 	addiu	$a0,$zero,0x3
/*  f110ce0:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0f110ce4:
/*  f110ce4:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f110ce8:	3c018006 */ 	lui	$at,%hi(var80062944)
/*  f110cec:	a02a2944 */ 	sb	$t2,%lo(var80062944)($at)
/*  f110cf0:	03e00008 */ 	jr	$ra
/*  f110cf4:	27bd0020 */ 	addiu	$sp,$sp,0x20
);

GLOBAL_ASM(
glabel func0f110cf8
/*  f110cf8:	27bdffd8 */ 	addiu	$sp,$sp,-40
/*  f110cfc:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f110d00:	309000ff */ 	andi	$s0,$a0,0xff
/*  f110d04:	afa40028 */ 	sw	$a0,0x28($sp)
/*  f110d08:	3c058007 */ 	lui	$a1,%hi(g_SaveLocations)
/*  f110d0c:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f110d10:	2406ffff */ 	addiu	$a2,$zero,-1
/*  f110d14:	24a55bc0 */ 	addiu	$a1,$a1,%lo(g_SaveLocations)
/*  f110d18:	24040004 */ 	addiu	$a0,$zero,0x4
/*  f110d1c:	00001825 */ 	or	$v1,$zero,$zero
/*  f110d20:	2407ffff */ 	addiu	$a3,$zero,-1
.L0f110d24:
/*  f110d24:	8ca20000 */ 	lw	$v0,0x0($a1)
/*  f110d28:	10400006 */ 	beqz	$v0,.L0f110d44
/*  f110d2c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f110d30:	904e030b */ 	lbu	$t6,0x30b($v0)
/*  f110d34:	560e0007 */ 	bnel	$s0,$t6,.L0f110d54
/*  f110d38:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f110d3c:	1000000f */ 	beqz	$zero,.L0f110d7c
/*  f110d40:	00601025 */ 	or	$v0,$v1,$zero
.L0f110d44:
/*  f110d44:	54c70003 */ 	bnel	$a2,$a3,.L0f110d54
/*  f110d48:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f110d4c:	00603025 */ 	or	$a2,$v1,$zero
/*  f110d50:	24630001 */ 	addiu	$v1,$v1,0x1
.L0f110d54:
/*  f110d54:	1464fff3 */ 	bne	$v1,$a0,.L0f110d24
/*  f110d58:	24a50004 */ 	addiu	$a1,$a1,0x4
/*  f110d5c:	04c00007 */ 	bltz	$a2,.L0f110d7c
/*  f110d60:	2402ffff */ 	addiu	$v0,$zero,-1
/*  f110d64:	00c02025 */ 	or	$a0,$a2,$zero
/*  f110d68:	320500ff */ 	andi	$a1,$s0,0xff
/*  f110d6c:	0fc44317 */ 	jal	func0f110c5c
/*  f110d70:	afa60024 */ 	sw	$a2,0x24($sp)
/*  f110d74:	10000001 */ 	beqz	$zero,.L0f110d7c
/*  f110d78:	8fa20024 */ 	lw	$v0,0x24($sp)
.L0f110d7c:
/*  f110d7c:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f110d80:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f110d84:	27bd0028 */ 	addiu	$sp,$sp,0x28
/*  f110d88:	03e00008 */ 	jr	$ra
/*  f110d8c:	00000000 */ 	sll	$zero,$zero,0x0
);

GLOBAL_ASM(
glabel func0f110d90
/*  f110d90:	00047880 */ 	sll	$t7,$a0,0x2
/*  f110d94:	3c01800a */ 	lui	$at,%hi(var800a2330)
/*  f110d98:	002f0821 */ 	addu	$at,$at,$t7
/*  f110d9c:	240effff */ 	addiu	$t6,$zero,-1
/*  f110da0:	03e00008 */ 	jr	$ra
/*  f110da4:	ac2e2330 */ 	sw	$t6,%lo(var800a2330)($at)
);

GLOBAL_ASM(
glabel func0f110da8
/*  f110da8:	27bdffd0 */ 	addiu	$sp,$sp,-48
/*  f110dac:	3c0e8007 */ 	lui	$t6,%hi(var80075bf4)
/*  f110db0:	8dce5bf4 */ 	lw	$t6,%lo(var80075bf4)($t6)
/*  f110db4:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f110db8:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f110dbc:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f110dc0:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f110dc4:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f110dc8:	15c0000c */ 	bnez	$t6,.L0f110dfc
/*  f110dcc:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f110dd0:	3c10800a */ 	lui	$s0,%hi(var800a2330)
/*  f110dd4:	3c03800a */ 	lui	$v1,%hi(var800a2344)
/*  f110dd8:	24632344 */ 	addiu	$v1,$v1,%lo(var800a2344)
/*  f110ddc:	26102330 */ 	addiu	$s0,$s0,%lo(var800a2330)
/*  f110de0:	2402ffff */ 	addiu	$v0,$zero,-1
.L0f110de4:
/*  f110de4:	26100004 */ 	addiu	$s0,$s0,0x4
/*  f110de8:	1603fffe */ 	bne	$s0,$v1,.L0f110de4
/*  f110dec:	ae02fffc */ 	sw	$v0,-0x4($s0)
/*  f110df0:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f110df4:	3c018007 */ 	lui	$at,%hi(var80075bf4)
/*  f110df8:	ac2f5bf4 */ 	sw	$t7,%lo(var80075bf4)($at)
.L0f110dfc:
/*  f110dfc:	00009025 */ 	or	$s2,$zero,$zero
/*  f110e00:	00009825 */ 	or	$s3,$zero,$zero
/*  f110e04:	00128e00 */ 	sll	$s1,$s2,0x18
.L0f110e08:
/*  f110e08:	0011c603 */ 	sra	$t8,$s1,0x18
/*  f110e0c:	00182600 */ 	sll	$a0,$t8,0x18
/*  f110e10:	0004ce03 */ 	sra	$t9,$a0,0x18
/*  f110e14:	03202025 */ 	or	$a0,$t9,$zero
/*  f110e18:	0fc459f6 */ 	jal	func0f1167d8
/*  f110e1c:	03008825 */ 	or	$s1,$t8,$zero
/*  f110e20:	10400010 */ 	beqz	$v0,.L0f110e64
/*  f110e24:	00112600 */ 	sll	$a0,$s1,0x18
/*  f110e28:	3c0a800a */ 	lui	$t2,%hi(var800a2330)
/*  f110e2c:	254a2330 */ 	addiu	$t2,$t2,%lo(var800a2330)
/*  f110e30:	00044603 */ 	sra	$t0,$a0,0x18
/*  f110e34:	00124880 */ 	sll	$t1,$s2,0x2
/*  f110e38:	012a8021 */ 	addu	$s0,$t1,$t2
/*  f110e3c:	0fc45c0b */ 	jal	func0f11702c
/*  f110e40:	01002025 */ 	or	$a0,$t0,$zero
/*  f110e44:	8e0b0000 */ 	lw	$t3,0x0($s0)
/*  f110e48:	00112600 */ 	sll	$a0,$s1,0x18
/*  f110e4c:	00046603 */ 	sra	$t4,$a0,0x18
/*  f110e50:	104b0004 */ 	beq	$v0,$t3,.L0f110e64
/*  f110e54:	01802025 */ 	or	$a0,$t4,$zero
/*  f110e58:	0fc45c0b */ 	jal	func0f11702c
/*  f110e5c:	24130001 */ 	addiu	$s3,$zero,0x1
/*  f110e60:	ae020000 */ 	sw	$v0,0x0($s0)
.L0f110e64:
/*  f110e64:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f110e68:	2a410005 */ 	slti	$at,$s2,0x5
/*  f110e6c:	5420ffe6 */ 	bnezl	$at,.L0f110e08
/*  f110e70:	00128e00 */ 	sll	$s1,$s2,0x18
/*  f110e74:	3c108007 */ 	lui	$s0,%hi(g_SaveLocations)
/*  f110e78:	3c148007 */ 	lui	$s4,%hi(var80075bd0)
/*  f110e7c:	3c118007 */ 	lui	$s1,%hi(var80075bd0)
/*  f110e80:	26315bd0 */ 	addiu	$s1,$s1,%lo(var80075bd0)
/*  f110e84:	26945bd0 */ 	addiu	$s4,$s4,%lo(var80075bd0)
/*  f110e88:	26105bc0 */ 	addiu	$s0,$s0,%lo(g_SaveLocations)
/*  f110e8c:	24120001 */ 	addiu	$s2,$zero,0x1
/*  f110e90:	8e040000 */ 	lw	$a0,0x0($s0)
.L0f110e94:
/*  f110e94:	5080001b */ 	beqzl	$a0,.L0f110f04
/*  f110e98:	26100004 */ 	addiu	$s0,$s0,0x4
/*  f110e9c:	a080030e */ 	sb	$zero,0x30e($a0)
/*  f110ea0:	8e040000 */ 	lw	$a0,0x0($s0)
/*  f110ea4:	02601825 */ 	or	$v1,$s3,$zero
/*  f110ea8:	9082030c */ 	lbu	$v0,0x30c($a0)
/*  f110eac:	18400007 */ 	blez	$v0,.L0f110ecc
/*  f110eb0:	244dffff */ 	addiu	$t5,$v0,-1
/*  f110eb4:	a08d030c */ 	sb	$t5,0x30c($a0)
/*  f110eb8:	8e040000 */ 	lw	$a0,0x0($s0)
/*  f110ebc:	908e030c */ 	lbu	$t6,0x30c($a0)
/*  f110ec0:	55c00003 */ 	bnezl	$t6,.L0f110ed0
/*  f110ec4:	908f030b */ 	lbu	$t7,0x30b($a0)
/*  f110ec8:	02401825 */ 	or	$v1,$s2,$zero
.L0f110ecc:
/*  f110ecc:	908f030b */ 	lbu	$t7,0x30b($a0)
.L0f110ed0:
/*  f110ed0:	000fc080 */ 	sll	$t8,$t7,0x2
/*  f110ed4:	0238c821 */ 	addu	$t9,$s1,$t8
/*  f110ed8:	8f280000 */ 	lw	$t0,0x0($t9)
/*  f110edc:	11000002 */ 	beqz	$t0,.L0f110ee8
/*  f110ee0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f110ee4:	02401825 */ 	or	$v1,$s2,$zero
.L0f110ee8:
/*  f110ee8:	50600006 */ 	beqzl	$v1,.L0f110f04
/*  f110eec:	26100004 */ 	addiu	$s0,$s0,0x4
/*  f110ef0:	0fc443d3 */ 	jal	func0f110f4c
/*  f110ef4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f110ef8:	8e090000 */ 	lw	$t1,0x0($s0)
/*  f110efc:	a132030e */ 	sb	$s2,0x30e($t1)
/*  f110f00:	26100004 */ 	addiu	$s0,$s0,0x4
.L0f110f04:
/*  f110f04:	0214082b */ 	sltu	$at,$s0,$s4
/*  f110f08:	5420ffe2 */ 	bnezl	$at,.L0f110e94
/*  f110f0c:	8e040000 */ 	lw	$a0,0x0($s0)
/*  f110f10:	3c028007 */ 	lui	$v0,%hi(var80075bd0)
/*  f110f14:	3c038007 */ 	lui	$v1,%hi(var80075be0)
/*  f110f18:	24635be0 */ 	addiu	$v1,$v1,%lo(var80075be0)
/*  f110f1c:	24425bd0 */ 	addiu	$v0,$v0,%lo(var80075bd0)
.L0f110f20:
/*  f110f20:	24420004 */ 	addiu	$v0,$v0,0x4
/*  f110f24:	1443fffe */ 	bne	$v0,$v1,.L0f110f20
/*  f110f28:	ac40fffc */ 	sw	$zero,-0x4($v0)
/*  f110f2c:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f110f30:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f110f34:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f110f38:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f110f3c:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f110f40:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f110f44:	03e00008 */ 	jr	$ra
/*  f110f48:	27bd0030 */ 	addiu	$sp,$sp,0x30
);

GLOBAL_ASM(
glabel func0f110f4c
/*  f110f4c:	27bdc568 */ 	addiu	$sp,$sp,-15000
/*  f110f50:	3c0e7f1b */ 	lui	$t6,%hi(var7f1b39e8)
/*  f110f54:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f110f58:	afbe0038 */ 	sw	$s8,0x38($sp)
/*  f110f5c:	afb70034 */ 	sw	$s7,0x34($sp)
/*  f110f60:	afb60030 */ 	sw	$s6,0x30($sp)
/*  f110f64:	afb5002c */ 	sw	$s5,0x2c($sp)
/*  f110f68:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f110f6c:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f110f70:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f110f74:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f110f78:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f110f7c:	25ce39e8 */ 	addiu	$t6,$t6,%lo(var7f1b39e8)
/*  f110f80:	8dc10000 */ 	lw	$at,0x0($t6)
/*  f110f84:	27b43a88 */ 	addiu	$s4,$sp,0x3a88
/*  f110f88:	3c097f1b */ 	lui	$t1,%hi(var7f1b39f8)
/*  f110f8c:	ae810000 */ 	sw	$at,0x0($s4)
/*  f110f90:	8dd90004 */ 	lw	$t9,0x4($t6)
/*  f110f94:	252939f8 */ 	addiu	$t1,$t1,%lo(var7f1b39f8)
/*  f110f98:	27a80070 */ 	addiu	$t0,$sp,0x70
/*  f110f9c:	ae990004 */ 	sw	$t9,0x4($s4)
/*  f110fa0:	8dc10008 */ 	lw	$at,0x8($t6)
/*  f110fa4:	3c0d7f1b */ 	lui	$t5,%hi(var7f1b3a00)
/*  f110fa8:	25ad3a00 */ 	addiu	$t5,$t5,%lo(var7f1b3a00)
/*  f110fac:	ae810008 */ 	sw	$at,0x8($s4)
/*  f110fb0:	8dd9000c */ 	lw	$t9,0xc($t6)
/*  f110fb4:	27b70068 */ 	addiu	$s7,$sp,0x68
/*  f110fb8:	00809025 */ 	or	$s2,$a0,$zero
/*  f110fbc:	ae99000c */ 	sw	$t9,0xc($s4)
/*  f110fc0:	8d210000 */ 	lw	$at,0x0($t1)
/*  f110fc4:	27b00070 */ 	addiu	$s0,$sp,0x70
/*  f110fc8:	00008825 */ 	or	$s1,$zero,$zero
/*  f110fcc:	ad010000 */ 	sw	$at,0x0($t0)
/*  f110fd0:	91210004 */ 	lbu	$at,0x4($t1)
/*  f110fd4:	00809825 */ 	or	$s3,$a0,$zero
/*  f110fd8:	27b50a88 */ 	addiu	$s5,$sp,0xa88
/*  f110fdc:	a1010004 */ 	sb	$at,0x4($t0)
/*  f110fe0:	8da10000 */ 	lw	$at,0x0($t5)
/*  f110fe4:	2416ffff */ 	addiu	$s6,$zero,-1
/*  f110fe8:	241e0003 */ 	addiu	$s8,$zero,0x3
/*  f110fec:	aee10000 */ 	sw	$at,0x0($s7)
/*  f110ff0:	91a10004 */ 	lbu	$at,0x4($t5)
/*  f110ff4:	a2e10004 */ 	sb	$at,0x4($s7)
/*  f110ff8:	a080030a */ 	sb	$zero,0x30a($a0)
.L0f110ffc:
/*  f110ffc:	82190000 */ 	lb	$t9,0x0($s0)
/*  f111000:	02a03025 */ 	or	$a2,$s5,$zero
/*  f111004:	02595821 */ 	addu	$t3,$s2,$t9
/*  f111008:	a1600305 */ 	sb	$zero,0x305($t3)
/*  f11100c:	a2760300 */ 	sb	$s6,0x300($s3)
/*  f111010:	924a030b */ 	lbu	$t2,0x30b($s2)
/*  f111014:	82040000 */ 	lb	$a0,0x0($s0)
/*  f111018:	000a4080 */ 	sll	$t0,$t2,0x2
/*  f11101c:	02884821 */ 	addu	$t1,$s4,$t0
/*  f111020:	0fc459ec */ 	jal	func0f1167b0
/*  f111024:	8d250000 */ 	lw	$a1,0x0($t1)
/*  f111028:	14400028 */ 	bnez	$v0,.L0f1110cc
/*  f11102c:	8fac0a88 */ 	lw	$t4,0xa88($sp)
/*  f111030:	11800010 */ 	beqz	$t4,.L0f111074
/*  f111034:	00117880 */ 	sll	$t7,$s1,0x2
/*  f111038:	27b81288 */ 	addiu	$t8,$sp,0x1288
/*  f11103c:	27a30a88 */ 	addiu	$v1,$sp,0xa88
/*  f111040:	27ae0088 */ 	addiu	$t6,$sp,0x88
/*  f111044:	022e2821 */ 	addu	$a1,$s1,$t6
/*  f111048:	8c640000 */ 	lw	$a0,0x0($v1)
/*  f11104c:	01f81021 */ 	addu	$v0,$t7,$t8
/*  f111050:	82060000 */ 	lb	$a2,0x0($s0)
.L0f111054:
/*  f111054:	ac440000 */ 	sw	$a0,0x0($v0)
/*  f111058:	8c640004 */ 	lw	$a0,0x4($v1)
/*  f11105c:	24630004 */ 	addiu	$v1,$v1,0x4
/*  f111060:	a0a60000 */ 	sb	$a2,0x0($a1)
/*  f111064:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f111068:	24420004 */ 	addiu	$v0,$v0,0x4
/*  f11106c:	1480fff9 */ 	bnez	$a0,.L0f111054
/*  f111070:	24a50001 */ 	addiu	$a1,$a1,0x1
.L0f111074:
/*  f111074:	82190000 */ 	lb	$t9,0x0($s0)
/*  f111078:	02595821 */ 	addu	$t3,$s2,$t9
/*  f11107c:	a16002d2 */ 	sb	$zero,0x2d2($t3)
/*  f111080:	924a030b */ 	lbu	$t2,0x30b($s2)
/*  f111084:	57ca0007 */ 	bnel	$s8,$t2,.L0f1110a4
/*  f111088:	820c0000 */ 	lb	$t4,0x0($s0)
/*  f11108c:	0fc46052 */ 	jal	func0f118148
/*  f111090:	82040000 */ 	lb	$a0,0x0($s0)
/*  f111094:	82080000 */ 	lb	$t0,0x0($s0)
/*  f111098:	02484821 */ 	addu	$t1,$s2,$t0
/*  f11109c:	a12202d2 */ 	sb	$v0,0x2d2($t1)
/*  f1110a0:	820c0000 */ 	lb	$t4,0x0($s0)
.L0f1110a4:
/*  f1110a4:	000c78c0 */ 	sll	$t7,$t4,0x3
/*  f1110a8:	024fc021 */ 	addu	$t8,$s2,$t7
/*  f1110ac:	af0002d8 */ 	sw	$zero,0x2d8($t8)
/*  f1110b0:	0fc45a4f */ 	jal	func0f11693c
/*  f1110b4:	82040000 */ 	lb	$a0,0x0($s0)
/*  f1110b8:	820d0000 */ 	lb	$t5,0x0($s0)
/*  f1110bc:	000d70c0 */ 	sll	$t6,$t5,0x3
/*  f1110c0:	024ec821 */ 	addu	$t9,$s2,$t6
/*  f1110c4:	10000008 */ 	beqz	$zero,.L0f1110e8
/*  f1110c8:	a72202dc */ 	sh	$v0,0x2dc($t9)
.L0f1110cc:
/*  f1110cc:	820b0000 */ 	lb	$t3,0x0($s0)
/*  f1110d0:	2401000d */ 	addiu	$at,$zero,0xd
/*  f1110d4:	24080005 */ 	addiu	$t0,$zero,0x5
/*  f1110d8:	024b5021 */ 	addu	$t2,$s2,$t3
/*  f1110dc:	14410002 */ 	bne	$v0,$at,.L0f1110e8
/*  f1110e0:	a15602d2 */ 	sb	$s6,0x2d2($t2)
/*  f1110e4:	a248030c */ 	sb	$t0,0x30c($s2)
.L0f1110e8:
/*  f1110e8:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f1110ec:	27a90075 */ 	addiu	$t1,$sp,0x75
/*  f1110f0:	0209082b */ 	sltu	$at,$s0,$t1
/*  f1110f4:	1420ffc1 */ 	bnez	$at,.L0f110ffc
/*  f1110f8:	26730001 */ 	addiu	$s3,$s3,0x1
/*  f1110fc:	a64002d0 */ 	sh	$zero,0x2d0($s2)
/*  f111100:	1a20004b */ 	blez	$s1,.L0f111230
/*  f111104:	0000a825 */ 	or	$s5,$zero,$zero
/*  f111108:	27b00088 */ 	addiu	$s0,$sp,0x88
/*  f11110c:	27b41288 */ 	addiu	$s4,$sp,0x1288
/*  f111110:	241e0018 */ 	addiu	$s8,$zero,0x18
.L0f111114:
/*  f111114:	864c02d0 */ 	lh	$t4,0x2d0($s2)
/*  f111118:	82040000 */ 	lb	$a0,0x0($s0)
/*  f11111c:	8e850000 */ 	lw	$a1,0x0($s4)
/*  f111120:	019e0019 */ 	multu	$t4,$s8
/*  f111124:	24070010 */ 	addiu	$a3,$zero,0x10
/*  f111128:	00007812 */ 	mflo	$t7
/*  f11112c:	024f9821 */ 	addu	$s3,$s2,$t7
/*  f111130:	0fc45a00 */ 	jal	func0f116800
/*  f111134:	26660006 */ 	addiu	$a2,$s3,0x6
/*  f111138:	1440001b */ 	bnez	$v0,.L0f1111a8
/*  f11113c:	2401000a */ 	addiu	$at,$zero,0xa
/*  f111140:	82040000 */ 	lb	$a0,0x0($s0)
/*  f111144:	02e4c021 */ 	addu	$t8,$s7,$a0
/*  f111148:	830d0000 */ 	lb	$t5,0x0($t8)
/*  f11114c:	024d7021 */ 	addu	$t6,$s2,$t5
/*  f111150:	81d90300 */ 	lb	$t9,0x300($t6)
/*  f111154:	16d9000b */ 	bne	$s6,$t9,.L0f111184
/*  f111158:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11115c:	924b030a */ 	lbu	$t3,0x30a($s2)
/*  f111160:	864802d0 */ 	lh	$t0,0x2d0($s2)
/*  f111164:	256a0001 */ 	addiu	$t2,$t3,0x1
/*  f111168:	a24a030a */ 	sb	$t2,0x30a($s2)
/*  f11116c:	82090000 */ 	lb	$t1,0x0($s0)
/*  f111170:	02e96021 */ 	addu	$t4,$s7,$t1
/*  f111174:	818f0000 */ 	lb	$t7,0x0($t4)
/*  f111178:	024fc021 */ 	addu	$t8,$s2,$t7
/*  f11117c:	a3080300 */ 	sb	$t0,0x300($t8)
/*  f111180:	82040000 */ 	lb	$a0,0x0($s0)
.L0f111184:
/*  f111184:	0fc45a4f */ 	jal	func0f11693c
/*  f111188:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11118c:	a6620004 */ 	sh	$v0,0x4($s3)
/*  f111190:	8e8d0000 */ 	lw	$t5,0x0($s4)
/*  f111194:	ae6d0000 */ 	sw	$t5,0x0($s3)
/*  f111198:	864e02d0 */ 	lh	$t6,0x2d0($s2)
/*  f11119c:	25d90001 */ 	addiu	$t9,$t6,0x1
/*  f1111a0:	1000001f */ 	beqz	$zero,.L0f111220
/*  f1111a4:	a65902d0 */ 	sh	$t9,0x2d0($s2)
.L0f1111a8:
/*  f1111a8:	5441001e */ 	bnel	$v0,$at,.L0f111224
/*  f1111ac:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f1111b0:	820b0000 */ 	lb	$t3,0x0($s0)
/*  f1111b4:	024b1021 */ 	addu	$v0,$s2,$t3
/*  f1111b8:	804a0305 */ 	lb	$t2,0x305($v0)
/*  f1111bc:	25490001 */ 	addiu	$t1,$t2,0x1
/*  f1111c0:	a0490305 */ 	sb	$t1,0x305($v0)
/*  f1111c4:	820c0000 */ 	lb	$t4,0x0($s0)
/*  f1111c8:	024c1021 */ 	addu	$v0,$s2,$t4
/*  f1111cc:	804f0305 */ 	lb	$t7,0x305($v0)
/*  f1111d0:	29e10002 */ 	slti	$at,$t7,0x2
/*  f1111d4:	54200013 */ 	bnezl	$at,.L0f111224
/*  f1111d8:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f1111dc:	804802d2 */ 	lb	$t0,0x2d2($v0)
/*  f1111e0:	25180001 */ 	addiu	$t8,$t0,0x1
/*  f1111e4:	a05802d2 */ 	sb	$t8,0x2d2($v0)
/*  f1111e8:	820d0000 */ 	lb	$t5,0x0($s0)
/*  f1111ec:	000d70c0 */ 	sll	$t6,$t5,0x3
/*  f1111f0:	024e1821 */ 	addu	$v1,$s2,$t6
/*  f1111f4:	8c7902d8 */ 	lw	$t9,0x2d8($v1)
/*  f1111f8:	5720000a */ 	bnezl	$t9,.L0f111224
/*  f1111fc:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f111200:	8e8b0000 */ 	lw	$t3,0x0($s4)
/*  f111204:	ac6b02d8 */ 	sw	$t3,0x2d8($v1)
/*  f111208:	0fc45a4f */ 	jal	func0f11693c
/*  f11120c:	82040000 */ 	lb	$a0,0x0($s0)
/*  f111210:	820a0000 */ 	lb	$t2,0x0($s0)
/*  f111214:	000a48c0 */ 	sll	$t1,$t2,0x3
/*  f111218:	02496021 */ 	addu	$t4,$s2,$t1
/*  f11121c:	a58202dc */ 	sh	$v0,0x2dc($t4)
.L0f111220:
/*  f111220:	26b50001 */ 	addiu	$s5,$s5,0x1
.L0f111224:
/*  f111224:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f111228:	16b1ffba */ 	bne	$s5,$s1,.L0f111114
/*  f11122c:	26940004 */ 	addiu	$s4,$s4,0x4
.L0f111230:
/*  f111230:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f111234:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f111238:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f11123c:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f111240:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f111244:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f111248:	8fb5002c */ 	lw	$s5,0x2c($sp)
/*  f11124c:	8fb60030 */ 	lw	$s6,0x30($sp)
/*  f111250:	8fb70034 */ 	lw	$s7,0x34($sp)
/*  f111254:	8fbe0038 */ 	lw	$s8,0x38($sp)
/*  f111258:	03e00008 */ 	jr	$ra
/*  f11125c:	27bd3a98 */ 	addiu	$sp,$sp,0x3a98
/*  f111260:	000470c0 */ 	sll	$t6,$a0,0x3
/*  f111264:	01c47023 */ 	subu	$t6,$t6,$a0
/*  f111268:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f11126c:	01c47021 */ 	addu	$t6,$t6,$a0
/*  f111270:	000e70c0 */ 	sll	$t6,$t6,0x3
/*  f111274:	27bdffe0 */ 	addiu	$sp,$sp,-32
/*  f111278:	01c47023 */ 	subu	$t6,$t6,$a0
/*  f11127c:	3c0f800a */ 	lui	$t7,0x800a
/*  f111280:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f111284:	25efe000 */ 	addiu	$t7,$t7,-8192
/*  f111288:	000e7100 */ 	sll	$t6,$t6,0x4
/*  f11128c:	01cf8021 */ 	addu	$s0,$t6,$t7
/*  f111290:	8e030e68 */ 	lw	$v1,0xe68($s0)
/*  f111294:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f111298:	14600017 */ 	bnez	$v1,.L0f1112f8
/*  f11129c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1112a0:	54a00011 */ 	bnezl	$a1,.L0f1112e8
/*  f1112a4:	92090e40 */ 	lbu	$t1,0xe40($s0)
/*  f1112a8:	92190e40 */ 	lbu	$t9,0xe40($s0)
/*  f1112ac:	24040890 */ 	addiu	$a0,$zero,0x890
/*  f1112b0:	37280040 */ 	ori	$t0,$t9,0x40
/*  f1112b4:	0fc5db69 */ 	jal	func0f176da4
/*  f1112b8:	a2080e40 */ 	sb	$t0,0xe40($s0)
/*  f1112bc:	00402025 */ 	or	$a0,$v0,$zero
/*  f1112c0:	0fc5796e */ 	jal	func0f15e5b8
/*  f1112c4:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f1112c8:	0fc5db69 */ 	jal	func0f176da4
/*  f1112cc:	24040890 */ 	addiu	$a0,$zero,0x890
/*  f1112d0:	0c004aac */ 	jal	func00012ab0
/*  f1112d4:	00402025 */ 	or	$a0,$v0,$zero
/*  f1112d8:	ae020e68 */ 	sw	$v0,0xe68($s0)
/*  f1112dc:	10000006 */ 	beqz	$zero,.L0f1112f8
/*  f1112e0:	00401825 */ 	or	$v1,$v0,$zero
/*  f1112e4:	92090e40 */ 	lbu	$t1,0xe40($s0)
.L0f1112e8:
/*  f1112e8:	ae050e68 */ 	sw	$a1,0xe68($s0)
/*  f1112ec:	00a01825 */ 	or	$v1,$a1,$zero
/*  f1112f0:	312affbf */ 	andi	$t2,$t1,0xffbf
/*  f1112f4:	a20a0e40 */ 	sb	$t2,0xe40($s0)
.L0f1112f8:
/*  f1112f8:	14600006 */ 	bnez	$v1,.L0f111314
/*  f1112fc:	3c047f1b */ 	lui	$a0,%hi(var7f1b3a08)
/*  f111300:	3c057f1b */ 	lui	$a1,%hi(var7f1b3a14)
/*  f111304:	24a53a14 */ 	addiu	$a1,$a1,%lo(var7f1b3a14)
/*  f111308:	24843a08 */ 	addiu	$a0,$a0,%lo(var7f1b3a08)
/*  f11130c:	0c002ff4 */ 	jal	func0000bfd0
/*  f111310:	240601ca */ 	addiu	$a2,$zero,0x1ca
.L0f111314:
/*  f111314:	00001025 */ 	or	$v0,$zero,$zero
/*  f111318:	24030080 */ 	addiu	$v1,$zero,0x80
.L0f11131c:
/*  f11131c:	8e0b0e68 */ 	lw	$t3,0xe68($s0)
/*  f111320:	01626021 */ 	addu	$t4,$t3,$v0
/*  f111324:	ad800800 */ 	sw	$zero,0x800($t4)
/*  f111328:	8e0d0e68 */ 	lw	$t5,0xe68($s0)
/*  f11132c:	01a27021 */ 	addu	$t6,$t5,$v0
/*  f111330:	24420008 */ 	addiu	$v0,$v0,0x8
/*  f111334:	1443fff9 */ 	bne	$v0,$v1,.L0f11131c
/*  f111338:	a5c00804 */ 	sh	$zero,0x804($t6)
/*  f11133c:	8e0f0e68 */ 	lw	$t7,0xe68($s0)
/*  f111340:	24020010 */ 	addiu	$v0,$zero,0x10
/*  f111344:	24090004 */ 	addiu	$t1,$zero,0x4
/*  f111348:	ade00880 */ 	sw	$zero,0x880($t7)
/*  f11134c:	8e180e68 */ 	lw	$t8,0xe68($s0)
/*  f111350:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f111354:	00001825 */ 	or	$v1,$zero,$zero
/*  f111358:	a3020888 */ 	sb	$v0,0x888($t8)
/*  f11135c:	8e190e68 */ 	lw	$t9,0xe68($s0)
/*  f111360:	24050010 */ 	addiu	$a1,$zero,0x10
/*  f111364:	24040080 */ 	addiu	$a0,$zero,0x80
/*  f111368:	a3220889 */ 	sb	$v0,0x889($t9)
/*  f11136c:	8e080e68 */ 	lw	$t0,0xe68($s0)
/*  f111370:	a100088a */ 	sb	$zero,0x88a($t0)
/*  f111374:	8e0a0e68 */ 	lw	$t2,0xe68($s0)
/*  f111378:	a149088b */ 	sb	$t1,0x88b($t2)
/*  f11137c:	8e0b0e68 */ 	lw	$t3,0xe68($s0)
/*  f111380:	a160088c */ 	sb	$zero,0x88c($t3)
/*  f111384:	8e0c0e68 */ 	lw	$t4,0xe68($s0)
/*  f111388:	a180088d */ 	sb	$zero,0x88d($t4)
/*  f11138c:	8e0e0e68 */ 	lw	$t6,0xe68($s0)
/*  f111390:	a1cd088e */ 	sb	$t5,0x88e($t6)
/*  f111394:	8e0f0e68 */ 	lw	$t7,0xe68($s0)
/*  f111398:	a1e0088f */ 	sb	$zero,0x88f($t7)
/*  f11139c:	00001025 */ 	or	$v0,$zero,$zero
.L0f1113a0:
/*  f1113a0:	8e190e68 */ 	lw	$t9,0xe68($s0)
/*  f1113a4:	000341c0 */ 	sll	$t0,$v1,0x7
/*  f1113a8:	0040c025 */ 	or	$t8,$v0,$zero
/*  f1113ac:	03284821 */ 	addu	$t1,$t9,$t0
/*  f1113b0:	01225021 */ 	addu	$t2,$t1,$v0
/*  f1113b4:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f1113b8:	1444fff9 */ 	bne	$v0,$a0,.L0f1113a0
/*  f1113bc:	a1580000 */ 	sb	$t8,0x0($t2)
/*  f1113c0:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f1113c4:	5465fff6 */ 	bnel	$v1,$a1,.L0f1113a0
/*  f1113c8:	00001025 */ 	or	$v0,$zero,$zero
/*  f1113cc:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f1113d0:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f1113d4:	27bd0020 */ 	addiu	$sp,$sp,0x20
/*  f1113d8:	03e00008 */ 	jr	$ra
/*  f1113dc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1113e0:	000470c0 */ 	sll	$t6,$a0,0x3
/*  f1113e4:	01c47023 */ 	subu	$t6,$t6,$a0
/*  f1113e8:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f1113ec:	01c47021 */ 	addu	$t6,$t6,$a0
/*  f1113f0:	000e70c0 */ 	sll	$t6,$t6,0x3
/*  f1113f4:	01c47023 */ 	subu	$t6,$t6,$a0
/*  f1113f8:	3c0f800a */ 	lui	$t7,0x800a
/*  f1113fc:	25efe000 */ 	addiu	$t7,$t7,-8192
/*  f111400:	000e7100 */ 	sll	$t6,$t6,0x4
/*  f111404:	01cf1821 */ 	addu	$v1,$t6,$t7
/*  f111408:	8c780e68 */ 	lw	$t8,0xe68($v1)
/*  f11140c:	27bdffe0 */ 	addiu	$sp,$sp,-32
/*  f111410:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f111414:	5300000f */ 	beqzl	$t8,.L0f111454
/*  f111418:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f11141c:	8c790e40 */ 	lw	$t9,0xe40($v1)
/*  f111420:	24040890 */ 	addiu	$a0,$zero,0x890
/*  f111424:	00194840 */ 	sll	$t1,$t9,0x1
/*  f111428:	05230009 */ 	bgezl	$t1,.L0f111450
/*  f11142c:	ac600e68 */ 	sw	$zero,0xe68($v1)
/*  f111430:	0fc5db69 */ 	jal	func0f176da4
/*  f111434:	afa30018 */ 	sw	$v1,0x18($sp)
/*  f111438:	8fa30018 */ 	lw	$v1,0x18($sp)
/*  f11143c:	00402825 */ 	or	$a1,$v0,$zero
/*  f111440:	0c004b2d */ 	jal	func00012cb4
/*  f111444:	8c640e68 */ 	lw	$a0,0xe68($v1)
/*  f111448:	8fa30018 */ 	lw	$v1,0x18($sp)
/*  f11144c:	ac600e68 */ 	sw	$zero,0xe68($v1)
.L0f111450:
/*  f111450:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0f111454:
/*  f111454:	27bd0020 */ 	addiu	$sp,$sp,0x20
/*  f111458:	03e00008 */ 	jr	$ra
/*  f11145c:	00000000 */ 	sll	$zero,$zero,0x0
);

GLOBAL_ASM(
glabel func0f111460
/*  f111460:	000470c0 */ 	sll	$t6,$a0,0x3
/*  f111464:	01c47023 */ 	subu	$t6,$t6,$a0
/*  f111468:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f11146c:	01c47021 */ 	addu	$t6,$t6,$a0
/*  f111470:	000e70c0 */ 	sll	$t6,$t6,0x3
/*  f111474:	27bdffc8 */ 	addiu	$sp,$sp,-56
/*  f111478:	01c47023 */ 	subu	$t6,$t6,$a0
/*  f11147c:	3c0f800a */ 	lui	$t7,0x800a
/*  f111480:	25efe000 */ 	addiu	$t7,$t7,-8192
/*  f111484:	000e7100 */ 	sll	$t6,$t6,0x4
/*  f111488:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f11148c:	01cf5021 */ 	addu	$t2,$t6,$t7
/*  f111490:	30d0ffff */ 	andi	$s0,$a2,0xffff
/*  f111494:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f111498:	afa60040 */ 	sw	$a2,0x40($sp)
/*  f11149c:	2408ffff */ 	addiu	$t0,$zero,-1
/*  f1114a0:	2409ffff */ 	addiu	$t1,$zero,-1
/*  f1114a4:	8d420e68 */ 	lw	$v0,0xe68($t2)
/*  f1114a8:	24040010 */ 	addiu	$a0,$zero,0x10
/*  f1114ac:	00003825 */ 	or	$a3,$zero,$zero
.L0f1114b0:
/*  f1114b0:	8c430800 */ 	lw	$v1,0x800($v0)
/*  f1114b4:	14a30006 */ 	bne	$a1,$v1,.L0f1114d0
/*  f1114b8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1114bc:	94580804 */ 	lhu	$t8,0x804($v0)
/*  f1114c0:	16180003 */ 	bne	$s0,$t8,.L0f1114d0
/*  f1114c4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1114c8:	1000000a */ 	beqz	$zero,.L0f1114f4
/*  f1114cc:	00e04825 */ 	or	$t1,$a3,$zero
.L0f1114d0:
/*  f1114d0:	54600006 */ 	bnezl	$v1,.L0f1114ec
/*  f1114d4:	24e70001 */ 	addiu	$a3,$a3,0x1
/*  f1114d8:	94590804 */ 	lhu	$t9,0x804($v0)
/*  f1114dc:	57200003 */ 	bnezl	$t9,.L0f1114ec
/*  f1114e0:	24e70001 */ 	addiu	$a3,$a3,0x1
/*  f1114e4:	00e04025 */ 	or	$t0,$a3,$zero
/*  f1114e8:	24e70001 */ 	addiu	$a3,$a3,0x1
.L0f1114ec:
/*  f1114ec:	14e4fff0 */ 	bne	$a3,$a0,.L0f1114b0
/*  f1114f0:	24420008 */ 	addiu	$v0,$v0,0x8
.L0f1114f4:
/*  f1114f4:	2401ffff */ 	addiu	$at,$zero,-1
/*  f1114f8:	1521002f */ 	bne	$t1,$at,.L0f1115b8
/*  f1114fc:	02002025 */ 	or	$a0,$s0,$zero
/*  f111500:	afa5003c */ 	sw	$a1,0x3c($sp)
/*  f111504:	afa80030 */ 	sw	$t0,0x30($sp)
/*  f111508:	0fc479ac */ 	jal	func0f11e6b0
/*  f11150c:	afaa0024 */ 	sw	$t2,0x24($sp)
/*  f111510:	00022600 */ 	sll	$a0,$v0,0x18
/*  f111514:	00045e03 */ 	sra	$t3,$a0,0x18
/*  f111518:	01602025 */ 	or	$a0,$t3,$zero
/*  f11151c:	8fa5003c */ 	lw	$a1,0x3c($sp)
/*  f111520:	8fa80030 */ 	lw	$t0,0x30($sp)
/*  f111524:	04410003 */ 	bgez	$v0,.L0f111534
/*  f111528:	8faa0024 */ 	lw	$t2,0x24($sp)
/*  f11152c:	1000002d */ 	beqz	$zero,.L0f1115e4
/*  f111530:	00001025 */ 	or	$v0,$zero,$zero
.L0f111534:
/*  f111534:	2401ffff */ 	addiu	$at,$zero,-1
/*  f111538:	55010004 */ 	bnel	$t0,$at,.L0f11154c
/*  f11153c:	8d430e68 */ 	lw	$v1,0xe68($t2)
/*  f111540:	10000028 */ 	beqz	$zero,.L0f1115e4
/*  f111544:	00001025 */ 	or	$v0,$zero,$zero
/*  f111548:	8d430e68 */ 	lw	$v1,0xe68($t2)
.L0f11154c:
/*  f11154c:	3c02800a */ 	lui	$v0,%hi(g_Vars+0x58)
/*  f111550:	8c42a018 */ 	lw	$v0,%lo(g_Vars+0x58)($v0)
/*  f111554:	8c6c0880 */ 	lw	$t4,0x880($v1)
/*  f111558:	000879c0 */ 	sll	$t7,$t0,0x7
/*  f11155c:	004c6823 */ 	subu	$t5,$v0,$t4
/*  f111560:	29a10014 */ 	slti	$at,$t5,0x14
/*  f111564:	50200004 */ 	beqzl	$at,.L0f111578
/*  f111568:	ac620880 */ 	sw	$v0,0x880($v1)
/*  f11156c:	1000001d */ 	beqz	$zero,.L0f1115e4
/*  f111570:	00001025 */ 	or	$v0,$zero,$zero
/*  f111574:	ac620880 */ 	sw	$v0,0x880($v1)
.L0f111578:
/*  f111578:	8d4e0e68 */ 	lw	$t6,0xe68($t2)
/*  f11157c:	afaa0024 */ 	sw	$t2,0x24($sp)
/*  f111580:	afa80030 */ 	sw	$t0,0x30($sp)
/*  f111584:	afa5003c */ 	sw	$a1,0x3c($sp)
/*  f111588:	0fc54057 */ 	jal	func0f15015c
/*  f11158c:	01cf3021 */ 	addu	$a2,$t6,$t7
/*  f111590:	8faa0024 */ 	lw	$t2,0x24($sp)
/*  f111594:	8fa90030 */ 	lw	$t1,0x30($sp)
/*  f111598:	8fa5003c */ 	lw	$a1,0x3c($sp)
/*  f11159c:	8d580e68 */ 	lw	$t8,0xe68($t2)
/*  f1115a0:	000918c0 */ 	sll	$v1,$t1,0x3
/*  f1115a4:	0303c821 */ 	addu	$t9,$t8,$v1
/*  f1115a8:	af250800 */ 	sw	$a1,0x800($t9)
/*  f1115ac:	8d4b0e68 */ 	lw	$t3,0xe68($t2)
/*  f1115b0:	01636021 */ 	addu	$t4,$t3,$v1
/*  f1115b4:	a5900804 */ 	sh	$s0,0x804($t4)
.L0f1115b8:
/*  f1115b8:	2401ffff */ 	addiu	$at,$zero,-1
/*  f1115bc:	55210004 */ 	bnel	$t1,$at,.L0f1115d0
/*  f1115c0:	8d430e68 */ 	lw	$v1,0xe68($t2)
/*  f1115c4:	10000007 */ 	beqz	$zero,.L0f1115e4
/*  f1115c8:	00001025 */ 	or	$v0,$zero,$zero
/*  f1115cc:	8d430e68 */ 	lw	$v1,0xe68($t2)
.L0f1115d0:
/*  f1115d0:	000969c0 */ 	sll	$t5,$t1,0x7
/*  f1115d4:	006d7021 */ 	addu	$t6,$v1,$t5
/*  f1115d8:	ac6e0884 */ 	sw	$t6,0x884($v1)
/*  f1115dc:	8d420e68 */ 	lw	$v0,0xe68($t2)
/*  f1115e0:	24420884 */ 	addiu	$v0,$v0,2180
.L0f1115e4:
/*  f1115e4:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f1115e8:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f1115ec:	27bd0038 */ 	addiu	$sp,$sp,0x38
/*  f1115f0:	03e00008 */ 	jr	$ra
/*  f1115f4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1115f8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1115fc:	00000000 */ 	sll	$zero,$zero,0x0
);