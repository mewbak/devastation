void TownDead()
{
	int tidx;

	tidx = GetActiveTowner(TOWN_DEADGUY);
	TownCtrlMsg(tidx);

	if(!qtextflag) {
		if(quests[6]._qactive == 2 && !quests[6]._qlog) {
			return;
		}
		if(quests[6]._qactive != 1) {
			towner[tidx]._tAnimDelay = 1000;
			towner[tidx]._tAnimFrame = 1;
			strcpy(towner[tidx]._tName, "Slain Townsman");
		}
	}
	if(quests[6]._qactive != 1) {
		towner[tidx]._tAnimCnt = 0;
	}
}