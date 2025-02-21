#include <windows.h>
#include <string.h>
#include <stdio.h>
/* This is where all the input to the window goes to */
HWND textfield,button1,button2,button3,button4,FIELD1,FIELD2;


LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_CREATE:{
			textfield = CreateWindow("STATIC", "Please input two numbers", WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 10, 210, 20, hwnd, (HMENU) 0, NULL, NULL);
			button1=CreateWindow( "BUTTON", "+", WS_CHILD | WS_VISIBLE, 55, 130, 25, 25, hwnd, (HMENU) 1, NULL, NULL);
			button2=CreateWindow( "BUTTON", "-", WS_CHILD | WS_VISIBLE, 90, 130, 25, 25, hwnd, (HMENU) 2, NULL, NULL);
			button3=CreateWindow( "BUTTON", "x", WS_CHILD | WS_VISIBLE, 125, 130, 25, 25, hwnd, (HMENU) 3, NULL, NULL);
			button4=CreateWindow( "BUTTON", "/", WS_CHILD | WS_VISIBLE, 160, 130, 25, 25, hwnd, (HMENU) 4, NULL, NULL);
			
			FIELD1 = CreateWindow("EDIT", " ", WS_CHILD | WS_VISIBLE | WS_BORDER, 75, 50, 100, 20, hwnd, NULL, NULL, NULL);
			FIELD2 = CreateWindow("EDIT", " ", WS_CHILD | WS_VISIBLE | WS_BORDER, 75, 90, 100, 20, hwnd, NULL, NULL, NULL);
				break;
		}
		case WM_COMMAND: {
			char Num1[20],Num2[20],transform[20];
			double numA,numB;
			GetWindowText(FIELD1,Num1,20);
			GetWindowText(FIELD2,Num2,20);

			numA=atof(Num1);
			numB=atof(Num2);

			switch(LOWORD(wParam)) {
				case 1: {
					double sum=numA+numB;
					sprintf(transform,"%f",sum);
					MessageBox(hwnd,transform,"result",MB_OK);
					break;
				}
				case 2: {
					double sub=numA-numB;
					sprintf(transform,"%f",sub);
					MessageBox(hwnd,transform,"result",MB_OK);
					break;
				}
				case 3: {
					double mul=numA*numB;
					sprintf(transform,"%f",mul);
					MessageBox(hwnd,transform,"result",MB_OK);
					break;
				}
				case 4: {
					double div=numA/numB;
					sprintf(transform,"%f",div);
					MessageBox(hwnd,transform,"result",MB_OK);
					break;
				}
			}


			break;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	 wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+25);
	
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
