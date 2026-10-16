#include <cassert>
#include "QBarImg.hpp"


QBarImg::QBarImg(const CBarPtr p_pBar, const QLayout* p_pLayout)
    :   QBar(p_pBar, p_pLayout, BarType::IMG)
{
}

QBarImg::~QBarImg()
{
}

