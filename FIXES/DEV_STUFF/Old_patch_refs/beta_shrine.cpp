void __fastcall OperateShrine(int pnum, int i, int sType)
{
	int *_garbage; // edx
	signed __int64 t; // [esp+18h] [ebp-2Ch] MAPDST
	int v4; // [esp+28h] [ebp-1Ch] MAPDST
	__int64 lv; // [esp+2Ch] [ebp-18h] MAPDST
	int r; // [esp+34h] [ebp-10h] MAPDST
	int v3; // [esp+38h] [ebp-Ch] MAPDST
	int v2; // [esp+3Ch] [ebp-8h] MAPDST
	int v1; // [esp+40h] [ebp-4h] MAPDST

	if ( !object[i]._oSelFlag )
	{
		return;
	}

	SetRndSeed(object[i]._oRndSeed);
	if ( !deltaload )
	{
		PlaySfxLoc(36, object[i]._ox, object[i]._oy);
	}
	object[i]._oSelFlag = 0;
	object[i]._oAnimFlag = 1;
	object[i]._oAnimDelay = 1;
	switch ( object[i]._oVar1 )
	{
	case 0:
		if ( !deltaload )
		{
			r = random(155, 4);
			if ( r )
			{
				v1 = -1;
			}
			else
			{
				v1 = 5;
			}
			if ( r == 1 )
			{
				v2 = 5;
			}
			else
			{
				v2 = -1;
			}
			if ( r == 2 )
			{
				v3 = 5;
			}
			else
			{
				v3 = -1;
			}
			if ( r == 3 )
			{
				v4 = 5;
			}
			else
			{
				v4 = -1;
			}
			ModifyPlrStr(pnum, v1);
			ModifyPlrMag(pnum, v2);
			ModifyPlrDex(pnum, v3);
			ModifyPlrVit(pnum, v4);
			if ( myplr == pnum )
			{
				InitDiabloMsg(8);
			}
			goto DO_NET_SEND_RET;
		}
		break;
	case 1:
		if ( !deltaload )
		{
			v1 = plr[pnum]._pLevel << 7;
			plr[pnum]._pHitPoints += v1;
			plr[pnum]._pHPBase += v1;
			if ( plr[pnum]._pHitPoints > plr[pnum]._pMaxHP )
			{
				plr[pnum]._pHitPoints = plr[pnum]._pMaxHP;
				plr[pnum]._pHPBase = plr[pnum]._pMaxHPBase;
			}
			v1 = plr[pnum]._pLevel << 7;
			plr[pnum]._pMana -= v1;
			plr[pnum]._pManaBase -= v1;
			if ( plr[pnum]._pMana < 0 )
			{
				plr[pnum]._pManaBase -= plr[pnum]._pMana;
				plr[pnum]._pMana = 0;
			}
			if ( myplr == pnum )
			{
				drawpanflag = 255;
				InitDiabloMsg(9);
			}
			goto DO_NET_SEND_RET;
		}
		break;
	case 2:
		if ( !deltaload )
		{
			v1 = 0;
			if ( plr[pnum].InvBody[0]._itype != -1 )
			{
				v1 = 1;
			}
			if ( plr[pnum].InvBody[6]._itype != -1 )
			{
				++v1;
			}
			if ( plr[pnum].InvBody[4]._itype != -1 )
			{
				++v1;
			}
			if ( plr[pnum].InvBody[5]._itype != -1 )
			{
				++v1;
			}
			if ( v1 > 1 )
			{
				r = random(156, v1) + 1;
				if ( plr[pnum].InvBody[0]._itype != -1 && !--r )
				{
					plr[pnum].InvBody[0]._itype = -1;
				}
				if ( plr[pnum].InvBody[6]._itype != -1 && !--r )
				{
					plr[pnum].InvBody[6]._itype = -1;
				}
				if ( plr[pnum].InvBody[4]._itype != -1 && !--r )
				{
					plr[pnum].InvBody[4]._itype = -1;
				}
				if ( plr[pnum].InvBody[5]._itype != -1 && r == 1 )
				{
					plr[pnum].InvBody[5]._itype = -1;
				}
				if ( plr[pnum].InvBody[0]._itype != -1 )
				{
					plr[pnum].InvBody[0]._iDurability += 10;
					plr[pnum].InvBody[0]._iMaxDur += 10;
				}
				if ( plr[pnum].InvBody[6]._itype != -1 )
				{
					plr[pnum].InvBody[6]._iDurability += 10;
					plr[pnum].InvBody[6]._iMaxDur += 10;
				}
				if ( plr[pnum].InvBody[4]._itype != -1 )
				{
					plr[pnum].InvBody[4]._iDurability += 10;
					plr[pnum].InvBody[4]._iMaxDur += 10;
				}
				if ( plr[pnum].InvBody[5]._itype != -1 )
				{
					plr[pnum].InvBody[5]._iDurability += 10;
					plr[pnum].InvBody[5]._iMaxDur += 10;
				}
				CalcPlrInv(pnum, 1);
			}
			if ( myplr == pnum )
			{
				InitDiabloMsg(10);
			}
			goto DO_NET_SEND_RET;
		}
		break;
	case 3:
		v2 = currlevel << 8;
		for ( r = 0; r < nummonsters; ++r )
		{
			v1 = monstactive[r];
			monster[v1]._mhitpoints += v2;
			monster[v1]._mmaxhp += v2;
			monster[v1].mArmorClass = 0;
		}
		if ( !deltaload )
		{
			if ( myplr == pnum )
			{
				InitDiabloMsg(11);
			}
			goto DO_NET_SEND_RET;
		}
		break;
	case 4:
		if ( !deltaload && myplr == pnum )
		{
			if ( plr[pnum]._pGold > 1 )
			{
				AddPlrExperience(pnum, currlevel, 1000 * currlevel * currlevel);
				TakePlrsMoney(plr[pnum]._pGold - 1);
			}
			InitDiabloMsg(12);
			goto DO_NET_SEND_RET;
		}
		break;
	case 5:
		if ( !deltaload && myplr == pnum )
		{
			lv = 0i64;
			t = 1i64;
			for ( r = 1; r <= 37; ++r )
			{
				if ( t & *(_QWORD *)plr[pnum]._pMemSpells )
				{
					++lv;
				}
				t *= 2i64;
			}
			if ( lv > 1 )
			{
				lv = random(157, 74) + 1;
				r = 1;
				t = 1i64;
				while ( lv >= 0 && (SHIDWORD(lv) > 0 || (_DWORD)lv) )
				{
					if ( t & *(_QWORD *)plr[pnum]._pMemSpells )
					{
						--lv;
					}
					if ( lv >= 0 && (SHIDWORD(lv) > 0 || (_DWORD)lv) )
					{
						if ( ++r <= 37 )
						{
							t *= 2i64;
						}
						else
						{
							r = 1;
							t = 1i64;
						}
					}
				}
				if ( LOBYTE(plr[pnum]._pRSplType) == 1 && plr[pnum]._pRSpell == r )
				{
					plr[pnum]._pRSpell = -1;
					LOBYTE(plr[pnum]._pRSplType) = 4;
					drawpanflag = 255;
				}
				*(_QWORD *)plr[pnum]._pMemSpells ^= t;
				plr[pnum]._pSplLvl[r] = 0;
				t = 1i64;
				for ( r = 1; r <= 37; ++r )
				{
					if ( t & *(_QWORD *)plr[pnum]._pMemSpells )
					{
						++plr[pnum]._pSplLvl[r];
					}
					t *= 2i64;
				}
			}
			InitDiabloMsg(13);
			goto DO_NET_SEND_RET;
		}
		break;
	case 6:
		for ( r = 0; r < nobjects; ++r )
		{
			v1 = objectactive[r];
			if ( (object[v1]._otype == 5 || object[v1]._otype == 6 || object[v1]._otype == 7)
			  && !object[v1]._oSelFlag )
			{
				object[v1]._oRndSeed = GetRndSeed();
				object[v1]._oSelFlag = 1;
				object[v1]._oAnimFrame -= 2;
			}
		}
		if ( !deltaload )
		{
			if ( myplr == pnum )
			{
				InitDiabloMsg(14);
			}
			goto DO_NET_SEND_RET;
		}
		break;
	case 7:
		for ( r = 0; r < nummonsters; ++r )
		{
			monster[monstactive[r]].mMagicRes |= 0x10u;
		}
		if ( !deltaload && myplr == pnum )
		{
			_garbage = plr[pnum]._pMemSpells;
			*_garbage |= 1u;
			_garbage[1] = _garbage[1];
			plr[pnum]._pSplLvl[1] = 5;
			InitDiabloMsg(15);
			goto DO_NET_SEND_RET;
		}
		break;
	case 8:
		if ( !deltaload && myplr == pnum )
		{
			for ( r = random(158, 4) + 4; r > 0; --r )
			{
				v1 = random(158, 4);
				do
				{
					v2 = random(158, 4);
				}
				while ( v1 == v2 );
				if ( !v1 )
				{
					v3 = plr[pnum]._pBaseStr;
				}
				if ( v1 == 1 )
				{
					v3 = plr[pnum]._pBaseMag;
				}
				if ( v1 == 2 )
				{
					v3 = plr[pnum]._pBaseDex;
				}
				if ( v1 == 3 )
				{
					v3 = plr[pnum]._pBaseVit;
				}
				if ( !v2 )
				{
					v4 = plr[pnum]._pBaseStr;
					ModifyPlrStr(pnum, v3 - v4);
				}
				if ( v2 == 1 )
				{
					v4 = plr[pnum]._pBaseMag;
					ModifyPlrMag(pnum, v3 - v4);
				}
				if ( v2 == 2 )
				{
					v4 = plr[pnum]._pBaseDex;
					ModifyPlrDex(pnum, v3 - v4);
				}
				if ( v2 == 3 )
				{
					v4 = plr[pnum]._pBaseVit;
					ModifyPlrVit(pnum, v3 - v4);
				}
				if ( !v1 )
				{
					ModifyPlrStr(pnum, v4 - v3);
				}
				if ( v1 == 1 )
				{
					ModifyPlrMag(pnum, v4 - v3);
				}
				if ( v1 == 2 )
				{
					ModifyPlrDex(pnum, v4 - v3);
				}
				if ( v1 == 3 )
				{
					ModifyPlrVit(pnum, v4 - v3);
				}
			}
			plr[pnum]._pMaxHP += 1280;
			plr[pnum]._pHitPoints += 1280;
			plr[pnum]._pMaxHPBase += 1280;
			plr[pnum]._pHPBase += 1280;
			if ( !(plr[pnum]._pIFlags & 0x8000000) )
			{
				plr[pnum]._pMaxMana += 1280;
				plr[pnum]._pMana += 1280;
				plr[pnum]._pMaxManaBase += 1280;
				plr[pnum]._pManaBase += 1280;
			}
			drawpanflag = 255;
			InitDiabloMsg(16);
			goto DO_NET_SEND_RET;
		}
		break;
	case 9:
		for ( r = 0; r < nummonsters; ++r )
		{
			v1 = monstactive[r];
			monster[v1].mHit = 100;
			monster[v1].mHit2 = 100;
			monster[v1].mMinDamage = (signed int)monster[v1].mMinDamage >> 1;
			monster[v1].mMaxDamage = (signed int)monster[v1].mMaxDamage >> 1;
			monster[v1].mMinDamage2 = (signed int)monster[v1].mMinDamage2 >> 1;
			monster[v1].mMaxDamage2 = (signed int)monster[v1].mMaxDamage2 >> 1;
		}
		if ( !deltaload && myplr == pnum )
		{
			InitDiabloMsg(17);
			goto DO_NET_SEND_RET;
		}
		break;
	case 0xA:
		if ( !deltaload )
		{
			pfile_436A75(pnum);
			ModifyPlrMag(pnum, 2);
			if ( myplr == pnum )
			{
				InitDiabloMsg(18);
			}
			goto DO_NET_SEND_RET;
		}
		break;
	case 0xB:
		if ( !deltaload )
		{
			do
			{
				do
				{
					v1 = random(159, 112);
					v2 = random(159, 112);
					v3 = dPiece[v1][v2];
				}
				while ( nSolidTable[v3] );
			}
			while ( dObject[v1][v2] || dMonster[v1][v2] );
			AddMissile(plr[pnum].WorldX, plr[pnum].WorldY, v1, v2, plr[pnum]._pdir, 3, 0, pnum, 0);
			goto DO_NET_SEND_RET;
		}
		break;
	case 0xC:
		if ( !deltaload && myplr == pnum )
		{
			for ( r = 0; r < 40; ++r )
			{
				if ( !plr[pnum].InvGrid[r] )
				{
					v2 = 5 * currlevel + random(160, 10 * currlevel);
					v1 = plr[pnum]._pNumInv;
					plr[pnum].InvList[v1] = stru_615EE8;
					++plr[pnum]._pNumInv;
					plr[pnum].InvGrid[r] = plr[pnum]._pNumInv;
					plr[pnum].InvList[v1]._ivalue = v2;
					plr[pnum]._pGold += v2;
					SetGoldCurs(pnum, v1);
				}
			}
			InitDiabloMsg(19);
			goto DO_NET_SEND_RET;
		}
		break;
	default:
DO_NET_SEND_RET:
		if ( myplr == pnum )
		{
			NetSendCmdParam2(0, 0x31u, pnum, i);
		}
		break;
	}
}