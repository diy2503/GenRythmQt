#include "QNote.hpp"
#include "CImageBuffer.hpp"

QNote::QNote() {}

void QNote::setNote(CNotePtr p_pNote)
{
    if (p_pNote != nullptr)
    {
        p_pNote->checkValidity();

        CImageBufferPtr l_buf = CImageBuffer::render(p_pNote);
        QImage          l_img(l_buf->getBuffer(), l_buf->width(), l_buf->height(), QImage::Format_Indexed8);

        l_img.setColorCount(2);
        l_img.setColor(0, QColor("black").rgb());
        l_img.setColor(1, QColor("white").rgb());

        setPixmap(QPixmap::fromImage(l_img));
    }
}