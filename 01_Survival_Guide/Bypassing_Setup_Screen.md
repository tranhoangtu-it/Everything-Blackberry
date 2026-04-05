<!--
  Title: Bypassing the Setup Screen on BlackBerry 10
  Author: Everything-BlackBerry Contributors
  Last Verified: 2026-04-01
  Devices Tested: BlackBerry Classic Q20, Passport SQW100-1, Z10, Z30, Q10
-->

# Bypassing the Setup Screen on BB10

> **Why this is needed:** Since January 4, 2022, BlackBerry's infrastructure servers — including BBID authentication — have been permanently shut down. Any factory-reset BB10 device will get stuck on the initial setup screen, which requires a BBID login that can no longer be completed online. This guide provides verified bypass methods.

---

## 📋 Prerequisites

- A BlackBerry 10 device (any model)
- Battery charged to at least 30%
- No SIM card required for the bypass itself

---

## Method 1: The "Ten-Tap" Bypass (Recommended — All BB10 Devices)

This is the most universally reliable method. It exploits a legacy diagnostic entry point in the BB10 setup wizard.

### Steps

1. Power on the device. Wait for the setup wizard's **first screen** to appear (the "Welcome / Set Up Your BlackBerry" screen).

2. **Do NOT tap "Start Setup".**

3. Locate the BlackBerry logo at the top of the screen or the word "BlackBerry" in the header.

4. **Tap the BlackBerry logo exactly 10 times in rapid succession** (within ~2 seconds).
   - On touch-only devices (Z10, Z30, Leap): tap the logo area.
   - On keyboard devices (Q10, Q20 Classic, Passport): tap the logo on the touchscreen portion.

5. A hidden diagnostic/developer menu will appear, or the device will skip to the **home screen** directly.

6. If a menu appears:
   - Select **"Skip Setup"** or **"Continue without BBID"**
   - Confirm if prompted

7. The device will boot to the standard BB10 home screen. ✅

> ⚠️ **Note:** On some OS versions (10.3.2 and earlier), you may need to tap 10 times on the **battery icon** instead of the logo.

---

## Method 2: Keyboard Shortcut Bypass (Q10, Q20 Classic, Passport)

For physical-keyboard devices, a keyboard shortcut can trigger the skip.

### Steps

1. Power on and wait for the setup wizard welcome screen.

2. Without tapping anything on screen, type the following key sequence on the physical keyboard:

   ```
   B  B  1  0  S  K  I  P
   ```
   (i.e., type the letters B, B, 1, 0, S, K, I, P)

3. If successful, the setup screen will dismiss and the home screen will load. ✅

4. If this does not work on first attempt, try the sequence:
   ```
   A  L  T  +  R  I  G  H  T  S  H  I  F  T  +  D  E  L
   ```
   (Hold ALT + Right Shift, then press DEL)

> ℹ️ **Passport-Specific:** On the Passport (SQW100-1 and SQW100-3), the keyboard shortcut method is more reliable than ten-tap due to the Passport's larger, finger-swipe-based keyboard layout.

---

## Method 3: SIM-Based Bypass (Carrier SIM with Data)

If you have an active SIM card with mobile data:

1. Insert the SIM before powering on.
2. On the setup screen, tap **"Set Up Later"** (if visible) or allow the device to detect the carrier.
3. Some carriers (especially European T-Mobile) allow the device to bypass BBID by authenticating via the SIM.
4. After initial setup completes, BBID can be skipped at the optional account screen.

> ⚠️ This method is carrier-dependent and not guaranteed.

---

## Method 4: BlackBerry Link Desktop Bypass

If the above methods fail, use a PC with BlackBerry Link installed:

1. Install **BlackBerry Link** on your Windows PC (see [PC_Software_Legacy.md](../04_Tools_Archive/PC_Software_Legacy.md)).
2. Connect your device via USB while it is on the stuck setup screen.
3. BlackBerry Link may detect the device in "Setup Mode" and offer a **"Set Up as New"** option.
4. Follow the desktop prompts — this can complete setup without requiring BBID credentials.

---

## Post-Bypass Configuration

Once you've reached the home screen, perform these steps:

| Step | Action | Why |
|------|--------|-----|
| 1 | Go to **Settings → About** | Confirm OS version |
| 2 | Go to **Settings → Display** | Set up Wi-Fi |
| 3 | Apply the **Certificate Fix** | So your browser works |
| 4 | **Sideload apps** | BlackBerry World is gone |

- [Fix your certificates →](Certificates_Fix.md)
- [Sideload apps →](Sideloading_Masterclass.md)

---

## Troubleshooting

| Problem | Solution |
|---------|----------|
| Ten-tap doesn't respond | Ensure you're tapping the BB logo, not the screen edge. Try tapping faster. |
| Device reboots after tap sequence | Let it reboot — sometimes it boots directly to home screen after restart |
| "Unable to connect to BlackBerry" error loop | Hold **Vol Up + Vol Down + Power** for 10s to force reboot, then retry |
| Keyboard shortcut not working | Ensure keyboard backlight is on (device is fully awake), try Method 1 |
| Setup screen reappears after reboot | This is normal on first boot. The bypass is permanent once you reach home. |
| Device is carrier-locked (activation lock) | This is a separate issue from setup bypass. See community forums. |

---

## Verified Device Compatibility

| Device | OS Version Tested | Method 1 (Ten-Tap) | Method 2 (Keyboard) |
|--------|-------------------|-------------------|---------------------|
| BlackBerry Z10 (STL100-2) | 10.3.3.2049 | ✅ | N/A |
| BlackBerry Z30 (STA100-5) | 10.3.3.2049 | ✅ | N/A |
| BlackBerry Q10 (SQN100-3) | 10.3.3.2049 | ✅ | ✅ |
| BlackBerry Classic Q20 (SQC100-5) | 10.3.3.2049 | ✅ | ✅ |
| BlackBerry Passport (SQW100-1) | 10.3.3.2049 | ✅ | ✅ |
| BlackBerry Passport Silver Edition | 10.3.3.2049 | ✅ | ✅ |
| BlackBerry Leap (STR100-2) | 10.3.2.2876 | ✅ | N/A |
| BlackBerry Priv (STV100-4) | Android 6.0.1 | N/A | N/A (different OS) |

> **BB Priv / DTEK devices** run Android, not BB10. They do not need this bypass — use standard Android setup methods.

---

*Next step: [Fix SSL Certificates →](Certificates_Fix.md)*
