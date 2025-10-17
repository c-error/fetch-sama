#include <windows.h>
#include <powrprof.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define BUFFLEN 1024*4
#define HELPMSG "\n\n ?n.exe help\n\n" \
                "\t?n.exe auto\t\t\t\tprint evil/neuro art based on time\n" \
                "\t?n.exe <file name>\t\t\tprint txt file art\n" \
                "\t?n.exe rgb b <r;g;b> <string>\tset background color\n" \
                "\t?n.exe rgb f <r;g;b> <string>\tset foreground color\n" \
                "\t?n.exe rgb rst\t\t\treset all colors\n" \
                "\n\n example:\n\n" \
                "\t?n.exe rgb b 255;0;0 \"Hello-World!\"\n" \
                "\t?n.exe rgb f 0;255;0 \"Hello-World!\"\n\n"

#pragma comment(lib, "PowrProf.lib")

static const GUID GUID_HIGH_PERFORMANCE = {0x8c5e7fda, 0xe8bf, 0x4a96, {0x9a,0x85,0xa6,0xe2,0x3a,0x8c,0x63,0x5c}};
static const GUID GUID_BALANCED = {0x381b4222, 0xf694, 0x41f0, {0x96,0x85,0xff,0x5b,0xb2,0x60,0xdf,0x2e}};
static const GUID GUID_POWER_SAVER = {0xa1841308, 0x3541, 0x4fab, {0xbc,0x81,0xf7,0x15,0x56,0xf2,0x0b,0x4a}};



void replace(char *str, const char *old, int len, const char *new) {

    char temp[BUFFLEN];
    char *p;

    strcpy(temp, str);
    str[0] = '\0';
    
    p = strstr(temp, old);
    while (p != NULL) {

        strncat(str, temp, p - temp);
        strcat(str, new);
        memmove(temp, p+len, strlen(p+len) + 1);
        p = strstr(temp, old);
    }
    strcat(str, temp);
}



int buildPath(char *buff, char *path) {

    char temp[BUFFLEN];
    if (GetModuleFileNameA(NULL, temp, BUFFLEN)) {

        temp[strrchr(temp, '\\') - temp] = '\0';

        if (path) snprintf(buff, BUFFLEN, "%s\\%s", temp, path);
        else strcpy(buff,  temp);

        return 1;
    }
    return 0;
}



void printHelp(HANDLE hOut, char* exe) {

    DWORD _;
    char temp[BUFFLEN];
    strcpy(temp, HELPMSG);

    char *file = strrchr(exe, '\\');

    if (file) file++;
    else file = exe;
    replace(file, ".exe", 4, "");
    replace(temp, "?n", 2, file);
    WriteConsoleA(hOut, temp, strlen(temp), &_, NULL);
}



int main(int argc, char *argv[]) {

    DWORD dwMode = 0;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    SetConsoleOutputCP(65001);

    if (argc < 2) {
        printHelp(hOut, argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "rgb") == 0) {
        
        DWORD _;
        char temp[BUFFLEN];

        if (strcmp(argv[2], "f") == 0) {

            snprintf(temp, BUFFLEN, "%c[38;2;%sm%s", 27, argv[3], argv[4]);
            WriteConsoleA(hOut, temp, BUFFLEN, &_, NULL);
            return 0;

        } else if (strcmp(argv[2], "b") == 0) {

            snprintf(temp, BUFFLEN, "%c[48;2;%sm%s", 27, argv[3], argv[4]);
            WriteConsoleA(hOut, temp, BUFFLEN, &_, NULL);
            return 0;
        
        } else if (strcmp(argv[2], "rst") == 0) {

            snprintf(temp, BUFFLEN, "%c[0m", 27);
            WriteConsoleA(hOut, temp, BUFFLEN, &_, NULL);
            return 0;
        
        } else {

            printHelp(hOut, argv[0]);
            return 1;
        }
    } else if (strcmp(argv[1], "help") == 0) {
        
        printHelp(hOut, argv[0]);
        return 0;
    }

    char value[256];
    char line[BUFFLEN];
    char color[13][256];
    char accent[4][256];
    char info[21][256];
    char cach[200][BUFFLEN];

    HKEY hKey;
    DWORD regLen = 256;

    MEMORYSTATUSEX memInfo; memInfo.dwLength = sizeof(memInfo);

    SYSTEMTIME st;
    GetLocalTime(&st);

    if (st.wHour > 12) snprintf(info[19], 256, "%02d:%02d:%02d PM (%02d/%02d/%04d)", st.wHour-12, st.wMinute, st.wSecond, st.wDay, st.wMonth, st.wYear);
    else if (st.wHour == 12) snprintf(info[19], 256, "%02d:%02d:%02d PM (%02d/%02d/%04d)", st.wHour, st.wMinute, st.wSecond, st.wDay, st.wMonth, st.wYear);
    else snprintf(info[19], 256, "%02d:%02d:%02d AM (%02d/%02d/%04d)", st.wHour, st.wMinute, st.wSecond, st.wDay, st.wMonth, st.wYear);

    if (strcmp(argv[1], "auto") == 0) {
        if (st.wHour >= 18 || st.wHour <= 6) strcpy(argv[1],  "evil");
        else strcpy(argv[1],  "neuro");
    }

    GetConsoleTitleA(info[14], 256);
    char* tLen = strrchr(info[14], '\\');

    if (tLen) {
        snprintf(info[14], 256, tLen+1);
        replace(info[14], "  ", 2, " ");

        info[14][25] = ' ';
        info[14][26] = '.';
        info[14][27] = '.';
        info[14][28] = '.';
        info[14][29] = '\0';
    } else {
        info[14][0] = ' ';
        info[14][1] = '.';
        info[14][2] = '.';
        info[14][3] = '.';
        info[14][4] = '\0';
    }

    buildPath(info[13], NULL);

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", 0, KEY_READ | KEY_WOW64_64KEY, &hKey) == ERROR_SUCCESS
        && 
        RegQueryValueExA(hKey, "BaseBoardProduct", NULL, NULL, (LPBYTE)value, &regLen) == ERROR_SUCCESS) {
        strcpy(info[0],  value);
    }
    RegCloseKey(hKey);



    regLen = 256;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ | KEY_WOW64_64KEY, &hKey) == ERROR_SUCCESS
        && 
        RegQueryValueExA(hKey, "ProcessorNameString", NULL, NULL, (LPBYTE)value, &regLen) == ERROR_SUCCESS) {
        replace(value, "(R) Core(TM)", 12, "");
        strcpy(info[1],  value);
    }
    RegCloseKey(hKey);



    regLen = 256;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\WinSAT", 0, KEY_READ | KEY_WOW64_64KEY, &hKey) == ERROR_SUCCESS
        && 
        RegQueryValueExA(hKey, "PrimaryAdapterString", NULL, NULL, (LPBYTE)value, &regLen) == ERROR_SUCCESS) {
        strcpy(info[2],  value);
    }
    RegCloseKey(hKey);



    HDC hdc = GetDC(NULL);

        int width  = GetDeviceCaps(hdc, HORZRES);
        int height = GetDeviceCaps(hdc, VERTRES);
        int refresh = GetDeviceCaps(hdc, VREFRESH);

        snprintf(info[3], 256, "%dx%d @ %dHz", width, height, refresh);
    ReleaseDC(NULL, hdc);



    int totalPack = 0;
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ | KEY_WOW64_64KEY, &hKey) == ERROR_SUCCESS) {

            char subKey[256];
            DWORD subKeyLen;
            int i = 0;

            while (1) {
                subKeyLen = 256;
                if (RegEnumKeyExA(hKey, i++, subKey, &subKeyLen, NULL, NULL, NULL, NULL) != ERROR_SUCCESS) { totalPack += i; break; }
            }
        }
        RegCloseKey(hKey);
        if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ | KEY_WOW64_64KEY, &hKey) == ERROR_SUCCESS) {

            char subKey[256];
            DWORD subKeyLen;
            int i = 0;

            while (1) {
                subKeyLen = 256;
                if (RegEnumKeyExA(hKey, i++, subKey, &subKeyLen, NULL, NULL, NULL, NULL) != ERROR_SUCCESS) { totalPack += i; break; }
            }
        }
        RegCloseKey(hKey);
    snprintf(info[16], 256, "%d Packages", totalPack-2);


    if (GlobalMemoryStatusEx(&memInfo)) {

        double totalGB = memInfo.ullTotalPhys / 1073741824.0;
        double usedGB  = totalGB - (memInfo.ullAvailPhys / 1073741824.0);

        double totalPGB = memInfo.ullTotalPageFile / 1073741824.0;
        double usedPGB = totalPGB - (memInfo.ullAvailPageFile / 1073741824.0);
        double pagPer = (usedPGB / totalPGB) * 100.0;

        snprintf(info[6], 256, "%u%%", memInfo.dwMemoryLoad);
        snprintf(info[7], 256, "%.2f / %.2f GB (Memory)", usedGB, totalGB);
        snprintf(info[8], 256, "%.0f%%", pagPer);
        snprintf(info[9], 256, "%.2f / %.2f GB (Pagefile)", usedPGB, totalPGB);
    }

    
    
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ | KEY_WOW64_64KEY, &hKey) == ERROR_SUCCESS) {

        char tempA[256], tempB[256], tempC[256];
            regLen = 256;
            if (RegQueryValueExA(hKey, "ProductName", NULL, NULL, (LPBYTE)value, &regLen) == ERROR_SUCCESS) {

                // value[regLen - 1] = '\0';
                strcpy(tempA,  value);
            }

            regLen = 256;
            if(RegQueryValueExA(hKey, "CurrentBuild", NULL, NULL, (LPBYTE)value, &regLen) == ERROR_SUCCESS) {
                // value[regLen - 1] = '\0';
                strcpy(tempB,  value);
            }

            regLen = 256;
            if(RegQueryValueExA(hKey, "DisplayVersion", NULL, NULL, (LPBYTE)value, &regLen) == ERROR_SUCCESS) {
                // value[regLen - 1] = '\0';
                strcpy(tempC,  value);
            }
        snprintf(info[11], 256, "%s - %s (%s)", tempA, tempB, tempC);

        regLen = 256;
        if(RegQueryValueExA(hKey, "RegisteredOwner", NULL, NULL, (LPBYTE)value, &regLen) == ERROR_SUCCESS) {
            // value[regLen - 1] = '\0';
            strcpy(info[17],  value);
        }

        regLen = 256;
        DWORD tempTime;
        if(RegQueryValueExA(hKey, "InstallDate", NULL, NULL, (LPBYTE)&tempTime, &regLen) == ERROR_SUCCESS) {
            
            double diff = difftime(time(NULL), (time_t)tempTime);
            snprintf(info[12], 256, "%d days", (int)(diff / 86400));
        }
    }
    RegCloseKey(hKey);

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {

        char subKeyName[256];
        regLen = 256;
        DWORD idx = 0, subKeyLen;

        while (1) {
            subKeyLen = sizeof(subKeyName);
            if (RegEnumKeyEx(hKey, idx, subKeyName, &subKeyLen, NULL, NULL, NULL, NULL) != ERROR_SUCCESS) break;

            HKEY hSubKey;
            if (RegOpenKeyExA(hKey, subKeyName, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS && RegQueryValueEx(hSubKey, "DhcpIPAddress", NULL, NULL, (LPBYTE)value, &regLen) == ERROR_SUCCESS) {
                strcpy(info[10], value);
                RegCloseKey(hSubKey);
            }
            idx++;
        }
    }
    RegCloseKey(hKey);

    char drives[256];
    if (GetLogicalDriveStringsA(256, drives)) {

        unsigned __int64 tb = 0, fb = 0;
        char *p = drives;
        while (*p) {
            ULARGE_INTEGER total, freeAll, tmp;
            if (GetDiskFreeSpaceExA(p, &tmp, &total, &freeAll)) {
                tb += total.QuadPart;
                fb += freeAll.QuadPart;
            }
            p += strlen(p) + 1;
        }

        double totalS = tb / 1073741824.0;
        double useS = totalS - (fb / 1073741824.0);
        double usePer = (useS / totalS) * 100.0;
        
        snprintf(info[4], 256, "%.0f%%", usePer);
        snprintf(info[5], 256, "%.2f / %.2f GB (Storage)", useS, totalS);
    }


    GUID *activeSchemeGuid = NULL;
    if (PowerGetActiveScheme(NULL, &activeSchemeGuid) == ERROR_SUCCESS) {

        if (IsEqualGUID(activeSchemeGuid, &GUID_HIGH_PERFORMANCE)) strcpy(info[15], "High-Performance");
        else if (IsEqualGUID(activeSchemeGuid, &GUID_BALANCED)) strcpy(info[15], "Balanced-Power");
        else if (IsEqualGUID(activeSchemeGuid, &GUID_POWER_SAVER)) strcpy(info[15], "Low-Performance");
        else strcpy(info[15], "Custom-Profile!");
        LocalFree(activeSchemeGuid);
    }



    DWORD64 uptime_ms = GetTickCount64();
    
    DWORD64 seconds = uptime_ms / 1000;
    DWORD64 minutes = seconds / 60;
    DWORD64 hours = minutes / 60;
    DWORD64 days = hours / 24;

    if (days <= 0) snprintf(info[18], 256, "%llu hours, %llu min", hours % 24, minutes % 60);
    else snprintf(info[18], 256, "%llu days, %llu hours, %llu min", days, hours % 24, minutes % 60);
    
    char filePath[256];
    snprintf(filePath, 256, "%s\\configs\\%s.txt", info[13], argv[1]);
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("\n \"%s.txt\" File Not Found! add config txt file on this location: %s\\configs", argv[1], info[13]);
        printHelp(hOut, argv[0]);
        return 1;
    }

    int len = 1;
    int mlen = 0;
    // char temp[BUFFLEN];

    while (fgets(line, sizeof(line), file)) {

        if (line[0] == '[') {

                 if (line[1] == 'A' && line[2] == ']') {    replace(line, "[A]=", 4, "");  replace(line, "\n", 1, ""); strcpy(accent[0], line);    }
            else if (line[1] == 'B' && line[2] == ']') {    replace(line, "[B]=", 4, "");  replace(line, "\n", 1, ""); strcpy(accent[1], line);    }
            else if (line[1] == 'C' && line[2] == ']') {    replace(line, "[C]=", 4, "");  replace(line, "\n", 1, ""); strcpy(accent[2], line);    }
            else if (line[1] == 'H' && line[2] == ']') {    replace(line, "[H]=", 4, "");  replace(line, "\n", 1, ""); strcpy(accent[3], line);    }
            else if (line[1] == '1' && line[2] == ']') {    replace(line, "[1]=", 4, "");  replace(line, "\n", 1, ""); snprintf(color[0] , 256, "%c[38;2;%sm", 27, line);   }     // 1
            else if (line[1] == '2' && line[2] == ']') {    replace(line, "[2]=", 4, "");  replace(line, "\n", 1, ""); snprintf(color[1] , 256, "%c[38;2;%sm", 27, line);   }     // 2
            else if (line[1] == '3' && line[2] == ']') {    replace(line, "[3]=", 4, "");  replace(line, "\n", 1, ""); snprintf(color[2] , 256, "%c[38;2;%sm", 27, line);   }     // 3
            else if (line[1] == '4' && line[2] == ']') {    replace(line, "[4]=", 4, "");  replace(line, "\n", 1, ""); snprintf(color[3] , 256, "%c[38;2;%sm", 27, line);   }     // 4
            else if (line[1] == '5' && line[2] == ']') {    replace(line, "[5]=", 4, "");  replace(line, "\n", 1, ""); snprintf(color[4] , 256, "%c[38;2;%sm", 27, line);   }     // 5
            else if (line[1] == '6' && line[2] == ']') {    replace(line, "[6]=", 4, "");  replace(line, "\n", 1, ""); snprintf(color[5] , 256, "%c[38;2;%sm", 27, line);   }     // 6
            else if (line[1] == '7' && line[2] == ']') {    replace(line, "[7]=", 4, "");  replace(line, "\n", 1, ""); snprintf(color[6] , 256, "%c[38;2;%sm", 27, line);   }     // 7
            else if (line[1] == '8' && line[2] == ']') {    replace(line, "[8]=", 4, "");  replace(line, "\n", 1, ""); snprintf(color[7] , 256, "%c[38;2;%sm", 27, line);   }     // 8
            else if (line[1] == '9' && line[2] == ']') {    replace(line, "[9]=", 4, "");  replace(line, "\n", 1, ""); snprintf(color[8] , 256, "%c[38;2;%sm", 27, line);   }     // 9
            else if (line[1] == '1' && line[2] == '0') {    replace(line, "[10]=", 5, ""); replace(line, "\n", 1, ""); snprintf(color[9] , 256, "%c[38;2;%sm", 27, line);   }     // 10
            else if (line[1] == '1' && line[2] == '1') {    replace(line, "[11]=", 5, ""); replace(line, "\n", 1, ""); snprintf(color[10], 256, "%c[38;2;%sm", 27, line);   }     // 11
            else if (line[1] == '1' && line[2] == '2') {    replace(line, "[12]=", 5, ""); replace(line, "\n", 1, ""); snprintf(color[11], 256, "%c[38;2;%sm", 27, line);   }     // 12
            else if (line[1] == '!') {

                replace(line, "[!]", 3, "");
                replace(line, "\n", 1, "");

                for (int i=13; i >= 0; i--) {
                    
                    char idx[5];
                    snprintf(idx, 5, "$%d", i);
                    if (color[i-1] != NULL) replace(line, idx, strlen(idx), color[i-1]);
                }

                int l;     
                switch (len) {

                    case 1:  l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm┌─────────────── Hardware ───────────────┐%c[0m",                  line, 27, accent[0], 27); break;
                    case 2:  l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm├ %c[38;2;%sm%s%c[0m",                                                  line, 27, accent[0], 27, accent[2], info[0], 27); break;
                    case 3:  l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm│ %c[38;2;%sm├■ %c[38;2;%sm%s%c[0m",                               line, 27, accent[0], 27, accent[1], 27, accent[2], info[1], 27); break;
                    case 4:  l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm│ %c[38;2;%sm├■ %c[38;2;%sm%s%c[0m",                               line, 27, accent[0], 27, accent[1], 27, accent[2], info[2], 27); break;
                    case 5:  l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm│ %c[38;2;%sm├■ %c[38;2;%sm%s%c[0m",                               line, 27, accent[0], 27, accent[1], 27, accent[2], info[3], 27); break;
                    case 6:  l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm│ %c[38;2;%sm├■ %c[38;2;%sm[%c[38;2;%sm%s%c[38;2;%sm] %s%c[0m",    line, 27, accent[0], 27, accent[1], 27, accent[2], 27, accent[3], info[4], 27, accent[2], info[5], 27); break;
                    case 7:  l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm│ %c[38;2;%sm├■ %c[38;2;%sm[%c[38;2;%sm%s%c[38;2;%sm] %s%c[0m",    line, 27, accent[0], 27, accent[1], 27, accent[2], 27, accent[3], info[6], 27, accent[2], info[7], 27); break;
                    case 8:  l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm│ %c[38;2;%sm├■ %c[38;2;%sm[%c[38;2;%sm%s%c[38;2;%sm] %s%c[0m",    line, 27, accent[0], 27, accent[1], 27, accent[2], 27, accent[3], info[8], 27, accent[2], info[9], 27); break;
                    case 9:  l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm│ %c[38;2;%sm└■ %c[38;2;%sm%s%c[0m",                               line, 27, accent[0], 27, accent[1], 27, accent[2], info[10], 27); break;
                    case 10: l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm└────────────────────────────────────────┘%c[0m",                  line, 27, accent[0], 27); break;
                    case 11: l = snprintf(cach[len-1], BUFFLEN, "\t %s%c[0m", line, 27); break;
                    case 12: l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm┌─────────────── Software ───────────────┐%c[0m",                  line, 27, accent[0]); break;
                    case 13: l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm├ %c[38;2;%sm%s%c[0m",                                             line, 27, accent[0], 27, accent[2], info[11], 27); break;
                    case 14: l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm│ %c[38;2;%sm├ Age: %c[38;2;%sm%s%c[0m",                           line, 27, accent[0], 27, accent[1], 27, accent[2], info[12], 27); break;
                    case 15: l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm│ %c[38;2;%sm├ Path: %c[38;2;%sm%s%c[0m",                          line, 27, accent[0], 27, accent[1], 27, accent[2], info[13], 27); break;
                    case 16: l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm│ %c[38;2;%sm├ Shell: %c[38;2;%sm%s%c[0m",                         line, 27, accent[0], 27, accent[1], 27, accent[2], info[14], 27); break;
                    case 17: l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm│ %c[38;2;%sm├ Power: %c[38;2;%sm%s%c[0m",                         line, 27, accent[0], 27, accent[1], 27, accent[3], info[15], 27); break;
                    case 18: l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm│ %c[38;2;%sm└■ %c[38;2;%sm%s%c[0m",                               line, 27, accent[0], 27, accent[1], 27, accent[2], info[16], 27); break;
                    case 19: l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm└────────────────────────────────────────┘%c[0m",                  line, 27, accent[0], 27); break;
                    case 20: l = snprintf(cach[len-1], BUFFLEN, "\t %s%c[0m", line, 27); break;
                    case 21: l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm┌───────────────── User ─────────────────┐%c[0m",                  line, 27, accent[0], 27); break;
                    case 22: l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm├ %c[38;2;%sm%s%c[0m",                                             line, 27, accent[0], 27, accent[3], info[17], 27); break;
                    case 23: l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm│ %c[38;2;%sm├ Uptime: %c[38;2;%sm%s%c[0m",                        line, 27, accent[0], 27, accent[1], 27, accent[2], info[18], 27); break;
                    case 24: l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm│ %c[38;2;%sm├ Now: %c[38;2;%sm%s%c[0m",                           line, 27, accent[0], 27, accent[1], 27, accent[2], info[19], 27); break;
                    case 25: l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm│ %c[38;2;%sm└%c[90m □ ■%c[31m ■%c[91m ■%c[32m ■%c[92m ■%c[33m ■%c[93m ■%c[34m ■%c[94m ■%c[35m ■%c[95m ■%c[36m ■%c[96m ■%c[37m ■%c[97m ■%c[0m", line, 27, accent[0], 27, accent[1], 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27); break;
                    case 26: l = snprintf(cach[len-1], BUFFLEN, "\t %s \t%c[38;2;%sm└────────────────────────────────────────┘%c[0m",                  line, 27, accent[0], 27); break;
                    default: l = snprintf(cach[len-1], BUFFLEN, "\t %s%c[0m", line, 27);
                }

                if (l > mlen) mlen = l;
                len++;
            }
        }
    }

    fclose(file);

    char *memBuff = malloc(len*mlen);
    char *tmp = memBuff;

    for (int i = 0; i < len; i++) {

        memcpy(tmp, cach[i], mlen);
        tmp += mlen;
        *tmp++ = '\n';
    }
    *tmp = '\0';

    fwrite(memBuff, 1, tmp - memBuff, stdout);
    fflush(stdout);
    free(memBuff);

    return 0;
}
