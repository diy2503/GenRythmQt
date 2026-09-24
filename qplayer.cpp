#include "QPlayer.hpp"
#include "CPlayer.hpp"


#include <QUrl>


#define SOUND_FILE_PATH_CC      "C:/DATA/DEV/GenRythm/sounds/Roland-Kit/Roland R-8/R8Snare01.wav"
#define SOUND_FILE_PATH_GC      "C:/DATA/DEV/GenRythm/sounds/Roland-Kit/Roland R-8/R8Kick01.wav"
#define SOUND_FILE_PATH_CH      "C:/DATA/DEV/GenRythm/sounds/Roland-Kit/Roland R-8/R8Hat_O02.wav"
#define SOUND_VOLUME_DEFAULT    (1.0f)


QPlayer::QPlayer(QObject *parent)
    : QObject{parent}
{
    // Sounds initialisation
    for (uint8_t i = 0; i < (uint8_t)NoteInstr::MAX; ++i)
    {
        initSound((NoteInstr)i);
    }
}

QPlayer::~QPlayer()
{
}

void QPlayer::initSound(NoteInstr p_instr)
{
    QSoundEffect* pSnd = nullptr;

    switch (p_instr)
    {
    case NoteInstr::CC:
    {
        pSnd = &m_sounds[static_cast<uint8_t>(p_instr)];
        pSnd->setSource(QUrl::fromLocalFile(SOUND_FILE_PATH_CC));
        connect(this, &QPlayer::playCC, pSnd, &QSoundEffect::play);
        break;
    }
    case NoteInstr::GC:
    {
        pSnd = &m_sounds[static_cast<uint8_t>(p_instr)];
        pSnd->setSource(QUrl::fromLocalFile(SOUND_FILE_PATH_GC));
        connect(this, &QPlayer::playGC, pSnd, &QSoundEffect::play);
        break;
    }
    case NoteInstr::CH:
    {
        pSnd = &m_sounds[static_cast<uint8_t>(p_instr)];
        pSnd->setSource(QUrl::fromLocalFile(SOUND_FILE_PATH_CH));
        connect(this, &QPlayer::playCH, pSnd, &QSoundEffect::play);
        break;
    }
    case NoteInstr::SILENT:
    default:
    {
        break;
    }
    }

    if (pSnd != nullptr)
    {
        pSnd->setLoopCount(1);
        pSnd->setVolume(SOUND_VOLUME_DEFAULT);
    }
}


bool QPlayer::setStatus(ePlayStatus p_val)
{
    bool bRet = true;

    if (p_val != getStatus())
    {
        bRet = CPlayer::setStatus(p_val);

        if (bRet == true)
        {
            emit statusChanged(p_val);
        }
    }

    return bRet;
}

uint32_t QPlayer::playNote(NoteInstr p_notNoteInstr)
{
    switch (p_notNoteInstr)
    {
    case NoteInstr::CC: emit playCC(); break;
    case NoteInstr::GC: emit playGC(); break;
    case NoteInstr::CH: emit playCH(); break;
    case NoteInstr::SILENT:
    default:    break;
    }

    return 0;   // asynchronous
}


