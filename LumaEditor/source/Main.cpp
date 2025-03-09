#include <Luma2D.h>

using namespace Luma2D::Core;

int main(int argc, char** argv)
{
    PlugData plugData;
    plugData.libPath = "../LumaMain/libLumaMain.so";
    plugData.createSym = "_Z15Luma2D_OnCreatev";
    plugData.updateSym = "_Z15Luma2D_OnUpdatev";
    plugData.renderSym = "_Z15Luma2D_OnRenderv";
    plugData.renderUISym = "_Z17Luma2D_OnRenderUIv";
    plugData.shutdownSym = "_Z17Luma2D_OnShutdownv";

    ApplicationSpecification appInfo;
    appInfo.name = "Luma Editor";
    appInfo.author = "Magnus Ahlstromer V";
    appInfo.plugData = plugData;

    Application lumaEditor(appInfo);
    lumaEditor.Run();

    return 0;
}
