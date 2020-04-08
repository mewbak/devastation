void *__stdcall SMemAlloc(DWORD size, char *file, int line)
{
	return malloc(size);
}

BOOL __stdcall SMemFree(void *p, char *file, int line)
{
	free(p);
	return TRUE;
}

void __cdecl app_fatal(const char *pszFmt, ...)
{
	va_list arglist; // [esp+8h] [ebp+8h]

	va_start(arglist, pszFmt);
	printf(pszFmt, arglist);
	exit(1);
}

void ErrDlg(int nResource, DWORD dwError, const char *pszFile, int nLineNo)
{
	printf("%d", dwError);
	exit(1);
}

struct TMemBlock {
	TMemBlock *pNext;
	int nSig;
	DWORD size1;
	DWORD size2;
	DWORD size3;
};

struct TMemHeader {
	DWORD dwSize;
	int nSig;
	DWORD dwHead1;
	DWORD dwHead2;
};

TMemBlock *sgpMemBlock;
CRITICAL_SECTION sgMemCrit;
DWORD num_mem_sigs; // current mem used
DWORD cur_mem_sigs; // maximum mem used

TMemBlock *engine_CreateNewSig(int nSig);
void engine_add_cur_sig(TMemBlock *pBlock, DWORD dwLen);
char *engine_swap_bytes(unsigned int nSig, char *nSwap);
const char *engine_get_sig_error(TMemBlock *pBlock, DWORD nLen);

// bin exact - global [init_cleanup]
void engine_debug_trap(BOOL show_cursor) // FreeMemoryBlocks
{
	TMemBlock *p, *old;

	EnterCriticalSection(&sgMemCrit);

	p = sgpMemBlock;
	while ( p )
	{
		old = p->pNext;
		SMemFree(p, "C:\\Diablo\\Direct\\ENGINE.CPP", 1970);
		p = old;
	}

	LeaveCriticalSection(&sgMemCrit);
}

// bin exact - global [sound_file_load]
void engine_add_sound_sig(int nSig, DWORD dwLen) // AddMemoryBlock
{
	TMemBlock *v3; // eax

	v3 = engine_CreateNewSig(nSig);
	if ( !v3 )
	{
		ErrDlg(105, GetLastError(), "C:\\Diablo\\Direct\\ENGINE.CPP", 2058);
	}
	engine_add_cur_sig(v3, dwLen);
}

// bin exact - static
TMemBlock *engine_CreateNewSig(int nSig) // GetMemoryBlock
{
	TMemBlock *result; // eax
	TMemBlock *v3; // edi

	result = sgpMemBlock;
	while ( result ) // for loop?
	{
		if ( result->nSig == nSig )
		{
			return result;
		}
		result = result->pNext;
	}

	v3 = (TMemBlock *)SMemAlloc(sizeof(*v3), "C:\\Diablo\\Direct\\ENGINE.CPP", 1997);
	memset(v3, 0, sizeof(*v3));
	v3->nSig = nSig;
	v3->pNext = sgpMemBlock;
	sgpMemBlock = v3;
	return sgpMemBlock;
}

// bin exact - static
void engine_add_cur_sig(TMemBlock *pBlock, DWORD dwLen) // SetBlockSize
{
	TMemBlock *i; // eax

	pBlock->size1 += dwLen;
	if ( pBlock->size2 < pBlock->size1 )
	{
		pBlock->size2 = pBlock->size1;
	}
	num_mem_sigs += dwLen;
	if ( cur_mem_sigs < num_mem_sigs )
	{
		cur_mem_sigs = num_mem_sigs;
		for ( i = sgpMemBlock; i != NULL; i = i->pNext )
		{
			i->size3 = i->size1;
		}
	}
}

// bin exact - global [sound_file_cleanup]
void engine_check_sig_error(int nSig, int nLen) // CheckBlockError
{
	TMemBlock *v4; // eax
	const char *v5; // esi
	char *v6; // eax
	char a2[5]; // [esp+8h] [ebp-8h]

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
		v6 = engine_swap_bytes(nSig, a2);
		app_fatal(v5, v6);
	}
}

// bin exact - static
char *engine_swap_bytes(unsigned int nSig, char *nSwap) // SwapSignature
{
	__asm {
		mov		eax, nSig
		bswap	eax
		mov		nSig, eax
	}
	*(DWORD *)nSwap = nSig;
	nSwap[4] = 0;

	return nSwap;
}

// bin exact needs to be static NO prototype - static
const char *engine_get_sig_error(TMemBlock *pBlock, DWORD nLen) // CheckUnderflow
{
	DWORD v6; // eax

	v6 = pBlock->size1;
	pBlock->size1 -= nLen;
	if ( v6 < pBlock->size1 )
	{
		return "memory block signature underflow: %s";
	}
	v6 = num_mem_sigs;
	num_mem_sigs -= nLen;
	if ( v6 < num_mem_sigs )
	{
		return "memory free underflow";
	}
	return NULL;
}

BYTE *DiabloAllocPtr(DWORD dwBytes, int nSig, int nLine, char *pszFile)
{
	BYTE *p; // ebx
	TMemBlock *pBlk; // eax
	TMemHeader *pHead; // eax
	DWORD *pFoot; // ecx

	EnterCriticalSection(&sgMemCrit);
	p = (BYTE *)SMemAlloc(dwBytes + 24, pszFile, nLine);
	if ( p != NULL )
	{
		pBlk = engine_CreateNewSig(nSig);
		if ( pBlk != NULL )
		{
			engine_add_cur_sig(pBlk, dwBytes);
			pHead = (TMemHeader *)p;
			p += 16;
			pFoot = (DWORD *)&p[dwBytes];
			pHead->nSig = nSig;
			pHead->dwSize = dwBytes;
			pHead->dwHead1 = 0x497208AB;
			pHead->dwHead2 = 0x127834DC;
			pFoot[0] = 0x23481A9;
			pFoot[1] = 0xFCB87147;
		}
		else
		{
			SMemFree(p, "C:\\Diablo\\Direct\\ENGINE.CPP", 2126);
			p = NULL;
		}
	}
	LeaveCriticalSection(&sgMemCrit);
	if ( p == NULL )
	{
		ErrDlg(105, GetLastError(), pszFile, nLine);
	}
	return p;
}

// bin exact
void mem_free_dbg(BYTE *p, int nLine, char *pszFile)
{
	const char *pszErr; // esi
	TMemHeader *pHead; // edi
	DWORD *pFooter; // eax
	TMemBlock *pBlk; // eax
	int nSig;

	if ( p == NULL )
	{
		return;
	}

	EnterCriticalSection(&sgMemCrit);

	pszErr = NULL;
	pHead = (TMemHeader *)(p - 16);
	nSig = pHead->nSig;

	if ( pszErr == NULL )
	{
		if ( pHead->dwHead1 != 0x497208AB || pHead->dwHead2 != 0x127834DC )
		{
			pszErr = "Memory block header corruption: %s";
		}
	}
	if ( pszErr == NULL )
	{
		pFooter = (DWORD *)&p[pHead->dwSize]; // try p +=
		if ( pFooter[0] != 0x23481A9 || pFooter[1] != 0xFCB87147 )
		{
			pszErr = "Memory block footer corruption: %s";
		}
	}
	if ( pszErr == NULL )
	{
		pBlk = engine_CreateNewSig(nSig);
		if ( pBlk != NULL )
		{
			pszErr = engine_get_sig_error(pBlk, pHead->dwSize);
		}
		else
		{
			pszErr = "Attempt to free memory with unknown signature %s";
		}
	}

	SMemFree(pHead, pszFile, nLine);
	LeaveCriticalSection(&sgMemCrit);

	if ( pszErr != NULL )
	{
		char a2[5]; // [esp+10h] [ebp-8h]
		app_fatal(pszErr, engine_swap_bytes(nSig, a2));
	}
}

void fuckstuff()
{
	engine_debug_trap(0);
}







