void drawUpperScreen(BYTE *pBuff)
{
	int nType;
	DWORD *pMask;

	nType = 0; //16 lower
	pMask = NULL;
	if(cel_transparency_active) {
		pc = block_lvid[level_piece_id];
		if(arch_draw_type == 0) {
			nType = 32; //48 lower
		} else if(arch_draw_type == 1 && (pc == 1 || pc == 3)) {
			nType = 64; //80 lower
			pMask = &LeftMask[31];
		} else if(arch_draw_type == 2 && (pc == 2 || pc == 3)) {
			nType = 64; //80 lower
			pMask = &RightMask[31];
		}
	}

	gpCelFrame = SpeedFrameTbl;

	if(light_table_index == 0) {
		if(level_cel_block & 0x8000) {
			level_cel_block = gpCelFrame[level_cel_block & 0xFFF][0] + (level_cel_block & 0xF000);
		}
		pFrameTable = SwapEndianL32(&pDungeonCels[level_cel_block & 0xFFF]);
		function = RenderJmp_Solid[(level_cel_block >> 12) + nType + 8];
		CallFuncProc(pBuff, &pDungeonCels[pFrameTable], NULL, pMask);
	} else if(light_table_index == lightmax) {
		if(level_cel_block & 0x8000) {
			level_cel_block = gpCelFrame[level_cel_block & 0xFFF][0] + (level_cel_block & 0xF000);
		}
		pFrameTable = SwapEndianL32(&pDungeonCels[level_cel_block & 0xFFF]);
		function = RenderJmp_Black[(level_cel_block >> 12) + nType];
		CallFuncProc(pBuff, &pDungeonCels[pFrameTable], NULL, pMask);
	} else if(!(level_cel_block & 0x8000)) {
		pFrameTable = SwapEndianL32(&pDungeonCels[level_cel_block & 0xFFF]);
		function = RenderJmp_Light[(level_cel_block >> 12) + nType];
		CallFuncProc(pBuff, &pDungeonCels[pFrameTable], &pLightTbl[light_table_index << 8], pMask);
	} else {
		function = RenderJmp_Solid[(level_cel_block >> 12) + nType];
		CallFuncProc(pBuff, &pSpeedCels[gpCelFrame[level_cel_block & 0xFFF][light_table_index]], NULL, pMask);
	}
}
