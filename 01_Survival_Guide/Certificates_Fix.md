<!--
  Title: Fixing SSL/TLS Certificate Errors on BlackBerry 10
  Author: Everything-BlackBerry Contributors
  Last Verified: 2026-04-01
  Devices Tested: BlackBerry Classic Q20, Passport SQW100-1, Z10, Z30 (BB10 OS 10.3.3)
-->

# Certificates Fix — Restoring Browser Security on BB10

> **The Problem:** The BB10 browser (and many apps that use HTTPS) stopped working properly after September 2021, when Let's Encrypt's old root certificate (`DST Root CA X3`) expired. The new root certificate (`ISRG Root X1`) was not included in BB10's default certificate store. This causes "Connection not secure" or "Cannot connect to site" errors on a large percentage of modern websites.

---

## 📋 Prerequisites

- BB10 device on OS **10.3.x** (all sub-versions affected)
- Wi-Fi connection to the internet (or ability to transfer files)
- The ISRG Root X1 certificate file (download link below)

---

## Understanding the Problem

### Certificate Chain of Trust

Modern websites use **Let's Encrypt** as a Certificate Authority (CA). Let's Encrypt's certificates chain up to **ISRG Root X1** as the root CA. BlackBerry 10's certificate store was last updated in 2017 and does not include this root certificate.

```
Website Certificate (leaf)
       ↓ signed by
Let's Encrypt R3 (intermediate CA)
       ↓ signed by
ISRG Root X1 (root CA)  ← BB10 doesn't know this root ❌
```

Without ISRG Root X1 in the trust store, BB10 cannot verify the certificate chain, so HTTPS connections fail with an error.

### Impact

Approximately **60% of websites** on the modern internet use Let's Encrypt certificates. This affects:
- The built-in BB10 Browser
- BlackBerry Hub (for web-based email providers)
- Many sideloaded Android apps that use native HTTP libraries

---

## Method 1: Manual Certificate Installation (Recommended)

### Step 1: Download the ISRG Root X1 Certificate

Download the certificate in DER format from Let's Encrypt:

```
https://letsencrypt.org/certs/isrgrootx1.der
```

Save the file as `isrgrootx1.der`.

> 💡 If you can't access that URL from your BB10 browser, download it on a PC and transfer via USB or email attachment.

### Step 2: Transfer to Your Device

**Option A — Email yourself the certificate:**
1. Email `isrgrootx1.der` as an attachment to an email address configured on your BB10 device.
2. Open the email on your BB10 and tap the attachment.

**Option B — USB file transfer:**
1. Connect your BB10 to your PC via USB.
2. On the device, select **"USB Drive"** mode when prompted.
3. Copy `isrgrootx1.der` to the device's **Downloads** folder.
4. Open the **Files** app on your BB10 and navigate to Downloads.
5. Tap `isrgrootx1.der`.

**Option C — Wi-Fi file transfer (Sachesi or FTP):**
1. Use a file manager app or Sachesi to push the file to `/accounts/1000/shared/downloads/`.

### Step 3: Install the Certificate

1. Locate `isrgrootx1.der` in the **Files** app or open it from the email attachment.
2. Tap the file.
3. BB10 will recognize it as a certificate and show an installation prompt:
   - **"Install Certificate"** dialog will appear.
   - Certificate details will show: **"ISRG Root X1"**, **Issued by: ISRG**, **Valid until: 2035-06-04**.
4. Tap **"Trust"** or **"Install"**.
5. The certificate is now in your device's trust store. ✅

### Step 4: Verify the Fix

1. Open the BB10 Browser.
2. Navigate to `https://letsencrypt.org` — it should load without errors.
3. Navigate to `https://community.crackberry.com` — another good test.
4. Tap the padlock icon in the browser URL bar to view certificate details.

---

## Method 2: Install Additional Missing Root Certificates

Beyond ISRG Root X1, other root certificates may be missing. The following are commonly needed in 2026:

### Certificate Bundle

| Certificate | Issued By | Valid Until | File |
|-------------|-----------|-------------|------|
| **ISRG Root X1** | ISRG | 2035-06-04 | `isrgrootx1.der` |
| **ISRG Root X2** | ISRG | 2040-09-17 | `isrgrootx2.der` |
| **GlobalSign Root R6** | GlobalSign | 2034-12-15 | `gsr6.der` |
| **DigiCert Global Root G3** | DigiCert | 2037-01-15 | `dgcert_g3.der` |

Download each from their respective CA's website and install using Method 1 above.

---

## Method 3: Browser Settings Workaround (Partial Fix)

If certificate installation fails, you can configure the browser to use alternative DNS resolvers that may help with some OCSP validation issues:

1. Go to **Settings → Network Connections → Wi-Fi → [Your Network] → Edit**.
2. Under **"DNS"**, set:
   - Primary DNS: `1.1.1.1` (Cloudflare)
   - Secondary DNS: `8.8.8.8` (Google)
3. Tap **Save**.

> ⚠️ This is a partial workaround and does not fix the root certificate trust issue. Use Method 1 for a proper fix.

---

## Method 4: Community Certificate Update Package (.bar)

The BB10 community has compiled a `.bar` file that installs multiple root certificates in one step:

1. Download the community certificate update package from CrackBerry forums (search for "BB10 certificate update 2024").
2. Sideload it using Sachesi ([Sideloading_Masterclass.md](Sideloading_Masterclass.md)).
3. Launch the installed app — it will install all certificates automatically.

> ℹ️ **Verify the source** of this package before installing. Only use packages from trusted community members with verified posts.

---

## Technical Details (For Advanced Users)

### Where BB10 Stores Certificates

BB10 uses an NSS (Network Security Services) certificate database located at:
```
/base/usr/share/trusted-certs/
```
Root certificates are stored as DER-encoded files. The system reads these at runtime.

### Certificate Verification

The BB10 OS uses **OCSP stapling** and **CRL (Certificate Revocation Lists)** for certificate validation. With server-side validation no longer possible (since BB infrastructure is down), the device falls back to basic certificate chain validation only.

### Why Older Websites Still Work

Websites using certificates from older CAs (VeriSign/Symantec, Comodo/Sectigo, DigiCert's legacy roots) that were in BB10's original certificate store continue to work without any fix. Only Let's Encrypt and newer CA roots are affected.

---

## Troubleshooting

| Problem | Solution |
|---------|----------|
| Certificate file won't install | Ensure the file is `.der` format, not `.pem` (different encoding) |
| Browser still shows errors after install | Reboot the device after certificate installation |
| "Untrusted certificate" on specific site only | That site's CA may use a different root; check the specific CA |
| Certificate shows as installed but doesn't work | Try clearing browser cache: **Browser → Settings → Privacy → Clear Browsing Data** |
| Can't download cert file because browser is broken | Download on PC and transfer via USB |

---

*Next: [See which apps work in 2026 →](Working_Apps_Directory.md)*
