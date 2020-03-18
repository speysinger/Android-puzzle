QT += core gui
QT += widgets sql multimedia network quick quickwidgets

QMAKE_CXXFLAGS += -std=c++17

TARGET = puzzle
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += "_GLIBCXX_USE_CXX11_ABI=0"

SOURCES += \
    buttons/modebutton.cpp \
    buttons/pickedbutton.cpp \
    buttons/styledbutton.cpp \
    database/dbfacade.cpp \
    database/jsondocument.cpp \
    database/levelsdbfacade.cpp \
    buttons/levelmodewidget.cpp \
    game/gamemanager.cpp \
    html_view/artinfowidget.cpp \
    main.cpp \
    game/pathpoints.cpp \
    game/puzzlepath.cpp \
    game/puzzlegame.cpp \
    game/itemground.cpp \
    game/random_points.cpp \
    game/puzzleview.cpp \
    menu/level_icons_view/iconsview.cpp \
    menu/level_icons_view/levelicon.cpp \
    menu/level_icons_view/menuitemproxy.cpp \
    menu/levelmenuscreen.cpp \
    menu/mainmenuscreen.cpp \
    screen_controller/gamescreencontroller.cpp \
    screen_controller/levelmenuscreencontroller.cpp \
    screen_controller/mainmenuscreencontroller.cpp \
    screen_controller/screensstack.cpp \
    game/puzzleitem/puzzleitem.cpp \
    game/puzzleitem/selectableitem.cpp \
    game/puzzleitem/rotatableitem.cpp \
    game/puzzleitem/movableitem.cpp \
    game/puzzleitem/settableitem.cpp \
    game/puzzleitem/puzzlematrix.cpp \
    html_view/helpviewer.cpp \
    screen_controller/settingsscreencontroller.cpp \
    screen_controller/testingscreencontroller.cpp \
    settings/settingwidget.cpp \
    database/settingsdbfacade.cpp \
    html_view/scrolledtextbrowser.cpp \
    settings/update/eralistmodel.cpp \
    settings/update/loader.cpp \
    settings/update/progressbarwidget.cpp \
    settings/update/updater.cpp \
    settings/update/updatewidget.cpp \
    sound_controller/media.cpp \
    sound_controller/soundcontroller.cpp \
    sound_controller/universalmodebutton.cpp \
    statistic/sortfilterproxymodel.cpp \
    statistic/statisticmodel.cpp \
    statistic/statisticwidget.cpp \
    testing/models/draggridmodel.cpp \
    testing/models/dropgridmodel.cpp \
    testing/models/testingresultsmodel.cpp \
    testing/testmanager.cpp \
    testing/testresultswidget.cpp \
    testing/testsettingswidget.cpp \
    testing/widgetoftesting.cpp

HEADERS += \
    buttons/modebutton.h \
    buttons/pickedbutton.h \
    buttons/styledbutton.h \
    database/dbfacade.h \
    database/jsondocument.h \
    database/levelsdbfacade.h \
    database/levelstructures.h \
    database/settingsdbfacade.h \
    game/gamemanager.h \
    game/pathpoints.h \
    game/puzzlepath.h \
    game/puzzlegame.h \
    game/itemground.h \
    game/random_points.h \
    game/puzzleview.h \
    game/puzzleitem/puzzleitem.h \
    game/puzzleitem/selectableitem.h \
    game/puzzleitem/rotatableitem.h \
    game/puzzleitem/movableitem.h \
    game/puzzleitem/settableitem.h \
    game/puzzleitem/puzzlematrix.h \
    buttons/levelmodewidget.h \
    html_view/artinfowidget.h \
    menu/level_icons_view/iconsview.h \
    menu/level_icons_view/levelicon.h \
    menu/level_icons_view/menuitemproxy.h \
    menu/levelmenuscreen.h \
    menu/mainmenuscreen.h \
    screen_controller/gamescreencontroller.h \
    screen_controller/levelmenuscreencontroller.h \
    screen_controller/mainmenuscreencontroller.h \
    screen_controller/settingsscreencontroller.h \
    screen_controller/testingscreencontroller.h \
    settings/update/eralistmodel.h \
    settings/update/loader.h \
    settings/update/progressbarwidget.h \
    settings/update/qmlbuttonshandler.h \
    settings/update/qmlwidget.h \
    settings/update/updater.h \
    settings/update/updatewidget.h \
    singleton.h \
    mode.h \
    screen_controller/screensstack.h \
    html_view/helpviewer.h \
    html_view/scrolledtextbrowser.h \
    settings/settingwidget.h \
    sound_controller/media.h \
    sound_controller/soundcontroller.h \
    sound_controller/universalmodebutton.h \
    statistic/sortfilterproxymodel.h \
    statistic/statisticmodel.h \
    statistic/statisticwidget.h \
    testing/models/draggridmodel.h \
    testing/models/dropgridmodel.h \
    testing/models/testingresultsmodel.h \
    testing/testmanager.h \
    testing/testresultswidget.h \
    testing/testsettingswidget.h \
    testing/widgetoftesting.h

 ANDROID_PACKAGE_SOURCE_DIR = $$PWD/../android

DISTFILES += \
    ../android/AndroidManifest.xml \
    ../android/gradle/wrapper/gradle-wrapper.jar \
    ../android/gradlew \
    ../android/res/values/libs.xml \
    ../android/build.gradle \
    ../android/gradle/wrapper/gradle-wrapper.properties \
    ../android/gradlew.bat \
    ../android/gradle.properties \
    ../_build/android-build/gradle/wrapper/gradle-4.6-bin.zip

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/../android
}

RESOURCES += \
  ../resources/resources.qrc


