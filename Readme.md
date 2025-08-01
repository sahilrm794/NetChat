# 🗨️ NetChat: Linux-Based TCP Client-Server Chat

**NetChat** is a basic client-server chat application built in **C++** using low-level **TCP/IP socket programming** on **Linux**. It enables real-time text communication between a server and a client on the same machine (localhost).

---

## 🚀 Features

- Built using raw TCP sockets and POSIX system calls
- One-on-one communication between server and client
- Simple protocol for sending and receiving messages
- Graceful shutdown with `/exit` command
- Runs seamlessly on Linux or WSL (Windows Subsystem for Linux)

---

## 📁 Project Structure

NetChat/
├── server.cpp       # Server-side source code
├── client.cpp       # Client-side source code
└── README.md        # Project documentation


---

## 🧰 Technologies Used

- **C++**
- **Linux / WSL**
- **TCP/IP Socket Programming**
- **System Calls**: `socket()`, `bind()`, `listen()`, `accept()`, `connect()`, `read()`, `write()`, `close()`

---

## ⚙️ How to Run (Linux or WSL)

1.  **Open a terminal**, navigate to the project directory.

2.  **Compile both files**:

    ```bash
    g++ server.cpp -o server
    g++ client.cpp -o client
    ```

3.  **Start the server in one terminal**:

    ```bash
    ./server
    ```

4.  **Start the client in another terminal**:

    ```bash
    ./client
    ```

5.  **Chat away!** Use `/exit` on either side to terminate the connection.

💡 **Example Output**

**Server Terminal:**

📡 Server is listening on port 8080...
✅ Connection accepted from 127.0.0.1
📨 Client says: Hello Server!
📤 Server replied.


**Client Terminal:**

Connected to server at 127.0.0.1:8080
Type a message: Hello Server!
Server: Hello from server!


---

## 📝 Resume Highlights

- Developed a basic client-server chat application using TCP sockets in C++ on Linux.
- Implemented a simple message protocol and handled communication using system calls like `socket()`, `bind()`, `listen()`, `accept()`, and `connect()`.
- Gained hands-on understanding of low-level networking, process communication, and socket-level debugging.
- Tested on localhost to simulate real-time message exchange between client and server processes.

---

## 🧪 Testing

Tested on:
- Ubuntu 22.04 (native)
- WSL2 with Ubuntu
- GCC 11+

---

## 📎 License

This project is free and open-source. Feel free to use it for learning and experimentation.

---