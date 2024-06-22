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

//注册窗口需要用到的窗口类
extern  WNDCLASSEX wClass;

typedef void(*Draw)();
extern  Draw Render;

namespace data {
	extern int pid;
	extern HANDLE handle;
	extern  HWND Game_handle;
	extern uintptr_t module;
	extern uintptr_t module2;

	//extern 	int Gamer_quantity;
	//extern int ViewWidth;
	//extern int ViewHeight;
	//extern float Sc_z;
	//extern float Sc_x;
	//extern float Sc_foot;
	//extern float Sc_head;
	//extern float BoxHeight;
	//extern float BoxWidth;
	//extern float hpPercentage;

	//偏移
	extern std::vector<uintptr_t> gamer_quantity;
	extern std::vector<uintptr_t> w;
	extern std::vector<uintptr_t> Matrix_address;

	//开关
	extern bool pane;
}

