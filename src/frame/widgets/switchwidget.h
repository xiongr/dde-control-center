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

#ifndef SWITCHWIDGET_H
#define SWITCHWIDGET_H

#include "widgets/settingsitem.h"

#include <dswitchbutton.h>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

namespace dcc {
namespace widgets {

class SwitchWidget : public SettingsItem
{
    Q_OBJECT

public:
    explicit SwitchWidget(QWidget *parent = nullptr);
    explicit SwitchWidget(const QString &title, QFrame *parent = nullptr);
    explicit SwitchWidget(QLabel *widget, QWidget *parent = nullptr);

    void setChecked(const bool checked = true);
    void setTitle(const QString &title);
    bool checked() const;

    QLabel *leftWidget() const { return m_leftWidget; }

Q_SIGNALS:
    void checkedChanged(const bool checked) const;
    void clicked();

protected:
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QLabel *m_leftWidget;
    Dtk::Widget::DSwitchButton *m_switchBtn;
};

}
}

#endif // SWITCHWIDGET_H
