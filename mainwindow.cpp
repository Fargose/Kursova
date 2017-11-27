#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("FerumChecker 1.1");
    ListCPU.read("DB/CPU.txt");
    ListMB.read("DB/MBB.txt");
    ListMB.print(ui->listWidget);
    ListOZU.read("DB/OZU.txt");
    ListVC.read("DB/VC.txt");
    ListHD.read("DB/HW.txt");
    ListSW.read("DB/SW.txt");
    for(int i = 0;i < ListSW.getSize();i++)
    {
        if(!ListSW.getEl(i)->Verification(ListCPU,ListVC))
        {
            ListSW.DeleteIn(i);
            i--;
        }
    }
    QPixmap MPX;
    MPX.load("Images/Comp.png");
    ui->compimage->setPixmap(MPX);
    ui->compimage->setScaledContents(true);
    CurrentComp = new cComputer();
    lbl[0] = ui->CpuImage;
    lbl[1] = ui->MBImage;
    lbl[2] = ui->VcImage;
    lbl[3] = ui->OzuImage;
    lbl[4] = ui->ozuimage2;
    lbl[5] = ui->HWImage;
    connect(ui->MBImage,SIGNAL(double_clicked()),this,SLOT(on_MBClicked()));
    connect(ui->MBImage,SIGNAL(clicked()),this,SLOT(on_MBCh()));
    connect(ui->CpuImage,SIGNAL(double_clicked()),this,SLOT(on_CPU_Clicked()));
    connect(ui->CpuImage,SIGNAL(clicked()),this,SLOT(on_CPUCh()));
    connect(ui->VcImage,SIGNAL(double_clicked()),this,SLOT(on_VC_Clicked()));
    connect(ui->VcImage,SIGNAL(clicked()),this,SLOT(on_VCCh()));
    connect(ui->OzuImage,SIGNAL(double_clicked()),this,SLOT(on_OZU1_clicked()));
    connect(ui->OzuImage,SIGNAL(clicked()),this,SLOT(on_OZU1Ch()));
    connect(ui->ozuimage2,SIGNAL(double_clicked()),this,SLOT(on_OZU2_clicked()));
    connect(ui->ozuimage2,SIGNAL(clicked()),this,SLOT(on_OZU2Ch()));
    connect(ui->HWImage,SIGNAL(double_clicked()),this,SLOT(on_HW_clicked()));
    connect(ui->HWImage,SIGNAL(clicked()),this,SLOT(on_HWCh()));

    ui->CpuImage->setToolTip("Відсутнє");
    ui->MBImage->setToolTip("Відсутнє");
    ui->VcImage->setToolTip("Відсутнє");
    ui->OzuImage->setToolTip("Відсутнє");
    ui->ozuimage2->setToolTip("Відсутнє");
    ui->HWImage->setToolTip("Відсутнє");
    ui->listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    CurrentComp->Show(ui->CompInformation);
    ui->CompMenu->addAction("&Підібрати компютер",this,SLOT(OpenCrComSl()));
    ui->CompMenu->addAction("&Додати елемент",this,SLOT(NewHardOpen()));







}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->ImageLabel->clear();
    ui->TextInfo->clear();

    if(index == 1)
    {
        ListCPU.print(ui->listWidget);
        ui->pushButton->setText("Додати");
        ClearInf();

    }
    else if(index == 0)
    {
        ListMB.print(ui->listWidget);
        ui->pushButton->setText("Додати");
        ClearInf();


    }
    else if(index == 2)
    {
        ListOZU.print(ui->listWidget);
        ui->pushButton->setText("Додати");
        ClearInf();

    }
    else if(index == 3)
    {
        ListVC.print(ui->listWidget);
        ui->pushButton->setText("Додати");
        ClearInf();


    }
    else if(index == 4)
    {
        ListHD.print(ui->listWidget);
        ui->pushButton->setText("Додати");
        ClearInf();


    }
    else if(index == 5)
    {
        ListSW.print(ui->listWidget);
        ui->pushButton->setText("Перевірити");
        ui->MinLabel->setText("Мінімальні вимоги");
        ui->BestLabel->setText("Рекомендовані вимоги");
        ui->CheckResLabl->setText("Cумісність: ");
        ui->SettingsLabel->setText("Рекомендовані налаштування: ");
        ui->BestLabel->setStyleSheet("color:black");
        ui->MinLabel->setStyleSheet("color:black");
        ui->SettingsLabelNumber->setStyleSheet("color:black");
        ui->CheckResNum->setStyleSheet("color:black");



    }

}



void MainWindow::on_pushButton_clicked()
{
    if(ui->listWidget->currentRow() >=0)
    {
        if(ui->comboBox->currentIndex() == 1)
        {
            if(CurrentComp->SetCPU(ListCPU.getEl(ui->listWidget->currentRow())) == true)
            {

                CurrentComp->Show(lbl);
                ui->CpuImage->setToolTip(ListCPU.getEl(ui->listWidget->currentRow())->GetName());

            }
        }
        else if(ui->comboBox->currentIndex() == 0)
        {
            CurrentComp->SetMB(ListMB.getEl(ui->listWidget->currentRow()));

            CurrentComp->Show(lbl);
            ui->MBImage->setToolTip(ListMB.getEl(ui->listWidget->currentRow())->GetName());

        }
        else if(ui->comboBox->currentIndex() == 2)
        {
            int bb = CurrentComp->SetOZU(ListOZU.getEl(ui->listWidget->currentRow()));
            if(bb == 0)
            {

                ui->ozuimage2->setToolTip(ui->OzuImage->toolTip());
                ui->OzuImage->setToolTip(ListOZU.getEl(ui->listWidget->currentRow())->GetName());

            }
            else if(bb == 1)
            {


                ui->OzuImage->setToolTip(ListOZU.getEl(ui->listWidget->currentRow())->GetName());
            }
            CurrentComp->Show(lbl);

        }
        else if(ui->comboBox->currentIndex() == 3)
        {

            if(CurrentComp->SetVC(ListVC.getEl(ui->listWidget->currentRow())) == true)
            {

                CurrentComp->Show(lbl);
                ui->VcImage->setToolTip(ListVC.getEl(ui->listWidget->currentRow())->GetName());

            }
        }
        else if(ui->comboBox->currentIndex() == 4)
        {
            if(CurrentComp->SetHW(ListHD.getEl(ui->listWidget->currentRow())) == true)
            {

                CurrentComp->Show(lbl);
                ui->HWImage->setToolTip(ListHD.getEl(ui->listWidget->currentRow())->GetName());

            }
        }
        else if(ui->comboBox->currentIndex() == 5)
        {
            int _rs = CurrentComp->CheckSoftware(ListSW.getEl(ui->listWidget->currentRow()));
            if(_rs != -1)
            {
                if(_rs >= 95)
                {
                    ui->BestLabel->setStyleSheet("color:green");
                    ui->MinLabel->setStyleSheet("color:green");
                    ui->SettingsLabelNumber->setText("Максимальні");
                    ui->SettingsLabelNumber->setStyleSheet("color:green");
                    ui->CheckResNum->setStyleSheet("color:green");


                }
                if(_rs >= 70 && _rs < 95)
                {
                    ui->BestLabel->setStyleSheet("color:orange)");
                    ui->MinLabel->setStyleSheet("color:green");
                    ui->SettingsLabelNumber->setText("Високі");
                    ui->SettingsLabelNumber->setStyleSheet("color:green");
                    ui->CheckResNum->setStyleSheet("color:green");


                }
                if(_rs >= 50 && _rs < 70)
                {
                    ui->BestLabel->setStyleSheet("color:orange");
                    ui->MinLabel->setStyleSheet("color:orange");
                    ui->SettingsLabelNumber->setText("Середні");
                    ui->SettingsLabelNumber->setStyleSheet("color:orange");
                    ui->CheckResNum->setStyleSheet("color:yellow");

                }
                if(_rs >= 35 && _rs < 50)
                {
                    ui->BestLabel->setStyleSheet("color:red");
                    ui->MinLabel->setStyleSheet("color:orange");
                    ui->SettingsLabelNumber->setText("Низькі");
                    ui->SettingsLabelNumber->setStyleSheet("color:orange");
                    ui->CheckResNum->setStyleSheet("color:orange");

                }
                if(_rs < 35)
                {
                    ui->BestLabel->setStyleSheet("color:red");
                    ui->MinLabel->setStyleSheet("color:red");
                    ui->SettingsLabelNumber->setText("Мінімальні\\ПЗ не запуститься");
                    ui->SettingsLabelNumber->setStyleSheet("color:red");
                    ui->CheckResNum->setStyleSheet("color:red");

                }
                ui->CheckResNum->setText(QString::number(_rs)+"%");
            }

        }
    }
    CurrentComp->Show(ui->CompInformation);
}


void MainWindow::on_MBClicked()
{
    if(CurrentComp->DelMB() == true)
    {
        ui->MBImage->setToolTip("Відсутнє");
        ui->ozuimage2->setToolTip("Відсутнє");
        ui->CpuImage->setToolTip("Відсутнє");
        ui->OzuImage->setToolTip("Відсутнє");
        ui->VcImage->setToolTip("Відсутнє");
        ui->HWImage->setToolTip("Відсутнє");
    }
    CurrentComp->Show(lbl);

    CurrentComp->Show(ui->CompInformation);

}

void MainWindow::on_CPU_Clicked()
{
    CurrentComp->DelCPU();
    CurrentComp->Show(lbl);
    ui->CpuImage->setToolTip("Відсутнє");

    CurrentComp->Show(ui->CompInformation);
}

void MainWindow::on_VC_Clicked()
{
    CurrentComp->DelVC();
    CurrentComp->Show(lbl);
    ui->VcImage->setToolTip("Відсутнє");

    CurrentComp->Show(ui->CompInformation);
}

void MainWindow::on_OZU1_clicked()
{
    CurrentComp->DelOZU(0);
    ui->OzuImage->setToolTip("Відсутнє");
    CurrentComp->Show(lbl);

    CurrentComp->Show(ui->CompInformation);
}

void MainWindow::on_OZU2_clicked()
{
    CurrentComp->DelOZU(1);
    CurrentComp->Show(lbl);
    ui->ozuimage2->setToolTip("Відсутнє");

    CurrentComp->Show(ui->CompInformation);
}

void MainWindow::on_HW_clicked()
{
    CurrentComp->DelHW();
    CurrentComp->Show(lbl);
    ui->HWImage->setToolTip("Відсутнє");

    CurrentComp->Show(ui->CompInformation);

}

void MainWindow::on_MBCh()
{
    if(CurrentComp->GetMB())
    {
        ClearInf();
        CurrentComp->GetMB()->Show(ui->TextInfo,ui->ImageLabel);CurrentComp->Show(ui->CompInformation);


    }
    ui->pushButton->setEnabled(false);

}

void MainWindow::on_CPUCh()
{
    if(CurrentComp->GetCpu())
    {
        ClearInf();
        CurrentComp->GetCpu()->Show(ui->TextInfo,ui->ImageLabel);
        CurrentComp->Show(ui->CompInformation);

    }
    ui->pushButton->setEnabled(false);

}

void MainWindow::on_VCCh()
{
    if(CurrentComp->GetVC())
    {
        ClearInf();
        CurrentComp->GetVC()->Show(ui->TextInfo,ui->ImageLabel);
        CurrentComp->Show(ui->CompInformation);

    }
    ui->pushButton->setEnabled(false);

}

void MainWindow::on_OZU1Ch()
{
    if(CurrentComp->GetOZU(0))
    {
        ClearInf();
        CurrentComp->GetOZU(0)->Show(ui->TextInfo,ui->ImageLabel);
        CurrentComp->Show(ui->CompInformation);

    }
    ui->pushButton->setEnabled(false);

}
void MainWindow::on_OZU2Ch()
{
    if(CurrentComp->GetOZU(1))
    {
        ClearInf();
        CurrentComp->GetOZU(1)->Show(ui->TextInfo,ui->ImageLabel);
        CurrentComp->Show(ui->CompInformation);

    }
    ui->pushButton->setEnabled(false);

}

void MainWindow::on_HWCh()
{
    if(CurrentComp->GetHW())
    {
        ClearInf();
        CurrentComp->GetHW()->Show(ui->TextInfo,ui->ImageLabel);

        CurrentComp->Show(ui->CompInformation);

    }
    ui->pushButton->setEnabled(false);

}

void MainWindow::on_listWidget_pressed(const QModelIndex &index)
{
    ui->pushButton->setEnabled(true);
    ui->ImageLabel->clear();
    ui->TextInfo->clear();
    if(ui->comboBox->currentIndex() == 1)
    {
        ListCPU.ShowInf(index.row(),ui->TextInfo,ui->ImageLabel);
    }
    else if(ui->comboBox->currentIndex() == 0)
    {
        ListMB.ShowInf(index.row(),ui->TextInfo,ui->ImageLabel);
    }
    else if(ui->comboBox->currentIndex() == 2)
    {
        ListOZU.ShowInf(index.row(),ui->TextInfo,ui->ImageLabel);
    }
    else if(ui->comboBox->currentIndex() == 3)
    {
        ListVC.ShowInf(index.row(),ui->TextInfo,ui->ImageLabel);
    }
    else if(ui->comboBox->currentIndex() == 4)
    {
        ListHD.ShowInf(index.row(),ui->TextInfo,ui->ImageLabel);
    }
    else if(ui->comboBox->currentIndex() == 5)
    {
        ListSW.ShowInf(index.row(),ui->TextInfo,ui->ImageLabel);
        ui->MinLabel->setText("Мінімальні вимоги");
        ui->BestLabel->setText("Рекомендовані вимоги");
        ui->CheckResLabl->setText("Cумісність: ");
        ui->SettingsLabel->setText("Рекомендовані налаштування: ");
    }
}

void MainWindow::OpenCrComSl()
{
    Dialog_CreateComp * DL = new Dialog_CreateComp;
    connect(this,SIGNAL(SWList(cHardList<cSoftware>)),DL,SLOT(PrCSW(cHardList<cSoftware>)));
    emit SWList(ListSW);
    connect(DL,SIGNAL(TransInf(infForCreate)),this,SLOT(CreateZbComp(infForCreate)));
    DL->exec();

}

void MainWindow::ClearInf()
{
    ui->ImageLabel->clear();
    ui->TextInfo->clear();
    ui->BestLabel->setStyleSheet("color:black");
    ui->MinLabel->setStyleSheet("color:black");
    ui->SettingsLabelNumber->setStyleSheet("color:black");
    ui->CheckResNum->setStyleSheet("color:black");
    ui->MinLabel->setText("");
    ui->BestLabel->setText("");
    ui->CheckResLabl->setText("");
    ui->SettingsLabel->setText("");
    ui->SettingsLabelNumber->setText("");
    ui->CheckResNum->setText("");
}





void MainWindow::on_RefreshButton_clicked()
{
    ListCPU.Clear();
    ListMB.Clear();
    ListOZU.Clear();
    ListVC.Clear();
    ListHD.Clear();
    ListSW.Clear();
    ListCPU.read("DB/CPU.txt");
    ListMB.read("DB/MBB.txt");
    ListMB.print(ui->listWidget);
    ListOZU.read("DB/OZU.txt");
    ListVC.read("DB/VC.txt");
    ListHD.read("DB/HW.txt");
    ListSW.read("DB/SW.txt");

    for(int i = 0;i < ListSW.getSize();i++)
    {
        if(!ListSW.getEl(i)->Verification(ListCPU,ListVC))
        {
            ListSW.DeleteIn(i);
            i--;
        }
    }
    ui->comboBox->setCurrentIndex(0);
    ClearInf();

}

void MainWindow::CreateZbComp(infForCreate ifc)
{
    cComputer* BufComp = new cComputer();
    cCPU* BufCPU = new cCPU();

    if(ifc.price ==-1)
    {
        for(int i = 0;i < ListCPU.getSize();i++)
        {
            if(ListCPU.getEl(i)->getFrequency() == ifc.frequency )
            {
                BufCPU = ListCPU.getEl(i);
                break;
            }
        }
        for(int i = 0;i < ListMB.getSize();i++)
        {
            if(ListMB.getEl(i)->GetSoket() == BufCPU->GetSoket())
            {
                BufComp->SetMB(ListMB.getEl(i));
                BufComp->SetCPU(BufCPU);
                break;
            }
        }
        for(int i = 0;i < ListVC.getSize();i++)
        {
            if(ListVC.getEl(i)->GetMem() == ifc.VMem )
            {
                BufComp->SetVC(ListVC.getEl(i));
                break;

            }
        }
        for(int i = 0;i < ListOZU.getSize();i++)
        {
            if(ListOZU.getEl(i)->GetMemory()*2 >= ifc.memozu && ListOZU.getEl(i)->GetMemory()*2 < ifc.memozu*2)
            {
                BufComp->SetOZU(ListOZU.getEl(i));
                 BufComp->SetOZU(ListOZU.getEl(i));
                break;
            }
        }
        for(int i = 0;i < ListHD.getSize();i++)
        {
            if(ListHD.getEl(i)->GetMem() == ifc.mem )
            {
                BufComp->SetHW(ListHD.getEl(i));

            }
        }

        CurrentComp = BufComp;
        CurrentComp->Show(lbl);

        CurrentComp->Show(ui->CompInformation);
        ui->MBImage->setToolTip(CurrentComp->GetMB()->GetName());

        ui->CpuImage->setToolTip(CurrentComp->GetCpu()->GetName());
        ui->OzuImage->setToolTip(CurrentComp->GetOZU(0)->GetName());
        ui->VcImage->setToolTip(CurrentComp->GetVC()->GetName());
        ui->HWImage->setToolTip(CurrentComp->GetHW()->GetName());
        return;
    }
    else
    {

        for(int i = 0;i<ListCPU.getSize();i++)
        {
            if(ListCPU.getEl(i)->getFrequency() == ifc.frequency)
            {
                BufCPU = ListCPU.getEl(i);

                for(int k = 0;k< ListMB.getSize();k++)
                {
                    if(ListMB.getEl(k)->GetSoket() == BufCPU->GetSoket())
                    {
                        BufComp->SetMB(ListMB.getEl(k),0);
                        BufComp->SetCPU(BufCPU);
                        for(int j = 0;j<ListOZU.getSize();j++)
                        {
                            if(ListOZU.getEl(j)->GetMemory()*2 >= ifc.memozu && ListOZU.getEl(j)->GetMemory()*2 < ifc.memozu*2)
                            {
                                BufComp->SetOZU(ListOZU.getEl(j));
                                 BufComp->SetOZU(ListOZU.getEl(j));
                            }
                        }

                        for(int j = 0;j<ListHD.getSize();j++)
                        {
                            if(ListHD.getEl(j)->GetMem() == ifc.mem)
                            {
                                BufComp->SetHW(ListHD.getEl(j));

                            }
                        }
                        for(int j = 0;j<ListVC.getSize();j++)
                        {
                            if(ListVC.getEl(j)->GetMem() == ifc.VMem)
                            {
                                BufComp->SetVC(ListVC.getEl(j));

                            }
                            if(BufComp->IsFull() && BufComp->GetPrice() <=ifc.price)
                            {
                                CurrentComp = BufComp;
                                CurrentComp->Show(lbl);

                                CurrentComp->Show(ui->CompInformation);
                                ui->MBImage->setToolTip(CurrentComp->GetMB()->GetName());

                                ui->CpuImage->setToolTip(CurrentComp->GetCpu()->GetName());
                                ui->OzuImage->setToolTip(CurrentComp->GetOZU(0)->GetName());
                                ui->VcImage->setToolTip(CurrentComp->GetVC()->GetName());
                                ui->HWImage->setToolTip(CurrentComp->GetHW()->GetName());
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
    QMessageBox::information(0,"Помилка збірки!","Неможливо зібрати збірку за такою ціною!");

}

void MainWindow::NewHardOpen()
{
    newhard * HL = new newhard() ;


    connect(HL,SIGNAL(TransInf(DataHW,int)),this,SLOT(NewHard(DataHW,int)));

    connect(this,SIGNAL(Lists(cHardList<cCPU>,cHardList<cVideoCard>)),HL,SLOT(PrCSW(cHardList<cCPU>,cHardList<cVideoCard>)));
       emit Lists(ListCPU,ListVC);
    HL->exec();
}

void MainWindow::NewHard(DataHW HW, int i)
{

    if(i == 1)
    {
        cCPU* buf = new cCPU(&HW);
        ListCPU.Add(buf);
        ListCPU.PrintTF("DB/CPU.txt",i);
        ListCPU.print(ui->listWidget);
        ui->comboBox->setCurrentIndex(i);
    }
    else if(i == 0)
    {
        cMotherBoard* buf = new cMotherBoard(&HW);
        ListMB.Add(buf);
        ListMB.PrintTF("DB/MBB.txt",i);
        ListMB.print(ui->listWidget);
        ui->comboBox->setCurrentIndex(i);
    }
    else if(i == 3)
    {
        cVideoCard* buf = new cVideoCard(&HW);
        ListVC.Add(buf);
        ListVC.PrintTF("DB/VC.txt",i);
        ListVC.print(ui->listWidget);
        ui->comboBox->setCurrentIndex(i);
    }
    else if(i == 2)
    {
        cOZU* buf = new cOZU(&HW);
        ListOZU.Add(buf);
        ListOZU.PrintTF("DB/OZU.txt",i);
        ListOZU.print(ui->listWidget);
        ui->comboBox->setCurrentIndex(i);
    }
    else if(i == 4)
    {
        cHardDrive* buf = new cHardDrive(&HW);
        ListHD.Add(buf);
        ListHD.PrintTF("DB/HW.txt",i);
        ListHD.print(ui->listWidget);
        ui->comboBox->setCurrentIndex(i);
    }
    else if(i == 5)
    {
        cSoftware* buf = new cSoftware(&HW);
        ListSW.Add(buf);
        for(int i = 0;i < ListSW.getSize();i++)
        {
            if(!ListSW.getEl(i)->Verification(ListCPU,ListVC))
            {
                ListSW.DeleteIn(i);
                i--;
            }
        }

        ListSW.print(ui->listWidget);
        ListSW.PrintTF("DB/SW.txt",i);
        ui->comboBox->setCurrentIndex(i);

    }



}

void MainWindow::on_DelBut_clicked()
{
    int i = ui->listWidget->currentRow();
    int j = ui->comboBox->currentIndex();
    if(i != -1)
    {
        if(j== 0)
        {
            ListMB.DeleteIn(i);
    ListMB.PrintTF("DB/MBB.txt",j);
            ListMB.print(ui->listWidget);
        }
        if(j == 1)
        {
            ListCPU.DeleteIn(i);
            ListCPU.PrintTF("DB/CPU.txt",j);
            ListCPU.print(ui->listWidget);
        }
        if(j== 2)
        {
            ListOZU.DeleteIn(i);
            ListOZU.PrintTF("DB/OZU.txt",j);
            ListOZU.print(ui->listWidget);
        }
        if(j == 3)
        {
            ListVC.DeleteIn(i);
            ListVC.PrintTF("DB/VC.txt",j);
            ListVC.print(ui->listWidget);
        }
        if(j == 4)
        {
            ListHD.DeleteIn(i);
            ListHD.PrintTF("DB/HW.txt",j);
            ListHD.print(ui->listWidget);
        }
        if(j == 5)
        {
            ListSW.DeleteIn(i);
            ListSW.print(ui->listWidget);
            ListHD.PrintTF("DB/SW.txt",j);
        }
        ClearInf();
    }
}
