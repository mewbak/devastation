pLevelPieces = DiabLoad("Levels\\L1Data\\L1.MIN", NULL, 'TILE');
pLevelPieces -> pMiniTiles/pMicroTiles

mini 40x40
micro 112x112

#define DBORDER 16
#define TMINI(t) (((t) - DBORDER) >> 1)
#define TMICRO(t) (((t) << 1) + DBORDER)

void ObjSetMini(int x, int y, int v)
{
	int xx, yy;
	long v1, v2, v3, v4;

#ifdef USE_ASM
	__asm {
		mov		esi, pMegaTiles
		xor		eax, eax
		mov		ax, word ptr v
		dec		eax
		shl		eax, 3
		add		esi, eax
		xor		eax, eax
		lodsw
		inc		eax
		mov		v1, eax
		lodsw
		inc		eax
		mov		v2, eax
		lodsw
		inc		eax
		mov		v3, eax
		lodsw
		inc		eax
		mov		v4, eax
	}
#else
	v--;
	v1 = ((WORD *)&pMegaTiles[v << 3])[0] + 1;
	v2 = ((WORD *)&pMegaTiles[v << 3])[1] + 1;
	v3 = ((WORD *)&pMegaTiles[v << 3])[2] + 1;
	v4 = ((WORD *)&pMegaTiles[v << 3])[3] + 1;
#endif

	xx = TMICRO(x);//2 * x + 16;
	yy = TMICRO(y);//2 * y + 16;
	ObjSetMicro(xx, yy, v1);
	ObjSetMicro(xx + 1, yy, v2);
	ObjSetMicro(xx, yy + 1, v3);
	ObjSetMicro(xx + 1, yy + 1, v4);
}