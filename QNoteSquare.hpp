#ifndef QNOTESQUARE_HPP
#define QNOTESQUARE_HPP

#include "QNote.hpp"

class QNoteSquare : public QNote
{
public:
    explicit QNoteSquare(QLabel *p_pLabel, QObject *parent = nullptr);

    void updateStyle(void) override;

private:
    // Colors palettes
    static QString m_sStyleCH_L;
    static QString m_sStyleCH_H;
    static QString m_sStyleCC_L;
    static QString m_sStyleCC_H;
    static QString m_sStyleGC_L;
    static QString m_sStyleGC_H;
    static QString m_sStyleSILENT_L;
    static QString m_sStyleSILENT_H;
};

#endif // QNOTESQUARE_HPP
