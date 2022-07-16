# Copyright 2019 Manna Harbour
# https://github.com/manna-harbour/miryoku

MOUSEKEY_ENABLE = yes # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
#AUTO_SHIFT_ENABLE = yes # Auto Shift

SWAP_HANDS_ENABLE = yes
CAPS_WORD_ENABLE  = yes

OLED_ENABLE = yes
OLED_DRIVER = SSD1306
LTO_ENABLE  = yes

SRC += manna-harbour_miryoku.c # keymaps

include users/manna-harbour_miryoku/custom_rules.mk

include users/manna-harbour_miryoku/post_rules.mk
