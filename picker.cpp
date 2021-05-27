#include <windows.h>
#include <cstdio>

typedef WINAPI COLORREF (*GETPIXEL)(HDC, int, int);

POINT getCursorPos() {
    POINT pos;
    GetCursorPos(&pos);
    return pos;
}

RGBTRIPLE colorRefToRGB(COLORREF ref) {
    return RGBTRIPLE{GetBValue(ref), GetGValue(ref), GetRValue(ref)};
}

RGBTRIPLE getColorAt(int x, int y) {
    HINSTANCE hGDI = LoadLibrary("gdi32.dll");
    auto getPixel = (GETPIXEL) GetProcAddress(hGDI, "GetPixel");

    auto hdc = GetDC(nullptr);
    auto colorref = (*getPixel)(hdc, x, y);

    FreeLibrary(hGDI);
    return colorRefToRGB(colorref);
}

