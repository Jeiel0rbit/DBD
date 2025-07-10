# Webview Discord Bot Dashboard

This project provides a dashboard for a Discord bot using webview. It includes a Node.js backend and a web-based frontend.

## Features

*   **Dashboard:** A web-based interface to manage your Discord bot.
*   **Cross-platform:** Built with webview, allowing it to run on various operating systems.
*   **Node.js Backend:** Handles API requests and serves the frontend.

## Getting Started

To build and run this project, you'll need CMake, a C++ compiler (like g++), Node.js, and npm installed on your system.

### Prerequisites

*   [Node.js](https://nodejs.org/en/download/) (includes npm)
*   [CMake](https://cmake.org/download/)
*   A C++ compiler (e.g., g++ on Linux, MinGW on Windows, Clang on macOS)

### Building and Running

Follow these steps to set up and run the dashboard:

1.  **Clone the repository (if you haven't already):**

    ```bash
    git clone https://github.com/Jeiel0rbit/DBD
    cd webview_discord_bot
    ```

2.  **Build the project:**

    ```bash
    cmake .
    make
    ```

    This will compile the C++ application and link it with the webview library.

3.  **Run the application:**

    ```bash
    ./webview_discord_bot
    ```

    Upon execution, the application will:
    *   Check for Node.js and npm.
    *   Install Node.js dependencies for the backend (this might take a while on the first run).
    *   Start the Node.js backend server in the background.
    *   Open a webview window navigating to the dashboard (usually `http://localhost:3001`).

    When you close the webview window, the application will attempt to stop the Node.js server processes.

## Project Structure

*   `main.cpp`: The main C++ application that initializes webview and manages the Node.js backend.
*   `DBD/backend/`: Contains the Node.js backend server.
*   `DBD/frontend/`: Contains the web-based frontend files (HTML, CSS, JavaScript).
*   `webview/`: The webview library source code.

## Important Notes

*   The Node.js backend runs on `http://localhost:3001`. Ensure this port is free.
*   The application attempts to kill Node.js processes when the webview closes. In some cases, you might need to manually verify and stop any remaining Node.js processes.
