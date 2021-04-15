#include "SetRichEditText.h"
#include <Windows.h>
#include <Richedit.h>
#include <regex>

std::wstring to_unix_str(std::wstring str)
{
	for (size_t i = 0; i < str.size();)
	{
		if (str[i] == '\r')
			str.erase(str.begin() + i);
		else
			i++;
	}
	return str;
}

void SetRichEditText(HWND h, LPWSTR text)
{
	std::wstring str = to_unix_str(text);
	std::wregex r(TEXT("https?://[^\\n ]+"));
	std::wsmatch m;
	SetWindowText(h, text);
	SendMessage(h, EM_SETEVENTMASK, NULL, ENM_LINK);
	size_t prelen = 0;
	while (std::regex_search(str, m, r, std::regex_constants::match_any))
	{
		CHARRANGE cr;
		cr.cpMin = prelen + m.position(0);
		cr.cpMax = prelen + m.position(0) + m.length(0);
		SendMessage(h, EM_EXSETSEL, NULL, (LPARAM)&cr);
		CHARFORMAT cf;
		cf.cbSize = sizeof(cf);
		cf.dwMask = CFM_LINK;
		cf.dwEffects = CFE_LINK;
		cf.crTextColor = RGB(0, 0, 255);
		SendMessage(h, EM_SETCHARFORMAT, SCF_SELECTION, (WPARAM)&cf);
		str = str.substr(m.position(0) + m.length(0));
		prelen += m.position(0) + m.length(0);
	}
}

INT_PTR CALLBACK OnRichEditClickMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NOTIFY && ((LPNMHDR)lParam)->code == EN_LINK)
	{
		ENLINK *el = (ENLINK*)lParam;
		if (el->msg == WM_LBUTTONUP)
		{
			HWND hRE = GetDlgItem(hwnd, ((LPNMHDR)lParam)->idFrom);
			int len = GetWindowTextLength(hRE);
			TCHAR* text = new TCHAR[len + 1];
			GetWindowText(hRE, text, len);
			text[len] = 0;
			std::wstring ut = to_unix_str(text);
			ut = ut.substr(el->chrg.cpMin, el->chrg.cpMax - el->chrg.cpMin);
			delete text;
			return (int)ShellExecute(hwnd, TEXT("open"), ut.c_str(), NULL, NULL, SW_NORMAL);
		}
	}
	return 0;
}
