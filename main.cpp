#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;
string fileName="books.txt";
int maxRecordSize = 60;
struct book{
    char isbn[6];/// max five characters
    char title[21];/// max 20 characters
    char author[21];/// max 20 characters
    int price,year,numofpages;
    void save(int numOfRecord){
        fstream file(fileName , ios::out | ios::in);
        if(numOfRecord != -1){
            file.seekp(numOfRecord*maxRecordSize + 2 , ios::beg);
        }else{
            file.seekp(0l, ios::end);
        }
        for(int i=strlen(isbn) ; i<5 ; i++){
            isbn[i]=' ';
        }
        isbn[5]=0;
        for(int i=strlen(title) ; i<20 ; i++){
            title[i]=' ';
        }
        title[20]=0;
        for(int i=strlen(author) ; i<20 ; i++){
            author[i]=' ';
        }
        author[20]=0;
        file.write(isbn , sizeof isbn);
        file.write(title , sizeof title);
        file.write(author , sizeof author);
        file.write((char*)&price , sizeof(price));
        file.write((char*)&year , sizeof(year));
        file.write((char*)&numofpages , sizeof(numofpages));
        file.close();
    }
};
ostream& operator<<(ostream& out , book b){
    out<<b.isbn<<" "<<b.author<<" "<<b.title<<" "<<b.price
    <<" "<<b.year<<" "<<b.numofpages;
}
void add_book(int numOfRecord){
    book b;
    cout<<"Enter the ISBN (5 chars) : ";
    cin>>b.isbn;
    cout<<"Enter the title of the book : ";
    cin>>b.title;
    cout<<"Enter the author name : ";
    cin>>b.author;
    cout<<"Enter the price : ";
    cin>>b.price;
    cout<<"Enter the year : ";
    cin>>b.year;
    cout<<"the number of pages : ";
    cin>>b.numofpages;
    b.save(numOfRecord);
}
/// did I use it?
/*
book read_book(int numOfRecord){
    fstream file(fileName , ios::in | ios::out);
    file.seekg(numOfRecord*maxRecordSize + 2 , ios::beg);
    file.read(b.isbn , sizeof b.isbn);
    file.read(b.title , sizeof b.title);
    file.read(b.author , sizeof b.author);
    file.read((char*)&b.price , sizeof(b.price));
    file.read((char*)&b.year , sizeof(b.year));
    file.read((char*)&b.numofpages , sizeof(b.numofpages));
    return b;
}*/
bool delete_book(){
    cout<<"Enter the isbn : ";
    char chr[6];
    cin>>chr;
     fstream file(fileName , ios::out | ios::in);
     file.seekg(2,ios::beg);
     short counter=0;
    while(true){
        book b;
        file.read(b.isbn , sizeof b.isbn);
        if(file.eof())break;
        file.read(b.title , sizeof b.title);
        file.read(b.author , sizeof b.author);
        file.read((char*)&b.price , sizeof(b.price));
        file.read((char*)&b.year , sizeof(b.year));
        file.read((char*)&b.numofpages , sizeof(b.numofpages));
        if(b.isbn[0] == '*'){
                counter++;
                continue;/// deleted record
        }
        bool ok=true;
        for(int i = 0 ; i<5 ; i++){
            if(b.isbn[i] != chr[i]){
                ok=false;
                break;
            }
        }
        if(ok){// book is found
            file.seekg(0 , ios::beg);
            short currHead;
            file.read((char*)&currHead , sizeof(currHead));
            file.seekp(0 , ios::beg);
            file.write((char*)&counter , sizeof(counter));
            file.seekp(counter*maxRecordSize + 2 , ios::beg);
            char star='*';
            file.write((char*)&star , sizeof(star));
            file.write((char*)&currHead , sizeof(currHead));
            file.close();
            return true;
        }
        counter++;
    }
    file.close();
    return false;
}
bool update_book(){
    cout<<"Enter the isbn : ";
    char chr[6];
    cin>>chr;
     fstream file(fileName , ios::out | ios::in);
     file.seekg(2,ios::beg);
     short counter=0;
    while(true){
        book b;
        file.read(b.isbn , sizeof b.isbn);
        if(file.eof())break;
        file.read(b.title , sizeof b.title);
        file.read(b.author , sizeof b.author);
        file.read((char*)&b.price , sizeof(b.price));
        file.read((char*)&b.year , sizeof(b.year));
        file.read((char*)&b.numofpages , sizeof(b.numofpages));
        if(b.isbn[0] == '*'){
            counter++;/// this is a must don't delete it
            continue;/// deleted record
        }
        bool ok=true;
        for(int i = 0 ; i<5 ; i++){
            if(b.isbn[i] != chr[i]){
                ok=false;
                break;
            }
        }
        if(ok){/// book is found
            add_book(counter);
            file.close();
            return true;
        }
        counter++;
    }
    file.close();
    return false;
}
bool print_book(){
    cout<<"Enter the isbn : ";
    char chr[6];
    cin>>chr;
     fstream file(fileName , ios::out | ios::in);
     file.seekg(2,ios::beg);
    while(true){
        book b;
        file.read(b.isbn , sizeof b.isbn);
        if(file.eof())break;
        file.read(b.title , sizeof b.title);
        file.read(b.author , sizeof b.author);
        file.read((char*)&b.price , sizeof(b.price));
        file.read((char*)&b.year , sizeof(b.year));
        file.read((char*)&b.numofpages , sizeof(b.numofpages));
        if(b.isbn[0] == '*')continue;/// deleted record
        bool ok=true;
        for(int i = 0 ; i<5 ; i++){
            if(b.isbn[i] != chr[i]){
                ok=false;
                break;
            }
        }
        if(ok){/// book is found
            cout<<b<<endl;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
void print_all_books(){
    fstream file(fileName , ios::out | ios::in);
     file.seekg(2,ios::beg);

    while(true){
        book b;
        file.read(b.isbn , sizeof b.isbn);
        if(file.eof())break;
        file.read(b.title , sizeof b.title);
        file.read(b.author , sizeof b.author);
        file.read((char*)&b.price , sizeof(b.price));
        file.read((char*)&b.year , sizeof(b.year));
        file.read((char*)&b.numofpages , sizeof(b.numofpages));
        if(b.isbn[0] == '*')continue;/// deleted record
        cout<<b<<endl;
    }
    file.close();
}
void compact_file(){
    fstream file(fileName , ios::out | ios::in);
     file.seekg(2 , ios::beg);
     vector<book> vec;
     book b;
    while(true){
        file.read(b.isbn , sizeof b.isbn);
        if(file.eof())break;
        file.read(b.title , sizeof b.title);
        file.read(b.author , sizeof b.author);
        file.read((char*)&b.price , sizeof(b.price));
        file.read((char*)&b.year , sizeof(b.year));
        file.read((char*)&b.numofpages , sizeof(b.numofpages));
        if(b.isbn[0] == '*')continue;/// deleted record
        vec.push_back(b);
    }
    file.close();
    ofstream fileOut(fileName);
    short head=-1;
    fileOut.seekp(0 , ios::beg);
    fileOut.write((char*)&head , sizeof(head));
    fileOut.close();
    for(int i=0 ; i<(int)vec.size() ; i++){
        vec[i].save(head);///append it the file
    }
}

void first_time_run_file(){
    fstream file(fileName , ios::out);
    short x=-1;
    file.write((char*)&x , sizeof(x));
    file.close();
}
int main(){
  ///  first_time_run_file();
    while(true){
        fstream file(fileName , ios::out | ios::in);
        short listHead;
        file.read((char*)&listHead , sizeof(listHead));
        cout<<"1- delete book by isbn"<<endl;
        cout<<"2- add a book"<<endl;
        cout<<"3- update a book"<<endl;
        cout<<"4- print all books"<<endl;
        cout<<"5- print a book"<<endl;
        cout<<"6- compact the file"<<endl;
        cout<<"7- get the size of the file(to test the compact function)"<<endl;
        cout<<"0- exit"<<endl;
        int choice;
        cin>>choice;
        switch(choice){
        case 1:
            if(delete_book()){
                cout<<"Record deleted successfully"<<endl;
            }else{
                cout<<"Record wasn't found"<<endl;
            }
            break;
        case 2:
            /// first we update the list head
            if(listHead != -1){
                short x;
                file.seekg(listHead * maxRecordSize + 3 , ios::beg);
                /// we add 3 to go over the * character
                file.read((char*)&x , sizeof(x));
                file.seekp(0 , ios::beg);
                file.write((char*)&x , sizeof(x));
            }
            add_book(listHead);
            break;
        case 3:
            if(update_book()){
                cout<<"Record updated successfully"<<endl;
            }else{
                cout<<"Record wasn't found"<<endl;
            }
            break;
        case 4:
            print_all_books();
            break;
        case 5:
            print_book();
            break;
        case 6:
            compact_file();
            break;
        case 7:
            file.seekg(0l , ios::end);
            cout<<"the size of the file = "<<file.tellg()<<endl;
        default:
            return 0;
        }
        file.close();
        cout<<endl<<endl;
    }
    return 0;
}
