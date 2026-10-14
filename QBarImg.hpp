#ifndef QBAR_IMG_HPP
#define QBAR_IMG_HPP

#include <QLayout>
#include <QLabel>
#include "QNoteImg.hpp"
#include "QBar.hpp"

class QBarImg : public QBar
{
public:
    explicit QBarImg(QLayout* p_pLayout);
    virtual ~QBarImg(void) override;

    bool Display(CBarPtr p_pBar) const override;
};

typedef shared_ptr<QBarImg> QBarImgPtr;

#endif // QBAR_IMG_HPP
