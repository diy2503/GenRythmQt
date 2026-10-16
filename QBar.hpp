#ifndef QBAR_HPP
#define QBAR_HPP

#include <QLayout>
#include "CBar.hpp"
#include "QNote.hpp"

enum class BarType
{
    SQUARE = 0,
    IMG,
    MAX,
};

class QBar : public QObject
{
    Q_OBJECT
public:
    QBar(const CBarPtr p_pBar, const QLayout* p_pLayout, BarType p_type);
    virtual ~QBar(void);

    void Display(void) const;

private:
    QNote* createQNote(QLabel *p_pLabel) const;

protected slots:
    virtual void on_playerPosChanged(uint8_t p_pos);

protected:
    CBarPtr m_pBar;

    vector<QNote*> m_noteLabelCH;
    vector<QNote*> m_noteLabelCC;
    vector<QNote*> m_noteLabelGC;

    QLayout* m_pLayoutBarCH = nullptr;
    QLayout* m_pLayoutBarCC = nullptr;
    QLayout* m_pLayoutBarGC = nullptr;

private:
    BarType m_eType = BarType::MAX;
};

typedef shared_ptr<QBar> QBarPtr;

#endif // QBAR_HPP
