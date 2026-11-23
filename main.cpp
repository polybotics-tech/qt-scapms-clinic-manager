#include "gui/LoginWindow.h"
#include "gui/MainWindow.h"

#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LoginWindow loginWindow;

    QObject::connect(&loginWindow,
                     &LoginWindow::loginSuccessful,
                     &loginWindow,
                     [&loginWindow](const QString &role) {
                         MainWindow *mainWindow = new MainWindow();
                         mainWindow->setProperty("userRole", role);
                         mainWindow->applyRolePermissions();

                         //--automatically destroy the window when closed.
                         mainWindow->setAttribute(Qt::WA_DeleteOnClose);

                         mainWindow->show();
                         loginWindow.hide();
                     });

    loginWindow.show();

    return app.exec();
}