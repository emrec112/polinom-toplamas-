#include <iostream>
#include <string>
#include <fstream>
#define FILENAME "input.txt"
#define toplamIndex 0
#define polinomSon -1
//delete eklenecek

using namespace std;

struct Degisken{
    int katsayi;
    int derece;
    Degisken *next;
};

struct Polinom{
    Degisken *head;

    Polinom();
    ~Polinom();

    bool empty() const;
    bool checkZero(int check);
    void removefront();
    void insertordered(const int &k, const int &d);
    Polinom *mergepolinom(Polinom *p);
    void printpoli(Degisken *selected);
};

Polinom::Polinom(){
    head = NULL;
}

Polinom::~Polinom(){
    while(!empty()) removefront();
}

bool Polinom::empty() const{
    return head == NULL;
}

bool Polinom::checkZero(int k){
    return k == 0;
}

void Polinom::removefront(){
     if(head == NULL){
         return;
     }
     Degisken *temp = head;
     head = head->next;
     delete temp;
}

void Polinom::insertordered(const int &k, const int &d){//küçükten büyüğe sıralı uyucak şekilde 
    if(checkZero(k))
        return;
    Degisken *v = new Degisken;
    v->derece = d;
    v->katsayi = k;

    if(head == NULL){
        v->next = NULL;
        head = v;
        return;
    }

    if(head->derece > v->derece){
        v->next = head;
        head = v;
        return;
    }

    Degisken *pre = head;
    while(pre->next != NULL){
        if(v->derece <= pre->next->derece)
            break;
        pre = pre->next;
    }
    if(pre->next != NULL && v->derece == pre->next->derece){
        pre->next->katsayi += v->katsayi;
        delete v;
    }else{
        v->next = pre->next;
        pre->next = v;
    }
} 

Polinom *Polinom::mergepolinom(Polinom *p){//iki polinomu toplar
    Polinom *Merged = new Polinom;

    Degisken *firstp = this->head;
    Degisken *secondp = p->head;


    while((firstp != NULL) || (secondp != NULL)){

        if(firstp == NULL){
            Merged->insertordered(secondp->katsayi, secondp->derece);
            secondp = secondp->next;
            continue;
        }

        else if(secondp == NULL){
            Merged->insertordered(firstp->katsayi, firstp->derece);
            firstp = firstp->next;
            continue;
        }

        else if(secondp->derece > firstp->derece){
            Merged->insertordered(secondp->katsayi, secondp->derece);
            secondp = secondp->next;
        }

        else if(secondp->derece == firstp->derece){
            Merged->insertordered((firstp->katsayi + secondp->katsayi), secondp->derece);
            firstp = firstp->next;
            secondp = secondp->next;
        }
        else{
            Merged->insertordered(firstp->katsayi, firstp->derece);
            firstp = firstp->next;
        }
    }
    return Merged;

}

void Polinom::printpoli(Degisken *selected){

    if(head == NULL){
        cout << "liste bos!!\n";
        return;
    }

    if(selected == NULL)
        return;

    printpoli(selected->next);

    if(selected->katsayi > 0){
        cout << " + " << selected->katsayi << "x^" << selected->derece;
    }

    else if(selected->katsayi < 0){
        cout << " - " << -selected->katsayi << "x^" << selected->derece;
    }

}

int main(){
    ifstream inputs;
    inputs.open(FILENAME, ios::in);
    int katsayi, derece, i = 0, count = 0;
    string str;

    while(!inputs.eof()){
        getline(inputs,str);
        i++;
    }
    
    inputs.clear();
    inputs.seekg(0);
    Polinom *polinom = new Polinom[i];

    while(!inputs.eof()){// -1leri görene kadar dereceleri alıyoruz
        inputs >> katsayi;
        inputs >> derece;

        if(derece < 0 && derece != -1){
            cout << "hatali polinom girildi." << endl;
            exit(0);
        }

        if((katsayi == polinomSon) && (derece == polinomSon)){
            count++;
            continue;
        }

        polinom[count].insertordered(katsayi, derece);
    }

    count = 0;
    while(count < i){
        //cout << count + 1 <<". polinom : ";
        polinom[count].printpoli(polinom[count].head);
        cout << endl;
        count++;
    }
    
    Polinom toplamPolinom = polinom[toplamIndex];

    for(int index = 1; index < i; index++){// toplananları 0. indexteki polinomda topluyoruz
        toplamPolinom = *toplamPolinom.mergepolinom(&polinom[index]);
    }

    cout << "toplanmis hali : ";
    toplamPolinom.printpoli(toplamPolinom.head);
    cout << endl;

}