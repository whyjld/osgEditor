#ifndef ADDSHADERDIALOG_H
#define ADDSHADERDIALOG_H

#include <osg/Shader>

#include <QDialog>

namespace Ui {
class AddShaderDialog;
}

class AddShaderDialog : public QDialog
{
    Q_OBJECT

public:
    enum { ShaderCount = 6 };
    explicit AddShaderDialog(QWidget *parent = 0);
    ~AddShaderDialog();

    int exec(bool shader[ShaderCount]);
private:
    Ui::AddShaderDialog *ui;
};

#endif // ADDSHADERDIALOG_H
