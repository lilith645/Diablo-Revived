/**
 * @file track.cpp
 *
 * Implementation of functionality tracking what the mouse cursor is pointing at.
 */
#include "all.h"

DEVILUTION_BEGIN_NAMESPACE

static BYTE sgbIsScrolling;
static DWORD sgdwLastWalk;
static BOOL sgbIsWalking;
static BYTE sgbCommand;
static WORD sgwParam1;

void track_process()
{
	if (!sgbIsWalking)
		return;

	if (cursmx < 0 || cursmx >= MAXDUNX - 1 || cursmy < 0 || cursmy >= MAXDUNY - 1)
		return;

	if (sgbCommand == CMD_WALKXY && plr[myplr]._pVar8 <= 6 && plr[myplr]._pmode != PM_STAND)
		return;

	if (cursmx != plr[myplr]._ptargx || cursmy != plr[myplr]._ptargy) {
		DWORD tick = SDL_GetTicks();
		if ((int)(tick - sgdwLastWalk) >= tick_delay * 6) {
			sgdwLastWalk = tick;
			/*NetSendCmdLoc(TRUE, CMD_WALKXY, cursmx, cursmy);
			if (!sgbIsScrolling)
				sgbIsScrolling = TRUE;*/
			switch (sgbCommand) {
				case CMD_WALKXY:
					NetSendCmdLoc(TRUE, CMD_WALKXY, cursmx, cursmy);
					if (!sgbIsScrolling)
						sgbIsScrolling = 1;
					break;
				case CMD_SATTACKXY:
				case CMD_RATTACKXY:
					NetSendCmdLoc(TRUE, sgbCommand, cursmx, cursmy);
					break;
				case CMD_ATTACKID:
				case CMD_RATTACKID:
					if (pcursmonst != sgwParam1)
						return;
					NetSendCmdParam1(TRUE, sgbCommand, pcursmonst);
					break;
			}
		}
	}
}

void track_lmb_loc(BYTE bCmd, BYTE x, BYTE y) {
	NetSendCmdLoc(TRUE, bCmd, x, y);
	sgbCommand = bCmd;
}

void track_lmb_param1(BYTE bCmd, WORD wParam1) {
	NetSendCmdParam1(TRUE, bCmd, wParam1);
	sgbCommand = bCmd;
	sgwParam1 = wParam1;
}

void track_repeat_walk(BOOL rep)
{
	if (sgbIsWalking == rep)
		return;

	sgbIsWalking = rep;
	if (rep) {
		sgbIsScrolling = FALSE;
		sgdwLastWalk = SDL_GetTicks() - tick_delay;
		//NetSendCmdLoc(TRUE, CMD_WALKXY, cursmx, cursmy);
	} else if (sgbIsScrolling) {
		sgbIsScrolling = FALSE;
	}
}

BOOL track_isscrolling()
{
	return sgbIsScrolling;
}

DEVILUTION_END_NAMESPACE
