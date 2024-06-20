#include "data.h"

MARGINS Margin;
LPDIRECT3D9              g_pD3D = NULL;
LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
D3DPRESENT_PARAMETERS    g_d3dpp = {};
ID3DXLine* pLine = 0;
ID3DXFont* Font;

HWND auxiliary_handle, GameHwnd;
RECT window_rectangle;
int  window_high, window_wide;

//注册窗口需要用到的窗口类
WNDCLASSEX wClass;

typedef void(*Draw)();
Draw Render;

int pid = 0;
HANDLE handle = nullptr;
HWND Game_handle = 0x0;
uintptr_t module = 0x0;
uintptr_t module2 = 0x0;
float Sc_z;
float Sc_x;
float Sc_foot;
float Sc_head;
float BoxHeight;
float BoxWidth;
int Gamer_quantity;
Figure_Data figure_data;
uintptr_t repeat = 0;
int Myself_camp;
int ViewWidth = 0;
int ViewHeight = 0;
RECT RectGame;
float Matrix[4][4];

std::vector<uintptr_t> gamer_quantity = { 0x0058D758,0x500,0x4,0xC,0x4 };
uintptr_t list_head;