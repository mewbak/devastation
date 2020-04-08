#include "diablo.h"
#include "../3rdParty/Storm/Source/storm.h"

int light_table_index; // weak
int PitchTbl[1024];
DWORD sgdwCursWdtOld; // idb
DWORD sgdwCursX; // idb
DWORD sgdwCursY; // idb
unsigned char *gpBufEnd; // weak
DWORD sgdwCursHgt;
int level_cel_block; // weak
DWORD sgdwCursXOld; // idb
DWORD sgdwCursYOld; // idb
char arch_draw_type; // weak
DDSURFACEDESC DDS_desc;
int cel_transparency_active; // weak
int level_piece_id; // weak
DWORD sgdwCursWdt;
void (*DrawPlrProc)(int, int, int, int, int, BYTE *, int, int, int, int);
BYTE sgSaveBack[8192];
int draw_monster_num; // weak
DWORD sgdwCursHgtOld; // idb

/* data */

/* used in 1.00 debug */
char *szMonModeAssert[18] =
{
	"standing",
	"walking (1)",
	"walking (2)",
	"walking (3)",
	"attacking",
	"getting hit",
	"dying",
	"attacking (special)",
	"fading in",
	"fading out",
	"attacking (ranged)",
	"standing (special)",
	"attacking (special ranged)",
	"delaying",
	"charging",
	"stoned",
	"healing",
	"talking"
};

char *szPlrModeAssert[12] =
{
	"standing",
	"walking (1)",
	"walking (2)",
	"walking (3)",
	"attacking (melee)",
	"attacking (ranged)",
	"blocking",
	"getting hit",
	"dying",
	"casting a spell",
	"changing levels",
	"quitting"
};

void ClearCursor() // CODE_FIX: this was supposed to be in cursor.cpp
{
	sgdwCursWdt = 0;
	sgdwCursWdtOld = 0;
}

static void scrollrt_draw_cursor_back_buffer()
{
	int i;
	BYTE *src, *dst;

	if(sgdwCursWdt == 0) {
		return;
	}

	/// ASSERT: assert(gpBuffer);
	src = sgSaveBack;
	dst = &gpBuffer[SCREENXY(sgdwCursX, sgdwCursY)];

	for(i = sgdwCursHgt; i != 0; i--, src += sgdwCursWdt, dst += 768) {
		memcpy(dst, src, sgdwCursWdt);
	}

	sgdwCursXOld = sgdwCursX;
	sgdwCursYOld = sgdwCursY;
	sgdwCursWdtOld = sgdwCursWdt;
	sgdwCursHgtOld = sgdwCursHgt;
	sgdwCursWdt = 0;
}

static void scrollrt_draw_cursor_item()
{
	int i, mx, my, col;
	BYTE *src, *dst;

	/// ASSERT: assert(! sgdwCursWdt);

	if(pcurs <= 0 || cursW == 0 || cursH == 0) {
		return;
	}

	mx = MouseX - 1;
	if(mx < 0) {
		mx = 0;
	} else if(mx > 640 - 1) {
		return;
	}
	my = MouseY - 1;
	if(my < 0) {
		my = 0;
	} else if(my > 480 - 1) {
		return;
	}

	sgdwCursX = mx;
	sgdwCursWdt = sgdwCursX + cursW + 1;
	if(sgdwCursWdt > 640 - 1) {
		sgdwCursWdt = 640 - 1;
	}
	sgdwCursX &= ~3;
	sgdwCursWdt |= 3;
	sgdwCursWdt -= sgdwCursX;
	sgdwCursWdt++;

	sgdwCursY = my;
	sgdwCursHgt = sgdwCursY + cursH + 1;
	if(sgdwCursHgt > 480 - 1) {
		sgdwCursHgt = 480 - 1;
	}
	sgdwCursHgt -= sgdwCursY;
	sgdwCursHgt++;

	/// ASSERT: assert(sgdwCursWdt * sgdwCursHgt < sizeof sgSaveBack);
	/// ASSERT: assert(gpBuffer);
	dst = sgSaveBack;
	src = &gpBuffer[SCREENXY(sgdwCursX, sgdwCursY)];

	for(i = sgdwCursHgt; i != 0; i--, dst += sgdwCursWdt, src += 768) {
		memcpy(dst, src, sgdwCursWdt);
	}

	mx++;
	my++;
	gpBufEnd = &gpBuffer[PitchTbl[640] - cursW - 2];

	if(pcurs >= CURSOR_FIRSTITEM) {
		col = PAL16_YELLOW + 5;
		if(plr[myplr].HoldItem._iMagical != 0) {
			col = PAL16_BLUE + 5;
		}
		if(!plr[myplr].HoldItem._iStatFlag) {
			col = PAL16_RED + 5;
		}
		CelDrawHdrClrHL(col, mx + 64, my + cursH + 160 - 1, (BYTE *)pCursCels, pcurs, cursW, 0, 8);
		if(col != PAL16_RED + 5) {
			Cel2DrawHdrOnly(mx + 64, my + cursH + 160 - 1, (BYTE *)pCursCels, pcurs, cursW, 0, 8);
		} else {
			Cel2DrawHdrLightRed(mx + 64, my + cursH + 160 - 1, (BYTE *)pCursCels, pcurs, cursW, 0, 8, 1);
		}
	} else {
		Cel2DrawHdrOnly(mx + 64, my + cursH + 160 - 1, (BYTE *)pCursCels, pcurs, cursW, 0, 8);
	}
}

void DrawMissile(int x, int y, int sx, int sy, int a5, int a6, BOOL pre)
{
	int i, mx, my, nCel;
	MissileStruct *m;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	if(dMissile[x][y] == -1) {
		for(i = 0; i < nummissiles; i++) {
			/// ASSERT: assert(missileactive[i] < MAXMISSILES);
			if(missileactive[i] >= MAXMISSILES)
				break;
			m = &missile[missileactive[i]];
			if(m->_mix == x && m->_miy == y && m->_miPreFlag == pre && m->_miDrawFlag) {
				pCelBuff = m->_miAnimData;
				if(!pCelBuff) {
					// app_fatal("Draw Missile type %d: NULL Cel Buffer", m->_mitype);
					return;
				}
				nCel = m->_miAnimFrame;
				pFrameTable = (DWORD *)pCelBuff;
				if(nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
					// app_fatal("Draw Missile: frame %d of %d, missile type==%d", nCel, pFrameTable[0], m->_mitype);
					return;
				}
				mx = sx + m->_mixoff - m->_miAnimWidth2;
				my = sy + m->_miyoff;
				if(m->_miUniqTrans)
					Cl2DecodeFrm3(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, a5, a6, m->_miUniqTrans + 3);
				else if(m->_miLightFlag)
					Cl2DecodeLightTbl(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, a5, a6);
				else
					Cl2DecodeFrm1(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, a5, a6);
			}
		}
	} else {
		m = &missile[dMissile[x][y] - 1];
		if(m->_miPreFlag == pre && m->_miDrawFlag) {
			pCelBuff = m->_miAnimData;
			if(!pCelBuff) {
				// app_fatal("Draw Missile 2 type %d: NULL Cel Buffer", m->_mitype);
				return;
			}
			nCel = m->_miAnimFrame;
			pFrameTable = (DWORD *)pCelBuff;
			if(nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
				// app_fatal("Draw Missile 2: frame %d of %d, missile type==%d", nCel, pFrameTable[0], m->_mitype);
				return;
			}
			mx = sx + m->_mixoff - m->_miAnimWidth2;
			my = sy + m->_miyoff;
			if(m->_miUniqTrans)
				Cl2DecodeFrm3(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, a5, a6, m->_miUniqTrans + 3);
			else if(m->_miLightFlag)
				Cl2DecodeLightTbl(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, a5, a6);
			else
				Cl2DecodeFrm1(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, a5, a6);
		}
	}
}

void DrawClippedMissile(int x, int y, int sx, int sy, int a5, int a6, BOOL pre)
{
	int i, mx, my, nCel;
	MissileStruct *m;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	if(dMissile[x][y] == -1) {
		for(i = 0; i < nummissiles; i++) {
			/// ASSERT: assert(missileactive[i] < MAXMISSILES);
			if(missileactive[i] >= MAXMISSILES)
				break;
			m = &missile[missileactive[i]];
			if(m->_mix == x && m->_miy == y && m->_miPreFlag == pre && m->_miDrawFlag) {
				pCelBuff = m->_miAnimData;
				if(!pCelBuff) {
					// app_fatal("Draw Missile type %d Clipped: NULL Cel Buffer", m->_mitype);
					return;
				}
				nCel = m->_miAnimFrame;
				pFrameTable = (DWORD *)pCelBuff;
				if(nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
					// app_fatal("Draw Clipped Missile: frame %d of %d, missile type==%d", nCel, pFrameTable[0], m->_mitype);
					return;
				}
				mx = sx + m->_mixoff - m->_miAnimWidth2;
				my = sy + m->_miyoff;
				if(m->_miUniqTrans)
					Cl2DecodeFrm5(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, a5, a6, m->_miUniqTrans + 3);
				else if(m->_miLightFlag)
					Cl2DecodeFrm6(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, a5, a6);
				else
					Cl2DecodeFrm4(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, a5, a6);
			}
		}
	} else {
		m = &missile[dMissile[x][y] - 1];
		if(m->_miPreFlag == pre && m->_miDrawFlag) {
			pCelBuff = m->_miAnimData;
			if(!pCelBuff) {
				// app_fatal("Draw Missile 2 type %d Clipped: NULL Cel Buffer", m->_mitype);
				return;
			}
			nCel = m->_miAnimFrame;
			pFrameTable = (DWORD *)pCelBuff;
			if(nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
				// app_fatal("Draw Clipped Missile 2: frame %d of %d, missile type==%d", nCel, pFrameTable[0], m->_mitype);
				return;
			}
			mx = sx + m->_mixoff - m->_miAnimWidth2;
			my = sy + m->_miyoff;
			if(m->_miUniqTrans)
				Cl2DecodeFrm5(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, a5, a6, m->_miUniqTrans + 3);
			else if(m->_miLightFlag)
				Cl2DecodeFrm6(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, a5, a6);
			else
				Cl2DecodeFrm4(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, a5, a6);
		}
	}
}

static void DrawMonster(int x, int y, int mx, int my, int m, int a6, int a7)
{
	int nCel;
	char trans;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	if((DWORD)m >= MAXMONSTERS) {
		// app_fatal("Draw Monster: tried to draw illegal monster %d", m);
		return;
	}

	pCelBuff = monster[m]._mAnimData;
	if(!pCelBuff) {
		// app_fatal("Draw Monster \"%s\": NULL Cel Buffer", monster[m].mName);
		return;
	}

	nCel = monster[m]._mAnimFrame;
	pFrameTable = (DWORD *)pCelBuff;
	if(nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
		/*
		const char *szMode = "unknown action";
		if(monster[m]._mmode <= 17)
			szMode = szMonModeAssert[monster[m]._mmode];
		app_fatal(
			"Draw Monster \"%s\" %s: facing %d, frame %d of %d",
			monster[m].mName,
			szMode,
			monster[m]._mdir,
			nCel,
			pFrameTable[0]);
		*/
		return;
	}

	if(!(dFlags[x][y] & 0x40)) {
		Cl2DecodeFrm3(mx, my, monster[m]._mAnimData, monster[m]._mAnimFrame, monster[m].MType->flags_1, a6, a7, 1);
	} else {
		trans = 0;
		if(monster[m]._uniqtype)
			trans = monster[m]._uniqtrans + 4;
		if(monster[m]._mmode == MM_STONE)
			trans = 2;
		if(plr[myplr]._pInfraFlag && light_table_index > 8)
			trans = 1;
		if(trans)
			Cl2DecodeFrm3(mx, my, monster[m]._mAnimData, monster[m]._mAnimFrame, monster[m].MType->flags_1, a6, a7, trans);
		else
			Cl2DecodeLightTbl(mx, my, monster[m]._mAnimData, monster[m]._mAnimFrame, monster[m].MType->flags_1, a6, a7);
	}
}

static void DrawClippedMonster(int x, int y, int mx, int my, int m, int a6, int a7)
{
	int nCel;
	char trans;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	if((DWORD)m >= MAXMONSTERS) {
		// app_fatal("Draw Monster Clipped: tried to draw illegal monster %d", m);
		return;
	}

	pCelBuff = monster[m]._mAnimData;
	if(!pCelBuff) {
		// app_fatal("Draw Monster \"%s\" Clipped: NULL Cel Buffer", monster[m].mName);
		return;
	}

	nCel = monster[m]._mAnimFrame;
	pFrameTable = (DWORD *)pCelBuff;
	if(nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
		/*
		const char *szMode = "unknown action";
		if(monster[m]._mmode <= 17)
			szMode = szMonModeAssert[monster[m]._mmode];
		app_fatal(
			"Draw Monster \"%s\" %s Clipped: facing %d, frame %d of %d",
			monster[m].mName,
			szMode,
			monster[m]._mdir,
			nCel,
			pFrameTable[0]);
		*/
		return;
	}

	if(!(dFlags[x][y] & 0x40)) {
		Cl2DecodeFrm5(mx, my, monster[m]._mAnimData, monster[m]._mAnimFrame, monster[m].MType->flags_1, a6, a7, 1);
	} else {
		trans = 0;
		if(monster[m]._uniqtype)
			trans = monster[m]._uniqtrans + 4;
		if(monster[m]._mmode == MM_STONE)
			trans = 2;
		if(plr[myplr]._pInfraFlag && light_table_index > 8)
			trans = 1;
		if(trans)
			Cl2DecodeFrm5(mx, my, monster[m]._mAnimData, monster[m]._mAnimFrame, monster[m].MType->flags_1, a6, a7, trans);
		else
			Cl2DecodeFrm6(mx, my, monster[m]._mAnimData, monster[m]._mAnimFrame, monster[m].MType->flags_1, a6, a7);
	}
}

static void DrawPlayer(int pnum, int x, int y, int px, int py, BYTE *pCelBuff, int nCel, int nWidth, int a9, int a10)
{
	int l;
	DWORD *pFrameTable;

	if(dFlags[x][y] & 0x40 || plr[myplr]._pInfraFlag || !setlevel && !currlevel) {
		if(!pCelBuff) {
			// app_fatal("Drawing player %d \"%s\": NULL Cel Buffer", pnum, plr[pnum]._pName);
			return;
		}
		pFrameTable = (DWORD *)pCelBuff;
		if(nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
			/*
			const char *szMode = "unknown action";
			if(plr[pnum]._pmode <= 11)
				szMode = szPlrModeAssert[plr[pnum]._pmode];
			app_fatal(
				"Drawing player %d \"%s\" %s: facing %d, frame %d of %d",
				pnum,
				plr[pnum]._pName,
				szMode,
				plr[pnum]._pdir,
				nCel,
				pFrameTable[0]);
			*/
			return;
		}
		if(pnum == pcursplr)
			Cl2DecodeFrm2(165, px, py, pCelBuff, nCel, nWidth, a9, a10);
		if(pnum == myplr) {
			Cl2DecodeFrm1(px, py, pCelBuff, nCel, nWidth, a9, a10);
			if(plr[pnum].pManaShield)
				Cl2DecodeFrm1(
					px + plr[pnum]._pAnimWidth2 - misfiledata[MFILE_MANASHLD].mAnimWidth2[0],
					py,
					misfiledata[MFILE_MANASHLD].mAnimData[0],
					1,
					misfiledata[MFILE_MANASHLD].mAnimWidth[0],
					a9,
					a10);
		} else if(!(dFlags[x][y] & 0x40) || plr[myplr]._pInfraFlag && light_table_index > 8) {
			Cl2DecodeFrm3(px, py, pCelBuff, nCel, nWidth, a9, a10, 1);
			if(plr[pnum].pManaShield)
				Cl2DecodeFrm3(
					px + plr[pnum]._pAnimWidth2 - misfiledata[MFILE_MANASHLD].mAnimWidth2[0],
					py,
					misfiledata[MFILE_MANASHLD].mAnimData[0],
					1,
					misfiledata[MFILE_MANASHLD].mAnimWidth[0],
					a9,
					a10,
					1);
		} else {
			l = light_table_index;
			if(light_table_index < 5)
				light_table_index = 0;
			else
				light_table_index -= 5;
			Cl2DecodeLightTbl(px, py, pCelBuff, nCel, nWidth, a9, a10);
			if(plr[pnum].pManaShield)
				Cl2DecodeLightTbl(
					px + plr[pnum]._pAnimWidth2 - misfiledata[MFILE_MANASHLD].mAnimWidth2[0],
					py,
					misfiledata[MFILE_MANASHLD].mAnimData[0],
					1,
					misfiledata[MFILE_MANASHLD].mAnimWidth[0],
					a9,
					a10);
			light_table_index = l;
		}
	}
}

static void DrawClippedPlayer(int pnum, int x, int y, int px, int py, BYTE *pCelBuff, int nCel, int nWidth, int a9, int a10)
{
	int l;
	DWORD *pFrameTable;

	if(dFlags[x][y] & 0x40 || plr[myplr]._pInfraFlag) {
		if(!pCelBuff) {
			// app_fatal("Drawing player %d \"%s\" clipped: NULL Cel Buffer", pnum, plr[pnum]._pName);
			return;
		}
		pFrameTable = (DWORD *)pCelBuff;
		if(nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
			/*
			const char *szMode = "unknown action";
			if(plr[pnum]._pmode <= 11)
				szMode = szPlrModeAssert[plr[pnum]._pmode];
			app_fatal(
				"Drawing player %d \"%s\" %s clipped: facing %d, frame %d of %d",
				pnum,
				plr[pnum]._pName,
				szMode,
				plr[pnum]._pdir,
				nCel,
				pFrameTable[0]);
			*/
			return;
		}
		if(pnum == pcursplr)
			Cl2DecodeClrHL(165, px, py, pCelBuff, nCel, nWidth, a9, a10);
		if(pnum == myplr) {
			Cl2DecodeFrm4(px, py, pCelBuff, nCel, nWidth, a9, a10);
			if(plr[pnum].pManaShield)
				Cl2DecodeFrm4(
					px + plr[pnum]._pAnimWidth2 - misfiledata[MFILE_MANASHLD].mAnimWidth2[0],
					py,
					misfiledata[MFILE_MANASHLD].mAnimData[0],
					1,
					misfiledata[MFILE_MANASHLD].mAnimWidth[0],
					a9,
					a10);
		} else if(!(dFlags[x][y] & 0x40) || plr[myplr]._pInfraFlag && light_table_index > 8) {
			Cl2DecodeFrm5(px, py, pCelBuff, nCel, nWidth, a9, a10, 1);
			if(plr[pnum].pManaShield)
				Cl2DecodeFrm5(
					px + plr[pnum]._pAnimWidth2 - misfiledata[MFILE_MANASHLD].mAnimWidth2[0],
					py,
					misfiledata[MFILE_MANASHLD].mAnimData[0],
					1,
					misfiledata[MFILE_MANASHLD].mAnimWidth[0],
					a9,
					a10,
					1);
		} else {
			l = light_table_index;
			if(light_table_index < 5)
				light_table_index = 0;
			else
				light_table_index -= 5;
			Cl2DecodeFrm6(px, py, pCelBuff, nCel, nWidth, a9, a10);
			if(plr[pnum].pManaShield)
				Cl2DecodeFrm6(
					px + plr[pnum]._pAnimWidth2 - misfiledata[MFILE_MANASHLD].mAnimWidth2[0],
					py,
					misfiledata[MFILE_MANASHLD].mAnimData[0],
					1,
					misfiledata[MFILE_MANASHLD].mAnimWidth[0],
					a9,
					a10);
			light_table_index = l;
		}
	}
}

void DrawDeadPlayer(int x, int y, int sx, int sy, int a5, int a6, BOOL clipped)
{
	int i, px, py, nCel;
	PlayerStruct *p;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	if(clipped)
		DrawPlrProc = DrawClippedPlayer;
	else
		DrawPlrProc = DrawPlayer;

	dFlags[x][y] &= ~4;

	for(i = 0; i < MAX_PLRS; i++) {
		p = &plr[i];
		if(p->plractive && !p->_pHitPoints && p->plrlevel == (unsigned char)currlevel && p->WorldX == x && p->WorldY == y) {
			pCelBuff = p->_pAnimData;
			if(!pCelBuff) {
				// app_fatal("Drawing dead player %d \"%s\": NULL Cel Buffer", i, p->_pName);
				break;
			}
			nCel = p->_pAnimFrame;
			pFrameTable = (DWORD *)pCelBuff;
			if(nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
				// app_fatal("Drawing dead player %d \"%s\": facing %d, frame %d of %d", i, p->_pName, p->_pdir, nCel, pFrameTable[0]);
				break;
			}
			dFlags[x][y] |= 4;
			px = sx + p->_pxoff - p->_pAnimWidth2;
			py = sy + p->_pyoff;
			DrawPlrProc(i, x, y, px, py, p->_pAnimData, p->_pAnimFrame, p->_pAnimWidth, a5, a6);
		}
	}
}

static void DrawObject(int x, int y, int ox, int oy, BOOL pre, int a6, int dir)
{
	int sx, sy, xx, yy, nCel;
	char bv;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	if(dObject[x][y] > 0) {
		bv = dObject[x][y] - 1;
		if(object[bv]._oPreFlag != pre)
			return;
		sx = ox - object[bv]._oAnimWidth2;
		sy = oy;
	} else {
		bv = -(dObject[x][y] + 1);
		if(object[bv]._oPreFlag != pre)
			return;
		xx = object[bv]._ox - x;
		yy = object[bv]._oy - y;
		sx = (xx << 5) + ox - object[bv]._oAnimWidth2 - (yy << 5);
		sy = oy + (yy << 4) + (xx << 4);
		a6 = 0;
		dir = 8;
	}

	/// ASSERT: assert((unsigned char)bv < MAXOBJECTS);
	if((unsigned char)bv >= MAXOBJECTS)
		return;

	pCelBuff = object[bv]._oAnimData;
	if(!pCelBuff) {
		// app_fatal("Draw Object type %d: NULL Cel Buffer", object[bv]._otype);
		return;
	}

	nCel = object[bv]._oAnimFrame;
	pFrameTable = (DWORD *)pCelBuff;
	if(nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
		// app_fatal("Draw Object: frame %d of %d, object type==%d", nCel, pFrameTable[0], object[bv]._otype);
		return;
	}

	if(bv == pcursobj)
		CelDecodeClr(194, sx, sy, object[bv]._oAnimData, object[bv]._oAnimFrame, object[bv]._oAnimWidth, a6, dir);
	if(object[bv]._oLight) {
		CelDecodeHdrLightOnly(sx, sy, object[bv]._oAnimData, object[bv]._oAnimFrame, object[bv]._oAnimWidth, a6, dir);
	} else {
		/// ASSERT: assert(object[bv]._oAnimData);
		if(object[bv]._oAnimData) /// BUGFIX: _oAnimData was already checked, this is redundant
			CelDrawHdrOnly(sx, sy, object[bv]._oAnimData, object[bv]._oAnimFrame, object[bv]._oAnimWidth, a6, dir);
	}
}

static void DrawClippedObject(int x, int y, int ox, int oy, BOOL pre, int a6, int dir)
{
	int sx, sy, xx, yy, nCel;
	char bv;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	if(dObject[x][y] > 0) {
		bv = dObject[x][y] - 1;
		if(object[bv]._oPreFlag != pre)
			return;
		sx = ox - object[bv]._oAnimWidth2;
		sy = oy;
	} else {
		bv = -(dObject[x][y] + 1);
		if(object[bv]._oPreFlag != pre)
			return;
		xx = object[bv]._ox - x;
		yy = object[bv]._oy - y;
		sx = (xx << 5) + ox - object[bv]._oAnimWidth2 - (yy << 5);
		sy = oy + (yy << 4) + (xx << 4);
		a6 = 0;
		dir = 8;
	}

	/// ASSERT: assert((unsigned char)bv < MAXOBJECTS);
	if((unsigned char)bv >= MAXOBJECTS)
		return;

	pCelBuff = object[bv]._oAnimData;
	if(!pCelBuff) {
		// app_fatal("Draw Object type %d Clipped: NULL Cel Buffer", object[bv]._otype);
		return;
	}

	nCel = object[bv]._oAnimFrame;
	pFrameTable = (DWORD *)pCelBuff;
	if(nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
		// app_fatal("Draw Clipped Object: frame %d of %d, object type==%d", nCel, pFrameTable[0], object[bv]._otype);
		return;
	}

	if(bv == pcursobj)
		CelDrawHdrClrHL(194, sx, sy, object[bv]._oAnimData, object[bv]._oAnimFrame, object[bv]._oAnimWidth, a6, dir);
	if(object[bv]._oLight)
		Cel2DecodeHdrLight(sx, sy, object[bv]._oAnimData, object[bv]._oAnimFrame, object[bv]._oAnimWidth, a6, dir);
	else
		Cel2DrawHdrOnly(sx, sy, object[bv]._oAnimData, object[bv]._oAnimFrame, object[bv]._oAnimWidth, a6, dir);
}

static void scrollrt_draw_clipped_dungeon(BYTE *pBuff, int sx, int sy, int dx, int dy, int me_flag);

static void scrollrt_draw_clipped_e_flag(BYTE *pBuff, int x, int y, int a4, int a5)
{
	int i, lti_old, cta_old, lpi_old;
	BYTE *dst;
	MICROS *pMap;

	lti_old = light_table_index;
	cta_old = cel_transparency_active;
	lpi_old = level_piece_id;

	level_piece_id = dPiece[x][y];
	light_table_index = dLight[x][y];
	cel_transparency_active = (unsigned char)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
	pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];

	dst = pBuff;
	arch_draw_type = 1;
	level_cel_block = pMap->mt[0];
	if(level_cel_block != 0) {
		drawLowerScreen(dst);
	}
	arch_draw_type = 2;
	level_cel_block = pMap->mt[1];
	if(level_cel_block != 0) {
		drawLowerScreen(dst + 32);
	}

	dst = pBuff;
	arch_draw_type = 0;
	for(i = 2; i < MicroTileLen; i += 2) {
		dst -= 768 * 32;
		level_cel_block = pMap->mt[i];
		if(level_cel_block != 0) {
			drawLowerScreen(dst);
		}
		level_cel_block = pMap->mt[i + 1];
		if(level_cel_block != 0) {
			drawLowerScreen(dst + 32);
		}
	}

	scrollrt_draw_clipped_dungeon(pBuff, x, y, a4, a5, 0);

	light_table_index = lti_old;
	cel_transparency_active = cta_old;
	level_piece_id = lpi_old;
}

static void scrollrt_draw_clipped_dungeon(BYTE *pBuff, int sx, int sy, int dx, int dy, int me_flag)
{
	int px, py, nCel, nMon, negMon, p;
	char bFlag, bDead, bObj, bItem, bPlr, bArch, bMap, negPlr, dd;
	DeadStruct *pDeadGuy;
	ItemStruct *pItem;
	PlayerStruct *pPlayer;
	MonsterStruct *pMonster;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	/// ASSERT: assert((DWORD)sx < MAXDUNX);
	/// ASSERT: assert((DWORD)sy < MAXDUNY);
	bFlag = dFlags[sx][sy];
	bDead = dDead[sx][sy];
	bObj = dObject[sx][sy];
	bItem = dItem[sx][sy];
	bPlr = dPlayer[sx][sy];
	bArch = dSpecial[sx][sy];
	bMap = dTransVal[sx][sy];
	nMon = dMonster[sx][sy];

	/// ASSERT: assert((DWORD)(sy-1) < MAXDUNY);
	negPlr = dPlayer[sx][sy - 1];
	negMon = dMonster[sx][sy - 1];

	if(visiondebug && bFlag & 0x40) {
		Cel2DecodeHdrOnly(pBuff, (BYTE *)pSquareCel, 1, 64, 0, 8);
	}
	if(MissilePreFlag && bFlag & 1) {
		DrawClippedMissile(sx, sy, dx, dy, 0, 8, 1);
	}
	if(light_table_index < lightmax) {
		if(bDead != 0) {
			pDeadGuy = &dead[(bDead & 0x1F) - 1];
			dd = (bDead >> 5) & 7;
			px = dx - pDeadGuy->_deadWidth2;
			pCelBuff = pDeadGuy->_deadData[dd];
			/// ASSERT: assert(pDeadGuy->_deadData[dd] != NULL);
			if(pCelBuff != NULL) {
				pFrameTable = (DWORD *)pDeadGuy->_deadData[dd];
				nCel = pDeadGuy->_deadFrame;
				if(nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
					if(pDeadGuy->_deadtrans != 0) {
						Cl2DecodeFrm5(px, dy, pCelBuff, nCel, pDeadGuy->_deadWidth, 0, 8, pDeadGuy->_deadtrans);
					} else {
						Cl2DecodeFrm6(px, dy, pCelBuff, nCel, pDeadGuy->_deadWidth, 0, 8);
					}
				} else {
					// app_fatal("Clipped dead sub: frame %d of %d, deadnum==%d", nCel, pFrameTable[0], (bDead & 0x1F) - 1);
				}
			}
		}
		if(bObj != 0) {
			DrawClippedObject(sx, sy, dx, dy, 1, 0, 8);
		}
	}
	if(bItem != 0) {
		pItem = &item[bItem - 1];
		if(!pItem->_iPostDraw) {
			/// ASSERT: assert((unsigned char)bItem <= MAXITEMS);
			if((unsigned char)bItem <= MAXITEMS) {
				pCelBuff = pItem->_iAnimData;
				if(pCelBuff != NULL) {
					pFrameTable = (DWORD *)pCelBuff;
					nCel = pItem->_iAnimFrame;
					if(nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
						px = dx - pItem->_iAnimWidth2;
						if(bItem - 1 == pcursitem) {
							CelDrawHdrClrHL(181, px, dy, pCelBuff, pItem->_iAnimFrame, pItem->_iAnimWidth, 0, 8);
						}
						Cel2DecodeHdrLight(px, dy, pItem->_iAnimData, pItem->_iAnimFrame, pItem->_iAnimWidth, 0, 8);
					} else {
						/*
						app_fatal(
							"Draw Clipped \"%s\" Item: frame %d of %d, item type==%d",
							pItem->_iIName,
							nCel,
							pFrameTable[0],
							pItem->_itype);
						*/
					}
				} else {
					// app_fatal("Draw Item \"%s\" Clipped 1: NULL Cel Buffer", pItem->_iIName);
				}
			}
		}
	}
	if(bFlag & 0x20) {
		p = -(negPlr + 1);
		if((DWORD)p < MAX_PLRS) {
			pPlayer = &plr[p];
			px = dx + pPlayer->_pxoff - pPlayer->_pAnimWidth2;
			py = dy + pPlayer->_pyoff;
			DrawClippedPlayer(p, sx, sy - 1, px, py, pPlayer->_pAnimData, pPlayer->_pAnimFrame, pPlayer->_pAnimWidth, 0, 8);
			if(me_flag && pPlayer->_peflag != 0) {
				if(pPlayer->_peflag == 2) {
					scrollrt_draw_clipped_e_flag(pBuff - (768 * 16 + 96), sx - 2, sy + 1, dx - 96, dy - 16);
				}
				scrollrt_draw_clipped_e_flag(pBuff - 64, sx - 1, sy + 1, dx - 64, dy);
			}
		} else {
			// app_fatal("draw player clipped: tried to draw illegal player %d", p);
		}
	}
	if(bFlag & 0x10 && (bFlag & 0x40 || plr[myplr]._pInfraFlag) && negMon < 0) {
		draw_monster_num = -(negMon + 1);
		if((DWORD)draw_monster_num < MAXMONSTERS) {
			pMonster = &monster[draw_monster_num];
			if(!(pMonster->_mFlags & 1)) {
				if(pMonster->MType != NULL) {
					px = dx + pMonster->_mxoff - pMonster->MType->flags_2;
					py = dy + pMonster->_myoff;
					if(draw_monster_num == pcursmonst) {
						Cl2DecodeClrHL(233, px, py, pMonster->_mAnimData, pMonster->_mAnimFrame, pMonster->MType->flags_1, 0, 8);
					}
					DrawClippedMonster(sx, sy, px, py, draw_monster_num, 0, 8);
					if(me_flag && pMonster->_meflag) {
						scrollrt_draw_clipped_e_flag(pBuff - 64, sx - 1, sy + 1, dx - 64, dy);
					}
				} else {
					// app_fatal("Draw Monster \"%s\" Clipped: uninitialized monster", pMonster->mName);
				}
			}
		} else {
			// app_fatal("Draw Monster Clipped: tried to draw illegal monster %d", draw_monster_num);
		}
	}
	if(bFlag & 4) {
		DrawDeadPlayer(sx, sy, dx, dy, 0, 8, 1);
	}
	if(bPlr > 0) {
		p = bPlr - 1;
		if((DWORD)p < MAX_PLRS) {
			pPlayer = &plr[p];
			px = dx + pPlayer->_pxoff - pPlayer->_pAnimWidth2;
			py = dy + pPlayer->_pyoff;
			DrawClippedPlayer(p, sx, sy, px, py, pPlayer->_pAnimData, pPlayer->_pAnimFrame, pPlayer->_pAnimWidth, 0, 8);
			if(me_flag && pPlayer->_peflag != 0) {
				if(pPlayer->_peflag == 2) {
					scrollrt_draw_clipped_e_flag(pBuff - (768 * 16 + 96), sx - 2, sy + 1, dx - 96, dy - 16);
				}
				scrollrt_draw_clipped_e_flag(pBuff - 64, sx - 1, sy + 1, dx - 64, dy);
			}
		} else {
			// app_fatal("draw player clipped: tried to draw illegal player %d", p);
		}
	}
	if(nMon > 0 && (bFlag & 0x40 || plr[myplr]._pInfraFlag)) {
		draw_monster_num = nMon - 1;
		if((DWORD)draw_monster_num < MAXMONSTERS) {
			pMonster = &monster[draw_monster_num];
			if(!(pMonster->_mFlags & 1)) {
				if(pMonster->MType != NULL) {
					px = dx + pMonster->_mxoff - pMonster->MType->flags_2;
					py = dy + pMonster->_myoff;
					if(draw_monster_num == pcursmonst) {
						Cl2DecodeClrHL(233, px, py, pMonster->_mAnimData, pMonster->_mAnimFrame, pMonster->MType->flags_1, 0, 8);
					}
					DrawClippedMonster(sx, sy, px, py, draw_monster_num, 0, 8);
					if(me_flag && pMonster->_meflag) {
						scrollrt_draw_clipped_e_flag(pBuff - 64, sx - 1, sy + 1, dx - 64, dy);
					}
				} else {
					// app_fatal("Draw Monster \"%s\" Clipped: uninitialized monster", pMonster->mName);
				}
			}
		} else {
			// app_fatal("Draw Monster Clipped: tried to draw illegal monster %d", draw_monster_num);
		}
	}
	if(bFlag & 1) {
		DrawClippedMissile(sx, sy, dx, dy, 0, 8, 0);
	}
	if(bObj != 0 && light_table_index < lightmax) {
		DrawClippedObject(sx, sy, dx, dy, 0, 0, 8);
	}
	if(bItem != 0) {
		pItem = &item[bItem - 1];
		if(pItem->_iPostDraw) {
			/// ASSERT: assert((unsigned char)bItem <= MAXITEMS);
			if((unsigned char)bItem <= MAXITEMS) {
				pCelBuff = pItem->_iAnimData;
				if(pCelBuff != NULL) {
					pFrameTable = (DWORD *)pCelBuff;
					nCel = pItem->_iAnimFrame;
					if(nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
						px = dx - pItem->_iAnimWidth2;
						if(bItem - 1 == pcursitem) {
							CelDrawHdrClrHL(181, px, dy, pCelBuff, pItem->_iAnimFrame, pItem->_iAnimWidth, 0, 8);
						}
						Cel2DecodeHdrLight(px, dy, pItem->_iAnimData, pItem->_iAnimFrame, pItem->_iAnimWidth, 0, 8);
					} else {
						/*
						app_fatal(
							"Draw Clipped \"%s\" Item 2: frame %d of %d, item type==%d",
							pItem->_iIName,
							nCel,
							pFrameTable[0],
							pItem->_itype);
						*/
					}
				} else {
					// app_fatal("Draw Item \"%s\" Clipped 2: NULL Cel Buffer", pItem->_iIName);
				}
			}
		}
	}
	if(bArch != 0) {
		cel_transparency_active = (unsigned char)TransList[bMap];
		Cel2DecodeLightTrans(pBuff, pSpecialCels, bArch, 64, 0, 8);
	}
}

static void scrollrt_draw_lower(int x, int y, int sx, int sy, int a5, int some_flag)
{
	int i, j;
	BYTE *dst;
	MICROS *pMap;

	/// ASSERT: assert(gpBuffer);

	pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];

	if(some_flag) {
		if((DWORD)y < MAXDUNY && (DWORD)x < MAXDUNX) {
			level_piece_id = dPiece[x][y];
			light_table_index = dLight[x][y];
			if(level_piece_id != 0) {
				dst = &gpBuffer[sx + 32 + PitchTbl[sy]];
				cel_transparency_active = (unsigned char)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
				arch_draw_type = 2;
				level_cel_block = pMap->mt[1];
				if(level_cel_block != 0) {
					drawLowerScreen(dst);
				}
				arch_draw_type = 0;
				dst -= 768 * 32;
				level_cel_block = pMap->mt[3];
				if(level_cel_block != 0) {
					drawLowerScreen(dst);
				}
				dst -= 768 * 32;
				level_cel_block = pMap->mt[5];
				if(level_cel_block != 0) {
					drawLowerScreen(dst);
				}
				dst -= 768 * 32;
				level_cel_block = pMap->mt[7];
				if(level_cel_block != 0) {
					drawLowerScreen(dst);
				}
				dst -= 768 * 32;
				level_cel_block = pMap->mt[9];
				if(level_cel_block != 0) {
					drawLowerScreen(dst);
				}
				dst -= 768 * 32;
				level_cel_block = pMap->mt[11];
				if(level_cel_block != 0 && leveltype == DTYPE_HELL) {
					drawLowerScreen(dst);
				}
				scrollrt_draw_clipped_dungeon(&gpBuffer[sx + PitchTbl[sy]], x, y, sx, sy, 0);
			} else {
				world_draw_black_tile(&gpBuffer[sx + PitchTbl[sy]]);
			}
		}
		x++;
		y--;
		sx += 64;
		pMap++;
		a5--;
	}

	j = a5;
	while(j != 0) {
		j--;
		if(y < 0 || x >= MAXDUNX) {
			break;
		}
		if(y < MAXDUNY && x >= 0) {
			level_piece_id = dPiece[x][y];
			light_table_index = dLight[x][y];
			if(level_piece_id == 0) {
				world_draw_black_tile(&gpBuffer[sx + PitchTbl[sy]]);
			} else {
				dst = &gpBuffer[sx + PitchTbl[sy]];
				cel_transparency_active = (unsigned char)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
				arch_draw_type = 1;
				level_cel_block = pMap->mt[0];
				if(level_cel_block != 0) {
					drawLowerScreen(dst);
				}
				arch_draw_type = 2;
				level_cel_block = pMap->mt[1];
				if(level_cel_block != 0) {
					drawLowerScreen(dst + 32);
				}
				arch_draw_type = 0;
				for(i = 2; i < MicroTileLen; i += 2) {
					dst -= 768 * 32;
					level_cel_block = pMap->mt[i];
					if(level_cel_block != 0) {
						drawLowerScreen(dst);
					}
					level_cel_block = pMap->mt[i + 1];
					if(level_cel_block != 0) {
						drawLowerScreen(dst + 32);
					}
				}
				scrollrt_draw_clipped_dungeon(&gpBuffer[sx + PitchTbl[sy]], x, y, sx, sy, 1);
			}
		}
		x++;
		y--;
		sx += 64;
		pMap++;
	}

	if(some_flag && (DWORD)y < MAXDUNY && (DWORD)x < MAXDUNX) {
		level_piece_id = dPiece[x][y];
		light_table_index = dLight[x][y];
		if(level_piece_id == 0) {
			world_draw_black_tile(&gpBuffer[sx + PitchTbl[sy]]);
		} else {
			dst = &gpBuffer[sx + PitchTbl[sy]];
			cel_transparency_active = (unsigned char)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
			arch_draw_type = 1;
			level_cel_block = pMap->mt[0];
			if(level_cel_block != 0) {
				drawLowerScreen(dst);
			}
			arch_draw_type = 0;
			dst -= 768 * 32;
			level_cel_block = pMap->mt[2];
			if(level_cel_block != 0) {
				drawLowerScreen(dst);
			}
			dst -= 768 * 32;
			level_cel_block = pMap->mt[4];
			if(level_cel_block != 0) {
				drawLowerScreen(dst);
			}
			dst -= 768 * 32;
			level_cel_block = pMap->mt[6];
			if(level_cel_block != 0) {
				drawLowerScreen(dst);
			}
			dst -= 768 * 32;
			level_cel_block = pMap->mt[8];
			if(level_cel_block != 0) {
				drawLowerScreen(dst);
			}
			dst -= 768 * 32;
			level_cel_block = pMap->mt[10];
			if(level_cel_block != 0 && leveltype == DTYPE_HELL) {
				drawLowerScreen(dst);
			}
			scrollrt_draw_clipped_dungeon(&gpBuffer[sx + PitchTbl[sy]], x, y, sx, sy, 0);
		}
	}
}

static void scrollrt_draw_clipped_dungeon_2(BYTE *pBuff, int sx, int sy, int a4, int a5, int dx, int dy, int me_flag);

static void scrollrt_draw_clipped_e_flag_2(BYTE *pBuff, int x, int y, int a4, signed int a5, int sx, int sy)
{
	int lti_old, cta_old, lpi_old;
	BYTE *dst;
	MICROS *pMap;

	lti_old = light_table_index;
	cta_old = cel_transparency_active;
	lpi_old = level_piece_id;

	level_piece_id = dPiece[x][y];
	light_table_index = dLight[x][y];
	dst = &pBuff[768 * 32 * a4];
	cel_transparency_active = (unsigned char)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
	pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];

	switch(a4) {
	case 0:
		level_cel_block = pMap->mt[2];
		if(level_cel_block != 0) {
			drawLowerScreen(dst);
		}
		level_cel_block = pMap->mt[3];
		if(level_cel_block != 0) {
			drawLowerScreen(dst + 32);
		}
	case 1:
		dst -= 768 * 32;
		level_cel_block = pMap->mt[4];
		if(level_cel_block != 0) {
			drawLowerScreen(dst);
		}
		level_cel_block = pMap->mt[5];
		if(level_cel_block != 0) {
			drawLowerScreen(dst + 32);
		}
	case 2:
		dst -= 768 * 32;
		level_cel_block = pMap->mt[6];
		if(level_cel_block != 0) {
			drawLowerScreen(dst);
		}
		level_cel_block = pMap->mt[7];
		if(level_cel_block != 0) {
			drawLowerScreen(dst + 32);
		}
	case 3:
		dst -= 768 * 32;
		level_cel_block = pMap->mt[8];
		if(level_cel_block != 0) {
			drawLowerScreen(dst);
		}
		level_cel_block = pMap->mt[9];
		if(level_cel_block != 0) {
			drawLowerScreen(dst + 32);
		}
		break;
	}

	if(a5 < 8) {
		scrollrt_draw_clipped_dungeon_2(pBuff, x, y, a4, a5, sx, sy, 0);
	}

	light_table_index = lti_old;
	cel_transparency_active = cta_old;
	level_piece_id = lpi_old;
}

static void scrollrt_draw_clipped_dungeon_2(BYTE *pBuff, int sx, int sy, int a4, int a5, int dx, int dy, int me_flag)
{
	int px, py, nCel, nMon, negMon, p;
	char bFlag, bDead, bObj, bItem, bPlr, bArch, bMap, negPlr, dd;
	DeadStruct *pDeadGuy;
	ItemStruct *pItem;
	PlayerStruct *pPlayer;
	MonsterStruct *pMonster;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	/// ASSERT: assert((DWORD)sx < MAXDUNX);
	/// ASSERT: assert((DWORD)sy < MAXDUNY);
	bFlag = dFlags[sx][sy];
	bDead = dDead[sx][sy];
	bObj = dObject[sx][sy];
	bItem = dItem[sx][sy];
	bPlr = dPlayer[sx][sy];
	bArch = dSpecial[sx][sy];
	bMap = dTransVal[sx][sy];
	nMon = dMonster[sx][sy];

	/// ASSERT: assert((DWORD)(sy-1) < MAXDUNY);
	negPlr = dPlayer[sx][sy - 1];
	negMon = dMonster[sx][sy - 1];

	if(visiondebug && bFlag & 0x40) {
		Cel2DecodeHdrOnly(pBuff, (BYTE *)pSquareCel, 1, 64, a5, 8);
	}
	if(MissilePreFlag && bFlag & 1) {
		DrawClippedMissile(sx, sy, dx, dy, a5, 8, 1);
	}
	if(light_table_index < lightmax) {
		if(bDead != 0) {
			pDeadGuy = &dead[(bDead & 0x1F) - 1];
			dd = (bDead >> 5) & 7;
			px = dx - pDeadGuy->_deadWidth2;
			pCelBuff = pDeadGuy->_deadData[dd];
			/// ASSERT: assert(pDeadGuy->_deadData[dd] != NULL);
			if(pCelBuff != NULL) {
				pFrameTable = (DWORD *)pDeadGuy->_deadData[dd];
				nCel = pDeadGuy->_deadFrame;
				if(nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
					if(pDeadGuy->_deadtrans != 0) {
						Cl2DecodeFrm5(px, dy, pCelBuff, pDeadGuy->_deadFrame, pDeadGuy->_deadWidth, a5, 8, pDeadGuy->_deadtrans);
					} else {
						Cl2DecodeFrm6(px, dy, pCelBuff, pDeadGuy->_deadFrame, pDeadGuy->_deadWidth, a5, 8);
					}
				} else {
					// app_fatal("Clipped dead sub2: frame %d of %d, deadnum==%d", nCel, pFrameTable[0], (bDead & 0x1F) - 1);
				}
			}
		}
		if(bObj != 0) {
			DrawClippedObject(sx, sy, dx, dy, 1, a5, 8);
		}
	}
	if(bItem != 0) {
		pItem = &item[bItem - 1];
		if(!pItem->_iPostDraw) {
			/// ASSERT: assert((unsigned char)bItem <= MAXITEMS);
			if((unsigned char)bItem <= MAXITEMS) {
				pCelBuff = pItem->_iAnimData;
				if(pCelBuff != NULL) {
					pFrameTable = (DWORD *)pCelBuff;
					nCel = pItem->_iAnimFrame;
					if(nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
						px = dx - pItem->_iAnimWidth2;
						if(bItem - 1 == pcursitem) {
							CelDrawHdrClrHL(181, px, dy, pCelBuff, pItem->_iAnimFrame, pItem->_iAnimWidth, a5, 8);
						}
						Cel2DecodeHdrLight(px, dy, pItem->_iAnimData, pItem->_iAnimFrame, pItem->_iAnimWidth, a5, 8);
					} else {
						/*
						app_fatal(
							"Draw Clipped \"%s\" Item 3: frame %d of %d, item type==%d",
							pItem->_iIName,
							nCel,
							pFrameTable[0],
							pItem->_itype);
						*/
					}
				} else {
					// app_fatal("Draw Item \"%s\" Clipped 3: NULL Cel Buffer", pItem->_iIName);
				}
			}
		}
	}
	if(bFlag & 0x20) {
		p = -(negPlr + 1);
		if((DWORD)p < MAX_PLRS) {
			pPlayer = &plr[p];
			px = dx + pPlayer->_pxoff - pPlayer->_pAnimWidth2;
			py = dy + pPlayer->_pyoff;
			DrawClippedPlayer(p, sx, sy - 1, px, py, pPlayer->_pAnimData, pPlayer->_pAnimFrame, pPlayer->_pAnimWidth, a5, 8);
			if(me_flag && pPlayer->_peflag != 0) {
				if(pPlayer->_peflag == 2) {
					scrollrt_draw_clipped_e_flag_2(pBuff - (768 * 16 + 96), sx - 2, sy + 1, a4, a5, dx - 96, dy - 16);
				}
				scrollrt_draw_clipped_e_flag_2(pBuff - 64, sx - 1, sy + 1, a4, a5, dx - 64, dy);
			}
		} else {
			// app_fatal("draw player clipped: tried to draw illegal player %d", p);
		}
	}
	if(bFlag & 0x10 && (bFlag & 0x40 || plr[myplr]._pInfraFlag) && negMon < 0) {
		draw_monster_num = -(negMon + 1);
		if((DWORD)draw_monster_num < MAXMONSTERS) {
			pMonster = &monster[draw_monster_num];
			if(!(pMonster->_mFlags & 1)) {
				if(pMonster->MType != NULL) {
					px = dx + pMonster->_mxoff - pMonster->MType->flags_2;
					py = dy + pMonster->_myoff;
					if(draw_monster_num == pcursmonst) {
						Cl2DecodeClrHL(233, px, py, pMonster->_mAnimData, pMonster->_mAnimFrame, pMonster->MType->flags_1, a5, 8);
					}
					DrawClippedMonster(sx, sy, px, py, draw_monster_num, a5, 8);
					if(me_flag && !pMonster->_meflag) {
						scrollrt_draw_clipped_e_flag_2(pBuff - 64, sx - 1, sy + 1, a4, a5, dx - 64, dy);
					}
				} else {
					// app_fatal("Draw Monster \"%s\" Clipped: uninitialized monster", pMonster->mName);
				}
			}
		} else {
			// app_fatal("Draw Monster Clipped: tried to draw illegal monster %d", draw_monster_num);
		}
	}
	if(bFlag & 4) {
		DrawDeadPlayer(sx, sy, dx, dy, a5, 8, 1);
	}
	if(bPlr > 0) {
		p = bPlr - 1;
		if((DWORD)p < MAX_PLRS) {
			pPlayer = &plr[p];
			px = dx + pPlayer->_pxoff - pPlayer->_pAnimWidth2;
			py = dy + pPlayer->_pyoff;
			DrawClippedPlayer(p, sx, sy, px, py, pPlayer->_pAnimData, pPlayer->_pAnimFrame, pPlayer->_pAnimWidth, a5, 8);
			if(me_flag && pPlayer->_peflag != 0) {
				if(pPlayer->_peflag == 2) {
					scrollrt_draw_clipped_e_flag_2(pBuff - (768 * 16 + 96), sx - 2, sy + 1, a4, a5, dx - 96, dy - 16);
				}
				scrollrt_draw_clipped_e_flag_2(pBuff - 64, sx - 1, sy + 1, a4, a5, dx - 64, dy);
			}
		} else {
			// app_fatal("draw player clipped: tried to draw illegal player %d", p);
		}
	}
	if(nMon > 0 && (bFlag & 0x40 || plr[myplr]._pInfraFlag)) {
		draw_monster_num = nMon - 1;
		if((DWORD)draw_monster_num < MAXMONSTERS) {
			pMonster = &monster[draw_monster_num];
			if(!(pMonster->_mFlags & 1)) {
				if(pMonster->MType != NULL) {
					px = dx + pMonster->_mxoff - pMonster->MType->flags_2;
					py = dy + pMonster->_myoff;
					if(draw_monster_num == pcursmonst) {
						Cl2DecodeClrHL(233, px, py, pMonster->_mAnimData, pMonster->_mAnimFrame, pMonster->MType->flags_1, a5, 8);
					}
					DrawClippedMonster(sx, sy, px, py, draw_monster_num, a5, 8);
					if(me_flag && !pMonster->_meflag) {
						scrollrt_draw_clipped_e_flag_2(pBuff - 64, sx - 1, sy + 1, a4, a5, dx - 64, dy);
					}
				} else {
					// app_fatal("Draw Monster \"%s\" Clipped: uninitialized monster", pMonster->mName);
				}
			}
		} else {
			// app_fatal("Draw Monster Clipped: tried to draw illegal monster %d", draw_monster_num);
		}
	}
	if(bFlag & 1) {
		DrawClippedMissile(sx, sy, dx, dy, a5, 8, 0);
	}
	if(bObj != 0 && light_table_index < lightmax) {
		DrawClippedObject(sx, sy, dx, dy, 0, a5, 8);
	}
	if(bItem != 0) {
		pItem = &item[bItem - 1];
		if(pItem->_iPostDraw) {
			/// ASSERT: assert((unsigned char)bItem <= MAXITEMS);
			if((unsigned char)bItem <= MAXITEMS) {
				pCelBuff = pItem->_iAnimData;
				if(pCelBuff != NULL) {
					pFrameTable = (DWORD *)pCelBuff;
					nCel = pItem->_iAnimFrame;
					if(nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
						px = dx - pItem->_iAnimWidth2;
						if(bItem - 1 == pcursitem) {
							CelDrawHdrClrHL(181, px, dy, pCelBuff, nCel, pItem->_iAnimWidth, a5, 8);
						}
						Cel2DecodeHdrLight(px, dy, pItem->_iAnimData, pItem->_iAnimFrame, pItem->_iAnimWidth, a5, 8);
					} else {
						/*
						app_fatal(
							"Draw Clipped \"%s\" Item 4: frame %d of %d, item type==%d",
							pItem->_iIName,
							nCel,
							pFrameTable[0],
							pItem->_itype);
						*/
					}
				} else {
					// app_fatal("Draw Item \"%s\" Clipped 4: NULL Cel Buffer", pItem->_iIName);
				}
			}
		}
	}
	if(bArch != 0) {
		cel_transparency_active = (unsigned char)TransList[bMap];
		Cel2DecodeLightTrans(pBuff, pSpecialCels, bArch, 64, a5, 8);
	}
}

static void scrollrt_draw_lower_2(int x, int y, int sx, int sy, int a5, int a6, int some_flag)
{
	int i, j, dir;
	BYTE *dst;
	MICROS *pMap;

	/// ASSERT: assert(gpBuffer);

	pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];
	dir = 2 * a6 + 2;

	if(some_flag) {
		if(y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_piece_id = dPiece[x][y];
			light_table_index = dLight[x][y];
			if(level_piece_id != 0) {
				dst = &gpBuffer[sx - (768 * 32 - 32) + PitchTbl[sy]];
				cel_transparency_active = (unsigned char)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
				for(i = 0; i < (MicroTileLen >> 1) - 1; i++) {
					if(a6 <= i) {
						level_cel_block = pMap->mt[2 * i + 3];
						if(level_cel_block != 0) {
							drawLowerScreen(dst);
						}
					}
					dst -= 768 * 32;
				}
				if(dir < 8) {
					scrollrt_draw_clipped_dungeon_2(&gpBuffer[sx + PitchTbl[sy] - 768 * 16 * dir], x, y, a6, dir, sx, sy, 0);
				}
			}
		}
		x++;
		y--;
		sx += 64;
		a5--;
		pMap++;
	}

	j = a5;
	while(j != 0) {
		j--;
		if(x >= MAXDUNX || y < 0) {
			break;
		}
		if(y < MAXDUNY && x >= 0) {
			level_piece_id = dPiece[x][y];
			light_table_index = dLight[x][y];
			if(level_piece_id != 0) {
				dst = &gpBuffer[sx - 768 * 32 + PitchTbl[sy]];
				cel_transparency_active = (unsigned char)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
				i = 0;
				while(i < (MicroTileLen >> 1) - 1) {
					if(a6 <= i) {
						level_cel_block = pMap->mt[2 * i + 2];
						if(level_cel_block != 0) {
							drawLowerScreen(dst);
						}
						level_cel_block = pMap->mt[2 * i + 3];
						if(level_cel_block != 0) {
							drawLowerScreen(dst + 32);
						}
					}
					i++;
					dst -= 768 * 32;
				}
				if(dir < 8) {
					scrollrt_draw_clipped_dungeon_2(&gpBuffer[sx + PitchTbl[sy] - 768 * 32 * (a6 + 1)], x, y, a6, dir, sx, sy, 1);
				}
			}
		}
		x++;
		y--;
		sx += 64;
		pMap++;
	}

	if(some_flag && (DWORD)y < MAXDUNY && (DWORD)x < MAXDUNX) {
		level_piece_id = dPiece[x][y];
		light_table_index = dLight[x][y];
		if(level_piece_id != 0) {
			dst = &gpBuffer[sx - 768 * 32 + PitchTbl[sy]];
			cel_transparency_active = (unsigned char)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
			for(i = 0; i < (MicroTileLen >> 1) - 1; i++) {
				if(a6 <= i) {
					level_cel_block = pMap->mt[2 * i + 2];
					if(level_cel_block != 0) {
						drawLowerScreen(dst);
					}
				}
				dst -= 768 * 32;
			}
			if(dir < 8) {
				scrollrt_draw_clipped_dungeon_2(&gpBuffer[sx + PitchTbl[sy] - 768 * 16 * dir], x, y, a6, dir, sx, sy, 0);
			}
		}
	}
}

static void scrollrt_draw_dungeon(BYTE *pBuff, int sx, int sy, int a4, int a5, int dx, int dy, int me_flag);

static void scrollrt_draw_e_flag(BYTE *pBuff, int x, int y, int a4, int a5, int sx, int sy)
{
	int i, lti_old, cta_old, lpi_old;
	BYTE *dst;
	MICROS *pMap;

	lti_old = light_table_index;
	cta_old = cel_transparency_active;
	lpi_old = level_piece_id;

	level_piece_id = dPiece[x][y];
	light_table_index = dLight[x][y];
	dst = pBuff;
	cel_transparency_active = (unsigned char)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
	pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];

	arch_draw_type = 1;
	level_cel_block = pMap->mt[0];
	if(level_cel_block != 0) {
		drawUpperScreen(dst);
	}
	arch_draw_type = 2;
	level_cel_block = pMap->mt[1];
	if(level_cel_block != 0) {
		drawUpperScreen(dst + 32);
	}

	arch_draw_type = 0;
	for(i = 1; i < (MicroTileLen >> 1) - 1; i++) {
		dst -= 768 * 32;
		if(a4 >= i) {
			level_cel_block = pMap->mt[2 * i];
			if(level_cel_block != 0) {
				drawUpperScreen(dst);
			}
			level_cel_block = pMap->mt[2 * i + 1];
			if(level_cel_block != 0) {
				drawUpperScreen(dst + 32);
			}
		}
	}

	scrollrt_draw_dungeon(pBuff, x, y, a4, a5, sx, sy, 0);

	light_table_index = lti_old;
	cel_transparency_active = cta_old;
	level_piece_id = lpi_old;
}

static void scrollrt_draw_dungeon(BYTE *pBuff, int sx, int sy, int a4, int a5, int dx, int dy, int me_flag)
{
	int px, py, nCel, nMon, negMon, p;
	char bFlag, bDead, bObj, bItem, bPlr, bArch, bMap, negPlr, dd;
	DeadStruct *pDeadGuy;
	ItemStruct *pItem;
	PlayerStruct *pPlayer;
	MonsterStruct *pMonster;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	/// ASSERT: assert((DWORD)sx < MAXDUNX);
	/// ASSERT: assert((DWORD)sy < MAXDUNY);
	bFlag = dFlags[sx][sy];
	bDead = dDead[sx][sy];
	bObj = dObject[sx][sy];
	bItem = dItem[sx][sy];
	bPlr = dPlayer[sx][sy];
	bArch = dSpecial[sx][sy];
	bMap = dTransVal[sx][sy];
	nMon = dMonster[sx][sy];

	/// ASSERT: assert((DWORD)(sy-1) < MAXDUNY);
	negPlr = dPlayer[sx][sy - 1];
	negMon = dMonster[sx][sy - 1];

	if(visiondebug && (bFlag & 0x40)) {
		CelDecodeHdrOnly(pBuff, (BYTE *)pSquareCel, 1, 64, 0, a5);
	}
	if(MissilePreFlag && (bFlag & 1)) {
		DrawMissile(sx, sy, dx, dy, 0, a5, 1);
	}
	if(light_table_index < lightmax) {
		if(bDead != 0) {
			pDeadGuy = &dead[(bDead & 0x1F) - 1];
			dd = (unsigned char)(bDead >> 5) & 7;
			px = dx - pDeadGuy->_deadWidth2;
			pCelBuff = pDeadGuy->_deadData[dd];
			/// ASSERT: assert(pDeadGuy->_deadData[dd] != NULL);
			if(pCelBuff != NULL) {
				nCel = pDeadGuy->_deadFrame;
				pFrameTable = (DWORD *)pCelBuff;
				if(nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
					if(pDeadGuy->_deadtrans != 0) {
						Cl2DecodeFrm3(px, dy, pDeadGuy->_deadData[dd], pDeadGuy->_deadFrame, pDeadGuy->_deadWidth, 0, a5, pDeadGuy->_deadtrans);
					} else {
						Cl2DecodeLightTbl(px, dy, pDeadGuy->_deadData[dd], pDeadGuy->_deadFrame, pDeadGuy->_deadWidth, 0, a5);
					}
				} else {
					// app_fatal("Unclipped dead: frame %d of %d, deadnum==%d", nCel, pFrameTable[0], (bDead & 0x1F) - 1);
				}
			}
		}
		if(bObj != 0) {
			DrawObject(sx, sy, dx, dy, 1, 0, a5);
		}
	}
	if(bItem != 0) {
		pItem = &item[bItem - 1];
		if(!pItem->_iPostDraw) {
			/// ASSERT: assert((unsigned char)bItem <= MAXITEMS);
			if((unsigned char)bItem <= MAXITEMS) {
				pCelBuff = pItem->_iAnimData;
				if(pCelBuff != NULL) {
					nCel = pItem->_iAnimFrame;
					pFrameTable = (DWORD *)pCelBuff;
					if(nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
						px = dx - pItem->_iAnimWidth2;
						if(bItem - 1 == pcursitem) {
							CelDecodeClr(181, px, dy, pItem->_iAnimData, pItem->_iAnimFrame, pItem->_iAnimWidth, 0, a5);
						}
						CelDecodeHdrLightOnly(px, dy, pItem->_iAnimData, pItem->_iAnimFrame, pItem->_iAnimWidth, 0, a5);
					} else {
						// app_fatal("Draw \"%s\" Item 1: frame %d of %d, item type==%d", pItem->_iIName, nCel, pFrameTable[0], pItem->_itype);
					}
				} else {
					// app_fatal("Draw Item \"%s\" 1: NULL Cel Buffer", pItem->_iIName);
				}
			}
		}
	}
	if(bFlag & 0x20) {
		p = -(negPlr + 1);
		if((DWORD)p < MAX_PLRS) {
			pPlayer = &plr[p];
			px = dx + pPlayer->_pxoff - pPlayer->_pAnimWidth2;
			py = dy + pPlayer->_pyoff;
			DrawPlayer(p, sx, sy - 1, px, py, pPlayer->_pAnimData, pPlayer->_pAnimFrame, pPlayer->_pAnimWidth, 0, a5);
			if(me_flag && pPlayer->_peflag != 0) {
				if(pPlayer->_peflag == 2) {
					scrollrt_draw_e_flag(pBuff - (768 * 16 + 96), sx - 2, sy + 1, a4, a5, dx - 96, dy - 16);
				}
				scrollrt_draw_e_flag(pBuff - 64, sx - 1, sy + 1, a4, a5, dx - 64, dy);
			}
		} else {
			// app_fatal("draw player: tried to draw illegal player %d", p);
		}
	}
	if((bFlag & 0x10) && ((bFlag & 0x40) || plr[myplr]._pInfraFlag) && negMon < 0) {
		draw_monster_num = -(negMon + 1);
		if((DWORD)draw_monster_num < MAXMONSTERS) {
			pMonster = &monster[draw_monster_num];
			if(!(pMonster->_mFlags & 1)) {
				if(pMonster->MType != NULL) {
					py = dy + pMonster->_myoff;
					px = dx + pMonster->_mxoff - pMonster->MType->flags_2;
					if(draw_monster_num == pcursmonst) {
						Cl2DecodeFrm2(233, px, py, pMonster->_mAnimData, pMonster->_mAnimFrame, pMonster->MType->flags_1, 0, a5);
					}
					DrawMonster(sx, sy, px, py, draw_monster_num, 0, a5);
					if(me_flag && !pMonster->_meflag) {
						scrollrt_draw_e_flag(pBuff - 64, sx - 1, sy + 1, a4, a5, dx - 64, dy);
					}
				} else {
					// app_fatal("Draw Monster \"%s\": uninitialized monster", pMonster->mName);
				}
			}
		} else {
			// app_fatal("Draw Monster: tried to draw illegal monster %d", draw_monster_num);
		}
	}
	if(bFlag & 4) {
		DrawDeadPlayer(sx, sy, dx, dy, 0, a5, 0);
	}
	if(bPlr > 0) {
		p = bPlr - 1;
		if((DWORD)p < MAX_PLRS) {
			pPlayer = &plr[p];
			px = dx + pPlayer->_pxoff - pPlayer->_pAnimWidth2;
			py = dy + pPlayer->_pyoff;
			DrawPlayer(p, sx, sy, px, py, pPlayer->_pAnimData, pPlayer->_pAnimFrame, pPlayer->_pAnimWidth, 0, a5);
			if(me_flag && pPlayer->_peflag != 0) {
				if(pPlayer->_peflag == 2) {
					scrollrt_draw_e_flag(pBuff - (768 * 16 + 96), sx - 2, sy + 1, a4, a5, dx - 96, dy - 16);
				}
				scrollrt_draw_e_flag(pBuff - 64, sx - 1, sy + 1, a4, a5, dx - 64, dy);
			}
		} else {
			// app_fatal("draw player: tried to draw illegal player %d", p);
		}
	}
	if(nMon > 0 && ((bFlag & 0x40) || plr[myplr]._pInfraFlag)) {
		draw_monster_num = nMon - 1;
		if((DWORD)draw_monster_num < MAXMONSTERS) {
			pMonster = &monster[draw_monster_num];
			if(!(pMonster->_mFlags & 1)) {
				if(pMonster->MType != NULL) {
					py = dy + pMonster->_myoff;
					px = dx + pMonster->_mxoff - pMonster->MType->flags_2;
					if(draw_monster_num == pcursmonst) {
						Cl2DecodeFrm2(233, px, py, pMonster->_mAnimData, pMonster->_mAnimFrame, pMonster->MType->flags_1, 0, a5);
					}
					DrawMonster(sx, sy, px, py, draw_monster_num, 0, a5);
					if(me_flag && !pMonster->_meflag) {
						scrollrt_draw_e_flag(pBuff - 64, sx - 1, sy + 1, a4, a5, dx - 64, dy);
					}
				} else {
					// app_fatal("Draw Monster \"%s\": uninitialized monster", pMonster->mName);
				}
			}
		} else {
			// app_fatal("Draw Monster: tried to draw illegal monster %d", draw_monster_num);
		}
	}
	if(bFlag & 1) {
		DrawMissile(sx, sy, dx, dy, 0, a5, 0);
	}
	if(bObj != 0 && light_table_index < lightmax) {
		DrawObject(sx, sy, dx, dy, 0, 0, a5);
	}
	if(bItem != 0) {
		pItem = &item[bItem - 1];
		if(pItem->_iPostDraw) {
			/// ASSERT: assert((unsigned char)bItem <= MAXITEMS);
			if((unsigned char)bItem <= MAXITEMS) {
				pCelBuff = pItem->_iAnimData;
				if(pCelBuff != NULL) {
					nCel = pItem->_iAnimFrame;
					pFrameTable = (DWORD *)pCelBuff;
					if(nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
						px = dx - pItem->_iAnimWidth2;
						if(bItem - 1 == pcursitem) {
							CelDecodeClr(181, px, dy, pItem->_iAnimData, pItem->_iAnimFrame, pItem->_iAnimWidth, 0, a5);
						}
						CelDecodeHdrLightOnly(px, dy, pItem->_iAnimData, pItem->_iAnimFrame, pItem->_iAnimWidth, 0, a5);
					} else {
						// app_fatal("Draw \"%s\" Item 2: frame %d of %d, item type==%d", pItem->_iIName, nCel, pFrameTable[0], pItem->_itype);
					}
				} else {
					// app_fatal("Draw Item \"%s\" 2: NULL Cel Buffer", pItem->_iIName);
				}
			}
		}
	}
	if(bArch != 0) {
		cel_transparency_active = (unsigned char)TransList[bMap];
		CelDecodeHdrLightTrans(pBuff, pSpecialCels, bArch, 64, 0, a5);
	}
}

static void scrollrt_draw_upper(int x, int y, int sx, int sy, int a5, int a6, int some_flag)
{
	int i, j, dir;
	BYTE *dst;
	MICROS *pMap;

	/// ASSERT: assert(gpBuffer);

	pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];
	dir = 2 * a6 + 2;
	if(dir > 8) {
		dir = 8;
	}

	if(some_flag) {
		if(y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_piece_id = dPiece[x][y];
			light_table_index = dLight[x][y];
			if(level_piece_id != 0) {
				dst = &gpBuffer[sx + 32 + PitchTbl[sy]];
				cel_transparency_active = (unsigned char)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
				if(a6 >= 0) {
					level_cel_block = pMap->mt[1];
					if(level_cel_block != 0) {
						arch_draw_type = 2;
						drawUpperScreen(dst);
						arch_draw_type = 0;
					}
				}
				dst -= 768 * 32;
				if(a6 >= 1) {
					level_cel_block = pMap->mt[3];
					if(level_cel_block != 0) {
						drawUpperScreen(dst);
					}
				}
				dst -= 768 * 32;
				if(a6 >= 2) {
					level_cel_block = pMap->mt[5];
					if(level_cel_block != 0) {
						drawUpperScreen(dst);
					}
				}
				dst -= 768 * 32;
				if(a6 >= 3) {
					level_cel_block = pMap->mt[7];
					if(level_cel_block != 0) {
						drawUpperScreen(dst);
					}
				}
				scrollrt_draw_dungeon(&gpBuffer[sx + PitchTbl[sy]], x, y, a6, dir, sx, sy, 0);
			} else {
				world_draw_black_tile(&gpBuffer[sx + PitchTbl[sy]]);
			}
		}
		x++;
		y--;
		sx += 64;
		a5--;
		pMap++;
	}

	for(j = 0; j < a5; j++) {
		if(y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_piece_id = dPiece[x][y];
			light_table_index = dLight[x][y];
			if(level_piece_id != 0) {
				dst = &gpBuffer[sx + PitchTbl[sy]];
				cel_transparency_active = (unsigned char)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
				arch_draw_type = 1;
				level_cel_block = pMap->mt[0];
				if(level_cel_block != 0) {
					drawUpperScreen(dst);
				}
				arch_draw_type = 2;
				level_cel_block = pMap->mt[1];
				if(level_cel_block != 0) {
					drawUpperScreen(dst + 32);
				}
				arch_draw_type = 0;
				for(i = 1; i < (MicroTileLen >> 1) - 1; i++) {
					dst -= 768 * 32;
					if(a6 >= i) {
						level_cel_block = pMap->mt[2 * i];
						if(level_cel_block != 0) {
							drawUpperScreen(dst);
						}
						level_cel_block = pMap->mt[2 * i + 1];
						if(level_cel_block != 0) {
							drawUpperScreen(dst + 32);
						}
					}
				}
				scrollrt_draw_dungeon(&gpBuffer[sx + PitchTbl[sy]], x, y, a6, dir, sx, sy, 1);
			} else {
				world_draw_black_tile(&gpBuffer[sx + PitchTbl[sy]]);
			}
		}
		x++;
		y--;
		sx += 64;
		pMap++;
	}

	if(some_flag && y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
		level_piece_id = dPiece[x][y];
		light_table_index = dLight[x][y];
		if(level_piece_id != 0) {
			dst = &gpBuffer[sx + PitchTbl[sy]];
			cel_transparency_active = (unsigned char)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
			arch_draw_type = 1;
			if(a6 >= 0) {
				level_cel_block = pMap->mt[0];
				if(level_cel_block != 0) {
					drawUpperScreen(dst);
				}
			}
			arch_draw_type = 0;
			dst -= 768 * 32;
			if(a6 >= 1) {
				level_cel_block = pMap->mt[2];
				if(level_cel_block != 0) {
					drawUpperScreen(dst);
				}
			}
			dst -= 768 * 32;
			if(a6 >= 2) {
				level_cel_block = pMap->mt[4];
				if(level_cel_block != 0) {
					drawUpperScreen(dst);
				}
			}
			dst -= 768 * 32;
			if(a6 >= 3) {
				level_cel_block = pMap->mt[6];
				if(level_cel_block != 0) {
					drawUpperScreen(dst);
				}
			}
			scrollrt_draw_dungeon(&gpBuffer[sx + PitchTbl[sy]], x, y, a6, dir, sx, sy, 0);
		} else {
			world_draw_black_tile(&gpBuffer[sx + PitchTbl[sy]]);
		}
	}
}

static void DrawGame(int x, int y)
{
	int i, sx, sy, chunks, blocks;

	ViewDX = 640;
	ViewDY = 352;
	ViewBX = 10;
	ViewBY = 11;

	sx = ScrollInfo._sxoff + 64;
	sy = ScrollInfo._syoff + 175;
	x -= 10;
	y--;
	chunks = 10;
	blocks = 8;

	if(chrflag || questlog) {
		x += 2;
		y -= 2;
		sx += 288;
		chunks = 6;
	}
	if(invflag || sbookflag) {
		x += 2;
		y -= 2;
		sx -= 32;
		chunks = 6;
	}

	switch(ScrollInfo._sdir) {
	case 0:
		break;
	case 2:
		chunks++;
	case 1:
		sy -= 32;
		x--;
		y--;
		blocks++;
		break;
	case 4:
		blocks++;
	case 3:
		chunks++;
		break;
	case 5:
		blocks++;
		break;
	case 6:
		blocks++;
	case 7:
		sx -= 64;
		x--;
		y++;
		chunks++;
		break;
	case 8:
		sx -= 64;
		sy -= 32;
		x -= 2;
		chunks++;
		blocks++;
		break;
	}

	/// ASSERT: assert(gpBuffer);
	gpBufEnd = &gpBuffer[PitchTbl[160]];
	for(i = 0; i < 4; i++) {
		scrollrt_draw_upper(x, y, sx, sy, chunks, i, 0);
		y++;
		sx -= 32;
		sy += 16;
		scrollrt_draw_upper(x, y, sx, sy, chunks, i, 1);
		x++;
		sx += 32;
		sy += 16;
	}
	/// ASSERT: assert(gpBuffer);
	gpBufEnd = &gpBuffer[PitchTbl[512]];
	for(i = 0; i < blocks; i++) {
		scrollrt_draw_lower(x, y, sx, sy, chunks, 0);
		y++;
		sx -= 32;
		sy += 16;
		scrollrt_draw_lower(x, y, sx, sy, chunks, 1);
		x++;
		sx += 32;
		sy += 16;
	}
	arch_draw_type = 0;
	for(i = 0; i < 4; i++) {
		scrollrt_draw_lower_2(x, y, sx, sy, chunks, i, 0);
		y++;
		sx -= 32;
		sy += 16;
		scrollrt_draw_lower_2(x, y, sx, sy, chunks, i, 1);
		x++;
		sx += 32;
		sy += 16;
	}
}

static void DrawZoom(int x, int y)
{
	int i, sx, sy, chunks, blocks;
	int wdt, nSrcOff, nDstOff;

	ViewDX = 384;
	ViewDY = 192;
	ViewBX = 6;
	ViewBY = 6;

	sx = ScrollInfo._sxoff + 64;
	sy = ScrollInfo._syoff + 143;
	x -= 6;
	y--;
	chunks = 6;
	blocks = 3;

	switch(ScrollInfo._sdir) {
	case 0:
		break;
	case 2:
		chunks++;
	case 1:
		sy -= 32;
		x--;
		y--;
		blocks++;
		break;
	case 4:
		blocks++;
	case 3:
		chunks++;
		break;
	case 5:
		blocks++;
		break;
	case 6:
		blocks++;
	case 7:
		sx -= 64;
		x--;
		y++;
		chunks++;
		break;
	case 8:
		sx -= 64;
		sy -= 32;
		x -= 2;
		chunks++;
		blocks++;
		break;
	}

	/// ASSERT: assert(gpBuffer);
	gpBufEnd = &gpBuffer[PitchTbl[143]];
	for(i = 0; i < 4; i++) {
		scrollrt_draw_upper(x, y, sx, sy, chunks, i, 0);
		y++;
		sx -= 32;
		sy += 16;
		scrollrt_draw_upper(x, y, sx, sy, chunks, i, 1);
		x++;
		sx += 32;
		sy += 16;
	}
	/// ASSERT: assert(gpBuffer);
	gpBufEnd = &gpBuffer[PitchTbl[320]];
	for(i = 0; i < blocks; i++) {
		scrollrt_draw_lower(x, y, sx, sy, chunks, 0);
		y++;
		sx -= 32;
		sy += 16;
		scrollrt_draw_lower(x, y, sx, sy, chunks, 1);
		x++;
		sx += 32;
		sy += 16;
	}
	arch_draw_type = 0;
	for(i = 0; i < 4; i++) {
		scrollrt_draw_lower_2(x, y, sx, sy, chunks, i, 0);
		y++;
		sx -= 32;
		sy += 16;
		scrollrt_draw_lower_2(x, y, sx, sy, chunks, i, 1);
		x++;
		sx += 32;
		sy += 16;
	}

	if(chrflag || questlog) {
		nSrcOff = SCREENXY(112, 159);
		nDstOff = SCREENXY(320, 350);
		wdt = 160;
	} else if(invflag || sbookflag) {
		nSrcOff = SCREENXY(112, 159);
		nDstOff = SCREENXY(0, 350);
		wdt = 160;
	} else {
		nSrcOff = SCREENXY(32, 159);
		nDstOff = SCREENXY(0, 350);
		wdt = 320;
	}

	/// ASSERT: assert(gpBuffer);

#ifdef USE_ASM
	__asm {
		mov		esi, gpBuffer
		mov		edx, nDstOff
		mov		edi, esi
		mov		ecx, nSrcOff
		add		edi, edx
		add		esi, ecx
		mov		ebx, edi
		add		ebx, 768
		mov		edx, 176
	label1:
		mov		ecx, wdt
	label2:
		mov		al, [esi]
		inc		esi
		mov		ah, al
		mov		[edi], ax
		mov		[ebx], ax
		add		edi, 2
		add		ebx, 2
		dec		ecx
		jnz		label2
		mov		eax, 768
		add		eax, wdt
		sub		esi, eax
		add		eax, eax
		sub		ebx, eax
		sub		edi, eax
		dec		edx
		jnz		label1
	}
#else
	int hgt;
	BYTE *src, *dst1, *dst2;

	src = &gpBuffer[nSrcOff];
	dst1 = &gpBuffer[nDstOff];
	dst2 = &gpBuffer[nDstOff + 768];

	for(hgt = 176; hgt != 0; hgt--, src -= 768 + wdt, dst1 -= 2 * (768 + wdt), dst2 -= 2 * (768 + wdt)) {
		for(i = wdt; i != 0; i--) {
			*dst1++ = *src;
			*dst1++ = *src;
			*dst2++ = *src;
			*dst2++ = *src;
			src++;
		}
	}
#endif
}

void DrawView(int StartX, int StartY)
{
	if(zoomflag) {
		DrawGame(StartX, StartY);
	} else {
		DrawZoom(StartX, StartY);
	}
	if(automapflag) {
		DrawAutomap();
	}
	if(invflag) {
		DrawInv();
	} else if(sbookflag) {
		DrawSpellBook();
	}

	DrawDurIcon();

	if(chrflag) {
		DrawChr();
	} else if(questlog) {
		DrawQuestLog();
	} else if(plr[myplr]._pStatPts != 0 && !spselflag) {
		DrawLevelUpIcon();
	}
	if(uitemflag) {
		DrawUniqueInfo();
	}
	if(qtextflag) {
		DrawQText();
	}
	if(spselflag) {
		DrawSpellList();
	}
	if(dropGoldFlag) {
		DrawGoldSplit(dropGoldValue);
	}
	if(helpflag) {
		DrawHelp();
	}
	if(msgflag) {
		DrawDiabloMsg();
	}
	if(deathflag) {
		RedBack();
	} else if(PauseMode != 0) {
		gmenu_draw_pause();
	}

	DrawPlrMsg();
	gmenu_draw();
	doom_draw();
	DrawInfoBox();
	DrawLifeFlask();
	DrawManaFlask();
}

void ClearScreenBuffer()
{
	lock_buf(3);

	/// ASSERT: assert(gpBuffer);

#ifdef USE_ASM
	__asm {
		mov		edi, gpBuffer
		add		edi, SCREENXY(0, 0)
		mov		edx, 480
		xor		eax, eax
	zeroline:
		mov		ecx, 640 / 4
		rep stosd
		add		edi, 768 - 640
		dec		edx
		jnz		zeroline
	}
#else
	int i;
	BYTE *dst;

	dst = &gpBuffer[SCREENXY(0, 0)];

	for(i = 0; i < 480; i++, dst += 768) {
		memset(dst, 0, 640);
	}
#endif

	unlock_buf(3);
}

#ifdef _DEBUG
void ScrollView()
{
	BOOL scroll;

	if(pcurs >= CURSOR_FIRSTITEM)
		return;

	scroll = FALSE;

	if(MouseX < 20) {
		if(dmaxy - 1 <= ViewY || dminx >= ViewX) {
			if(dmaxy - 1 > ViewY) {
				ViewY++;
				scroll = TRUE;
			}
			if(dminx < ViewX) {
				ViewX--;
				scroll = TRUE;
			}
		} else {
			ViewY++;
			ViewX--;
			scroll = TRUE;
		}
	}
	if(MouseX > 640-20) {
		if(dmaxx - 1 <= ViewX || dminy >= ViewY) {
			if(dmaxx - 1 > ViewX) {
				ViewX++;
				scroll = TRUE;
			}
			if(dminy < ViewY) {
				ViewY--;
				scroll = TRUE;
			}
		} else {
			ViewY--;
			ViewX++;
			scroll = TRUE;
		}
	}
	if(MouseY < 20) {
		if(dminy >= ViewY || dminx >= ViewX) {
			if(dminy < ViewY) {
				ViewY--;
				scroll = TRUE;
			}
			if(dminx < ViewX) {
				ViewX--;
				scroll = TRUE;
			}
		} else {
			ViewX--;
			ViewY--;
			scroll = TRUE;
		}
	}
	if(MouseY > 480-20) {
		if(dmaxy - 1 <= ViewY || dmaxx - 1 <= ViewX) {
			if(dmaxy - 1 > ViewY) {
				ViewY++;
				scroll = TRUE;
			}
			if(dmaxx - 1 > ViewX) {
				ViewX++;
				scroll = TRUE;
			}
		} else {
			ViewX++;
			ViewY++;
			scroll = TRUE;
		}
	}

	if(scroll)
		ScrollInfo._sdir = 0;
}

void EnableFrameCount()
{
	frameflag = frameflag == 0;
	framestart = GetTickCount();
}

static void DrawFPS()
{
	DWORD v0; // eax
	int v1; // esi
	char String[12]; // [esp+8h] [ebp-10h]
	HDC hdc; // [esp+14h] [ebp-4h]

	if ( frameflag && gbActive )
	{
		++frameend;
		v0 = GetTickCount();
		v1 = v0 - framestart;
		if ( v0 - framestart >= 1000 )
		{
			framestart = v0;
			framerate = 1000 * frameend / v1;
			frameend = 0;
		}
		if ( framerate > 99 )
			framerate = 99;
		wsprintf(String, "%2d", framerate);
		if ( !lpDDSPrimary->GetDC(&hdc) )
		{
			TextOut(hdc, 0, 400, String, strlen(String));
			lpDDSPrimary->ReleaseDC(hdc);
		}
	}
}
#endif

static void DoBlitScreen(DWORD dwX, DWORD dwY, DWORD dwWdt, DWORD dwHgt)
{
	int nSrcOff, nDstOff, nSrcWdt, nDstWdt;
	DWORD dwTicks;
	HRESULT hDDVal;
	RECT SrcRect;

	/// ASSERT: assert(! (dwX & 3));
	/// ASSERT: assert(! (dwWdt & 3));

	if(lpDDSBackBuf != NULL) {
		SrcRect.left = dwX + 64;
		SrcRect.top = dwY + 160;
		SrcRect.right = SrcRect.left + dwWdt - 1;
		SrcRect.bottom = SrcRect.top + dwHgt - 1;
		/// ASSERT: assert(! gpBuffer);
		dwTicks = GetTickCount();
		while(1) {
			hDDVal = lpDDSPrimary->BltFast(dwX, dwY, lpDDSBackBuf, &SrcRect, DDBLTFAST_WAIT);
			if(hDDVal == DD_OK) {
				break;
			}
			if(dwTicks - GetTickCount() > 5000) {
				break;
			}
			Sleep(1);
			if(hDDVal == DDERR_SURFACELOST) {
				return;
			}
			if(hDDVal != DDERR_WASSTILLDRAWING && hDDVal != DDERR_SURFACEBUSY) {
				break;
			}
		}
		if(hDDVal != DDERR_SURFACELOST
		&& hDDVal != DDERR_WASSTILLDRAWING
		&& hDDVal != DDERR_SURFACEBUSY
		&& hDDVal != DD_OK) {
			DDErrMsg(hDDVal, 3596, "C:\\Src\\Diablo\\Source\\SCROLLRT.CPP");
		}
	} else {
		nSrcOff = SCREENXY(dwX, dwY);
		nDstOff = dwX * (SCREEN_BPP / 8) + dwY * DDS_desc.lPitch;
		nSrcWdt = 768 - dwWdt;
		nDstWdt = DDS_desc.lPitch - dwWdt * (SCREEN_BPP / 8);
		dwWdt >>= 2;

		lock_buf(6);

		/// ASSERT: assert(gpBuffer);

#if defined(USE_ASM) && !defined(RGBMODE)
		__asm {
			mov		esi, gpBuffer
			mov		edi, DDS_desc.lpSurface
			add		esi, nSrcOff
			add		edi, nDstOff
			mov		eax, nSrcWdt
			mov		ebx, nDstWdt
			mov		edx, dwHgt
		blitline:
			mov		ecx, dwWdt
			rep movsd
			add		esi, eax
			add		edi, ebx
			dec		edx
			jnz		blitline
		}
#else
		int wdt, hgt;
		BYTE *src, *dst;

		src = &gpBuffer[nSrcOff];
		dst = (BYTE *)DDS_desc.lpSurface + nDstOff;

		for(hgt = 0; hgt < dwHgt; hgt++, src += nSrcWdt, dst += nDstWdt) {
			for(wdt = 0; wdt < 4 * dwWdt; wdt++) {
#ifndef RGBMODE
				*dst++ = *src++;
#else
				PALETTEENTRY pal = system_palette[*src++];
				dst[0] = pal.peBlue;
				dst[1] = pal.peGreen;
				dst[2] = pal.peRed;
				dst += 4;
#endif
			}
		}
#endif

		unlock_buf(6);
	}
}

static void DrawMain(int dwHgt, int draw_desc, int draw_hp, int draw_mana, int draw_sbar, int draw_btn)
{
	int ysize;
	DWORD dwTicks;
	BOOL retry;
	HRESULT hDDVal;

	ysize = dwHgt;

	if(!gbActive || lpDDSPrimary == NULL) {
		return;
	}

	if(lpDDSPrimary->IsLost() == DDERR_SURFACELOST) {
		if(lpDDSPrimary->Restore() != DD_OK) {
			return;
		}
		ResetPal();
		ysize = 480;
	}

	if(lpDDSBackBuf == NULL) {
		retry = TRUE;
		dwTicks = GetTickCount();
		while(1) {
			DDS_desc.dwSize = sizeof(DDS_desc);
			hDDVal = lpDDSPrimary->Lock(NULL, &DDS_desc, DDLOCK_WRITEONLY|DDLOCK_WAIT, NULL);
			if(hDDVal == DD_OK) {
				break;
			}
			if(dwTicks - GetTickCount() > 5000) {
				break;
			}
			Sleep(1);
			if(hDDVal == DDERR_SURFACELOST) {
				return;
			}
			if(hDDVal != DDERR_WASSTILLDRAWING && hDDVal != DDERR_SURFACEBUSY) {
				if(!retry || hDDVal != DDERR_GENERIC) {
					break;
				}
				retry = FALSE;
				dx_reinit();
				ysize = 480;
				dwTicks = GetTickCount();
			}
		}
		if(hDDVal == DDERR_SURFACELOST
		|| hDDVal == DDERR_WASSTILLDRAWING
		|| hDDVal == DDERR_SURFACEBUSY) {
			return;
		}
		if(hDDVal != DD_OK) {
			DDErrMsg(hDDVal, 3707, "C:\\Src\\Diablo\\Source\\SCROLLRT.CPP");
		}
	}

	/// ASSERT: assert(ysize >= 0 && ysize <= 480);

	if(ysize > 0) {
		DoBlitScreen(0, 0, 640, ysize);
	}
	if(ysize < 480) {
		if(draw_sbar) {
			DoBlitScreen(204, 357, 232, 28);
		}
		if(draw_desc) {
			DoBlitScreen(176, 398, 288, 60);
		}
		if(draw_mana) {
			DoBlitScreen(460, 352, 88, 72);
			DoBlitScreen(564, 416, 56, 56);
		}
		if(draw_hp) {
			DoBlitScreen(96, 352, 88, 72);
		}
		if(draw_btn) {
			DoBlitScreen(8, 357, 72, 119);
			DoBlitScreen(556, 357, 72, 48);
			if(gbMaxPlayers > 1) {
				DoBlitScreen(84, 443, 36, 32);
				DoBlitScreen(524, 443, 36, 32);
			}
		}
		if(sgdwCursWdtOld != 0) {
			DoBlitScreen(sgdwCursXOld, sgdwCursYOld, sgdwCursWdtOld, sgdwCursHgtOld);
		}
		if(sgdwCursWdt != 0) {
			DoBlitScreen(sgdwCursX, sgdwCursY, sgdwCursWdt, sgdwCursHgt);
		}
	}

	if(lpDDSBackBuf == NULL) {
		hDDVal = lpDDSPrimary->Unlock(NULL);
		if(hDDVal != DDERR_SURFACELOST && hDDVal != DD_OK) {
			DDErrMsg(hDDVal, 3779, "C:\\Src\\Diablo\\Source\\SCROLLRT.CPP");
		}
	}

#ifdef _DEBUG
	DrawFPS();
#endif
}

void scrollrt_draw_game_screen(BOOL draw_cursor)
{
	int hgt;

	if(force_redraw == 255) {
		force_redraw = 0;
		hgt = 480;
	} else {
		hgt = 0;
	}

	if(draw_cursor) {
		lock_buf(0);
		scrollrt_draw_cursor_item();
		unlock_buf(0);
	}

	DrawMain(hgt, 0, 0, 0, 0, 0);

	if(draw_cursor) {
		lock_buf(0);
		scrollrt_draw_cursor_back_buffer();
		unlock_buf(0);
	}
}

void DrawAndBlit()
{
	int hgt;
	BOOL ddsdesc, ctrlPan;

	if(!gbRunGame) {
		return;
	}

	if(force_redraw == 255) {
		drawhpflag = TRUE;
		drawmanaflag = TRUE;
		drawbtnflag = TRUE;
		drawsbarflag = TRUE;
		ddsdesc = FALSE;
		ctrlPan = TRUE;
		hgt = 480;
	} else if(force_redraw == 1) {
		ddsdesc = TRUE;
		ctrlPan = FALSE;
		hgt = 352;
	} else {
		return;
	}

	force_redraw = 0;

	lock_buf(0);
	if(leveltype != DTYPE_TOWN) {
		DrawView(ViewX, ViewY);
	} else {
		T_DrawView(ViewX, ViewY);
	}
	if(ctrlPan) {
		DrawCtrlPan();
	}
	if(drawhpflag) {
		UpdateLifeFlask();
	}
	if(drawmanaflag) {
		UpdateManaFlask();
	}
	if(drawbtnflag) {
		DrawCtrlBtns();
	}
	if(drawsbarflag) {
		DrawInvBelt();
	}
	if(talkflag) {
		DrawTalkPan();
		hgt = 480;
	}
	scrollrt_draw_cursor_item();
	unlock_buf(0);

	DrawMain(hgt, ddsdesc, drawhpflag, drawmanaflag, drawsbarflag, drawbtnflag);

	lock_buf(0);
	scrollrt_draw_cursor_back_buffer();
	unlock_buf(0);

	drawhpflag = FALSE;
	drawmanaflag = FALSE;
	drawbtnflag = FALSE;
	drawsbarflag = FALSE;
}
