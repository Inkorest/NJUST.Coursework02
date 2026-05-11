#include <stdio.h>
#include <windows.h>
#include "auth.h"

int main()
{
    if (user_register())
        return 1;
    scanf("%s");
    return 0;
}
