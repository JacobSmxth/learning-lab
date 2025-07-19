# 🦀 Rust Lab

This directory documents my entry into the Rust programming language — a critical skill for high-assurance systems, OS development, and performance-critical backend tooling. Rust is my endgame systems language following mastery in C.

---

## 📁 Structure

Rust/
├── guessing_game/ # CLI game using RNG and pattern matching
├── hello_cargo/ # Cargo-based "Hello, world!" scaffolding
├── hello_world/ # Basic syntax introduction
├── variables/ # Variable types, shadowing, mutability
├── notes/ # Learning journal and insights
└── README.md

---

## 📘 Projects Overview

### `guessing_game/`
- First non-trivial Rust program
- Uses `rand` crate and CLI input parsing
- Demonstrates pattern matching and control flow

### `variables/`
- Covers `let`, `mut`, shadowing, and type inference
- Outputs compiled binaries with cargo build

---

## 🧠 Learning Themes

- Ownership, borrowing, and lifetimes (⚠️ upcoming)
- Crates and Cargo project structure
- Pattern matching and enums
- Standard library utilities (`std::fs`, `std::io`)
- Error handling: `Result`, `Option`, `unwrap`, `expect`

---

## 🛠 Tooling

- `rustup`, `cargo`, `clippy`, `rustfmt`, `cargo-watch`
- `target/` directories contain compiled artifacts (usually in `.gitignore`)

---

## 🛣️ Roadmap

- [ ] CLI utilities with `clap`
- [ ] File manipulation and I/O streams
- [ ] Build a safe wrapper over `unsafe` C bindings
- [ ] Custom memory allocators
- [ ] Experimental kernel modules

---

🔥 *Rust is my strategic pivot into memory-safe, high-performance systems programming — bridging the gap between raw power (C) and modern maintainability.*
