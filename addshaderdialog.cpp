#include "addshaderdialog.h"
#include "ui_addshaderdialog.h"

AddShaderDialog::AddShaderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddShaderDialog)
{
    ui->setupUi(this);
}

AddShaderDialog::~AddShaderDialog()
{
    delete ui;
}

int AddShaderDialog::exec(bool shader[ShaderCount])
{
    ui->cbVertex->setEnabled(!shader[0]);
    ui->cbVertex->setChecked(!shader[0]);
    ui->cbTessControl->setEnabled(!shader[1]);
    ui->cbTessEvaluation->setEnabled(!shader[2]);
    ui->cbGeometry->setEnabled(!shader[3]);
    ui->cbFragment->setEnabled(!shader[4]);
    ui->cbFragment->setChecked(!shader[4]);
    ui->cbCompute->setEnabled(!shader[5]);

    int ret = QDialog::exec();

    shader[0] = ui->cbVertex->isChecked();
    shader[1] = ui->cbTessControl->isChecked();
    shader[2] = ui->cbTessEvaluation->isChecked();
    shader[3] = ui->cbGeometry->isChecked();
    shader[4] = ui->cbFragment->isChecked();
    shader[5] = ui->cbCompute->isChecked();

    return ret;
}
