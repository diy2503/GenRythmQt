#ifndef QBAR_IMG_HPP
#define QBAR_IMG_HPP

#include <QLayout>
#include <QLabel>
#include "QBar.hpp"

class QBarImg : public QBar
{
public:
    explicit QBarImg(const CBarPtr p_pBar, const QLayout* p_pLayout);
    virtual ~QBarImg(void) override;
};

typedef shared_ptr<QBarImg> QBarImgPtr;

#endif // QBAR_IMG_HPP
