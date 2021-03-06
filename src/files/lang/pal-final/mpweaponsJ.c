#include <ultra64.h>

char *lang[] = {
	/*  0*/ "%shas the\nData Uplink\n",
	/*  1*/ "%shas the\nBriefcase\n",
	/*  2*/ "%shas the %s Briefcase\n",
	/*  3*/ "%shas our\nBriefcase\n",
	/*  4*/ "Got the %s Briefcase\n",
	/*  5*/ "You captured\nthe %s Briefcase\n",
	/*  6*/ "%scaptured our\nBriefcase\n",
	/*  7*/ "%scaptured\nthe %s Briefcase\n",
	/*  8*/ "Have a point for living!\n",
	/*  9*/ "You're supposed to look\n",
	/* 10*/ "after your friends!\n",
	/* 11*/ "Well done!\n",
	/* 12*/ "You popped a cap!\n",
	/* 13*/ "Have 2 Points...\n",
	/* 14*/ "You are the victim!\n",
	/* 15*/ "Protect %s!\n",
	/* 16*/ "Get %s!\n",
	/* 17*/ "Download successful.\n",
	/* 18*/ "Connection broken.\n",
	/* 19*/ "Starting download.\n",
	/* 20*/ "You need to use the Data Uplink.\n",
	/* 21*/ "King of\nthe Hill!\n",
	/* 22*/ "We have\nthe Hill!\n",
	/* 23*/ "%shas captured\nthe Hill!\n",
	/* 24*/ "%ds/Point\n",
	/* 25*/ "1 Point!\n",
	/* 26*/ "No Shield\n",
	/* 27*/ "Automatics\n",
	/* 28*/ "Rocket Launcher\n",
	/* 29*/ "Simulants\n",
	/* 30*/ "King of the Hill\n",
	/* 31*/ "Complex FarSight\n",
	/* 32*/ "Capture the Briefcase\n",
	/* 33*/ "Pistol One-Hit Kills\n",
	/* 34*/ "Capture the Flag\n",
	/* 35*/ "Cloaking\n",
	/* 36*/ "Temple Explosives\n",
	/* 37*/ "Slayer\n",
	/* 38*/ "Tranquilizer\n",
	/* 39*/ "Slow Motion\n",
	/* 40*/ "Press START\n",
	/* 41*/ "Paused\n",
	/* 42*/ "Custom\n",
	/* 43*/ "Random\n",
	/* 44*/ "Random Five\n",
	/* 45*/ "Close Combat\n",
	/* 46*/ "Proximity Mine\n",
	/* 47*/ "Rocket Launcher\n",
	/* 48*/ "Grenade Launcher\n",
	/* 49*/ "Explosive\n",
	/* 50*/ "Golden Magnum\n",
	/* 51*/ "Heavy\n",
	/* 52*/ "Tranquilizer\n",
	/* 53*/ "FarSight\n",
	/* 54*/ "Power\n",
	/* 55*/ "Automatics\n",
	/* 56*/ "Pistols\n",
	/* 57*/ "Test\n",
	/* 58*/ "4mb Test\n",
	/* 59*/ "Nothing\n",
	/* 60*/ "Shield\n",
	/* 61*/ "Disabled\n",
	/* 62*/ "Objectives Complete\n",
	/* 63*/ "Unknown\n",
	/* 64*/ "Missing\n",
	/* 65*/ "Damaged Controller Pak Inserted\n",
	/* 66*/ "is damaged or inserted\n",
	/* 67*/ "incorrectly.\n",
	/* 68*/ "Please remove and try again.\n",
	/* 69*/ "Full Controller Pak Inserted\n",
	/* 70*/ "is too full to save files.\n",
	/* 71*/ "Use the Game Notes Editor to\n",
	/* 72*/ "free some space (hold START\n",
	/* 73*/ "while powering up.\n",
	/* 74*/ "OK\n",
	/* 75*/ "----------\n",
	/* 76*/ "Hurricane Fists\n",
	/* 77*/ "Cloaking Device\n",
	/* 78*/ "Invincible\n",
	/* 79*/ "All Guns in Solo\n",
	/* 80*/ "Unlimited Ammo\n",
	/* 81*/ "Unlimited Ammo, No Reloads\n",
	/* 82*/ "Slo-mo Single Player\n",
	/* 83*/ "DK Mode\n",
	/* 84*/ "Trent's Magnum\n",
	/* 85*/ "FarSight\n",
	/* 86*/ "Small Jo\n",
	/* 87*/ "Small Characters\n",
	/* 88*/ "Enemy Shields\n",
	/* 89*/ "Jo Shield\n",
	/* 90*/ "Super Shield\n",
	/* 91*/ "Classic Sight\n",
	/* 92*/ "Team Heads Only\n",
	/* 93*/ "Play as Elvis\n",
	/* 94*/ "Enemy Rockets\n",
	/* 95*/ "Unlimited Ammo - Laptop Sentry Gun\n",
	/* 96*/ "Marquis of Queensbury Rules\n",
	/* 97*/ "Perfect Darkness\n",
	/* 98*/ "Pugilist\n",
	/* 99*/ "Hotshot\n",
	/*100*/ "Hit and Run\n",
	/*101*/ "Alien\n",
	/*102*/ "R-Tracker / Weapon Cache Locations\n",
	/*103*/ "Rocket Launcher\n",
	/*104*/ "Sniper Rifle\n",
	/*105*/ "X-Ray Scanner\n",
	/*106*/ "Superdragon\n",
	/*107*/ "Laptop Gun\n",
	/*108*/ "Phoenix\n",
	/*109*/ "Psychosis Gun\n",
	/*110*/ "PP7\n",
	/*111*/ "DD44\n",
	/*112*/ "Klobb\n",
	/*113*/ "KF7 Soviet\n",
	/*114*/ "ZMG (9mm)\n",
	/*115*/ "D5K\n",
	/*116*/ "AR33\n",
	/*117*/ "RC-P90\n",
	/*118*/ "Velvet Dark\n",
	/*119*/ "Fun\n",
	/*120*/ "Gameplay\n",
	/*121*/ "Weapons\n",
	/*122*/ "Buddies\n",
	/*123*/ "Weapons for Jo in Solo\n",
	/*124*/ "Classic Weapons for Jo in Solo\n",
	/*125*/ "dataDyne Defection",
	/*126*/ "dataDyne Extraction",
	/*127*/ "A51 Infiltration",
	/*128*/ "A51 Rescue",
	/*129*/ "A51 Escape",
	/*130*/ "Difficulty:\n",
	/*131*/ "Cheat Solo Missions\n",
	/*132*/ "Cheat Combat Simulator\n",
	/*133*/ "Cheat Co-Operative\n",
	/*134*/ "Cheat Counter-Operative\n",
	/*135*/ "Dishonored\n",
	/*136*/ "Cheated\n",
	/*137*/ "Cheat available",
	/*138*/ "Complete",
	/*139*/ "for cheat:",
	/*140*/ "on",
	/*141*/ "in under",
	/*142*/ " or insert Game Boy (r) Perfect Dark into Transfer Pak (tm), connect Transfer Pak to any controller, then enter and exit menu",
	/*143*/ "Select cheat for information\n",
	/*144*/ "Buddy Available",
	/*145*/ "Win Golds on the firing range to enable classic guns.\n",
	/*146*/ "Sight on Screen\n",
	/*147*/ "Target\n",
	/*148*/ "Zoom Range\n",
	/*149*/ "Show Ammo\n",
	/*150*/ "Gun Function\n",
	/*151*/ "Paintball\n",
	/*152*/ "Subtitles\n",
	/*153*/ "Mission Time\n",
	/*154*/ "Mode\n",
	/*155*/ "Split\n",
	/*156*/ "Do you want to abort\nthe mission?\n",
	/*157*/ "Joanna Leather\n",
	/*158*/ "Joanna Negotiator\n",
	/*159*/ "Elvis (Waistcoat)\n",
	/*160*/ "Error\n",
	/*161*/ "Cannot delete file as\nit is being used.\n",
	/*162*/ "Cancel\n",
	/*163*/ "Time Limit:\n",
	/*164*/ "Score Limit:\n",
	/*165*/ "Team Score Limit:\n",
	/*166*/ "Challenge Completed!\n",
	/*167*/ "Challenge Failed!\n",
	/*168*/ "Challenge Cheated!\n",
	/*169*/ "Cutscene Subtitles\n",
	/*170*/ "In-Game Subtitles\n",
	/*171*/ "Alternative Title Screen\n",
	/*172*/ "Start Challenge\n",
	/*173*/ "dataDyne Investigation",
	/*174*/ "Error\n",
	/*175*/ "The Controller Pak\nhas been removed.\n",
	/*176*/ "Attempt Repair\n",
	/*177*/ "Are you sure you want\nto attempt repair of\nthis Controller Pak?\n",
	/*178*/ "Data may be lost!\n",
	/*179*/ "Cancel\n",
	/*180*/ "Repair\n",
	/*181*/ "Repair Successful\n",
	/*182*/ "The Controller Pak has\nbeen repaired.\n",
	/*183*/ "Repair Failed\n",
	/*184*/ "The Controller Pak could\nnot be repaired.\n",
	/*185*/ "L/R: ",
	/*186*/ "C-UP: ",
	/*187*/ "C-L/R: ",
	/*188*/ "C-DOWN: ",
	/*189*/ "A: ",
	/*190*/ "B: ",
	/*191*/ "STICK: ",
	/*192*/ "Z: ",
	/*193*/ "D-PAD: ",
	/*194*/ "AIM TOGGLE",
	/*195*/ "LOOK UP / GET UP",
	/*196*/ "STRAFE",
	/*197*/ "LOOK DOWN / CROUCH",
	/*198*/ "CHANGE GUN / ACTIVEMENU",
	/*199*/ "RELOAD / ACTION / SECONDARY FIRE",
	/*200*/ "WALK AND TURN",
	/*201*/ "FIRE",
	/*202*/ "AS C-BUTTONS",
	/*203*/ "Turn off all Cheats\n",
	/*204*/ NULL,
	/*205*/ NULL,
	/*206*/ NULL,
	/*207*/ NULL,
	/*208*/ NULL,
	/*209*/ NULL,
	/*210*/ NULL,
	/*211*/ NULL,
	/*212*/ NULL,
	/*213*/ NULL,
	/*214*/ NULL,
	/*215*/ NULL,
	/*216*/ NULL,
	/*217*/ NULL,
	/*218*/ NULL,
	/*219*/ NULL,
	/*220*/ NULL,
	/*221*/ NULL,
	/*222*/ NULL,
	/*223*/ NULL,
	/*224*/ NULL,
	/*225*/ NULL,
	/*226*/ NULL,
	/*227*/ NULL,
	/*228*/ NULL,
	/*229*/ NULL,
	/*230*/ NULL,
	/*231*/ NULL,
	/*232*/ NULL,
	/*233*/ NULL,
	/*234*/ NULL,
	/*235*/ NULL,
	/*236*/ NULL,
	/*237*/ NULL,
	/*238*/ NULL,
	/*239*/ NULL,
	/*240*/ NULL,
	/*241*/ NULL,
	/*242*/ NULL,
	/*243*/ NULL,
	/*244*/ NULL,
	/*245*/ NULL,
	/*246*/ NULL,
	/*247*/ NULL,
	/*248*/ NULL,
	/*249*/ NULL,
	/*250*/ NULL,
	/*251*/ NULL,
	/*252*/ NULL,
	/*253*/ NULL,
	/*254*/ NULL,
	/*255*/ NULL,
	/*256*/ NULL,
	/*257*/ NULL,
	/*258*/ NULL,
	/*259*/ NULL,
	/*260*/ NULL,
	/*261*/ NULL,
	/*262*/ NULL,
	/*263*/ NULL,
	/*264*/ NULL,
	/*265*/ NULL,
	/*266*/ NULL,
	/*267*/ NULL,
	/*268*/ NULL,
	/*269*/ NULL,
	/*270*/ NULL,
	/*271*/ NULL,
	/*272*/ NULL,
	/*273*/ NULL,
	/*274*/ NULL,
	/*275*/ NULL,
	/*276*/ NULL,
	/*277*/ NULL,
	/*278*/ NULL,
	/*279*/ NULL,
	/*280*/ NULL,
	/*281*/ NULL,
	/*282*/ NULL,
	/*283*/ NULL,
};
