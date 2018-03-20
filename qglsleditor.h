#ifndef QGLSLEDITOR_H
#define QGLSLEDITOR_H

#include <osg/Shader>
#include <osg/ref_ptr>

#include <Qsci/qsciscintilla.h>
#include <QLineEdit>

class QGLSLEditor : public QsciScintilla
{
    Q_OBJECT
public:
    enum MarkerType
    {
        ERROR,    ///< Symbol marker for Errors
        WARNING,  ///< Symbol marker for warnings
    };

    explicit QGLSLEditor(QWidget *parent = 0);

    void setSearchWidget(QWidget* searchWidget, QLineEdit* searchLineEdit);

    void setShader(osg::Shader* shader);
public slots:
    void clearErrors();
    void searchNext();
    void searchPrev();
    void highlightAllSearch();
    void highlightAllSearch(const QString& text);
    void toggleSearchBox();

private slots:
    void comment();
    void charAdded(int c);
    void resetHighlightColour();

private:
    bool autoClose(const QString close);
    bool closing(const QString close);
    void braceIndent();

    QWidget* m_SearchWidget;
    QLineEdit* m_SearchLineEdit;
    std::vector<int>  m_FileMarkers;
    int m_SearchIndicator;

    osg::ref_ptr<osg::Shader> m_Shader;
    bool m_Changed;
};

#endif // QGLSLEDITOR_H
