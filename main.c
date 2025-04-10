#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "create_and_set_value.h"

#define GREEN   "\033[0;32m"
#define YELLOW  "\033[1;33m"
#define RED     "\033[0;31m"
#define RESET   "\033[0m"

void enumerate_subkeys(HKEY hkey);
void create_dword_value(HKEY hkey, LPCSTR subKeyName);

int main(int argc, char *argv[])
{
    // We first open the key (can't be read directly)

    HKEY hkey;
    LPCSTR subKey = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options";
    LONG lresult;
    LONG createKey;
    HKEY newKey;
    DWORD disposition;
    LPCSTR keyName = "taskmgr.exe";

    lresult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKey, 0, KEY_READ | KEY_ENUMERATE_SUB_KEYS | KEY_WRITE, &hkey);

    if (lresult != ERROR_SUCCESS)
    {
        if (lresult == ERROR_FILE_NOT_FOUND)
        {
            printf("Key not found\n");
        }
        else
        {
            printf("Error opening key (code %ld)\n", lresult); // 0x5 == access refused && 0x6 == invalid handle
        }
        return EXIT_FAILURE;
    }

    printf(GREEN "[+] Opened the subkey %s successfully!\n" RESET, subKey);

    Sleep(1000);

    printf(GREEN "Before creation\n" RESET);
    enumerate_subkeys(hkey);


    Sleep(1000);
    
    // we create the subkey
    createKey = RegCreateKeyEx(
        hkey,
        keyName,
        0,
        NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_WRITE,
        NULL,
        &newKey,
        &disposition);

    if (createKey != ERROR_SUCCESS)
    {
        printf(RED "[-] Failed to create or open subkey. Error code: %ld\n" RESET, createKey);
        RegCloseKey(hkey);
        return EXIT_FAILURE;
    }

    if (disposition == REG_CREATED_NEW_KEY)
    {
        printf(GREEN "[+] Key %s was newly created!\n" RESET, keyName);
    }
    else if (disposition == REG_OPENED_EXISTING_KEY)
    {
        printf(YELLOW "[!] Key %s already exists.\n" RESET, keyName);
    }

    Sleep(1000);

    // creating our dword value (its a string but i cba to modify)
    create_dword_value(newKey, keyName);

    Sleep(1000);

    RegCloseKey(newKey);

    printf(GREEN "After creation\n" RESET);
    enumerate_subkeys(hkey);

    Sleep(1000);
    RegCloseKey(hkey);

    return EXIT_SUCCESS;
}