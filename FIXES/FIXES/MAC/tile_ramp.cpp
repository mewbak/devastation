BOOL tile_45(BYTE *dst, BYTE *src, int *i, BOOL trans) // left + trap
{
	int dist = dst - gpBufEnd;

	if ( dist >= 0 )
	{
		dist += 1023;
		dist >>= 8;
		if ( dist > (768 * 15) >> 8 )
		{
			dst -= 768 * 16; // skip first half of 32x32 height
			src += 32 * 9;
			return FALSE;
		}
		world_tbl = WorldTbl3x16[dist];
		src += WorldTbl17_1[world_tbl >> 2];
		dst -= 192 * world_tbl;
		*i -= world_tbl >> 1;
		if ( trans )
		{
			WorldBoolFlag += world_tbl >> 2;
		}
	}

	return TRUE;
}

BOOL tile_42(BYTE *dst, BYTE *src, int *j, BOOL trans) // right no trap
{
	int dist = dst - gpBufEnd;

	if ( dist >= 0 )
	{
		dist += 1023;
		dist >>= 8;
		if ( dist > (768 * 14) >> 8 )
		{
			dst -= 768 * 15;
			src += 32 * 8;
			return FALSE;
		}
		world_tbl = WorldTbl3x16[dist];
		src += WorldTbl17_2[world_tbl >> 2];
		dst -= 192 * world_tbl;
		*j += world_tbl >> 1;
		if ( trans )
		{
			WorldBoolFlag += world_tbl >> 2;
		}
	}

	return TRUE;
}

	i = 30;
	if ( tile_45(&i) )
	{
		DrawTriangle();
	}
	j = 2;
	if ( tile_42(&j) )
	{
		DrawSquare();
	}