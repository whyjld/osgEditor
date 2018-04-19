#include "addtexturedialog.h"
#include "ui_addtexturedialog.h"

AddTextureDialog::AddTextureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTextureDialog)
{
    ui->setupUi(this);
}

AddTextureDialog::~AddTextureDialog()
{
    delete ui;
}
