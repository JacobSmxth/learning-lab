# 🧠 Assembly Lab

This directory documents my hands-on learning with x86 Assembly, focusing on low-level architecture concepts, bootloaders, and binary manipulation. These projects provide the groundwork for understanding operating system design, memory layout, and bare-metal programming.

---

## 📁 Directory Structure

Assembly/
├── beginning/ # ISO bootable experiments and simple loaders
│ ├── first.asm # First bootable image
│ ├── second.asm # Sequential experiments
│ ├── multiStage/ # Multi-stage bootloader: stage1 → stage2
├── functioningBootloader/ # A working, clean multistage bootloader
├── examplesAndSuch/ # Miscellaneous/test code including AI-generated bootloaders
└── README.md

---

## 🔧 Projects Breakdown

### `beginning/`
- 🔹 Single-file `.asm` and `.iso` experiments
- 🔹 Builds basic bootable disks using `nasm` + `dd`
- 🔹 Introduces BIOS interrupts, boot sector layout, and infinite loops

### `multiStage/`
- 🧩 Simulates real OS flow with Stage 1 and Stage 2
- Bootloader chain loading (`0x7c00` → `0x8000`)
- Disk image creation with multiple stages stitched together

### `functioningBootloader/`
- ✅ A minimal working bootloader pipeline from scratch
- `stage1.asm`: MBR loader
- `stage2.asm`: Stage that handles basic output or memory ops

### `examplesAndSuch/`
- AI-generated and concept demos for additional inspiration

---

## 🛠 Toolchain

- **Assembler**: `nasm`
- **Image Tools**: `dd`, `mkisofs`
- **Emulation**: `qemu-system-x86_64`, `bochs`, `virtualbox`
- **Hex tools**: `xxd`, `hexdump`, `objdump`

---

## 🧭 Learning Outcomes

- BIOS & boot sector anatomy (MBR, 512-byte loaders)
- Real-mode assembly, segment:offset addressing
- Stack operations, jumps, and memory movement
- Bootable image creation and ISO packaging

---

🪐 *This Assembly lab is foundational for future OSDev, kernel programming, and systems design in C and Rust. Part of my [learning-lab](https://github.com/JacobSmxth/learning-lab) portfolio.*

