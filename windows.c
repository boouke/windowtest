#include <windows.h>

int getFileName(){
    char fileName[MAX_PATH];
    GetModuleFileName(NULL, fileName, MAX_PATH);
    MessageBox(NULL, fileName, "File Name", MB_ICONEXCLAMATION | MB_OK);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {   
        case WM_LBUTTONDOWN:{
            getFileName();
            break;
        }
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wndc;
    HWND hwnd;
    MSG msg;
    
    wndc.cbSize        = sizeof(WNDCLASSEX);
    wndc.style         = 0;
    wndc.lpfnWndProc   = WndProc;
    wndc.cbClsExtra    = 0;
    wndc.cbWndExtra    = 0;
    wndc.hInstance     = hInstance;
    wndc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wndc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wndc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wndc.lpszMenuName  = NULL;
    wndc.lpszClassName = "WindowClass";
    wndc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wndc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "WindowClass",
        "WindowName",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080,
        NULL, NULL, hInstance, NULL);
       
    if (hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
