#ifndef QPLAYER_H
#define QPLAYER_H

#include <QObject>
#include <QSoundEffect>
#include "CPlayer.hpp"

typedef struct
{
    shared_ptr<QSoundEffect> sndFx;
    string file;
    float volume;
} SoundCfg;


class QPlayer : public QObject, public CPlayer
{
    Q_OBJECT
private:
    explicit QPlayer(QObject *parent = nullptr);
    virtual ~QPlayer(void);

    void initSound(NoteInstr p_instr);

public:
    QPlayer(const QPlayer&) = delete;
    QPlayer& operator=(const QPlayer&) = delete;

    static QPlayer& getInstance() {
        static QPlayer m_instance;
        return m_instance;
    }

    // Overriden inhirited methods
    virtual bool setStatus(ePlayStatus p_val);
protected:
    virtual uint32_t playNote(NoteInstr p_notNoteInstr);

    std::array<QSoundEffect, (uint8_t)NoteInstr::MAX> m_sounds;

signals:
    void statusChanged(ePlayStatus p_status);
    void playCC();
    void playGC();
    void playCH();
};

#endif // QPLAYER_H


