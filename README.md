# FaceTrackerSteamOSC

SteamLinkでVRChatでフェイストラッキングを動かせるようになる。

Quest Proが必要

アバターの設定が必須

## Build from source

Open with VisualStudio

Build

## Option

ip portSend portRecv

## Avatar setting

中身は「/sl/xrfb/facew/」を「/avatar/parameters/」に書き換えているだけ。

OSCが来たらアバターの表情が動くように設定する。

例：

XR_FACE_EXPRESSION_BROW_LOWERER_R_FB

→/avatar/parameters/BrowLowererR

Boothにアニメーションファイルのサンプルをおいてるのでご参考。

また、それぞれの設定すべき表情は下記から確認可能。

https://developer.oculus.com/documentation/unity/move-face-tracking/

## Donate

https://a3s.booth.pm/items/4715968

## Twitter

https://twitter.com/A3_yuu