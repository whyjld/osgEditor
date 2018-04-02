#include "createnodedialog.h"
#include "ui_createnodedialog.h"

CreateNodeDialog::CreateNodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNodeDialog)
{
    ui->setupUi(this);

    QStringList items;
    items << "Group";
    items << "MatrixTransform";
    items << "PositionAttitudeTransform";
    items << "Camera";
    items << "Switch";
    items << "Geode";
    ui->cbType->addItems(items);
}

CreateNodeDialog::~CreateNodeDialog()
{
    delete ui;
}

int CreateNodeDialog::exec(CreateNodeDialog::NodeType& type)
{
    int ret = QDialog::exec();
    if(QDialog::Accepted == ret)
    {
        type = (CreateNodeDialog::NodeType)ui->cbType->currentIndex();
    }
    return ret;
}

QString CreateNodeDialog::getName() const
{
    return ui->leName->text();
}
