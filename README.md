# C++ HTTP Server

A lightweight and extensible HTTP server written in C++ using Boost.Beast, supporting Express-style middleware, routing, and static file serving.

---

## 🧠 Features

- 📦 Minimal Express-like middleware system
- 📡 Route-based request handling (GET, POST, etc.)
- 🧾 JSON request body parsing
- 🗂 Static file serving (`index.html`, `style.css`, `app.js`)
- ✅ C++20 and modern Boost usage
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
- C++20 compiler
- Boost (Beast, Asio)
- `dotenv-cpp` (for .env support)

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

You can configure port and other values via `.env`:

```
PORT=8080
```

If using `PROJECT_ROOT` to locate `.env`, define it when compiling (I recomend to define it in the Top CMakeLists.txt file):

```bash
-DPROJECT_ROOT="\"./http_cpp/\""
```

or

```cmake
set(PROJECT_ROOT "/home/tigran/Desktop/learn/http_cpp")
```

Code snippet:

```cpp
#ifdef PROJECT_ROOT
    Karich::globals::project_root = PROJECT_ROOT;
    {
        std::string env_path = Karich::globals::project_root + ".env";
        dotenv::init(env_path.c_str());
    }
#else
    std::cout << "Define the project root folder" << std::endl;
    return (EXIT_FAILURE);
#endif
```

---

## ✍️ Example Route

```cpp
router.get("/ping", [](const Request& req, Response& res, Next next) {
    res.send("pong");
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
