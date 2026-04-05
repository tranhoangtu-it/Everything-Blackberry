<!--
  Title: Autoloader Directory — BB10 Firmware Guide
  Author: Everything-BlackBerry Contributors
  Last Verified: 2026-04-01
-->

# Autoloader Directory

> **What is an Autoloader?** An Autoloader is a self-contained Windows executable (`.exe`) file that contains the complete BlackBerry 10 operating system firmware for a specific device model and carrier variant. Running the autoloader on a Windows PC while the device is connected via USB will wipe the device and install the specified OS version from scratch. It is the most reliable way to update, downgrade, or restore a BB10 device.

---

## Understanding Autoloaders

### How They Work

```
PC (Windows)                    BB10 Device (USB connected)
─────────────────────           ──────────────────────────
Autoloader .exe launched   →    Device enters recovery mode
Firmware extraction        →    OS partitions wiped
OS image transmission      →    Partitions written (progress %)
Validation                 →    Checksum verification
                                Device reboots into fresh OS
```

### Key Properties

| Property | Detail |
|----------|--------|
| File format | Self-extracting Windows executable (`.exe`) |
| Average file size | 2–3 GB per autoloader |
| Platform required | Windows (XP through Windows 11) |
| Device connection | USB only (not Wi-Fi) |
| Effect | **Complete wipe** — all user data destroyed |
| Driver required | BlackBerry USB driver (included in BlackBerry Link or standalone) |

### Autoloader vs OTA Update

| Method | Pros | Cons |
|--------|------|------|
| **Autoloader** | Always works; guaranteed OS version; restores bricked devices | Wipes all data; requires Windows PC |
| **OTA (Over The Air)** | Preserves data; no PC needed | OTA servers offline since 2022; no longer available |

> ⚠️ **Data backup is essential.** Before running any autoloader, back up your device using BlackBerry Link or manual file copy via USB.

---

## Part 1: Device Model and Variant Identification

Before downloading an autoloader, you must identify your exact device model. Autoloaders are **carrier-specific** in some cases.

### How to Find Your Model Number

1. On the device: **Settings → About → Hardware** — shows the model number (e.g., `SQC100-5`)
2. On the back of the device: look for the model number on the sticker under the battery cover

### Model Number to Carrier Matrix

| Model | Device | Carrier/Region |
|-------|--------|---------------|
| SQC100-1 | Classic | AT&T (USA) |
| SQC100-2 | Classic | Verizon (USA, CDMA) |
| SQC100-3 | Classic | T-Mobile (USA) |
| SQC100-5 | Classic | Unlocked (Global GSM) |
| SQW100-1 | Passport | Rogers / Unlocked (Global) |
| SQW100-2 | Passport | AT&T (USA) |
| SQW100-3 | Passport | T-Mobile / Unlocked |
| SQW100-4 | Passport Silver | Unlocked (all regions) |
| STA100-5 | Z30 | Unlocked (Global) |
| STL100-1 | Z10 | CDMA (Verizon) |
| STL100-2 | Z10 | GSM (AT&T, T-Mobile) |
| STL100-3 | Z10 | European |
| STL100-4 | Z10 | Unlocked Global |
| SQN100-3 | Q10 | Unlocked Global |
| STR100-2 | Leap | Unlocked Global |

---

## Part 2: Essential Autoloader Versions by Device

> ℹ️ **Note on sources:** BlackBerry's official download servers are offline. Autoloaders must be obtained from community mirrors. Verify checksums (SHA-256) before running any autoloader. Recommended sources are listed below.

### BlackBerry Classic (Q20)

| OS Version | Notes | Recommended |
|------------|-------|-------------|
| `10.3.1.2576` | Launch OS version | ⬇️ Only if needed for specific app compatibility |
| `10.3.2.2876` | Intermediate; improved Android Runtime | ⬇️ Alternative |
| **`10.3.3.2049`** | **Final OS release; highest stability and compatibility** | ✅ **Recommended** |

**Autoloader names to search for:**
- `Z30_10.3.3.2049_SQC100-1_ATT_Verizon_ATT_Verizon_10.3.3.2049.exe` (carrier specific naming varies)
- Generic search: `"Classic" "SQC100" "10.3.3.2049" autoloader`

### BlackBerry Passport (SQW100)

| OS Version | Notes | Recommended |
|------------|-------|-------------|
| `10.3.0.678` | Launch OS for original Passport | ⬇️ Historical only |
| `10.3.1.2576` | First major update | ⬇️ If needed |
| `10.3.2.2876` | Significant improvements to keyboard touch | ⬇️ Good stable choice |
| **`10.3.3.2049`** | **Final and recommended** | ✅ **Recommended** |

### BlackBerry Z10

| OS Version | Recommended |
|------------|-------------|
| `10.3.3.2049` (STL100-2/4) | ✅ Recommended |
| `10.3.2.2876` (STL100-1 CDMA) | Use for Verizon variant |

### BlackBerry Z30

| OS Version | Recommended |
|------------|-------------|
| `10.3.3.2049` (STA100-5) | ✅ Recommended |
| `10.3.2.2876` | Alternative |

### BlackBerry Q10

| OS Version | Recommended |
|------------|-------------|
| `10.3.3.2049` | ✅ Recommended |

### BlackBerry Leap

| OS Version | Recommended |
|------------|-------------|
| `10.3.3.2049` (STR100-2) | ✅ Recommended |
| `10.3.2.2876` | Some users report better battery on this version |

---

## Part 3: How to Run an Autoloader

### Prerequisites

- Windows 7, 8.1, 10, or 11 (32-bit or 64-bit)
- BlackBerry USB drivers installed (included with BlackBerry Link)
- Device battery ≥ 50%
- USB cable (original BlackBerry cable recommended)
- ~5 GB free disk space

### Step-by-Step Instructions

```
1. BACKUP YOUR DATA FIRST
   ─────────────────────────────────────────────────────
   a) Open BlackBerry Link on your PC
   b) Connect device via USB
   c) Perform a full device backup
   d) Verify the backup completed successfully
   e) Note: The autoloader WILL wipe everything

2. DOWNLOAD THE AUTOLOADER
   ─────────────────────────────────────────────────────
   a) Find the correct autoloader for your model (see above)
   b) Verify the SHA-256 hash against the community-provided checksums
   c) Save to a known location (e.g., C:\BB_Autoloaders\)

3. VERIFY THE HASH (PowerShell on Windows)
   ─────────────────────────────────────────────────────
   Get-FileHash "C:\BB_Autoloaders\AutoLoader.exe" -Algorithm SHA256

4. CLOSE BLACKBERRY LINK (important!)
   ─────────────────────────────────────────────────────
   BB Link must be closed before running the autoloader.
   It conflicts with the autoloader's USB communication.

5. RUN THE AUTOLOADER
   ─────────────────────────────────────────────────────
   a) Right-click the autoloader .exe
   b) Select "Run as Administrator"
   c) The autoloader GUI will appear
   d) Follow the on-screen instructions
   e) Connect your device when prompted

6. WAIT FOR COMPLETION
   ─────────────────────────────────────────────────────
   a) The process takes 15-40 minutes depending on device
   b) DO NOT disconnect the USB cable during this process
   c) The device will reboot several times — this is normal
   d) Progress percentage is shown in the autoloader GUI

7. SETUP BYPASS
   ─────────────────────────────────────────────────────
   After the flash completes, the device will boot to the
   setup screen. You'll need to bypass BBID again.
   See: Bypassing_Setup_Screen.md
```

### Troubleshooting Autoloader Issues

| Problem | Solution |
|---------|----------|
| "Device not found" | Reinstall BlackBerry USB drivers; try a different USB port |
| Autoloader freezes at 0% | Disconnect, reboot device into recovery mode (hold Vol Up + Power), retry |
| Autoloader freezes mid-process | **Do not panic** — wait 10 minutes; if no progress, force-quit and retry |
| "Wrong device" error | You have the wrong autoloader for your model number |
| Device stuck in boot loop after | Run autoloader again; the OS write was incomplete |
| Windows 11 compatibility warning | Ignore the warning and proceed — autoloaders work on Win 11 |

---

## Part 4: Community Mirror Sources

> ⚠️ **Security notice:** Only use autoloaders from trusted community sources. Always verify SHA-256 checksums. Never run `.exe` files from unknown sources.

| Source | What They Host |
|--------|---------------|
| **CrackBerry Forums** → BB10 Software | Community-verified autoloaders with checksums |
| **Archive.org** | Historical firmware archives |
| **Sachesi** (built-in) | Can download autoloaders directly via community-maintained API |
| **BB10 Telegram group** | Members share verified links (see Resources_&_Links.md) |

### Using Sachesi to Download Autoloaders

Sachesi has a built-in firmware downloader that can retrieve autoloaders:

1. Open Sachesi → **"Extracts"** tab.
2. Enter your device PIN or select device model.
3. Select OS version `10.3.3.2049`.
4. Click **"Search"** — Sachesi will find available firmware.
5. Click **"Download"** — saves the autoloader package.

---

*See also: [PC Software Legacy Guide →](PC_Software_Legacy.md)*
