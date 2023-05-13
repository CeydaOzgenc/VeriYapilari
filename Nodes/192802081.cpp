#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>
using namespace std;
struct ders{ 
	char derskodu[10]; 
	char dersadi[50]; 
	ders *sonraki; 
};
struct ogrenci{ 
	char ogrno[15]; 
	char ad[30] ; 
	char soyad[30]; 
	ders *dersdugumu; 
	ogrenci *sonraki; 
}; 
#ifndef LISTE_H
#define LISTE_H
struct  Liste
{
	ogrenci *bas;
	FILE *dosya;
	int ogrencisayisi;
	ogrenci *dugum_olustur(char *,char *,char *,char*,char*);
	void olustur();
	void listeKur();
	void ekle(char *,char *,char *,char *,char *);
	void dersSil();
	void ogrenciSil(int ogrenci_no);
	void listele();
	void ara();
	void kesisimBul();
	void dosyaYaz();

};
#endif
void Liste::olustur(){
	bas=NULL;
	ogrencisayisi=0;
	listeKur();
};
ogrenci * Liste::dugum_olustur(char *yeni_ogrno,char *yeni_ad,char *yeni_soyad,char *yeni_derskodu,char *yeni_dersadi){
	ogrenci *yeni_ogrenci;
	ders *yeni_ders;
	yeni_ogrenci=new ogrenci;
	strcpy(yeni_ogrenci->ogrno,yeni_ogrno);
	strcpy(yeni_ogrenci->ad,yeni_ad);
	strcpy(yeni_ogrenci->soyad,yeni_soyad);
	yeni_ders=new ders;
	yeni_ogrenci->dersdugumu=yeni_ders;
	strcpy(yeni_ders->derskodu,yeni_derskodu);
	strcpy(yeni_ders->dersadi,yeni_dersadi);
	//cout<<yeni_ogrenci->ogrno<<"-"<<yeni_ogrenci->ad<<"-"<<yeni_ogrenci->soyad<<"-"<<yeni_ders->derskodu<<"-"<<yeni_ders->dersadi<<endl;
	yeni_ogrenci->sonraki=NULL;
	yeni_ders->sonraki=NULL;
	return yeni_ogrenci;
}
void Liste::ekle(char *yeni_ogrno,char *yeni_ad,char *yeni_soyad,char *yeni_derskodu,char *yeni_dersadi){
	ogrenci *tara, *arka, *yeni_ogrenci;
	ders *yeni_ders;
	tara=bas;
	if(bas== NULL){
		bas = dugum_olustur(yeni_ogrno,yeni_ad,yeni_soyad,yeni_derskodu,yeni_dersadi);
		ogrencisayisi++;
		return;
	}
	if(atoi(yeni_ogrno) < atoi(bas->ogrno)){
		yeni_ogrenci = dugum_olustur(yeni_ogrno,yeni_ad,yeni_soyad,yeni_derskodu,yeni_dersadi);
		yeni_ogrenci->sonraki=bas;
		bas = yeni_ogrenci;
		ogrencisayisi++;
		return;
	}
	while(tara && atoi(yeni_ogrno) > atoi(tara->ogrno)){
		arka = tara;
		tara=tara->sonraki;
	}
	if((tara!=NULL) && atoi(yeni_ogrno) == atoi(tara->ogrno)){
		yeni_ders=new ders;
		yeni_ders->sonraki=tara->dersdugumu;
		tara->dersdugumu=yeni_ders;
		strcpy(yeni_ders->derskodu,yeni_derskodu);
		strcpy(yeni_ders->dersadi,yeni_dersadi);
	}
	else{
		yeni_ogrenci=dugum_olustur(yeni_ogrno,yeni_ad,yeni_soyad,yeni_derskodu,yeni_dersadi);
		if(tara){
			yeni_ogrenci->sonraki=tara;
			arka->sonraki=yeni_ogrenci;
		}
		else{
			arka->sonraki=yeni_ogrenci;
		}
		ogrencisayisi++;
	}
}
void Liste::listele(){
	ogrenci *tara;
	ders *ders_bilgi;
	tara=bas;
	while(tara){
		cout<<tara->ogrno<<" "<<tara->ad<<" "<<tara->soyad<<" ";
		ders_bilgi=tara->dersdugumu;
		while(ders_bilgi){
			cout<<ders_bilgi->derskodu<<" "<<ders_bilgi->dersadi<<" ";
			ders_bilgi=ders_bilgi->sonraki;
		}
		cout<<endl;
		tara=tara->sonraki;
	}
}
void Liste::listeKur(){
	ifstream dosya[3];
	string dosyaad[3]={"mat101.txt","fiz101.txt","eng101.txt"};
	for (int i = 0; i < 3; i++)
	{
		string line,ders_no,ders_ad;
		int sayac=0;
		dosya[i].open(dosyaad[i], ios::in);
		while(getline(dosya[i],line)){
			int say=0;
			string kelime = "",ogr_no,ogr_ad,ogr_soyad;
    		for (auto x : line) 
    		{
        		if (x == ' ')
        		{
        			say++;
        			if(sayac!=0){
        				if(say==1){
        					ogr_no=kelime;
        				}
        				else if(say==2){
        					ogr_ad=kelime;
        				}
        				else if(say==3){
        					ogr_soyad=kelime;
        				}
        				else if(say==4){
        					ogr_ad= ogr_ad+" "+ogr_soyad;
        					ogr_soyad=kelime;
        				}
        				else{
        					ogr_ad= ogr_ad+" "+ogr_soyad;
        					ogr_soyad=kelime;
        				}
        			}
        			else{
        				if(say==1){ders_no=kelime;}
        				else{ders_ad=kelime;}
        			}
            		kelime = "";
       	 		}
       			else {
            		kelime = kelime + x;
        		}
    		}
    		if(sayac=!0){
    			char dersno[6],ogrencino[8],ograd[50],ogrsoyad[30],dersad[15];
    			if(""!=ogr_no){
    				strcpy(ograd, ogr_ad.c_str());
    				strcpy(ogrsoyad, ogr_soyad.c_str());
    				strcpy(ogrencino, ogr_no.c_str());
    				strcpy(dersno, ders_no.c_str());
    				strcpy(dersad, ders_ad.c_str());
    				ekle(ogrencino,ograd,ogrsoyad,dersno,dersad);
    			}
    		}

			sayac++;
		}
	}
}
void Liste::dosyaYaz(){
	ogrenci *tara;
	ders *ders_bilgi;
	tara=bas;
	ofstream myfile; 
  	myfile.open ("ceydaozgenc.txt");
	while(tara){
		myfile << tara->ogrno <<" "<< tara->ad <<" "<< tara->soyad <<" ";
		ders_bilgi=tara->dersdugumu;
		while(ders_bilgi){
			myfile << ders_bilgi->derskodu <<" "<< ders_bilgi->dersadi <<" ";
			ders_bilgi=ders_bilgi->sonraki;
		}
		myfile <<"\n";
		tara=tara->sonraki;
	}
	myfile.close();
}
typedef Liste Veriyapisi;
Veriyapisi veri;
bool secim_yap(char secim){
	bool sonlandir=false;
	int ogr_no;
	switch (secim) {
  		case 'A': case 'a': 
  			veri.ara();
    		break;
  		case 'L': case 'l':
  			veri.listele();
    		break;
  		case 'O': case 'o':
  			cout<<"Silinecek ogrenci numarasini giriniz: ";
  			cin>>ogr_no;
  		 	veri.ogrenciSil(ogr_no);
    		break;
  		case 'Y': case 'y':
  			veri.dosyaYaz();
    		break;
    	case 'K': case 'k':
  			veri.kesisimBul();
    		break;
    	case 'D': case 'd':
  			veri.dersSil();
    		break;
  		case 'C': case 'c':
    		cout << "Programi sonlandimak istediginize emin misiniz? (E/H):";
    		cin>>secim;
    		if(secim=='E' || secim=='e'){
    			sonlandir=true;
    		}
    		else if(secim!='H' || secim!='h'){
    			cout<<"Hata: Yanlis giris yaptiniz!!"<<endl;
    			secim_yap('C');
    		}
    		break;
    	default:
    		cout<<"Hata: Yanlis giris yaptiniz!!"<<endl;
    		cout<<"Tekrar deneyiniz {A,D,K,L,O,Y,C}"<<endl;
    		cin>>secim;
    		secim_yap(secim);
    		break; 
	}
	return sonlandir;
}
void Liste::kesisimBul(){
	ogrenci *tara;
	ders *ders_bilgi;
	char k1_dersno[50],k2_dersno[50];
	cout<<"1. Ders kodunu giriniz: ";
	cin>>k1_dersno;
	cout<<"2. Ders kodunu giriniz: ";
	cin>>k2_dersno;
	int say;
	tara=bas;
	while(tara){
		say=0;
		ders_bilgi=tara->dersdugumu;
		while(ders_bilgi){
			if(std::string(ders_bilgi->derskodu)==std::string(k1_dersno)){
				say++;
			}
			if(std::string(ders_bilgi->derskodu)==std::string(k2_dersno)){
				say++;
			}
			ders_bilgi=ders_bilgi->sonraki;
		}
		if (say==2)
		{
			cout<<tara->ogrno<<" "<<tara->ad<<" "<<tara->soyad<<" ";
			while(ders_bilgi){
			cout<<ders_bilgi->derskodu<<" "<<ders_bilgi->dersadi<<" ";
			ders_bilgi=ders_bilgi->sonraki;
			}
			cout<<endl;
		}
		tara=tara->sonraki;
	}
}
void Liste::ogrenciSil(int ogrenci_no){
	ogrenci *tara, *arka;
	ders *pn;
	tara = bas;
	if(ogrenci_no<atoi(bas->ogrno)){
		cout<<"Hata: Gecersiz ogrenci numarasi!!"<<endl;
		secim_yap('O');
		return;
	}
	if(ogrenci_no == atoi(bas->ogrno)){
		bas=bas->sonraki;
		pn=tara->dersdugumu;
		while(pn){
			tara->dersdugumu=pn->sonraki;
			delete pn;
			pn=tara->dersdugumu;
		}
		delete tara;
		ogrencisayisi--;
		return;
	}
	while(tara && atoi(tara->ogrno)<ogrenci_no){
		arka = tara;
		tara=tara->sonraki;
	}
	if(tara==NULL){
		cout<<"Hata: Gecersiz ogrenci numarasi!!"<<endl;
		secim_yap('O');
	}
	else{
		arka->sonraki=tara->sonraki;
		pn=tara->dersdugumu;
		while(pn){
			tara->dersdugumu=pn->sonraki;
			delete pn;
			pn=tara->dersdugumu;
		}
		delete tara;
		ogrencisayisi--;
	}
}
void Liste::dersSil(){
	ogrenci *tara;
	ders *pn,*pnarka;
	tara = bas;
	char ders_kodu[10];
	int ogrenci_no,say;
	cout<<"Ogrenci numarasini giriniz: ";
  	cin>>ogrenci_no;
  	cout<<"Silinecek ders kodunu giriniz: ";
  	cin>>ders_kodu;
	if(ogrenci_no<atoi(bas->ogrno)){
		cout<<"Hata: Gecersiz ogrenci numarasi!!"<<endl;
		veri.dersSil();
		return;
	}
	while(tara && atoi(tara->ogrno)<ogrenci_no){
		tara=tara->sonraki;
	}
	if(tara==NULL){
		cout<<"Hata: Gecersiz ogrenci numarasi!!"<<endl;
		veri.dersSil();
	}
	else{
		say=0;
		pn=tara->dersdugumu;
		while(pn && std::string(pn->derskodu) != std::string(ders_kodu)){
			pnarka=pn;
			pn= pn->sonraki;
			say++;
		}
		if(pn!=NULL)
		{
			if(say==0){
				pnarka=pn->sonraki;
				tara->dersdugumu=pnarka;
			}
			else{
				pnarka->sonraki=pn->sonraki;
			}
			delete pn;
		}
		else{
			cout<<"Hata: Gecersiz ders kodu numarasi!!"<<endl;
			veri.dersSil();
		}
	}
}
void Liste::ara(){
	ogrenci *tara;
	ders *ders_bilgi;
	tara=bas;
	char secenek[50],secim;
	cout<<"Numaraya gore arama icin: N"<<endl<<"Soyadina gore arama icin: S"<<endl;
  	cout<<"Seciminiz: ";
  	cin>>secim;
    if(secim=='S' || secim=='s'){
    	cout<<"Soyadini giriniz: ";
    	cin>>secenek;
		while(tara){
			if(std::string(tara->soyad) == std::string(secenek)){
				cout<<tara->ogrno<<" "<<tara->ad<<" "<<tara->soyad<<" ";
				ders_bilgi=tara->dersdugumu;
				while(ders_bilgi!=NULL){
					cout<<ders_bilgi->derskodu<<" "<<ders_bilgi->dersadi<<" ";
					ders_bilgi=ders_bilgi->sonraki;
				}
				cout<<endl;
			}
			tara=tara->sonraki;
		} 
    }
    else if(secim=='N' || secim=='n'){
    	cout<<"Numarayi giriniz: ";
    	cin>>secenek;
		while(tara){
			if(atoi(tara->ogrno) == atoi(secenek)){
				cout<<tara->ogrno<<" "<<tara->ad<<" "<<tara->soyad<<" ";
				ders_bilgi=tara->dersdugumu;
				while(ders_bilgi){
					cout<<ders_bilgi->derskodu<<" "<<ders_bilgi->dersadi<<" ";
					ders_bilgi=ders_bilgi->sonraki;
				}
				cout<<endl;
			}
			tara=tara->sonraki;
		}
    }
    else{
    	cout<<"Hata: Yanlis giris yaptiniz!!"<<endl;
    	secim_yap('A');
    }
}
void secim_yazisi(){
	cout<<"			---ISLEM MENUSU---"<<endl;
	cout<<"Yapmak istediginiz islem icin asagidaki durumlardan birini giriniz..."<<endl;
	cout<<"Arama yapmak icin: A"<<endl;
	cout<<"Ders silmek icin: D"<<endl;
	cout<<"Kesisim bulmak icin: K"<<endl;
	cout<<"Listeyi ekrana yazdirmak icin: L"<<endl;
	cout<<"Ogrenci silmek icin: O"<<endl;
	cout<<"Dosyaya yaz: Y"<<endl;
	cout<<"Cikis icin: C"<<endl;
	cout<<"Seciminiz: ";
}
int main(){
	veri.olustur();
	bool bitir=false;
	char secim;
	while(!bitir){
		secim_yazisi();
		cin >> secim;
		bitir=secim_yap(secim);
	}
	return EXIT_SUCCESS;
}