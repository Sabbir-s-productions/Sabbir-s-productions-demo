#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

HWND hEdit;
double num1 = 0, num2 = 0;
char op = 0;
char display[100] = "";

void AppendText(const char *text)
{
    strcat(display, text);
    SetWindowText(hEdit, display);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {
            hEdit = CreateWindow(
                "EDIT", "",
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT,
                10, 10, 260, 40,
                hwnd, NULL, NULL, NULL);

            char *btns[] = {
                "7","8","9","/",
                "4","5","6","*",
                "1","2","3","-",
                "C","0","=","+"
            };

            int x = 10, y = 60;

            for(int i=0;i<16;i++)
            {
                CreateWindow(
                    "BUTTON",
                    btns[i],
                    WS_VISIBLE | WS_CHILD,
                    x,y,60,40,
                    hwnd,
                    (HMENU)(100+i),
                    NULL,NULL
                );

                x += 65;

                if((i+1)%4==0)
                {
                    x = 10;
                    y += 45;
                }
            }
            return 0;
        }

        case WM_COMMAND:
        {
            int id = LOWORD(wParam);

            if(id >= 100 && id <= 115)
            {
                char text[10];
                GetWindowText((HWND)lParam, text, sizeof(text));

                if(text[0] >= '0' && text[0] <= '9')
                {
                    AppendText(text);
                }
                else if(text[0] == 'C')
                {
                    display[0] = '\0';
                    num1 = num2 = 0;
                    op = 0;
                    SetWindowText(hEdit, "");
                }
                else if(text[0] == '+' || text[0] == '-' ||
                        text[0] == '*' || text[0] == '/')
                {
                    num1 = atof(display);
                    op = text[0];
                    display[0] = '\0';
                    SetWindowText(hEdit, "");
                }
                else if(text[0] == '=')
                {
                    num2 = atof(display);

                    double result = 0;

                    switch(op)
                    {
                        case '+': result = num1 + num2; break;
                        case '-': result = num1 - num2; break;
                        case '*': result = num1 * num2; break;

                        case '/':
                            if(num2 == 0)
                            {
                                MessageBox(hwnd,
                                           "Cannot divide by zero!",
                                           "Error",
                                           MB_OK);
                                return 0;
                            }
                            result = num1 / num2;
                            break;
                    }

                    sprintf(display, "%.2lf", result);
                    SetWindowText(hEdit, display);
                }
            }
            return 0;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASS wc = {0};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "CalculatorClass";

    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        "CalculatorClass",
        "Calculator",
        WS_OVERLAPPEDWINDOW,
        100,100,300,280,
        NULL,NULL,
        hInstance,NULL
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg;

    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}