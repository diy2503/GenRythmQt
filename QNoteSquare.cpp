#include "QNoteSquare.hpp"

#define STYLE_CH_L  "background-color: darkred;       border-color: rgb(200, 200, 200); border-style: solid; border-width: 1px; border-radius: 5px"
#define STYLE_CH_H  "background-color: red;           border-color: rgb(255, 255, 255); border-style: solid; border-width: 1px; border-radius: 5px"
#define STYLE_CC_L  "background-color: darkcyan;      border-color: rgb(200, 200, 200); border-style: solid; border-width: 1px; border-radius: 5px"
#define STYLE_CC_H  "background-color: cyan;          border-color: rgb(255, 255, 255); border-style: solid; border-width: 1px; border-radius: 5px"
#define STYLE_GC_L  "background-color: darkgreen;     border-color: rgb(200, 200, 200); border-style: solid; border-width: 1px; border-radius: 5px"
#define STYLE_GC_H  "background-color: lightgreen;    border-color: rgb(255, 255, 255); border-style: solid; border-width: 1px; border-radius: 5px"
#define STYLE_S_L   "background-color: transparent;   border-color: rgb(200, 200, 200); border-style: solid; border-width: 1px; border-radius: 5px"
#define STYLE_S_H   "background-color: rgb(50,50,50); border-color: rgb(255, 255, 255); border-style: solid; border-width: 1px; border-radius: 5px"

QString QNoteSquare::m_sStyleCH_L       = STYLE_CH_L;
QString QNoteSquare::m_sStyleCH_H       = STYLE_CH_H;
QString QNoteSquare::m_sStyleCC_L       = STYLE_CC_L;
QString QNoteSquare::m_sStyleCC_H       = STYLE_CC_H;
QString QNoteSquare::m_sStyleGC_L       = STYLE_GC_L;
QString QNoteSquare::m_sStyleGC_H       = STYLE_GC_H;
QString QNoteSquare::m_sStyleSILENT_L   = STYLE_S_L;
QString QNoteSquare::m_sStyleSILENT_H   = STYLE_S_H;

QNoteSquare::QNoteSquare(QLabel *p_pLabel, QObject *parent/*nullptr*/)
    : QNote(p_pLabel, parent)
{

}

void QNoteSquare::updateStyle(void)
{  
    if ((m_pNote != nullptr) && (m_pLabel != nullptr))
    {
        QString l_style;

        switch (m_pNote->getInstr())
        {
        case NoteInstr::CC: l_style = (m_bHighlight? m_sStyleCC_H : m_sStyleCC_L); break;
        case NoteInstr::GC: l_style = (m_bHighlight? m_sStyleGC_H : m_sStyleGC_L); break;
        case NoteInstr::CH: l_style = (m_bHighlight? m_sStyleCH_H : m_sStyleCH_L); break;
        case NoteInstr::SILENT:
        case NoteInstr::MAX:
        default:
            l_style = (m_bHighlight? m_sStyleSILENT_H : m_sStyleSILENT_L);
            break;
        }

        m_pLabel->setStyleSheet(l_style);
    }
}
