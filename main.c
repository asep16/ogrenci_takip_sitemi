#include <stdio.h>
#include <stdlib.h>

#define BOS_KAYIT_KODU -1
#define MAX_KAYIT_SAY 100

struct urun
{
    int urun_kodu;
    char urun_adi[16];
    float birim_fiyati;
    int stok_miktari;
};

typedef struct urun urun_type;

int menu_secim();
void dosya_yarat();
void urun_ekle(FILE *);
void urun_sil(FILE *);
void urun_guncelle(FILE *);
void urun_goruntule(FILE *);
void tumunu_listele(FILE *);
void stoga_gore_listele(FILE *);
void yedekle(FILE *);
void yedekte_urun_goruntule();

int main()
{
    FILE *fptr;
    int secenek;

    if((fptr=fopen("urunler.dat","rb+"))==NULL)
    {
        dosya_yarat();
        if((fptr=fopen("urunler.dat","rb+"))==NULL)
        {
            printf("Urun dosyasi acilamadi.\n");
            return 0;
        }
    }

    do
    {
        secenek=menu_secim();
        switch(secenek)
        {
        case 1:
            urun_ekle(fptr);
            break;
        case 2:
            urun_sil(fptr);
            break;
        case 3:
            urun_guncelle(fptr);
            break;
        case 4:
            urun_goruntule(fptr);
            break;
        case 5:
            tumunu_listele(fptr);
            break;
        case 6:
            stoga_gore_listele(fptr);
            break;
        case 7:
            yedekle(fptr);
            break;
        case 8:
            yedekte_urun_goruntule();
            break;
        }
    }
    while(secenek!=9);

    return 0;
}

int menu_secim(void)
{
    int secim;

    printf("\n");
    printf("            1. Yeni Urun Ekleme\n");
    printf("            2. Urun Silme\n");
    printf("            3. Urun Guncelleme\n");
    printf("            4. Bir Urunu Goruntuleme\n");
    printf("            5. Tum Urunleri Goruntuleme\n");
    printf("            6. Stok Miktari Azalan Urunleri Goruntuleme\n");
    printf("            7. Urun Dosyasini Yedekleme\n");
    printf("            8. Yedek Dosyasinda Bir Urunu Goruntuleme\n");
    printf("            9. Cikis\n");
    printf("\n");
    do
    {
        printf("\nSeciminizi Giriniz:");
        scanf("%d", &secim);
    }
    while(secim<1 || secim>9);

    return secim;
}

void dosya_yarat()
{
    FILE *fptr;
    urun_type bos_kayit;
    int i;

    bos_kayit.urun_kodu=BOS_KAYIT_KODU;

    if((fptr=fopen("urunler.dat","wb"))==NULL)
        printf("Bos kayitlar iceren dosya yaratilamadi.\n");
    else
    {
        for(i=1; i<=MAX_KAYIT_SAY; i++)
            fwrite(&bos_kayit,sizeof(urun_type),1,fptr);
        fclose(fptr);
    }

    return;
}

void urun_ekle(FILE *fptr)
{
    urun_type bir_urun;
    int kod;
    int kayit_no;

    printf("Eklemek istediginiz yeni urunun kodunu giriniz:");
    scanf("%d",&kod);

    kayit_no=kod-100;

    fseek(fptr,(kayit_no-1)*sizeof(urun_type),SEEK_SET);
    fread(&bir_urun,sizeof(urun_type),1,fptr);
    if(bir_urun.urun_kodu==BOS_KAYIT_KODU)
    {
        bir_urun.urun_kodu=kod;
        printf("Urun adini giriniz:");
        fflush(stdin);
        gets(bir_urun.urun_adi);
        printf("Urunun birim fiyatini giriniz:");
        scanf("%f",&bir_urun.birim_fiyati);
        printf("Urunun stok miktarini giriniz:");
        scanf("%d",&bir_urun.stok_miktari);

        fseek(fptr,(kayit_no-1)*sizeof(urun_type),SEEK_SET);
        fwrite(&bir_urun,sizeof(urun_type),1,fptr);
        printf("Ekleme islemi basari ile gerceklestirildi.\n");
    }
    else
        printf("Girdiginiz kod numarasina sahip urun bulunmaktadir.\n");

    return;
}

void urun_sil(FILE *fptr)
{
    urun_type bir_urun;
    int kod;
    int kayit_no;

    printf("Silmek istediginiz urunun kodunu giriniz:");
    scanf("%d",&kod);

    kayit_no=kod-100;

    fseek(fptr,(kayit_no-1)*sizeof(urun_type),SEEK_SET);
    fread(&bir_urun,sizeof(urun_type),1,fptr);
    if(bir_urun.urun_kodu==BOS_KAYIT_KODU)
        printf("Girdiginiz kod numarasina sahip urun bulunmamaktadir.\n");
    else
    {
        bir_urun.urun_kodu=BOS_KAYIT_KODU;
        fseek(fptr,(kayit_no-1)*sizeof(urun_type),SEEK_SET);
        fwrite(&bir_urun,sizeof(urun_type),1,fptr);
        printf("Silme islemi basari ile gerceklestirildi.\n");
    }

    return;
}

void urun_guncelle(FILE *fptr)
{
    urun_type bir_urun;
    int kod;
    int kayit_no;

    printf("Guncellemek istediginiz urunun kodunu giriniz:");
    scanf("%d",&kod);

    kayit_no=kod-100;

    fseek(fptr,(kayit_no-1)*sizeof(urun_type),SEEK_SET);
    fread(&bir_urun,sizeof(urun_type),1,fptr);
    if(bir_urun.urun_kodu==BOS_KAYIT_KODU)
        printf("Girdiginiz kod numarasina sahip urun bulunmamaktadir.\n");
    else
    {
        printf("Urunun yeni birim fiyatini giriniz:");
        scanf("%f",&bir_urun.birim_fiyati);
        printf("Urunun yeni stok miktarini giriniz:");
        scanf("%d",&bir_urun.stok_miktari);

        fseek(fptr,(kayit_no-1)*sizeof(urun_type),SEEK_SET);
        fwrite(&bir_urun,sizeof(urun_type),1,fptr);
        printf("Guncelleme islemi basari ile gerceklestirildi.\n");
    }

    return;
}

void urun_goruntule(FILE *fptr)
{
    urun_type bir_urun;
    int kod;
    int kayit_no;

    printf("Goruntulemek istediginiz urunun kodunu giriniz:");
    scanf("%d",&kod);

    kayit_no=kod-100;

    fseek(fptr,(kayit_no-1)*sizeof(urun_type),SEEK_SET);
    fread(&bir_urun,sizeof(urun_type),1,fptr);
    if(bir_urun.urun_kodu==BOS_KAYIT_KODU)
        printf("Girdiginiz kod numarasina sahip urun bulunmamaktadir.\n");
    else
    {
        printf("Kodu Adi             Birim Fiyati Stok Miktari\n");
        printf("---- --------------- ------------ ------------\n");
        printf("%d  %-15s %-12.2f %d\n",bir_urun.urun_kodu,bir_urun.urun_adi,bir_urun.birim_fiyati,bir_urun.stok_miktari);
    }

    return;
}

void tumunu_listele(FILE *fptr)
{
    urun_type bir_urun;
    int i;

    rewind(fptr);
    printf("Kodu Adi             Birim Fiyati Stok Miktari\n");
    printf("---- --------------- ------------ ------------\n");

    for(i=1; i<=MAX_KAYIT_SAY; i++)
    {
        fread(&bir_urun,sizeof(urun_type),1,fptr);

        if(bir_urun.urun_kodu!=BOS_KAYIT_KODU)
            printf("%d  %-15s %-12.2f %d\n",bir_urun.urun_kodu,bir_urun.urun_adi,bir_urun.birim_fiyati,bir_urun.stok_miktari);
    }

    return;
}

void stoga_gore_listele(FILE *fptr)
{
    int stok_siniri,i;
    urun_type bir_urun;

    printf("Stok miktari icin sinir degerini giriniz:");
    scanf("%d",&stok_siniri);

    rewind(fptr);
    printf("Kodu Adi             Birim Fiyati Stok Miktari\n");
    printf("---- --------------- ------------ ------------\n");

    for(i=1; i<=MAX_KAYIT_SAY; i++)
    {
        fread(&bir_urun,sizeof(urun_type),1,fptr);

        if(bir_urun.urun_kodu!=BOS_KAYIT_KODU)
            if(bir_urun.stok_miktari<stok_siniri)
                printf("%d  %-15s %-12.2f %d\n",bir_urun.urun_kodu,bir_urun.urun_adi,bir_urun.birim_fiyati,bir_urun.stok_miktari);
    }

    return;
}

void yedekle(FILE *fptr)
{
    FILE *yptr;
    int i;
    urun_type bir_urun;
    if ((yptr=fopen("urunler_yedek.dat","wb"))==NULL)
    {
        printf("Yedek dosya acilamadi.");
    }
    else
    {
        rewind(fptr);
        for (i=1; i<=MAX_KAYIT_SAY; i++)
        {
            fread(&bir_urun,sizeof(urun_type),1,fptr);
            if (bir_urun.urun_kodu != BOS_KAYIT_KODU)
            {
                fwrite(&bir_urun,sizeof(urun_type),1,yptr);
            }
        }
        fclose(yptr);
    }

}

void yedekte_urun_goruntule()
{
    FILE *yptr;
    urun_type bir_urun;
    int kodu,ilk_kayit_no,son_kayit_no,orta_kayit_no,bulundu;
    if ((yptr=fopen("urunler_yedek.dat","rb"))==NULL)
    {
        printf("Yedek dosya acilamadi.");
    }
    else
    {
        printf("Goruntulemek istediginiz urun kodunu giriniz : ");
        scanf("%d",&kodu);
        ilk_kayit_no = 1;
        fseek(yptr,0,SEEK_END);
        son_kayit_no = ftell(yptr)/sizeof(urun_type);
        bulundu=0;
        while ((ilk_kayit_no <= son_kayit_no) && (bulundu ==0))
        {
            orta_kayit_no = (ilk_kayit_no+son_kayit_no)/2;
            fseek(yptr,(orta_kayit_no-1)*sizeof(urun_type),SEEK_SET);
            fread(&bir_urun,sizeof(urun_type),1,yptr);
            if (kodu < bir_urun.urun_kodu)
            {
                son_kayit_no=orta_kayit_no;
            }
            else
            {
                if (kodu > bir_urun.urun_kodu)
                {
                    ilk_kayit_no = orta_kayit_no;
                }
                else
                    bulundu=1;
            }
        }

        if (bulundu == 0)
        {
            printf("Girdiniz kod numarasina sahip urun bulunmamaktadir.");
        }
        else
        {
            printf("Kodu Adi             Birim Fiyati Stok Miktari\n");
            printf("---- --------------- ------------ ------------\n");
            printf("%d  %-15s %-12.2f %d\n",bir_urun.urun_kodu,bir_urun.urun_adi,bir_urun.birim_fiyati,bir_urun.stok_miktari);
        }


    }

}
