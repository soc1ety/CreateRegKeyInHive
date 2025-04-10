# readme.md (or don't) 

## purpose
i was bored and fed up with task manager not showing me the info i needed, so i decided to play around with the windows registry to replace it by SystemInformer (also known as ProcessHacker) whenever i use `win+r` `taskmgr` or `ctrl-alt-suppr` shortcuts.  
doing it in a few clicks was too easy so i went the less easy way and played with some really interesting (documented 🙏) win32 functions.  

## what it does 

- opens the `HKEY_LOCAL_MACHINE` registry key 
- lists all subkeys within that key before modification  
- creates a new subkey under `Image File Execution Options` (full path : `HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\`) 
- sets the key/value pair
- again lists all subkeys within that key after modification to confirm the creation of the subkey 

## use case 

not much i guess, mostly fueled by boredom and i like learning new stuff whether it's useful or not at the end

## structure and APIs used 

- `main.c`: core logic explained above 
- `create_dword_value.c`: contains helper functions
- `create_dword_value`.h`: function declarations

[RegOpenKeyEx](https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regopenkeyexa)  
[RegEnumKeyEx](https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regenumkeyexa)  
[RegQueryInfoKey](https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regqueryinfokeya)  
[RegCreateKeyEx](https://learn.microsoft.com/fr-fr/windows/win32/api/winreg/nf-winreg-regcreatekeyexa)  
[RegSetValueEx](https://learn.microsoft.com/fr-fr/windows/win32/api/winreg/nf-winreg-regsetvalueexa)

## some more words 

code is kind of atrocious and not really cleaned/optimized but i'm okay with it since I don't plan on working on it anymore  
even though i see some ways of weaponizing it and i'd like to learn more about windows registry stuff, we'll see

## last words 

enjoy (or not i will understand) 
