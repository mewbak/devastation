BOOL CALLBACK FuncDlg(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg) {
	case WM_INITDIALOG:
		TextDlg(hDlg, lParam);
		return TRUE;
	case WM_COMMAND:
		if(wParam == 1) {
			EndDialog(hDlg, 1);
		} else if(wParam == 2) {
			EndDialog(hDlg, 0);
		}
		return TRUE;
	}

	return FALSE;
}