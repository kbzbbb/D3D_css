#include "protract.h"
#include "tool.h"

void Get_data() {
	Game_handle = FindWindow(NULL, L"Counter-Strike Source");
	if (Game_handle == 0)
		return;
	pid = take_pid(L"hl2.exe");
	if (pid == 0)
		return;
	handle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	if (handle == nullptr)
		return;
	module = take_module(L"server.dll");
	if (module == 0)
		return;
	module2 = take_module(L"engine.dll");
	if (module2 == 0)
		return;
}

void getGameRect(RECT& RectGame)
{
	RECT stRect, stKhRect;
	GetWindowRect(Game_handle, &stRect);
	GetClientRect(Game_handle, &stKhRect);
	RectGame.left = stRect.left;
	RectGame.right = stRect.right;
	RectGame.top = stRect.bottom - stKhRect.bottom;
	RectGame.bottom = stRect.bottom;
}

void protract()
{
	ViewWidth = (RectGame.right - RectGame.left) / 2;
	ViewHeight = (RectGame.bottom - RectGame.top) / 2;
	list_head = module + 0x4F615C;
	Gamer_quantity = read_multilevel<int>(module, gamer_quantity);
	repeat = read_memory<int>(list_head);
	Myself_camp = read_memory<int>(repeat + 0x1F4);

	protract_Begin();
	for (int i = 0; i < Gamer_quantity; i++) {
		repeat = read_memory<int>(list_head + (i * 0x10));
		figure_data.life = read_memory<int>(repeat + 0xe4);
		figure_data.camp = read_memory<int>(repeat + 0x1F4);

		if (figure_data.life == 1 || figure_data.camp == Myself_camp) continue;

		figure_data.x = read_memory<float>(repeat + 0x308);
		figure_data.y = read_memory<float>(repeat + 0x30C);
		figure_data.z = read_memory<float>(repeat + 0x310);
		Gamer_quantity = read_multilevel<int>(module, gamer_quantity);

		read_list<float>(module2 + 0x5AAA64, &Matrix, 4 * 4);

		Sc_z = Matrix[2][0] * figure_data.x + Matrix[2][1] * figure_data.y + Matrix[2][2] * figure_data.z + Matrix[2][3];
		float Scale = 1 / Sc_z;
		if (Sc_z < 0) continue;
		Sc_x = ViewWidth + (Matrix[0][0] * figure_data.x + Matrix[0][1] * figure_data.y + Matrix[0][2] * figure_data.z + Matrix[0][3]) * Scale * ViewWidth;
		Sc_foot = ViewHeight - (Matrix[1][0] * figure_data.x + Matrix[1][1] * figure_data.y + Matrix[1][2] * (figure_data.z - 8) + Matrix[1][3]) * Scale * ViewHeight;
		Sc_head = ViewHeight - (Matrix[1][0] * figure_data.x + Matrix[1][1] * figure_data.y + Matrix[1][2] * (figure_data.z + 78) + Matrix[1][3]) * Scale * ViewHeight;

		BoxHeight = Sc_foot - Sc_head;
		BoxWidth = BoxHeight * 0.526515151552;
		Sc_x -= BoxWidth / 2;
		Sc_head -= 0.0F;

		Draw_line(D3DCOLOR_ARGB(255, 0, 255, 0), 500, 0, Sc_x, Sc_head, 2);
		Draw_frame(Sc_x, Sc_head, BoxWidth, BoxHeight, 2, D3DCOLOR_ARGB(255, 255, 0, 0));
	}
	protract_end();
}

void Begin()
{
	create_window(Game_handle, protract);
	Information_circulate();
}

int main() {
	Get_data();
	getGameRect(RectGame);

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Begin, NULL, 0, NULL);

	while (1)
	{
		//for (int i = 0; i < Gamer_quantity; i++) {




		//	
		//}
	}

	return 0;
}