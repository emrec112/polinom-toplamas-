#include <iostream>
#include <string>
#include <fstream>
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
    void addfront(const int &k, const int &d);
    void addback(const int &k, const int &d);
    void removefront();
    void removeback();
    void insertordered(const int &k, const int &d);
    void removeordered(const int &k, const int &d);
    Polinom *mergepolinom(Polinom *p);
    void printpoli();
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

void Polinom::addfront(const int &k, const int &d){
    if(checkZero(k))
        return;
    Degisken *v = new Degisken;
    v->katsayi = k;
    v->derece = d;
    if(head != NULL && head->derece == v->derece){
        head->katsayi += v->katsayi;
        delete v;
    }else{
    v->next = head;
    head = v;
    }
}

void Polinom::addback(const int &k, const int &d){
    if(checkZero(k))
        return;
    Degisken *v = new Degisken;
    v->katsayi = k;
    v->derece = d;
    v->next = NULL;

    if(head == NULL) head = v;

    else{
        Degisken *u = head;
        while(u->next != NULL){
            u = u->next;
        }

        if(u->derece == v->derece){
            u->katsayi += v->katsayi;
            delete v;
        }else{
        u->next = v;
        }
    }
}

void Polinom::removefront(){
    if(head == NULL){
        return;
    }
    Degisken *temp = head;
    head = head->next;
    delete temp;
}

void Polinom::removeback(){
    if(head == NULL){
        return;
    }
    
    Degisken *temp = head;

    if(temp->next == NULL){
        head = NULL;
        delete temp;
    }

    while(temp->next != NULL){
        if(temp->next->next == NULL){
            delete temp->next;
            temp->next = NULL;
            return;
        }
        temp = temp->next;
    }
}

void Polinom::insertordered(const int &k, const int &d){
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

    if(head->derece < v->derece){
        v->next = head;
        head = v;
        return;
    }

    Degisken *pre = head;
    while(pre->next != NULL){
        if(v->derece >= pre->next->derece)
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

void Polinom::removeordered(const int &k, const int &d){
    if(head == NULL){
        return;
    }

    Degisken *v = new Degisken;
    v->derece = d;
    v->katsayi = k;

    if((head->derece == v->derece) && (head->katsayi == v->katsayi)){
        Degisken *temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Degisken *pre = head;
    while(pre->next != NULL){
        if((pre->next->derece == v->derece) && (pre->next->katsayi == v->katsayi)){
            Degisken *temp = pre->next;
            pre->next = pre->next->next;
            delete temp;
            return;
        }

        pre = pre->next;
    }
    if(pre->next == NULL){
        cout << "eleman bulunamadi\n";
        return;
    }
}   

Polinom *Polinom::mergepolinom(Polinom *p){
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

void Polinom::printpoli(){
	Degisken* selected = head;

    if(head == NULL){
        cout << "liste bos!!\n";
        return;
    }

	while (selected != NULL)
	{   
		cout << selected->katsayi;
        if(selected->derece != 0)
            cout << "x^" << selected->derece;
        if(selected->next == NULL){
            cout << endl;
            return;
        }
        cout << " + ";
		selected = selected->next;
	}
}

int main(){
    ifstream inputs;
    string file = "input.txt";
    inputs.open(file, ios::in);
    int katsayi, derece, i = 0, count = 0;
    string str;

    while(!inputs.eof()){
        getline(inputs,str);
        i++;
    }
    
    inputs.clear();
    inputs.seekg(0);
    Polinom *polinom = new Polinom[i];

    while(!inputs.eof()){
        inputs >> katsayi;
        inputs >> derece;

        if(derece < 0 && derece != -1){
            cout << "hatali polinom girildi." << endl;
            exit(0);
        }

        if((katsayi == -1) && (derece == -1)){
            count++;
            continue;
        }

        polinom[count].insertordered(katsayi, derece);
    }

    count = 0;
    while(count < i){
        cout << count + 1 <<". polinom : ";
        polinom[count].printpoli();
        count++;
    }
    
    Polinom toplamPolinom = polinom[0];

    for(int index = 1; index < i; index++){
        toplamPolinom = *toplamPolinom.mergepolinom(&polinom[index]);
    }

    cout << "toplanmis hali : ";
    toplamPolinom.printpoli();

}