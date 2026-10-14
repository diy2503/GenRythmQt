#ifndef QNOTE_IMG_HPP
#define QNOTE_IMG_HPP

#include <QLabel>
#include "CNote.hpp"

class QNoteImg : public QLabel
{
public:
    QNoteImg();

    void setNote(CNotePtr p_pNote);
};

typedef shared_ptr<QNoteImg> QNoteImgPtr;
#endif // QNOTE_IMG_HPP
