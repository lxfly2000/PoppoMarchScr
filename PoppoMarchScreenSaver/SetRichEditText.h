#include <Windows.h>

void SetRichEditText(HWND h, LPCWSTR text);
INT_PTR CALLBACK OnRichEditClickMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
