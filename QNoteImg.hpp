#ifndef QNOTE_IMG_HPP
#define QNOTE_IMG_HPP

#include <QLabel>
#include "QNote.hpp"

class QNoteImg : public QNote
{
public:
    explicit QNoteImg(QLabel *p_pLabel, QObject *parent = nullptr);

    void updateStyle(void) override;
};

typedef shared_ptr<QNoteImg> QNoteImgPtr;
#endif // QNOTE_IMG_HPP
