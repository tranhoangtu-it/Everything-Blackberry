# Contributing to Everything-BlackBerry

Thank you for considering a contribution! This project thrives on community knowledge. Please read these guidelines carefully before submitting.

---

## 📋 Table of Contents

1. [Code of Conduct](#code-of-conduct)
2. [How to Contribute](#how-to-contribute)
3. [Adding a New Guide](#adding-a-new-guide)
4. [Adding or Updating Device Specs](#adding-or-updating-device-specs)
5. [Writing Style Guide](#writing-style-guide)
6. [Pull Request Process](#pull-request-process)

---

## 🤝 Code of Conduct

- Be respectful and constructive. BlackBerry enthusiasts come from all backgrounds.
- No misinformation. If you're unsure, mark content clearly with `> ⚠️ **Unverified** — needs testing.`
- Do not include links to pirated firmware or illegal content.

---

## 🛠 How to Contribute

### Option 1: Edit Directly on GitHub
Click the pencil icon (✏️) on any Markdown file to propose an edit via GitHub's web editor.

### Option 2: Fork & Pull Request
```bash
# 1. Fork the repository on GitHub
# 2. Clone your fork
git clone https://github.com/YOUR_USERNAME/Everything-BlackBerry.git
cd Everything-BlackBerry

# 3. Create a feature branch
git checkout -b feat/add-passport-tips

# 4. Make your changes
# 5. Commit with a descriptive message
git commit -m "docs(survival): add Passport battery optimization tips"

# 6. Push and open a Pull Request
git push origin feat/add-passport-tips
```

---

## 📄 Adding a New Guide

### Placement Rules

| Content Type | Location |
|---|---|
| Tips for new owners / survival tricks | `01_Survival_Guide/` |
| Development tutorials, code samples | `02_Development_Suite/` |
| Device history, specs, deep dives | `03_Device_Museum/` |
| Firmware, PC software, tools | `04_Tools_Archive/` |
| Community links, historical events | `05_Community_&_History/` |

### File Naming Convention

- Use `PascalCase_With_Underscores.md` for Markdown documents.
- Use `snake_case.json` for data files.
- Use `PascalCase.cpp` / `PascalCase.py` for code samples.

### Required Frontmatter (Comment Block)

Start every new Markdown guide with the following block:

```markdown
<!--
  Title: <Your Guide Title>
  Author: <Your GitHub username>
  Last Verified: <YYYY-MM-DD>
  Devices Tested: <e.g., BlackBerry Passport SQW100-1, BB10 OS 10.3.3>
-->
```

### Minimum Content Requirements

A guide must contain:
- **Introduction** — what problem does this solve?
- **Prerequisites** — what does the reader need before starting?
- **Step-by-step instructions** — numbered list, clear and concise
- **Verification** — how does the reader confirm success?
- **Troubleshooting** — at least 2-3 common failure modes

---

## 📱 Adding or Updating Device Specs

Device data lives in `03_Device_Museum/devices_database.json`.

### JSON Schema

Each device entry must conform to this schema:

```json
{
  "model_name": "String — Full commercial name",
  "codename": "String — Internal development codename",
  "release_date": "String — YYYY-MM-DD or YYYY-MM",
  "manufacturer": "String — RIM, BlackBerry Ltd, or TCL",
  "form_factor": "String — Touchscreen | QWERTY Slider | All-Touch | Candybar QWERTY",
  "cpu": "String — Chip model and clock speed",
  "ram": "String — e.g., 2 GB LPDDR3",
  "storage": "String — e.g., 32 GB eMMC",
  "os_version": "String — OS shipped + max supported version",
  "screen_res": "String — e.g., 1080x1920",
  "screen_size": "String — diagonal in inches",
  "battery": "String — capacity in mAh",
  "status_in_2026": "String — Active | Functional | Limited | Legacy Only"
}
```

### Validation

Before submitting, validate your JSON:

```bash
python3 -c "import json; json.load(open('03_Device_Museum/devices_database.json'))"
```

---

## ✍️ Writing Style Guide

- **Tone**: Technical but accessible. Write for a smart person who is new to BlackBerry.
- **Tense**: Present tense for current state; past tense for history.
- **Accuracy first**: If a service is dead, say so clearly. Don't soften the truth.
- **Markdown features**: Use tables for comparisons, `> blockquotes` for important warnings, and fenced code blocks with language identifiers.
- **Links**: Use relative links for internal files (e.g., `[guide](../01_Survival_Guide/Sideloading_Masterclass.md)`) and full URLs for external resources.
- **Screenshots**: Place images in an `assets/images/` sub-directory within the relevant section folder.

---

## 🔀 Pull Request Process

1. Ensure your PR targets the `main` branch.
2. Fill out the PR template completely.
3. Self-review your diff for typos, broken links, and formatting issues.
4. A maintainer will review within 7 days.
5. Address any requested changes within 14 days, or the PR may be closed.

### PR Title Format

```
<type>(<scope>): <short description>

Types: feat | fix | docs | data | refactor
Scopes: survival | dev | museum | tools | community | root

Examples:
  feat(survival): add guide for Z30 battery replacement
  fix(museum): correct Passport RAM spec to 3 GB
  data(museum): add Bold 9900 to devices_database.json
```

---

*Thank you for helping preserve BlackBerry history and keeping these devices useful!* 🫐
