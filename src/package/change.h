/********************************************************************
Copyright (c) 2013-2015 - Mogara

This file is part of QSanguosha-Hegemony.

This game is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 3.0
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

See the LICENSE file for more details.

Mogara
*********************************************************************/

#ifndef _H_CHANGE_H
#define _H_CHANGE_H

#include "package.h"
#include "card.h"
#include "skill.h"
#include "standard.h"
#include <QAbstractButton>
#include <QGroupBox>
#include <QDialog>

class SanyaoCard : public SkillCard
{
    Q_OBJECT

public:
    Q_INVOKABLE SanyaoCard();

    bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    void onEffect(const CardEffectStruct &effect) const;
};

class QiceCard : public SkillCard
{
    Q_OBJECT

public:
    Q_INVOKABLE QiceCard();

    bool targetFixed() const;
    bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    bool targetsFeasible(const QList<const Player *> &targets, const Player *Self) const;

    const Card *validate(CardUseStruct &card_use) const;
};

class GuhuoDialog : public QDialog
{
    Q_OBJECT

public:
    static GuhuoDialog *getInstance(const QString &object, bool left = true, bool right = true,
        bool play_only = true, bool slash_combined = false, bool delayed_tricks = false);

    public slots:
    void popup();
    void selectCard(QAbstractButton *button);

protected:
    explicit GuhuoDialog(const QString &object, bool left = true, bool right = true,
        bool play_only = true, bool slash_combined = false, bool delayed_tricks = false);
    virtual bool isButtonEnabled(const QString &button_name) const;
    QAbstractButton *createButton(const Card *card);

    QHash<QString, const Card *> map;

private:
    QGroupBox *createLeft();
    QGroupBox *createRight();
    QButtonGroup *group;

    QString object_name;
    bool play_only; // whether the dialog will pop only during the Play phase
    bool slash_combined; // create one 'Slash' button instead of 'Slash', 'Fire Slash', 'Thunder Slash'
    bool delayed_tricks; // whether buttons of Delayed Tricks will be created

signals:
    void onButtonClick();
};

class ChangePackage : public Package
{
    Q_OBJECT

public:
    ChangePackage();
};

class Pearl : public Treasure
{
    Q_OBJECT

public:
    Q_INVOKABLE Pearl(Card::Suit suit = Heart, int number = 13);
};

class ChangeEquipPackage : public Package
{
    Q_OBJECT

public:
    ChangeEquipPackage();
};

#endif