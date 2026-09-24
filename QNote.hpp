#ifndef PP
#define PP

#include <QLabel>
#include "CNote.hpp"

class QNote : public QLabel
{
public:
    QNote();

    void setNote(CNotePtr p_pNote);
};

typedef shared_ptr<QNote> QNotePtr;
#endif // PP
