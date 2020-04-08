struct TMemBlock {
	DWORD dwDataSize;
	int nSig;
	DWORD dwHeader;
	DWORD dwHeader2;
	int field_10;
};

DWORD num_mem_sigs;
DWORD cur_mem_sigs;
TMemBlock *sgpMemBlock = NULL;

void engine_debug_trap(BOOL show_cursor);
void engine_add_sound_sig(int nSig, BYTE *p);
TMemBlock *engine_CreateNewSig(int nSig);
void engine_add_cur_sig(TMemBlock *pBlock, DWORD dwStart);
void engine_check_sig_error(int nSig, int nLen);
char *engine_swap_bytes(unsigned int nSig, int nSwap);
const char *engine_get_sig_error(TMemBlock *pBlock, int nLen);


void engine_debug_trap(BOOL show_cursor)
{
	TMemBlock *v1; // eax
	TMemBlock *v2; // esi

	sgMemCrit.Enter();
	v1 = sgpMemBlock;
	if ( sgpMemBlock )
	{
		do
		{
			v2 = (TMemBlock *)v1->dwDataSize;
			SMemFree(v1, "C:\\Diablo\\Direct\\ENGINE.CPP", 1970);
			v1 = v2;
		}
		while ( v2 );
	}
	sgMemCrit.Leave();
}

void engine_add_sound_sig(int nSig, BYTE *p)
{
	TMemBlock *v3; // eax
	DWORD v4; // eax

	v3 = engine_CreateNewSig(nSig);
	if ( !v3 )
	{
		v4 = GetLastError();
		ErrDlg(105, v4, "C:\\Diablo\\Direct\\ENGINE.CPP", 2058);
	}
	engine_add_cur_sig(v3, (DWORD)p);
}

TMemBlock *engine_CreateNewSig(int nSig)
{
	TMemBlock *result; // eax
	TMemBlock *v3; // edi

	result = sgpMemBlock;
	if ( sgpMemBlock )
	{
		while ( result->nSig != nSig )
		{
			result = (TMemBlock *)result->dwDataSize;
			if ( !result )
			{
				goto LABEL_4;
			}
		}
	}
	else
	{
LABEL_4:
		v3 = (TMemBlock *)SMemAlloc(20, "C:\\Diablo\\Direct\\ENGINE.CPP", 1997);
		memset(v3, 0, 0x14u);
		v3->nSig = nSig;
		v3->dwDataSize = (DWORD)sgpMemBlock;
		result = v3;
		sgpMemBlock = v3;
	}
	return result;
}

void engine_add_cur_sig(TMemBlock *pBlock, DWORD dwStart)
{
	unsigned int v2; // eax
	TMemBlock *i; // eax

	v2 = dwStart + pBlock->dwHeader;
	pBlock->dwHeader = v2;
	if ( pBlock->dwHeader2 < v2 )
	{
		pBlock->dwHeader2 = v2;
	}
	num_mem_sigs += dwStart;
	if ( cur_mem_sigs < num_mem_sigs )
	{
		cur_mem_sigs = num_mem_sigs;
		for ( i = sgpMemBlock; i; i = (TMemBlock *)i->dwDataSize )
		{
			i->field_10 = i->dwHeader;
		}
	}
}

void engine_check_sig_error(int nSig, int nLen)
{
	TMemBlock *v4; // eax
	const char *v5; // esi
	char *v6; // eax
	int a2; // [esp+8h] [ebp-8h]

	v4 = engine_CreateNewSig(nSig);
	if ( v4 )
	{
		v5 = engine_get_sig_error(v4, nLen);
	}
	else
	{
		v5 = "Bad signature unused: %s";
	}
	if ( v5 )
	{
		v6 = engine_swap_bytes(nSig, (int)&a2);
		app_fatal(v5, v6);
	}
}

#define _byteswap_ulong(x) ((x & 0xFF) << 24) | (((x >> 8) & 0xFF) << 16) | (((x >> 16) & 0xFF) << 8) | ((x >> 24) & 0xFF)
char *engine_swap_bytes(unsigned int nSig, int nSwap)
{
// TODO: figure out how to generate 'bswap' using C++ in VC6
/*
	__asm {
		mov		eax, nSig
		bswap	eax
		mov		nSig, eax
	}
*/
	*(_BYTE *)(nSwap + 4) = '\0';
	*(_DWORD *)nSwap = _byteswap_ulong(nSig);
	return (char *)nSwap;
}

const char *engine_get_sig_error(TMemBlock *pBlock, int nLen)
{
	unsigned int v2; // eax
	unsigned int v3; // esi
	bool v4; // cf
	const char *result; // eax
	DWORD v6; // eax

	v2 = pBlock->dwHeader;
	v3 = pBlock->dwHeader - nLen;
	pBlock->dwHeader = v3;
	v4 = v2 < v3;
	result = "memory block signature underflow: %s";
	if ( !v4 )
	{
		v6 = num_mem_sigs;
		num_mem_sigs -= nLen;
		result = v6 < num_mem_sigs ? "memory free underflow" : NULL;
	}
	return result;
}

unsigned char *DiabloAllocPtr(int dwBytes)
{
	TMemBlock *v6; // ebx
	TMemBlock *v7; // eax
	TMemBlock *v8; // eax
	DWORD *v9; // ecx
	DWORD v10; // eax
	int nSig = 'TEST';
	int nLine = __LINE__;
	char *pszFile = __FILE__;
	sgMemCrit.Enter();
	v6 = (TMemBlock *)SMemAlloc(dwBytes + 24, pszFile, nLine);
	if ( v6 )
	{
		v7 = engine_CreateNewSig(nSig);
		if ( v7 )
		{
			engine_add_cur_sig(v7, dwBytes);
			v6->nSig = nSig;
			v8 = v6;
			v6 = (TMemBlock *)((char *)v6 + 16);
			v8->dwDataSize = dwBytes;
			v8->dwHeader = 0x497208AB;
			v9 = (DWORD *)((char *)&v6->dwDataSize + dwBytes);
			v8->dwHeader2 = 0x127834DC;
			*v9 = 0x23481A9;
			v9[1] = 0xFCB87147;
		}
		else
		{
			SMemFree(v6, "C:\\Diablo\\Direct\\ENGINE.CPP", 2126);
			v6 = 0;
		}
	}
	sgMemCrit.Leave();
	if ( !v6 )
	{
		v10 = GetLastError();
		ErrDlg(105, v10, pszFile, nLine);
	}
	return (BYTE *)v6;
}

void mem_free_dbg(void *p2)
{
	const char *pszErr; // esi
	TMemBlock *pBlk; // edi
	int v6; // ebx
	DWORD *pFooter; // eax
	TMemBlock *v8; // eax
	char *v9; // eax
	int nLine = __LINE__;
	char *pszFile = __FILE__;
	BYTE *p = (BYTE *)p2;
	if ( p )
	{
		pszErr = 0;
		pBlk = CONTAINING_RECORD(p, TMemBlock, field_10); /* p - 16 */
		sgMemCrit.Enter();
		v6 = pBlk->nSig;
		if ( pBlk->dwHeader != 0x497208AB || pBlk->dwHeader2 != 0x127834DC )
		{
			pszErr = "Memory block header corruption: %s";
		}
		if ( !pszErr )
		{
			pFooter = (DWORD *)&p[pBlk->dwDataSize];
			if ( *pFooter != 0x23481A9 || pFooter[1] != 0xFCB87147 )
			{
				pszErr = "Memory block footer corruption: %s";
			}
			if ( !pszErr )
			{
				pszErr = "Attempt to free memory with unknown signature %s";
				v8 = engine_CreateNewSig(pBlk->nSig);
				if ( v8 )
				{
					pszErr = engine_get_sig_error(v8, pBlk->dwDataSize);
				}
			}
		}
		SMemFree(p - 16, pszFile, nLine);
		sgMemCrit.Leave();
		if ( pszErr )
		{
			v9 = engine_swap_bytes(v6, (int)&nLine);
			app_fatal(pszErr, v9);
		}
	}
}