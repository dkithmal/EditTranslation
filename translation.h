#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QFile>
#include <QtXml>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QStringList>


namespace Ui {
class Translation;
}

class Translation : public QDialog
{
    Q_OBJECT

public:
    explicit Translation(QWidget *parent = 0);
    ~Translation();

private:
    Ui::Translation *ui;
    QString tranlatingTsFilePath;
    QString googleTranlatedFilePath;
    QString manualTranlatingFileSavePath;
    QString manualTranlatedFilePath;
    QString updateTsFilePath;
    QStringList translatedStringList;


private slots:
    void tranlatingTsFileSelectClicked();
    void googleTranslatedFileSelectClicked();
    void manualTranlatingFileSavePathSelectClicked();
    void genaratePushButtonClicked();
    void manualTranslatedFileSelectClicked();
    void updatingTsFileSelectClicked();
    void updateTsFilePushButtonClicked();

};

#endif // TRANSLATION_H
