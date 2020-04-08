void StartPlayerKill(int pnum, int earflag)
{
	int i, pdd;
	BOOL diablolevel;
	ItemStruct *pi;
	PlayerStruct *p;
	ItemStruct ear;

	p = &plr[pnum];
	if(p->_pHitPoints <= 0 && p->_pmode == PM_DEATH) {
		return;
	}

	if(myplr == pnum) {
		NetSendCmdParam1(TRUE, CMD_PLRDEAD, earflag);
	}

	diablolevel = gbMaxPlayers > 1 && plr[pnum].plrlevel == 16;

	if((DWORD)pnum >= MAX_PLRS) {
		app_fatal("StartPlayerKill: illegal player %d", pnum);
	}

	if(plr[pnum]._pClass == PC_WARRIOR) {
		PlaySfxLoc(PS_DEAD, p->WorldX, p->WorldY); /// BUGFIX: use `PS_WARR71` like other classes?
	} else if(plr[pnum]._pClass == PC_ROGUE) {
		PlaySfxLoc(PS_ROGUE71, p->WorldX, p->WorldY);
	} else if(plr[pnum]._pClass == PC_SORCERER) {
		PlaySfxLoc(PS_MAGE71, p->WorldX, p->WorldY);
	}

	if(p->_pgfxnum != 0) {
		p->_pgfxnum = 0;
		p->_pGFXLoad = 0;
		SetPlrAnims(pnum);
	}
	if(!(p->_pGFXLoad & 0x80)) {
		LoadPlrGFX(pnum, 128);
	}

	NewPlrAnim(pnum, p->_pDAnim[p->_pdir], p->_pDFrames, 1, p->_pDWidth);
	p->_pmode = PM_DEATH;
	p->_pBlockFlag = 0;
	p->_pInvincible = 1;
	SetPlayerHitPoints(pnum, 0);
	p->_pVar8 = 1;

	if(pnum != myplr && earflag == 0 && !diablolevel) {
		pi = p->InvBody;
		i = NUM_INVLOC;
		while(i--) {
			pi->_itype = -1;
			pi++;
		}
		CalcPlrInv(pnum, FALSE);
	}
	if(plr[pnum].plrlevel == currlevel) {
		FixPlayerLocation(pnum, p->_pdir);
		RemovePlrFromMap(pnum);
		dFlags[p->WorldX][p->WorldY] |= 4;
		SetPlayerOld(pnum);
		if(pnum == myplr) {
			drawhpflag = 1;
			deathdelay = 30;
			if(pcurs >= CURSOR_FIRSTITEM) {
				PlrDeadItem(pnum, &p->HoldItem, 0, 0);
				SetCursor_(CURSOR_HAND);
			}
			if(!diablolevel) {
				DropHalfPlayersGold(pnum);
				if(earflag != -1) {
					if(earflag != 0) {
						SetPlrHandItem(&ear, IDI_EAR);
						sprintf(ear._iName, "Ear of %s", plr[pnum]._pName);
						if(plr[pnum]._pClass == PC_SORCERER) {
							ear._iCurs = 19;
						} else if(plr[pnum]._pClass == PC_WARRIOR) {
							ear._iCurs = 20;
						} else if(plr[pnum]._pClass == PC_ROGUE) {
							ear._iCurs = 21;
						}
						ear._iCreateInfo = plr[pnum]._pName[0] << 8 | plr[pnum]._pName[1];
						ear._iSeed = plr[pnum]._pName[2] << 24 | plr[pnum]._pName[3] << 16 | plr[pnum]._pName[4] << 8 | plr[pnum]._pName[5];
						ear._ivalue = plr[pnum]._pLevel;
						if(FindGetItem(IDI_EAR, ear._iCreateInfo, ear._iSeed) == -1) {
							PlrDeadItem(pnum, &ear, 0, 0);
						}
					} else {
						pi = p->InvBody;
						i = NUM_INVLOC;
						while(i--) {
							pdd = (i + p->_pdir) & 7;
							PlrDeadItem(pnum, pi, offset_x[pdd], offset_y[pdd]);
							pi++;
						}
						CalcPlrInv(pnum, FALSE);
					}
				}
			}
		}
	}

	SetPlayerHitPoints(pnum, 0);
}