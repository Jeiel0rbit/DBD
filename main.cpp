#include <webview/webview.h>
#include <string>
#include <thread> // For std::this_thread::sleep_for
#include <chrono> // For std::chrono::seconds
#include <cstdlib> // For system()
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif



int main() {
#ifdef _WIN32
    // Set console code page to UTF-8 so console output correctly displays unicode.
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    // Define the path to the backend server.js
    std::string backend_path = "DBD/backend";
    std::string server_js_path = backend_path + "/server.js";
    std::string npm_install_command = "npm install --prefix " + backend_path;
    std::string node_command = "node " + server_js_path;

    // Check if node and npm are available
    std::cout << "Checking for Node.js and npm..." << std::endl;
    if (system("node -v > /dev/null 2>&1") != 0 || system("npm -v > /dev/null 2>&1") != 0) {
        std::cerr << "Node.js or npm is not installed or not in PATH. Please install them to run the dashboard." << std::endl;
        return 1;
    }
    std::cout << "Node.js and npm found." << std::endl;

    // 1. Install Node.js dependencies
    std::cout << "Installing Node.js dependencies for the backend (this might take a while)..." << std::endl;
    int install_result = system(npm_install_command.c_str());
    if (install_result != 0) {
        std::cerr << "Error installing Node.js dependencies. Please check the output above. Exiting." << std::endl;
        return 1;
    }
    std::cout << "Node.js dependencies installed." << std::endl;

    // 2. Start the Node.js backend server in the background
    std::cout << "Starting Node.js backend server..." << std::endl;
#ifdef _WIN32
    // On Windows, use start command to run in a new detached console
    // Note: This does not provide the PID directly to the C++ app for clean shutdown.
    // A more robust solution would involve CreateProcess and storing the PID.
    std::string start_server_command = "start /B " + node_command;
#else
    // On Linux/macOS, run in background
    // Note: This does not provide the PID directly to the C++ app for clean shutdown.
    // A more robust solution would involve fork/exec and storing the PID.
    std::string start_server_command = node_command + " &";
#endif
    system(start_server_command.c_str());
    std::cout << "Node.js backend server started. Waiting for it to initialize..." << std::endl;

    // Give the server a moment to start up
    std::this_thread::sleep_for(std::chrono::seconds(5)); // Adjust as needed based on server startup time


    // 3. Initialize and run the webview
    webview::webview w(true, nullptr);
    w.set_title("Bot Host Dashboard");
    w.set_size(1200, 800, WEBVIEW_HINT_NONE);
    w.navigate("http://localhost:3001"); // Navigate to the backend server's address
    w.run();

    // 4. When webview closes, attempt to kill the Node.js server process
    // This is a simplistic approach and might kill other node processes.
    // For a more precise shutdown, the PID of the spawned process should be captured and used.
    std::cout << "Webview closed. Attempting to stop Node.js server processes..." << std::endl;
#ifdef _WIN32
    system("taskkill /F /IM node.exe"); // Kills all node.exe processes
#else
    system("killall node"); // Kills all node processes
#endif
    std::cout << "Node.js server stop attempt complete. You may need to manually verify and stop any remaining node processes." << std::endl;

    return 0;
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) {
    return main();
}
#endif
