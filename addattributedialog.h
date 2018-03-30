#ifndef ADDATTRIBUTEDIALOG_H
#define ADDATTRIBUTEDIALOG_H

#include <osg/StateSet>

#include <QDialog>

namespace Ui {
class AddAttributeDialog;
}

class AddAttributeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAttributeDialog(osg::StateSet::AttributeList& list, QWidget *parent = 0);
    ~AddAttributeDialog();

    int exec(osg::StateAttribute::Type& type);
private slots:
    void on_cbAttribute_currentIndexChanged(int index);

private:
    Ui::AddAttributeDialog *ui;

    osg::StateSet::AttributeList& m_AttributeList;
};

#endif // ADDATTRIBUTEDIALOG_H
