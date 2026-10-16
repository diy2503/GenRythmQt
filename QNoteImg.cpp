#include "QNoteImg.hpp"
#include "CImageBuffer.hpp"

QNoteImg::QNoteImg(QLabel *p_pLabel, QObject *parent/*nullptr*/)
    : QNote(p_pLabel, parent)
{

}

void QNoteImg::updateStyle(void)
{
    if ((m_pNote != nullptr) && (m_pLabel != nullptr))
    {
        m_pNote->checkValidity();

        CImageBufferPtr l_buf = CImageBuffer::render(m_pNote);
        QImage          l_img(l_buf->getBuffer(), l_buf->width(), l_buf->height(), QImage::Format_Indexed8);

        l_img.setColorCount(2);
        l_img.setColor(m_bHighlight? 1 : 0, QColor("black").rgb());
        l_img.setColor(m_bHighlight? 0 : 1, QColor("white").rgb());

        m_pLabel->setPixmap(QPixmap::fromImage(l_img));
    }
}