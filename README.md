<img width="1536" height="1024" alt="image" src="https://github.com/user-attachments/assets/6d40e11b-4c22-4878-87ae-6cadbd06518d" />

# 🖥️ FidaOS

FidaOS is a simple command-line operating system built from scratch using C and x86 Assembly.  
This project was developed to explore how operating systems work at a low level by implementing core components manually, without relying on existing OS frameworks.
[![Watch FidaOS Demo](https://img.youtube.com/vi/irG-IZGzjAc/0.jpg)](https://www.youtube.com/watch?v=irG-IZGzjAc)

---

## 🚀 Overview

FidaOS is designed as a minimal but functional system that demonstrates how a computer can boot, take input, process commands, and manage data. The system includes a custom kernel, basic drivers, a command-line shell, and a small file system.

Rather than focusing on complexity, the goal was to apply the fundamentals—how input is handled, how memory is used, and how different parts of an operating system interact with each other.

---

## ✨ Features

FidaOS provides a working command-line environment where users can create, edit, and manage files. It also includes simple built-in programs for interaction and testing.

The system supports:
- A custom shell for command execution  
- File creation, deletion, listing, and reading  
- A text editor with multiple editing modes (overwrite, append, prepend)  
- Keyboard input handling with Shift and Caps Lock support  
- A blinking cursor interface for user feedback  
- Built-in programs such as Snake and Pong  

---

## 🧠 Skills Demonstrated

Through this project, I developed hands-on experience with:

- Low-level programming in C without standard libraries  
- Direct hardware interaction (keyboard input via I/O ports, VGA memory at 0xB8000)  
- Operating system design (kernel, drivers, file system, shell)  
- Memory management and debugging (resolving pointer-related issues)  
- Building a command-line interface with command parsing  
- Designing modular systems with clear separation between kernel, drivers, and programs  
- Implementing real-time input handling and game loops    

---

## 📂 Project Structure

The project is organized into separate modules to keep the system clean and maintainable:

- `kernel/` → Core system logic and command handling  
- `drivers/` → Hardware interaction (keyboard, display)  
- `programs/` → Built-in applications like Snake, Pong, and editor  
- `include/` → Header files for shared structures and functions  
- `fs.c` → File system implementation  
- `boot.asm` → Bootloader code  
- `linker.ld` → Memory layout configuration  
- `grub/` → Boot configuration  

---

## 🖥️ Commands

FidaOS provides a small but functional set of commands:

- `help` → show available commands  
- `clear` → clear the screen  
- `ls` → list files and programs  
- `touch <file>` → create a file  
- `rm <file>` → delete a file  
- `cat <file>` → view file contents  
- `edit <file>` → overwrite file contents  
- `append <file>` → add content to the end  
- `prepend <file>` → add content to the beginning  
- `run <program>` → execute a program  

---

## 🛠️ Tech Stack

- C (low-level system programming)  
- x86 Assembly  
- GRUB bootloader  
- QEMU (for running and testing the OS)  

---

## ▶️ Running the Project

The OS can be built using GCC and NASM, then run using QEMU.

Once built, it can be launched with:

qemu-system-i386 -cdrom os.iso

---

## 🎯 Purpose

The purpose of FidaOS was to obtain a practical understanding of how operating systems work internally by building one from scratch.

---

## 👨‍💻 Author

Md Abrar Mahbub Fida.
North South University (NSU), Dhaka, Bangladesh
