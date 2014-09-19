#include "translation.h"
#include "ui_translation.h"

Translation::Translation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Translation)
{
    ui->setupUi(this);
}

Translation::~Translation()
{
    delete ui;
}


void Translation::tranlatingTsFileSelectClicked()
{
    tranlatingTsFilePath=QFileDialog::getOpenFileName(this, tr("Select Qt .ts file to tranlate"),"D:/dk work/Motarola");
    ui->lETranlatingTsFilePath->setText(tranlatingTsFilePath);

}

void Translation::googleTranslatedFileSelectClicked()
{
    googleTranlatedFilePath=QFileDialog::getOpenFileName(this, tr("Select Google Tranlated File"),"D:/dk work/Motarola");
    ui->lEGoogleTranlatedFile->setText(googleTranlatedFilePath);

}

void Translation::manualTranlatingFileSavePathSelectClicked()
{

    manualTranlatingFileSavePath=QFileDialog::getExistingDirectory(this, tr("Select Manual Tranlating file Save Directry"),"D:/dk work/Motarola");
    ui->lEManualTranlatingfileSavePath->setText(manualTranlatingFileSavePath);

}



void Translation::manualTranslatedFileSelectClicked()
{
    manualTranlatedFilePath=QFileDialog::getOpenFileName(this, tr("Select Manual tranlated File"),"D:/dk work/Motarola");
    ui->lEManualTranlatedFile->setText(manualTranlatedFilePath);

}

void Translation::updatingTsFileSelectClicked()
{
    updateTsFilePath=QFileDialog::getOpenFileName(this, tr("Select Qt .ts file to Update"),"D:/dk work/Motarola");
    ui->lEupdatingTsFile->setText(updateTsFilePath);

}



void Translation::genaratePushButtonClicked()
{
    if(tranlatingTsFilePath.length()==0)
    {
        QMessageBox::warning(this,"Error","Please Select .ts file that need to translate");
        return;
    }

    if(googleTranlatedFilePath.length()==0)
    {
        QMessageBox::warning(this,"Error","Please Select Google Tranlated File ");
        return;

    }
    if(manualTranlatingFileSavePath.length()==0)
    {
        QMessageBox::warning(this,"Error","Please Select manual Tranlation file Save Directry");
        return;

    }


    QFile tranlatingFile(tranlatingTsFilePath);

    if(!tranlatingFile.open(QFile::ReadWrite| QIODevice::Text))
    {
        qDebug()<<"error";

    }
    else
    {
        //QFile googleTranlatingFile(googleTranlatingFileSavePath+"/"+"googleTranlatingFile.txt");
        QFile googleTranlatedFile(googleTranlatedFilePath);
        if(!googleTranlatedFile.open(QFile::ReadWrite| QIODevice::Text))
        {
            qDebug()<<"error";

        }
        else
        {

            QFile manualTranlatingFile(manualTranlatingFileSavePath+"/"+"manualTranlatingFile.txt");

            if(!manualTranlatingFile.open(QFile::ReadWrite| QIODevice::Text))
            {
                qDebug()<<"error";
                return;

            }
            else
            {

                QTextStream googletranlatedFileGenarate(&googleTranlatedFile);
                QTextStream manualtranlatingFileGenarate(&manualTranlatingFile);


                QStringList tranlatedWords;

                while (!googletranlatedFileGenarate.atEnd()) {
                    tranlatedWords.append(googletranlatedFileGenarate.readLine());



                }



                QDomDocument document;

                document.setContent(&tranlatingFile);
                QDomElement root= document.firstChildElement();


                QDomNodeList context = root.elementsByTagName("context");

                int wordCount=0;

                for(int j=0;j<context.count();j++)
                {
                    QDomNodeList messages=context.at(j).toElement().elementsByTagName("message");
                    QString className=context.at(j).toElement().elementsByTagName("name").at(0).firstChild().nodeValue();


                    for(int i=0;i<messages.count();i++)
                    {


                        QString source=messages.at(i).toElement().elementsByTagName("source").at(0).firstChild().nodeValue();
                        // googletranlatedFileGenarate<<source<<"\n";
                        manualtranlatingFileGenarate<<className<<"\t"<<source<<"\t"<<tranlatedWords.at(wordCount)<<"\n";
                        wordCount++;


                    }

                }


            }



            googleTranlatedFile.close();
            manualTranlatingFile.close();
            tranlatingFile.close();
            QMessageBox::information(this,"Success","Manual Tranlating File Created");
        }

    }






}



void Translation::updateTsFilePushButtonClicked()
{
    if(manualTranlatedFilePath.length()==0)
    {
        QMessageBox::warning(this,"Error","Please Select Manual Tranlated file");
        return;
    }

    if(updateTsFilePath.length()==0)
    {
        QMessageBox::warning(this,"Error","Please Select .ts File that need to Translate");
        return;

    }



    QFile manualTranlatedFile(manualTranlatedFilePath);
     manualTranlatedFile.open(QIODevice::ReadOnly | QIODevice::Text);


    QTextStream in(&manualTranlatedFile);
    while(!in.atEnd())
    {

        QString line = in.readLine();
        QString tranlatedWord=line.split("\t").at(2);
        translatedStringList.append(tranlatedWord);


    }


    QFile updatingTsFile(updateTsFilePath);
    //set tranlating strings
    if(!updatingTsFile.open(QFile::ReadWrite| QIODevice::Text))
    {
        qDebug()<<"error";

    }
    else
    {
            QDomDocument document;

            document.setContent(&updatingTsFile);
            QDomElement root= document.firstChildElement();


            QDomNodeList context = root.elementsByTagName("context");

            int x=0;

            for(int j=0;j<context.count();j++)
            {
                QDomNodeList messages=context.at(j).toElement().elementsByTagName("message");


                for(int i=0;i<messages.count();i++)
                {
                    QDomElement tranlation=document.createElement("translation");
                    tranlation.appendChild(document.createTextNode(translatedStringList.at(x)));


                    messages.at(i).toElement().removeChild(messages.at(i).toElement().elementsByTagName("translation").at(0));
                    messages.at(i).toElement().appendChild(tranlation);

                    x++;


                }

            }

            document.appendChild(root);
            updatingTsFile.close();


            if(!updatingTsFile.open(QFile::ReadWrite|QIODevice::Truncate | QIODevice::Text))
            {
                qDebug()<<"error";

            }
            else
            {

                QTextStream stream(&updatingTsFile);
                stream.setCodec("UTF-8"); // change the file codec to UTF-8.
                stream <<document.toString();
                updatingTsFile.close();
                QMessageBox::information(this,"Success","Tranlated .ts File");



            }


         manualTranlatedFile.close();





     }

}
