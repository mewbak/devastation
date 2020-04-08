void TextDlg(HWND hDlg, char *text)
{
	center_window(hDlg);

	if(text != NULL) {
		SetDlgItemText(hDlg, 1000, text);
	}
}