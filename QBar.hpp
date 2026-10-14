#ifndef QBAR_HPP
#define QBAR_HPP

#include <QLayout>
#include <QLabel>
#include "CBar.hpp"

class QBar
{
public:
    QBar(QLayout* p_pLayout);
    virtual ~QBar(void);

    virtual bool Display(CBarPtr p_pBar) const = 0;

protected:
    vector<QLabel*> m_noteLabelCH;
    vector<QLabel*> m_noteLabelCC;
    vector<QLabel*> m_noteLabelGC;

    QLayout* m_pLayoutBarCH = nullptr;
    QLayout* m_pLayoutBarCC = nullptr;
    QLayout* m_pLayoutBarGC = nullptr;
};

typedef shared_ptr<QBar> QBarPtr;

#endif // QBAR_HPP
