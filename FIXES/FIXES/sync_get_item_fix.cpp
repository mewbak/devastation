SyncGetItem check mac release
only last two are asserts

void SyncGetItem(int x,int y,int idx,short ci,int iseed)

{
	char cVar1;
	ushort a2;
	undefined4 str;
	short sVar3;
	short sVar4;
	int ii;
	undefined2 in_register_0000001e;
	uint uVar6;
	short sVar7;
	uint uVar8;
	int j;
	int jj;
	short unaff_s3;
	short in_lo;
	
	uVar6 = CONCAT22(in_register_0000001e,ci);
	str = GetStr("STR___DOING_SYNCGETITEM____N");
	_psx_debug_log_(str);
	uVar8 = y * 0xc + x * 0x510;
	if (dItem[x][x] != '\0') {
		str = GetStr("STR___ATTEMPTING_TO_FIND_ITEM_BY__X_Y__N");
		_psx_debug_log_(str);
		cVar1 = dItem[x][y];
		ii = ((int)cVar1 + -1) * 0x140;
		if ((*(int *)(&DAT_802fa7e8 + ii) == idx) && (*(int *)(&DAT_802fa6b0 + ii) == iseed)) {
			a2 = *(ushort *)(&DAT_802fa6b4 + ii);
			uVar8 = (uint)a2;
			if (uVar8 == (uint)(ushort)ci) {
				uVar8 = GetStr("STR____X_Y__SAID_II_____D__FINDGETITEM_SAYS_II_____D_N");
				iseed = FindGetItem(idx,a2,iseed);
				ii = _psx_debug_log_(uVar8,(int)cVar1 + -1);
				goto LAB_803ff9ec;
			}
		}
		FindGetItem(idx,ci,iseed);
		str = GetStr("STR___BAD__X_Y____DID_FINDGETITEM___D__N");
		ii = _psx_debug_log_(str);
	LAB_803ff9ec:
		sVar4 = (short)y + 0x69;
		if (ii == 0) {
			FUN_8024900c(y);
			return;
		}
		FUN_802102d4(uVar8 + 0x414e5300);
		ii = y;
		FUN_80248cd4();
		str = DAT_80373bcc;
		DAT_80373b80 = -ii + 0x36;
		if ((-ii - 1U < 10) && (0x40 < DAT_80373b80 + DAT_80373b84)) {
			DAT_80373b80 = 0x40 - DAT_80373b84;
		}
		sVar3 = (short)DAT_80373b80 + (short)DAT_80373b88 * -9;
		*(short *)(y + 10) = sVar3;
		sVar7 = (short)uVar8 * 2 + (short)str + -0x48a3;
		*(short *)(y + 8) = sVar7;
		*(short *)(y + 0xc) = sVar7 - in_lo;
		*(short *)(y + 0xe) = sVar3 + sVar4 * unaff_s3;
		*(uint *)y = iseed & 0xff000000U | _DAT_6567650d & uVar6;
		_DAT_6567650d = _DAT_6567650d & 0xff000000 | y & uVar6;
		return;
	}

	str = GetStr("STR___NONGOOD__X_Y__N");
	_psx_debug_log_(str);
	ii = FindGetItem(idx,ci,iseed);
	str = GetStr("STR___FINDGETITEM_RETURNED__D_N");
	_psx_debug_log_(str,ii);
	if (ii == -1) {
		return;
	}

	str = GetStr("STR___REMOVING_ITEM_FROM_MAP__N");
	_psx_debug_log_(str);
	(&dItem)
	[(int)(char)(&DAT_802fa6bd)[ii * 0x140] * 0xc +
	 (int)(char)(&DAT_802fa6bc)[ii * 0x140] * 0x510] = 0;
	j = 0;
	while (j < numitems) {
		jj = itemactive[j];
		if (jj == ii) {
			str = GetStr("STR___REMOVING_ITEM_INDEX__D__STRUCT__D_NUMITEMS__D__FROM_ITEM_LIST__N");
			_psx_debug_log_(str,j,jj,numitems);
			DeleteItem(jj,j);
			str = GetStr("STR___ITEM_REMOVED___FINDGETITEM___D__NUMITEMS___D_N");
			j = FindGetItem(idx,ci,iseed);
			_psx_debug_log_(str,j,numitems);
			if (FindGetItem(idx,ci,iseed) != -1) {
				assert_fail(2487,"source/INV.cpp","FindGetItem(idx,ci,iseed) == -1");
			}
			j = 0;
		}
		else {
			j = j + 1;
		}
	}

	if (FindGetItem(idx,ci,iseed) != -1) {
		assert_fail(2496,"source/INV.cpp","FindGetItem(idx, ci, iseed) == -1");
	}
	str = GetStr("STR___ITEM_IS_DEFINITELY_REMOVED__N");
	_psx_debug_log_(str);
	return;
}

