# WordSorter Web Server

A simple HTTP server that accepts a list of words through a web interface, sorts them, and returns the sorted words. The server is built using C++ and the Boost.Beast library.

## Requirements

- C++17 or later
- CMake (3.10 or higher)
- Boost libraries (1.70.0 or later:
  - `boost_system`
  - `boost_filesystem`

## Installation

### Installing Boost on Void Linux

1. Update package repository:
  
  ```bash
  sudo xbps-install -S
  ```
  
2. Install Boost development libraries:
   ```bash
   sudo xbps-install -y boost-devel
   ```
    
## Building the Project

### Clone this repository:

  ```bash
  git clone 
  cd WordSorter
  ```

### Run CMake to configure the project:

  ```bash
  cmake -Bbuild -GNinja
  ```
### Compile the project:

  ```bash
  cmake --build build
  ```

## Running the Server

### Start the server:

  ```bash
  ./build/WordSorterWebServer
  ```

### License

  This project is licensed under the MIT License - see the LICENSE file for details.
  Contributing
