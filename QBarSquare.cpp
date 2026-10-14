#include "QBarSquare.hpp"

#define QBS_LINE_W      1
#define QBS_STYLE       (QFrame::Panel | QFrame::Plain)

QPalette QBarSquare::paletteCH      = QPalette(QBS_COLOR_CH);
QPalette QBarSquare::paletteCC      = QPalette(QBS_COLOR_CC);
QPalette QBarSquare::paletteGC      = QPalette(QBS_COLOR_GC);
QPalette QBarSquare::paletteSILENT  = QPalette(QBS_COLOR_BLACK);


QBarSquare::QBarSquare(QLayout* p_pLayout)
    :   QBar(p_pLayout)
{
    // Retrieve QNoteImg pointers from Layouts
    for (uint8_t i = 0; i < m_pLayoutBarCH->count(); ++i)
    {
        auto l_pWidget = m_pLayoutBarCH->itemAt(i)->widget();
        auto l_pLabel = qobject_cast<QLabel*>(l_pWidget);
        if (l_pLabel != nullptr)
        {
            l_pLabel->setFrameStyle(QBS_STYLE);
            l_pLabel->setLineWidth(QBS_LINE_W);
            l_pLabel->setAutoFillBackground(true);
            l_pLabel->setPalette(paletteSILENT);
        }
    }
    for (uint8_t i = 0; i < m_pLayoutBarCC->count(); ++i)
    {
        auto l_pWidget = m_pLayoutBarCC->itemAt(i)->widget();
        auto l_pLabel = qobject_cast<QLabel*>(l_pWidget);
        if (l_pLabel != nullptr)
        {
            l_pLabel->setFrameStyle(QBS_STYLE);
            l_pLabel->setLineWidth(QBS_LINE_W);
            l_pLabel->setAutoFillBackground(true);
            l_pLabel->setPalette(paletteSILENT);
        }
    }
    for (uint8_t i = 0; i < m_pLayoutBarGC->count(); ++i)
    {
        auto l_pWidget = m_pLayoutBarGC->itemAt(i)->widget();
        auto l_pLabel = qobject_cast<QLabel*>(l_pWidget);
        if (l_pLabel != nullptr)
        {
            l_pLabel->setFrameStyle(QBS_STYLE);
            l_pLabel->setLineWidth(QBS_LINE_W);
            l_pLabel->setAutoFillBackground(true);
            l_pLabel->setPalette(paletteSILENT);
        }
    }
}

QBarSquare::~QBarSquare()
{

}


bool QBarSquare::Display(CBarPtr p_pBar) const
{
    bool l_res = (p_pBar != nullptr);

    for (uint8_t i = 0; i < p_pBar->getLength(); ++i)
    {
        CNotePtr l_pNoteCH = nullptr;
        CNotePtr l_pNoteCC = nullptr;
        CNotePtr l_pNoteGC = nullptr;

        p_pBar->getNote(i, l_pNoteCH, l_pNoteCC, l_pNoteGC);

        setNoteColor(m_noteLabelCH[i], l_pNoteCH);
        setNoteColor(m_noteLabelCC[i], l_pNoteCC);
        setNoteColor(m_noteLabelGC[i], l_pNoteGC);
    }

    return l_res;
}

void QBarSquare::setNoteColor(QLabel* const p_pLabel, const CNotePtr p_pNote)
{
    if ((p_pLabel != nullptr) && (p_pNote != nullptr))
    {
        switch (p_pNote->getInstr())
        {
        case NoteInstr::CC:
            p_pLabel->setPalette(paletteCC);
            break;
        case NoteInstr::GC:
            p_pLabel->setPalette(paletteGC);
            break;
        case NoteInstr::CH:
            p_pLabel->setPalette(paletteCH);
            break;
        case NoteInstr::SILENT:
        case NoteInstr::MAX:
        default:
            p_pLabel->setPalette(paletteSILENT);
            break;
        }
    }
}
