struct TMemRecord {
	TMemRecord *pNext;
	DWORD dwID;
	DWORD size1;
	DWORD size2;
	DWORD size3;
};

struct TMemHeader {
	DWORD dwSize;
	DWORD dwID;
	DWORD dwLo;
	DWORD dwHi;
};

struct TMemFooter {
	DWORD dwLo;
	DWORD dwHi;
};

TMemRecord *sgpMemRecord;
CRITICAL_SECTION sgMemCrit;
DWORD sgdwCurrAlloc;
DWORD sgdwMaxAlloc;


void FreeMemRecords(BOOL show_cursor)
{
	TMemRecord *p;

	sgMemCrit.Enter();

	while(sgpMemRecord != NULL) {
		p = p->pNext;
		SMemFree(sgpMemRecord, "C:\\Diablo\\Direct\\ENGINE.CPP", 1970);
		sgpMemRecord = p;
	}

	sgMemCrit.Leave();
}

static TMemRecord *GetMemRecord(DWORD dwID)
{
	TMemRecord *p;

	for(p = sgpMemRecord; p != NULL; p = p->Next) {
		if(p->dwID == dwID) {
			return p;
		}
	}

	p = (TMemRecord *)SMemAlloc(sizeof(*p), "C:\\Diablo\\Direct\\ENGINE.CPP", 1997);
	memset(p, 0, sizeof(*p));
	p->dwID = dwID;
	p->pNext = sgpMemRecord;
	sgpMemRecord = p;

	return p;
}

static void UpdateMemUsed(TMemRecord *pBlock, DWORD dwLen)
{
	TMemRecord *p;

	pBlock->size1 += dwLen;
	if(pBlock->size2 < pBlock->size1) {
		pBlock->size2 = pBlock->size1;
	}

	sgdwCurrAlloc += dwLen;
	if(sgdwMaxAlloc < sgdwCurrAlloc) {
		sgdwMaxAlloc = sgdwCurrAlloc;
		for(p = sgpMemRecord; p != NULL; p = p->pNext) {
			p->size3 = p->size1;
		}
	}
}

void AddMemRecord(DWORD dwID, DWORD dwLen)
{
	TMemRecord *p;

	p = GetMemRecord(dwID);
	if(p == NULL) {
		ErrDlg(105, GetLastError(), "C:\\Diablo\\Direct\\ENGINE.CPP", 2058);
	}
	UpdateMemUsed(p, dwLen);
}

static char *SwapSignature(DWORD dwID, char *pszName)
{
#ifdef USE_ASM
	__asm {
		mov		eax, dwID
		bswap	eax
		mov		dwID, eax
	}
	((DWORD *)pszName)[0] = dwID;
#else
	pszName[0] = (dwID >> 24) & 0xFF;
	pszName[1] = (dwID >> 16) & 0xFF;
	pszName[2] = (dwID >> 8) & 0xFF;
	pszName[3] = dwID & 0xFF;
#endif
	pszName[4] = '\0';

	return pszName;
}

static const char *CheckUnderflow(TMemRecord *pBlock, DWORD dwSize)
{
	DWORD dwTemp;

	dwTemp = pBlock->size1;
	pBlock->size1 -= dwSize;
	if(dwTemp < pBlock->size1) {
		return "memory block signature underflow: %s";
	}

	dwTemp = sgdwCurrAlloc;
	sgdwCurrAlloc -= dwSize;
	if(dwTemp < sgdwCurrAlloc) {
		return "memory free underflow";
	}

	return NULL;
}

void CheckMemRecord(DWORD dwID, DWORD dwSize)
{
	TMemRecord *p;
	const char *pszErr;

	p = GetMemRecord(dwID);
	if(p != NULL) {
		pszErr = CheckUnderflow(p, dwSize);
	} else {
		pszErr = "Bad signature unused: %s";
	}

	if(pszErr != NULL) {
		char szName[5];
		app_fatal(pszErr, SwapSignature(dwID, szName));
	}
}

BYTE *DiabloAllocPtr(DWORD dwBytes, DWORD dwID, int nLine, const char *pszFile)
{
	BYTE *p;
	TMemRecord *pRecord;
	TMemHeader *pHeader;
	TMemFooter *pFooter;

	sgMemCrit.Enter();

	p = (BYTE *)SMemAlloc(sizeof(*pHeader) + dwBytes + sizeof(*pFooter), pszFile, nLine);
	if(p != NULL) {
		pRecord = GetMemRecord(dwID);
		if(pRecord != NULL) {
			UpdateMemUsed(pRecord, dwBytes);
			pHeader = (TMemHeader *)p;
			p += sizeof(*pHeader);
			pFooter = (TMemFooter *)&p[dwBytes];
			pHeader->dwID = dwID;
			pHeader->dwSize = dwBytes;
			pHeader->dwLo = 0x497208AB;
			pHeader->dwHi = 0x127834DC;
			pFooter->dwLo = 0x023481A9;
			pFooter->dwHi = 0xFCB87147;
		} else {
			SMemFree(p, "C:\\Diablo\\Direct\\ENGINE.CPP", 2126);
			p = NULL;
		}
	}

	sgMemCrit.Leave();

	if(p == NULL) {
		ErrDlg(105, GetLastError(), pszFile, nLine);
	}

	return p;
}

void mem_free_dbg(BYTE *p, int nLine, const char *pszFile)
{
	DWORD dwID;
	const char *pszErr;
	TMemRecord *pRecord;
	TMemHeader *pHeader;
	TMemFooter *pFooter;

	if(p == NULL) {
		return;
	}

	sgMemCrit.Enter();

	pszErr = NULL;
	pHeader = (TMemHeader *)(p - sizeof(*pHeader));
	dwID = pHeader->dwID;

	if(pszErr == NULL) {
		if(pHeader->dwLo != 0x497208AB || pHeader->dwHi != 0x127834DC) {
			pszErr = "Memory block header corruption: %s";
		}
	}
	if(pszErr == NULL) {
		pFooter = (TMemFooter *)&p[pHeader->dwSize];
		if(pFooter->dwLo != 0x023481A9 || pFooter->dwHi != 0xFCB87147) {
			pszErr = "Memory block footer corruption: %s";
		}
	}
	if(pszErr == NULL) {
		pRecord = GetMemRecord(dwID);
		if(pRecord != NULL) {
			pszErr = CheckUnderflow(pRecord, pHeader->dwSize);
		} else {
			pszErr = "Attempt to free memory with unknown signature %s";
		}
	}

	SMemFree(pHeader, pszFile, nLine);
	sgMemCrit.Leave();

	if(pszErr != NULL) {
		char szName[5];
		app_fatal(pszErr, SwapSignature(dwID, szName));
	}
}
