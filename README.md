```
  ____  _            _    ____
 | __ )| | __ _  ___| | _| __ )  ___ _ __ _ __ _   _
 |  _ \| |/ _` |/ __| |/ /  _ \ / _ \ '__| '__| | | |
 | |_) | | (_| | (__|   <| |_) |  __/ |  | |  | |_| |
 |____/|_|\__,_|\___|_|\_\____/ \___|_|  |_|   \__, |
                                                |___/
  _____ _   _ _______   ______ _____   _____
 |  ___| \ | |__   __| |  ____|  __ \ / ____|
 | |__ |  \| |  | |    | |__  | |  | | |  __
 |  __|| . ` |  | |    |  __| | |  | | | |_ |
 | |___| |\  |  | |    | |____| |__| | |__| |
 |_____|_| \_|  |_|    |______|_____/ \_____|
```

# Everything-BlackBerry 🫐

> **The most comprehensive, technically accurate, and user-friendly archive for BlackBerry devices, software, and culture.**

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Status](https://img.shields.io/badge/Status-Active%202026-brightgreen)](#current-status-2026)
[![Contributions Welcome](https://img.shields.io/badge/Contributions-Welcome-blue)](CONTRIBUTING.md)

---

## 🎯 Value Proposition

Whether you're a **newcomer** who just unboxed a BlackBerry Classic, a **developer** trying to build native QNX apps in 2026, or a **historian** cataloguing RIM's legacy — this repository has everything you need. We cover hardware specs, OS survival tricks, sideloading guides, native development, and the rich cultural history of the world's most iconic mobile brand.

**Why BlackBerry still matters in 2026:**
- Unmatched physical keyboard typing experience
- BB10 (QNX-based) is one of the most secure mobile OSes ever built
- Thriving niche community keeping devices alive
- A fascinating case study in corporate rise and fall

---

## 📚 Table of Contents

| # | Section | Description |
|---|---------|-------------|
| 1 | [📖 Current Status 2026](#current-status-2026) | What's alive, what's dead |
| 2 | [🆘 01 — Survival Guide](01_Survival_Guide/) | Essential reading for new owners |
| 3 | [💻 02 — Development Suite](02_Development_Suite/) | Build native BB10 apps |
| 4 | [🏛️ 03 — Device Museum](03_Device_Museum/) | Hardware specs & deep dives |
| 5 | [🔧 04 — Tools Archive](04_Tools_Archive/) | Firmware, PC software |
| 6 | [🌐 05 — Community & History](05_Community_&_History/) | Timeline & resources |
| 7 | [🤝 Contributing](CONTRIBUTING.md) | How to contribute |

---

## 📡 Current Status 2026

> Last verified: April 2026

### ✅ Still Working

| Service / Feature | Status | Notes |
|-------------------|--------|-------|
| **BlackBerry Infrastructure (BIS/BES)** | ❌ Dead | Shut down Jan 4, 2022 |
| **BB10 OS itself** | ✅ Alive | Fully functional offline & Wi-Fi |
| **BlackBerry World** | ❌ Dead | Store closed; use sideloading |
| **BBM (BlackBerry Messenger)** | ❌ Dead | Shut down May 31, 2019 |
| **Telegram (via Bgram)** | ✅ Working | Best messaging option in 2026 |
| **WhatsApp** | ⚠️ Workaround | Sideload older APKs; limited |
| **Email (IMAP/SMTP)** | ✅ Working | Native BB10 mail client works |
| **Browser (BB10 built-in)** | ⚠️ Partial | Needs certificate fix — see [Certificates_Fix.md](01_Survival_Guide/Certificates_Fix.md) |
| **Android Runtime (Player)** | ✅ Working | Runs Android 4.3-era APKs |
| **BlackBerry Link** | ✅ Working | With compatibility mode on Win10/11 |
| **BlackBerry Protect** | ❌ Dead | Use Google Find My Device workaround |
| **Device Activation / BBID** | ❌ Dead | Use bypass methods — see [Bypassing_Setup_Screen.md](01_Survival_Guide/Bypassing_Setup_Screen.md) |
| **Cascades/QNX Development** | ✅ Working | NDK still available; community-maintained |
| **Sachesi (sideloading tool)** | ✅ Working | Open-source, community-maintained |

### 🔑 Key Takeaways for 2026

> **"BlackBerry's servers are gone, but the hardware is not."**

- The BBID activation requirement can be bypassed on all BB10 devices.
- Sideloading Android APKs is the primary way to install apps.
- The QNX kernel and native Cascades framework still function perfectly.
- A dedicated community on Telegram and CrackBerry forums provides ongoing support.

---

## 📁 Repository Structure

```
Everything-BlackBerry/
├── README.md                          ← You are here
├── README_VN.md                       ← Vietnamese summary
├── CONTRIBUTING.md                    ← Contribution guidelines
├── LICENSE                            ← MIT License
│
├── 01_Survival_Guide/
│   ├── Bypassing_Setup_Screen.md      ← Skip BBID/activation
│   ├── Sideloading_Masterclass.md     ← Install .bar and .apk files
│   ├── Certificates_Fix.md            ← Fix SSL/TLS browser errors
│   └── Working_Apps_Directory.md      ← Apps that still work in 2026
│
├── 02_Development_Suite/
│   ├── Cascades_Qt_Setup.md           ← Full Momentics IDE setup
│   ├── Hello_BlackBerry_Native.cpp    ← Hello World in Cascades/Qt
│   ├── Native_UI_Patterns.md          ← Hub, Active Frames, Peek
│   └── Android_Runtime_Optimization.md← Make Android apps run better
│
├── 03_Device_Museum/
│   ├── devices_database.json          ← 20+ device specs in JSON
│   ├── Focus_Classic_Q20.md           ← Deep dive: BlackBerry Classic
│   └── Focus_Passport.md             ← Deep dive: BlackBerry Passport
│
├── 04_Tools_Archive/
│   ├── Autoloader_Directory.md        ← Firmware autoloader index
│   └── PC_Software_Legacy.md         ← BB Link & Blend on Win10/11
│
└── 05_Community_&_History/
    ├── Historical_Timeline.md         ← RIM/BB history 1984–2026
    └── Resources_&_Links.md          ← Best community resources
```

---

## 🚀 Quick Start

**New to BlackBerry? Start here:**

1. **[Bypass the Setup Screen](01_Survival_Guide/Bypassing_Setup_Screen.md)** — Your device needs this first
2. **[Fix Certificates](01_Survival_Guide/Certificates_Fix.md)** — So your browser works
3. **[Sideload Apps](01_Survival_Guide/Sideloading_Masterclass.md)** — Install modern apps
4. **[Find Working Apps](01_Survival_Guide/Working_Apps_Directory.md)** — Know what to install

**Developer? Go here:**

1. **[Set Up Cascades/Qt](02_Development_Suite/Cascades_Qt_Setup.md)**
2. **[Hello World Sample](02_Development_Suite/Hello_BlackBerry_Native.cpp)**
3. **[UI Patterns Guide](02_Development_Suite/Native_UI_Patterns.md)**

---

## 🌏 Other Languages

- 🇻🇳 **[Tóm tắt Tiếng Việt (README_VN.md)](README_VN.md)**

---

## 🤝 Contributing

See **[CONTRIBUTING.md](CONTRIBUTING.md)** for guidelines on adding guides, fixing errors, or submitting device specs.

---

*This project is community-maintained and not affiliated with BlackBerry Limited or TCL Communication.*
