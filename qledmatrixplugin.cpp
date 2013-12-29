/*******************************************************************************
**
**  Copyright (C) 2009 Pierre-Etienne Messier <pierre.etienne.messier@gmail.com>
**                     http://pemessier.hexpresso.org/
**
**  This library is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with this library.  If not, see <http://www.gnu.org/licenses/>.
**
*******************************************************************************/

#include "qledmatrix.h"
#include "qledmatrixplugin.h"

#include <QtPlugin>

QLedMatrixPlugin::QLedMatrixPlugin(QObject* parent): QObject(parent)
{
    initialized = false;
}

void QLedMatrixPlugin::initialize(QDesignerFormEditorInterface* /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool QLedMatrixPlugin::isInitialized() const
{
    return initialized;
}

QWidget* QLedMatrixPlugin::createWidget(QWidget* parent)
{
    return new QLedMatrix(parent);
}

QString QLedMatrixPlugin::name() const
{
    return QString::fromAscii("QLedMatrix");
}

QString QLedMatrixPlugin::group() const
{
    return QString::fromAscii("Display Widgets");
}

QIcon QLedMatrixPlugin::icon() const
{
    return QIcon(QString::fromAscii(":/qledmatrix.png"));
}

QString QLedMatrixPlugin::toolTip() const
{
    return QString();
}

QString QLedMatrixPlugin::whatsThis() const
{
    return QString();
}

bool QLedMatrixPlugin::isContainer() const
{
    return false;
}

QString QLedMatrixPlugin::domXml() const
{
    return QString::fromAscii(
           "<widget class=\"QLedMatrix\" name=\"ledMatrix\">\n"
           " <property name=\"geometry\">\n"
           "  <rect>\n"
           "   <x>0</x>\n"
           "   <y>0</y>\n"
           "   <width>100</width>\n"
           "   <height>100</height>\n"
           "  </rect>\n"
           " </property>\n"
           " <property name=\"rows\" >\n"
           "  <number>8</number>\n"
           " </property>\n"
           " <property name=\"columns\" >\n"
           "  <number>8</number>\n"
           " </property>\n"
           " <property name=\"backgroundColor\" >\n"
           "  <color>\n"
           "   <red>0</red>\n"
           "   <green>0</green>\n"
           "   <blue>0</blue>\n"
           "  </color>\n"
           " </property>\n"
           " <property name=\"backgroundMode\" >\n"
           "  <enum>Qt::OpaqueMode</enum>\n"
           " </property>\n"
           " <property name=\"darkLedColor\" >\n"
           "  <color>\n"
           "   <red>34</red>\n"
           "   <green>34</green>\n"
           "   <blue>34</blue>\n"
           "  </color>\n"
           " </property>\n"
           "</widget>\n");
}

QString QLedMatrixPlugin::includeFile() const
{
    return QString::fromAscii("qledmatrix.h");
}

Q_EXPORT_PLUGIN2(qledmatrixplugin, QLedMatrixPlugin)
