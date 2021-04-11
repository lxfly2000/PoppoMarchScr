#include "SettingsDialog.h"
#include "Config.h"
#include "../resource.h"

#include <windowsx.h>

static WNDPROC stProc;

INT_PTR CALLBACK LIstProc(HWND hwnd, UINT msg, WPARAM w, LPARAM l)
{
	if (msg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hwnd, &ps);
		HDC hMemDC = CreateCompatibleDC(hDC);
		HBITMAP hBmp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BANNER));
		BITMAP bmp;
		GetObject(hBmp, sizeof(bmp), &bmp);
		SelectObject(hMemDC, hBmp);
		SetStretchBltMode(hDC, HALFTONE);
		RECT r;
		GetClientRect(hwnd, &r);
		StretchBlt(hDC, 0, 0, r.right, r.bottom, hMemDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
		DeleteObject(hMemDC);
		EndPaint(hwnd, &ps);
		return 0;
	}
	return CallWindowProc(stProc, hwnd, msg, w, l);
}

void OnInitAboutDialog(HWND hwnd)
{
	TCHAR t[256];
	LoadString(NULL, IDS_STRING_ABOUT, t, ARRAYSIZE(t));
	Edit_SetText(GetDlgItem(hwnd, IDC_EDIT_MESSAGE), t);
	HWND hStatic = GetDlgItem(hwnd, IDC_STATIC_BITMAP);
	HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_MESSAGE);
	HBITMAP hBmp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BANNER));
	BITMAP bmp;
	GetObject(hBmp, sizeof(bmp), &bmp);
	RECT rs,re;
	rs.right = bmp.bmWidth;
	rs.bottom = bmp.bmHeight;
	GetClientRect(hEdit, &re);
	stProc = (WNDPROC)GetWindowLongPtr(hStatic, GWLP_WNDPROC);
	SetWindowLongPtr(hStatic, GWLP_WNDPROC, (LONG_PTR)LIstProc);
	SetWindowPos(hStatic, NULL, NULL, NULL, re.bottom*rs.right/rs.bottom, re.bottom, SWP_NOZORDER | SWP_NOMOVE);
}

INT_PTR CALLBACK AboutDialogCallback(HWND hwnd, UINT msg, WPARAM w, LPARAM l)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		OnInitAboutDialog(hwnd);
		break;
	case WM_COMMAND:
		switch (LOWORD(w))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	}
	return 0;
}

void OnInitSettingsDialog(HWND hwnd)
{
	if (!InitConfigFile())
		return;
	HWND hCombo = GetDlgItem(hwnd, IDC_COMBO_ANIM_SPEED);
	ComboBox_AddString(hCombo, TEXT("Slow"));
	ComboBox_AddString(hCombo, TEXT("Normal"));
	ComboBox_AddString(hCombo, TEXT("Fast"));
	ComboBox_AddString(hCombo, TEXT("Very Fast"));
	ComboBox_SetCurSel(hCombo, ReadInt(KEY_ANIMATION_SPEED));
	CheckDlgButton(hwnd, IDC_CHECK_SHOW_FPS, ReadInt(KEY_SHOW_FPS) ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(hwnd, IDC_CHECK_PLAY_BGM, ReadInt(KEY_PLAY_BGM) ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(hwnd, IDC_CHECK_CLOSE_BY_CLICK, ReadInt(KEY_CLOSE_BY_CLICKING, 1) ? BST_CHECKED : BST_UNCHECKED);
}

INT_PTR OnSettingsOk(HWND hwnd)
{
	WriteInt(KEY_ANIMATION_SPEED, ComboBox_GetCurSel(GetDlgItem(hwnd, IDC_COMBO_ANIM_SPEED)));
	WriteInt(KEY_SHOW_FPS, IsDlgButtonChecked(hwnd, IDC_CHECK_SHOW_FPS) == BST_CHECKED ? 1 : 0);
	WriteInt(KEY_PLAY_BGM, IsDlgButtonChecked(hwnd, IDC_CHECK_PLAY_BGM) == BST_CHECKED ? 1 : 0);
	WriteInt(KEY_CLOSE_BY_CLICKING, IsDlgButtonChecked(hwnd, IDC_CHECK_CLOSE_BY_CLICK) == BST_CHECKED ? 1 : 0);
	return EndDialog(hwnd, 1);
}

INT_PTR CALLBACK SettingsDialogCallback(HWND hwnd, UINT msg, WPARAM w, LPARAM l)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		OnInitSettingsDialog(hwnd);
		break;
	case WM_COMMAND:
		switch (LOWORD(w))
		{
		case IDOK:
			return OnSettingsOk(hwnd);
		case IDCANCEL:
			return EndDialog(hwnd, 0);
		case IDC_BUTTON_ABOUT:
			return DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ABOUT), hwnd, AboutDialogCallback);
		}
		break;
	}
	return 0;
}

INT_PTR SettingsDialog(HINSTANCE hInst,HWND hWndParent)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_SETTINGS), hWndParent, SettingsDialogCallback);
}
