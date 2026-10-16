#ifndef QNOTE_HPP
#define QNOTE_HPP

#include <QLabel>
#include "CNote.hpp"

class QNote : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool highlight
                   READ isHighlight
                       WRITE setHighlight
                           NOTIFY highlightChanged)

public:
    explicit QNote(QLabel *p_pLabel, QObject *parent = nullptr);
    virtual ~QNote(void) {}

    bool isHighlight() const;
    void setHighlight(bool p_bHighlight);

    void setNote(CNotePtr p_pNote, bool p_bHighlight);

signals:
    void highlightChanged(bool p_bHighlight);

protected:
    virtual void updateStyle(void);

protected:
    QLabel*     m_pLabel     = nullptr;
    CNotePtr    m_pNote      = nullptr;
    bool        m_bHighlight = false;
};
typedef shared_ptr<QNote> QNotePtr;
#endif // QNOTE_HPP
