#pragma once
#include "Precompilation.h"
#include <vector>

class Figure_Data {
public:
	float life;
	int camp;
	float x;
	float y;
	float z;
};

extern  MARGINS Margin;
extern  LPDIRECT3D9              g_pD3D;
extern  LPDIRECT3DDEVICE9        g_pd3dDevice;
extern  D3DPRESENT_PARAMETERS    g_d3dpp;
extern  ID3DXLine* pLine;
extern  ID3DXFont* Font;

extern  HWND auxiliary_handle, GameHwnd;
extern  RECT window_rectangle;
extern  int  window_high, window_wide;

//ע�ᴰ����Ҫ�õ��Ĵ�����
extern  WNDCLASSEX wClass;

typedef void(*Draw)();
extern  Draw Render;

extern int pid;
extern HANDLE handle;
extern  HWND Game_handle;
extern uintptr_t module;
extern uintptr_t module2;
extern float Sc_z;
extern float Sc_x;
extern float Sc_foot;
extern float Sc_head;
extern float BoxHeight;
extern float BoxWidth;
extern int Gamer_quantity;
extern Figure_Data figure_data;
extern uintptr_t repeat;
extern int Myself_camp;
extern int ViewWidth;
extern int ViewHeight;
extern RECT RectGame;
extern float Matrix[4][4];

//ƫ��
extern std::vector<uintptr_t> gamer_quantity;
extern uintptr_t list_head;
