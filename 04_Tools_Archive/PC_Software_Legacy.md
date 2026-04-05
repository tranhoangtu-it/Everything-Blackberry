<!--
  Title: Running BlackBerry Link and BlackBerry Blend on Windows 10/11
  Author: Everything-BlackBerry Contributors
  Last Verified: 2026-04-01
  Tested: Windows 10 22H2, Windows 11 23H2
-->

# PC Software Legacy — BlackBerry Link & BlackBerry Blend on Windows 10/11

> BlackBerry's official PC software — **BlackBerry Link** and **BlackBerry Blend** — were designed for Windows 7/8 and were discontinued in 2019. However, with the right compatibility settings and driver fixes, both applications run successfully on Windows 10 and Windows 11 in 2026.

---

## BlackBerry Link vs. BlackBerry Blend

| Feature | BlackBerry Link | BlackBerry Blend |
|---------|----------------|-----------------|
| **Primary use** | Device backup, OS management, media sync | Access device content from PC (messages, files, Hub) |
| **Connection** | USB only | USB or Wi-Fi |
| **Real-time sync** | No (manual sync) | Yes (live access to messages) |
| **File transfer** | Full device media management | Drive-style file access |
| **Autoloader support** | USB driver install | None |
| **Windows 10/11 compat** | ✅ Works with fixes | ✅ Works with fixes |
| **Last official version** | 1.2.3 | 1.2.2 |

---

## Part 1: BlackBerry Link on Windows 10/11

### 1.1 Installation

1. Download BlackBerry Link 1.2.3 from the community mirror (CrackBerry forums or Archive.org — search "BlackBerry Link 1.2.3 installer").

2. **Before installing**: Right-click the installer → **Properties** → **Compatibility** tab:
   - Check "Run this program in compatibility mode for:"
   - Select **"Windows 8"**
   - Check "Run as administrator"
   - Click **Apply**

3. Run the installer:
   ```
   BlackBerryLink_1.2.3.60.exe
   ```

4. During installation, if Windows shows "Windows protected your PC" (SmartScreen):
   - Click **"More info"**
   - Click **"Run anyway"**

5. The installer will:
   - Install BlackBerry Link
   - Install BlackBerry USB drivers (RIM BlackBerry device driver)
   - Add BlackBerry Link to startup

### 1.2 Driver Fix for Windows 10/11

BB Link installs legacy USB drivers that sometimes fail on modern Windows. If your device is not recognized:

**Method A — Device Manager Fix:**

```
1. Connect BB10 device via USB
2. Open Device Manager (Win+X → Device Manager)
3. Look for "Unknown Device" or "BlackBerry Device" with a yellow warning icon
4. Right-click → "Update driver"
5. "Browse my computer for drivers"
6. "Let me pick from a list of available drivers"
7. Select "Universal Serial Bus devices" → look for "RIM BlackBerry" entry
8. If not found, browse to: C:\Program Files (x86)\Common Files\Research In Motion\USB Drivers\
```

**Method B — Manual Driver Install (PowerShell as Admin):**

```powershell
# Install the BlackBerry USB driver manually
# First, find the driver INF file
$driverPath = "C:\Program Files (x86)\Common Files\Research In Motion\USB Drivers"

# Enumerate INF files in the driver directory
Get-ChildItem "$driverPath\*.inf" | ForEach-Object {
    Write-Host "Found: $($_.Name)"
}

# Install the driver (replace filename with the actual .inf found)
pnputil /add-driver "$driverPath\RimUsb_Win32.inf" /install
```

**Method C — Zadig USB Driver Override (advanced users):**

```
1. Download Zadig from https://zadig.akeo.ie/
2. Connect BB10 device in USB mass storage mode
3. In Zadig, select "BlackBerry Device" from the dropdown
4. Select "WinUSB" as the replacement driver
5. Click "Replace Driver"
Note: This replaces the RIM driver with WinUSB which BB Link may not like.
      Only use this as a last resort.
```

### 1.3 Using BlackBerry Link

**Device Backup:**

```
1. Connect device via USB
2. BlackBerry Link should auto-detect the device (may take 30-60 seconds)
3. Click "Back Up" in the left panel
4. Choose backup location (default: Documents\BlackBerry\Backup\)
5. Click "Back Up Now"
6. Backup includes: contacts, calendar, messages, settings, app data
   (Does NOT include media files — back those up manually)
```

**Restoring from Backup:**

```
1. After running an autoloader (fresh OS), bypass setup screen
2. Connect device to PC — BB Link detects it as a new device
3. Click "Restore"
4. Browse to your backup file (.bbb extension)
5. Select which data to restore
6. Click "Restore"
```

**Media Sync:**

```
1. In BB Link, click on your device name
2. Click "Music" or "Photos"
3. Choose sync direction (Device → PC or PC → Device)
4. Select folders to sync
```

### 1.4 Known Issues with BB Link on Windows 10/11

| Issue | Fix |
|-------|-----|
| BB Link doesn't start | Run as Administrator; check compatibility mode is set to Windows 8 |
| Device not detected | Reinstall USB drivers (Method A above); try different USB ports |
| "Service unavailable" error | BB's online services are dead — this is expected. Backup/restore still works locally. |
| BB Link crashes on open | Delete `%AppData%\BlackBerry\BlackBerryLink\` folder and restart |
| Sync fails mid-way | Disable Windows Defender real-time protection during sync; re-enable after |
| High CPU usage | This is a known BB Link bug; minimize the window — it uses less CPU minimized |

---

## Part 2: BlackBerry Blend on Windows 10/11

### 2.1 What BlackBerry Blend Does

BlackBerry Blend is a **remote access layer** for your BB10 device. When running:

- Your PC gets a virtual drive letter (e.g., `F:\`) mapped to your device's storage
- You can read and reply to **BB10 Hub messages** from your PC's keyboard
- **Files** on the device are directly accessible as if on a local drive
- Works over **Wi-Fi** or **USB** (Wi-Fi is more convenient)

### 2.2 Installation

1. Download BlackBerry Blend 1.2.2 from the community mirror.

2. Same compatibility settings as Link:
   - Right-click installer → Properties → Compatibility → Windows 8 → Run as administrator

3. Run `BlackBerryBlend_1.2.2.exe`

4. After installation, Blend icon appears in system tray.

### 2.3 Setting Up Wi-Fi Blend Connection

On your BB10 device:

```
1. Settings → Device Connections → BlackBerry Blend
2. Toggle "Allow BlackBerry Blend" to ON
3. Ensure device and PC are on the same Wi-Fi network
4. Note the device IP from Settings → About → Network
```

On your PC:

```
1. Open BlackBerry Blend
2. Click "Pair a device"
3. Blend will scan the local network for BB10 devices
4. Your device should appear — click it
5. A PIN confirmation appears on both device and PC
6. Confirm the PIN matches and tap "Trust" on the device
```

### 2.4 Using BlackBerry Blend

**Accessing the Hub:**

```
In Blend, click the "Hub" icon in the left sidebar.
Your messages appear in a list identical to the BB10 Hub.
Reply to messages using your PC keyboard — responses are 
sent by your BB10 phone, not from your PC.
```

**File Access (virtual drive):**

```
After connecting, a new drive letter appears in Windows Explorer.
This maps to your device's /shared/documents/ folder.
You can copy files to/from the device like any USB drive.
```

### 2.5 Known Issues with BB Blend on Windows 10/11

| Issue | Fix |
|-------|-----|
| Blend can't find device on Wi-Fi | Ensure both are on the same subnet; disable Wi-Fi AP isolation on router |
| Blend shows "Authenticating..." forever | Delete `%AppData%\BlackBerry\BlackBerryBlend\` and re-pair |
| Virtual drive not appearing | Try USB connection instead of Wi-Fi |
| Hub says "Service unavailable" | Expected — BBM/social integrations are dead. Email still works. |
| Blend crashes on Windows 11 | Use compatibility mode Windows 7 (not 8) for Blend specifically |

---

## Part 3: BlackBerry Desktop Software (Legacy BB7 and Earlier)

For BlackBerry 7 and earlier devices (Bold 9900, Curve 9360, etc.), the PC companion software is **BlackBerry Desktop Software** (version 7.1).

### Key Differences

| Feature | BB Link (BB10) | BB Desktop Software (BB7) |
|---------|----------------|--------------------------|
| OS compatibility | BB10 only | BB5, BB6, BB7 |
| Windows 11 support | ✅ With fixes | ⚠️ Requires more workarounds |
| Media sync | ✅ | ✅ |
| App management | ✅ | ✅ |
| Backup format | `.bbb` (encrypted) | `.ipd` (standard) |

### Installing BB Desktop Software on Windows 10/11

```
1. Download BlackBerry Desktop Software 7.1.x from Archive.org
   (search "BlackBerry Desktop Software 7.1")

2. Right-click installer → Properties → Compatibility:
   - Windows Vista (Service Pack 2)
   - Run as administrator
   - Override high DPI scaling (set to "Application")

3. Run installer as Administrator

4. For driver issues on Windows 11:
   a) Open Device Manager after connecting device
   b) Right-click the unrecognized device
   c) Browse manually to: C:\Program Files (x86)\Common Files\Research In Motion\Shared\Loader\
   d) Install the RIM Composite Device driver
```

---

## Part 4: Running BB Software on Linux/macOS

### Linux (via Wine)

```bash
# Install Wine on Ubuntu/Debian:
sudo apt install wine winetricks

# Install required Windows libraries:
winetricks vcrun2010 vcrun2013 dotnet45

# Run BlackBerry Link:
wine BlackBerryLink_1.2.3.exe

# Note: USB passthrough in Wine requires additional setup:
# https://wiki.winehq.org/USB_Device_Sharing
```

> ⚠️ Linux support via Wine is community-maintained and may be unstable. A Windows VM (VirtualBox/VMware with USB passthrough) is more reliable.

### macOS

BlackBerry Link for Mac was version **1.2.3** and ran on macOS up to Mojave (10.14). It does **not** run on macOS Catalina or later due to the removal of 32-bit app support.

**Workaround for macOS:**
- Use a Windows VM in Parallels Desktop or VirtualBox with USB passthrough
- Install BlackBerry Link in the Windows VM

---

*Back to: [Autoloader Directory →](Autoloader_Directory.md)*
