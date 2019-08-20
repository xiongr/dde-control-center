/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *             listenerri <listenerri@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef WIREDPAGE_H
#define WIREDPAGE_H

#include "widgets/contentwidget.h"
#include "widgets/switchwidget.h"
#include "connectioneditpage.h"
#include "window/namespace.h"

#include <QPointer>
#include <QListView>
#include <QStandardItemModel>
#include <wireddevice.h>

class QPushButton;

namespace dde {
namespace network {
class NetworkModel;
}
}

namespace dcc {
namespace widgets {
class SettingsGroup;
class NextPageWidget;
}

}

namespace DCC_NAMESPACE {

namespace network {

class WiredPage : public dcc::ContentWidget
{
    Q_OBJECT
public:
    explicit WiredPage(dde::network::WiredDevice *dev, QWidget *parent = nullptr);

    void setModel(dde::network::NetworkModel *model);

Q_SIGNALS:
    void requestConnectionsList(const QString &devPath);
    void requestActiveConnection(const QString &devPath, const QString &uuid) const;
    void requestNextPage(ContentWidget * const w) const;
    void requestFrameKeepAutoHide(const bool autoHide) const;
    void requestDeviceEnabled(const QString &devPath, const bool enabled) const;
    void requestShowConnEditPage(dde::network::NetworkDevice *device, const QString &session) const;
    void requestRemoveConnEditPage(dde::network::NetworkDevice *device) const;

private Q_SLOTS:
    void initUI();

    void refreshConnectionList();
    void editConnection();
    void editConnection1(const QModelIndex &idx);
    void createNewConnection();
    void activateConnection();
    void activateConnection1(const QModelIndex &idx);
    void checkActivatedConnection();
    void onDeviceStatusChanged(const dde::network::WiredDevice::DeviceStatus stat);
    void onDeviceRemoved();

private:
    dde::network::WiredDevice *m_device;
    dde::network::NetworkModel *m_model;

    dcc::widgets::SwitchWidget *m_switch;

    QListView *m_lvProfiles;
    QStandardItemModel *m_modelprofiles;

    QPointer<ConnectionEditPage> m_editPage;

    QPushButton *m_createBtn;
    dcc::widgets::SettingsGroup *m_settingsGrp;
    dcc::widgets::SettingsGroup *m_tipsGrp;

    QMap<dcc::widgets::NextPageWidget *, QString> m_connectionPath;
};

}

}

#endif // WIREDPAGE_H
