/**
 * @file interfac.cpp
 *
 * Implementation of load screens.
 */
#include "all.h"

DEVILUTION_BEGIN_NAMESPACE

BYTE *sgpBackCel;
DWORD sgdwProgress;
int progress_id;

/** The color used for the progress bar as an index into the palette. */
const BYTE BarColor[3] = { 138, 43, 254 };
/** The screen position of the top left corner of the progress bar. */
const int BarPos[3][2] = { { 53, 37 }, { 53, 421 }, { 53, 37 } };

static void FreeInterface()
{
	MemFreeDbg(sgpBackCel);
}

static void InitCutscene(unsigned int uMsg)
{
	assert(!sgpBackCel);

	switch (uMsg) {
	case WM_DIABNEXTLVL:
		switch (gnLevelTypeTbl[currlevel]) {
		case DTYPE_TOWN:
			sgpBackCel = LoadFileInMem("Gendata\\Cuttt.CEL", NULL);
			LoadPalette("Gendata\\Cuttt.pal");
			progress_id = 1;
			break;
		case DTYPE_CATHEDRAL:
			if (currlevel < 17) {
				sgpBackCel = LoadFileInMem("Gendata\\Cutl1d.CEL", NULL);
				LoadPalette("Gendata\\Cutl1d.pal");
				progress_id = 0;
			} else {
				sgpBackCel = LoadFileInMem("Nlevels\\cutl5.CEL", NULL);
				LoadPalette("Nlevels\\cutl5.pal");
				progress_id = 1;
			}
			break;
		case DTYPE_CATACOMBS:
			sgpBackCel = LoadFileInMem("Gendata\\Cut2.CEL", NULL);
			LoadPalette("Gendata\\Cut2.pal");
			progress_id = 2;
			break;
		case DTYPE_CAVES:
			if (currlevel < 17) {
				sgpBackCel = LoadFileInMem("Gendata\\Cut3.CEL", NULL);
				LoadPalette("Gendata\\Cut3.pal");
				progress_id = 1;
			} else {
				sgpBackCel = LoadFileInMem("Nlevels\\cutl6.CEL", NULL);
				LoadPalette("Nlevels\\cutl6.pal");
				progress_id = 1;
			}
			break;
		case DTYPE_HELL:
			if (currlevel < 15) {
				sgpBackCel = LoadFileInMem("Gendata\\Cut4.CEL", NULL);
				LoadPalette("Gendata\\Cut4.pal");
				progress_id = 1;
			} else {
				sgpBackCel = LoadFileInMem("Gendata\\Cutgate.CEL", NULL);
				LoadPalette("Gendata\\Cutgate.pal");
				progress_id = 1;
			}
			break;
		default:
			sgpBackCel = LoadFileInMem("Gendata\\Cutl1d.CEL", NULL);
			LoadPalette("Gendata\\Cutl1d.pal");
			progress_id = 0;
			break;
		}
		break;
	case WM_DIABPREVLVL:
		if (gnLevelTypeTbl[currlevel - 1] == 0) {
			sgpBackCel = LoadFileInMem("Gendata\\Cuttt.CEL", NULL);
			LoadPalette("Gendata\\Cuttt.pal");
			progress_id = 1;
		} else {
			switch (gnLevelTypeTbl[currlevel]) {
			case DTYPE_TOWN:
				sgpBackCel = LoadFileInMem("Gendata\\Cuttt.CEL", NULL);
				LoadPalette("Gendata\\Cuttt.pal");
				progress_id = 1;
				break;
			case DTYPE_CATHEDRAL:
				if (currlevel < 17) {
					sgpBackCel = LoadFileInMem("Gendata\\Cutl1d.CEL", NULL);
					LoadPalette("Gendata\\Cutl1d.pal");
					progress_id = 0;
				} else {
					sgpBackCel = LoadFileInMem("Nlevels\\cutl5.CEL", NULL);
					LoadPalette("Nlevels\\cutl5.pal");
					progress_id = 1;
				}
				break;
			case DTYPE_CATACOMBS:
				sgpBackCel = LoadFileInMem("Gendata\\Cut2.CEL", NULL);
				LoadPalette("Gendata\\Cut2.pal");
				progress_id = 2;
				break;
			case DTYPE_CAVES:
				if (currlevel < 17) {
					sgpBackCel = LoadFileInMem("Gendata\\Cut3.CEL", NULL);
					LoadPalette("Gendata\\Cut3.pal");
					progress_id = 1;
				} else {
					sgpBackCel = LoadFileInMem("Nlevels\\cutl6.CEL", NULL);
					LoadPalette("Nlevels\\cutl6.pal");
					progress_id = 1;
				}
				break;
			case DTYPE_HELL:
				sgpBackCel = LoadFileInMem("Gendata\\Cut4.CEL", NULL);
				LoadPalette("Gendata\\Cut4.pal");
				progress_id = 1;
				break;
			default:
				sgpBackCel = LoadFileInMem("Gendata\\Cutl1d.CEL", NULL);
				LoadPalette("Gendata\\Cutl1d.pal");
				progress_id = 0;
				break;
			}
		}
		break;
	case WM_DIABSETLVL:
		if (setlvlnum == SL_BONECHAMB) {
			sgpBackCel = LoadFileInMem("Gendata\\Cut2.CEL", NULL);
			LoadPalette("Gendata\\Cut2.pal");
			progress_id = 2;
		} else if (setlvlnum == SL_VILEBETRAYER) {
			sgpBackCel = LoadFileInMem("Gendata\\Cutportr.CEL", NULL);
			LoadPalette("Gendata\\Cutportr.pal");
			progress_id = 1;
		} else {
			sgpBackCel = LoadFileInMem("Gendata\\Cutl1d.CEL", NULL);
			LoadPalette("Gendata\\Cutl1d.pal");
			progress_id = 0;
		}
		break;
	case WM_DIABRTNLVL:
		if (setlvlnum == SL_BONECHAMB) {
			sgpBackCel = LoadFileInMem("Gendata\\Cut2.CEL", NULL);
			LoadPalette("Gendata\\Cut2.pal");
			progress_id = 2;
		} else if (setlvlnum == SL_VILEBETRAYER) {
			sgpBackCel = LoadFileInMem("Gendata\\Cutportr.CEL", NULL);
			LoadPalette("Gendata\\Cutportr.pal");
			progress_id = 1;
		} else {
			sgpBackCel = LoadFileInMem("Gendata\\Cutl1d.CEL", NULL);
			LoadPalette("Gendata\\Cutl1d.pal");
			progress_id = 0;
		}
		break;
	case WM_DIABWARPLVL:
		sgpBackCel = LoadFileInMem("Gendata\\Cutportl.CEL", NULL);
		LoadPalette("Gendata\\Cutportl.pal");
		progress_id = 1;
		break;
	case WM_DIABLOADGAME:
		sgpBackCel = LoadFileInMem("Gendata\\Cutstart.CEL", NULL);
		LoadPalette("Gendata\\Cutstart.pal");
		progress_id = 1;
		break;
	case WM_DIABNEWGAME:
		sgpBackCel = LoadFileInMem("Gendata\\Cutstart.CEL", NULL);
		LoadPalette("Gendata\\Cutstart.pal");
		progress_id = 1;
		break;
	case WM_DIABTOWNWARP:
	case WM_DIABTWARPUP:
		switch (gnLevelTypeTbl[plr[myplr].plrlevel]) {
		case DTYPE_TOWN:
			sgpBackCel = LoadFileInMem("Gendata\\Cuttt.CEL", NULL);
			LoadPalette("Gendata\\Cuttt.pal");
			progress_id = 1;
			break;
		case DTYPE_CATHEDRAL:
			if (plr[myplr].plrlevel < 17) {
				sgpBackCel = LoadFileInMem("Gendata\\Cutl1d.CEL", NULL);
				LoadPalette("Gendata\\Cutl1d.pal");
				progress_id = 0;
			} else {
				sgpBackCel = LoadFileInMem("Nlevels\\Cutl5.CEL", NULL);
				LoadPalette("Nlevels\\Cutl5.pal");
				progress_id = 1;
			}
			break;
		case DTYPE_CATACOMBS:
			sgpBackCel = LoadFileInMem("Gendata\\Cut2.CEL", NULL);
			LoadPalette("Gendata\\Cut2.pal");
			progress_id = 2;
			break;
		case DTYPE_CAVES:
			if (plr[myplr].plrlevel < 17) {
				sgpBackCel = LoadFileInMem("Gendata\\Cut3.CEL", NULL);
				LoadPalette("Gendata\\Cut3.pal");
				progress_id = 1;
			} else {
				sgpBackCel = LoadFileInMem("Nlevels\\Cutl6.CEL", NULL);
				LoadPalette("Nlevels\\Cutl6.pal");
				progress_id = 1;
			}
			break;
		case DTYPE_HELL:
			sgpBackCel = LoadFileInMem("Gendata\\Cut4.CEL", NULL);
			LoadPalette("Gendata\\Cut4.pal");
			progress_id = 1;
			break;
		}
		break;
	case WM_DIABRETOWN:
		sgpBackCel = LoadFileInMem("Gendata\\Cuttt.CEL", NULL);
		LoadPalette("Gendata\\Cuttt.pal");
		progress_id = 1;
		break;
	default:
		app_fatal("Unknown progress mode");
		break;
	}

	sgdwProgress = 0;
}

static void DrawProgress(CelOutputBuffer out, int x, int y, int progress_id)
{
	BYTE *dst = out.at(x, y);
	for (int i = 0; i < 22; ++i, dst += out.pitch()) {
		*dst = BarColor[progress_id];
	}
}

static void DrawCutscene()
{
	DWORD i;

	lock_buf(1);
	CelOutputBuffer out = GlobalBackBuffer();
	CelDrawTo(out, PANEL_X, 480 - 1 + UI_OFFSET_Y, sgpBackCel, 1, 640);

	for (i = 0; i < sgdwProgress; i++) {
		DrawProgress(
		    out,
		    BarPos[progress_id][0] + i + PANEL_X,
		    BarPos[progress_id][1] + UI_OFFSET_Y,
		    progress_id);
	}

	unlock_buf(1);
	force_redraw = 255;
	scrollrt_draw_game_screen(FALSE);
}

void interface_msg_pump()
{
	MSG Msg;

	while (FetchMessage(&Msg)) {
		if (Msg.message != DVL_WM_QUIT) {
			TranslateMessage(&Msg);
			PushMessage(&Msg);
		}
	}
}

BOOL IncProgress()
{
	interface_msg_pump();
	sgdwProgress += 23;
	if (sgdwProgress > 534)
		sgdwProgress = 534;
	if (sgpBackCel)
		DrawCutscene();
	return sgdwProgress >= 534;
}

void ShowProgress(unsigned int uMsg)
{
	WNDPROC saveProc;

	gbSomebodyWonGameKludge = FALSE;
	plrmsg_delay(TRUE);

	assert(ghMainWnd);
	saveProc = SetWindowProc(DisableInputWndProc);

	interface_msg_pump();
	ClearScreenBuffer();
	scrollrt_draw_game_screen(TRUE);
	InitCutscene(uMsg);
	BlackPalette();
	DrawCutscene();
	PaletteFadeIn(8);
	IncProgress();
	sound_init();
	IncProgress();

	switch (uMsg) {
	case WM_DIABLOADGAME:
		IncProgress();
		IncProgress();
		LoadGame(TRUE);
		IncProgress();
		IncProgress();
		break;
	case WM_DIABNEWGAME:
		plr[myplr].pOriginalCathedral = !gbIsHellfire;
		IncProgress();
		FreeGameMem();
		IncProgress();
		pfile_remove_temp_files();
		IncProgress();
		LoadGameLevel(TRUE, ENTRY_MAIN);
		IncProgress();
		break;
	case WM_DIABNEXTLVL:
		IncProgress();
		if (!gbIsMultiplayer) {
			SaveLevel();
		} else {
			DeltaSaveLevel();
		}
		IncProgress();
		FreeGameMem();
		currlevel++;
		leveltype = gnLevelTypeTbl[currlevel];
		assert(plr[myplr].plrlevel == currlevel);
		IncProgress();
		LoadGameLevel(FALSE, ENTRY_MAIN);
		IncProgress();
		break;
	case WM_DIABPREVLVL:
		IncProgress();
		if (!gbIsMultiplayer) {
			SaveLevel();
		} else {
			DeltaSaveLevel();
		}
		IncProgress();
		FreeGameMem();
		currlevel--;
		leveltype = gnLevelTypeTbl[currlevel];
		assert(plr[myplr].plrlevel == currlevel);
		IncProgress();
		LoadGameLevel(FALSE, ENTRY_PREV);
		IncProgress();
		break;
	case WM_DIABSETLVL:
		SetReturnLvlPos();
		IncProgress();
		if (!gbIsMultiplayer) {
			SaveLevel();
		} else {
			DeltaSaveLevel();
		}
		IncProgress();
		setlevel = TRUE;
		leveltype = setlvltype;
		FreeGameMem();
		IncProgress();
		LoadGameLevel(FALSE, ENTRY_SETLVL);
		IncProgress();
		break;
	case WM_DIABRTNLVL:
		IncProgress();
		if (!gbIsMultiplayer) {
			SaveLevel();
		} else {
			DeltaSaveLevel();
		}
		IncProgress();
		setlevel = FALSE;
		FreeGameMem();
		IncProgress();
		GetReturnLvlPos();
		LoadGameLevel(FALSE, ENTRY_RTNLVL);
		IncProgress();
		break;
	case WM_DIABWARPLVL:
		IncProgress();
		if (!gbIsMultiplayer) {
			SaveLevel();
		} else {
			DeltaSaveLevel();
		}
		IncProgress();
		FreeGameMem();
		GetPortalLevel();
		IncProgress();
		LoadGameLevel(FALSE, ENTRY_WARPLVL);
		IncProgress();
		break;
	case WM_DIABTOWNWARP:
		IncProgress();
		if (!gbIsMultiplayer) {
			SaveLevel();
		} else {
			DeltaSaveLevel();
		}
		IncProgress();
		FreeGameMem();
		currlevel = plr[myplr].plrlevel;
		leveltype = gnLevelTypeTbl[currlevel];
		assert(plr[myplr].plrlevel == currlevel);
		IncProgress();
		LoadGameLevel(FALSE, ENTRY_TWARPDN);
		IncProgress();
		break;
	case WM_DIABTWARPUP:
		IncProgress();
		if (!gbIsMultiplayer) {
			SaveLevel();
		} else {
			DeltaSaveLevel();
		}
		IncProgress();
		FreeGameMem();
		currlevel = plr[myplr].plrlevel;
		leveltype = gnLevelTypeTbl[currlevel];
		assert(plr[myplr].plrlevel == currlevel);
		IncProgress();
		LoadGameLevel(FALSE, ENTRY_TWARPUP);
		IncProgress();
		break;
	case WM_DIABRETOWN:
		IncProgress();
		if (!gbIsMultiplayer) {
			SaveLevel();
		} else {
			DeltaSaveLevel();
		}
		IncProgress();
		FreeGameMem();
		currlevel = plr[myplr].plrlevel;
		leveltype = gnLevelTypeTbl[currlevel];
		assert(plr[myplr].plrlevel == currlevel);
		IncProgress();
		LoadGameLevel(FALSE, ENTRY_MAIN);
		IncProgress();
		break;
	}

	assert(ghMainWnd);

	PaletteFadeOut(8);
	FreeInterface();

	saveProc = SetWindowProc(saveProc);
	assert(saveProc == DisableInputWndProc);

	NetSendCmdLocParam1(TRUE, CMD_PLAYER_JOINLEVEL, plr[myplr]._px, plr[myplr]._py, plr[myplr].plrlevel);
	plrmsg_delay(FALSE);
	ResetPal();

	if (gbSomebodyWonGameKludge && plr[myplr].plrlevel == 16) {
		PrepDoEnding();
	}

	gbSomebodyWonGameKludge = FALSE;
}

DEVILUTION_END_NAMESPACE
