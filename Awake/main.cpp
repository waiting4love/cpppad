#include <tchar.h>
#include <Windows.h>
void main()
{
    ::SetThreadExecutionState(ES_SYSTEM_REQUIRED |
        ES_DISPLAY_REQUIRED |
        ES_CONTINUOUS);
    ::MessageBox(nullptr, _T("Keep Awake"), _T("Keep Awake"), MB_OK);

    ::ExitProcess(0);
}