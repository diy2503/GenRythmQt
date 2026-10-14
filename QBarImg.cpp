#include <cassert>
#include "QBarImg.hpp"
#include "QNoteImg.hpp"

QBarImg::QBarImg(QLayout* p_pLayout)
    :   QBar(p_pLayout)
{
}

QBarImg::~QBarImg()
{
}


bool QBarImg::Display(CBarPtr p_pBar) const
{
    bool l_res = (p_pBar != nullptr);

    for (uint8_t i = 0; i < p_pBar->getLength(); ++i)
    {
        CNotePtr l_pNoteCH = nullptr;
        CNotePtr l_pNoteCC = nullptr;
        CNotePtr l_pNoteGC = nullptr;

        p_pBar->getNote(i, l_pNoteCH, l_pNoteCC, l_pNoteGC);

        static_cast<QNoteImg*>(m_noteLabelCH[i])->setNote(l_pNoteCH);
        static_cast<QNoteImg*>(m_noteLabelCC[i])->setNote(l_pNoteCC);
        static_cast<QNoteImg*>(m_noteLabelGC[i])->setNote(l_pNoteGC);
    }

    return l_res;
}
