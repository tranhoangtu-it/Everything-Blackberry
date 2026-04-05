<!--
  Title: Sideloading Masterclass — Installing .bar and .apk on BB10
  Author: Everything-BlackBerry Contributors
  Last Verified: 2026-04-01
  Devices Tested: BlackBerry Classic Q20, Passport SQW100-1, Z10, Z30
-->

# Sideloading Masterclass

> **What is sideloading?** Since BlackBerry World (the official app store) closed permanently in 2019, sideloading — installing apps from sources outside the official store — is the **only** way to install new applications on BB10 devices. This guide covers every method in detail.

---

## 📋 Prerequisites

- BB10 device with setup bypass completed ([Bypassing_Setup_Screen.md](Bypassing_Setup_Screen.md))
- Developer Mode enabled on the device (instructions below)
- A Windows, macOS, or Linux computer
- USB cable or Wi-Fi connection

---

## Part 1: Understanding the Two App Formats

BB10 supports two completely different app formats. Understanding this distinction is critical.

### Native `.bar` Files — QNX/Cascades Apps

| Property | Detail |
|----------|--------|
| **Platform** | QNX / BlackBerry Native Platform |
| **Framework** | Cascades (Qt-based) or Adobe AIR |
| **Performance** | Excellent — runs at full native speed |
| **Integration** | Full access to BB10 APIs (Hub, Active Frames, etc.) |
| **File extension** | `.bar` |
| **Example** | BlackBerry Maps, official BB10 Twitter app |

### Android `.apk` Files — Android Runtime (Player)

| Property | Detail |
|----------|--------|
| **Platform** | BB10 Android Runtime (based on Android 4.3 Jelly Bean) |
| **Framework** | Standard Android |
| **Performance** | Good, but with ~15-20% overhead vs native Android |
| **Integration** | Limited — no access to BB10 Hub, Active Frames |
| **File extension** | `.apk` (repackaged as `.bar` for some tools) |
| **Compatibility** | Apps targeting Android API ≤ 18 work best |
| **Example** | Bgram (Telegram client), WhatsApp (older versions) |

> 💡 **Rule of thumb:** Always prefer a native `.bar` app over an Android `.apk` when both exist. Native apps are faster, use less battery, and integrate with BB10 properly.

---

## Part 2: Enabling Developer Mode

Developer Mode allows installing unsigned apps and connecting debugging tools.

### Steps

1. On your BB10 device, go to **Settings** (swipe down from top, tap gear icon).
2. Navigate to **Security and Privacy → Development Mode**.
3. Toggle **"Use Development Mode"** to **ON**.
4. Set a **Password** for the development connection (remember this — you'll need it for Sachesi).
5. The device will display its **IP address** — note it down.

> ⚠️ **Security Note:** Developer Mode opens port 22 (SSH) and a debugging port on your device. Only enable it when actively sideloading, and use it on trusted networks.

---

## Part 3: Method A — Sachesi (Recommended GUI Tool)

**Sachesi** is an open-source cross-platform tool specifically designed for BlackBerry 10. It can extract, install, and manage `.bar` packages, and also download official firmware.

### 3.1 Installing Sachesi

1. Download Sachesi from the GitHub releases page:
   - **Windows**: `Sachesi-2.x.x-win.exe`
   - **macOS**: `Sachesi-2.x.x-mac.dmg`
   - **Linux**: `Sachesi-2.x.x-linux.AppImage`
   - GitHub: `https://github.com/kyleferguson/Sachesi`

2. Install and launch Sachesi.

### 3.2 Connecting to Your Device

1. In Sachesi, click the **"Install"** tab.
2. Enter your device's IP address in the **IP** field.
3. Enter the developer mode password you set earlier.
4. Click **Connect**. A green indicator confirms the connection.

### 3.3 Installing a `.bar` File

1. Drag and drop a `.bar` file onto the Sachesi window, OR click **"Browse"** and select the file.
2. Click **"Install"**.
3. Sachesi will upload and install the package. A progress bar shows the status.
4. The app will appear in your BB10 app list. ✅

### 3.4 Installing an Android `.apk` File

Android APKs must first be converted to `.bar` format for BB10:

**Option A — Using Sachesi's built-in converter:**
1. In Sachesi, go to **"Apps"** → **"Convert APK"**.
2. Browse to your `.apk` file and click **Convert**.
3. Sachesi wraps the APK in a BB10-compatible `.bar` container.
4. Install the resulting `.bar` file as above.

**Option B — Pre-converted APKs:**
Many Android apps are already available as pre-converted `.bar` files in the community. Check [Working_Apps_Directory.md](Working_Apps_Directory.md) for links.

---

## Part 4: Method B — DBBT (Drag & Drop BB Tool)

**DBBT** (Drag and Drop BB Tool) is a simpler, browser-based approach that requires no dedicated desktop app.

### 4.1 Prerequisites

- Python 3.x installed on your computer
- `bbdeploy` command-line tool (part of BlackBerry Native SDK / NDK)

### 4.2 Command-Line Installation

```bash
# Install a .bar file via command line
# Replace IP, PASSWORD, and FILENAME with your values

# For native .bar files:
blackberry-deploy -installApp -device <DEVICE_IP> -password <DEV_MODE_PASSWORD> <APP_FILE.bar>

# Example:
blackberry-deploy -installApp -device 169.254.0.1 -password mypass123 bgram.bar

# To list installed apps:
blackberry-deploy -listInstalledApps -device 169.254.0.1 -password mypass123

# To uninstall an app:
blackberry-deploy -uninstallApp -device 169.254.0.1 -password mypass123 -package-id com.example.myapp
```

> 📦 `blackberry-deploy` is part of the **BlackBerry Native SDK**. See [Cascades_Qt_Setup.md](../02_Development_Suite/Cascades_Qt_Setup.md) for installation instructions.

---

## Part 5: Method C — Chrome Extension (Unofficial, Legacy)

> ⚠️ This method is **legacy** and only works with older Chrome versions (< v88). Provided for historical reference only.

The unofficial "BB10 Sideloader" Chrome extension allowed drag-and-drop `.bar` installation directly from the browser.

1. The extension connected to the device's developer mode web server.
2. Users dragged `.bar` files onto the extension popup.
3. As Chrome deprecated its extension architecture (MV2), this stopped working.

**Modern replacement:** Use Sachesi (Method A) instead.

---

## Part 6: Installing Apps Over Wi-Fi (No USB)

Sachesi and `blackberry-deploy` both support Wi-Fi installation, which is more convenient than USB.

### Requirements
- Device and computer on the same Wi-Fi network
- Developer Mode enabled with IP noted

### Wi-Fi vs USB Comparison

| Feature | Wi-Fi | USB |
|---------|-------|-----|
| Speed | Slower (~2 MB/s) | Faster (~10 MB/s) |
| Convenience | High (wireless) | Low (requires cable) |
| Reliability | Good on stable network | Very reliable |
| Recommended for | Small apps < 50 MB | Large games/apps |

---

## Part 7: Finding `.bar` and `.apk` Files

> ⚠️ Only install apps from sources you trust. Verify checksums when possible.

### Recommended Sources

| Source | Type | URL |
|--------|------|-----|
| **CrackBerry Forums** | `.bar` and APK | `forums.crackberry.com` |
| **Snap** (BB10 alternative store) | `.bar` | Available via sideload |
| **APKMirror** | `.apk` (raw) | `apkmirror.com` |
| **Telegram groups** | `.bar` packs | See [Resources_&_Links.md](../05_Community_%26_History/Resources_&_Links.md) |

### Version Compatibility for Android APKs

The BB10 Android Runtime targets **Android 4.3 (API level 18)**. When selecting APK versions:

```
✅ Works well:    APK targeting API ≤ 18 (Android 4.3 or older)
⚠️ May work:     APK targeting API 19-22 (Android 4.4 – 5.1)
❌ Usually fails: APK targeting API ≥ 23 (Android 6.0+)
```

---

## Troubleshooting

| Problem | Solution |
|---------|----------|
| "Connection refused" in Sachesi | Verify Developer Mode is ON; check IP address; try USB instead of Wi-Fi |
| App installs but won't launch | App may require a higher Android API version; try an older APK version |
| "Bad signature" error | The `.bar` may need to be re-signed; use `blackberry-signer` tool |
| App crashes on launch | Check if the app uses Google Play Services (incompatible with BB10) |
| `.bar` file says "Incompatible" | Ensure the `.bar` is for BB10, not for BB7 or BB Playbook |
| Sachesi can't find device | Ensure device and PC are on the same network; check firewall rules |

---

*Next: [See which apps still work in 2026 →](Working_Apps_Directory.md)*
