#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main() {
    string path;
    cout << "Enter path: ";
    cin >> path;

    // Check if the path exists and is a directory
    if (!fs::exists(path) || !fs::is_directory(path)) {
        cout << "Invalid directory path. Please check and try again.\n";
        return 1;
    }

    // Iterate through all files in the directory
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            string filename = entry.path().filename().string();
            string extension = entry.path().extension().string();

            // Remove the dot from the extension
            if (!extension.empty() && extension[0] == '.') {
                extension = extension.substr(1);
            }

            if (!extension.empty()) {  // Ensure extension is not empty
                fs::path targetDir = path + "/" + extension;

                // Check if the directory exists, if not, create it
                if (!fs::exists(targetDir)) {
                    fs::create_directory(targetDir);
                    cout << "Created directory: " << targetDir << endl;
                }

                // Move the file to the directory based on its extension
                fs::path targetPath = targetDir / filename;
                fs::rename(entry.path(), targetPath);
                cout << "Moved " << filename << " to " << targetDir << endl;
            }
        }
    }

    cout << "Files organized by extensions.\n";
    return 0;
}
