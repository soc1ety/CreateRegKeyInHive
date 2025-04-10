#include <windows.h>
#include <stdio.h>
#include "create_and_set_value.h"

// Used to get the number of subkeys (prevents infinite loop when last subkey is printed)
void enumerate_subkeys(HKEY hkey)
{
    DWORD subKeyCount = 0;
    DWORD maxSubKeyLen;
    DWORD dwSize;
    char dwValue[255];

    RegQueryInfoKey(
        hkey,
        NULL,
        NULL,
        NULL,
        &subKeyCount,
        &maxSubKeyLen,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL);

    for (DWORD i = 0; i < subKeyCount; i++)
    {
        dwSize = sizeof(dwValue);
        RegEnumKeyEx(hkey, i, dwValue, &dwSize, NULL, NULL, NULL, NULL);
        printf("%s\n", dwValue);
    }
}

// Function to create a string value inside a registry key (its a string not dword but i cba to change as well)
void create_dword_value(HKEY hkey, LPCSTR subKeyName)
{
    LPCSTR valueName = "Debugger";
    LPCSTR valueData = "C:\\Program Files\\SystemInformer\\SystemInformer.exe"; // bc we want to swap taskmgr for systeminformer

    LONG result = RegSetValueEx(
        hkey,
        valueName,
        0,
        REG_SZ,
        (const BYTE *)valueData,
        (DWORD)(strlen(valueData) + 1));

    if (result == ERROR_SUCCESS)
    {
        printf("[+] Successfully created REG_SZ value '%s' with data '%s'\n", valueName, valueData);
    }
    else
    {
        printf("[-] Failed to set REG_SZ value. Error code: %ld\n", result);
    }
}
