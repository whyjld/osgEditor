#ifndef ADDTEXTUREDIALOG_H
#define ADDTEXTUREDIALOG_H

#include <QDialog>

namespace Ui {
class AddTextureDialog;
}

class AddTextureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTextureDialog(QWidget *parent = 0);
    ~AddTextureDialog();

private:
    Ui::AddTextureDialog *ui;
};

#endif // ADDTEXTUREDIALOG_H
