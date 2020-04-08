LRESULT __fastcall PROC3_GM_Game(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
else
{
if ( Msg == WM_MOUSEMOVE )
{
	MouseX = lParam - dword_5030CC;
	MouseY = (lParam >> 16) - dword_5030D0;
	return 0;
}
if ( Msg == WM_KEYDOWN )
{
	if ( plr[myplr]._pInvincible && deathflag )
	{
		if ( wParam == VK_UP )
			gmenu_up();
		if ( wParam == VK_DOWN )
			gmenu_down();
		if ( wParam == VK_RETURN )
			select_menu_option();
		return 0;
	}
	if ( wParam == VK_ESCAPE )
	{
		if ( helpflag )
		{
			helpflag = 0;
		}
		else if ( qtextflag )
		{
			qtextflag = 0;
			if ( !leveltype )
				sfx_stop();
		}
		else if ( stextflag )
		{
			STextESC();
		}
		else if ( questlog )
		{
			QuestlogOff();
		}
		else if ( msgflag )
		{
			msgdelay = 0;
		}
		else if ( diablo109_dword_634480 )
		{
			diablo109_dword_634480 = 0;
		}
		else
		{
			diablo109_dword_634480 = 1;
			menu_option_selected = 0;
		}
	}
	if ( wParam == VK_PAUSE )
	{
		if ( currlevel )
		{
			if ( PauseMode )
				PauseMode = 0;
			else
				PauseMode = 2;
		}
		else
		{
			InitDiabloMsg(6);
		}
	}
	if ( wParam == VK_F1 )
	{
		if ( !helpflag )
		{
			if ( stextflag )
			{
				ClearPanel();
				AddPanelString("No help available", 1);
				AddPanelString("while in stores", 1);
				result = 0;
			}
			else
			{
				invflag = 0;
				chrflag = 0;
				speed_flag = 0;
				spselflag = 0;
				if ( qtextflag && !leveltype )
				{
					qtextflag = 0;
					sfx_stop();
				}
				questlog = 0;
				automapflag = 0;
				msgdelay = 0;
				diablo109_dword_634480 = 0;
				DisplayHelp();
				result = 0;
			}
			return result;
		}
		helpflag = 0;
	}
	if ( wParam == VK_F5 && debug_mode_key_inverted_v )
		do_send_spell(myplr, 21, 0, 0, 0);
	if ( wParam == VK_F6 && debug_mode_key_inverted_v )
		do_send_spell(myplr, 21, 0, 5, 1);
	if ( wParam == VK_F7 && debug_mode_key_inverted_v )
		do_send_spell(myplr, 21, 0, 2, 5);
	if ( wParam == VK_F8 && debug_mode_key_inverted_v )
		do_send_spell(myplr, 21, 0, 3, 9);
	if ( wParam == VK_F9 )
	{
		DrawAndBlit();
		CaptureScreen();
		++quote_pcx_number;
	}
	if ( wParam == VK_F4 && (debug_mode_key_w || debug_mode_key_inverted_v) )
		debug_mode_key_f = debug_mode_key_f == 0;
	if ( wParam == VK_RETURN && plr[myplr].InvList[0]._itype != -1 && !diablo109_dword_634480 && !stextflag )
		do_send_spell(myplr, 19, 0, 1, 0);
	if ( wParam == VK_UP )
	{
		if ( diablo109_dword_634480 )
		{
			gmenu_up();
		}
		else if ( stextflag )
		{
			STextUp();
		}
		else if ( questlog )
		{
			QuestlogUp();
		}
		else if ( helpflag )
		{
			HelpScrollUp();
		}
		else if ( automapflag )
		{
			AutomapUp();
		}
	}
	if ( wParam == VK_DOWN )
	{
		if ( diablo109_dword_634480 )
		{
			gmenu_down();
		}
		else if ( stextflag )
		{
			STextDown();
		}
		else if ( questlog )
		{
			QuestlogDown();
		}
		else if ( helpflag )
		{
			HelpScrollDown();
		}
		else if ( automapflag )
		{
			AutomapDown();
		}
	}
	if ( wParam == VK_LEFT && automapflag )
		AutomapLeft();
	if ( wParam == VK_RIGHT && automapflag )
		AutomapRight();
	if ( wParam == VK_RETURN )
	{
		if ( diablo109_dword_634480 )
		{
			select_menu_option();
		}
		else if ( stextflag )
		{
			STextEnter();
		}
		else if ( questlog )
		{
			QuestlogEnter();
		}
	}
	if ( wParam == VK_TAB )
	{
		if ( currlevel )
		{
			if ( automapflag )
				automapflag = 0;
			else
				StartAutomap();
		}
		else
		{
			InitDiabloMsg(1);
		}
	}
	if ( wParam == VK_SPACE )
	{
		if ( !invflag && chrflag && MouseX < 480 )
			SetCursorPos(MouseX + 160, MouseY);
		if ( !chrflag && invflag && MouseX > 160 )
			SetCursorPos(MouseX - 160, MouseY);
		helpflag = 0;
		invflag = 0;
		chrflag = 0;
		speed_flag = 0;
		spselflag = 0;
		if ( qtextflag && !leveltype )
		{
			qtextflag = 0;
			sfx_stop();
		}
		questlog = 0;
		automapflag = 0;
		msgdelay = 0;
		diablo109_dword_634480 = 0;
		if ( pcurs != 1 && pcurs < 8 )
			SetCursor(1);
	}
	return 0;
}
if ( Msg != WM_CHAR )
	return DefWindowProcA(hWnda, Msga, wParam, lParam);
if ( plr[myplr]._pInvincible )
{
	result = 0;
}
else
{
	switch ( wParam )
	{
		case '*':
			if ( debug_mode_key_inverted_v )
				AddPlrExperience(
					myplr,
					plr[myplr]._pLevel,
					plr[myplr]._pNextExper - plr[myplr]._pExperience);
			result = 0;
			break;
		case '+':
		case '=':
			if ( automapflag )
				AutomapZoomIn();
			result = 0;
			break;
		case '-':
		case '_':
			if ( automapflag )
				AutomapZoomOut();
			result = 0;
			break;
		case '1':
			if ( speed_flag )
				SetSpeedSpell(0);
			else
				ToggleSpell(0);
			result = 0;
			break;
		case '2':
			if ( speed_flag )
				SetSpeedSpell(1);
			else
				ToggleSpell(1);
			result = 0;
			break;
		case '3':
			if ( speed_flag )
				SetSpeedSpell(2);
			else
				ToggleSpell(2);
			result = 0;
			break;
		case 'B':
		case 'b':
			if ( debug_mode_key_inverted_v )
				++plr[myplr]._pSplLvl[plr[myplr]._pTSpell];
			result = 0;
			break;
		case 'C':
		case 'c':
			if ( stextflag )
			{
				result = 0;
			}
			else
			{
				chrflag = chrflag == 0;
				if ( !chrflag || invflag )
				{
					if ( MouseX < 480 )
						SetCursorPos(MouseX + 160, MouseY);
				}
				else if ( MouseX > 160 )
				{
					SetCursorPos(MouseX - 160, MouseY);
				}
				result = 0;
			}
			break;
		case 'F':
		case 'f':
			if ( dbl_4BBFB8 < 1.0 )
			{
				dbl_4BBFB8 = dbl_4BBFB8 + 0.05;
				qword_4BBFC0 = *&dbl_4BBFB8;
				CopyPalette(system_palette, orig_palette);
				ApplyGamma(system_palette, 0, 256);
				lpDDPalette->lpVtbl->SetEntries(lpDDPalette, 0, 0, 256, system_palette);
			}
			result = 0;
			break;
		case 'G':
		case 'g':
			if ( dbl_4BBFB8 > 0.3 )
			{
				dbl_4BBFB8 = dbl_4BBFB8 - 0.05;
				qword_4BBFC0 = *&dbl_4BBFB8;
				CopyPalette(system_palette, orig_palette);
				ApplyGamma(system_palette, 0, 256);
				lpDDPalette->lpVtbl->SetEntries(lpDDPalette, 0, 0, 256, system_palette);
			}
			result = 0;
			break;
		case 'I':
		case 'i':
			if ( stextflag )
			{
				result = 0;
			}
			else
			{
				invflag = invflag == 0;
				if ( !invflag || chrflag )
				{
					if ( MouseX > 160 )
						SetCursorPos(MouseX - 160, MouseY);
				}
				else if ( MouseX < 480 )
				{
					SetCursorPos(MouseX + 160, MouseY);
				}
				result = 0;
			}
			break;
		case 'L':
		case 'l':
			if ( debug_mode_key_inverted_v )
				ToggleLighting2();
			result = 0;
			break;
		case 'M':
		case 'm':
			if ( debug_mode_key_inverted_v )
			{
				sprintf(tempstr, "Invincible = %i", plr[myplr]._pInvincible);
				AddPanelString(tempstr, 0);
			}
			result = 0;
			break;
		case 'P':
		case 'p':
			if ( currlevel )
			{
				if ( debug_mode_key_w )
				{
					PauseMode = 1;
				}
				else if ( PauseMode )
				{
					PauseMode = 0;
				}
				else
				{
					PauseMode = 2;
				}
			}
			else
			{
				InitDiabloMsg(6);
			}
			result = 0;
			break;
		case 'Q':
		case 'q':
			if ( diablo109_dword_634480 )
			{
				result = 0;
			}
			else if ( stextflag )
			{
				result = 0;
			}
			else
			{
				if ( questlog )
					questlog = 0;
				else
					StartQuestlog();
				result = 0;
			}
			break;
		case 'R':
		case 'r':
			sprintf(tempstr, "seed = %i", plr[myplr]._pSeedTbl[currlevel]);
			AddPanelString(tempstr, 0);
			result = 0;
			break;
		case 'S':
		case 's':
			if ( diablo109_dword_634480 )
			{
				result = 0;
			}
			else if ( stextflag )
			{
				result = 0;
			}
			else
			{
				if ( speed_flag )
					speed_flag = 0;
				else
					DoSpeedBook();
				result = 0;
			}
			break;
		case 'T':
		case 't':
			if ( debug_mode_key_inverted_v )
			{
				sprintf(tempstr, "X = %i  Y = %i", plr[myplr].WorldX, plr[myplr].WorldY);
				AddPanelString(tempstr, 0);
			}
			result = 0;
			break;
		case 'V':
		case 'v':
			if ( demo_mode )
				strcpy(tempstr, "Pre-release Demo");
			else
				strcpy(tempstr, "V1.0");
			AddPanelString(tempstr, 1);
			result = 0;
			break;
		case 'Z':
		case 'z':
			zoomflag = zoomflag == 0;
			result = 0;
			break;
		case 'd':
			if ( debug_mode_key_w )
			{
				sprintf(tempstr, "TransVal = %i", dung_map[plr[myplr].WorldX][plr[myplr].WorldY]);
				AddPanelString(tempstr, 0);
			}
			result = 0;
			break;
		case 'e':
			if ( debug_mode_key_w )
			{
				sprintf(tempstr, "EFlag = %i", plr[myplr]._peflag);
				AddPanelString(tempstr, 0);
			}
			result = 0;
			break;
		default:
			return DefWindowProcA(hWnda, Msga, wParam, lParam);
	}
}
}

}