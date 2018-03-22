#ifndef PROPERTYTREEATTRIBUTEMATRIXITEM_H
#define PROPERTYTREEATTRIBUTEMATRIXITEM_H

#include "propertytreeitem.h"
#include "propertytreeattributevectoritem.h"

#include <osg/Matrix>

#include <functional>

typedef std::function<const osg::Matrix&()> MatrixGetter_t;
typedef std::function<void(const osg::Matrix&)> MatrixSetter_t;

class PropertyTreeAttributeMatrixItem : public PropertyTreeItem
{
public:
    PropertyTreeAttributeMatrixItem(PropertyTreeItem *parent, const QString& name, const MatrixGetter_t& getter, const MatrixSetter_t& setter)
        : PropertyTreeItem(parent)
        , m_Getter(getter)
        , m_Setter(setter)
        , m_Matrix(getter())
        , m_Name(name)
    {
        for(size_t r = 0;r < 4;++r)
        {
            QString name;
            name.sprintf("Row[%d]", r);
            m_ChildItems.push_back(new PropertyTreeAttributeVectorItem<osg::Matrix::value_type>(this, name, m_Matrix(r, 0), m_Matrix(r, 1), m_Matrix(r, 2), m_Matrix(r, 3)));
        }
    }
    virtual ~PropertyTreeAttributeMatrixItem()
    {

    }

    virtual QVariant data(int column, int role) const
    {
        if(Qt::DisplayRole == role)
        {
            switch(column)
            {
            case ptcProperty:
                return m_Name;
            case ptcValue:
                if(true)
                {
                    std::stringstream ss;
                    ss.flags(std::ios::fixed);
                    ss.precision(4);

                    for(size_t r = 0;r < 4;++r)
                    {
                        ss << "(" << m_Matrix(r, 0);
                        for(size_t c = 1;c < 4;++c)
                        {
                            ss << ", " << m_Matrix(r, c);
                        }
                        ss << ")";
                    }
                    return QVariant(ss.str().c_str());
                }
            }
        }
        return PropertyTreeItem::data(column, role);

    }
private:
    MatrixGetter_t m_Getter;
    MatrixSetter_t m_Setter;

    osg::Matrix m_Matrix;
    QVariant m_Name;
};

#endif // PROPERTYTREEATTRIBUTEMATRIXITEM_H
