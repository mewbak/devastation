scrollrt
		GetClientRect( ghMainWnd, &SrcRect );
		ClientToScreen( ghMainWnd, (POINT*)&SrcRect );
		ClientToScreen( ghMainWnd, (POINT*)&SrcRect+1 );
		nSrcOff = SCREENXY(dwX, dwY);
		nDstOff = (SrcRect.left + dwX) + (SrcRect.top + dwY) * DDS_desc.lPitch;
		
init
	DWORD dwWindowWidth   = SCREEN_WIDTH  + GetSystemMetrics( SM_CXFIXEDFRAME ) * 2;
	DWORD dwWindowHeight  = SCREEN_HEIGHT + GetSystemMetrics( SM_CYFIXEDFRAME ) * 2 + GetSystemMetrics( SM_CYCAPTION );
	RECT v15;
	GetClientRect(GetDesktopWindow(), &v15);
	int X = (v15.right - dwWindowWidth) >> 1;
	if ( X < 0 )
		X = 0;
	int Y = (v15.bottom - dwWindowHeight) >> 1;
	if ( Y < 0 )
		Y = 0;
	hWnd = CreateWindowEx(
			0,
			"DIABLO",
			"DIABLO",
			WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
			X,
			Y,
			dwWindowWidth,
			dwWindowHeight,
			NULL,
			NULL,
			ghInst,
			NULL);