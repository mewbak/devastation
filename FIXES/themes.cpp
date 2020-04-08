BOOL TFit_Shrine(int i)
{
	int xp, yp, found;

	/// ASSERT: assert((DWORD)i < MAXTHEMES);

	xp = 0;
	yp = 0;
	found = 0;
	while(found == 0) {
		if(dTransVal[xp][yp] == themes[i].ttval) {
			if(nTrapTable[dPiece[xp][yp - 1]]
			&& !nSolidTable[dPiece[xp - 1][yp]]
			&& !nSolidTable[dPiece[xp + 1][yp]]
			&& dTransVal[xp - 1][yp] == themes[i].ttval
			&& dTransVal[xp + 1][yp] == themes[i].ttval
			&& dObject[xp - 1][yp - 1] == 0
			&& dObject[xp + 1][yp - 1] == 0) {
				found = 1;
			}
			if(found == 0
			&& nTrapTable[dPiece[xp - 1][yp]]
			&& !nSolidTable[dPiece[xp][yp - 1]]
			&& !nSolidTable[dPiece[xp][yp + 1]]
			&& dTransVal[xp][yp - 1] == themes[i].ttval
			&& dTransVal[xp][yp + 1] == themes[i].ttval
			&& dObject[xp - 1][yp - 1] == 0
			&& dObject[xp - 1][yp + 1] == 0) {
				found = 2;
			}
		}
		if(found == 0) {
			xp++;
			if(xp == MAXDUNX) {
				xp = 0;
				yp++;
				if(yp == MAXDUNY) {
					return FALSE;
				}
			}
		}
	}

	themex = xp;
	themey = yp;
	themeVar1 = found;
	return TRUE;
}

BOOL TFit_Obj5(int t)
{
	int xp, yp, i, r, rs;
	BOOL found;

	/// ASSERT: assert((DWORD)t < MAXTHEMES);

	xp = 0;
	yp = 0;
	r = random(0, 5) + 1;
	rs = r;
	while(r > 0) {
		found = FALSE;
		if(dTransVal[xp][yp] == themes[t].ttval && !nSolidTable[dPiece[xp][yp]]) {
			found = TRUE;
			for(i = 0; found && i < 25; i++) {
				if(nSolidTable[dPiece[xp + trm5x[i]][yp + trm5y[i]]]) {
					found = FALSE;
				}
				if(dTransVal[xp + trm5x[i]][yp + trm5y[i]] != themes[t].ttval) {
					found = FALSE;
				}
			}
		}
		if(!found) {
			xp++;
			if(xp == MAXDUNX) {
				xp = 0;
				yp++;
				if(yp == MAXDUNY) {
					if(r == rs) {
						return FALSE;
					}
					yp = 0;
				}
			}
			continue;
		}
		r--;
	}

	themex = xp;
	themey = yp;
	return TRUE;
}

BOOL TFit_SkelRoom(int t)
{
	int i;

	if(leveltype != DTYPE_CATHEDRAL && leveltype != DTYPE_CATACOMBS) {
		return FALSE;
	}

	for(i = 0; i < nummtypes; i++) {
		if(IsSkel(Monsters[i].mtype)) {
			themeVar1 = i;
			return TFit_Obj5(t);
		}
	}

	return FALSE;
}

BOOL TFit_GoatShrine(int t)
{
	int i;

	for(i = 0; i < nummtypes; i++) {
		if(IsGoat(Monsters[i].mtype)) {
			themeVar1 = i;
			return TFit_Obj5(t);
		}
	}

	return FALSE;
}

BOOL CheckThemeObj3(int xp, int yp, int t, int f)
{
	int i;

	/// ASSERT: assert((DWORD)t < MAXTHEMES);

	for(i = 0; i < 9; i++) {
		if(xp + trm3x[i] < 0 || yp + trm3y[i] < 0) {
			return FALSE;
		}
		if(nSolidTable[dPiece[xp + trm3x[i]][yp + trm3y[i]]]) {
			return FALSE;
		}
		if(dTransVal[xp + trm3x[i]][yp + trm3y[i]] != themes[t].ttval) {
			return FALSE;
		}
		if(dObject[xp + trm3x[i]][yp + trm3y[i]] != 0) {
			return FALSE;
		}
		if(f != -1 && random(0, f) == 0) {
			return FALSE;
		}
	}

	return TRUE;
}

BOOL TFit_Obj3(int t)
{
	int xp, yp;
	char objrnd[4] = { 4, 4, 3, 5 };

	for(yp = 1; yp < MAXDUNY - 1; yp++) {
		for(xp = 1; xp < MAXDUNX - 1; xp++) {
			if(CheckThemeObj3(xp, yp, t, objrnd[leveltype - 1])) {
				themex = xp;
				themey = yp;
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CheckThemeReqs(int t)
{
	BOOL rv;

	rv = TRUE;
	switch(t) {
	case THEME_SHRINE:
	case THEME_LIBRARY:
		if(leveltype == DTYPE_CAVES || leveltype == DTYPE_HELL) {
			rv = FALSE;
		}
		break;
	case THEME_SKELROOM:
		if(leveltype == DTYPE_CAVES || leveltype == DTYPE_HELL) {
			rv = FALSE;
		}
		break;
	case THEME_BLOODFOUNTAIN:
		if(!bFountainFlag) {
			rv = FALSE;
		}
		break;
	case THEME_PURIFYINGFOUNTAIN:
		if(!pFountainFlag) {
			rv = FALSE;
		}
		break;
	case THEME_MURKYFOUNTAIN:
		if(!mFountainFlag) {
			rv = FALSE;
		}
		break;
	case THEME_TEARFOUNTAIN:
		if(!tFountainFlag) {
			rv = FALSE;
		}
		break;
	case THEME_ARMORSTAND:
	case THEME_WEAPONRACK:
		if(leveltype == DTYPE_CATHEDRAL) {
			rv = FALSE;
		}
		break;
	case THEME_CAULDRON:
		if(leveltype != DTYPE_HELL || !cauldronFlag) {
			rv = FALSE;
		}
		break;
	}

	return rv;
}

BOOL SpecialThemeFit(int i, int t)
{
	BOOL rv;

	rv = CheckThemeReqs(t);
	switch(t) {
	case THEME_SHRINE:
	case THEME_LIBRARY:
		if(rv) {
			rv = TFit_Shrine(i);
		}
		break;
	case THEME_SKELROOM:
		if(rv) {
			rv = TFit_SkelRoom(i);
		}
		break;
	case THEME_BLOODFOUNTAIN:
		if(rv) {
			rv = TFit_Obj5(i);
		}
		if(rv) {
			bFountainFlag = FALSE;
		}
		break;
	case THEME_PURIFYINGFOUNTAIN:
		if(rv) {
			rv = TFit_Obj5(i);
		}
		if(rv) {
			pFountainFlag = FALSE;
		}
		break;
	case THEME_MURKYFOUNTAIN:
		if(rv) {
			rv = TFit_Obj5(i);
		}
		if(rv) {
			mFountainFlag = FALSE;
		}
		break;
	case THEME_TEARFOUNTAIN:
		if(rv) {
			rv = TFit_Obj5(i);
		}
		if(rv) {
			tFountainFlag = FALSE;
		}
		break;
	case THEME_CAULDRON:
		if(rv) {
			rv = TFit_Obj5(i);
		}
		if(rv) {
			cauldronFlag = FALSE;
		}
		break;
	case THEME_GOATSHRINE:
		if(rv) {
			rv = TFit_GoatShrine(i);
		}
		break;
	case THEME_TORTURE:
	case THEME_DECAPITATED:
	case THEME_ARMORSTAND:
	case THEME_BRNCROSS:
	case THEME_WEAPONRACK:
		if(rv) {
			rv = TFit_Obj3(i);
		}
		break;
	case THEME_TREASURE:
		rv = treasureFlag;
		if(rv) {
			treasureFlag = FALSE;
		}
		break;
	}

	return rv;
}

BOOL CheckThemeRoom(int tv)
{
	int i, j, tarea;

	for(i = 0; i < numtrigs; i++) {
		if(dTransVal[trigs[i]._tx][trigs[i]._ty] == tv) {
			return FALSE;
		}
	}

	tarea = 0;
	for(j = 0; j < MAXDUNY; j++) {
		for(i = 0; i < MAXDUNX; i++) {
			if(dTransVal[i][j] == tv) {
				if(dFlags[i][j] & 8) {
					return FALSE;
				}
				tarea++;
			}
		}
	}
	if(leveltype == DTYPE_CATHEDRAL && (tarea < 9 || tarea > 100)) {
		return FALSE;
	}

	for(j = 0; j < MAXDUNY; j++) {
		for(i = 0; i < MAXDUNX; i++) {
			if(dTransVal[i][j] == tv && !nSolidTable[dPiece[i][j]]) {
				if(dTransVal[i - 1][j] != tv && !nSolidTable[dPiece[i - 1][j]]) {
					return FALSE;
				}
				if(dTransVal[i + 1][j] != tv && !nSolidTable[dPiece[i + 1][j]]) {
					return FALSE;
				}
				if(dTransVal[i][j - 1] != tv && !nSolidTable[dPiece[i][j - 1]]) {
					return FALSE;
				}
				if(dTransVal[i][j + 1] != tv && !nSolidTable[dPiece[i][j + 1]]) {
					return FALSE;
				}
			}
		}
	}

	return TRUE;
}

void InitThemes()
{
	int i, t;

	numthemes = 0;
	zharlib = -1;
	armorFlag = TRUE;
	bFountainFlag = TRUE;
	cauldronFlag = TRUE;
	mFountainFlag = TRUE;
	pFountainFlag = TRUE;
	tFountainFlag = TRUE;
	treasureFlag = TRUE;
	bCrossFlag = FALSE;
	weaponFlag = TRUE;

	if(currlevel == 16) {
		return;
	}

	if(leveltype == DTYPE_CATHEDRAL) {
		for(i = 0; i < 4; i++) {
			ThemeGoodIn[i] = 0;
		}
		for(i = 0; i < 256 && numthemes < MAXTHEMES; i++) {
			if(CheckThemeRoom(i)) {
				themes[numthemes].ttval = i;
				t = ThemeGood[random(0, 4)];
				while(!SpecialThemeFit(numthemes, t)) {
					t = random(0, 17);
				}
				themes[numthemes].ttype = t;
				numthemes++;
			}
		}
	}
	if(leveltype == DTYPE_CATACOMBS || leveltype == DTYPE_CAVES || leveltype == DTYPE_HELL) {
		/// ASSERT: assert((DWORD)themeCount < MAXTHEMES);
		for(i = 0; i < themeCount; i++) {
			themes[i].ttype = -1;
		}
		if(QuestStatus(QTYPE_ZHAR)) {
			for(i = 0; i < themeCount; i++) {
				themes[i].ttval = themeLoc[i].ttval;
				if(SpecialThemeFit(i, THEME_LIBRARY)) {
					themes[i].ttype = THEME_LIBRARY;
					zharlib = i;
					break;
				}
			}
		}
		for(i = 0; i < themeCount; i++) {
			if(themes[i].ttype == -1) {
				themes[i].ttval = themeLoc[i].ttval;
				t = ThemeGood[random(0, 4)];
				while(!SpecialThemeFit(i, t)) {
					t = random(0, 17);
				}
				themes[i].ttype = t;
			}
		}
		numthemes += themeCount;
	}
}

void HoldThemeRooms()
{
	int i, x, y;
	char v;

	if(currlevel == 16) {
		return;
	}

	/// ASSERT: assert((DWORD)numthemes < MAXTHEMES);

	if(leveltype == DTYPE_CATHEDRAL) {
		for(i = 0; i < numthemes; i++) {
			v = themes[i].ttval;
			for(y = 0; y < MAXDUNY; y++) {
				for(x = 0; x < MAXDUNX; x++) {
					if(dTransVal[x][y] == v) {
						dFlags[x][y] |= 8;
					}
				}
			}
		}
	} else {
		DRLG_HoldThemeRooms();
	}
}

void PlaceThemeMonsts(int t, int f)
{
	int xp, yp, mtype, numscattypes, i;
	int scattertypes[111];

	numscattypes = 0;
	/// ASSERT: assert((DWORD)t < MAXTHEMES);

	for(i = 0; i < nummtypes; i++) {
		if(Monsters[i].mPlaceFlags & 1) {
			scattertypes[numscattypes++] = i;
		}
	}

	mtype = scattertypes[random(0, numscattypes)];

	for(yp = 0; yp < MAXDUNY; yp++) {
		for(xp = 0; xp < MAXDUNX; xp++) {
			if(dTransVal[xp][yp] == themes[t].ttval
			&& !nSolidTable[dPiece[xp][yp]]
			&& dItem[xp][yp] == 0
			&& dObject[xp][yp] == 0
			&& random(0, f) == 0) {
				AddMonster(xp, yp, random(0, 8), mtype, 1);
			}
		}
	}
}

void Theme_Barrel(int t)
{
	int xp, yp, r;
	char barrnd[4] = { 2, 6, 4, 8 };
	char monstrnd[4] = { 5, 7, 3, 9 };

	/// ASSERT: assert((DWORD)t < MAXTHEMES);

	for(yp = 0; yp < MAXDUNY; yp++) {
		for(xp = 0; xp < MAXDUNX; xp++) {
			if(dTransVal[xp][yp] == themes[t].ttval
			&& !nSolidTable[dPiece[xp][yp]]
			&& random(0, barrnd[leveltype - 1]) == 0) {
				if(random(0, barrnd[leveltype - 1]) == 0) {
					r = OBJ_BARREL;
				} else {
					r = OBJ_BARRELEX;
				}
				AddObject(r, xp, yp);
			}
		}
	}

	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
}

void Theme_Shrine(int t)
{
	char monstrnd[4] = { 6, 6, 3, 9 };

	TFit_Shrine(t);

	if(themeVar1 == 1) {
		AddObject(OBJ_CANDLE2, themex - 1, themey);
		AddObject(OBJ_SHRINER, themex, themey);
		AddObject(OBJ_CANDLE2, themex + 1, themey);
	} else {
		AddObject(OBJ_CANDLE2, themex, themey - 1);
		AddObject(OBJ_SHRINEL, themex, themey);
		AddObject(OBJ_CANDLE2, themex, themey + 1);
	}

	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
}

void Theme_MonstPit(int t)
{
	int r, ixp, iyp;
	char monstrnd[4] = { 6, 7, 3, 9 };

	/// ASSERT: assert((DWORD)t < MAXTHEMES);

	r = random(0, 100) + 1;
	ixp = 0;
	iyp = 0;
	while(r > 0) {
		if(dTransVal[ixp][iyp] == themes[t].ttval && !nSolidTable[dPiece[ixp][iyp]]) {
			r--;
		}
		if(r > 0) {
			ixp++;
			if(ixp == MAXDUNX) {
				ixp = 0;
				iyp++;
				if(iyp == MAXDUNY) {
					iyp = 0;
				}
			}
		}
	}

	CreateRndItem(ixp, iyp, TRUE, FALSE, TRUE);
	ItemNoFlippy();
	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
}

void Theme_Treasure(int t)
{
	int xp, yp, i, rv, s;
	char treasrnd[4] = { 4, 9, 7, 10 };
	char monstrnd[4] = { 6, 8, 3, 7 };

	/// ASSERT: assert((DWORD)t < MAXTHEMES);

	s = GetRndSeed(); /* unused */

	for(yp = 0; yp < MAXDUNY; yp++) {
		for(xp = 0; xp < MAXDUNX; xp++) {
			if(dTransVal[xp][yp] == themes[t].ttval && !nSolidTable[dPiece[xp][yp]]) {
				rv = random(0, treasrnd[leveltype - 1]);
				if(2 * random(0, treasrnd[leveltype - 1]) == 0) { /// BUGFIX: 'random(0, 2 * treasrnd[leveltype - 1]) == 0'
					CreateTypeItem(xp, yp, FALSE, ITYPE_GOLD, IMISC_NONE, FALSE, TRUE);
					ItemNoFlippy();
				}
				if(rv == 0) {
					CreateRndItem(xp, yp, FALSE, FALSE, TRUE);
					ItemNoFlippy();
				}
				if(rv == 0 || rv >= treasrnd[leveltype - 1] - 2) {
					i = ItemNoFlippy();
					if(rv >= treasrnd[leveltype - 1] - 2 && leveltype != DTYPE_CATHEDRAL) {
						item[i]._ivalue >>= 1;
					}
				}
			}
		}
	}

	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
}