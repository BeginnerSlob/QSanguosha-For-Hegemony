--[[********************************************************************
	Copyright (c) 2013-2015 Mogara

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
*********************************************************************]]

-- translation for Hegemony Momentum Package

return {
	["change"] = "君临天下·变",
	["change_equip"] = "君临天下·变",

	["#xunyou"] = "曹魏的谋主",
	["xunyou"] = "荀攸",
	["illustrator:xunyou"] = "未知",
	["qice"] = "奇策",
	[":qice"] = "出牌阶段限一次，你可以将所有手牌当任意一张非延时类锦囊牌使用，你不能以此法使用目标数超过X的牌（X为你的手牌数），此锦囊结算完成后，你可以变更副将。",
	["zhiyu"] = "智愚",
	[":zhiyu"] = "当你受到伤害后，你可以摸一张牌并展示你的所有手牌，若颜色均相同，则伤害来源弃置一张手牌。",

	["#bianhuanghou"] = "奕世之雍容",
	["bianhuanghou"] = "卞皇后",
	["illustrator:bianhuanghou"] = "未知",
	["wanwei"] = "挽危",
	[":wanwei"] = "当你因被其他角色获得或弃置而失去牌时，你可以改为自己选择失去的牌。",
	["yuejian"] = "约俭",
	[":yuejian"] = "与你势力相同角色的弃牌阶段开始时，若其本回合未使用牌指定过除该角色外的角色为目标，则该角色本回合手牌上限等同于其体力上限。",

	["#masu"] = "",
	["masu"] = "马谡",
	["illustrator:masu"] = "未知",
	["sanyao"] = "散谣",
	[":sanyao"] = "出牌阶段限一次，你可以弃置一张牌并选择一名体力值最大的角色，对该角色造成1点伤害。",
	["zhiman"] = "制蛮",
	[":zhiman"] = "当你对其他角色造成伤害时，你可以防止此伤害，获得该角色装备区或判定区里的一张牌，然后你可以变更副将。",

	["#shamoke"] = "",
	["shamoke"] = "沙摩柯",
	["illustrator:shamoke"] = "未知",
	["jili"] = "蒺藜",
	[":jili"] = "每当你于出牌阶段内使用第X张牌时，你可以摸X张牌；你可以额外使用X张【杀】（X为你装备区里武器牌的攻击范围）。",

	["#lingtong"] = "豪情烈胆",
	["lingtong"] = "凌统",
	["illustrator:lingtong"] = "",
	["liefeng"] = "烈风",
	[":liefeng"] = "当你失去装备牌后，你可以弃置一名其他角色的一张牌。",
	["xuanlve"] = "旋略",
	[":xuanlve"] = "限定技，出牌阶段，你可以获得场上至多三张装备牌，然后将这些牌分别置入至多三名角色的装备区内。",
	
	["#lvfan"] = "忠笃亮道",
	["lvfan"] = "吕范",
	["illustrator:lvfan"] = "未知",
	["diaodu"] = "调度",
	[":diaodu"] = "出牌阶段限一次，你可令所有与你势力相同的角色依次选择一项：1. 使用手牌中的一张装备牌；2. 将装备区里的一张牌移动至另一名与你势力相同的角色的装备区里。",
	["xingcai"] = "兴财",
	[":xingcai"] = "其他角色的出牌阶段结束时，若你于此阶段失去了X张或更多的牌，则你可以将手牌摸至体力上限，然后可以变更副将（X为你已损失的体力值）。",

	["#zuoci"] = "谜之仙人",
	["zuoci"] = "左慈",
	["illustrator:zuoci"] = "未知",
	["huashen"] = "化身",
	[":huashen"] = "准备阶段开始时，你可以观看剩余武将牌堆中的五张牌，亮出其中两张势力相同的武将牌，将这些武将牌置于你的武将牌旁，称为“化身”（若已有“化身”则将原来的“化身”置入剩余的武将牌堆），你获得“化身”的技能，暗置你的另一张武将牌。左慈处于明置状态时，你不能明置另一张武将牌。",
	["xinsheng"] = "新生",
	[":xinsheng"] = "当你受到伤害后，你可以从剩余武将牌堆中连续亮出武将牌直到亮出一张与“化身”势力相同的武将牌。你可以将之与一张“化身”替换。",

	["#licuiguosi"] = "飞熊倾祸",
	["licuiguosi"] = "李催＆郭汜",
	["&licuiguosi"] = "李催郭汜",
	["illustrator:licuiguosi"] = "未知",
	["xichou"] = "隙仇",
	[":xichou"] = "锁定技，当你首次明置此武将牌时，你加2点体力上限，回复2点体力,；当你于出牌阶段内使用与此阶段内你使用的上一张牌颜色不同的牌时，若没有角色处于濒死状态，你失去1点体力。",

	["#lord_sunquan"] = "",
	["lord_sunquan"] = "孙权-君",
	["&lord_sunquan"] = "孙权" ,
	["illustrator:lord_sunquan"] = "未知",
--[[
	["wuxin"] = "悟心",
	[":wuxin"] = "摸牌阶段开始时，你可以观看牌堆顶的X张牌（X为群势力角色数），然后你可以改变这些牌的顺序。",
	["hongfa"] = "弘法",
	[":hongfa"] = "君主技，当此武将牌明置时，你获得\"江东水势图\"；" ..
				  "君主技，准备阶段开始时，若没有\"天兵\"，你将牌堆顶的X张牌置于\"江东水势图\"上，称为\"天兵\"（X为群势力角色数）。\n\n" ..
				  "#\"江东水势图\"\n" ..
				  "你执行的效果中的\"群势力角色数\"+X（X为不大于\"天兵\"数的自然数）；" ..
				  "每当你失去体力时，你可以将一张\"天兵\"置入弃牌堆，防止此失去体力；" ..
				  "与你势力相同的角色可以将一张\"天兵\"当【杀】使用或打出。",
	["heavenly_army"] = "天兵",
	["hongfa_slash"] = "弘法",
	["#HongfaTianbing"] = "%from 发动了“<font color=\"yellow\"><b>黄巾天兵符</b></font>”的效果，令群势力角色数%arg",
	["wendao"] = "问道",
	[":wendao"] = "出牌阶段限一次，你可以弃置一张红色牌，获得弃牌堆里或场上的一张【太平要术】。",
	["@hongfa-prevent"] = "你可以发动“弘法”，防止此次失去体力",
	["~hongfa1"] = "选择一张\"天兵\"→点击确定",
	["@hongfa-tianbing"] = "<font color='#ffcc33'><b>%src</b></font> 你可以发动“弘法”，令“群势力角色数”+X",
	["~hongfa2"] = "选择X张\"天兵\"→点击确定",
]]
	["Pearl"] = "定澜夜明珠",
	[":Pearl"] = "装备牌·宝物\n\n技能：",
--[[
	["#PeaceSpellNatureDamage"] = "【<font color=\"yellow\"><b>太平要术</b></font>】的效果被触发，防止了 %from 对 %to 造成的 %arg 点 %arg2 伤害" ,
	["#PeaceSpellLost"] = "%from 失去了装备区中的【<font color=\"yellow\"><b>太平要术</b></font>】，须失去1点体力并摸两张牌" ,
]]
}
