/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef PC
#include <QtQuick>
#include <sailfishapp.h>
#else
#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "themewrapper_pc.h"
#endif
#include "appinfo.h"
#include "jsonloader.h"
#include "transactionsmanager.h"
int main(int argc, char *argv[])
{
#ifndef PC
    int exitcode = -1;
    QGuiApplication *app = SailfishApp::application(argc, argv);
    app->setQuitOnLastWindowClosed(true);

    AppInfo appinfo(app);
    JsonLoader json(app, &appinfo);

    QQuickView *view = SailfishApp::createView();
    view->rootContext()->setContextProperty("jsonloader", &json);
    view->rootContext()->setContextProperty("transactionmanager", &json.getTransactionManager());
    view->rootContext()->setContextProperty("accounttypesmanager", &json.getAccountTypeManager());
    view->rootContext()->setContextProperty("appinfo", &appinfo);
    view->setSource(SailfishApp::pathTo("/qml/mymoney.qml"));
    view->showFullScreen();

    exitcode = app->exec();
    //delete view;
    //delete app;
    return exitcode;
#else
    QApplication app(argc, argv);
    AppInfo appinfo(&app);
    JsonLoader json(&app, &appinfo);
    ThemeWrapper_PC theme;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("jsonloader", &json);
    engine.rootContext()->setContextProperty("transactionmanager", &json.getTransactionManager());
    engine.rootContext()->setContextProperty("accounttypesmanager", &json.getAccountTypeManager());
    engine.rootContext()->setContextProperty("appinfo", &appinfo);
    engine.rootContext()->setContextProperty("Theme", &theme);
    engine.load(QUrl(QStringLiteral("qrc:///qml/main_pc.qml")));
    return app.exec();
#endif
}

