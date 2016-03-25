
BOOL MyStopDeviceAD(HANDLE hDevice); // 停止采集线程
UINT ReadDataThread_Dma(PVOID hWnd);
UINT ReadDataThread_Half(PVOID hWnd);
UINT ReadDataThread_Npt(PVOID hWnd);
int run(long *adbuffer);
void yuntai(int angle);