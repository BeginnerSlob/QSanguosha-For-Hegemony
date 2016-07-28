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

#include "change.h"
#include "standard-basics.h"
#include "standard-tricks.h"
#include "client.h"
#include "engine.h"
#include "structs.h"
#include "gamerule.h"
#include "settings.h"
#include "json.h"
#include "roomthread.h"
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCommandLinkButton>

class Zhiyu : public MasochismSkill
{
public:
    Zhiyu() : MasochismSkill("zhiyu")
    {
    }

    bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        ServerPlayer *from = data.value<DamageStruct>().from;
        if (player->askForSkillInvoke(this, QVariant::fromValue(from))) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }

        return false;
    }

    void onDamaged(ServerPlayer *player, const DamageStruct &damage) const
    {
        player->drawCards(1, objectName());

        Room *room = player->getRoom();

        if (player->isKongcheng())
            return;
        room->showAllCards(player);

        QList<const Card *> cards = player->getHandcards();
        Card::Color color = cards.first()->getColor();
        bool same_color = true;
        foreach (const Card *card, cards) {
            if (card->getColor() != color) {
                same_color = false;
                break;
            }
        }

        if (same_color && damage.from && damage.from->canDiscard(damage.from, "h"))
            room->askForDiscard(damage.from, objectName(), 1, 1);
    }
};

QiceCard::QiceCard()
{
    will_throw = false;
    handling_method = Card::MethodNone;
}

bool QiceCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const
{
    const Card *card = Self->tag.value("qice").value<const Card *>();
    Card *mutable_card = Sanguosha->cloneCard(card);
    if (mutable_card) {
        mutable_card->addSubcards(this->subcards);
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }
    return mutable_card && targets.length() < Self->getHandcardNum()
        && mutable_card->targetFilter(targets, to_select, Self)
        && !Self->isProhibited(to_select, mutable_card, targets);
}

bool QiceCard::targetFixed() const
{
    const Card *card = Self->tag.value("qice").value<const Card *>();
    Card *mutable_card = Sanguosha->cloneCard(card);
    if (mutable_card) {
        mutable_card->addSubcards(this->subcards);
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }
    return mutable_card && mutable_card->targetFixed();
}

bool QiceCard::targetsFeasible(const QList<const Player *> &targets, const Player *Self) const
{
    const Card *card = Self->tag.value("qice").value<const Card *>();
    Card *mutable_card = Sanguosha->cloneCard(card);
    if (mutable_card) {
        mutable_card->addSubcards(this->subcards);
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }
    if (mutable_card && mutable_card->targetFixed()) {
        int target_num = 0;
        QList<const Player *> players;
        if (mutable_card->isKindOf("BuringCamps")) {
            players = Self->getNextAlive()->getFormation();
        } else if (mutable_card->isKindOf("ImperialOrder")) {
            if (!Self->hasShownOneGeneral())
                players << Self;
            foreach (const Player *p, Self->getAliveSiblings()) {
                if (!p->hasShownOneGeneral())
                    players << p;
            }
        } else if (mutable_card->isKindOf("AOE")) {
            players = Self->getAliveSiblings();
        } else if (mutable_card->isKindOf("GlobalEffect")) {
            players << Self;
            players << Self->getAliveSiblings();
        }
        Q_ASSERT(!players.isEmpty());
        foreach (const Player *p, players) {
            if (Self->isProhibited(p, mutable_card))
                continue;
            ++target_num;
        }
        if (target_num > Self->getHandcardNum())
            return false;
    }
    return mutable_card && mutable_card->targetsFeasible(targets, Self);
}

const Card *QiceCard::validate(CardUseStruct &card_use) const
{
    Card *use_card = Sanguosha->cloneCard(user_string);
    use_card->setSkillName("qice");
    use_card->addSubcards(this->subcards);
    bool available = true;
    foreach (ServerPlayer *to, card_use.to) {
        if (card_use.from->isProhibited(to, use_card)) {
            available = false;
            break;
        }
    }
    available = available && use_card->isAvailable(card_use.from);
    use_card->deleteLater();
    if (!available) return NULL;
    return use_card;
}

GuhuoDialog *GuhuoDialog::getInstance(const QString &object, bool left, bool right,
    bool play_only, bool slash_combined, bool delayed_tricks)
{
    static GuhuoDialog *instance;
    if (instance == NULL || instance->objectName() != object)
        instance = new GuhuoDialog(object, left, right, play_only, slash_combined, delayed_tricks);

    return instance;
}

GuhuoDialog::GuhuoDialog(const QString &object, bool left, bool right, bool play_only,
    bool slash_combined, bool delayed_tricks)
    : object_name(object), play_only(play_only),
    slash_combined(slash_combined), delayed_tricks(delayed_tricks)
{
    setObjectName(object);
    setWindowTitle(Sanguosha->translate(object));
    group = new QButtonGroup(this);

    QHBoxLayout *layout = new QHBoxLayout;
    if (left) layout->addWidget(createLeft());
    if (right) layout->addWidget(createRight());
    setLayout(layout);

    connect(group, SIGNAL(buttonClicked(QAbstractButton *)), this, SLOT(selectCard(QAbstractButton *)));
}

bool GuhuoDialog::isButtonEnabled(const QString &button_name) const
{
    const Card *card = map[button_name];
    QString allowings = Self->property("allowed_guhuo_dialog_buttons").toString();
    if (allowings.isEmpty())
        return !Self->isCardLimited(card, Card::MethodUse, true) && card->isAvailable(Self);
    else {
        if (!allowings.split("+").contains(card->objectName())) // for OLDB~
            return false;
        else
            return !Self->isCardLimited(card, Card::MethodUse, true) && card->isAvailable(Self);
    }
}

void GuhuoDialog::popup()
{
    // for zhanyi

    if (objectName() == "zhanyi" && Self->getMark("ViewAsSkill_zhanyiEffect") == 0) {
        emit onButtonClick();
        return;
    }

    // end

    if (play_only && Sanguosha->currentRoomState()->getCurrentCardUseReason() != CardUseStruct::CARD_USE_REASON_PLAY) {
        emit onButtonClick();
        return;
    }

    bool has_enabled_button = false;
    foreach(QAbstractButton *button, group->buttons()) {
        bool enabled = isButtonEnabled(button->objectName());
        if (enabled)
            has_enabled_button = true;
        button->setEnabled(enabled);
    }
    if (!has_enabled_button) {
        emit onButtonClick();
        return;
    }

    Self->tag.remove(object_name);
    exec();
}

void GuhuoDialog::selectCard(QAbstractButton *button)
{
    const Card *card = map.value(button->objectName());
    Self->tag[object_name] = QVariant::fromValue(card);
    if (button->objectName().contains("slash")) {
        if (objectName() == "guhuo")
            Self->tag["GuhuoSlash"] = button->objectName();
        else if (objectName() == "nosguhuo")
            Self->tag["NosGuhuoSlash"] = button->objectName();
        else if (objectName() == "zhanyi")
            Self->tag["ZhanyiSlash"] = button->objectName();
    }
    emit onButtonClick();
    accept();
}

QGroupBox *GuhuoDialog::createLeft()
{
    QGroupBox *box = new QGroupBox;
    box->setTitle(Sanguosha->translate("basic"));

    QVBoxLayout *layout = new QVBoxLayout;

    QList<const Card *> cards = Sanguosha->findChildren<const Card *>();
    foreach(const Card *card, cards) {
        if (card->getTypeId() == Card::TypeBasic && !map.contains(card->objectName())
            && !ServerInfo.Extensions.contains("!" + card->getPackage())
            && !(slash_combined && map.contains("slash") && card->objectName().contains("slash"))) {
            Card *c = Sanguosha->cloneCard(card->objectName());
            c->setParent(this);
            layout->addWidget(createButton(c));

            if (!slash_combined && card->objectName() == "slash"
                && !ServerInfo.Extensions.contains("!maneuvering")) {
                Card *c2 = Sanguosha->cloneCard(card->objectName());
                c2->setParent(this);
                layout->addWidget(createButton(c2));
            }
        }
    }

    layout->addStretch();
    box->setLayout(layout);
    return box;
}

QGroupBox *GuhuoDialog::createRight()
{
    QGroupBox *box = new QGroupBox(Sanguosha->translate("trick"));
    QHBoxLayout *layout = new QHBoxLayout;

    QGroupBox *box1 = new QGroupBox(Sanguosha->translate("single_target_trick"));
    QVBoxLayout *layout1 = new QVBoxLayout;

    QGroupBox *box2 = new QGroupBox(Sanguosha->translate("multiple_target_trick"));
    QVBoxLayout *layout2 = new QVBoxLayout;

    QGroupBox *box3 = new QGroupBox(Sanguosha->translate("delayed_trick"));
    QVBoxLayout *layout3 = new QVBoxLayout;

    QList<const Card *> cards = Sanguosha->findChildren<const Card *>();
    foreach(const Card *card, cards) {
        if (card->getTypeId() == Card::TypeTrick && (delayed_tricks || card->isNDTrick())
            && !map.contains(card->objectName())
            && !ServerInfo.Extensions.contains("!" + card->getPackage())) {
            Card *c = Sanguosha->cloneCard(card->objectName());
            c->setSkillName(object_name);
            c->setParent(this);

            QVBoxLayout *layout;
            if (c->isKindOf("DelayedTrick"))
                layout = layout3;
            else if (c->isKindOf("SingleTargetTrick"))
                layout = layout1;
            else
                layout = layout2;
            layout->addWidget(createButton(c));
        }
    }

    box->setLayout(layout);
    box1->setLayout(layout1);
    box2->setLayout(layout2);
    box3->setLayout(layout3);

    layout1->addStretch();
    layout2->addStretch();
    layout3->addStretch();

    layout->addWidget(box1);
    layout->addWidget(box2);
    if (delayed_tricks)
        layout->addWidget(box3);
    return box;
}

QAbstractButton *GuhuoDialog::createButton(const Card *card)
{
    if (card->objectName() == "slash" && map.contains(card->objectName()) && !map.contains("normal_slash")) {
        QCommandLinkButton *button = new QCommandLinkButton(Sanguosha->translate("normal_slash"));
        button->setObjectName("normal_slash");
        button->setToolTip(card->getDescription());

        map.insert("normal_slash", card);
        group->addButton(button);

        return button;
    } else {
        QCommandLinkButton *button = new QCommandLinkButton(Sanguosha->translate(card->objectName()));
        button->setObjectName(card->objectName());
        button->setToolTip(card->getDescription());

        map.insert(card->objectName(), card);
        group->addButton(button);

        return button;
    }
}

class Qice : public ViewAsSkill
{
public:
    Qice() : ViewAsSkill("qice")
    {
    }

    QDialog *getDialog() const
    {
        return GuhuoDialog::getInstance("qice", false);
    }

    bool viewFilter(const QList<const Card *> &, const Card *to_select) const
    {
        return !to_select->isEquipped();
    }

    const Card *viewAs(const QList<const Card *> &cards) const
    {
        if (cards.length() < Self->getHandcardNum())
            return NULL;

        const Card *c = Self->tag.value("qice").value<const Card *>();
        if (c) {
            QiceCard *card = new QiceCard;
            card->setUserString(c->objectName());
            card->addSubcards(cards);
            card->setShowSkill(objectName());
            return card;
        } else
            return NULL;
    }

    bool isEnabledAtPlay(const Player *player) const
    {
        if (player->isKongcheng())
            return false;
        else
            return !player->hasUsed("QiceCard");
    }
};

SanyaoCard::SanyaoCard()
{
}

bool SanyaoCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const
{
    if (!targets.isEmpty()) return false;
    QList<const Player *> players = Self->getAliveSiblings();
    players << Self;
    int max = -1000;
    foreach(const Player *p, players) {
        if (max < p->getHp())
            max = p->getHp();
    }
    return to_select->getHp() == max;
}

void SanyaoCard::onEffect(const CardEffectStruct &effect) const
{
    effect.from->getRoom()->damage(DamageStruct("sanyao", effect.from, effect.to));
}

class Sanyao : public OneCardViewAsSkill
{
public:
    Sanyao() : OneCardViewAsSkill("sanyao")
    {
        filter_pattern = ".!";
    }

    bool isEnabledAtPlay(const Player *player) const
    {
        return player->canDiscard(player, "he") && !player->hasUsed("SanyaoCard");
    }

    const Card *viewAs(const Card *originalcard) const
    {
        SanyaoCard *first = new SanyaoCard;
        first->addSubcard(originalcard->getId());
        first->setSkillName(objectName());
        first->setShowSkill(objectName());
        return first;
    }
};

ChangePackage::ChangePackage()
    : Package("change")
{
    General *xunyou = new General(this, "xunyou", "wei", 3);
    xunyou->addSkill(new Zhiyu);
    xunyou->addSkill(new Qice);

    General *bianhuanghou = new General(this, "bianhuanghou", "wei", 3, false);
    bianhuanghou->addCompanion("caocao");

    General *masu = new General(this, "masu", "shu", 3);
    masu->addSkill(new Sanyao);

    General *shamoke = new General(this, "shamoke", "shu");
    Q_UNUSED(shamoke);

    General *lingtong = new General(this, "lingtong", "wei");
    lingtong->addCompanion("ganning");

    General *lvfan = new General(this, "lvfan", "wei", 3);
    Q_UNUSED(lvfan);

    General *zuoci = new General(this, "zuoci", "qun", 3);
    zuoci->addCompanion("yuji");

    General *licuiguosi = new General(this, "licuiguosi", "qun");
    licuiguosi->addCompanion("jiaxu");

    General *sunquan = new General(this, "lord_sunquan$", "wu", 4, true, true);
    Q_UNUSED(sunquan);

    addMetaObject<QiceCard>();
    addMetaObject<SanyaoCard>();
}

ADD_PACKAGE(Change)

Pearl::Pearl(Suit suit, int number) : Treasure(suit, number)
{
    setObjectName("Pearl");
}

ChangeEquipPackage::ChangeEquipPackage() : Package("change_equip", CardPack)
{
    Pearl *p = new Pearl();
    p->setParent(this);
}

ADD_PACKAGE(ChangeEquip)