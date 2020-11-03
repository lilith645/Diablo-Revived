/**
 * @file track.cpp
 *
 * Implementation of functionality tracking what the mouse cursor is pointing at.
 */
#include "all.h"

DEVILUTION_BEGIN_NAMESPACE

void track_process() {
  track_process_continuous_attacks();
}

void track_repeat_walk(BOOL rep)
{
	if (sgbIsWalking == rep)
		return;

	sgbIsWalking = rep;
	if (rep) {
		sgbIsScrolling = FALSE;
		sgdwLastWalk = SDL_GetTicks() - tick_delay;
	} else if (sgbIsScrolling) {
		sgbIsScrolling = FALSE;
	}
}

BOOL track_isscrolling()
{
	return sgbIsScrolling;
}

DEVILUTION_END_NAMESPACE
