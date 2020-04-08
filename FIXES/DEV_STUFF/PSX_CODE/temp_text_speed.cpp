void CalcTextSpeed__FPCc(char *Name)
{
	uint SfxFrames;
	int NoLines;
	int TextHeight;
	char SpeechName[16];
	char *ptr;
	int cw;
	
	ptr = qtextptr;
	NoLines = 0;
	cw = 0;
	if (FileSYS != 2) {
		qtbodge = 0;
		qtextSpd = 0x100;
		scrolltexty = qtexty << 8;
		return;
	}
	sprintf(SpeechName,"%s.VAG",Name);
	SfxFrames = BL_FileLength__FPcc(SpeechName,0);
	SfxFrames = SfxFrames / 0x69;
	while (*ptr != '\0') {
		cw += GetCharWidth(MediumFont,*ptr);
		if (cw >= 280 || *ptr == '\n') {
			cw = 0;
			NoLines++;
		}
		ptr++;
	}
	NoLines++;

	TextHeight = 10; // 11, 14 with space
	qtbodge = 0;
	qtextSpd = NoLines + 0xE7;
	scrolltexty = qtexty << 8;
	return;
}


void UndefinedFunction_8004da40(void)
{
	uint uVar1;
	int iVar2;
	int iVar3;
	undefined2 in_stack_00000028;
	undefined2 uStack0000002a;
	undefined2 in_stack_0000002c;
	undefined2 uStack0000002e;
	
	ptr = qtextptr;
	sprintf(SpeechName,"%s.VAG",Name);
	SfxFrames = BL_FileLength__FPcc(SpeechName,0);
	if (SfxFrames != 0) {
		rect.x = 0;
		rect.y = 0;
		rect.w = 280;
		rect.h = -1;
		iVar2 = GetWrap__5CFontPcP4RECT(&MediumFont, ptr, &rect);
		iVar3 = textadj;
		if (FeFlag != '\0') {
			iVar3 = fetextadj;
		}
		qtbodge = 0;
		qtextSpd = (((iVar2 * 0xf + 0xd7) - iVar3) * 0x10000) / (SfxFrames / 0x69);
		scrolltexty = qtexty << 0x10;
		return;
	}
					/* WARNING: Subroutine does not return */
	DBG_Error(0,"source/MINITEXT.cpp",0xaf);
}

	currTime = VID_GetTick__Fv();
	scrolltexty -= qtextSpd * (currTime - sgLastScroll);
	qtexty = scrolltexty >> 8;
	sgLastScroll = currTime;
	if (qtexty < 0x10) {
		scrolltexty += 0xf00;
		qtexty = scrolltexty >> 8;
		qtextptr = pnl;
		if (*pnl == '|') {
			qtextflag = 0;
		}
	}
