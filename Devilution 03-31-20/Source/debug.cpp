#include "diablo.h"

#ifdef _DEBUG
BOOL update_seed_check = FALSE;
#endif

int seed_index;
int level_seeds[NUMLEVELS];
int seed_table[4096];

void *pSquareCel;
char dMonsDbg[NUMLEVELS][MAXDUNX][MAXDUNY];
char dFlagDbg[NUMLEVELS][MAXDUNX][MAXDUNY];

void LoadDebugGFX()
{
	if ( visiondebug )
		pSquareCel = DiabLoad("Data\\Square.CEL", NULL, 'DBGS');
}

void FreeDebugGFX()
{
	void *v0; // ecx

	v0 = pSquareCel;
	pSquareCel = 0;
	mem_free_dbg(v0);
}

#ifdef _DEBUG
void init_seed_desync()
{
	int i;

	for(i = 0; i < 4096; i++) {
		seed_table[i] = -1;
	}

	seed_index = 0;

	for(i = 0; i < NUMLEVELS; i++) {
		level_seeds[i] = 0;
	}
}

void seed_desync_index_get()
{
	if(currlevel == 0) {
		return;
	}

	update_seed_check = TRUE;
	seed_index = level_seeds[currlevel];
}

void seed_desync_index_set()
{
	if(currlevel == 0) {
		return;
	}

	update_seed_check = FALSE;
	level_seeds[currlevel + 1] = seed_index;
}

void seed_desync_check(int seed)
{
	if(!update_seed_check || seed_index == 4096 || currlevel == 0) {
		return;
	}

	if(seed_table[seed_index] == -1) {
		seed_table[seed_index] = seed;
	} else if(seed != seed_table[seed_index]) {
		app_fatal("Seeds desynced");
	}

	seed_index++;
}
#endif

void CheckDungeonClear()
{
	int i;
	int j;

	for(i = 0; i < MAXDUNX; i++)
	{
		for(j = 0; j < MAXDUNY; j++)
		{
			if ( dMonster[i][j] )
				app_fatal("Monsters not cleared");
			if ( dPlayer[i][j] )
				app_fatal("Players not cleared");

			dMonsDbg[currlevel][i][j] = dFlags[i][j] & 2;
			dFlagDbg[currlevel][i][j] = dFlags[i][j] & 8;
		}
	}
}

#ifdef _DEBUG
void GiveGoldCheat()
{
	int i; // esi
	int ni; // ebp

	for(i = 0; i < 40; i++)
	{
		if ( !plr[myplr].InvGrid[i] )
		{
			ni = plr[myplr]._pNumInv++;
			SetPlrHandItem(&plr[myplr].InvList[ni], IDI_GOLD);
			GetPlrHandSeed(&plr[myplr].InvList[ni]);
			plr[myplr].InvList[ni]._ivalue = 5000;
			plr[myplr].InvList[ni]._iCurs = 6;
			plr[myplr]._pGold += 5000;
			plr[myplr].InvGrid[i] = plr[myplr]._pNumInv;
		}
	}
}

void StoresCheat()
{
	int i; // eax

	numpremium = 0;

	for(i = 0; i < 6; i++)
		premiumitem[i]._itype = -1;

	SpawnPremium(30);

	for(i = 0; i < 20; i++)
		witchitem[i]._itype = -1;

	SpawnWitch(30);
}

void TakeGoldCheat()
{
	int i; // esi
	char ig; // cl

	for(i = 0; i < 40; i++)
	{
		ig = plr[myplr].InvGrid[i];
		if ( ig > 0 && plr[myplr].InvList[ig - 1]._itype == ITYPE_GOLD )
			RemoveInvItem(myplr, ig - 1);
	}

	for(i = 0; i < 8; i++)
	{
		if ( plr[myplr].SpdList[i]._itype == ITYPE_GOLD )
			plr[myplr].SpdList[i]._itype = -1;
	}

	plr[myplr]._pGold = 0;
}

void MaxSpellsCheat()
{
	int i; // ebp

	for(i = 1; i < 37; i++)
	{
		if ( spelldata[i].sBookLvl != -1 )
		{
			*(_QWORD *)plr[myplr]._pMemSpells |= (__int64)1 << (i - 1);
			plr[myplr]._pSplLvl[i] = 10;
		}
	}
}

void SetSpellLevelCheat(char spl, int spllvl)
{
	*(_QWORD *)plr[myplr]._pMemSpells |= (__int64)1 << (spl - 1);
	plr[myplr]._pSplLvl[spl] = spllvl;
}

void SetAllSpellsCheat()
{
	SetSpellLevelCheat(SPL_FIREBOLT, 8);
	SetSpellLevelCheat(SPL_CBOLT, 11);
	SetSpellLevelCheat(SPL_HBOLT, 10);
	SetSpellLevelCheat(SPL_HEAL, 7);
	SetSpellLevelCheat(SPL_HEALOTHER, 5);
	SetSpellLevelCheat(SPL_LIGHTNING, 9);
	SetSpellLevelCheat(SPL_FIREWALL, 5);
	SetSpellLevelCheat(SPL_TELEKINESIS, 3);
	SetSpellLevelCheat(SPL_TOWN, 3);
	SetSpellLevelCheat(SPL_FLASH, 3);
	SetSpellLevelCheat(SPL_RNDTELEPORT, 2);
	SetSpellLevelCheat(SPL_MANASHIELD, 2);
	SetSpellLevelCheat(SPL_WAVE, 4);
	SetSpellLevelCheat(SPL_FIREBALL, 3);
	SetSpellLevelCheat(SPL_STONE, 1);
	SetSpellLevelCheat(SPL_CHAIN, 1);
	SetSpellLevelCheat(SPL_GUARDIAN, 4);
	SetSpellLevelCheat(SPL_ELEMENT, 3);
	SetSpellLevelCheat(SPL_NOVA, 1);
	SetSpellLevelCheat(SPL_GOLEM, 2);
	SetSpellLevelCheat(SPL_FLARE, 1);
	SetSpellLevelCheat(SPL_BONESPIRIT, 1);
}

void PrintDebugPlayer(_bool bNextPlayer)
{
	char dstr[128]; // [esp+Ch] [ebp-80h]

	if ( bNextPlayer )
		dbgplr = ((_BYTE)dbgplr + 1) & 3;

	sprintf(dstr, "Plr %i : Active = %i", dbgplr, plr[dbgplr].plractive);
	NetSendCmdString(1 << myplr, dstr);

	if ( plr[dbgplr].plractive )
	{
		sprintf(dstr, "  Plr %i is %s", dbgplr, plr[dbgplr]._pName);
		NetSendCmdString(1 << myplr, dstr);
		sprintf(dstr, "  Lvl = %i : Change = %i", plr[dbgplr].plrlevel, plr[dbgplr]._pLvlChanging);
		NetSendCmdString(1 << myplr, dstr);
		sprintf(dstr, "  x = %i, y = %i : tx = %i, ty = %i", plr[dbgplr].WorldX, plr[dbgplr].WorldY, plr[dbgplr]._ptargx, plr[dbgplr]._ptargy);
		NetSendCmdString(1 << myplr, dstr);
		sprintf(dstr, "  mode = %i : daction = %i : walk[0] = %i", plr[dbgplr]._pmode, plr[dbgplr].destAction, plr[dbgplr].walkpath[0]);
		NetSendCmdString(1 << myplr, dstr);
		sprintf(dstr, "  inv = %i : hp = %i", plr[dbgplr]._pInvincible, plr[dbgplr]._pHitPoints);
		NetSendCmdString(1 << myplr, dstr);
	}
}

void PrintDebugQuest()
{
	char dstr[128]; // [esp+0h] [ebp-80h]

	sprintf(dstr, "Quest %i :  Active = %i, Var1 = %i", dbgqst, quests[dbgqst]._qactive, quests[dbgqst]._qvar1);
	NetSendCmdString(1 << myplr, dstr);
	if ( ++dbgqst == MAXQUESTS )
		dbgqst = 0;
}

void PrintDebugMonster(int m)
{
	_bool bActive; // ecx
	int i; // eax
	char dstr[128]; // [esp+Ch] [ebp-80h]

	sprintf(dstr, "Monster %i = %s", m, monster[m].mName);
	NetSendCmdString(1 << myplr, dstr);
	sprintf(dstr, "X = %i, Y = %i", monster[m]._mx, monster[m]._my);
	NetSendCmdString(1 << myplr, dstr);
	sprintf(dstr, "Enemy = %i, HP = %i", monster[m]._menemy, monster[m]._mhitpoints);
	NetSendCmdString(1 << myplr, dstr);
	sprintf(dstr, "Mode = %i, Var1 = %i", monster[m]._mmode, monster[m]._mVar1);
	NetSendCmdString(1 << myplr, dstr);

	bActive = 0;

	for(i = 0; i < nummonsters; i++)
	{
		if ( monstactive[i] == m )
			bActive = 1;
	}

	sprintf(dstr, "Active List = %i, Squelch = %i", bActive, monster[m]._msquelch);
	NetSendCmdString(1 << myplr, dstr);
}

void GetDebugMonster()
{
	int v0; // ecx
	int v1; // eax

	v0 = pcursmonst;
	if ( pcursmonst == -1 )
	{
		v1 = dMonster[cursmx][cursmy];
		if ( v1 )
		{
			v0 = v1 - 1;
			if ( v1 <= 0 )
				v0 = -1 - v1;
		}
		else
		{
			v0 = dbgmon;
		}
	}
	PrintDebugMonster(v0);
}

void NextDebugMonster()
{
	char dstr[128]; // [esp+0h] [ebp-80h]

	if ( dbgmon++ == MAXMONSTERS )
		dbgmon = 0;

	sprintf(dstr, "Current debug monster = %i", dbgmon);
	NetSendCmdString(1 << myplr, dstr);
}
#endif
