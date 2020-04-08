void L4SaveQuads()
{
	int i, j, x, y;

	x = l4holdx;
	y = l4holdy;
	for (j = 0; j < 14; j++) {
		for (i = 0; i < 14; i++) {
			dflags[i + x][j + y] = 1;
			dflags[DMAXX - 1 - i - x][j + y] = 1;
			dflags[i + x][DMAXY - 1 - j - y] = 1;
			dflags[DMAXX - 1 - i - x][DMAXY - 1 - j - y] = 1;
		}
	}
}

void DRLG_L4(int entry)
{
	int i, j, spi, spj, ga;
	BOOL doneflag;

	do {
		DRLG_InitTrans();
		do {
			InitL4Dungeon();
			L4firstRoom();
			L4FixRim();
			 ga = GetArea();
			if(ga >= 173)
			{
				uShape();
			}
		}
		while(ga < 173);

//firstroom
	xmin = (20 - w) >> 1;
	xmax = 19 - w;
	rndx = xmin + random(0, xmax - xmin + 1);
	if (w + rndx > 19) {
		int tx = w + rndx - 19;
		x = rndx - tx + 1;
		//x = 19 - w + 1;
	} else {
		x = rndx;
	}
	ymin = (20 - h) >> 1;
	ymax = 19 - h;
	rndy = random(0, ymax - ymin + 1);
	rndy += ymin;
	if (h + rndy > 19) {
		int ty = h + rndy - 19;
		y = rndy - ty + 1;
		//y = 19 - h + 1;
	} else {
		y = rndy;
		
void DRLG_L4Subs()
{
	int x, y, i, rv;
	BYTE c;

	for (y = 0; y < DMAXY; y++) {
		for (x = 0; x < DMAXX; x++) {
			rv = random(0, 3);
			if (rv == 0) {
				c = dungeon[x][y];
				c = L4BTYPES[c];
				if (c != 0 && dflags[x][y] == 0) {
					rv = random(0, 16);
					i = -1;
					while (rv >= 0) {
						i++;
						if (i == sizeof(L4BTYPES)) {
							i = 0;
						}
						if (c == L4BTYPES[i]) {
							rv--;
						}
					}
					dungeon[x][y] = i;
				}
			}
		}
	}
	for (y = 0; y < DMAXY; y++) {
		for (x = 0; x < DMAXX; x++) {
			rv = random(0, 10);
			if (rv == 0) {
				c = dungeon[x][y];
				c = L4BTYPES[c];
				if (c == 6 && dflags[x][y] == 0) {
					rv = random(0, 3);
					dungeon[x][y] = rv + 95;
				}
			}
		}
	}
}

void L4makeDmt()
{
	int i, j, val, dmtx, dmty;

	for (j = 0, dmty = 1; dmty <= 77; j++, dmty += 2) {
		for (i = 0, dmtx = 1; dmtx <= 77; i++, dmtx += 2) {
			val = 8 * L4dungeon[dmtx + 1][dmty + 1]
			+ 4 * L4dungeon[dmtx][dmty + 1]
			+ 2 * L4dungeon[dmtx + 1][dmty]
			+ L4dungeon[dmtx][dmty];
			int idx = L4ConvTbl[val];
			dungeon[i][j] = idx;
		}
	}
}