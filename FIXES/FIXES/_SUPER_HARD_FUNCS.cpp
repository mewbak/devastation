void MAI_Lazhelp(int i)
{
	int mx, my;
	int md; /* fix */
	MonsterStruct *Monst;
	char df;

	if((DWORD)i >= MAXMONSTERS) {
		app_fatal("MAI_Lazhelp: Invalid monster %d", i);
	}

	Monst = &monster[i];
	if(Monst->_mmode != MM_STAND) {
		return;
	}

	mx = Monst->_mx;
	my = Monst->_my;
	M_GetDir(i); // leave no md

	if(dFlags[mx][my] & 2) {
		if(gbMaxPlayers == 1) {
			if(quests[Q_BETRAYER]._qvar1 <= 5) {
				Monst->_mgoal = 6;
			} else {
				Monst->_mgoal = 1;
				Monst->mtalkmsg = 0;
			}
		} else if(gbMaxPlayers != 1) {
			Monst->_mgoal = 1;
		}
	}
	if(Monst->_mgoal == 1) {
		MAI_Succ(i);
	}

	monster[i]._mdir = md; // change to mx, either will be min diff

	if(Monst->_mmode == MM_STAND) {
		Monst->_mAnimData = Monst->MType->Anims[0].Frames[md];
	}
}