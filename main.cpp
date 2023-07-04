#include <Windows.h>
#include <vector>
#include <string>

// Функция для получения путей к изображениям в заданной папке
std::vector<std::wstring> getImagePaths(const std::wstring& folderPath) {
    std::vector<std::wstring> imagePaths;
    WIN32_FIND_DATAW findData;
    HANDLE findHandle = FindFirstFileW((folderPath + L"\\*").c_str(), &findData);
    if (findHandle != INVALID_HANDLE_VALUE) {
        do {
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                std::wstring fileName = findData.cFileName;
                std::wstring filePath = folderPath + L"\\" + fileName;
                imagePaths.push_back(filePath);
            }
        } while (FindNextFileW(findHandle, &findData));
        FindClose(findHandle);
    }
    return imagePaths;
}

int main() {
    // Путь к папке с изображениями
    std::wstring imagePath = L"C:\\Users\\U1\\Build\\practice\\wallpaper";

    // Получаем список путей к изображениям в заданной папке
    std::vector<std::wstring> imagePaths = getImagePaths(imagePath);

    // Интервал смены обоев (в миллисекундах)
    const int wallpaperDelay = 1500;

    // Индекс текущего изображения
    int currentImageIndex = 0;

    // Установка первого обоев
    SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (PVOID)imagePaths[currentImageIndex].c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);

    while (true) {
        // Пауза в течение заданного интервала
        Sleep(wallpaperDelay);

        // Переход к следующему изображению
        currentImageIndex = (currentImageIndex + 1) % imagePaths.size();
        // Установка следующего обоев
        SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (PVOID)imagePaths[currentImageIndex].c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
    }

    return 0;
}