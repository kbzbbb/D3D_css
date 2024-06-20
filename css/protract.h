#pragma once
#include "data.h"

LRESULT WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);

bool initialize_D3D();

void create_window(HWND handle, Draw protract);

void Information_circulate();

void Draw_line(D3DCOLOR Color, float X1, float Y1, float X2, float Y2, float Width);

void Draw_writing(float X, float Y, const char* Str, D3DCOLOR Color);

void Draw_frame(float X, float Y, float W, float H, float Width, D3DCOLOR Color);

void protract_Begin();

void protract_end();
