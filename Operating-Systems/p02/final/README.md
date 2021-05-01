# Christian Elliott's Operating Systems Final Project

## Instructions
* To run the programs, first you must compile
  * `make` will first delete any existing `server` or `client` binaries
  * It will then compile `server.cpp` and `client.cpp`, producing two executables
* After compiling, open a second terminal in the same location as the project root
  * In the first terminal, run `make s` to start the server
  * In the second terminal, run `make c` to start a client connection

## Usage
* When a server is running and you connect a client, the server will automatically establish a connection
* Then, on the client, you may execute commands of the form:
  * `info FILE` where file is a file in the current director
  * `get FILE` where file is in a sub-directory
  * `exit` which will terminate the client connection

## Notes
The server supports multiple connections, however, it is not handled by a queue.
Furthermore, it has not been cleaned of bugs. For example, I've run into issues
with parsing info/get requests where the filenames are wrong or invalid.