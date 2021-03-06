//
// Stage ID 0x4e
//

#include "stagesetup.h"

s32 intro[];
u32 props[];
struct path paths[];
struct ailist ailists[];

struct stagesetup setup = {
	NULL,
	NULL,
	NULL,
	intro,
	props,
	paths,
	ailists,
	NULL,
};

u32 props[] = {
	tag(0x00, 1)
	stdobject(0x0100, MODEL_A51_CRATE1, 0xffff, 0x00021501, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000003e8, 0x00000000, 0x00000000, 0x0fff0000)
	tag(0x01, 1)
	stdobject(0x0100, MODEL_A51_CRATE1, 0xffff, 0x00021501, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000003e8, 0x00000000, 0x00000000, 0x0fff0000)
	tag(0x02, 1)
	stdobject(0x0100, MODEL_A51_CRATE1, 0xffff, 0x00021501, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000003e8, 0x00000000, 0x00000000, 0x0fff0000)
	endprops
};

s32 intro[] = {
	outfit(OUTFIT_DEFAULT)
	endintro
};

struct path paths[] = {
	{ NULL, 0, 0 },
};

/**
 * Some kind of camera movement test? When you press a button it jumps forward
 * to the next camera animation rather than ending the cutscene.
 */
u8 func0c00_017c[] = {
	set_chr_chrflag(CHR_COOP, CHRCFLAG_HIDDEN)
	set_chr_chrflag(CHR_ANTI, CHRCFLAG_HIDDEN)
	set_music_track(MUSIC_G5_INTRO)
	camera_movement(0x045d)
	cmd01c8(2)

	beginloop(0x12)
		cmd01c9(/*goto*/ 0x59)
	endloop(0x12)

	label(0x59)
	cmd01c8(3)

	beginloop(0x13)
		cmd01c9(/*goto*/ 0x59)
	endloop(0x13)

	label(0x59)
	camera_movement(0x045d)
	show_object(0x00)
	set_object_flag2(0x00, OBJFLAG2_04000000)
	set_object_flag3(0x00, OBJFLAG3_00000010)
	object_do_animation(0x045e, 0x00, 0x04, 0xffff)

	beginloop(0x08)
		if_camera_animating(/*goto*/ 0x31)
		goto_next(0x59)

		label(0x31)
		if_controller_button_pressed(/*goto*/ 0x59)
		label(0x31)
	endloop(0x08)

	label(0x59)
	hide_object(0x00)
	camera_movement(0x0464)
	show_object(0x01)
	set_object_flag2(0x01, OBJFLAG2_04000000)
	set_object_flag3(0x01, OBJFLAG3_00000010)
	object_do_animation(0x0465, 0x01, 0x04, 0xffff)

	beginloop(0x0b)
		if_camera_animating(/*goto*/ 0x31)
		goto_next(0x59)

		label(0x31)
		if_controller_button_pressed(/*goto*/ 0x59)
		label(0x31)
	endloop(0x0b)

	label(0x59)
	hide_object(0x01)
	camera_movement(0x0461)

	show_object(0x00)
	set_object_flag2(0x00, OBJFLAG2_04000000)
	set_object_flag3(0x00, OBJFLAG3_00000010)
	object_do_animation(0x0462, 0x00, 0x04, 0xffff)

	show_object(0x01)
	set_object_flag2(0x01, OBJFLAG2_04000000)
	set_object_flag3(0x01, OBJFLAG3_00000010)
	object_do_animation(0x0463, 0x01, 0x04, 0xffff)

	beginloop(0x0a)
		if_camera_animating(/*goto*/ 0x31)
		goto_next(0x59)

		label(0x31)
		if_controller_button_pressed(/*goto*/ 0x59)
		label(0x31)
	endloop(0x0a)

	label(0x59)
	hide_object(0x01)
	hide_object(0x00)
	camera_movement(0x046c)

	show_object(0x01)
	unset_object_flag2(0x01, OBJFLAG2_04000000)
	set_object_flag3(0x01, OBJFLAG3_00000010)
	object_do_animation(0x046e, 0x01, 0x04, 0xffff)

	show_object(0x00)
	set_object_flag2(0x00, OBJFLAG2_04000000)
	set_object_flag3(0x00, OBJFLAG3_00000010)
	object_do_animation(0x046d, 0x00, 0x04, 0xffff)

	show_object(0x02)
	set_object_flag2(0x02, OBJFLAG2_04000000)
	set_object_flag3(0x02, OBJFLAG3_00000010)
	object_do_animation(0x046f, 0x02, 0x04, 0xffff)

	beginloop(0x0e)
		if_camera_animating(/*goto*/ 0x31)
		goto_next(0x59)

		label(0x31)
		if_controller_button_pressed(/*goto*/ 0x59)
		label(0x31)
	endloop(0x0e)

	label(0x59)
	unset_chr_chrflag(CHR_COOP, CHRCFLAG_HIDDEN)
	unset_chr_chrflag(CHR_ANTI, CHRCFLAG_HIDDEN)
	cmd01c8(5)

	beginloop(0x15)
		cmd01c9(/*goto*/ 0x59)
	endloop(0x15)

	label(0x59)
	restart_default_music
	reset_ambience
	enter_firstperson
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

struct ailist ailists[] = {
	{ func0c00_017c, 0x0401 },
	{ func0c00_017c, 0x0c00 },
	{ NULL, 0 },
};

