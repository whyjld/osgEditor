#ifndef _QSCILEXERGLSL_H__
#define _QSCILEXERGLSL_H__

#include <memory>
#include <sstream>

#include <Qsci/qscilexercustom.h>
#include <Qsci/qscistyle.h>
#include <Qsci/qsciapis.h>

class FlexLexer;

/**
    \class QsciLexerGLSL
    \brief Custom QScintilla lexer for GLSL
    Inherits from QsciLexerCustom to provide formatting specific to GLSL files
*/
class QsciLexerGLSL : public QsciLexerCustom
{
public:
    /**
        \brief enum for supported style types
    */
    enum StyleType
    {
        NONE,         ///<No styling
        DEFAULT,      ///<Default
        NUMBER,       ///<Numbers
        KEYWORD,      ///<GLSL Keywords
        FUNCTION,     ///<Functions
        STRING,       ///<Strings
        COMMENT,      ///<Comments
        OPERATOR,     ///<Operators
        WHITESPACE,   ///<Whitespace
        DATATYPE,     ///<GLSL datatypes
        PREPROCESSOR, ///<Preprocessor commands starting with #
        ILLEGAL       ///<Illegal GLSL characters
    };

    QsciLexerGLSL(QsciScintilla* parent = nullptr);
    virtual ~QsciLexerGLSL();
    virtual void styleText(int start, int end );
    virtual const char* language() const;
    virtual QColor defaultColor(int style) const;
    virtual QColor defaultPaper(int style) const;
    virtual QFont defaultFont(int style) const;
    virtual QString description(int style) const;

protected:
    void RegisterAPI();
    /**
        \brief parent QScintilla instance
    */
    QsciScintilla* m_Parent;
    /**
        \brief GLSL API instance
    */
    QsciAPIs* m_API;
    /**
        \brief Source stream
    */
    std::istringstream m_SourceInStream;
    /**
        \brief flex lexer instance
    */
    FlexLexer* m_FlexScanner;
    /**
        \brief copy constructor
    */
    QsciLexerGLSL( const QsciLexerGLSL & );
    /**
        \brief assignment operator
    */
    QsciLexerGLSL &operator=( const QsciLexerGLSL & );

};

#endif
