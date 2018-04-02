#ifndef CREATENODEDIALOG_H
#define CREATENODEDIALOG_H

#include <QDialog>

namespace Ui {
class CreateNodeDialog;
}

class CreateNodeDialog : public QDialog
{
    Q_OBJECT

public:
    enum NodeType
    {
        ntGroup,
        ntMatrixTransform,
        ntPositionAttitudeTransform,
        ntCamera,
        ntSwitch,
        ntGeode,
    };

    explicit CreateNodeDialog(QWidget *parent = 0);
    ~CreateNodeDialog();

    virtual int exec(NodeType& type);

    QString getName() const;

private:
    Ui::CreateNodeDialog *ui;
};

#endif // CREATENODEDIALOG_H
