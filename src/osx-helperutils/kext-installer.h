#ifndef SEAFILE_KEXT_INSTALLER_H
#define SEAFILE_KEXT_INSTALLER_H

#include <QObject>

#include "utils/singleton.h"

class QTimer;

class KextInstaller : public QObject
{
    Q_OBJECT
    SINGLETON_DEFINE(KextInstaller)

public:
    // This function wraps the logic of installing the helper tool and loading
    // the kernel driver (both implemented in ObjC), and use a timer to check
    // the state of the kext before returning.
    bool install();

private slots:
    void checkKextReady();

private:
    Q_DISABLE_COPY(KextInstaller)
    KextInstaller(QObject *parent=0);
    QTimer *check_timer_;
    bool install_finished_;
    bool kext_ready_;
};

#endif // SEAFILE_KEXT_INSTALLER_H