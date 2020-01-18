#include "particlewidget.h"

particleWidget::particleWidget(QWidget *parent):QQuickWidget(parent)
{
    this->setSource(QUrl::fromLocalFile(":/particle/theme/test.qml"));
}
