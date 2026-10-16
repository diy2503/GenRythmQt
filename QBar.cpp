#include <cassert>
#include "QBar.hpp"
#include "QNoteSquare.hpp"
#include "QNoteImg.hpp"

QBar::QBar(const CBarPtr p_pBar, const QLayout* p_pLayout, BarType p_type)
{
    assert(p_pLayout != nullptr);
    assert(p_pBar != nullptr);
    assert(p_type < BarType::MAX);

    m_pBar = p_pBar;
    m_eType = p_type;

    // --- Retrieve widgets
    int l_cnt = p_pLayout->count();
    assert(l_cnt >= 4);

    // Retrieve layout for CH, CC and GC bars
    m_pLayoutBarCH = p_pLayout->itemAt(1)->layout();
    m_pLayoutBarCC = p_pLayout->itemAt(2)->layout();
    m_pLayoutBarGC = p_pLayout->itemAt(3)->layout();

    assert(m_pLayoutBarCH != nullptr);
    assert(m_pLayoutBarCC != nullptr);
    assert(m_pLayoutBarGC != nullptr);

    // Retrieve QLabel pointers from Layouts
    for (uint8_t i = 0; i < m_pLayoutBarCH->count(); ++i)
    {
        auto l_pWidget = m_pLayoutBarCH->itemAt(i)->widget();
        auto l_pLabel = qobject_cast<QLabel*>(l_pWidget);
        if (l_pLabel != nullptr)
        {
            m_noteLabelCH.push_back(createQNote(l_pLabel));
        }
    }
    for (uint8_t i = 0; i < m_pLayoutBarCC->count(); ++i)
    {
        auto l_pWidget = m_pLayoutBarCC->itemAt(i)->widget();
        auto l_pLabel = qobject_cast<QLabel*>(l_pWidget);
        if (l_pLabel != nullptr)
        {
            m_noteLabelCC.push_back(createQNote(l_pLabel));
        }
    }
    for (uint8_t i = 0; i < m_pLayoutBarGC->count(); ++i)
    {
        auto l_pWidget = m_pLayoutBarGC->itemAt(i)->widget();
        auto l_pLabel = qobject_cast<QLabel*>(l_pWidget);
        if (l_pLabel != nullptr)
        {
            m_noteLabelGC.push_back(createQNote(l_pLabel));
        }
    }
}

QBar::~QBar()
{
    m_noteLabelCH.clear();
    m_noteLabelCC.clear();
    m_noteLabelGC.clear();

    m_pLayoutBarCH = nullptr;
    m_pLayoutBarCC = nullptr;
    m_pLayoutBarGC = nullptr;

    m_pBar = nullptr;
}

QNote* QBar::createQNote(QLabel *p_pLabel) const
{
    QNote* l_pNote = nullptr;

    switch (m_eType)
    {
    case BarType::SQUARE:   l_pNote = new QNoteSquare(p_pLabel); break;
    case BarType::IMG:      l_pNote = new QNoteImg(p_pLabel); break;
    case BarType::MAX:
    default:
    {}
    }

    return l_pNote;
}

void QBar::Display(void) const
{
    CNotePtr l_pNoteCH = nullptr;
    CNotePtr l_pNoteCC = nullptr;
    CNotePtr l_pNoteGC = nullptr;

    for (uint8_t i = 0; i < m_pBar->getLength(); ++i)
    {
        m_pBar->getNote(i, l_pNoteCH, l_pNoteCC, l_pNoteGC);

        m_noteLabelCH[i]->setNote(l_pNoteCH, false);
        m_noteLabelCC[i]->setNote(l_pNoteCC, false);
        m_noteLabelGC[i]->setNote(l_pNoteGC, false);
    }
}

void QBar::on_playerPosChanged(uint8_t p_pos)
{
    CNotePtr l_pNoteCH = nullptr;
    CNotePtr l_pNoteCC = nullptr;
    CNotePtr l_pNoteGC = nullptr;

    // Highlight proper labels
    m_pBar->getNote(p_pos, l_pNoteCH, l_pNoteCC, l_pNoteGC);
    m_noteLabelCH[p_pos]->setNote(l_pNoteCH, true);
    m_noteLabelCC[p_pos]->setNote(l_pNoteCC, true);
    m_noteLabelGC[p_pos]->setNote(l_pNoteGC, true);

    // Restore previous highlighted labels
    uint8_t l_prevPos = p_pos - 1;
    if (l_prevPos > m_noteLabelCH.size())
    {
        l_prevPos = m_noteLabelCH.size() - 1;
    }

    m_pBar->getNote(l_prevPos, l_pNoteCH, l_pNoteCC, l_pNoteGC);
    m_noteLabelCH[l_prevPos]->setNote(l_pNoteCH, false);
    m_noteLabelCC[l_prevPos]->setNote(l_pNoteCC, false);
    m_noteLabelGC[l_prevPos]->setNote(l_pNoteGC, false);
}

