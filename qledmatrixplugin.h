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

#ifndef QLEDMATRIXPLUGIN_H
#define QLEDMATRIXPLUGIN_H

#include <QDesignerCustomWidgetInterface>

class QLedMatrixPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

    public:
        QLedMatrixPlugin(QObject* parent = 0);

        bool isContainer() const;
        bool isInitialized() const;
        QIcon icon() const;
        QString domXml() const;
        QString group() const;
        QString includeFile() const;
        QString name() const;
        QString toolTip() const;
        QString whatsThis() const;
        QWidget* createWidget(QWidget* parent);
        void initialize(QDesignerFormEditorInterface* core);

    private:
        bool initialized;
};

#endif // QLEDMATRIXPLUGIN_H
