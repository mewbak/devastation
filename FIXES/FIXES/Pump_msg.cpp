void PumpUiMessage2(void (__stdcall *a1)(int))
{
	MSG msg;
	DWORD dwTicks, dwTicks1, dwTicks2;

	dwTicks1 = GetTickCount();
	int msecs = 0;
	int v7 = 0;
	//dwTicks = GetTickCount() + 1000 / 20;
	while ( gbRunGame )
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if(msg.message != WM_QUIT) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwTicks2 = GetTickCount() - dwTicks1;
			dwTicks1 = GetTickCount();
			if ( dwTicks2 > 1000 )
				dwTicks2 = 1000;
			msecs -= dwTicks2;
			if ( msecs <= 0 )
			{
				msecs += 1000 / 25;
				if ( msecs < -1000 )
					msecs = 0;
                if ( a1 )
                {
                    a1(v7++);
                }
				//interface_pump_title_message();
			}
			if ( (DWORD)msecs > 20 )
				msecs = 20;
			// if ( gbActive )
				// msecs = 0;
			Sleep(msecs);
		}
	}
}