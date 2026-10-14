#include <cassert>
#include "QBar.hpp"

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

    // Retrieve QLabel pointers from Layouts
    for (uint8_t i = 0; i < m_pLayoutBarCH->count(); ++i)
    {
        auto l_pWidget = m_pLayoutBarCH->itemAt(i)->widget();
        auto l_pLabel = qobject_cast<QLabel*>(l_pWidget);
        if (l_pLabel != nullptr)
        {
            m_noteLabelCH.push_back(l_pLabel);
        }
    }
    for (uint8_t i = 0; i < m_pLayoutBarCC->count(); ++i)
    {
        auto l_pWidget = m_pLayoutBarCC->itemAt(i)->widget();
        auto l_pLabel = qobject_cast<QLabel*>(l_pWidget);
        if (l_pLabel != nullptr)
        {
            m_noteLabelCC.push_back(l_pLabel);
        }
    }
    for (uint8_t i = 0; i < m_pLayoutBarGC->count(); ++i)
    {
        auto l_pWidget = m_pLayoutBarGC->itemAt(i)->widget();
        auto l_pLabel = qobject_cast<QLabel*>(l_pWidget);
        if (l_pLabel != nullptr)
        {
            m_noteLabelGC.push_back(l_pLabel);
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
}
