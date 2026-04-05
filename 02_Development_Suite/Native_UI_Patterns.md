<!--
  Title: Native UI Patterns — The BlackBerry 10 Experience
  Author: Everything-BlackBerry Contributors
  Last Verified: 2026-04-01
-->

# Native UI Patterns — The BlackBerry 10 Experience

> BlackBerry 10 introduced a unique, gesture-driven UI paradigm that was unlike anything on iOS or Android at the time. This document explains the three defining elements: **The Hub**, **Active Frames**, and the **Peek/Flow** gesture system — and how to implement them in Cascades.

---

## Overview: The BB10 UI Philosophy

BB10's UI was designed around a core principle: **"Content at the centre, everything else is secondary."**

Rather than relying on home screen icons and navigation bars, BB10 introduced a flow-based interaction model:

```
  ┌──────────────────────────────────────────────┐
  │                                              │
  │  ←── PEEK LEFT                  PEEK RIGHT ──→
  │  (shows Hub)                  (shows Settings/
  │                                Active Frames)  │
  │                                              │
  │              CURRENT APP                    │
  │           (full screen content)             │
  │                                             │
  │  SWIPE UP FROM BOTTOM = Minimize to Active Frame │
  │  SWIPE FROM BEZEL (right) = Navigate Back   │
  └──────────────────────────────────────────────┘
```

---

## 1. The BlackBerry Hub

### What Is It?

The **Hub** is the universal inbox for all communications: email, SMS, BBM (now defunct), social notifications, and app notifications — all in one unified view. It was a defining feature of BB10 and remains functional today.

### Accessing the Hub

From any app, users access the Hub via the **Peek gesture** (see below) or by tapping the Hub icon. The Hub appears as a left-side panel that slides in.

### Implementing Hub Integration in Cascades

```cpp
// Include Hub access headers
#include <bb/platform/NotificationMessageComposer>
#include <bb/platform/Notification>

// Posting a notification to the Hub
void MyApp::notifyHub(const QString& title, const QString& body)
{
    bb::platform::Notification notification;
    notification.setTitle(title);
    notification.setBody(body);

    // InvocationRequest lets the Hub know which app to open on tap
    bb::system::InvocationRequest request;
    request.setTarget("com.example.myapp.viewer");
    request.setAction("bb.action.VIEW");
    notification.setInvocationRequest(request);

    notification.notify(); // Posts to the Hub
}
```

### QML Hub Integration

```qml
// In your app's bar-descriptor.xml, declare the Hub integration:
// <invoke-target id="com.example.myapp.hub">
//     <type>APPLICATION</type>
// </invoke-target>

// In QML, use the InvokeActionItem to open Hub-related content:
ActionItem {
    title: "Reply from Hub"
    imageSource: "asset:///images/reply.png"
    onTriggered: {
        invokeQuery.execute()
    }
    attachedObjects: [
        Invocation {
            id: invokeQuery
            query {
                mimeType: "text/plain"
                invokeTargetId: "sys.pim.uib.email.hybridcompose"
            }
        }
    ]
}
```

### Hub Architecture

```
BB10 Hub (unified inbox)
├── Email accounts (IMAP/POP3/Exchange/Gmail)
├── SMS / MMS (via SIM)
├── Phone call log
├── BBM (historical; now defunct)
├── Twitter (via Blaq — community patched)
├── Facebook notifications
└── Custom app notifications (via bb::platform::Notification)
```

---

## 2. Active Frames

### What Are They?

**Active Frames** are the BB10 equivalent of multitasking thumbnails. When a user minimises an app (swipe up from the bottom), the app is placed in the "Active Frames" grid. Unlike iOS or Android, these frames can show **live, updating content** — like a live weather preview, a real-time counter, or a message preview.

### Why They're Special

On other OSes, a minimised app shows a static screenshot. BB10 Active Frames are **live previews** that continue to render even when the app is in the background. This is possible because BB10 uses QNX's process model, which keeps apps genuinely alive.

### Implementing Active Frames

```cpp
// In your application class, create and set a SceneCover
#include <bb/cascades/SceneCover>
#include <bb/cascades/Container>
#include <bb/cascades/Label>

void MyApp::setupActiveFrame()
{
    // Build the cover UI (this is a mini version of your app)
    Container* coverContainer = new Container();
    coverContainer->setBackground(Color::fromRGBA(0.1f, 0.1f, 0.1f, 1.0f));

    // A label that shows live data
    m_coverLabel = new Label();
    m_coverLabel->setText("Loading...");
    m_coverLabel->textStyle()->setBase(SystemDefaults::TextStyles::titleText());
    m_coverLabel->setHorizontalAlignment(HorizontalAlignment::Center);
    m_coverLabel->setVerticalAlignment(VerticalAlignment::Center);

    coverContainer->add(m_coverLabel);

    // SceneCover wraps the cover UI
    SceneCover* cover = SceneCover::create().content(coverContainer);
    Application::instance()->setCover(cover);
}

// Update the Active Frame from a background timer
void MyApp::onTimerTick()
{
    QString currentTime = QTime::currentTime().toString("hh:mm:ss");
    if (m_coverLabel) {
        m_coverLabel->setText(currentTime); // Updates the live frame!
    }
}
```

### QML Active Frame Example

```qml
// main.qml
import bb.cascades 1.4

Application {
    // The main scene shown when app is in foreground
    Page {
        id: mainPage
        Container {
            Label {
                text: "My App"
                textStyle.base: SystemDefaults.TextStyles.BigText
            }
        }
    }

    // The Active Frame shown when app is minimised
    cover: SceneCover {
        content: Container {
            background: Color.Black
            layout: DockLayout {}

            Label {
                id: liveData
                text: "Live: " + counter
                textStyle.base: SystemDefaults.TextStyles.TitleText
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Center
            }
        }
    }
}
```

### Active Frame Design Guidelines

| Guideline | Reason |
|-----------|--------|
| Keep it simple — 1-3 elements max | Active Frames are small (~280×210 pt) |
| Show the most important live data | That's the whole point of a "live" frame |
| Use dark backgrounds | The multitasking grid has a dark UI |
| Match the app's visual identity | Users identify apps by their Frame |

---

## 3. Peek & Flow Gestures

### What Is "Peek"?

**Peek** is the gesture of revealing a panel (Hub or app settings) by placing a finger on the bezel edge and dragging slightly inward — without fully navigating away. It "peeks" at the next layer.

Peek directions:
- **Peek left** (drag from right bezel edge toward left): reveals the **Hub**
- **Peek right** (drag from left bezel edge toward right): reveals the previous screen or settings

### What Is "Flow"?

**Flow** is the full gesture that completes a navigation action. If you Peek and keep dragging, you "flow" fully into the Hub or previous screen.

### Implementing Back Navigation (Flow Gesture)

```cpp
// BB10 handles back navigation automatically for NavigationPane.
// The right-edge swipe gesture fires the "popTransitionEnded" signal.
#include <bb/cascades/NavigationPane>

NavigationPane* navPane = new NavigationPane();

// Connect the back gesture signal
connect(navPane, SIGNAL(popTransitionEnded(bb::cascades::Page*)),
        this, SLOT(onBackNavigated(bb::cascades::Page*)));

void MyApp::onBackNavigated(bb::cascades::Page* page)
{
    // Clean up the popped page
    if (page) {
        page->deleteLater();
    }
}
```

### NavigationPane — The Flow Container

```qml
// NavigationPane implements the "flow" navigation pattern
import bb.cascades 1.4

NavigationPane {
    id: navPane

    // The initial (root) page
    Page {
        id: mainPage
        titleBar: TitleBar {
            title: "Inbox"
        }
        Container {
            ListView {
                id: messageList
                onTriggered: {
                    // Navigate to detail page on item tap
                    var detailPage = detailPageDefinition.createObject();
                    navPane.push(detailPage); // "flow" forward
                }
                attachedObjects: [
                    ComponentDefinition {
                        id: detailPageDefinition
                        source: "DetailPage.qml"
                    }
                ]
            }
        }
    }

    onPopTransitionEnded: {
        // Called when user swipes back (Flow gesture)
        page.destroy();
    }
}
```

### TabbedPane — The App Structure Pattern

Many BB10 apps use `TabbedPane` as the root container, with the Hub as a conceptual "first tab":

```qml
TabbedPane {
    showTabsOnActionBar: true

    Tab {
        title: "Home"
        imageSource: "asset:///images/tab_home.png"
        Page { /* ... */ }
    }
    Tab {
        title: "Search"
        imageSource: "asset:///images/tab_search.png"
        Page { /* ... */ }
    }
    Tab {
        title: "Settings"
        imageSource: "asset:///images/tab_settings.png"
        Page { /* ... */ }
    }
}
```

---

## 4. Action Bar and Context Menus

BB10's **Action Bar** sits at the bottom of the screen (on most devices) and contains up to 4 primary actions, with overflow in a bottom menu.

```qml
Page {
    actions: [
        ActionItem {
            title: "Share"
            imageSource: "asset:///images/share.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: shareContent()
        },
        ActionItem {
            title: "Delete"
            imageSource: "asset:///images/delete.png"
            ActionBar.placement: ActionBarPlacement.InOverflow
            onTriggered: confirmDelete()
        },
        DeleteActionItem {
            // Built-in delete action with standard icon and confirmation
            onTriggered: deleteItem()
        }
    ]
}
```

---

## 5. Sheets and Dialogs

BB10 uses **Sheets** (full-screen modal overlays) instead of dialogs for complex flows:

```qml
Sheet {
    id: mySheet
    content: Page {
        titleBar: TitleBar {
            title: "New Message"
            acceptAction: ActionItem {
                title: "Send"
                onTriggered: {
                    sendMessage()
                    mySheet.close()
                }
            }
            dismissAction: ActionItem {
                title: "Cancel"
                onTriggered: mySheet.close()
            }
        }
        // Sheet content here
    }
}

// To show the sheet:
mySheet.open()
```

---

## Summary: BB10 UI Principles

| Principle | Implementation |
|-----------|---------------|
| **Content-first** | Full-screen pages, no persistent navigation bars |
| **Gesture-driven** | Peek/Flow replace explicit back buttons |
| **Always-on** | Active Frames keep apps alive and visible |
| **Unified communications** | Hub aggregates all notifications |
| **Contextual actions** | Action Bar changes per-page, not app-wide |

---

*Next: [Android Runtime Optimization →](Android_Runtime_Optimization.md)*
