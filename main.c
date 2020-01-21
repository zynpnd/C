#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Ucret
{
    int YuzmeP;
    int YuzmeT;
    int FitnessP;
    int FitnessT;
    int TenisP;
    int TenisT;
} ucret;
typedef struct Bolumler
{
    int bolum_id;
    char bolum_ismi[10];
} Bolum;
typedef struct Uyeler
{
    char uye_id[10];
    char uye_adi[10];
    char uye_soyadi[10];
    int uye_yas;
    char uye_kampanya[10]; //eski uye - yeni uye
    char uye_odeme[10]; //pesin-taksit
    char uye_durum[10]; // ogrenci - sivil;
    int uye_ucret;
    int bsayisi;
    Bolum *bolum;
    struct Uyeler *sonraki;
} Uye;
Uye *uyeler=NULL,*gecici=NULL,*son=NULL,*temp,*onceki,*ilk=NULL;
ucret *Fiyat=NULL;
Bolum *bilk=NULL;
int Hesaplama(char kampanya,int yas,char durum,char odeme,int bolum);
int flag=0;
void listeTemizle(){

   gecici=ilk;
   while(gecici!=NULL){

    ilk=gecici->sonraki;
    gecici=gecici->sonraki;
    free(gecici);
   }
}
void DosyayaEkle()
{
   listeTemizle();
    FILE *UyeDosya;
    Uye *yeniUye;
    int uyesayisi=0,yas,ucret,bolum,temp,bolum_id;
    char ad[15],soyad[15],*bolum_ad,kampanya,durum,odeme,id[10];
    int hesapla=0;
    UyeDosya=fopen("uyeler1628.txt","a+");
    if(UyeDosya==NULL)
    {
        printf("\nEklenecek dosya acilmadi.\n");
        return ;
    }
    if(uyesayisi==0)
    {
        yeniUye=(Uye*)malloc(sizeof(Uye));
        uyesayisi++;
    }
    else
    {
        yeniUye=(Uye*)realloc(yeniUye,sizeof(Uye));
        uyesayisi++;
    }
    printf("\tUyenin idsi:");
    scanf("%s",id);
    for(gecici=ilk; gecici!=NULL; gecici=gecici->sonraki)
    {
        if(strcmp(gecici->uye_id,id)==0)
        {
            printf("Girdiginiz id kullanilmaktadir.Baska id giriniz");
            return ;
        }
    }
    printf("\tUyenin adi: ");
    scanf("%s",&ad);
    printf("\tUyenin soyadi:");
    scanf("%s",&soyad);
    printf("\tEski Uye[E/e]\n");
    printf("\tYeni Uye[Y/y]\n");
    printf("\tUyelik durumu(E/Y):");
    scanf(" %c",&kampanya);
    if(kampanya == 'e' || kampanya == 'E' || kampanya == 'Y' || kampanya == 'y') { }
    else
    {
        printf("\nYanlis secim yaptiniz.Lutfen tekrar deneyiniz.\n");
        return ;
    }
    printf("\tUyenin yasini giriniz:");
    scanf("%d",&yas);
    printf("\tOgrenci[O/o]\n");
    printf("\tSivil[S/s]\n");
    printf("\tUyelik durumu(O/S):");
    scanf(" %c",&durum);
    if(durum == 'O' || durum == 'o' || durum == 'S' || durum == 's') { }
    else
    {
        printf("\nYanlis secim yaptiniz.Lutfen tekrar deneyiniz.\n");
        return ;
    }
    for(gecici=ilk; gecici!=NULL; gecici=gecici->sonraki)
    {
        if(( durum == 'o' || durum == 'O' ) && yas >= 40)
        {
            printf("Ogrenciyi secemezsiniz.Cunku yasiniz 40 dan buyuk...");
            return ;
        }
    }
    printf("\tPesin[P/p]\n");
    printf("\tTaksit[T/t]\n");
    printf("\tOdeme durumu(P/T):");
    scanf(" %c",&odeme);
    if(odeme == 'P' || odeme == 'p'  || odeme == 'T'|| odeme == 't') { }
    else
    {
        printf("Yanlis secim yaptiniz.Lutfen tekrar deneyiniz.");
        return ;
    }
    printf("\n");
    printf("\tYuzme(Y) ----------------------------> 1\n");
    printf("\tFitness(F) --------------------------> 2\n");
    printf("\tTenis(T) ----------------------------->3\n");
    printf("\tFitness+Yuzme(FY) -------------------->4\n");
    printf("\tFitness+Tenis(FT) -------------------->5\n");
    printf("\tYuzme+Tenis(YT) ---------------------->6\n");
    printf("\tFitness+Yuzme+Tenis(FYT) ------------->7\n");
    printf(" Secmek istediginiz bolum:");
    scanf("%d",&bolum);
    if(bolum == 1  || bolum == 2 || bolum == 3)
    {
        temp=1;
        if(bolum == 1)
        {
            bolum_id=100;
            bolum_ad="Y";
        }
        else if(bolum == 2)
        {
            bolum_id=101;
            bolum_ad="F";
        }
        else
        {
            bolum_id=102;
            bolum_ad="T";
        }
    }
    else if(bolum ==4 || bolum ==5 || bolum == 6)
    {
        temp=2;
        if(bolum == 4)
        {
            bolum_id=103;
            bolum_ad="FY";
        }
        else if(bolum == 5)
        {
            bolum_id=104;
            bolum_ad="FT";
        }
        else
        {
            bolum_id=105;
            bolum_ad="YT";
        }
    }
    else if(bolum== 7)
    {
        temp=3;
        bolum_id=106;
        bolum_ad="FYT";
    }
    else
    {
        printf("Yanlis sayi girdiniz!");
        return ;
    }
    hesapla=Hesaplama(kampanya,yas,durum,odeme,bolum);
    printf("Odenecek ucret:%d",hesapla);
    fprintf(UyeDosya,"%s %s %s %c %d %c %c %d %d %s %d\n",id,ad,soyad,kampanya,yas,durum,odeme,temp,bolum_id,bolum_ad,hesapla);
    fclose(UyeDosya);
    Ekle();
}
void FiyatOku()
{
    FILE *Dosya=fopen("fiyatlar1628.txt","r");
    if(Dosya == NULL)
    {
        printf("Dosya okunmadi.");
        return;
    }
    Fiyat=(ucret *)malloc(sizeof(ucret));
    while(!feof(Dosya))
        fscanf(Dosya,"%d %d %d %d %d %d",&Fiyat->YuzmeP,&Fiyat->YuzmeT,&Fiyat->FitnessP,&Fiyat->FitnessT,&Fiyat->TenisP,&Fiyat->TenisT);
    //printf("%d %d %d %d %d %d",Fiyat->YuzmeP,Fiyat->YuzmeT,Fiyat->FitnessP,Fiyat->FitnessT,Fiyat->TenisP,Fiyat->TenisT);
    fclose(Dosya);
}
int Hesaplama(char kampanya,int yas,char durum,char odeme,int bolum)
{
    system("cls");
    int sec;
    double fiyat;
    printf("1 ay --------------->1\n");
    printf("3 ay --------------->2\n");
    printf("6 ay --------------->3\n");
    printf("12 ay -------------->4\n");
    printf("Kac aylik uyelik:");
    scanf("%d",&sec);
    switch(sec)
    {
    case 1:
        if(durum == 'O' || durum =='o') //ogrenci
        {
            if(kampanya == 'E' || kampanya == 'e')//eski uye
            {
                if(odeme == 'P' || odeme== 'p')  //pesin
                {
                    if(bolum == 7)//bolum sayisi 3 ise yani tum bolumleri aliyorsa
                    {
                        fiyat=(Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*0.2+(Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*0.05+(Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*0.03;
                        fiyat=(Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)-fiyat;
                    }
                    else  if(bolum == 6) //tum bolumleri almiyorsa
                    {
                        fiyat=(Fiyat->YuzmeP+Fiyat->TenisP)*0.2+(Fiyat->YuzmeP+Fiyat->TenisP)*0.05;
                        fiyat=(Fiyat->YuzmeP+Fiyat->TenisP)-fiyat;
                    }
                    else if(bolum == 5)
                    {
                        fiyat=(Fiyat->FitnessP+Fiyat->TenisP)*0.2+(Fiyat->FitnessP+Fiyat->TenisP)*0.05;
                        fiyat=(Fiyat->FitnessP+Fiyat->TenisP)-fiyat;
                    }
                    else if(bolum == 4)
                    {
                        fiyat=(Fiyat->FitnessP+Fiyat->YuzmeP)*0.2+(Fiyat->FitnessP+Fiyat->YuzmeP)*0.05;
                        fiyat=(Fiyat->FitnessP+Fiyat->YuzmeP)-fiyat;
                    }
                    else if(bolum == 3)
                    {
                        fiyat=(Fiyat->TenisP)*0.2+(Fiyat->TenisP)*0.05;
                        fiyat=(Fiyat->TenisP)-fiyat;
                    }
                    else if(bolum == 2)
                    {
                        fiyat=(Fiyat->FitnessP)*0.2+(Fiyat->FitnessP)*0.05;
                        fiyat=(Fiyat->FitnessP)-fiyat;
                    }
                    else
                    {
                        fiyat=(Fiyat->YuzmeP)*0.2+(Fiyat->YuzmeP)*0.05;
                        fiyat=(Fiyat->YuzmeP)-fiyat;
                    }

                }
                else//taksit
                {
                    if(bolum == 7)
                    {
                        fiyat=(Fiyat->FitnessT+Fiyat->TenisT+Fiyat->YuzmeT)-((Fiyat->FitnessT+Fiyat->TenisT+Fiyat->YuzmeT)*0.2+(Fiyat->FitnessT+Fiyat->TenisT+Fiyat->YuzmeT)*0.05+(Fiyat->FitnessT+Fiyat->TenisT+Fiyat->YuzmeT)*0.03);

                    }
                    else if(bolum == 6)
                    {
                        fiyat=(Fiyat->YuzmeT+Fiyat->TenisT)-((Fiyat->YuzmeT+Fiyat->TenisT)*0.2+(Fiyat->YuzmeT+Fiyat->TenisT)*0.05);
                    }
                    else if(bolum == 5)

                    {
                        fiyat=(Fiyat->FitnessT+Fiyat->TenisT)-((Fiyat->FitnessT+Fiyat->TenisT)*0.2+(Fiyat->FitnessT+Fiyat->TenisT)*0.05);
                    }
                    else if(bolum == 4)
                    {
                        fiyat=(Fiyat->FitnessT+Fiyat->YuzmeT)-((Fiyat->FitnessT+Fiyat->YuzmeT)*0.2+(Fiyat->FitnessT+Fiyat->YuzmeT)*0.05);
                    }
                    else if(bolum == 3)
                    {
                        fiyat=(Fiyat->TenisT)-((Fiyat->TenisT)*0.2+(Fiyat->TenisT)*0.05);
                    }
                    else if(bolum == 2)
                    {
                        fiyat=(Fiyat->FitnessT)-((Fiyat->FitnessT)*0.2+(Fiyat->FitnessT)*0.05);
                    }
                    else
                    {
                        fiyat=(Fiyat->YuzmeT)-((Fiyat->YuzmeT)*0.2+(Fiyat->YuzmeT)*0.05);
                    }
                }
            }
            else//yeni uye
            {
                if(bolum == 7)//bolum sayisi 3 ise yani tum bolumleri aliyorsa
                {
                    fiyat=(Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)-((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*0.2+(Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*0.03);
                }
                else  if(bolum == 6)
                {
                    fiyat=(Fiyat->YuzmeP+Fiyat->TenisP)-((Fiyat->YuzmeP+Fiyat->TenisP)*0.2);
                }
                else if(bolum == 5)
                {
                    fiyat=(Fiyat->FitnessP+Fiyat->TenisP)-((Fiyat->FitnessP+Fiyat->TenisP)*0.2);
                }
                else if(bolum == 4)
                {
                    fiyat=(Fiyat->FitnessP+Fiyat->YuzmeP)-((Fiyat->FitnessP+Fiyat->YuzmeP)*0.2);
                }
                else if(bolum == 3)
                {
                    fiyat=(Fiyat->TenisP)-((Fiyat->TenisP)*0.2);
                }
                else if(bolum == 2)
                {
                    fiyat=(Fiyat->FitnessP)-((Fiyat->FitnessP)*0.2);
                }
                else
                {
                    fiyat=(Fiyat->YuzmeP)-((Fiyat->YuzmeP)*0.2);
                }
            }
        }
        else //sivil
        {
            if(yas < 65)
            {
                if(bolum == 7)//bolum sayisi 3 ise yani tum bolumleri aliyorsa
                {
                    fiyat=(Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)-((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*0.03);
                }
                else  if(bolum == 6)
                {
                    fiyat=(Fiyat->YuzmeP+Fiyat->TenisP);
                }
                else if(bolum == 5)
                {
                    fiyat=(Fiyat->FitnessP+Fiyat->TenisP);
                }
                else if(bolum == 4)
                {
                    fiyat=(Fiyat->FitnessP+Fiyat->YuzmeP);
                }
                else if(bolum == 3)
                {
                    fiyat=(Fiyat->TenisP);
                }
                else if(bolum == 2)
                {
                    fiyat=(Fiyat->FitnessP);
                }
                else
                {
                    fiyat=(Fiyat->YuzmeP);
                }
            }
            else //65 ve uzeri ise
            {
                if(bolum == 7)//bolum sayisi 3 ise yani tum bolumleri aliyorsa
                {
                    fiyat=(Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)-((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*0.03+(Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*0.1);
                }
                else  if(bolum == 6)
                {
                    fiyat=(Fiyat->YuzmeP+Fiyat->TenisP)-((Fiyat->YuzmeP+Fiyat->TenisP)*0.1);
                }
                else if(bolum == 5)
                {
                    fiyat=(Fiyat->FitnessP+Fiyat->TenisP)-((Fiyat->FitnessP+Fiyat->TenisP)*0.1);
                }
                else if(bolum == 4)
                {
                    fiyat=(Fiyat->FitnessP+Fiyat->YuzmeP)-((Fiyat->FitnessP+Fiyat->YuzmeP)*0.1);
                }
                else if(bolum == 3)
                {
                    fiyat=(Fiyat->TenisP)-((Fiyat->TenisP)*0.1);
                }
                else if(bolum == 2)
                {
                    fiyat=(Fiyat->FitnessP)-((Fiyat->FitnessP)*0.1);
                }
                else
                {
                    fiyat=(Fiyat->YuzmeP)-((Fiyat->YuzmeP)*0.1);
                }
            }

        }
        break;
    case 2:
        if(durum == 'O' || durum =='o') //ogrenci
        {
            if(kampanya == 'E' || kampanya == 'e')//eski uye
            {
                if(odeme == 'P' || odeme== 'p')  //pesin
                {
                    if(bolum == 7)//bolum sayisi 3 ise yani tum bolumleri aliyorsa
                    {
                        fiyat=(((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*2)*0.2+((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*2)*0.05+(Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*2)*0.03;
                        fiyat=((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*2)-fiyat;
                    }
                    else  if(bolum == 6) //tum bolumleri almiyorsa
                    {
                        fiyat=((Fiyat->YuzmeP+Fiyat->TenisP)*2)*0.2+((Fiyat->YuzmeP+Fiyat->TenisP)*2)*0.05;
                        fiyat=((Fiyat->YuzmeP+Fiyat->TenisP)*2)-fiyat;
                    }
                    else if(bolum == 5)
                    {
                        fiyat=((Fiyat->FitnessP+Fiyat->TenisP)*2)*0.2+((Fiyat->FitnessP+Fiyat->TenisP)*2)*0.05;
                        fiyat=((Fiyat->FitnessP+Fiyat->TenisP)*2)-fiyat;
                    }
                    else if(bolum == 4)
                    {
                        fiyat=((Fiyat->FitnessP+Fiyat->YuzmeP)*2)*0.2+((Fiyat->FitnessP+Fiyat->YuzmeP)*2)*0.05;
                        fiyat=((Fiyat->FitnessP+Fiyat->YuzmeP)*2)-fiyat;
                    }
                    else if(bolum == 3)
                    {
                        fiyat=((Fiyat->TenisP)*2)*0.2+((Fiyat->TenisP)*2)*0.05;
                        fiyat=((Fiyat->TenisP)*2)-fiyat;
                    }
                    else if(bolum == 2)
                    {
                        fiyat=((Fiyat->FitnessP)*2)*0.2+((Fiyat->FitnessP)*2)*0.05;
                        fiyat=((Fiyat->FitnessP)*2)-fiyat;
                    }
                    else
                    {
                        fiyat=((Fiyat->YuzmeP)*2)*0.2+((Fiyat->YuzmeP)*2)*0.05;
                        fiyat=((Fiyat->YuzmeP)*2)-fiyat;
                    }
                }
                else//taksit
                {
                    if(bolum == 7)
                    {
                        fiyat=((Fiyat->FitnessT+Fiyat->TenisT+Fiyat->YuzmeT)*2)-(((Fiyat->FitnessT+Fiyat->TenisT+Fiyat->YuzmeT)*2)*0.2+((Fiyat->FitnessT+Fiyat->TenisT+Fiyat->YuzmeT)*2)*0.05+((Fiyat->FitnessT+Fiyat->TenisT+Fiyat->YuzmeT)*2)*0.03);

                    }
                    else if(bolum == 6)
                    {
                        fiyat=((Fiyat->YuzmeT+Fiyat->TenisT)*2)-(((Fiyat->YuzmeT+Fiyat->TenisT)*2)*0.2+((Fiyat->YuzmeT+Fiyat->TenisT)*2)*0.05);
                    }
                    else if(bolum == 5)

                    {
                        fiyat=((Fiyat->FitnessT+Fiyat->TenisT)*2)-(((Fiyat->FitnessT+Fiyat->TenisT)*2)*0.2+((Fiyat->FitnessT+Fiyat->TenisT)*2)*0.05);
                    }
                    else if(bolum == 4)
                    {
                        fiyat=((Fiyat->FitnessT+Fiyat->YuzmeT)*2)-(((Fiyat->FitnessT+Fiyat->YuzmeT)*2)*0.2+((Fiyat->FitnessT+Fiyat->YuzmeT)*2)*0.05);
                    }
                    else if(bolum == 3)
                    {
                        fiyat=((Fiyat->TenisT)*2)-(((Fiyat->TenisT)*2)*0.2+((Fiyat->TenisT)*2)*0.05);
                    }
                    else if(bolum == 2)
                    {
                        fiyat=((Fiyat->FitnessT)*2)-(((Fiyat->FitnessT)*2)*0.2+((Fiyat->FitnessT)*2)*0.05);
                    }
                    else
                    {
                        fiyat=((Fiyat->YuzmeT)*2)-(((Fiyat->YuzmeT)*2)*0.2+((Fiyat->YuzmeT)*2)*0.05);
                    }
                }
            }
            else//yeni
            {
                if(bolum == 7)//bolum sayisi 3 ise yani tum bolumleri aliyorsa
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*2)-(((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*2)*0.2+((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*2)*0.03);
                }
                else  if(bolum == 6)
                {
                    fiyat=((Fiyat->YuzmeP+Fiyat->TenisP)*2)-(((Fiyat->YuzmeP+Fiyat->TenisP)*2)*0.2);
                }
                else if(bolum == 5)
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->TenisP)*2)-(((Fiyat->FitnessP+Fiyat->TenisP)*2)*0.2);
                }
                else if(bolum == 4)
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->YuzmeP)*2)-(((Fiyat->FitnessP+Fiyat->YuzmeP)*2)*0.2);
                }
                else if(bolum == 3)
                {
                    fiyat=((Fiyat->TenisP)*2)-(((Fiyat->TenisP)*2)*0.2);
                }
                else if(bolum == 2)
                {
                    fiyat=((Fiyat->FitnessP)*2)-(((Fiyat->FitnessP)*2)*0.2);
                }
                else
                {
                    fiyat=((Fiyat->YuzmeP)*2)-(((Fiyat->YuzmeP)*2)*0.2);
                }
            }
        }
        else //sivil
        {
            if(yas < 65)
            {
                if(bolum == 7)//bolum sayisi 3 ise yani tum bolumleri aliyorsa
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*2)-(((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*2)*0.03);
                }
                else  if(bolum == 6)
                {
                    fiyat=((Fiyat->YuzmeP+Fiyat->TenisP)*2);
                }
                else if(bolum == 5)
                {
                    fiyat=(Fiyat->FitnessP+Fiyat->TenisP)*2;
                }
                else if(bolum == 4)
                {
                    fiyat=(Fiyat->FitnessP+Fiyat->YuzmeP)*2;
                }
                else if(bolum == 3)
                {
                    fiyat=(Fiyat->TenisP)*2;
                }
                else if(bolum == 2)
                {
                    fiyat=(Fiyat->FitnessP)*2;
                }
                else
                {
                    fiyat=(Fiyat->YuzmeP)*2;
                }
            }
            else  //65 yas ve uzeri ise
            {
                if(bolum == 7)//bolum sayisi 3 ise yani tum bolumleri aliyorsa
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*2)-(((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*2)*0.03+((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*2)*0.1);
                }
                else  if(bolum == 6)
                {
                    fiyat=((Fiyat->YuzmeP+Fiyat->TenisP)*2)-(((Fiyat->YuzmeP+Fiyat->TenisP)*2)*0.1);
                }
                else if(bolum == 5)
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->TenisP)*2)-(((Fiyat->FitnessP+Fiyat->TenisP)*2)*0.1);
                }
                else if(bolum == 4)
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->YuzmeP)*2)-(((Fiyat->FitnessP+Fiyat->YuzmeP)*2)*0.1);
                }
                else if(bolum == 3)
                {
                    fiyat=((Fiyat->TenisP)*2)-(((Fiyat->TenisP)*2)*0.1);
                }
                else if(bolum == 2)
                {
                    fiyat=((Fiyat->FitnessP)*2)-(((Fiyat->FitnessP)*2)*0.1);
                }
                else
                {
                    fiyat=((Fiyat->YuzmeP)*2)-(((Fiyat->YuzmeP)*2)*0.1);
                }
            }

        }
        break;
    case 3:
       if(durum == 'O' || durum =='o') //ogrenci
        {
            if(kampanya == 'E' || kampanya == 'e')//eski uye
            {
                if(odeme == 'P' || odeme== 'p')  //pesin
                {
                    if(bolum == 7)//bolum sayisi 3 ise yani tum bolumleri aliyorsa
                    {
                        fiyat=((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*4)-(((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*4)*0.2+((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*4)*0.05+((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*2)*0.03);
                    }
                    else  if(bolum == 6) //tum bolumleri almiyorsa
                    {
                        fiyat=((Fiyat->YuzmeP+Fiyat->TenisP)*4)-(((Fiyat->YuzmeP+Fiyat->TenisP)*4)*0.2+((Fiyat->YuzmeP+Fiyat->TenisP)*4)*0.05);

                    }
                    else if(bolum == 5)
                    {
                        fiyat=(((Fiyat->FitnessP+Fiyat->TenisP)*4)-((Fiyat->FitnessP+Fiyat->TenisP)*4)*0.2+((Fiyat->FitnessP+Fiyat->TenisP)*4)*0.05);
                    }
                    else if(bolum == 4)
                    {
                        fiyat=((Fiyat->FitnessP+Fiyat->YuzmeP)*4)-(((Fiyat->FitnessP+Fiyat->YuzmeP)*4)*0.2+((Fiyat->FitnessP+Fiyat->YuzmeP)*4)*0.05);
                    }
                    else if(bolum == 3)
                    {
                        fiyat=((Fiyat->TenisP)*4)-(((Fiyat->TenisP)*4)*0.2+((Fiyat->TenisP)*4)*0.05);
                    }
                    else if(bolum == 2)
                    {
                        fiyat=((Fiyat->FitnessP)*4)-(((Fiyat->FitnessP)*4)*0.2+((Fiyat->FitnessP)*4)*0.05);
                    }
                    else
                    {
                        fiyat=((Fiyat->YuzmeP)*4)-(((Fiyat->YuzmeP)*4)*0.2+((Fiyat->YuzmeP)*4)*0.05);
                    }
                }
                else//taksit
                {
                    if(bolum == 7)
                    {
                        fiyat=((Fiyat->FitnessT+Fiyat->TenisT+Fiyat->YuzmeT)*4)-(((Fiyat->FitnessT+Fiyat->TenisT+Fiyat->YuzmeT)*4)*0.2+((Fiyat->FitnessT+Fiyat->TenisT+Fiyat->YuzmeT)*4)*0.05+((Fiyat->FitnessT+Fiyat->TenisT+Fiyat->YuzmeT)*4)*0.03);

                    }
                    else if(bolum == 6)
                    {
                        fiyat=((Fiyat->YuzmeT+Fiyat->TenisT)*4)-(((Fiyat->YuzmeT+Fiyat->TenisT)*4)*0.2+((Fiyat->YuzmeT+Fiyat->TenisT)*4)*0.05);
                    }
                    else if(bolum == 5)

                    {
                        fiyat=((Fiyat->FitnessT+Fiyat->TenisT)*4)-(((Fiyat->FitnessT+Fiyat->TenisT)*4)*0.2+((Fiyat->FitnessT+Fiyat->TenisT)*4)*0.05);
                    }
                    else if(bolum == 4)
                    {
                        fiyat=((Fiyat->FitnessT+Fiyat->YuzmeT)*4)-(((Fiyat->FitnessT+Fiyat->YuzmeT)*4)*0.2+((Fiyat->FitnessT+Fiyat->YuzmeT)*4)*0.05);
                    }
                    else if(bolum == 3)
                    {
                        fiyat=((Fiyat->TenisT)*4)-(((Fiyat->TenisT)*4)*0.2+((Fiyat->TenisT)*4)*0.05);
                    }
                    else if(bolum == 2)
                    {
                        fiyat=((Fiyat->FitnessT)*4)-(((Fiyat->FitnessT)*4)*0.2+((Fiyat->FitnessT)*4)*0.05);
                    }
                    else
                    {
                        fiyat=((Fiyat->YuzmeT)*4)-(((Fiyat->YuzmeT)*4)*0.2+((Fiyat->YuzmeT)*4)*0.05);
                    }
                }
            }
            else//yeni
            {
                if(bolum == 7)//bolum sayisi 3 ise yani tum bolumleri aliyorsa
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*4)-(((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*4)*0.2+((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*4)*0.03);
                }
                else  if(bolum == 6)
                {
                    fiyat=((Fiyat->YuzmeP+Fiyat->TenisP)*4)-(((Fiyat->YuzmeP+Fiyat->TenisP)*4)*0.2);
                }
                else if(bolum == 5)
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->TenisP)*4)-(((Fiyat->FitnessP+Fiyat->TenisP)*4)*0.2);
                }
                else if(bolum == 4)
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->YuzmeP)*4)-(((Fiyat->FitnessP+Fiyat->YuzmeP)*4)*0.2);
                }
                else if(bolum == 3)
                {
                    fiyat=((Fiyat->TenisP)*4)-(((Fiyat->TenisP)*4)*0.2);
                }
                else if(bolum == 2)
                {
                    fiyat=((Fiyat->FitnessP)*4)-(((Fiyat->FitnessP)*4)*0.2);
                }
                else
                {
                    fiyat=((Fiyat->YuzmeP)*4)-(((Fiyat->YuzmeP)*4)*0.2);
                }
            }
        }
        else //sivil
        {
            if(yas < 65)
            {
                if(bolum == 7)//bolum sayisi 3 ise yani tum bolumleri aliyorsa
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*4)-(((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*4)*0.03);
                }
                else  if(bolum == 6)
                {
                    fiyat=((Fiyat->YuzmeP+Fiyat->TenisP)*4);
                }
                else if(bolum == 5)
                {
                    fiyat=(Fiyat->FitnessP+Fiyat->TenisP)*4;
                }
                else if(bolum == 4)
                {
                    fiyat=(Fiyat->FitnessP+Fiyat->YuzmeP)*4;
                }
                else if(bolum == 3)
                {
                    fiyat=(Fiyat->TenisP)*4;
                }
                else if(bolum == 2)
                {
                    fiyat=(Fiyat->FitnessP)*4;
                }
                else
                {
                    fiyat=(Fiyat->YuzmeP)*4;
                }
            }
            else  //65 yas ve uzeri ise
            {
                if(bolum == 7)//bolum sayisi 3 ise yani tum bolumleri aliyorsa
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*4)-(((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*4)*0.03+((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*4)*0.1);
                }
                else  if(bolum == 6)
                {
                    fiyat=((Fiyat->YuzmeP+Fiyat->TenisP)*4)-(((Fiyat->YuzmeP+Fiyat->TenisP)*4)*0.1);
                }
                else if(bolum == 5)
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->TenisP)*4)-(((Fiyat->FitnessP+Fiyat->TenisP)*4)*0.1);
                }
                else if(bolum == 4)
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->YuzmeP)*4)-(((Fiyat->FitnessP+Fiyat->YuzmeP)*4)*0.1);
                }
                else if(bolum == 3)
                {
                    fiyat=((Fiyat->TenisP)*4)-(((Fiyat->TenisP)*4)*0.1);
                }
                else if(bolum == 2)
                {
                    fiyat=((Fiyat->FitnessP)*4)-(((Fiyat->FitnessP)*4)*0.1);
                }
                else
                {
                    fiyat=((Fiyat->YuzmeP)*4)-(((Fiyat->YuzmeP)*4)*0.1);
                }
            }
        }
        break;
    case 4:
        if(durum == 'O' || durum =='o') //ogrenci
        {
            if(kampanya == 'E' || kampanya == 'e')//eski uye
            {
                if(odeme == 'P' || odeme== 'p')  //pesin
                {
                    if(bolum == 7)//bolum sayisi 3 ise yani tum bolumleri aliyorsa
                    {
                        fiyat=(((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*9)*0.2+((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*9)*0.05+(Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*9)*0.03;
                        fiyat=((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*9)-fiyat;
                    }
                    else  if(bolum == 6) //tum bolumleri almiyorsa
                    {
                        fiyat=((Fiyat->YuzmeP+Fiyat->TenisP)*9)*0.2+((Fiyat->YuzmeP+Fiyat->TenisP)*9)*0.05;
                        fiyat=((Fiyat->YuzmeP+Fiyat->TenisP)*9)-fiyat;
                    }
                    else if(bolum == 5)
                    {
                        fiyat=((Fiyat->FitnessP+Fiyat->TenisP)*9)*0.2+((Fiyat->FitnessP+Fiyat->TenisP)*9)*0.05;
                        fiyat=((Fiyat->FitnessP+Fiyat->TenisP)*9)-fiyat;
                    }
                    else if(bolum == 4)
                    {
                        fiyat=((Fiyat->FitnessP+Fiyat->YuzmeP)*9)*0.2+((Fiyat->FitnessP+Fiyat->YuzmeP)*9)*0.05;
                        fiyat=((Fiyat->FitnessP+Fiyat->YuzmeP)*9)-fiyat;
                    }
                    else if(bolum == 3)
                    {
                        fiyat=((Fiyat->TenisP)*9)*0.2+((Fiyat->TenisP)*9)*0.05;
                        fiyat=((Fiyat->TenisP)*9)-fiyat;
                    }
                    else if(bolum == 2)
                    {
                        fiyat=((Fiyat->FitnessP)*9)*0.2+((Fiyat->FitnessP)*9)*0.05;
                        fiyat=((Fiyat->FitnessP)*9)-fiyat;
                    }
                    else
                    {
                        fiyat=((Fiyat->YuzmeP)*9)*0.2+((Fiyat->YuzmeP)*9)*0.05;
                        fiyat=((Fiyat->YuzmeP)*9)-fiyat;
                    }
                }
                else//taksit
                {
                    if(bolum == 7)
                    {
                        fiyat=((Fiyat->FitnessT+Fiyat->TenisT+Fiyat->YuzmeT)*9)-(((Fiyat->FitnessT+Fiyat->TenisT+Fiyat->YuzmeT)*9)*0.2+((Fiyat->FitnessT+Fiyat->TenisT+Fiyat->YuzmeT)*9)*0.05+((Fiyat->FitnessT+Fiyat->TenisT+Fiyat->YuzmeT)*2)*0.03);

                    }
                    else if(bolum == 6)
                    {
                        fiyat=((Fiyat->YuzmeT+Fiyat->TenisT)*9)-(((Fiyat->YuzmeT+Fiyat->TenisT)*9)*0.2+((Fiyat->YuzmeT+Fiyat->TenisT)*9)*0.05);
                    }
                    else if(bolum == 5)

                    {
                        fiyat=((Fiyat->FitnessT+Fiyat->TenisT)*9)-(((Fiyat->FitnessT+Fiyat->TenisT)*9)*0.2+((Fiyat->FitnessT+Fiyat->TenisT)*9)*0.05);
                    }
                    else if(bolum == 4)
                    {
                        fiyat=((Fiyat->FitnessT+Fiyat->YuzmeT)*9)-(((Fiyat->FitnessT+Fiyat->YuzmeT)*9)*0.2+((Fiyat->FitnessT+Fiyat->YuzmeT)*9)*0.05);
                    }
                    else if(bolum == 3)
                    {
                        fiyat=((Fiyat->TenisT)*9)-(((Fiyat->TenisT)*9)*0.2+((Fiyat->TenisT)*9)*0.05);
                    }
                    else if(bolum == 2)
                    {
                        fiyat=((Fiyat->FitnessT)*9)-(((Fiyat->FitnessT)*9)*0.2+((Fiyat->FitnessT)*9)*0.05);
                    }
                    else
                    {
                        fiyat=((Fiyat->YuzmeT)*9)-(((Fiyat->YuzmeT)*9)*0.2+((Fiyat->YuzmeT)*9)*0.05);
                    }
                }
            }
            else//yeni
            {
                if(bolum == 7)//bolum sayisi 3 ise yani tum bolumleri aliyorsa
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*9)-(((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*9)*0.2+((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*9)*0.03);

                }
                else  if(bolum == 6)
                {
                    fiyat=((Fiyat->YuzmeP+Fiyat->TenisP)*9)-(((Fiyat->YuzmeP+Fiyat->TenisP)*9)*0.2);
                }
                else if(bolum == 5)
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->TenisP)*9)-(((Fiyat->FitnessP+Fiyat->TenisP)*9)*0.2);
                }
                else if(bolum == 4)
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->YuzmeP)*9)-(((Fiyat->FitnessP+Fiyat->YuzmeP)*9)*0.2);
                }
                else if(bolum == 3)
                {
                    fiyat=((Fiyat->TenisP)*9)-(((Fiyat->TenisP)*9)*0.2);
                }
                else if(bolum == 2)
                {
                    fiyat=((Fiyat->FitnessP)*9)-(((Fiyat->FitnessP)*9)*0.2);
                }
                else
                {
                    fiyat=((Fiyat->YuzmeP)*9)-(((Fiyat->YuzmeP)*9)*0.2);
                }
            }
        }
        else //sivil
        {
            if(yas >= 65)
            {
                if(bolum == 7)//bolum sayisi 3 ise yani tum bolumleri aliyorsa
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*9)-(((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*9)*0.03+((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*9)*0.1);
                }
                else  if(bolum == 6)
                {
                    fiyat=((Fiyat->YuzmeP+Fiyat->TenisP)*9)-(((Fiyat->YuzmeP+Fiyat->TenisP)*9)*0.1);
                }
                else if(bolum == 5)
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->TenisP)*9)-(((Fiyat->FitnessP+Fiyat->TenisP)*9)*0.1);
                }
                else if(bolum == 4)
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->YuzmeP)*9)-(((Fiyat->FitnessP+Fiyat->YuzmeP)*9)*0.1);
                }
                else if(bolum == 3)
                {
                    fiyat=((Fiyat->TenisP)*9)-(((Fiyat->TenisP)*9)*0.1);
                }
                else if(bolum == 2)
                {
                    fiyat=((Fiyat->FitnessP)*9)-(((Fiyat->FitnessP)*9)*0.1);
                }
                       else
                {
                    fiyat=((Fiyat->YuzmeP)*9)-(((Fiyat->YuzmeP)*9)*0.1);
                }
            }
            else
            {
                if(bolum == 7)//bolum sayisi 3 ise yani tum bolumleri aliyorsa
                {
                    fiyat=((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*4)-(((Fiyat->FitnessP+Fiyat->TenisP+Fiyat->YuzmeP)*4)*0.03);
                }
                else  if(bolum == 6)
                {
                    fiyat=(Fiyat->YuzmeP+Fiyat->TenisP)*4;
                }
                else if(bolum == 5)
                {
                    fiyat=(Fiyat->FitnessP+Fiyat->TenisP)*4;
                }
                else if(bolum == 4)
                {
                    fiyat=(Fiyat->FitnessP+Fiyat->YuzmeP)*4;
                }
                else if(bolum == 3)
                {
                    fiyat=(Fiyat->TenisP)*4;
                }
                else if(bolum == 2)
                {
                    fiyat=(Fiyat->FitnessP)*4;
                }
                else
                {
                    fiyat=(Fiyat->YuzmeP)*4;
                }
            }

        }
        break;
    default:
        printf("Yanlis secim!");
    }
    return fiyat;
}
void Ekle()
{
    FILE *dosya;
    dosya=fopen("uyeler1628.txt","r");
    if(dosya==NULL)
    {
        printf("Dosya okumak icin okunamadi...");
        return ;
    }
    while(!feof(dosya))
    {
        gecici=(Uye*)malloc(sizeof(Uye));
        gecici->bolum=(Bolum*)malloc(sizeof(Bolum));
        fscanf(dosya,"%s %s %s %s %d %s %s %d %d %s %d",gecici->uye_id,gecici->uye_adi,gecici->uye_soyadi,gecici->uye_kampanya,&gecici->uye_yas,gecici->uye_durum,gecici->uye_odeme,&gecici->bsayisi,&gecici->bolum->bolum_id,gecici->bolum->bolum_ismi,&gecici->uye_ucret);
        if(ilk==NULL)
        {
            ilk=gecici;
            son=gecici;
            son->sonraki=NULL;
        }
        else
        {
            son->sonraki=gecici;
            son=gecici;
            son->sonraki=NULL;
        }
    }
    fclose(dosya);
}
void Listeleme()
{
    gecici=ilk;
    while(gecici->sonraki!=NULL)
    {
        printf("%s %s %s %s %d %s %s %d %d %s %d\n",gecici->uye_id,gecici->uye_adi,gecici->uye_soyadi,gecici->uye_kampanya,gecici->uye_yas,gecici->uye_durum,gecici->uye_odeme,gecici->bsayisi,gecici->bolum->bolum_id,gecici->bolum->bolum_ismi,gecici->uye_ucret);
        gecici=gecici->sonraki;
    }
}
void Silme()
{
    system("cls");
    printf("\n\n");
    int sec;
    printf("Uye Idye Gore Silme ------------------>1\n");
    printf("Uye Adina Gore Silme ----------------->2\n");
    printf("Silmek istediginiz bolum:");
    scanf("%d",&sec);
    switch(sec)
    {
    case 1:
        IdGoreSilme();
        break;
    case 2:
        AdaGoreSilme();
        break;
    default:
        printf("Yanlis secim yaptiniz!");
        break;
    }
}
void IdGoreSilme()
{
    system("cls");
    char id[20];
    printf("Slinecek uyenin idsi:");
    scanf("%s",id);
    onceki=NULL;
    gecici=ilk;
    while(gecici !=NULL)
    {
        if(strcmp(gecici->uye_id,id) == 0)
            break;
        onceki=gecici;
        gecici=gecici->sonraki;
    }
    if(gecici!=NULL)
    {
        if(onceki == NULL)
        {
            if(ilk==son)
            {
                ilk=NULL;
                son=NULL;
            }
            else
                ilk=ilk->sonraki;
        }
        else
        {
            onceki->sonraki=gecici->sonraki;
            if(onceki->sonraki ==NULL)
                son=onceki;
        }
        free(gecici);
    }
    else
    {
        printf("Silmek istediginiz uye listede yok!\n");
        return ;
    }
    printf("Kayit silindi.");
}
void AdaGoreSilme()
{
    system("cls");
    char ad[20];
    printf("Silinecek uyenin adi:");
    scanf("%s",&ad);
    Uye*onceki;
    onceki=NULL;
    gecici=ilk;
    while(gecici !=NULL)
    {
        if(strcmp(gecici->uye_adi,ad) == 0)
            break;
        onceki=gecici;
        gecici=gecici->sonraki;
    }
    if(gecici!=NULL)
    {
        if(onceki == NULL)
        {
            if(ilk==son)
            {
                ilk=NULL;
                son=NULL;
            }
            else
                ilk=ilk->sonraki;
        }
        else
        {
            onceki->sonraki=gecici->sonraki;
            if(onceki->sonraki ==NULL)
                son=onceki;
        }
        free(gecici);
    }
    else
    {
        printf("Silmek istediginiz uye listede yok!\n");
        return ;
    }
    printf("Kayit silindi.");
}
void Arama()
{
    system("cls");
    int sec;
    printf("Uye idye Gore Arama ---------------->1\n");
    printf("Ada Gore Arama --------------------->2\n");
    printf("Soyada Gore Arama ------------------>3\n");
    printf("Spor Bolum idye Gore Arama --------->4\n");
    printf("Odeme Turune Gore Arama ------------>5\n");
    printf("Duruma Gore Arama ------------------>6\n");
    printf("Arama yapmak istediginiz bolum:\n");
    scanf("%d",&sec);
    switch(sec)
    {
    case 1:
        IdyeGoreArama();
        break;
    case 2:
        AdaGoreArama();
        break;
    case 3:
        SoyadaGoreArama();
        break;
    case 4:
        SporIdGoreArama();
        break;
    case 5:
        OdemeGoreArama();
        break;
    case 6:
        DurumGoreArama();
        break;
    default:
        printf("Yanlis secim yaptiniz!");
        return;
    }
}
void IdyeGoreArama()
{
    system("cls");
    char id[20];
    printf("\nAranacak id:");
    scanf("%s",&id);

    for(gecici=ilk; gecici!=NULL; gecici=gecici->sonraki)
    {
        if(strcmp(gecici->uye_id,id)==0)
        {
            printf("\n  Aranan Uye   \n");
            printf("%s %s %s %s %d %s %s %d %d\n",gecici->uye_id,gecici->uye_adi,gecici->uye_soyadi,gecici->uye_kampanya,gecici->uye_yas,gecici->uye_durum,gecici->uye_odeme,gecici->bsayisi,gecici->bolum->bolum_id);
        }
    }
}
void AdaGoreArama()
{
    system("cls");
    char ad[20];
    printf("\nAranacak ad:");
    scanf("%s",&ad);

    for(gecici=ilk; gecici!=NULL; gecici=gecici->sonraki)
    {
        if(strcmp(gecici->uye_adi,ad)==0)
        {
            printf("\n  Aranan Uye  \n");
            printf("%s %s %s %s %d %s %s %d %d\n",gecici->uye_id,gecici->uye_adi,gecici->uye_soyadi,gecici->uye_kampanya,gecici->uye_yas,gecici->uye_durum,gecici->uye_odeme,gecici->bsayisi,gecici->bolum->bolum_id);
        }
    }
}
void SoyadaGoreArama()
{
    system("cls");
    char soyad[20];
    printf("\nAranacak soyad:");
    scanf("%s",&soyad);

    for(gecici=ilk; gecici!=NULL; gecici=gecici->sonraki)
    {
        if(strcmp(gecici->uye_soyadi,soyad)==0)
        {
            printf("\n  Aranan Uye   \n");
            printf("%s %s %s %s %d %s %s %d %d\n",gecici->uye_id,gecici->uye_adi,gecici->uye_soyadi,gecici->uye_kampanya,gecici->uye_yas,gecici->uye_durum,gecici->uye_odeme,gecici->bsayisi,gecici->bolum->bolum_id);
        }
    }
}
void SporIdGoreArama()
{
    system("cls");
    int id;
    printf("\nAranacak bolum id:");
    scanf("%d",&id);

    for(gecici=ilk; gecici!=NULL; gecici=gecici->sonraki)
    {
        if(gecici->bolum->bolum_id == id)
        {
            printf("\n  Aranan Uye   \n");
            printf("%s %s %s %s %d %s %s %d %d %s %d\n",gecici->uye_id,gecici->uye_adi,gecici->uye_soyadi,gecici->uye_kampanya,gecici->uye_yas,gecici->uye_durum,gecici->uye_odeme,gecici->bsayisi,gecici->bolum->bolum_id,gecici->bolum->bolum_ismi,gecici->uye_ucret);
        }
    }
}
void OdemeGoreArama()
{
    system("cls");
    char odeme;
    printf("\nOdeme turu pesin veya taksit(P/T):");
    scanf(" %c",&odeme);
    gecici=ilk;
    if(odeme == 'P' || odeme == 'p'  || odeme == 'T'|| odeme == 't')
    {
        while(gecici != NULL)
        {
            char *temp = gecici->uye_odeme;
            if(*temp == odeme)
            {
                printf("\n  Aranan Uye  \n");
                printf("%s %s %s %s %d %s %s %d %d %s %d\n",gecici->uye_id,gecici->uye_adi,gecici->uye_soyadi,gecici->uye_kampanya,gecici->uye_yas,gecici->uye_durum,gecici->uye_odeme,gecici->bsayisi,gecici->bolum->bolum_id,gecici->bolum->bolum_ismi,gecici->uye_ucret);
            }
            gecici=gecici->sonraki;
        }
    }
}
void DurumGoreArama()
{
    system("cls");
    char durum;
    printf("\nDurum ogrenci veya sivil : ");
    scanf(" %c",&durum);
    if(durum == 'O' || durum == 'o' || durum == 'S' || durum == 's' )
    {
        for(gecici=ilk; gecici!=NULL; gecici=gecici->sonraki)
        {
            char *temp=gecici->uye_durum;
            if(*temp == durum)
            {
                printf("\n  Aranan Uye   \n");
                printf("%s %s %s %s %d %s %s %d %d\n",gecici->uye_id,gecici->uye_adi,gecici->uye_soyadi,gecici->uye_kampanya,gecici->uye_yas,gecici->uye_durum,gecici->uye_odeme,gecici->bsayisi,gecici->bolum->bolum_id);
            }
        }
    }
}
void Guncelleme()
{
    system("cls");
    int sec;
    char id[20],ad[20],soyad[20];
    printf("Guncelleme yapmak istedigiz uyenin idsini giriniz:");
    scanf("%s",&id);
    gecici=ilk;

  while(gecici != NULL)
  {
      char *temp=gecici->uye_id;

        if(*temp == *id)
        {
            while(1)
            {
                printf("Uye id -------------->1\n");
                printf("Uye adi ------------->2\n");
                printf("Uye soyadi ---------->3\n");
                printf("Cikmak icin---------->4\n");
                printf("Hangisini degistirmek istiyorsun:");
                scanf("%d",&sec);
                if(sec == 1)
                {
                    printf("Uye idyi girin:");
                    scanf("%s",gecici->uye_id);
                }
                else if(sec == 2)
                {
                    printf("Uye adini girin:");
                    scanf("%s",gecici->uye_adi);
                }
                else if(sec == 3)
                {
                    printf("Uye soyadini girin:");
                    scanf("%s",gecici->uye_soyadi);
                }
                else
                {
                    printf("Yanlis secim!");
                    return;
                }
                DosyayaYaz();

            }
        }
        else
        {
            printf("Guncellemek istediginiz id yoktur!");
            //return;
        }
        gecici=gecici->sonraki;
    }
}
void DosyayaYaz()
{
    FILE *dosya=fopen("uyeler1628.txt","w");
    if(dosya==NULL)
    {
        printf("Dosya okunmadi.");
        return ;
    }
    gecici=ilk;
    while(gecici != NULL)
    {
        fprintf(dosya,"%s %s %s %s %d %s %s %d %d %s %d\n",gecici->uye_id,gecici->uye_adi,gecici->uye_soyadi,gecici->uye_kampanya,gecici->uye_yas,gecici->uye_durum,gecici->uye_odeme,gecici->bsayisi,gecici->bolum->bolum_id,gecici->bolum->bolum_ismi,gecici->uye_ucret);
        gecici=gecici->sonraki;
    }
    fclose(dosya);

}
void FiyatGuncelle()
{
    int sec,secim;
    printf("%d %d %d %d %d %d\n",Fiyat->YuzmeP,Fiyat->YuzmeT,Fiyat->FitnessP,Fiyat->FitnessT,Fiyat->TenisP,Fiyat->TenisT);
    printf("Nakit --------------->1\n");
    printf("Taksit -------------->2\n");
    printf("Hangisini degistirmek istiyorsunuz:");
    scanf("%d",&sec);
    if(sec == 1)
    {
        printf("Yuzme -------------->1\n");
        printf("Fitness ------------>2\n");
        printf("Tenis -------------->3\n");
        printf("Hangisi:");
        scanf("%d",&secim);
        if(secim == 1)
        {
            printf("Yuzmenin yeni fiyati:");
            scanf("%d",&Fiyat->YuzmeP);
        }
        if(secim == 2)
        {
            printf("Fitness yeni fiyati:");
            scanf("%d",&Fiyat->FitnessP);
        }
        if(secim == 3)
        {
            printf("Tenisin yeni fiyati:");
            scanf("%d",&Fiyat->TenisP);
        }
    }
    else if(sec == 2)
    {
        printf("Yuzme ------------>1\n");
        printf("Fitness----------->2\n");
        printf("Tenis ------------>3\n");
        printf("Hangisi:");
        scanf("%d",&secim);
        if(secim == 1)
        {
            printf("Yuzmenin yeni fiyati:");
            scanf("%d",&Fiyat->YuzmeT);
        }
        if(secim == 2)
        {
            printf("Fitness yeni fiyati:");
            scanf("%d",&Fiyat->FitnessT);
        }
        if(secim == 3)
        {
            printf("Tenisin yeni fiyati:");
            scanf("%d",&Fiyat->TenisT);
        }
    }
    else
    {
        printf("Yanlis secim!");
        return;
    }
    printf("%d %d %d %d %d %d\n",Fiyat->YuzmeP,Fiyat->YuzmeT,Fiyat->FitnessP,Fiyat->FitnessT,Fiyat->TenisP,Fiyat->TenisT);
    FILE *Dosya=fopen("fiyatlar1628.txt","r+");
    if(Dosya == NULL)
    {
        printf("Dosya okunmadi.");
        return;
    }
    fprintf(Dosya,"%d %d %d %d %d %d",Fiyat->YuzmeP,Fiyat->YuzmeT,Fiyat->FitnessP,Fiyat->FitnessT,Fiyat->TenisP,Fiyat->TenisT);
    fclose(Dosya);
}
int main()
{
    if(flag==0)
    {
        Ekle();
        flag=1;
    }
    FiyatOku();
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t                   SPOR MERKEZI OTOMASYONUNA HOSGELDINIZ...                   \n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    getchar();
    system("cls");
    int secim;
    while(1)
    {
        printf("\n");
        printf("\t     1_) Ekleme... \n");
        printf("\t     2_) Silme... \n");
        printf("\t     3_) Guncelleme... \n ");
        printf("\t     4_) Listeleme... \n");
        printf("\t     5_) Arama... \n");
        printf("\t     6_) Fiyatlari Guncelleme... \n");
        printf("\t     7_) Cikis... ");
        printf("\n  Yapmak istediginiz islemi seciniz:");
        scanf("%d",&secim);
        system("cls");
        switch(secim)
        {
        case 1:
            DosyayaEkle();
            break;
        case 2:
            Silme();
            break;
        case 3:
            Guncelleme();
            break;
        case 4:
            Listeleme();
            break;
        case 5:
            Arama();
            break;
        case 6:
            FiyatGuncelle();
            break;
        case 7:
            printf("\tProgramdan ciktiniz.\n\t GULE GULE :)");
            return 0;
            break;
        default:
            printf("\nYanlis rakam sectiniz.Lutfen 1-7 arasinda bir rakam seciniz!\n");
        }
    }
    return 0;
}
