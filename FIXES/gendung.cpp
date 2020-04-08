void DRLG_InitTrans()
{
	memset(dTransVal, 0, sizeof(dTransVal));
	memset(TransList, 0, sizeof(TransList));
	TransVal = 1;
}

void DRLG_RectTrans(int x1, int y1, int x2, int y2)
{
	int i, j;

	for(j = y1; j <= y2; j++) {
		for(i = x1; i <= x2; i++) {
			dTransVal[i][j] = TransVal;
		}
	}

	TransVal++;
}

void DRLG_ListTrans(int num, BYTE *List)
{
	int i;
	BYTE x1, y1, x2, y2;

	for(i = 0; i < num; i++) {
		x1 = *List++;
		y1 = *List++;
		x2 = *List++;
		y2 = *List++;
		DRLG_RectTrans(x1, y1, x2, y2);
	}
}

void DRLG_AreaTrans(int num, BYTE *List)
{
	int i;
	BYTE x1, y1, x2, y2;

	for(i = 0; i < num; i++) {
		x1 = *List++;
		y1 = *List++;
		x2 = *List++;
		y2 = *List++;
		DRLG_RectTrans(x1, y1, x2, y2);
		TransVal--;
	}

	TransVal++;
}

void DRLG_PlaceThemeRooms(int minSize, int maxSize, int floor, int freq, BOOL rndSize)
{
	int i, j, themeW, themeH;
	int rv, rv2, min, max;

	themeCount = 0;
	memset(themeLoc, 0, sizeof(*themeLoc));

	for(j = 0; j < 40; j++) {
		for(i = 0; i < 40; i++) {
			if(dungeon[i][j] == floor && random(0, freq) == 0) {
				if(DRLG_WillThemeRoomFit(floor, i, j, minSize, maxSize, &themeW, &themeH)) {
					if(rndSize) {
						min = minSize - 2;
						max = maxSize - 2;
						rv = random(0, themeW - min + 1);
						rv2 = random(0, rv) + min;
						if(rv2 >= min && rv2 <= max) {
							themeW = rv2;
						} else {
							themeW = min;
						}
						rv = random(0, themeH - min + 1);
						rv2 = random(0, rv) + min;
						if(rv2 >= min && rv2 <= max) {
							themeH = rv2;
						} else {
							themeH = min;
						}
					}
					themeLoc[themeCount].x = i + 1;
					themeLoc[themeCount].y = j + 1;
					themeLoc[themeCount].width = themeW;
					themeLoc[themeCount].height = themeH;
					if(leveltype == DTYPE_CAVES) {
						DRLG_RectTrans(2 * (i + 2) + 16, 2 * (j + 2) + 16, 2 * (i + themeW - 1) + 17, 2 * (j + themeH - 1) + 17);
					} else {
						DRLG_MRectTrans(i + 1, j + 1, i + themeW, j + themeH);
					}
					themeLoc[themeCount].ttval = TransVal - 1;
					DRLG_CreateThemeRoom(themeCount);
					themeCount++;
				}
			}
		}
	}
}

BOOL SkipThemeRoom(int x, int y)
{
	int i;

	for(i = 0; i < themeCount; i++) {
		if(x >= themeLoc[i].x - 2 && x <= themeLoc[i].x + themeLoc[i].width + 2
		&& y >= themeLoc[i].y - 2 && y <= themeLoc[i].y + themeLoc[i].height + 2) {
			return FALSE;
		}
	}

	return TRUE;
}