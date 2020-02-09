/* Import */
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library
#include <windows.h> // Windows

/* Main */
int main(void) {
    // Global > ...
    unsigned long long bytesAvailable = 0uLL;
    unsigned long long bytesTotal = 0uLL;
    unsigned long long bytesUsed = 0uLL;

    float bytesAvailableRatio = 0.0f;
    float bytesTotalRatio = 0.0f;
    float bytesUsedRatio = 0.0f;

    // Update > ...
    ::GetDiskFreeSpaceExA(".", NULL, (_ULARGE_INTEGER*) &bytesTotal, (PULARGE_INTEGER) &bytesAvailable);
    bytesUsed = bytesTotal - bytesAvailable;

    bytesAvailableRatio = (bytesAvailable * 100) / bytesTotal;
    bytesTotalRatio = 100.0f;
    bytesUsedRatio = bytesTotalRatio - bytesAvailableRatio;

    {
        // Initialization > (... Buffer, Space ...)
        char captionBuffer[100] {0};
        char titleBuffer[50] {0};

        float spaceAvailable = ((long double) bytesAvailable) / 1024.00 / 1024.00 / 1024.00;
        float spaceTotal = ((long double) bytesTotal) / 1024.00 / 1024.00 / 1024.00;
        float spaceUsed = spaceTotal - spaceAvailable;

        // Update > ... Buffer
        ::sprintf(captionBuffer, "Available: %.*f GB \t[%.*f%c]\nUsed:        %.*f GB \t[%.*f%c]",
            (spaceAvailable == unsigned(spaceAvailable) ? 0 : 3), spaceAvailable, (bytesAvailableRatio == unsigned(bytesAvailableRatio) ? 0 : 3), bytesAvailableRatio, '%',
            (spaceUsed == unsigned(spaceUsed) ? 0 : 3), spaceUsed, (bytesUsedRatio == unsigned(bytesUsedRatio) ? 0 : 3), bytesUsedRatio, '%'
        );
        ::sprintf(titleBuffer, "  Disk Space            [%.*f GB]", (spaceTotal == unsigned(spaceTotal) ? 0 : 3), spaceTotal);

        // ...
        ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
        ::MessageBox(NULL, captionBuffer, titleBuffer, MB_OK);
    }

    // Return
    return 0;
}
