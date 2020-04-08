

//from hellfire
BOOL DRLG_L3Anvil()
{
	int sx, sy, sw, sh, xx, yy, ii, trys;
	BOOL found;

	sw = L3ANVIL[0];
	sh = L3ANVIL[1];
	sx = random(0, 40 - sw);
	sy = random(0, 40 - sh);

	found = FALSE;
	trys = 0;
	while (!found && trys < 200) {
		trys++;
		found = TRUE;
		ii = 2;
		for (yy = 0; yy < sh && found == TRUE; yy++) {
			for (xx = 0; xx < sw && found == TRUE; xx++) {
				if (L3ANVIL[ii] != 0 && dungeon[xx + sx][yy + sy] != L3ANVIL[ii]) {
					found = FALSE;
				}
				if (dflags[xx + sx][yy + sy] != 0) {
					found = FALSE;
				}
				ii++;
			}
		}
		if (!found) {
			sx++;
			if (sx == 40 - sw) {
				sx = 0;
				sy++;
				if (sy == 40 - sh) {
					sy = 0;
				}
			}
		}
	}
	if (trys >= 200) {
		return TRUE;
	}

	ii = sw * sh + 2;
	for (yy = 0; yy < sh; yy++) {
		for (xx = 0; xx < sw; xx++) {
			if (L3ANVIL[ii] != 0) {
				dungeon[xx + sx][yy + sy] = L3ANVIL[ii];
			}
			dflags[xx + sx][yy + sy] |= DLRG_PROTECTED;
			ii++;
		}
	}

	setpc_x = sx;
	setpc_y = sy;
	setpc_w = sw;
	setpc_h = sh;

	return FALSE;
}

// add rv
void DRLG_L3MakeMegas()
{
	int i, j, v, rv;

	for (j = 0; j < DMAXY-1; j++) {
		for (i = 0; i < DMAXX-1; i++) {
			v = dungeon[i + 1][j + 1] + 2 * dungeon[i][j + 1] + 4 * dungeon[i + 1][j] + 8 * dungeon[i][j];
			if (v == 6) {
				rv = random(0, 2);
				if (rv == 0) {
					v = 12;
				} else {
					v = 5;
				}
			}
			if (v == 9) {
				rv = random(0, 2);
				if (rv == 0) {
					v = 13;
				} else {
					v = 14;
				}
			}
			dungeon[i][j] = L3ConvTbl[v];
		}
		dungeon[DMAXX-1][j] = 8;
	}
	for (i = 0; i < DMAXX; i++) {
		dungeon[i][DMAXY-1] = 8;
	}
}
// add rv
void DRLG_L3FillStraights()
{
	int i, j, xc, xs, yc, ys, k, rv;

	for (j = 0; j < DMAXY - 1; j++) {
		xs = 0;
		for (i = 0; i < 37; i++) {
			if (dungeon[i][j] == 0 && dungeon[i][j + 1] == 1) {
				if (xs == 0) {
					xc = i;
				}
				xs++;
			} else {
				if (xs > 3 && random(0, 2) != 0) {
					for (k = xc; k < i; k++) {
						rv = random(0, 2);
						dungeon[k][j] = rv;
					}
				}
				xs = 0;
			}
		}
	}
	for (j = 0; j < DMAXY - 1; j++) {
		xs = 0;
		for (i = 0; i < 37; i++) {
			if (dungeon[i][j] == 1 && dungeon[i][j + 1] == 0) {
				if (xs == 0) {
					xc = i;
				}
				xs++;
			} else {
				if (xs > 3 && random(0, 2) != 0) {
					for (k = xc; k < i; k++) {
						rv = random(0, 2);
						dungeon[k][j + 1] = rv;
					}
				}
				xs = 0;
			}
		}
	}
	for (i = 0; i < DMAXX - 1; i++) {
		ys = 0;
		for (j = 0; j < 37; j++) {
			if (dungeon[i][j] == 0 && dungeon[i + 1][j] == 1) {
				if (ys == 0) {
					yc = j;
				}
				ys++;
			} else {
				if (ys > 3 && random(0, 2) != 0) {
					for (k = yc; k < j; k++) {
						rv = random(0, 2);
						dungeon[i][k] = rv;
					}
				}
				ys = 0;
			}
		}
	}
	for (i = 0; i < DMAXX - 1; i++) {
		ys = 0;
		for (j = 0; j < 37; j++) {
			if (dungeon[i][j] == 1 && dungeon[i + 1][j] == 0) {
				if (ys == 0) {
					yc = j;
				}
				ys++;
			} else {
				if (ys > 3 && random(0, 2) != 0) {
					for (k = yc; k < j; k++) {
						rv = random(0, 2);
						dungeon[i + 1][k] = rv;
					}
				}
				ys = 0;
			}
		}
	}
}
//remove continue
void DRLG_L3Wood()
{
	int i, j, x, y, xx, yy, rt, rp, x1, y1, x2, y2;
	BOOL skip;

	for (j = 0; j < DMAXY - 1; j++) { // BUGFIX: Change '0' to '1'
		for (i = 0; i < DMAXX - 1; i++) { // BUGFIX: Change '0' to '1'
			if (dungeon[i][j] == 10 && random(0, 2) != 0) {
				x = i;
				while (dungeon[x][j] == 10) {
					x++;
				}
				x--;
				if (x - i > 0) {
					dungeon[i][j] = 127;
					for (xx = i + 1; xx < x; xx++) {
						if (random(0, 2) != 0) {
							dungeon[xx][j] = 126;
						} else {
							dungeon[xx][j] = 129;
						}
					}
					dungeon[x][j] = 128;
				}
			}
			if (dungeon[i][j] == 9 && random(0, 2) != 0) {
				y = j;
				while (dungeon[i][y] == 9) {
					y++;
				}
				y--;
				if (y - j > 0) {
					dungeon[i][j] = 123;
					for (yy = j + 1; yy < y; yy++) {
						if (random(0, 2) != 0) {
							dungeon[i][yy] = 121;
						} else {
							dungeon[i][yy] = 124;
						}
					}
					dungeon[i][y] = 122;
				}
			}
			if (dungeon[i][j] == 11 && dungeon[i + 1][j] == 10 && dungeon[i][j + 1] == 9 && random(0, 2) != 0) {
				dungeon[i][j] = 125;
				x = i + 1;
				while (dungeon[x][j] == 10) {
					x++;
				}
				x--;
				for (xx = i + 1; xx < x; xx++) {
					if (random(0, 2) != 0) {
						dungeon[xx][j] = 126;
					} else {
						dungeon[xx][j] = 129;
					}
				}
				dungeon[x][j] = 128;
				y = j + 1;
				while (dungeon[i][y] == 9) {
					y++;
				}
				y--;
				for (yy = j + 1; yy < y; yy++) {
					if (random(0, 2) != 0) {
						dungeon[i][yy] = 121;
					} else {
						dungeon[i][yy] = 124;
					}
				}
				dungeon[i][y] = 122;
			}
		}
	}

	for (j = 0; j < DMAXY; j++) { // BUGFIX: Change '0' to '1'
		for (i = 0; i < DMAXX; i++) { // BUGFIX: Change '0' to '1'
			if (dungeon[i][j] == 7 && random(0, 1) == 0 && SkipThemeRoom(i, j)) {
				rt = random(0, 2);
				if (rt == 0) {
					y1 = j;
					while (WoodVertU(i, y1)) {
						y1--;
					}
					y1++;
					y2 = j;
					while (WoodVertD(i, y2)) {
						y2++;
					}
					y2--;
					skip = TRUE;
					if (dungeon[i][y1] == 7) {
						skip = FALSE;
					}
					if (dungeon[i][y2] == 7) {
						skip = FALSE;
					}
					if (y2 - y1 > 1 && skip) {
						rp = random(0, y2 - y1 - 1) + y1 + 1;
						for (y = y1; y <= y2; y++) {
							if (y == rp) {
								continue;
							}
							if (dungeon[i][y] == 7) {
								if (random(0, 2) != 0) {
									dungeon[i][y] = 135;
								} else {
									dungeon[i][y] = 137;
								}
							}
							if (dungeon[i][y] == 10) {
								dungeon[i][y] = 131;
							}
							if (dungeon[i][y] == 126) {
								dungeon[i][y] = 133;
							}
							if (dungeon[i][y] == 129) {
								dungeon[i][y] = 133;
							}
							if (dungeon[i][y] == 2) {
								dungeon[i][y] = 139;
							}
							if (dungeon[i][y] == 134) {
								dungeon[i][y] = 138;
							}
							if (dungeon[i][y] == 136) {
								dungeon[i][y] = 138;
							}
						}
					}
				}
				if (rt == 1) {
					x1 = i;
					while (WoodHorizL(x1, j)) {
						x1--;
					}
					x1++;
					x2 = i;
					while (WoodHorizR(x2, j)) {
						x2++;
					}
					x2--;
					skip = TRUE;
					if (dungeon[x1][j] == 7) {
						skip = FALSE;
					}
					if (dungeon[x2][j] == 7) {
						skip = FALSE;
					}
					if (x2 - x1 > 1 && skip) {
						rp = random(0, x2 - x1 - 1) + x1 + 1;
						for (x = x1; x <= x2; x++) {
							if (x == rp) {
								continue;
							}
							if (dungeon[x][j] == 7) {
								if (random(0, 2) != 0) {
									dungeon[x][j] = 134;
								} else {
									dungeon[x][j] = 136;
								}
							}
							if (dungeon[x][j] == 9) {
								dungeon[x][j] = 130;
							}
							if (dungeon[x][j] == 121) {
								dungeon[x][j] = 132;
							}
							if (dungeon[x][j] == 124) {
								dungeon[x][j] = 132;
							}
							if (dungeon[x][j] == 4) {
								dungeon[x][j] = 140;
							}
							if (dungeon[x][j] == 135) {
								dungeon[x][j] = 138;
							}
							if (dungeon[x][j] == 137) {
								dungeon[x][j] = 138;
							}
						}
					}
				}
			}
		}
	}

	AddFenceDoors();
	FenceDoorFix();
}
