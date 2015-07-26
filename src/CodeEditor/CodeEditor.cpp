#include <QTextEdit>

#include "CodeEditor.hpp"
#include "CodeGenerator.hpp"
#include "BashHighlighter.hpp"
#include "MatlabHighlighter.hpp"
#include "PythonHighlighter.hpp"
#include "BashGenerator.hpp"
#include "MatlabGenerator.hpp"
#include "PythonGenerator.hpp"

CodeEditor::CodeEditor(
        QWidget* _parent
        ) :
    QTabWidget(_parent)
{
    /// @todo put this in the preferences
//    const int tabWidth = 4;

    //MATLAB (C)
    setupMatlabEditor();
    //Bash
    setupBashEditor();
    //Python
    setupPythonEditor();
}

void CodeEditor::generateCode(
        const QList<NodeTreeItem*>& _nodeList
        )
{
    foreach(QString language, m_programmingLanguages)
    {
        m_textEditors[language]->setPlainText(m_codeGenerators[language]->generateCode(_nodeList));
    }
}

void CodeEditor::setupMatlabEditor(
        )
{
    const int tabWidth = 4;
    QString matlab("MATLAB");
    m_programmingLanguages << matlab;
    QFont matlabFont = QFont("Courier", 10);
    matlabFont.setStyleHint(QFont::Monospace);
    matlabFont.setFixedPitch(true);
    QFontMetrics matlabMetric(matlabFont);

    QTextEdit* matlabEditor = new QTextEdit(this);
    matlabEditor->setFont(matlabFont);
    matlabEditor->setTabStopWidth(tabWidth * matlabMetric.width(' '));

    new MatlabHighlighter(matlabEditor->document());
    m_textEditors[matlab] = matlabEditor;
    m_codeGenerators[matlab] = new MatlabGenerator();
    addTab(m_textEditors[matlab], matlab);
}

void CodeEditor::setupBashEditor(
        )
{
    const int tabWidth = 4;
    QString bash("Bash");
    m_programmingLanguages << bash;
    QFont bashFont = QFont("Courier", 10);
    bashFont.setStyleHint(QFont::Monospace);
    bashFont.setFixedPitch(true);
    QFontMetrics bashMetric(bashFont);

    QTextEdit* bashEditor = new QTextEdit(this);
    bashEditor->setFont(bashFont);
    bashEditor->setTabStopWidth(tabWidth * bashMetric.width(' '));

    new BashHighlighter(bashEditor->document());
    m_textEditors[bash] = bashEditor;
    m_codeGenerators[bash] = new BashGenerator();
    addTab(m_textEditors[bash], bash);
}

void CodeEditor::setupPythonEditor(
        )
{
    const int tabWidth = 4;
    QString python("Python");
    m_programmingLanguages << python;
    QFont pythonFont = QFont("Courier", 10);
    pythonFont.setStyleHint(QFont::Monospace);
    pythonFont.setFixedPitch(true);
    QFontMetrics pythonMetric(pythonFont);

    QTextEdit* pythonEditor = new QTextEdit(this);
    pythonEditor->setFont(pythonFont);
    pythonEditor->setTabStopWidth(tabWidth * pythonMetric.width(' '));

    new PythonHighlighter(pythonEditor->document());
    m_textEditors[python] = pythonEditor;
    m_codeGenerators[python] = new PythonGenerator();
    addTab(m_textEditors[python], python);
}

CodeEditor::~CodeEditor()
{

}
