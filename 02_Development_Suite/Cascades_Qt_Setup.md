<!--
  Title: BlackBerry Cascades & Qt Development Environment Setup
  Author: Everything-BlackBerry Contributors
  Last Verified: 2026-04-01
  Platform: Windows 10/11, Ubuntu 20.04+, macOS 12+
-->

# Cascades / Qt Development Environment Setup

> **Complete guide to setting up the BlackBerry 10 native development environment in 2026.** This covers finding and installing the Momentics IDE, configuring the NDK, setting up signing keys, and preparing your first project.

---

## 📋 Overview

BB10 native apps use:
- **QNX Neutrino RTOS** — the microkernel OS running on the hardware
- **Cascades framework** — RIM's Qt-based UI toolkit for BB10
- **BlackBerry Native SDK (NDK)** — the toolchain (compiler, linker, deployer)
- **Momentics IDE** — the Eclipse-based IDE, BB10's equivalent of Xcode/Android Studio

---

## Part 1: Obtaining the NDK and Momentics IDE

### 1.1 Finding the NDK in 2026

BlackBerry's official download servers are offline. The NDK is preserved by the community:

| Resource | URL | Notes |
|----------|-----|-------|
| **CrackBerry Dev Forum** | `forums.crackberry.com/blackberry-10-os-development-f395/` | Has pinned threads with mirror links |
| **Archive.org** | `archive.org/search?query=blackberry+NDK` | Archived installer packages |
| **GitHub (community mirrors)** | Search "blackberry NDK 10.3" | Several community forks |

### 1.2 NDK Versions

| NDK Version | BB10 Target OS | Recommended |
|-------------|---------------|-------------|
| NDK 10.3.1 | BB10 10.3.x | ✅ **Recommended** |
| NDK 10.2.1 | BB10 10.2.x | Legacy |
| NDK 10.0.9 | BB10 10.0.x | Legacy |

Download the **10.3.1 NDK** for maximum device compatibility.

### 1.3 Momentics IDE Installation

Momentics IDE is bundled with the NDK installer:

```
BlackBerry-NDK-10.3.1.XXXX-Windows.exe   (Windows ~1.2 GB)
BlackBerry-NDK-10.3.1.XXXX-Linux.bin     (Linux ~1.1 GB)
BlackBerry-NDK-10.3.1.XXXX-MacOSX.zip   (macOS ~1.1 GB)
```

**Windows Installation:**
```powershell
# Run the installer as Administrator
# Default install path: C:\bbndk\
# The installer sets up:
#   - QCC compiler (GCC-based ARM cross-compiler)
#   - blackberry-deploy tool
#   - blackberry-signer tool
#   - Momentics IDE (Eclipse-based)
```

**Linux Installation:**
```bash
chmod +x BlackBerry-NDK-10.3.1.XXXX-Linux.bin
./BlackBerry-NDK-10.3.1.XXXX-Linux.bin
# Accept license, choose install directory (e.g., ~/bbndk)
# Add to PATH:
echo 'export QNX_HOST=$HOME/bbndk/host/linux/x86' >> ~/.bashrc
echo 'export QNX_TARGET=$HOME/bbndk/target/qnx6' >> ~/.bashrc
echo 'export PATH=$QNX_HOST/usr/bin:$PATH' >> ~/.bashrc
source ~/.bashrc
```

**macOS Installation:**
```bash
unzip BlackBerry-NDK-10.3.1.XXXX-MacOSX.zip -d ~/bbndk
# Set environment variables same as Linux but:
export QNX_HOST=$HOME/bbndk/host/darwin/x86
export QNX_TARGET=$HOME/bbndk/target/qnx6
export PATH=$QNX_HOST/usr/bin:$PATH
```

---

## Part 2: Configuring Momentics IDE

### 2.1 First Launch

1. Launch Momentics IDE from the installation directory.
2. Choose a workspace directory (e.g., `~/bb10-workspace/`).
3. The IDE will show the **BlackBerry Native SDK Welcome** page.

### 2.2 Adding the Target Device

1. In Momentics, open **Window → Preferences → BlackBerry → Devices**.
2. Click **"Add"**.
3. Enter:
   - **Name**: `My BB10 Device` (or device model name)
   - **IP Address**: Device's Developer Mode IP (from Settings)
   - **Password**: Developer Mode password
4. Click **"Connect"** to verify.
5. The device should appear as **"Connected"** in green. ✅

### 2.3 Adding a Simulator (Optional)

The BB10 simulator is a VMware Virtual Machine:

1. Download the BB10 Simulator from the same source as the NDK.
2. Open in VMware Player (free) or VMware Workstation.
3. Start the simulator VM.
4. In Momentics Preferences → Devices, add the simulator's IP (usually `192.168.56.101`).

---

## Part 3: Obtaining and Configuring Code Signing Keys

> ⚠️ **Code signing in 2026:** BlackBerry's CSJ (Code Signing Key) server is offline. However, the community has developed workarounds for local/developer signing.

### 3.1 Background: What Are Signing Keys?

BB10 requires all `.bar` packages to be digitally signed before installation. Two levels of signing exist:

| Level | Purpose | Required for |
|-------|---------|-------------|
| **Debug signing** | Development/testing | Installing on your own device in Dev Mode |
| **Release signing** | Public distribution | Publishing to BlackBerry World (obsolete) |

For modern development, **debug signing** is sufficient.

### 3.2 Generating Debug Token

```bash
# On your development machine, after NDK is in PATH:

# Step 1: Generate a PKCS12 key file
blackberry-keytool -genkeypair \
  -keystore ~/bb10-signing/developer.p12 \
  -storepass your_password \
  -keypass your_password \
  -alias developer \
  -dname "CN=Developer, O=Personal, C=US" \
  -validity 3650

# Step 2: Create a debug token (requires device PIN)
# Get your device PIN from Settings → About → Hardware
blackberry-debugtokenrequest \
  -keystore ~/bb10-signing/developer.p12 \
  -storepass your_password \
  -devicepin YOUR_DEVICE_PIN \
  debugtoken.bar

# Step 3: Deploy debug token to device
blackberry-deploy \
  -installDebugToken debugtoken.bar \
  -device DEVICE_IP \
  -password DEVICE_DEV_PASSWORD
```

### 3.3 Configure Momentics for Signing

1. Open **Window → Preferences → BlackBerry → Signing**.
2. For **"Author Certificate"**, browse to your `.p12` file.
3. Enter the keystore password.
4. Check **"Use debug token"** for development builds.

---

## Part 4: Creating Your First Project

### 4.1 New Project Wizard

1. In Momentics: **File → New → BlackBerry Project**.
2. Select **"Cascades Application"**.
3. Enter project name (e.g., `HelloBlackBerry`).
4. Select template: **"Standard Empty Project"** or **"Hello World"**.
5. Click **Finish**.

### 4.2 Project Structure

```
HelloBlackBerry/
├── bar-descriptor.xml         ← App metadata, permissions, assets
├── HelloBlackBerry.pro        ← Qt project file (qmake)
├── src/
│   ├── main.cpp               ← Application entry point
│   └── applicationui.cpp      ← Main application class
├── assets/
│   └── main.qml               ← UI definition (QML)
├── translations/
│   └── HelloBlackBerry.ts     ← Localization strings
└── config.pri                 ← Build configuration
```

### 4.3 Building the Project

```bash
# Command-line build (alternative to Momentics GUI):
cd HelloBlackBerry
qcc -Vgcc_ntoarmv7le_cpp -o hello src/main.cpp \
  -I$QNX_TARGET/usr/include/qt4/QtCore \
  -L$QNX_TARGET/armle-v7/usr/lib \
  -lbb -lbbcascades

# Or use the bb-ant-tools for a full .bar build:
ant build
```

---

## Part 5: Environment Verification

Run this checklist to confirm your environment is working:

```bash
# Verify QCC compiler is accessible
qcc --version
# Expected output: QCC 10.3.1.xxxx

# Verify NDK target is set
echo $QNX_TARGET
# Expected: /path/to/bbndk/target/qnx6

# Verify device connection
blackberry-deploy -listInstalledApps -device YOUR_IP -password YOUR_PASS
# Should return list of installed packages

# Compile a simple test
echo '#include <stdio.h>
int main() { printf("Hello QNX\n"); return 0; }' > /tmp/test.c
qcc -Vgcc_ntoarmv7le -o /tmp/test_qnx /tmp/test.c
echo "Compilation: $?"
# Expected: Compilation: 0
```

---

## Part 6: Key SDK Components Reference

| Component | Location | Purpose |
|-----------|----------|---------|
| `qcc` | `$QNX_HOST/usr/bin/qcc` | C/C++ cross-compiler |
| `blackberry-deploy` | `$QNX_HOST/usr/bin/blackberry-deploy` | Deploy/install `.bar` files |
| `blackberry-signer` | `$QNX_HOST/usr/bin/blackberry-signer` | Code-sign packages |
| `blackberry-debugtokenrequest` | `$QNX_HOST/usr/bin/` | Generate debug tokens |
| `blackberry-nativepackager` | `$QNX_HOST/usr/bin/` | Create `.bar` packages |
| QML headers | `$QNX_TARGET/usr/include/bb/cascades/` | Cascades UI framework |
| Qt headers | `$QNX_TARGET/usr/include/qt4/` | Qt 4.8 framework |

---

## Troubleshooting

| Problem | Solution |
|---------|----------|
| `qcc: not found` | Add NDK host to PATH; source `.bashrc` |
| Momentics won't connect to device | Verify Developer Mode is on; check firewall |
| "Signing failed: server unreachable" | Use local debug signing (Step 3.2) |
| Build fails: "No such file bbcascades" | Ensure `QNX_TARGET` points to the correct NDK target |
| IDE very slow on modern hardware | Momentics is Eclipse-based; allocate 4+ GB heap in `eclipse.ini` |
| macOS Gatekeeper blocks IDE | Run `xattr -r -d com.apple.quarantine /path/to/Momentics.app` |

---

*Next: [See a complete Hello World example →](Hello_BlackBerry_Native.cpp)*
