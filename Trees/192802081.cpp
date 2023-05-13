#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <stack>
#include <queue>
#include <ctime>
using namespace std;
struct Ogrencidugum{
	char ogrno[15];
	char ad[30];
	char soyad[30];
	Ogrencidugum *sol;
	Ogrencidugum *sag;
};
struct Agac{
	Ogrencidugum *kok;
	int dugumsayisi;
	void olustur(string dosyaad);
	void ekle(char *,char *,char *);
	void agacKur(string dosyaad);
	void ogrenciSil(string ogrencino);
	void sil(Ogrencidugum **);
	void inorderTara(Ogrencidugum *);
	void preorderTara(Ogrencidugum *);
	void postorderTara(Ogrencidugum *);
	int ilkDerinlikAra(string ogrencino,int sayac);
	int ilkGenislikAra(string ogrencino,int sayac);
	void dosyayaYaz(Ogrencidugum *);
	void agacBosalt(Ogrencidugum *);
};
typedef Agac Veriyapisi;
Veriyapisi agac1,agac2,agac3;
ofstream myfile;
Veriyapisi agacsec(string yazi,string olay){
	int secim;
	if(olay=="liste"){
		cout<<"Hangi dosya icin "<<yazi<<" listeleme yapmak istiyorsunuz?.."<<endl;
	}
	else if(olay=="ara"){
		cout<<"Hangi dosya icin "<<yazi<<" oncelikli arama yapmak istiyorsunuz?.."<<endl;
	}
	else if(olay=="sil"){
		cout<<"Hangi dosya icin silme islemi yapmak istiyorsunuz?.."<<endl;
	}
	cout<<"data1.txt icin: 1"<<endl<<"data2.txt icin: 2"<<endl<<"data3.txt icin: 3"<<endl<<endl;
	cout<<"Seciminizi giriniz:";
	cin>>secim;
	cout<<endl;
	switch (secim) {
  		case 1:
  			return agac1;
    		break;
    	case 2:
  			return agac2;
    		break;
    	case 3:
  			return agac3;
    		break;
    	default:
    		cout<<"Hata: Yanlis giris yaptiniz!!"<<endl<<endl;
    		agacsec(yazi,olay);
    		break;
    }
}
int dosyaYazAgac(){
	int secim;
	cout<<"data1.txt icin: 1"<<endl<<"data2.txt icin: 2"<<endl<<"data3.txt icin: 3"<<endl<<endl;
	cout<<"Seciminizi giriniz:";
	cin>>secim;
	cout<<endl;
	return secim;
}
bool secim_yap(char secim){
	bool sonlandir=false;
	int ogr_no,isecim,sayac=0;
	char sec;
	string secti,dosyaad;
	Veriyapisi a_sec;
	switch (secim) {
  		case 'A': case 'a':
  			cout<<"Ilk derinlik oncelikli arama yapmak icin: D"<<endl;
  			cout<<"Ilk genislik oncelikli arama yapmak icin: G"<<endl<<endl;
  			cout<<"Seciminizi giriniz: ";
  			cin>>sec;
  			cout<<endl;
  			switch (sec) {
  				case 'D': case 'd':
  					a_sec=agacsec("derinlik","ara");
  					cout<<"Aranacak ogrenci numarasi: ";
  		    		cin>>secti;
  					sayac=a_sec.ilkDerinlikAra(secti,sayac);
    				break;
    			case 'G': case 'g': 
  					a_sec=agacsec("genislik","ara");
  					cout<<"Aranacak ogrenci numarasi: ";
  		    		cin>>secti;
  					sayac=a_sec.ilkGenislikAra(secti,sayac);
    				break;
    			default:
    				cout<<"Hata: Yanlis giris yaptiniz!!"<<endl<<endl;
    				secim_yap('A');
    				break;
  			}
    		break;
  		case 'L': case 'l':
  			cout<<"Preorder listeleme yapmak icin: R"<<endl;
  			cout<<"Inorder listeleme yapmak icin: I"<<endl;
  			cout<<"Postorder listeleme yapmak icin: O"<<endl<<endl;
  			cout<<"Seciminizi giriniz: ";
  			cin>>sec;
  			cout<<endl;
  			switch (sec) {
  				case 'R': case 'r':
  					a_sec=agacsec("preorder","liste");
  					a_sec.preorderTara(a_sec.kok);
    				break;
    			case 'I': case 'i': 
  					a_sec=agacsec("inorder","liste");
  					a_sec.inorderTara(a_sec.kok);
    				break;
    			case 'O': case 'o':
  					a_sec=agacsec("postorder","liste");
  					a_sec.postorderTara(a_sec.kok);
    				break;
    			default:
    				cout<<"Hata: Yanlis giris yaptiniz!!"<<endl<<endl;
    				secim_yap('L');
    				break;
  			}
    		break;
  		case 'S': case 's':
  			a_sec=agacsec("","sil");
  		    cout<<"Silinecek ogrenci numarasi: ";
  		    cin>>secti;
  		 	a_sec.ogrenciSil(secti);
    		break;
  		case 'Y': case 'y':
  			isecim=dosyaYazAgac();
  			switch (isecim) {
  				case 1:
  					myfile.open ("agac1.txt");
  					agac1.dosyayaYaz(agac1.kok);
  					myfile.close();
    				break;
    			case 2:
    				myfile.open ("agac2.txt");
  					agac2.dosyayaYaz(agac2.kok);
  					myfile.close();
    				break;
    			case 3:
    				myfile.open ("agac3.txt");
  					agac3.dosyayaYaz(agac3.kok);
  					myfile.close();
    				break;
    			default:
    				cout<<"Hata: Yanlis giris yaptiniz!!"<<endl<<endl;
    				secim_yap('Y');
    				break;
    		}
    		break;
  		case 'C': case 'c':
    		cout << "Programi sonlandimak istediginize emin misiniz? (E/H):";
    		cin>>secim;
    		if(secim=='E' || secim=='e'){
    			agac1.agacBosalt(agac1.kok);
    			agac2.agacBosalt(agac2.kok);
    			agac3.agacBosalt(agac3.kok);
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
void Agac::ekle(char *ogrno,char *ograd, char *ogrsoyad){
	Ogrencidugum *tara,*yeni;
	tara=kok;
	bool eklendi=false;
	yeni =new Ogrencidugum;
	strcpy(yeni->ogrno,ogrno);
	strcpy(yeni->ad,ograd);
	strcpy(yeni->soyad,ogrsoyad);
	yeni->sol=NULL;
	yeni->sag=NULL;
	if(kok==NULL){
		kok=yeni;
		dugumsayisi++;
		return;
	}
	while((tara!=NULL) && (!eklendi)){
		if(atoi(yeni->ogrno)<atoi(tara->ogrno)){
			if(tara->sol!=NULL){
				tara=tara->sol;
			}
			else{
				tara->sol=yeni;
				eklendi=true;
			}
		}
		else if(atoi(yeni->ogrno)>atoi(tara->ogrno)){
			if(tara->sag!=NULL){
				tara=tara->sag;
			}
			else{
				tara->sag=yeni;
				eklendi=true;
			}
		}
		else{
			cout<<"Veri tekrari olamaz."<<endl;
		}
	}
	if(eklendi){
		dugumsayisi++;
	}
}
void Agac::agacKur(string dosyaad){
	ifstream dosya;
	string line;
	dosya.open(dosyaad);
	while(getline(dosya,line)){
		int say=0;
		string kelime = "",ogr_no,ogr_ad,ogr_soyad;
    	for (auto x : line) {
        	if (x == ' '){
        		say++;
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
            	kelime = "";
       	 	}
       		else {
            	kelime = kelime + x;
        	}
    	}
    	char ogrencino[8],ograd[50],ogrsoyad[30];
    	if(""!=ogr_no){
    		strcpy(ograd, ogr_ad.c_str());
    		strcpy(ogrsoyad, ogr_soyad.c_str());
    		strcpy(ogrencino, ogr_no.c_str());
    		ekle(ogrencino,ograd,ogrsoyad);
		}
	}
}
void Agac::olustur(string dosyaad){
	kok = NULL;
	dugumsayisi = 0;
	agacKur(dosyaad);
}
void Agac::inorderTara(Ogrencidugum *ogrenci){
	if (ogrenci){
		inorderTara (ogrenci->sol);
		cout<<ogrenci->ogrno<<" "<<ogrenci->ad<<" "<<ogrenci->soyad<<endl;
		inorderTara (ogrenci->sag);
	}
}
void Agac::preorderTara(Ogrencidugum *ogrenci){
	if (ogrenci){
		cout<<ogrenci->ogrno<<" "<<ogrenci->ad<<" "<<ogrenci->soyad<<endl;
		preorderTara (ogrenci->sol);
		preorderTara (ogrenci->sag);
	}
}
void Agac::postorderTara(Ogrencidugum *ogrenci){
	if (ogrenci){
		postorderTara (ogrenci->sol);
		postorderTara (ogrenci->sag);
		cout<<ogrenci->ogrno<<" "<<ogrenci->ad<<" "<<ogrenci->soyad<<endl;
	}
}
void Agac::sil(Ogrencidugum **ogrenci){
	Ogrencidugum *r,*q;
	r=*ogrenci;
	if(r==NULL){
		return;
	}
	else if(r->sol==NULL){
		*ogrenci=r->sag;
		delete r;
	}
	else if(r->sag==NULL){
		*ogrenci=r->sol;
		delete r;
	}
	else{
		for (q = r->sag; q->sol; q=q->sol)
			q->sol=r->sol;
		*ogrenci=r->sag;
		delete r;
	}
}
void Agac::ogrenciSil(string ogrencino){
	Ogrencidugum *tara,*ust;
	tara=kok;
	bool bulundu=false;
	char yon='k';
	while(tara && !bulundu){
		if(stoi(ogrencino)<stoi(tara->ogrno)){
			ust=tara;
			yon='l';
			tara=tara->sol;
		}
		else if(stoi(ogrencino)>stoi(tara->ogrno)){
			ust=tara;
			yon='r';
			tara=tara->sag;
		}
		else{bulundu=true;}
	}
	if(bulundu){
		if(yon=='l')
			sil(&ust->sol);
		else if(yon=='r')
			sil(&ust->sag);
		else
			sil(&kok);
	}
	else{
		cout<<"Silinecek kayit bulunamadi."<<endl;
		secim_yap('s');
	}
}
int Agac::ilkDerinlikAra(string ogrencino, int sayac){
	Ogrencidugum *p;
	stack<Ogrencidugum*> yigin;
	yigin.push(kok);
	while(!yigin.empty()){
		sayac++;
		p=yigin.top();
		yigin.pop();
		if(ogrencino==p->ogrno){
			cout<<p->ogrno<<" "<<p->ad<<" "<<p->soyad<<endl;
			return sayac;
		}
		if(p->sol)
			yigin.push(p->sol);
		if(p->sag)
			yigin.push(p->sag);
	}
}
int Agac::ilkGenislikAra(string ogrencino, int sayac){
	Ogrencidugum *p;
	queue <Ogrencidugum*>kuyruk;
	kuyruk.push(kok);
	while(!kuyruk.empty()){
		sayac++;
		p=kuyruk.front();
		kuyruk.pop();
		if(ogrencino==p->ogrno){
			cout<<p->ogrno<<" "<<p->ad<<" "<<p->soyad<<endl;
			return sayac;
		}
		if(p->sol)
			kuyruk.push(p->sol);
		if(p->sag)
			kuyruk.push(p->sag);
	}
}
void Agac::dosyayaYaz(Ogrencidugum *ogrenci){
  	if (ogrenci){
		myfile<<ogrenci->ogrno<<" "<<ogrenci->ad<<" "<<ogrenci->soyad<<" "<<endl;
		dosyayaYaz (ogrenci->sol);
		dosyayaYaz (ogrenci->sag);
	}
}
void Agac::agacBosalt(Ogrencidugum *ogrenci){
	if(ogrenci){
		if (ogrenci ->sol != NULL){
			agacBosalt (ogrenci->sol);
			ogrenci->sol = NULL;
		}
		if (ogrenci->sag != NULL){
			agacBosalt (ogrenci->sag);
			ogrenci->sag = NULL;
		}
		delete ogrenci;
	}
}
void secim_yazisi(){
	cout<<"Asagidaki islemlerden birini seciniz..."<<endl<<endl;
	cout<<"Arama yapmak icin: A"<<endl;
	cout<<"Listeyi ekrana yazdirmak icin: L"<<endl;
	cout<<"Ogrenci silmek icin: S"<<endl;
	cout<<"Dosyaya yaz: Y"<<endl;
	cout<<"Cikis icin: C"<<endl;
}
int main(){
	agac1.olustur("data1.txt");
	agac2.olustur("data2.txt");
	agac3.olustur("data3.txt");
	bool bitir=false;
	char secim;
	while(!bitir){
		secim_yazisi();
		cin >> secim;
		cout<<endl;
		bitir=secim_yap(secim);
	}
	return EXIT_SUCCESS;
}