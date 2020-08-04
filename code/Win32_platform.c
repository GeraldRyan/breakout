#include <windows.h>

typedef int b32;

#define true 1
#define false 0

#define global_variable static
#define internal static

global_variable b32 running = true;

// messages come here
internal LRESULT CALLBACK window_callback(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{


  LRESULT result = 0;

  switch(message){
    case WM_CLOSE:
    case WM_DESTROY: {
      running = false;
    } break;

    default: {
       result = DefWindowProcA(window, message, w_param, l_param);
    }

  }

  return result; 
};

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

  WNDCLASSA window_class = {0};

  window_class.style = CS_HREDRAW | CS_VREDRAW;
  window_class.lpfnWndProc = window_callback;

  window_class.lpszClassName = "Game_Window_Class";

  RegisterClassA(&window_class);

  HWND window = CreateWindowExA(0, window_class.lpszClassName, "Breakout", WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, 0, 0);

  while (running) {
    // input
    MSG message;
    while (PeekMessageA(&message, window, 0,0, PM_REMOVE)){
      TranslateMessage(&message);
      DispatchMessage(&message);
    }

    // simulation

    // render
  }

}