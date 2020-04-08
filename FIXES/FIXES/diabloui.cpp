enum ui_interface_mode
{
	WM_UIFADE = 0x7E8,
	WM_UISELLIST = 0xBD0,
	WM_UISELCLASS = 0xBD1,
	WM_UIENTNAME = 0xBD2,
	WM_UISELLOAD = 0xBD3,
	WM_UISELDIFF = 0xBD4,
	WM_UILOADGAME = 0xBD5,
	WM_UINEWGAME = 0xBD6,
	WM_UIDELHERO = 0xBD7
};

// ref: 0x1000BC46
LRESULT CALLBACK SelHero_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch ( uMsg )
	{
	case WM_DESTROY:
		SelHero_DeleteAndFree(hWnd);
		break;
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		SendMessage(SDrawGetFrameWindow(NULL), uMsg, wParam, lParam);
		break;
	case WM_INITDIALOG:
		SelHero_LoadHeroGFX(hWnd);
		PostMessage(hWnd, WM_UIFADE, 0, 0);
		return 0;
	case WM_UIFADE:
		if ( !Fade_CheckRange5() )
			Fade_SetFadeTimer((int)hWnd);
		return 0;
	case WM_UISELLIST:
		SelHero_DoHeroSelList(hWnd);
		return 0;
	case WM_UISELCLASS:
		SelHero_DoHeroSelClass(hWnd);
		return 0;
	case WM_UIENTNAME:
		SelHero_DoEnterName(hWnd);
		return 0;
	case WM_UISELLOAD:
		SelHero_DoSelLoad(hWnd);
		return 0;
	case WM_UISELDIFF:
		SelHero_DoSelDiff(hWnd);
		return 0;
	case WM_UILOADGAME:
		if ( selhero_is_good == 1 )
		{
			SelHero_DoHeroEndFade(hWnd, SELHERO_CONNECT);
		}
		else
		{
			SelHero_DoHeroEndFade(hWnd, SELHERO_CONTINUE);
		}
		return 0;
	case WM_UINEWGAME:
		strcpy(selhero_heronamestr, heroinfo_create.name);
		if ( selhero_is_good == 1 )
		{
			SelHero_DoHeroEndFade(hWnd, SELHERO_CONNECT);
		}
		else
		{
			selhero_difficulty = 0;
			SelHero_DoHeroEndFade(hWnd, SELHERO_NEW_DUNGEON);
		}
		return 0;
	case WM_UIDELHERO:
		SelHero_DoStuffWithStrings(hWnd);
		return 0;
	}

	return (LRESULT)SDlgDefDialogProc(hWnd, uMsg, (HDC)wParam, (HWND)lParam);
}