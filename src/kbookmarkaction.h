/*
    This file is part of the KDE project
    SPDX-FileCopyrightText: 1998, 1999 Torben Weis <weis@kde.org>
    SPDX-FileCopyrightText: 2006 Daniel Teske <teske@squorn.de>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KBOOKMARKACTION_H
#define KBOOKMARKACTION_H

#include "kbookmarkactioninterface.h"
#include <QAction>

class KBookmark;
class KBookmarkOwner;

/**
 * This class is a QAction for bookmarks.
 * It provides a nice constructor.
 * And on triggered uses the owner to open the bookmark.
 */
class KBOOKMARKS_EXPORT KBookmarkAction : public QAction, public KBookmarkActionInterface
{
    Q_OBJECT
public:
    KBookmarkAction(const KBookmark &bk, KBookmarkOwner *owner, QObject *parent);
    virtual ~KBookmarkAction();

public Q_SLOTS:
    void slotSelected(Qt::MouseButtons mb, Qt::KeyboardModifiers km);

private Q_SLOTS:
    void slotTriggered();

private:
    KBookmarkOwner *m_pOwner;
};

#endif
