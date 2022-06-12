#include <windows.h>
#include <xstring>
#include <string>
typedef std::basic_string<TCHAR, std::char_traits<TCHAR>,
	std::allocator<TCHAR> > String;

using namespace std;

#define ID_NUM1 444
#define ID_NUM2 555
#define ID_CON 666
#define ID_DIS 777
#define ID_XOR 999

#define ID_OUTPUT 888

//String dec2bin(int num);
//string formString(int* pointer);
string formString(int num);
int dec2bin(int num);
int doCon(int x, int y);
int doDis(int x, int y);
int doXor(int x, int y);

HINSTANCE hInst;
LPCTSTR szWindowClass = (LPCTSTR)"QWERTY";
LPCTSTR szTitle = (LPCTSTR)"ÂÎÑÜÌÀ ÏÐÎÃÐÀÌÀ";

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_HAND);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;
	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance;
	hWnd = CreateWindow(szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		400,
		400,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}
HWND firstEdit, secondEdit, conButton, disButton,xorButton, outputText;
int s[32];
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;

	int size;
	char* X;
	char* Y;
	String res, num;
	int* pointer;
	char p[32];
	string result;

	for (int i = 0; i < 32; i++)
		s[i] = 0;

	switch (message)
	{
	case WM_CREATE:
		firstEdit = CreateWindow((LPCSTR)"edit", (LPCSTR)"0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 90, 25, 70, 25, hWnd, (HMENU)ID_NUM1, NULL, NULL);
		secondEdit = CreateWindow((LPCSTR)"edit", (LPCSTR)"0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 220, 25, 70, 25, hWnd, (HMENU)ID_NUM2, NULL, NULL);
		conButton = CreateWindow((LPCSTR)"button", (LPCSTR)"*", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 165, 10, 50, 25, hWnd, (HMENU)ID_CON, NULL, NULL);
		disButton = CreateWindow((LPCSTR)"button", (LPCSTR)"+", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 165, 40, 50, 25, hWnd, (HMENU)ID_DIS, NULL, NULL);
		xorButton = CreateWindow((LPCSTR)"button", (LPCSTR)"(+)", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 165, 70, 50, 25, hWnd, (HMENU)ID_XOR, NULL, NULL);
		outputText = CreateWindow((LPCSTR)"static", (LPCSTR)"Press button", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 10, 100, 360, 270, hWnd, (HMENU)ID_OUTPUT, NULL, NULL);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
		switch (wParam) {
		case ID_CON:

			size = GetWindowTextLength(firstEdit)*4;
			X = new char[size];
			GetWindowTextA(firstEdit, X, size);

			size = GetWindowTextLength(secondEdit)*4;
			Y = new char[size];
			GetWindowTextA(secondEdit, Y, size);
						
			//res = formString(7); 

			res = res + "X: " + formString(atol(X)) + '\n' + "Y: " + formString(atol(Y)) + "\n";

			res = res + "Сonjunction: " + formString(doCon(atol(X), atol(Y)));

			SetWindowText(outputText, res.data());
			break;

		case ID_DIS:
			size = GetWindowTextLength(firstEdit) * 4;
			X = new char[size];
			GetWindowTextA(firstEdit, X, size);

			size = GetWindowTextLength(secondEdit) * 4;
			Y = new char[size];
			GetWindowTextA(secondEdit, Y, size);

			res = res + "X: " + formString(atol(X)) + '\n' + "Y: " + formString(atol(Y)) + "\n";

			res = res + "Disjunction: " + formString(doDis(atol(X), atol(Y)));

			SetWindowText(outputText, res.data());
			break;

		
		case ID_XOR:
		
			size = GetWindowTextLength(firstEdit) * 4;
			X = new char[size];
			GetWindowTextA(firstEdit, X, size);

			size = GetWindowTextLength(secondEdit) * 4;
			Y = new char[size];
			GetWindowTextA(secondEdit, Y, size);

			res = res + "X: " + formString(atol(X)) + '\n' + "Y: " + formString(atol(Y)) + "\n";

			res = res + "By module 2: " + formString(doXor(atol(X), atol(Y)));

			SetWindowText(outputText, res.data());
			break;
		}
	
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int doCon(int x, int y)
{
	int res;
_asm {
	mov eax, x
	mov edx, y
	and eax, edx
	mov res, eax
}
return res;
}

int doDis(int x, int y)
{
	int res;
	_asm
	{
		mov eax, x
		mov ebx, y		
		or eax, ebx 	 
		mov res, eax
	}
	return res;
}

int doXor(int x, int y)
{
	int res;
	_asm {
		mov eax, x
		mov edx, y
		xor eax, edx
		mov res, eax
	}
	return res;
}
int dec2bin(int num) {
	int N = num, pr;
		for (int i = 0; i < 32; i++)
		s[i] = 0;

	__asm {
	mov eax, num
	test eax, eax
	jns start
	neg num
	start:
	mov eax, 2
	mov ebx, 2
	mov edx, 0
	mov esi, 31
	WhileLoop :
		mov eax, num 
		div ebx
		mov [s+esi*4], edx
		dec esi
		mov edx, 0
		mov num, eax
		cmp num, 0
	jnz WhileLoop
		mov eax, N
		test eax, eax
		jns endf
		mov ecx, 0
	InvertLoop:
		cmp[s + ecx * 4], 0
		jne eqNull
		jz eqOne
		eqOne :
		mov [s + ecx * 4], 1
		inc ecx
		jmp endInvLoop
		eqNull :
		mov[s + ecx * 4], 0
		inc ecx
		endInvLoop :
		cmp ecx, 31
		jbe InvertLoop
		mov ecx, 31
	PlusOneLoop:
		cmp[s + ecx * 4], 0
		jz point2
		mov[s + ecx * 4], 0
		dec ecx
		cmp ecx, 0
		jge PlusOneLoop
		point2 :
	mov[s + ecx * 4], 1
		mov[s], 1
		endf:
	}

	return 0;
}

string formString(int num) {
	int p[32];
	string result;
	dec2bin(num);
	for (int i = 0; i < 32; i++)
		p[i] = char(s[i]);
	for (int i = 0; i < 32; i++)
		result += to_string(p[i]);
	return result;
}
