#include <windows.h>
#include <stdint.h>
#include "utils.c"

struct
{
  int width, height;
  u32 *pixels;
  BITMAPINFO bitmap_info;
} typedef Render_Buffer;

Render_Buffer render_buffer;
// messages come here
internal LRESULT CALLBACK window_callback(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{

  LRESULT result = 0;

  switch (message)
  {
  case WM_CLOSE:
  case WM_DESTROY:
  {
    running = false;
  }
  break;
  case WM_SIZE:{
    // Get width and height
    RECT rect;
    GetWindowRect(window, &rect);
    render_buffer.width = rect.right - rect.left;
    render_buffer.height = rect.top - rect.bottom; 

    if (render_buffer.pixels){
      // free 
    }

    render_buffer.pixels = VirtualAlloc(0, sizeof(u32)*render_buffer.width * render_buffer.height,MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE
);


    // allocate buffer

    // fill the bitmapinfo
  } break;

  default:
  {
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

  HDC hdc = GetDC(window);

  while (running)
  {
    // input
    MSG message;
    while (PeekMessageA(&message, window, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&message);
      DispatchMessage(&message);
    }

    // simulation
    int width, height;
    void *memory;
    BITMAPINFO bitmap_info;
    // render
    StretchDIBits(hdc, 0, 0, render_buffer.width, render_buffer.height, 0, 0, render_buffer.width, render_buffer.height, render_buffer.pixels, &render_buffer.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
  }
}