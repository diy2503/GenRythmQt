#ifndef QBAR_SQUARE_H
#define QBAR_SQUARE_H

#include "QBar.hpp"

#define QBS_COLOR_CH        (Qt::green)
#define QBS_COLOR_CC        (Qt::cyan)
#define QBS_COLOR_GC        (Qt::red)
#define QBS_COLOR_BLACK     (Qt::black)

class QBarSquare : public QBar
{
public:
    explicit QBarSquare(QLayout* p_pLayout);
    virtual ~QBarSquare(void) override;

    bool Display(CBarPtr p_pBar) const override;

private:
    static void setNoteColor(QLabel* const p_pLabel, const CNotePtr p_pNote);

    // colors palettes
    static QPalette paletteCH;
    static QPalette paletteCC;
    static QPalette paletteGC;
    static QPalette paletteSILENT;
};

typedef shared_ptr<QBarSquare> QBarSquarePtr;
#endif // QBAR_SQUARE_H
