<!--
  Title: Android Runtime Optimization — Making APKs Work Better on BB10
  Author: Everything-BlackBerry Contributors
  Last Verified: 2026-04-01
  Devices Tested: BlackBerry Classic Q20, Passport SQW100-1, Z10, Z30
-->

# Android Runtime Optimization

> The BlackBerry 10 Android Runtime (known internally as "Player") allows BB10 to run Android APKs. It is based on Android 4.3 (Jelly Bean, API level 18). This guide covers technical tips to maximize APK compatibility and performance.

---

## Understanding the BB10 Android Runtime

### Architecture Overview

```
┌─────────────────────────────────────────────────────────┐
│                  BB10 / QNX Kernel                      │
├─────────────────────────────────────────────────────────┤
│              QNX Process Manager                        │
├──────────────────┬──────────────────────────────────────┤
│  Native (QNX)    │     Android Runtime (Player)         │
│  Cascades Apps   │  ┌─────────────────────────────────┐ │
│                  │  │  Dalvik VM (Android 4.3 based)  │ │
│                  │  │  Android Framework Libraries    │ │
│                  │  │  (no Google Play Services)      │ │
│                  │  │  Your APK runs here             │ │
│                  │  └─────────────────────────────────┘ │
└──────────────────┴──────────────────────────────────────┘
```

### Key Technical Characteristics

| Property | Value |
|----------|-------|
| Android API Level | 18 (Android 4.3 Jelly Bean) |
| Dalvik VM version | 1.6.0 |
| ABI | `armeabi-v7a` only |
| OpenGL ES | 2.0 |
| Google Play Services | ❌ Not available |
| Hardware acceleration | ✅ Partial |
| Multi-window | ❌ One Android app at a time |

---

## Tip 1: Selecting the Right APK Version

The single most important optimization is choosing the correct APK version.

### Version Selection Strategy

```
Target API Level Guide:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
API 16 (Android 4.1) ████████████████ Best compatibility
API 17 (Android 4.2) ███████████████  Excellent
API 18 (Android 4.3) ██████████████   Good (max native)
API 19 (Android 4.4) ██████████       Works often
API 20 (Android 4.4W)████████         Hit or miss
API 21 (Android 5.0) ████             Often fails
API 22 (Android 5.1) ███              Usually fails
API 23+ (Android 6+) █                Very likely fails
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### How to Check an APK's Target API

```bash
# Using Android SDK tools (on your PC):
aapt dump badging your_app.apk | grep "targetSdkVersion"

# Or using Python + apkutils:
pip install apkutils
python3 -c "
import apkutils
apk = apkutils.APK('your_app.apk')
print('Min SDK:', apk.get_min_sdk_version())
print('Target SDK:', apk.get_target_sdk_version())
"
```

---

## Tip 2: Removing Google Play Services Dependencies

Many modern Android apps fail on BB10 because they depend on **Google Play Services** (`com.google.android.gms`), which is not available on BB10.

### Identifying the Dependency

```bash
# Check if the APK references Google Play Services:
aapt dump xmltree your_app.apk AndroidManifest.xml | grep -i "google"

# Or decompile and search with apktool:
apktool d your_app.apk -o app_decompiled/
grep -r "com.google.android.gms" app_decompiled/
```

### Apps That Typically Work Without GMS

```
✅ Apps using:
   - Standard Android APIs only
   - OkHttp / Retrofit for networking
   - Firebase (old SDK < 9.x with fallback logic)
   - Custom push notification servers

❌ Apps that will fail due to GMS:
   - Apps using Google Maps SDK
   - Apps requiring Google Sign-In
   - Apps using Firebase Cloud Messaging (FCM)
   - Apps using SafetyNet / Play Integrity
   - Apps using in-app billing (Google Play Billing)
```

---

## Tip 3: Repacking APKs for Better BB10 Compatibility

For APKs that target API 19-22, you can repack them to declare a lower target SDK:

### Using apktool + dx (Advanced)

```bash
# Step 1: Decompile the APK
apktool d target_app.apk -o target_app_decompiled/

# Step 2: Edit AndroidManifest.xml — lower the targetSdkVersion
# Find: android:targetSdkVersion="21"
# Change to: android:targetSdkVersion="18"
nano target_app_decompiled/AndroidManifest.xml

# Step 3: Recompile
apktool b target_app_decompiled/ -o target_app_repacked.apk

# Step 4: Sign the repacked APK (required)
jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 \
  -keystore ~/.android/debug.keystore target_app_repacked.apk androiddebugkey

# Step 5: Zipalign (optimize)
zipalign -v 4 target_app_repacked.apk target_app_final.apk

# Step 6: Convert to .bar and sideload
# (use Sachesi to wrap the APK in a .bar container)
```

> ⚠️ Only repack APKs for personal use. Redistributing repacked APKs may violate the app's terms of service.

---

## Tip 4: Android Runtime Performance Tuning

### BB10 Developer Settings for Android Player

On your BB10 device, additional Android runtime settings can be accessed in Developer Mode:

1. Enable Developer Mode (Settings → Security → Development Mode).
2. Open the **Android App Settings** (visible in Developer settings on some OS versions).
3. Adjust JVM heap size if available.

### Memory Allocation

The Android Runtime allocates memory from the QNX system. If your Android app is memory-intensive:

```
Default Dalvik heap: 48 MB
Extended (if available): 256 MB

For memory-intensive apps (games):
- Close all other running apps first
- The BB10 Runtime reclaims memory aggressively
- Avoid apps that request > 128 MB heap
```

### CPU Performance

The Android Runtime runs on the same CPU as native apps. Performance tips:

| Technique | Effect |
|-----------|--------|
| Choose APKs with `armeabi-v7a` native libs | Best performance; avoids x86 translation |
| Avoid apps with heavy background services | They compete with BB10's native processes |
| Use OpenGL ES 2.0 apps | Supported natively; ES 3.0+ is not |
| Disable animations in Android app settings | Reduces GPU load on lower-end devices |

---

## Tip 5: Enabling Hardware Acceleration for Android Apps

Some Android apps render faster with hardware-accelerated drawing. This is controlled in the APK's manifest:

```xml
<!-- In AndroidManifest.xml of the app (after decompiling with apktool) -->
<application
    android:hardwareAccelerated="true"   <!-- Enable for the whole app -->
    ...>

    <activity
        android:name=".MainActivity"
        android:hardwareAccelerated="true"  <!-- Or per-activity -->
        ...>
```

BB10's Android Runtime supports hardware acceleration for most 2D drawing operations.

---

## Tip 6: Converting APK to `.bar` Format

When you convert an APK to `.bar` for BB10, you can include optimization metadata:

### Using Sachesi (GUI method)

Sachesi's APK converter creates a properly structured `.bar` file with sensible defaults. See [Sideloading_Masterclass.md](../01_Survival_Guide/Sideloading_Masterclass.md).

### Manual Conversion (Advanced)

```bash
# The BB10 .bar format is a ZIP archive with a specific structure
# For Android APKs, it wraps the APK with BB10 metadata

mkdir -p myapp_bar/android
cp your_app.apk myapp_bar/android/your_app.apk

# Create the BB10 descriptor file
cat > myapp_bar/MANIFEST.MF << 'EOF'
Manifest-Version: 1.0
Package-Author: Developer
Package-Author-Certificate-Hash: 0
Package-Id: com.example.myapp
Package-Version: 1.0.0.1
Package-Type: application
Application-Type: AIR
EOF

# Package as .bar
cd myapp_bar
zip -r ../your_app.bar .
cd ..

# Install via blackberry-deploy
blackberry-deploy -installApp -device DEVICE_IP \
  -password DEV_PASSWORD your_app.bar
```

---

## Tip 7: Debugging Android Apps on BB10

```bash
# Connect ADB over TCP (Android Debug Bridge)
# First ensure Developer Mode is ON
adb connect DEVICE_IP:5555

# Check connection
adb devices
# Output: DEVICE_IP:5555  device

# View Android logcat output for debugging
adb logcat | grep "com.example.myapp"

# Get crash logs
adb logcat -b crash

# Check Android Runtime version
adb shell getprop ro.build.version.sdk
# Expected: 18
```

---

## Quick Reference: APK Compatibility Checklist

Before sideloading an Android APK, verify:

- [ ] Target SDK ≤ 22 (ideally ≤ 18)
- [ ] Does NOT require Google Play Services
- [ ] Uses `armeabi-v7a` ABI (or pure Java/Dalvik)
- [ ] Does NOT use `android.hardware.nfc` (BB10 has limited NFC support)
- [ ] Does NOT require API 21+ features (ART runtime, Material Design transitions)
- [ ] For camera apps: BB10 Android camera API support is limited
- [ ] For Bluetooth apps: BB10 BT stack is separate; Android BT API may not work

---

## Known Compatible Android App Categories

| Category | Compatibility | Notes |
|----------|--------------|-------|
| Text editors / note apps | ✅ Excellent | No special hardware needed |
| Music players (offline) | ✅ Excellent | Use native BB10 player instead if possible |
| Ebook readers | ✅ Good | Avoid DRM-heavy versions |
| Podcast clients | ✅ Good | RSS-based apps work well |
| Turn-by-turn navigation | ✅ Good | HERE WeGo, OsmAnd work |
| Messengers (no GMS push) | ⚠️ Partial | Background notifications unreliable |
| Games (2D/casual) | ✅ Good | 3D/heavy games vary widely |
| Banking apps | ❌ Usually fails | SafetyNet/Play Integrity required |
| Streaming video | ❌ Usually fails | DRM (Widevine) not supported |

---

*Back to Development Suite overview: [Cascades Qt Setup →](Cascades_Qt_Setup.md)*
