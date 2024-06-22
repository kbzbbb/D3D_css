#include "tool.h"

int take_pid(const wchar_t* name)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pr32;
	pr32.dwSize = sizeof(PROCESSENTRY32);

	for (Process32First(snapshot, &pr32); Process32Next(snapshot, &pr32);) {
		if (!wcscmp(pr32.szExeFile, name)) {
			return pr32.th32ProcessID;
		}
	}
	CloseHandle(snapshot);
}

uintptr_t take_module(const wchar_t* module_name)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, data::pid);
	MODULEENTRY32 mo32;
	mo32.dwSize = sizeof(MODULEENTRY32);

	for (Module32First(snapshot, &mo32); Module32Next(snapshot, &mo32);) {
		if (!wcscmp(mo32.szModule, module_name)) {
			return (uintptr_t)mo32.modBaseAddr;
		}
	}
	CloseHandle(snapshot);
}
