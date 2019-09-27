/*
 * Copyright (C) 2019 Deepin Technology Co., Ltd.
 *
 * Author:     andywang <andywang_cm@deepin.com>
 *
 * Maintainer: andywang <andywang_cm@deepin.com>
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

#include "devicesettingsitem.h"
#include "modules/bluetooth/device.h"
#include "widgets/labels/normallabel.h"

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QTimer>

using namespace dcc::widgets;
using namespace dcc;
using namespace dcc::bluetooth;
using namespace DCC_NAMESPACE;
using namespace DCC_NAMESPACE::bluetooth;

DeviceSettingsItem::DeviceSettingsItem(const Device *device, QStyle *style)
    : m_device(device)
    , m_deviceItem(new DStandardItem)
    , m_parentDListView(nullptr)
{
    m_loadingIndicator = new DSpinner();
    m_loadingIndicator->QObject::setParent(this);
    m_loadingIndicator->setFixedSize(24, 24);
    m_loadingIndicator->hide();
    initItemActionList(style);
    setDevice(device);
    m_deviceItem->setText(m_device->name());
    m_deviceItem->setActionList(Qt::RightEdge, m_dActionList);
}

void DeviceSettingsItem::initItemActionList(QStyle *style)
{
    m_loadingAction = new DViewItemAction(Qt::AlignCenter, QSize(), QSize(), false, this);
    m_loadingAction->setWidget(m_loadingIndicator);
    m_iconAction = new DViewItemAction(Qt::AlignRight, QSize(), QSize(), true, this);
    m_textAction = new DViewItemAction(Qt::AlignLeft, QSize(), QSize(), true, this);
    m_iconAction->setIcon(style->standardIcon(QStyle::SP_ArrowRight));
    m_dActionList.append(m_loadingAction);
    m_dActionList.append(m_textAction);
    m_dActionList.append(m_iconAction);
}

void DeviceSettingsItem::setLoading(const bool loading)
{
    if (loading) {
        m_loadingIndicator->start();
        m_loadingIndicator->show();
        m_loadingAction->setVisible(true);
        m_textAction->setVisible(false);
    } else {
        m_loadingIndicator->stop();
        m_loadingIndicator->hide();
        m_loadingAction->setVisible(false);
        m_textAction->setVisible(true);
    }
    if (m_parentDListView) {
        m_parentDListView->update();
    }
}

void DeviceSettingsItem::setDevice(const Device *device)
{
    connect(device, &Device::stateChanged, this, &DeviceSettingsItem::onDeviceStateChanged);
    connect(device, &Device::pairedChanged, this, &DeviceSettingsItem::onDevicePairedChanged);

    connect(m_textAction, &QAction::triggered, this, [this] {
        Q_EMIT requestConnectDevice(m_device);
    });

    connect(m_iconAction, &QAction::triggered, this, [this] {
        Q_EMIT requestShowDetail(m_device);
    });
    connect(device, &Device::nameChanged, this, [this](const QString &name) {
        m_deviceItem->setText(name);
    });

    onDeviceStateChanged(device->state());
    onDevicePairedChanged(device->paired());
}

DStandardItem *DeviceSettingsItem::getStandardItem(DListView *parent)
{
    if (parent != nullptr) {
        m_parentDListView = parent;
        m_loadingIndicator->setParent(parent->viewport());
    }
    return m_deviceItem;
}

DStandardItem *DeviceSettingsItem::createStandardItem(DListView *parent)
{
    if (parent != nullptr) {
        m_parentDListView = parent;
        m_loadingIndicator->setParent(parent->viewport());
    }
    m_deviceItem = new DStandardItem;
    m_deviceItem->setText(m_device->name());
    m_deviceItem->setActionList(Qt::RightEdge, m_dActionList);
    return m_deviceItem;
}

void DeviceSettingsItem::onDeviceStateChanged(const Device::State &state)
{
    if (state == Device::StateAvailable) {
        setLoading(true);
        return;
    }
    QString tip;
    switch (state) {
    case Device::StateConnected: {
        tip = tr("Connected");
        setLoading(false);
        break;
    }
    case Device::StateUnavailable:
        tip = tr("Not connected");
        setLoading(false);
        break;
    default:
        break;
    }
    m_textAction->setText(tip);
}

void DeviceSettingsItem::onDevicePairedChanged(const bool &paired)
{
    if (paired) {
        m_iconAction->setVisible(true);
    } else {
        m_iconAction->setVisible(false);
    }
}

const Device *DeviceSettingsItem::device() const
{
    return m_device;
}