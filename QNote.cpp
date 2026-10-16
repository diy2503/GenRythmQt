#include "QNote.hpp"

#define QBS_LINE_WIDTH_L     1
#define QBS_LINE_WIDTH_H     2
#define QBS_STYLE       (QFrame::Panel | QFrame::Plain)


QNote::QNote(QLabel *p_pLabel, QObject *parent/*nullptr*/)
    : QObject(parent)
    , m_pLabel(p_pLabel)
{
}

bool QNote::isHighlight() const
{
    return m_bHighlight;
}

void QNote::setHighlight(bool p_bHighlight)
{
    if (m_bHighlight != p_bHighlight)
    {
        m_bHighlight = p_bHighlight;
        updateStyle();
    }
}

void QNote::setNote(CNotePtr p_pNote, bool p_bHighlight)
{
    bool bInvalidate = false;

    if (p_pNote != m_pNote)
    {
        m_pNote = p_pNote;
        bInvalidate = true;
    }

    if (m_bHighlight != p_bHighlight)
    {
        m_bHighlight = p_bHighlight;
        bInvalidate = true;
    }

    if (bInvalidate == true)
    {
        updateStyle();
    }
}

void QNote::updateStyle()
{
    if (m_pLabel != nullptr)
    {
        m_pLabel->setLineWidth(m_bHighlight? QBS_LINE_WIDTH_H : QBS_LINE_WIDTH_L);
    }
}
