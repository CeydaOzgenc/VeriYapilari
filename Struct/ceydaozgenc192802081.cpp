#include <iostream>
#include <stdlib.h>
using namespace std;
struct Ogrenci 
{ 
string isim,harfnotu; 
int ogrencino,*testnotlari; 
double ortalama; 
};
double notHesapla(int *testnot,string *harfnotu,double *ort,int t_sayi){
	double toplam=0;
	for(int y=0;y<t_sayi;y++){ // Kullanıcıdan alınan test sayısı kadar döngü oluşturmak.
		toplam+=*(testnot+y); // Test notlarını toplatmak.
	}
	*(ort)=toplam/t_sayi; // Test notlarının ortalamasını almak.
	if(*(ort)>=0 and *(ort)<=49){*(harfnotu)="F";} // "harfnotu" dinamik dizisinin i. indexine ortalama sonucu denk gelen harf notunu belirleyip aktarmak.
	else if(*(ort)<=64){*(harfnotu)="D";}
	else if(*(ort)<=74){*(harfnotu)="C";}
	else if(*(ort)<=84){*(harfnotu)="B";}
	else if(*(ort)<=100){*(harfnotu)="A";}
	cout<<"Ortalama is: "<<*(ort)<<" Harf notu: "<<*(harfnotu)<<endl<<endl;
}
void veriAl(int o_sayi,int t_sayi,string *ad,int *o_no,int *notlar,string *harfnotu,double *ort){
	int offset=0;
	for(int i=0;i<o_sayi;i++){ // Kullanıcıdan alınan öğreci sayısı kadar döngü oluşturmak.
		cout <<i+1<< ". ogrencinin adi:"; 
		cin>>*(ad+i); // "ad" dinamik dizisinin i. indexine kullanıcıdan alınan isimi girmek.
		cout<<i+1<< ". ogrencinin numarasi:";
		cin>>*(o_no+i);	// "o_no" dinamik dizisinin i. indexine kullanıcıdan alınan öğrenci numarasını girmek.
		for(int x=0;x<t_sayi;x++){// Kullanıcıdan alınan test sayısı kadar döngü oluşturmak.
			cout <<i+1<<". ogrencinin "<<x+1<< ". test notu:";
			cin>>*(notlar+x+offset); // "notlar" dinamik dizisinin (x+ofset). indexine kullanıcıdan alınan test notlarını girmek.
		}
		notHesapla(&notlar[offset],&harfnotu[i],&ort[i],t_sayi); // "notHesapla" fonksiyonu çağırma ve dinamik dizlerin birinci index'inin adreslerini "notHesapla" fonksiyonuna vermek.
		offset+=3;
	}
}
void sil(int o_sayi,int t_sayi,string *ad,int *o_no,int *notlar,string *harfnotu,double *ort){
	int offset=0;
	for(int i=0;i<o_sayi;i++){ // Kullanıcıdan alınan öğreci sayısı kadar döngü oluşturmak.
		delete (ad+i),(o_no+i),(harfnotu+i),(ort+i); //"ad", "o_no", "harfnotu", "ort" dinamik dizilerinin i. indexinin hafıza yerlerini iade etmek.
		for(int x=0;x<t_sayi;x++){// Kullanıcıdan alınan test sayısı kadar döngü oluşturmak.
			delete (notlar+x+offset); //"notlar" dinamik dizisinin (x+ofset). indexinin hafıza yerini iade etmek.
		}
		offset+=3;
	}
	exit(0);
}
void goster(int o_sayi,int t_sayi,string *ad,int *o_no,int *notlar,string *harfnotu,double *ort){
	int offset=0,secim;
	cout<<endl;
	for(int i=0;i<o_sayi;i++){ // Kullanıcıdan alınan öğreci sayısı kadar döngü oluşturmak.
		Ogrenci *ogrenci= new Ogrenci; // Ogrenci struct'ından "ogrenci" nesnesi oluşturmak.
		ogrenci->isim=*(ad+i); // "ogrenci" nesnesinin "isim" değerine "ad" dinamik belleğin i. indexindeki veriyi aktarmak.
		ogrenci->ogrencino=*(o_no+i); // "ogrenci" nesnesinin "ogrencino" değerine "o_no" dinamik belleğin i. indexindeki veriyi aktarmak.
		ogrenci->testnotlari=(notlar+offset); // "ogrenci" nesnesinin "testnotlari" değerine "notlar" dinamik belleğin ofset. indexinin adresini aktarmak.
		ogrenci->harfnotu=*(harfnotu+i); // "ogrenci" nesnesinin "harfnotu" değerine "harfnotu" dinamik belleğin i. indexindeki veriyi aktarmak.
		ogrenci->ortalama=*(ort+i); // "ogrenci" nesnesinin "ortalama" değerine "ort" dinamik belleğin i. indexindeki veriyi aktarmak.
		cout<<i+1<< ". ogrencinin adi: "<<ogrenci->isim<<endl<<i+1<< ". ogrencinin numarasi: "<<ogrenci->ogrencino<<endl; //"ogrenci" nesnesinin "isim" ve "ogrencino" değerini ekrana yazdırmak.
		for(int x=0;x<t_sayi;x++){ // Kullanıcıdan alınan test sayısı kadar döngü oluşturmak.
			cout <<i+1<<". ogrencinin "<<x+1<< ". test notu:"<<*(ogrenci->testnotlari+x) <<endl; //"ogrenci" nesnesinin "testnotlari" değerinin x. değerini ekrana yazdırmak.
		}
		cout<<"Ortalama is: "<<ogrenci->ortalama<<" Harf notu: "<<ogrenci->harfnotu<<endl<<endl;//"ogrenci" nesnesinin "ortalama" ve "harfnotu" değerini ekrana yazdırmak.
		offset+=3;
	}
	cout<<"Ogrenci bilgilerine bakmak icin:1"<<endl<<"Cikmak icin:2"<<endl<<"Seciminiz:";
	cin>>secim;
	switch (secim){ //Seçilen işleme göre yönlendirme yapmak.
		case 1:
		goster(o_sayi,t_sayi,&ad[0],&o_no[0],&notlar[0],&harfnotu[0],&ort[0]); // "goster" fonksiyonu çağırma ve dinamik dizlerin birinci index'inin adreslerini "goster" fonksiyonuna vermek.
		case 2:
		sil(o_sayi,t_sayi,&ad[0],&o_no[0],&notlar[0],&harfnotu[0],&ort[0]); // "sil" fonksiyonu çağırma ve dinamik dizlerin birinci index'inin adreslerini "sil" fonksiyonuna vermek.
	}
}
int main(){
	int *o_no,*notlar,o_sayi,t_sayi,secim;
	double *ort;
	string *ad,*harfnotu;
	harfnotu=new string[20]; 
	ad=new string[20];
	o_no=new int[20];
	notlar=new int[200];
	ort=new double[20]; //Dinamik bellekleri tanımlamak.
	cout<<"Ogrenci sayisini giriniz:";
	cin>>o_sayi;
	cout<<"Test sayisini giriniz:";
	cin>>t_sayi;
	cout<<endl;
	veriAl(o_sayi,t_sayi,&ad[0],&o_no[0],&notlar[0],&harfnotu[0],&ort[0]); // "veriAl" fonksiyonu çağırma ve dinamik dizlerin birinci index'inin adreslerini "veriAl" fonksiyonuna vermek. 
	cout<<endl;
	cout<<"Ogrenci bilgilerine bakmak icin:1"<<endl<<"Cikmak icin:2"<<endl<<"Seciminiz:";
	cin>>secim;
	switch (secim){ //Seçilen işleme göre yönlendirme yapmak.
		case 1:
		goster(o_sayi,t_sayi,&ad[0],&o_no[0],&notlar[0],&harfnotu[0],&ort[0]);// "goster" fonksiyonu çağırma ve dinamik dizlerin birinci index'inin adreslerini "goster" fonksiyonuna vermek.
		case 2:
		sil(o_sayi,t_sayi,&ad[0],&o_no[0],&notlar[0],&harfnotu[0],&ort[0]);// "sil" fonksiyonu çağırma ve dinamik dizlerin birinci index'inin adreslerini "sil" fonksiyonuna vermek.
	}
	return 0;
}