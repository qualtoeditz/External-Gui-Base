## 🚀 External GUI Base

A **stable**, **modular**, and **easy-to-use** external GUI foundation built with [Dear ImGui](https://github.com/ocornut/imgui). Perfect for creating overlay or external UI applications in C++.

[![License: MIT](https://img.shields.io/github/license/qualtoeditz/External-Gui-Base)](https://github.com/qualtoeditz/External-Gui-Base/blob/main/LICENSE)  
[![GitHub stars](https://img.shields.io/github/stars/qualtoeditz/External-Gui-Base?style=social)](https://github.com/qualtoeditz/External-Gui-Base/stargazers)  
[![GitHub issues](https://img.shields.io/github/issues/qualtoeditz/External-Gui-Base)](https://github.com/qualtoeditz/External-Gui-Base/issues)  
[![GitHub forks](https://img.shields.io/github/forks/qualtoeditz/External-Gui-Base?style=social)](https://github.com/qualtoeditz/External-Gui-Base/network/members)  

---

## ✨ Features

- Clean, modular code architecture  
- Simple integration into your projects  
- Window management, widget support, and input handling  
- Uses ImGui for lightweight rendering  
- Open source and easily extensible  

---

## 📦 Installation

```bash
git clone https://github.com/qualtoeditz/External-Gui-Base.git
cd External-Gui-Base
# Build with your preferred toolchain (Visual Studio, GCC, etc.)

🛠 Usage
Initialize and start your GUI using the base class.

Customize and add your own windows or widgets inside the main loop.

cpp
Copy
Edit
#include "GuiBase.h"

GuiBase gui;
gui.Initialize();

while (running) {
    gui.BeginFrame();

    ImGui::Begin("My Window");
    ImGui::Text("Hello, External GUI Base!");
    ImGui::End();

    gui.Render();
}
🤝 Contributing
Contributions, bug reports, and feature requests are welcome! Feel free to open issues or pull requests.

