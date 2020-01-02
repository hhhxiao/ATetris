#ifndef MODEWINDOW_H
#define MODEWINDOW_H

#include <QDialog>

namespace Ui {
class ModeWindow;
}

class ModeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ModeWindow(QWidget *parent = nullptr);
    ~ModeWindow();

private:
    Ui::ModeWindow *ui;
};

#endif // MODEWINDOW_H
