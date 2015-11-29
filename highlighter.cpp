#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::blue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b"   << "\\bconst\\b"    << "\\bdouble\\b"
                    << "\\benum\\b"   << "\\bexplicit\\b" << "\\bint\\b"
                    << "\\blong\\b"   << "\\bshort\\b"    << "\\bsigned\\b"
                    << "\\bstatic\\b" << "\\bunsigned\\b" << "\\bvolatile\\b"
                    << "string" << "\\breturn\\b";

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    actionFormat.setForeground(Qt::green);
    actionFormat.setFontWeight(QFont::Bold);
    QStringList keywordActions;
    keywordActions << "\\bfor\\b"     << "\\bwhile\\b" << "\\bcase\\b"
                   << "\\bforeach\\b" << "\\bdo\\b"    <<"\\bswich\\b"
                   << "\\+\\+"        <<"\\-\\-"       << "\\+\\="
                   << "\\-\\="        << "\\*\\="      << "\\/\\="
                   << "\\<"           << "\\>"         << "\\>\\="
                   << "\\=\\=";

    foreach (const QString &pattern, keywordActions) {
        rule.pattern = QRegExp(pattern);
        rule.format = actionFormat;
        highlightingRules.append(rule);
    }

    singleLineCommentFormat.setForeground(QColor(243,114,89));
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(QColor(243,114,89));

    quotationFormat.setForeground(Qt::magenta);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    rule.pattern = QRegExp("\'.*\'");
    rule.format = quotationFormat;
    highlightingRules.append(rule);


    functionFormat.setFontItalic(true);
    functionFormat.setForeground(QColor(253,245,169));
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    setCurrentBlockState(0);

int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
