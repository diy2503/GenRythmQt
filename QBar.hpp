#ifndef QBAR_HPP
#define QBAR_HPP

#include <QLayout>
#include <QLabel>
#include "QNote.hpp"
#include "CBar.hpp"

class QBar
{
public:
    QBar(QLayout* p_pLayout);
    virtual ~QBar(void);

    bool Display(CBarPtr p_pBar) const;

private:
    QLayout* m_pLayoutBarCH = nullptr;
    QLayout* m_pLayoutBarCC = nullptr;
    QLayout* m_pLayoutBarGC = nullptr;

    vector<QNote*> m_QnotesCH;
    vector<QNote*> m_QnotesCC;
    vector<QNote*> m_QnotesGC;
};

typedef shared_ptr<QBar> QBarPtr;

#endif // QBAR_HPP
