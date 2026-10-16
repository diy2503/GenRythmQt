#ifndef QBAR_SQUARE_H
#define QBAR_SQUARE_H

#include "QBar.hpp"


class QBarSquare : public QBar
{
public:
    explicit QBarSquare(const CBarPtr p_pBar, const QLayout* p_pLayout);
    virtual ~QBarSquare(void) override;
};

typedef shared_ptr<QBarSquare> QBarSquarePtr;
#endif // QBAR_SQUARE_H
