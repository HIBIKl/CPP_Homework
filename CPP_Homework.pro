QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += utf8
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#添加文件资源
SOURCES += \
    main.cpp \
    widget.cpp \
    Diag_and_Hori.cpp \
    IBR.cpp \
    STC.cpp \
    main_algorithm.cpp
    #./hzc/upload/Diagonal_Priority.cpp \
    #./hzc/upload/Horizonal_Priority.cpp \
    #./hzc/upload/IBR.cpp



HEADERS += \
    widget.h \
    Diag_and_Hori.h \
    IBR.h \
    STC.h
    #./hzc/upload/BigHeader.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

//导入自定义组件
SOURCES += \
    ./MaterialSDK/components/qtmaterialavatar.cpp \
    ./MaterialSDK/components/lib/qtmaterialstyle.cpp \
    ./MaterialSDK/components/lib/qtmaterialtheme.cpp \
    ./MaterialSDK/components/qtmaterialbadge.cpp \
    ./MaterialSDK/components/lib/qtmaterialoverlaywidget.cpp \
    ./MaterialSDK/components/qtmaterialcheckbox.cpp \
    ./MaterialSDK/components/lib/qtmaterialcheckable_internal.cpp \
    ./MaterialSDK/components/lib/qtmaterialcheckable.cpp \
    ./MaterialSDK/components/lib/qtmaterialripple.cpp \
    ./MaterialSDK/components/lib/qtmaterialrippleoverlay.cpp \
    ./MaterialSDK/components/qtmaterialfab.cpp \
    ./MaterialSDK/components/qtmaterialraisedbutton.cpp \
    ./MaterialSDK/components/qtmaterialflatbutton_internal.cpp \
    ./MaterialSDK/components/qtmaterialflatbutton.cpp \
    ./MaterialSDK/components/lib/qtmaterialstatetransition.cpp \
    ./MaterialSDK/components/qtmaterialiconbutton.cpp \
    ./MaterialSDK/components/qtmaterialprogress_internal.cpp \
    ./MaterialSDK/components/qtmaterialprogress.cpp \
    ./MaterialSDK/components/qtmaterialcircularprogress_internal.cpp \
    ./MaterialSDK/components/qtmaterialcircularprogress.cpp \
    ./MaterialSDK/components/qtmaterialslider_internal.cpp \
    ./MaterialSDK/components/qtmaterialslider.cpp \
    ./MaterialSDK/components/qtmaterialsnackbar_internal.cpp \
    ./MaterialSDK/components/qtmaterialsnackbar.cpp \
    ./MaterialSDK/components/qtmaterialradiobutton.cpp \
    ./MaterialSDK/components/qtmaterialtoggle_internal.cpp \
    ./MaterialSDK/components/qtmaterialtoggle.cpp \
    ./MaterialSDK/components/qtmaterialtextfield_internal.cpp \
    ./MaterialSDK/components/qtmaterialtextfield.cpp \
    ./MaterialSDK/components/qtmaterialtabs_internal.cpp \
    ./MaterialSDK/components/qtmaterialtabs.cpp \
    ./MaterialSDK/components/qtmaterialscrollbar_internal.cpp \
    ./MaterialSDK/components/qtmaterialscrollbar.cpp \
    ./MaterialSDK/components/qtmaterialdialog_internal.cpp \
    ./MaterialSDK/components/qtmaterialdialog.cpp \
    ./MaterialSDK/components/qtmaterialdrawer_internal.cpp \
    ./MaterialSDK/components/qtmaterialdrawer.cpp \
    ./MaterialSDK/components/qtmaterialappbar.cpp \
    ./MaterialSDK/components/qtmaterialautocomplete.cpp \
    ./MaterialSDK/components/qtmaterialpaper.cpp \
    ./MaterialSDK/components/qtmaterialtable.cpp \
    ./MaterialSDK/components/layouts/qtmaterialsnackbarlayout.cpp \
    ./MaterialSDK/components/qtmaterialautocomplete_internal.cpp \
    ./MaterialSDK/components/qtmaterialmenu.cpp \
    ./MaterialSDK/components/qtmaterialmenu_internal.cpp \
    ./MaterialSDK/components/qtmateriallist.cpp \
    ./MaterialSDK/components/qtmateriallistitem.cpp
HEADERS += \
    ./MaterialSDK/components/qtmaterialavatar_p.h \
    ./MaterialSDK/components/qtmaterialavatar.h \
    ./MaterialSDK/components/lib/qtmaterialstyle_p.h \
    ./MaterialSDK/components/lib/qtmaterialstyle.h \
    ./MaterialSDK/components/lib/qtmaterialtheme_p.h \
    ./MaterialSDK/components/lib/qtmaterialtheme.h \
    ./MaterialSDK/components/qtmaterialbadge_p.h \
    ./MaterialSDK/components/qtmaterialbadge.h \
    ./MaterialSDK/components/lib/qtmaterialoverlaywidget.h \
    ./MaterialSDK/components/qtmaterialcheckbox_p.h \
    ./MaterialSDK/components/qtmaterialcheckbox.h \
    ./MaterialSDK/components/lib/qtmaterialcheckable_internal.h \
    ./MaterialSDK/components/lib/qtmaterialcheckable_p.h \
    ./MaterialSDK/components/lib/qtmaterialripple.h \
    ./MaterialSDK/components/lib/qtmaterialrippleoverlay.h \
    ./MaterialSDK/components/lib/qtmaterialcheckable.h \
    ./MaterialSDK/components/qtmaterialfab_p.h \
    ./MaterialSDK/components/qtmaterialfab.h \
    ./MaterialSDK/components/qtmaterialraisedbutton_p.h \
    ./MaterialSDK/components/qtmaterialraisedbutton.h \
    ./MaterialSDK/components/qtmaterialflatbutton_internal.h \
    ./MaterialSDK/components/qtmaterialflatbutton_p.h \
    ./MaterialSDK/components/qtmaterialflatbutton.h \
    ./MaterialSDK/components/lib/qtmaterialstatetransition.h \
    ./MaterialSDK/components/lib/qtmaterialstatetransitionevent.h \
    ./MaterialSDK/components/qtmaterialiconbutton_p.h \
    ./MaterialSDK/components/qtmaterialiconbutton.h \
    ./MaterialSDK/components/qtmaterialprogress_internal.h \
    ./MaterialSDK/components/qtmaterialprogress_p.h \
    ./MaterialSDK/components/qtmaterialprogress.h \
    ./MaterialSDK/components/qtmaterialcircularprogress_internal.h \
    ./MaterialSDK/components/qtmaterialcircularprogress_p.h \
    ./MaterialSDK/components/qtmaterialcircularprogress.h \
    ./MaterialSDK/components/qtmaterialslider_internal.h \
    ./MaterialSDK/components/qtmaterialslider_p.h \
    ./MaterialSDK/components/qtmaterialslider.h \
    ./MaterialSDK/components/qtmaterialsnackbar_internal.h \
    ./MaterialSDK/components/qtmaterialsnackbar_p.h \
    ./MaterialSDK/components/qtmaterialsnackbar.h \
    ./MaterialSDK/components/qtmaterialradiobutton_p.h \
    ./MaterialSDK/components/qtmaterialradiobutton.h \
    ./MaterialSDK/components/qtmaterialtoggle_internal.h \
    ./MaterialSDK/components/qtmaterialtoggle_p.h \
    ./MaterialSDK/components/qtmaterialtoggle.h \
    ./MaterialSDK/components/qtmaterialtextfield_internal.h \
    ./MaterialSDK/components/qtmaterialtextfield_p.h \
    ./MaterialSDK/components/qtmaterialtextfield.h \
    ./MaterialSDK/components/qtmaterialtabs_internal.h \
    ./MaterialSDK/components/qtmaterialtabs_p.h \
    ./MaterialSDK/components/qtmaterialtabs.h \
    ./MaterialSDK/components/qtmaterialscrollbar_internal.h \
    ./MaterialSDK/components/qtmaterialscrollbar_p.h \
    ./MaterialSDK/components/qtmaterialscrollbar.h \
    ./MaterialSDK/components/qtmaterialdialog_internal.h \
    ./MaterialSDK/components/qtmaterialdialog_p.h \
    ./MaterialSDK/components/qtmaterialdialog.h \
    ./MaterialSDK/components/qtmaterialdrawer_internal.h \
    ./MaterialSDK/components/qtmaterialdrawer_p.h \
    ./MaterialSDK/components/qtmaterialdrawer.h \
    ./MaterialSDK/components/qtmaterialappbar.h \
    ./MaterialSDK/components/qtmaterialappbar_p.h \
    ./MaterialSDK/components/qtmaterialautocomplete.h \
    ./MaterialSDK/components/qtmaterialautocomplete_p.h \
    ./MaterialSDK/components/qtmaterialpaper.h \
    ./MaterialSDK/components/qtmaterialpaper_p.h \
    ./MaterialSDK/components/qtmaterialtable.h \
    ./MaterialSDK/components/qtmaterialtable_p.h \
    ./MaterialSDK/components//layouts/qtmaterialsnackbarlayout.h \
    ./MaterialSDK/components/layouts/qtmaterialsnackbarlayout_p.h \
    ./MaterialSDK/components/qtmaterialautocomplete_internal.h \
    ./MaterialSDK/components/qtmaterialmenu.h \
    ./MaterialSDK/components/qtmaterialmenu_p.h \
    ./MaterialSDK/components/qtmaterialmenu_internal.h \
    ./MaterialSDK/components/qtmateriallist.h \
    ./MaterialSDK/components/qtmateriallist_p.h \
    ./MaterialSDK/components/qtmateriallistitem.h \
    ./MaterialSDK/components/qtmateriallistitem_p.h

#导入Material组件库的SDK
#填绝对路径，否则无法编译
LIBS += F:/SDK/MaterialSDK/staticlib/libcomponents.a
INCLUDEPATH += ./MaterialSDK/components
PRE_TARGETDEPS += F:/SDK/MaterialSDK/staticlib/libcomponents.a

#subdirs模板告诉qmake生成一个makefile，它可以进入到特定子目录并为这个目录中的项目文件生成makefile并且为它调用make。
SUBDIRS += \
    ./MaterialSDK/components/components.pro

RESOURCES += \
    resources.qrc \
    resources.qrc


#opencv3.4.16环境变量
INCLUDEPATH += D:/opencv3.4.16/build/include \
               D:/opencv3.4.16/build/include/opencv \
               D:/opencv3.4.16/build/include/opencv2 \
               D:/opencv3.4.16/build/x64/vc15/bin \
               D:/opencv3.4.16/build/x64/vc15/lib

LIBS += -LD:/opencv3.4.16/build/x64/vc15/lib/ -lopencv_world3416
LIBS += -LD:/opencv3.4.16/build/x64/vc15/lib/ -lopencv_world3416d

INCLUDEPATH += D:/opencv3.4.16/build/x64/vc15
DEPENDPATH += D:/opencv3.4.16/build/x64/vc15
