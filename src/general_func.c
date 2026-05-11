#include "general_func.h"
#include <windows.h>

void gotoxy(int x, int y)
{
    // 获取标准输出句柄（单例模式思想，建议全局缓存以优化性能）
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // COORD 是 Windows 定义的一个结构体，包含 X 和 Y
    COORD pos = {(short)x, (short)y};
    // 设置光标位置
    SetConsoleCursorPosition(hConsole, pos);
}
