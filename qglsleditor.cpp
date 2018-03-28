#include "qglsleditor.h"
#include "glsl/QsciLexerGlsl.h"

#include <Qsci/qscicommandset.h>

#include <QMessageBox>
#include <QAction>
#include <QIcon>

QGLSLEditor::QGLSLEditor(QWidget *parent)
    : QsciScintilla(parent)
    , m_SearchWidget(nullptr)
    , m_SearchLineEdit(nullptr)
    , m_Changed(false)
{
    setLexer(new QsciLexerGLSL(this));

    setMarginType(0, MarginType::NumberMargin);
    setMarginWidth(0, " 012");
    setMarginsForegroundColor(QColor(128, 128, 128));

    setMarginType(1,MarginType::SymbolMargin);
    setMarginWidth(1, 12);
    setMarginMarkerMask(1, (1 << MarkerType::ERROR) | (1 << MarkerType::WARNING));

    setCaretForegroundColor(QColor(247, 247, 241));
    setCaretWidth(2);

    setBraceMatching(BraceMatch::SloppyBraceMatch);
    setMatchedBraceBackgroundColor(QColor(62, 61, 50));
    setUnmatchedBraceBackgroundColor(QColor(249, 38, 114));

    setAutoIndent(true);
    setIndentationsUseTabs(false);
    setIndentationWidth(4);

    SendScintilla(QsciScintillaBase::SCI_SETSCROLLWIDTHTRACKING, 1);
    SendScintilla(QsciScintillaBase::SCI_SETSCROLLWIDTH, 5);

    QIcon errorIcon = QIcon::fromTheme(QString("dialog-error"));
    QIcon warnIcon = QIcon::fromTheme(QString("dialog-warning"));

    markerDefine(errorIcon.pixmap(10,10), ERROR);
    markerDefine(warnIcon.pixmap(10,10), WARNING);

    standardCommands()->boundTo(Qt::Key_Slash | Qt::CTRL)->setKey(0);

    QAction *commentAction = new QAction(this);
    commentAction->setShortcut(Qt::Key_Slash | Qt::CTRL);

    connect(commentAction, SIGNAL(triggered()), this, SLOT(comment()));
    addAction(commentAction);

    QAction *searchAction = new QAction(this);
    searchAction->setShortcut(Qt::Key_F | Qt::CTRL);
    connect(searchAction, SIGNAL(triggered()), this, SLOT(toggleSearchBox()));
    addAction(searchAction);

    m_SearchIndicator = indicatorDefine(IndicatorStyle::PlainIndicator, -1);
    setIndicatorDrawUnder(true, m_SearchIndicator);
    setIndicatorForegroundColor(QColor(142,143,137,0));
    setIndicatorOutlineColor(QColor(142,143,137,255));

    connect(this, SIGNAL(SCN_CHARADDED(int)), this, SLOT(charAdded(int)));
    connect(this, SIGNAL(SCN_FOCUSIN()), this, SLOT(resetHighlightColour()));
}

void QGLSLEditor::setSearchWidget(QWidget* searchWidget, QLineEdit* searchLineEdit)
{
    m_SearchWidget = searchWidget;
    m_SearchLineEdit = searchLineEdit;

    connect(m_SearchLineEdit, SIGNAL(returnPressed()), this, SLOT(searchNext()));
}

void QGLSLEditor::setShader(osg::Shader* shader)
{
    if(shader != m_Shader.get())
    {
        if(m_Changed && !!m_Shader)
        {
            if(QMessageBox::Yes == QMessageBox::warning(NULL, tr("Warning"), tr("Save current shader source?"), QMessageBox::Yes | QMessageBox::No))
            {
                m_Shader->setShaderSource(text().toStdString());
            }
            m_Changed = false;
        }
        m_Shader = shader;
        setText(m_Shader->getShaderSource().c_str());
    }
}

void QGLSLEditor::apply()
{
    if(!!m_Shader)
    {
        m_Shader->setShaderSource(text().toStdString());
        m_Changed = false;
    }
}

void QGLSLEditor::clearErrors()
{
    markerDeleteAll(MarkerType::ERROR);
    markerDeleteAll(MarkerType::WARNING);
}

void QGLSLEditor::searchNext()
{
    QString st = m_SearchLineEdit->text();
    if(st.length() > 0 && findFirst(st, false, false, false, true))
    {
        setSelectionBackgroundColor(QColor(230, 219, 116));
        setSelectionForegroundColor(QColor(39,40,34));
    }
}

void QGLSLEditor::searchPrev()
{
    QString st = m_SearchLineEdit->text();
    if(st.length() > 0 && findFirst(st, false, false, false, true, false))
    {
        findNext();
        setSelectionBackgroundColor(QColor(230, 219, 116));
        setSelectionForegroundColor(QColor(39,40,34));
    }
    findNext();
}

void QGLSLEditor::highlightAllSearch()
{
    clearIndicatorRange(0, 0, lines(), text(lines()).length(), m_SearchIndicator);
    QString st = m_SearchLineEdit->text();
    if(st.length()==0)
    {
        return;
    }

    for(int c = text().indexOf(st, 0, Qt::CaseSensitivity::CaseInsensitive);
        c != -1;
        c = text().indexOf(st, c + 1, Qt::CaseSensitivity::CaseInsensitive))
    {
        int line;
        int indexFrom;
        lineIndexFromPosition(c, &line, &indexFrom);
        int indexTo = indexFrom + st.length();
        fillIndicatorRange(line, indexFrom, line, indexTo, m_SearchIndicator);
  }
}

void QGLSLEditor::highlightAllSearch(const QString& text)
{
    (text);
    highlightAllSearch();
}

void QGLSLEditor::toggleSearchBox()
{
    if(nullptr != m_SearchLineEdit && nullptr != m_SearchWidget)
    {
        bool searchFocus = m_SearchLineEdit->hasFocus();
        if(!searchFocus)
        {
            connect(this, SIGNAL(textChanged()), this, SLOT(highlightAllSearch()));
            m_SearchWidget->show();
            m_SearchLineEdit->setFocus();
        }
        else
        {
            disconnect(this, SIGNAL(textChanged()), this, SLOT(highlightAllSearch()));
            m_SearchWidget->hide();
            setFocus();
            clearIndicatorRange(0, 0, lines(), text(lines()).length(), m_SearchIndicator);
        }
    }
}

void QGLSLEditor::comment()
{
    beginUndoAction();

    int lineFrom;
    int indexFrom;
    int lineTo;
    int indexTo;
    if(hasSelectedText())
    {
        getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
    }
    else
    {
        getCursorPosition(&lineFrom, &indexFrom);
        lineTo = lineFrom;
        indexTo = indexFrom;
    }

    bool commented = true;
    for(int l = lineFrom;l <= lineTo;++l)
    {
        if(!text(l).startsWith("//"))
        {
            commented = false;
            break;
        }
    }

    if(commented)
    {
        for(int l = lineFrom;l <= lineTo;++l)
        {
            setSelection(l, 0, l, 2);
            removeSelectedText();
        }

        indexTo -= 2;
        if(indexFrom > 1)
        {
            indexFrom -= 2;
        }
    }
    else
    {
        for(int l = lineFrom;l <= lineTo;++l)
        {
            insertAt(QString("//"), l, 0);
        }

        indexTo += 2;
        if(indexFrom != 0)
        {
            indexFrom += 2;
        }
    }

    setSelection(lineFrom,indexFrom,lineTo,indexTo);
    endUndoAction();
}

void QGLSLEditor::charAdded(int c)
{
    switch(c)
    {
    case (int) '(':
        autoClose(QString(')'));
        break;
    case (int) '{':
        autoClose(QString('}'));
        break;
    case (int) '[':
        autoClose(QString(']'));
        break;
    case (int) ')':
        closing(QString(')'));
        break;
    case (int) '}':
        closing(QString('}'));
        break;
    case (int) ']':
        closing(QString(']'));
        break;
    case (int) '"':
        if(!closing(QString('"')))
        {
            autoClose(QString('"'));
        }
        break;
    case (int) '\n':
        braceIndent();
        break;
    }
    m_Changed = true;
}

void QGLSLEditor::resetHighlightColour()
{
    setSelectionBackgroundColor(QColor(61, 61, 52));
    resetSelectionForegroundColor();
}

bool QGLSLEditor::autoClose(const QString close)
{
    int cursorIndex;
    int cursorLine;
    getCursorPosition(&cursorLine, &cursorIndex);
    int length = lineLength(cursorLine);

    if (lines() - 1 == cursorLine)
    {
        ++length;
    }

    if(length - 1 == cursorIndex
            || text(cursorLine).at(cursorIndex).toLatin1() == ' ')
    {
        insert(close);
        return true;
    }
    return false;
}

bool QGLSLEditor::closing(const QString close)
{
    int cursorIndex;
    int cursorLine;
    getCursorPosition(&cursorLine, &cursorIndex);

    int length = lineLength(cursorLine);
    if(lines() - 1 == cursorLine && length == cursorIndex)
    {
        return false;
    }

    if(text(cursorLine).at(cursorIndex) == close.at(0))
    {
        setSelection(cursorLine, cursorIndex, cursorLine, cursorIndex + 1);
        removeSelectedText();
        return true;
    }


    if(close == QString('}') && indentation(cursorLine) + 1 == cursorIndex)
    {
        int indentSize = indentation(cursorLine)-indentationWidth();
        if(indentSize < 0)
        {
            indentSize = 0;
        }
        setIndentation(cursorLine, indentSize);
    }
    return false;
}

void QGLSLEditor::braceIndent()
{
    int cursorLine;
    int cursorIndex;
    getCursorPosition(&cursorLine, &cursorIndex);
    if(0 == cursorLine)
    {
        return;
    }

    QString currentLine;
    QString previousLine;

    currentLine = text(cursorLine);
    previousLine = text(cursorLine - 1);

    if(previousLine.endsWith("{\n"))
    {
        int indentSize = indentation(cursorLine-1);
        setIndentation(cursorLine, indentSize + indentationWidth());
        cursorIndex = cursorIndex + indentationWidth();
        setCursorPosition(cursorLine, cursorIndex);
        currentLine = text(cursorLine);

        if(currentLine.indexOf("}") == cursorIndex)
        {
            insert(QString("\n"));
        }
    }
    else if(currentLine.indexOf("}") == cursorIndex)
    {
        int indentSize = indentation(cursorLine)-indentationWidth();
        if(indentSize < 0)
        {
            indentSize = 0;
        }
        setIndentation(cursorLine, indentSize);
    }
}
