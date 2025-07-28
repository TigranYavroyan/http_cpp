# C++ HTTP Server

A lightweight and extensible HTTP server written in C++ using Boost.Beast, supporting Express-style middleware, routing, and static file serving.

---

## 🧠 Features

- 📦 Minimal Express-like middleware system
- 📡 Route-based request handling (GET, POST, etc.)
- 🧾 JSON request body parsing
- 🗂 Static file serving (`index.html`, `style.css`, `app.js`)
- ✅ C++17 and modern Boost usage
- 🔌 Easily extendable middleware chain

---

## 📁 Project Layout

```
http_cpp/
├── public/               # Static frontend files
│   ├── index.html
│   ├── style.css
│   └── app.js
├── includes/             # HTTP framework headers
│   ├── http_server.h
│   ├── router.h
│   ├── request.h
│   ├── response.h
│   ├── middleware.h
│   ├── middlewares.h
│   ├── next.h
│   └── ...
├── server.cpp            # Main entry point
├── .env                  # Environment variables (e.g. PORT=8080)
├── CMakeLists.txt        # Build script
└── .vscode/              # VSCode settings (optional)
```

---

## ⚙️ Build Instructions

### Prerequisites

- CMake ≥ 3.10
- C++17 compiler
- Boost (Beast, Asio)
- nlohmann::json

### Install Dependencies

```bash
sudo apt update
sudo apt install libboost-all-dev nlohmann-json3-dev
```

### Configuration

You can configure port and other values via `.env`:

```
PORT=8080
```

If using `PROJECT_ROOT` to locate `.env`, define it when compiling (I recommend to define it in srcs/CMakeLists.txt file):

```bash
-DPROJECT_ROOT="\"/absolute/path/to/http_cpp\""
```

or

```cmake
set(PROJECT_ROOT /absolute/path/to/http_cpp)
```

### Compile

```bash
cd http_cpp
mkdir build && cd build
cmake ..
make
```

---

## 🚀 Run

```bash
./http_server
```

---

## ✍️ Example Route

```cpp
router.get("/ping", [](const Request& req, Response& res, Next next) {
    // status must be always set by user
    res.send("pong").status(200);
});
```

---

## 🧪 Development Tips

- Add middleware using the `use()` method
- Use `res.send()` or `res.json()` for responses
- Static files are served from `/public`

---

## 👤 Author

Tigran Yavroyan  
[GitHub](https://github.com/TigranYavroyan)
