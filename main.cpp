#include <windows.h>
#include <iostream>

using namespace std;

#define max 100

int primocheck(int numero){
	//cout<<"entre a la func";
	bool primo=true ;
	int i ;
	for(i=2; i<=numero/2; ++i) {
      if(numero%i==0) {
         primo=false ;
         break;
      }
   }
   if (primo==true){
   	
   	return numero;
   	
   }else {
   		numero =numero+1;
   		primocheck(numero);
   }
	
}

int main(){
	//int max =100;
	int numero;
	cout<< "Ingrese un numero menor que 100 :";
	cin >> numero ;
	while (numero >max) {
		cout<< "El numero tiene que ser menor que 100, vuelva a ingresarlo : ";
		cin >> numero;
		
	}
	int primo1,primo2;
	primo1=2 ;
	primo2=2 ;
	
	while (primo1+primo2<=numero){//||(primo1+primo2==numero)){
	
		int resultado = primo1+primo2;
		int resultado_avanzado= resultado;
		
		cout <<primo1 <<" + "<<primo2<<" = "<< resultado << endl;
		//focus despues de esto ademas de que hay que buscar una forma de saber como unnumero es primo
		primo2++;
		
		//mirate aqui dqu
		primo2=primocheck(primo2);
		
		resultado=primo1+primo2;
		
		if (resultado == resultado_avanzado+2){
			resultado_avanzado= resultado; 
			
		}else {
			primo1++;
			primo1=primocheck(primo1);
		}
		
		
	}
	cout <<"por aqui voy";
	
}






/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
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
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
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
