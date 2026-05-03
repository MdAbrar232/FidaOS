# 🖥️ FidaOS

A simple command-line operating system built from scratch using C and x86 Assembly.

---

## 🚀 Overview

FidaOS is a minimal operating system developed to understand how operating systems work internally. It includes a custom kernel, basic drivers, a shell, a file system, and simple programs.

---

## ✨ Features

- Custom kernel
- Keyboard input (Shift + Caps Lock support)
- Command-line interface
- File system:
  - touch → create file
  - rm → delete file
  - ls → list files
  - cat → view file
- Text editor:
  - edit → overwrite
  - append → add to end
  - prepend → add to beginning
- Programs:
  - snake
  - pong
- Blinking cursor

---

## 🧠 What I Learned

- Basics of operating systems
- Writing low-level C code
- Handling keyboard input using scan codes
- Designing a simple file system
- Building a command-line shell
- Debugging multi-file C projects

---

## 📂 Structure

kernel/
drivers/
programs/
include/
fs.c
boot.asm
linker.ld
grub/

---

## 🖥️ Commands

help  
clear  
ls  
run <program>  
touch <file>  
rm <file>  
edit <file>  
append <file>  
prepend <file>  
cat <file>  

---

## 🛠️ Tech

C  
x86 Assembly  
GRUB  
QEMU  

---

## ▶️ Run

Build and run using your existing commands:

qemu-system-i386 -cdrom os.iso

---

## 🎯 Goal

To learn how operating systems work by building one from scratch.

---

## 📸 Demo

(Add your video link later)

---

## 👨‍💻 Author

Md Abrar
