#include <cassert>
#include "QBar.hpp"
#include "QNote.hpp"

QBar::QBar(QLayout* p_pLayout)
{
    assert(p_pLayout != nullptr);

    int l_cnt = p_pLayout->count();
    assert(l_cnt >= 4);

    // Retrieve layout for CH, CC and GC bars
    m_pLayoutBarCH = p_pLayout->itemAt(1)->layout();
    m_pLayoutBarCC = p_pLayout->itemAt(2)->layout();
    m_pLayoutBarGC = p_pLayout->itemAt(3)->layout();

    assert(m_pLayoutBarCH != nullptr);
    assert(m_pLayoutBarCC != nullptr);
    assert(m_pLayoutBarGC != nullptr);

    // Retrieve QNotes pointers from Layouts
    for (uint8_t i = 0; i < m_pLayoutBarCH->count(); ++i)
    {
        auto l_pWidget = m_pLayoutBarCH->itemAt(i)->widget();
        auto l_pLabel = qobject_cast<QLabel*>(l_pWidget);
        if (l_pLabel != nullptr)
        {
            m_QnotesCH.push_back(static_cast<QNote*>(l_pLabel));
        }
    }
    for (uint8_t i = 0; i < m_pLayoutBarCC->count(); ++i)
    {
        auto l_pWidget = m_pLayoutBarCC->itemAt(i)->widget();
        auto l_pLabel = qobject_cast<QLabel*>(l_pWidget);
        if (l_pLabel != nullptr)
        {
            m_QnotesCC.push_back(static_cast<QNote*>(l_pLabel));
        }
    }
    for (uint8_t i = 0; i < m_pLayoutBarGC->count(); ++i)
    {
        auto l_pWidget = m_pLayoutBarGC->itemAt(i)->widget();
        auto l_pLabel = qobject_cast<QLabel*>(l_pWidget);
        if (l_pLabel != nullptr)
        {
            m_QnotesGC.push_back(static_cast<QNote*>(l_pLabel));
        }
    }
}

QBar::~QBar()
{
    m_pLayoutBarCH = nullptr;
    m_pLayoutBarCC = nullptr;
    m_pLayoutBarGC = nullptr;
}


QLabel* QBar::nextLabel(const QLayout* p_pLayout, uint8_t p_idx, int8_t& p_skipped) const
{
    assert(p_pLayout != nullptr);
    assert(p_idx < p_pLayout->count());

    QLabel* l_pLabel = nullptr;

    p_skipped = -1;

    while ((l_pLabel == nullptr) && (p_idx < p_pLayout->count()))
    {
        auto l_pWidget = p_pLayout->itemAt(++p_idx)->widget();
        l_pLabel = qobject_cast<QLabel*>(l_pWidget);
        p_skipped++;
    }

    return l_pLabel;
}


bool QBar::Display(CBarPtr p_pBar) const
{
    bool l_res = (p_pBar != nullptr);

    for (uint8_t i = 0; i < p_pBar->getLength(); ++i)
    {
        CNotePtr l_pNoteCH = nullptr;
        CNotePtr l_pNoteCC = nullptr;
        CNotePtr l_pNoteGC = nullptr;

        p_pBar->getNote(i, l_pNoteCH, l_pNoteCC, l_pNoteGC);

        m_QnotesCH[i]->setNote(l_pNoteCH);
        m_QnotesCC[i]->setNote(l_pNoteCC);
        m_QnotesGC[i]->setNote(l_pNoteGC);
    }

    return l_res;
}
