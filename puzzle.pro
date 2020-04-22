QT += core gui
QT += widgets sql multimedia network quick quickwidgets

QMAKE_CXXFLAGS += -std=c++17
android{
QMAKE_LINK += -nostdlib++
}

TARGET = puzzle
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += "_GLIBCXX_USE_CXX11_ABI=0"

HEADERS += \
    src/database/dbfacade.h \
    src/database/jsonparser.h \
    src/database/levelsdbfacade.h \
    src/database/levelstructures.h \
    src/database/settingsdbfacade.h \
    src/game/gamemanager.h \
    src/game/itemground.h \
    src/game/pathpoints.h \
    src/game/puzzlegame.h \
    src/game/puzzleitem/movableitem.h \
    src/game/puzzleitem/puzzleitem.h \
    src/game/puzzleitem/puzzlematrix.h \
    src/game/puzzleitem/rotatableitem.h \
    src/game/puzzleitem/selectableitem.h \
    src/game/puzzleitem/settableitem.h \
    src/game/puzzlepath.h \
    src/game/puzzleview.h \
    src/game/random_points.h \
    src/menu/level_icons_view/iconsview.h \
    src/menu/level_icons_view/levelicon.h \
    src/menu/level_icons_view/menuiconproxy.h \
    src/menu/levelmenuscreen.h \
    src/menu/mainmenuscreen.h \
    src/mode.h \
    src/screen_controller/gamescreencontroller.h \
    src/screen_controller/levelmenuscreencontroller.h \
    src/screen_controller/mainmenuscreencontroller.h \
    src/screen_controller/screensstack.h \
    src/screen_controller/settingsscreencontroller.h \
    src/screen_controller/testingscreencontroller.h \
    src/settings/optionswidget.h \
    src/settings/update/eralistmodel.h \
    src/settings/update/loader.h \
    src/settings/update/progressbarwidget.h \
    src/settings/update/qmlbuttonshandler.h \
    src/settings/update/qmlwidget.h \
    src/settings/update/updater.h \
    src/settings/update/updatewidget.h \
    src/singleton.h \
    src/sound_controller/media.h \
    src/sound_controller/soundcontroller.h \
    src/sound_controller/universalmodebutton.h \
    src/statistic/sortfilterproxymodel.h \
    src/statistic/statisticmodel.h \
    src/statistic/statisticwidget.h \
    src/testing/models/draggridmodel.h \
    src/testing/models/dropgridmodel.h \
    src/testing/models/testingresultsmodel.h \
    src/testing/testmanager.h \
    src/testing/testresultswidget.h \
    src/testing/testsettingswidget.h \
    src/testing/widgetoftesting.h \
    src/ui/buttons/levelmodewidget.h \
    src/ui/buttons/modebutton.h \
    src/ui/buttons/pickedbutton.h \
    src/ui/buttons/styledbutton.h \
    src/ui/html_view/artinfowidget.h \
    src/ui/html_view/helpviewer.h \
    src/ui/html_view/scrolledtextbrowser.h

SOURCES += \
    src/database/dbfacade.cpp \
    src/database/jsonparser.cpp \
    src/database/levelsdbfacade.cpp \
    src/database/settingsdbfacade.cpp \
    src/game/gamemanager.cpp \
    src/game/itemground.cpp \
    src/game/pathpoints.cpp \
    src/game/puzzlegame.cpp \
    src/game/puzzleitem/movableitem.cpp \
    src/game/puzzleitem/puzzleitem.cpp \
    src/game/puzzleitem/puzzlematrix.cpp \
    src/game/puzzleitem/rotatableitem.cpp \
    src/game/puzzleitem/selectableitem.cpp \
    src/game/puzzleitem/settableitem.cpp \
    src/game/puzzlepath.cpp \
    src/game/puzzleview.cpp \
    src/game/random_points.cpp \
    src/main.cpp \
    src/menu/level_icons_view/iconsview.cpp \
    src/menu/level_icons_view/levelicon.cpp \
    src/menu/level_icons_view/menuiconproxy.cpp \
    src/menu/levelmenuscreen.cpp \
    src/menu/mainmenuscreen.cpp \
    src/screen_controller/gamescreencontroller.cpp \
    src/screen_controller/levelmenuscreencontroller.cpp \
    src/screen_controller/mainmenuscreencontroller.cpp \
    src/screen_controller/screensstack.cpp \
    src/screen_controller/settingsscreencontroller.cpp \
    src/screen_controller/testingscreencontroller.cpp \
    src/settings/optionswidget.cpp \
    src/settings/update/eralistmodel.cpp \
    src/settings/update/loader.cpp \
    src/settings/update/progressbarwidget.cpp \
    src/settings/update/updater.cpp \
    src/settings/update/updatewidget.cpp \
    src/sound_controller/media.cpp \
    src/sound_controller/soundcontroller.cpp \
    src/sound_controller/universalmodebutton.cpp \
    src/statistic/sortfilterproxymodel.cpp \
    src/statistic/statisticmodel.cpp \
    src/statistic/statisticwidget.cpp \
    src/testing/models/draggridmodel.cpp \
    src/testing/models/dropgridmodel.cpp \
    src/testing/models/testingresultsmodel.cpp \
    src/testing/testmanager.cpp \
    src/testing/testresultswidget.cpp \
    src/testing/testsettingswidget.cpp \
    src/testing/widgetoftesting.cpp \
    src/ui/buttons/levelmodewidget.cpp \
    src/ui/buttons/modebutton.cpp \
    src/ui/buttons/pickedbutton.cpp \
    src/ui/buttons/styledbutton.cpp \
    src/ui/html_view/artinfowidget.cpp \
    src/ui/html_view/helpviewer.cpp \
    src/ui/html_view/scrolledtextbrowser.cpp


contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

include(android_openssl/openssl.pri)

RESOURCES += \
    resources/resources.qrc

DISTFILES += \
    /android/AndroidManifest.xml \
    /android/build.gradle \
    /android/gradle/wrapper/gradle-wrapper.jar \
    /android/gradle/wrapper/gradle-wrapper.properties \
    /android/gradlew \
    /android/gradlew.bat \
    /android/res/values/libs.xml


