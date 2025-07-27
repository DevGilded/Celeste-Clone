
// #########################################################################
//                              Platform Globals
// #########################################################################
static bool running = true;

// #########################################################################
//                              Platform Functions
// #########################################################################
bool platform_create_window(int width, int height, char *title);
void platform_update_window();

// #########################################################################
//                              Windows Platform
// #########################################################################
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

// #########################################################################
//                              Windows Globals
// #########################################################################
static const char *classIDNAME = "Opplok Engine";
static HWND window;

// #########################################################################
//                              Platform Implementations
// #########################################################################
LRESULT CALLBACK windows_window_callback(HWND window, UINT msg,
                                         WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    switch (msg)
    {
    case WM_CLOSE:
    {
        running = false;
        break;
    }
    default:
    { // Let windows handle the default input for now
        result = DefWindowProcA(window, msg, wParam, lParam);
    }
    }

    return result;
}

bool platform_create_window(int width, int height, char *title)
{
    HINSTANCE instance = GetModuleHandleA(0); // 'A' stands for ANSI

    WNDCLASSA wc = {};
    wc.hInstance = instance;
    wc.hIcon = LoadIcon(instance, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // this means we decide the look of the cursor(arrow)
    wc.lpszClassName = classIDNAME;           // a unique identifire(ID)
    wc.lpfnWndProc = windows_window_callback; // Callback for Input into the window

    if (!RegisterClassA(&wc))
    {
        return false;
    }

    int dwStyle = WS_OVERLAPPEDWINDOW;

    window = CreateWindowExA(0, classIDNAME,
                             title,
                             dwStyle,
                             100, // window x position
                             100, // y position
                             width,
                             height,
                             NULL, // parent
                             NULL, // menu
                             instance,
                             NULL); // lparam

    if (window == NULL)
    {
        return false;
    }

    ShowWindow(window, SW_SHOW);

    return true;
}

void platform_update_window()
{
    MSG msg;

    while (PeekMessageA(&msg, window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg); // Calls the callback specified when creating the window
    }
}

#endif

int main()
{
    platform_create_window(1200, 720, "Opplok Game Engine");

    while (running)
    {
        // Do stuff
        platform_update_window();
    }

    return 0;
}