#include "protract.h"
#include "tool.h"

void Get_data() {
	data::Game_handle = FindWindow(NULL, L"Counter-Strike Source");
	if (data::Game_handle == 0)
		return;
	data::pid = take_pid(L"hl2.exe");
	if (data::pid == 0)
		return;
	data::handle = OpenProcess(PROCESS_ALL_ACCESS, false, data::pid);
	if (data::handle == nullptr)
		return;
	data::module = take_module(L"server.dll");
	if (data::module == 0)
		return;
	data::module2 = take_module(L"engine.dll");
	if (data::module2 == 0)
		return;
}

void getGameRect(RECT& RectGame)
{
	RECT stRect, stKhRect;
	GetWindowRect(data::Game_handle, &stRect);
	GetClientRect(data::Game_handle, &stKhRect);
	RectGame.left = stRect.left;
	RectGame.right = stRect.right;
	RectGame.top = stRect.bottom - stKhRect.bottom;
	RectGame.bottom = stRect.bottom;
}

void protract()
{
	protract_Begin();

	int Gamer_quantity = 0;
	uintptr_t list_head = data::module + 0x4F615C;
	uintptr_t w_head = 0x0;
	int W_camp = 0;
	uintptr_t repeat = 0x0;
	Figure_Data figure_data;
	Figure_Data W;
	uintptr_t Matrix_address;
	int ViewWidth = 0;
	int ViewHeight = 0;
	float Matrix[4][4];
	RECT RectGame;


	getGameRect(RectGame);
	ViewWidth = (RectGame.right - RectGame.left) / 2;
	ViewHeight = (RectGame.bottom - RectGame.top) / 2;

	Gamer_quantity = read_multilevel<int>(data::module, data::gamer_quantity);
	Matrix_address = read_multilevel<int>(data::module2, data::Matrix_address);
	w_head = read_multilevel<int>(data::module, data::w);
	W.camp = read_memory<int>(w_head + 0x1F4);
	W.x = read_memory<float>(w_head + 0x308);
	W.y = read_memory<float>(w_head + 0x30C);
	W.z = read_memory<float>(w_head + 0x310);

	for (int i = 1; i < Gamer_quantity; i++) {
		repeat = read_memory<int>(list_head + i * 0x10);
		figure_data.life = read_memory<int>(repeat + 0xe4);
		figure_data.camp = read_memory<int>(repeat + 0x1F4);
		if (figure_data.life == 1) continue;
		if(figure_data.camp == W.camp) continue;
		figure_data.x = read_memory<float>(repeat + 0x308);
		figure_data.y = read_memory<float>(repeat + 0x30C);
		figure_data.z = read_memory<float>(repeat + 0x310);

		if (data::pane == true) {
			read_list<float>(Matrix_address + 0x2D4, &Matrix, 4 * 4);

			float Sc_z;
			float Sc_x;
			float Sc_foot;
			float Sc_head;

			Sc_z = Matrix[2][0] * figure_data.x + Matrix[2][1] * figure_data.y + Matrix[2][2] * figure_data.z + Matrix[2][3];
			float Scale = 1 / Sc_z;
			if (Sc_z < 0) continue;
			Sc_x = ViewWidth + (Matrix[0][0] * figure_data.x + Matrix[0][1] * figure_data.y + Matrix[0][2] * figure_data.z + Matrix[0][3]) * Scale * ViewWidth;
			Sc_foot = ViewHeight - (Matrix[1][0] * figure_data.x + Matrix[1][1] * figure_data.y + Matrix[1][2] * (figure_data.z - 8) + Matrix[1][3]) * Scale * ViewHeight;
			Sc_head = ViewHeight - (Matrix[1][0] * figure_data.x + Matrix[1][1] * figure_data.y + Matrix[1][2] * (figure_data.z + 78) + Matrix[1][3]) * Scale * ViewHeight;

			float BoxHeight = Sc_foot - Sc_head;
			float BoxWidth = BoxHeight * 0.526515151552;
			Sc_x -= BoxWidth / 2;
			Sc_head -= 0.0F;

			Draw_line(D3DCOLOR_ARGB(255, 0, 0, 255), ViewWidth, 0, Sc_x + BoxWidth / 2, Sc_head, 1);
			Draw_frame(Sc_x, Sc_head, BoxWidth, BoxHeight, D3DCOLOR_ARGB(255, 0, 255, 0), 1);

			float hpPercentage = figure_data.life / 100.0f;
			Draw_line(D3DCOLOR_ARGB(255, 255, 0, 0), Sc_x, Sc_head, Sc_x, Sc_head + BoxHeight * hpPercentage, 2);
		}
	}
	protract_end();
}

void Begin()
{
	create_window(data::Game_handle, protract);
	Information_circulate();
}

int main() {
	Get_data();

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Begin, NULL, 0, NULL);
	while (1)
	{
	
	}
	return 0;
}