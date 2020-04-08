void __cdecl debug_dungeon_1()
{
	int i, j;
	int v0; // edx
	int v6; // esi
	int v9; // edx
	int v13; // esi
	int v17; // edi
	int v21; // esi
	int v25; // edi
	char dstr[124]; // [esp+Ch] [ebp-8Ch]
	int v31; // [esp+90h] [ebp-8h]
	int v32; // [esp+94h] [ebp-4h]

	v0 = 0;
	v32 = 0;
	for ( j = 0; j < 112; j++ )
	{
		for ( i = 0; i < 112; i++ )
		{
			v0 += dMonsDbg[currlevel][i][j];
			v32 += dFlagDbg[currlevel][i][j];
		}
	}
	sprintf(dstr, "Level %i : Monst Active Sum = %i : dFlag sum = %i", currlevel, v0, v32);
	NetSendCmdString(1 << myplr, dstr);
	v31 = 0;
	v32 = 0;
	for ( i = 1; i <= 2048; i++ )
	{
		if ( nSolidTable[i] )
		{
			v31 += i;
			v32++;
		}
	}

	v6 = 0;
	for ( i = 16; i < 96; i++ )
	{
		for ( j = 16; j < 96; j++ )
		{
			if ( !SolidLoc(i, j) )
			{
				v6++;
			}
		}
	}

	v9 = 0;
	for ( j = 0; j < 40; j++ )
	{
		for ( i = 0; i < 40; i++ )
		{
			v9 += (unsigned char)dungeon[i][j];
		}
	}
	sprintf(dstr, "Solid Sum = %i:%i : Monst Vol = %i : Dungeon Sum = %i", v31, v32, v6, v9);
	NetSendCmdString(1 << myplr, dstr);
	v13 = 0;
	for ( j = 0; j < 112; j++ )
	{
		for ( i = 0; i < 112; i++ )
		{
			v13 += dTransVal[i][j];
		}
	}

	v17 = 0;
	for ( j = 0; j < 112; j++ )
	{
		for ( i = 0; i < 112; i++ )
		{
			v17 += dPiece[i][j];
		}
	}
	sprintf(dstr, "Num themes = %i/%i : Trans Sum = %i : dPiece Sum = %i", numthemes, themeCount, v13, v17);
	NetSendCmdString(1 << myplr, dstr);
	if ( leveltype == 4 )
	{
		v21 = 0;
		for ( j = 0; j < 20; j++ )
		{
			for ( i = 0; i < 20; i++ )
			{
				v21 += dung[i][j];
			}
		}

		v25 = 0;
		for ( j = 0; j < 80; j++ )
		{
			for ( i = 0; i < 80; i++ )
			{
				v25 += L4dungeon[i][j];
			}
		}
		sprintf(dstr, "dung sum = %i : L4Dungeon sum = %i", v21, v25);
		/// BUGFIX: missing string send command
		/// NetSendCmdString(1 << myplr, dstr);
	}
}