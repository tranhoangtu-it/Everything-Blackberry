/**
 * Hello_BlackBerry_Native.cpp
 *
 * A complete, well-commented "Hello World" application for BlackBerry 10
 * using the Cascades framework (Qt-based UI toolkit by RIM/BlackBerry).
 *
 * This sample demonstrates:
 *  - The standard BB10 application lifecycle
 *  - Creating a Cascades UI entirely in C++ (without QML)
 *  - Proper use of the bb::Application, bb::cascades::Page, and
 *    bb::cascades::Label classes
 *  - Signal/slot connections (Qt's event system)
 *  - Active Frame support (BB10's multitasking thumbnail)
 *
 * Build with (from NDK environment):
 *   qcc -Vgcc_ntoarmv7le_cpp -o hello_bb Hello_BlackBerry_Native.cpp \
 *       -I$QNX_TARGET/usr/include/qt4 \
 *       -I$QNX_TARGET/usr/include/bb/cascades \
 *       -L$QNX_TARGET/armle-v7/usr/lib \
 *       -lbb -lbbcascades -lQtCore -lQtGui
 *
 * References:
 *  - Cascades API Docs (archived): https://developer.blackberry.com/native/apis/
 *  - Qt 4.8 Documentation: https://doc.qt.io/archives/qt-4.8/
 *
 * License: MIT
 * Author:  Everything-BlackBerry Contributors
 */

// ─── Qt Core includes ──────────────────────────────────────────────────────
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QLocale>
#include <QtCore/QTranslator>

// ─── BlackBerry Application includes ───────────────────────────────────────
// bb::Application is the entry point for all BB10 native applications.
// It manages the QNX event loop, Active Frame lifecycle, and OS integration.
#include <bb/Application>

// ─── BlackBerry Cascades UI includes ───────────────────────────────────────
// The core UI namespace. All visual components live here.
#include <bb/cascades/Application>
#include <bb/cascades/Page>
#include <bb/cascades/Container>
#include <bb/cascades/Label>
#include <bb/cascades/Button>
#include <bb/cascades/StackLayout>
#include <bb/cascades/StackLayoutProperties>
#include <bb/cascades/Color>
#include <bb/cascades/HorizontalAlignment>
#include <bb/cascades/VerticalAlignment>
#include <bb/cascades/SystemDefaults>
#include <bb/cascades/TextStyle>

// ─── Active Frame (thumbnail in multitasking view) ─────────────────────────
#include <bb/cascades/AbstractPane>
#include <bb/cascades/SceneCover>

using namespace bb::cascades;


// ─────────────────────────────────────────────────────────────────────────────
// HelloApplication
//
// Our main application class. Inherits from QObject (Qt's base class) so we
// can use signals and slots.
// ─────────────────────────────────────────────────────────────────────────────
class HelloApplication : public QObject
{
    // Q_OBJECT macro is required for any class that uses signals/slots.
    Q_OBJECT

public:
    /**
     * Constructor.
     *
     * @param app  Pointer to the bb::cascades::Application instance.
     *             We receive this from main() and use it to set up our UI.
     */
    HelloApplication(bb::cascades::Application* app) : QObject(app)
    {
        // ── Step 1: Build the UI ────────────────────────────────────────────
        // In Cascades, the UI is a tree of Pane > Container > Control objects.
        // We create a Page as the root, add a Container as the layout host,
        // and place our Label and Button inside the Container.

        // Root page — every BB10 screen is a Page (or NavigationPane of Pages)
        Page* root = new Page();

        // Main container — acts like a <div> in HTML, organises child controls
        Container* mainContainer = new Container();
        mainContainer->setLayout(StackLayout::create()
            .orientation(LayoutOrientation::TopToBottom));
        mainContainer->setHorizontalAlignment(HorizontalAlignment::Center);
        mainContainer->setVerticalAlignment(VerticalAlignment::Center);

        // ── Step 2: Create a greeting Label ────────────────────────────────
        Label* greetingLabel = new Label();
        greetingLabel->setText("Hello, BlackBerry World! 🫐");

        // Use the built-in "BigText" system style for prominent text
        greetingLabel->textStyle()->setBase(SystemDefaults::TextStyles::bigText());
        greetingLabel->setHorizontalAlignment(HorizontalAlignment::Center);

        // ── Step 3: Create a subtitle Label ────────────────────────────────
        Label* subtitleLabel = new Label();
        subtitleLabel->setText("Running on QNX Neutrino / Cascades");
        subtitleLabel->textStyle()->setBase(SystemDefaults::TextStyles::subtitleText());
        subtitleLabel->setHorizontalAlignment(HorizontalAlignment::Center);

        // ── Step 4: Create a Button ─────────────────────────────────────────
        // Buttons emit the clicked() signal when tapped.
        // We connect that signal to our slot (onButtonClicked) below.
        Button* actionButton = new Button();
        actionButton->setText("Tap Me!");

        // Qt signal/slot syntax: connect(sender, SIGNAL(...), receiver, SLOT(...))
        // When actionButton emits clicked(), this object's onButtonClicked() runs.
        connect(actionButton, SIGNAL(clicked()), this, SLOT(onButtonClicked()));

        // ── Step 5: Assemble the UI tree ────────────────────────────────────
        mainContainer->add(greetingLabel);
        mainContainer->add(subtitleLabel);
        mainContainer->add(actionButton);
        root->setContent(mainContainer);

        // ── Step 6: Set the Active Frame (multitasking thumbnail) ───────────
        // BB10's distinctive Active Frame appears when the user minimises the app.
        // Here we create a simple SceneCover with a label as the preview.
        SceneCover* cover = SceneCover::create()
            .content(Container::create()
                .add(Label::create()
                    .text("Hello BB 🫐")
                    .textStyle(SystemDefaults::TextStyles::titleText())
                    .horizontal(HorizontalAlignment::Center)
                    .vertical(VerticalAlignment::Center)));

        Application::instance()->setCover(cover);

        // ── Step 7: Give the root Page to the application ───────────────────
        app->setScene(root);

        // At this point the event loop will start in main(), and the UI
        // is displayed on the BB10 screen.
    }

public slots:
    /**
     * onButtonClicked
     *
     * Slot invoked when the user taps the "Tap Me!" button.
     * In a real application, you would navigate to a new page, open a dialog,
     * or trigger a background action here.
     */
    void onButtonClicked()
    {
        // Find the greeting label and update its text dynamically.
        // In a production app, you would keep a member pointer to the label
        // instead of searching the tree at runtime.
        bb::cascades::Application* cascadesApp = bb::cascades::Application::instance();
        if (!cascadesApp) return;

        AbstractPane* scene = cascadesApp->scene();
        if (!scene) return;

        // Traverse: Page → Container → Label (index 0)
        Page* page = qobject_cast<Page*>(scene);
        if (!page) return;

        Container* container = qobject_cast<Container*>(page->content());
        if (!container) return;

        Label* label = qobject_cast<Label*>(container->at(0));
        if (label) {
            label->setText("Button was tapped! 🎉");
        }
    }
};


// ─────────────────────────────────────────────────────────────────────────────
// main()
//
// Entry point for every BB10 native application.
//
// The flow is:
//   1. Instantiate bb::cascades::Application (wraps the QNX event loop)
//   2. Instantiate our application logic class (builds the UI, connects signals)
//   3. Call Application::exec() — this starts the event loop, which runs until
//      the user closes the app or the OS terminates it.
// ─────────────────────────────────────────────────────────────────────────────
int main(int argc, char* argv[])
{
    // bb::cascades::Application handles QNX process setup, Cascades
    // framework initialisation, and integrates with the BB10 window manager.
    bb::cascades::Application app(argc, argv);

    // Optional: load a translation file for localisation
    // QTranslator translator;
    // translator.load("HelloBlackBerry_" + QLocale().name(), "app/native/qm");
    // app.installTranslator(&translator);

    // Instantiate our application logic.
    // The constructor builds the full UI and calls app.setScene().
    HelloApplication hello(&app);

    // Start the Qt/QNX event loop.
    // exec() returns when the application is closed (BB10 sends a quit event).
    return bb::cascades::Application::exec();
}

// Required by Qt's MOC (Meta-Object Compiler) when signals/slots are defined
// in the same .cpp file (instead of splitting into .h/.cpp).
#include "Hello_BlackBerry_Native.moc"
