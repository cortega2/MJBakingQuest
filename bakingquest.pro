TEMPLATE = subdirs

SUBDIRS = game editor
game.file = src/game.pro
editor.file = src/editor.pro

OTHER_FILES += levels/* \
    pics/* \
    sounds/* \
    sprites/* \



