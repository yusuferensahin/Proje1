#include <stdio.h>  // Standart giriş/çıkış işlemleri için kütüphane
#include <stdlib.h> // Sistem çağrıları ve bellek yönetimi için kütüphane
#include <string.h> // String işlemleri için kütüphane
#define MAXPERSONEL 12  // Maksimum personel sayısı

// Personel bilgilerini tutan yapı tanımı
typedef struct {
    char isim[20];       // Personelin adı
    char soyisim[20];    // Personelin soyadı
    double satis;        // Personelin satış miktarı
    double performans;   // Performans değeri
} personel;

// Fonksiyon prototipleri
void ekleDegistir(personel dizi[], int n);   // Performans hesaplama
void alfabetikSiralama(personel dizi[], int n); // Alfabetik sıralama
void siralayarakYazdir(personel dizi[], int n); // Sonuçları dosyaya yazma

int main(void) {
    FILE *dosya;  // Dosya işaretçisi
    personel dizi[MAXPERSONEL]; // Personel bilgilerini tutacak dizi
    int i = 0;  // Personel sayacı
    double enBuyukSatis = 0;  // En büyük satış değerini saklar

    // satis.txt dosyasını okuma modunda aç
    dosya = fopen("satis.txt", "r");
    if (dosya == NULL) {  // Eğer dosya açılamazsa
        printf("Dosya acilamadi!\n");  // Hata mesajı yazdır
        system("pause");   // Kullanıcıdan devam için bir tuşa basmasını bekle
        exit(1);           // Programı hata ile sonlandır
    }

    // satis.txt dosyasını okuyarak diziye aktarma (SOYAD AD SATIS formatında)
    while (fscanf(dosya, "%s %s %lf", dizi[i].soyisim, dizi[i].isim, &dizi[i].satis) == 3) {
        // En büyük satış değerini bul
        if (dizi[i].satis > enBuyukSatis) {
            enBuyukSatis = dizi[i].satis;
        }
        i++;  // Bir sonraki personel için sayacı artır
    }
    fclose(dosya);  // Dosyayı kapat

    // Performans değerlerini hesapla
    ekleDegistir(dizi, i);

    // Personel isimlerine göre alfabetik sıralama
    alfabetikSiralama(dizi, i);

    // Sonuçları prfmns.txt dosyasına yaz
    siralayarakYazdir(dizi, i);

    return 0;  // Program başarıyla tamamlandı
}

// Performans hesaplayan fonksiyon
void ekleDegistir(personel dizi[], int n) {
    double enBuyukSatis = 0;  // En büyük satış değerini saklar

    // En büyük satış değerini bul
    for (int i = 0; i < n; i++) {
        if (dizi[i].satis > enBuyukSatis) {
            enBuyukSatis = dizi[i].satis;
        }
    }

    // Performans değerini hesapla: En büyük satış - Kişinin satışı
    for (int i = 0; i < n; i++) {
        dizi[i].performans = enBuyukSatis - dizi[i].satis;
    }
}

// Alfabetik sıralama yapan fonksiyon
void alfabetikSiralama(personel dizi[], int n) {
    personel temp;  // Geçici değişken (swap için kullanılır)

    // Bubble Sort algoritması ile sıralama
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // İsimlere göre sıralama (strcmp ile karşılaştırma)
            if (strcmp(dizi[j].isim, dizi[j + 1].isim) > 0) {
                // Elemanları yer değiştir
                temp = dizi[j];
                dizi[j] = dizi[j + 1];
                dizi[j + 1] = temp;
            }
        }
    }
}

// Sonuçları prfmns.txt dosyasına yazdıran fonksiyon
void siralayarakYazdir(personel dizi[], int n) {
    // prfmns.txt dosyasını yazma modunda aç
    FILE *dosya = fopen("prfmns.txt", "w");
    printf("Dosya basariyla yazildi");
    if (dosya == NULL) {  // Eğer dosya açılamazsa
        printf("Dosya yazmak icin acilamadi!\n");  // Hata mesajı yazdır
        system("pause");   // Kullanıcıdan devam için bir tuşa basmasını bekle
        exit(1);           // Programı hata ile sonlandır
    }

    // Her personelin bilgilerini dosyaya yaz
    for (int i = 0; i < n; i++) {
        fprintf(dosya, "%s %s %.2lf\n", dizi[i].isim, dizi[i].soyisim, dizi[i].performans);
    }

    fclose(dosya);  // Dosyayı kapat
}
