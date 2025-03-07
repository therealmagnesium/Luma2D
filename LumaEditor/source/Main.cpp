#include "LumaEditor.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    ApplicationSpecification appInfo;
    appInfo.name = "Luma2D Editor";
    appInfo.author = "Magnus Ahlstromer V";

    LumaEditor editor(appInfo);
    editor.Run();

    return 0;
}
