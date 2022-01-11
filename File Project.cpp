#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<string>
using namespace std;

struct Book{
    string ISBN,
           book_name,
           auther_name,
           publisher_name;

    int year_of_publishing,
        edition_num,
        popularity;
};

class Library{
private:
    string year_of_publishing,
           edition_num,
           popularity;
    int changes_num;
    vector<Book>v, v2;

public:
    //----------------------------- get data from the file when the program starts  -----------------------------
    Library(){
        ifstream in;
        in.open("Library_books.txt");

        if(in){
            Book b;
            while(!in.eof()){
                getline(in, b.ISBN, '|');
                if(b.ISBN=="")
                    break;
                getline(in, b.book_name, '|');
                getline(in, b.auther_name, '|');
                getline(in, b.publisher_name, '|');
                getline(in, year_of_publishing, '|');
                b.year_of_publishing = toInt(year_of_publishing);
                getline(in, edition_num, '|');
                b.edition_num = toInt(edition_num);
                getline(in, popularity);
                b.popularity = toInt(popularity);

                v.push_back(b);
            }

            in.close();
        }
    }

    //------------------ toString method converts an integer to a string ------------------
    string toString(int num){
        stringstream ss;
        string s;
        ss<<num;
        ss>>s;
        return s;
    }
    //------------------ toInt method converts a string to an integer ------------------
    int toInt(string s){
        stringstream ss(s);
        int num;
        ss>>num;
        return num;
    }

    //------------------ save to file operation ------------------
    void save_to_file(){
        ofstream of;
        of.open("Library_books.txt");
        for(int i=0; i<v.size(); ++i){
            Book book=v[i];

            of<<book.ISBN<<"|";
            of<<book.book_name<<"|";
            of<<book.auther_name<<"|";
            of<<book.publisher_name<<"|";
            of<<book.year_of_publishing<<"|";
            of<<book.edition_num<<"|";
            of<<book.popularity<<"\n";
        }
        of.close();
    }

    //--------------------- undo operation ---------------------
    void undo(){
        char cc;
        cout<<"undo The last operation has done.\nDo you want to redo the last undo (Y/N)? :  ";
        cin>>cc;

        if(cc=='y'||cc=='Y'){
            v=v2;
            cout<<"redo the last undo has done\n";
            ++changes_num;
        }
    }

    //--------------------- Printing book information ------------------
    void printBook(Book book){
        cout<<"ISBN : "<<book.ISBN<<" , "<<"Book name : "<<book.book_name<<" , "<<"Auther name : "<<book.auther_name<<" , "<<"Publisher name : "<<book.publisher_name<<" , "<<"Year of publishing : "<<book.year_of_publishing<<" , "<<"Edition number : "<<book.edition_num<<"\n";
    }

    //--------------------- add book operation ---------------------
    void add_book(){
        char ch='n';
        do{
            Book b;

            cin.ignore();
            cout<<"Enter ISBN : ";
            getline(cin, b.ISBN);

            bool found=0;
            for(int i=0; i<v.size(); ++i){
                Book book=v[i];
                if(book.ISBN==b.ISBN){
                    found=1;
                    cout<<"Record Exists\n";
                    printBook(book);
                    break;
                }
            }

            if(!found){
                v2=v;

                cout<<"Enter book name :  ";
                getline(cin, b.book_name);

                cout<<"Enter auther name :  ";
                getline(cin, b.auther_name);

                cout<<"Enter publisher name :  ";
                getline(cin, b.publisher_name);

                cout<<"Enter year of publishing :  ";
                cin>>b.year_of_publishing;

                cout<<"Enter edition number :  ";
                cin>>b.edition_num;

                b.popularity=1;
                v2.push_back(b);

                cout<<"Book added successfully\nDo you want to undo the last operation (y/n)?\n";
                char c;
                cin>>c;

                if(c=='y'||c=='Y')
                    undo();
                else{
                    v=v2;
                    ++changes_num;
                }
            }

            if(changes_num==5){
                save_to_file();
                changes_num=0;
            }

            cout<<"Do you want to add another book (Y/N)? :  ";
            cin>>ch;
        }while(ch=='y'||ch=='Y');
    }

    //------------------- delete operation --------------------
    void del_book(){
        char ch='n';
        do{
            Book b;

            cin.ignore();
            cout<<"Enter ISBN for the book you want to delete :  ";
            getline(cin, b.ISBN);

            bool found=0;
            for(int i=0; i<v.size(); ++i){
                Book book=v[i];
                if(book.ISBN==b.ISBN){
                    found=1;
                    break;
                }
            }

            if(found){
                v2.clear();
                for(int i=0; i<v.size(); ++i){
                    Book book=v[i];
                    if(book.ISBN!=b.ISBN)
                        v2.push_back(book);
                }

                cout<<"Book deleted successfully\nDo you want to undo the last operation (Y/N)? :  ";
                char c;
                cin>>c;

                if(c=='y'||c=='Y')
                    undo();
                else{
                    v=v2;
                    ++changes_num;
                }
            }
            else
                cout<<"Record doesn't exists\n";

            if(changes_num==5){
                save_to_file();
                changes_num=0;
            }

            cout<<"Do you want to delete another book (y/n)?\n";
            cin>>ch;
        }while(ch=='y'||ch=='Y');
    }

    //-------------------- update operation --------------------
    void upd_book(){
        char ch='n';
        do{
            Book b;

            cin.ignore();
            cout<<"Enter ISBN for the book you want to update :  ";
            getline(cin, b.ISBN);

            bool found=0;
            for(int i=0; i<v.size(); ++i){
                Book book=v[i];
                if(book.ISBN==b.ISBN){
                    found=1;
                    b.popularity=book.popularity;
                    break;
                }
            }

            if(found){
                v2.clear();
                for(int i=0; i<v.size(); ++i){
                    Book book=v[i];
                    if(book.ISBN!=b.ISBN)
                        v2.push_back(book);
                    else{
                        cout<<"Enter new book name :  ";
                        getline(cin, b.book_name);

                        cout<<"Enter new auther name :  ";
                        getline(cin, b.auther_name);

                        cout<<"Enter new publisher name :  ";
                        getline(cin, b.publisher_name);

                        cout<<"Enter new year of publishing :  ";
                        cin>>b.year_of_publishing;

                        cout<<"Enter new edition number :  ";
                        cin>>b.edition_num;

                        v2.push_back(b);
                    }
                }

                cout<<"Book updated successfully\nDo you want to undo the last operation (Y/N)? :  ";
                char c;
                cin>>c;

                if(c=='y'||c=='Y')
                    undo();
                else{
                    v=v2;
                    ++changes_num;
                }
            }
            else
                cout<<"Record doesn't exists\n";

            if(changes_num==5){
                save_to_file();
                changes_num=0;
            }

            cout<<"Do you want to update another book (y/n)?\n";
            cin>>ch;
        }while(ch=='y'||ch=='Y');
    }

    //-------------------- search operation ---------------------
    void find_book(){
        char ch='n';
        do{
            Book b;

            cin.ignore();
            cout<<"Enter ISBN for the book you want to find :  ";
            getline(cin, b.ISBN);

            bool found=0;
            int idx, cnt=0;
            for(int i=0; i<v.size(); ++i){
                Book book=v[i];
                if(book.ISBN==b.ISBN){
                    found=1;
                    cout<<"Record Exists\n";
                    printBook(book);
                    b.popularity = book.popularity;
                    idx=cnt;
                    break;
                }
                ++cnt;
            }

            if(!found)
                cout<<"Record doesn't exists\n";
            else
                v[idx].popularity=b.popularity +1;

            cout<<"Do you want to search for another book (y/n)?\n";
            cin>>ch;
        }while(ch=='y'||ch=='Y');
    }

    //---------------------- sorting functions ---------------------
      vector<Book> sort_Asc_ISBN(vector<Book>vb){
        int sz=vb.size();
        for(int i=sz-1; i>0; --i){
            for(int j=0; j<i; ++j){
                if(vb[j].ISBN>vb[j+1].ISBN)
                    swap(vb[j], vb[j+1]);
            }
        }

        return vb;
    }
    vector<Book> sort_Desc_ISBN(vector<Book>vb){
        int sz=vb.size();
        for(int i=sz-1; i>0; --i){
            for(int j=0; j<i; ++j){
                if(vb[j].ISBN<vb[j+1].ISBN)
                    swap(vb[j], vb[j+1]);
            }
        }

        return vb;
    }
    vector<Book> sort_Desc_popularity(vector<Book>vb){
        int sz=vb.size();
        for(int i=sz-1; i>0; --i){
            for(int j=0; j<i; ++j){
                if(vb[j].popularity<vb[j+1].popularity)
                    swap(vb[j], vb[j+1]);
            }
        }

        return vb;
    }

    //-------------------- display sorted books operation ---------------------
    void display_sorted_books(int type){
        v2.clear();
        if(type==1)
            v2=sort_Asc_ISBN(v);
        else
            v2=sort_Desc_ISBN(v);

        for(int i=0; i<v2.size(); ++i)
            printBook(v2[i]);
    }

    //--------------------- display most 5 popular book operation  --------------------
    void display_most_popular_books(){
        v2.clear();
        v2=sort_Desc_popularity(v);

        for(int i=0; (i<v2.size()&&i<5); ++i)
            printBook(v2[i]);

        if(v2.size()==0)
            cout<<"There are no books\n";
    }

};

    //--------------------- Main function  -----------------------------------------
int main(){
    Library Lib;

    char chr;
    int n;
    do{
        cout<<" ________________________________________________________________\n";
        cout<<"| If you want to add a new book                         | press 1|\n";
        cout<<" ----------------------------------------------------------------\n";
        cout<<"| If you want to Delete an existing book                | press 2|\n";
        cout<<" ----------------------------------------------------------------\n";
        cout<<"| If you want to Update an existing book                | press 3|\n";
        cout<<" ----------------------------------------------------------------\n";
        cout<<"| If you want to Search for a book                      | press 4|\n";
        cout<<" ----------------------------------------------------------------\n";
        cout<<"| If you want to save data to the file                  | press 5|\n";
        cout<<" ----------------------------------------------------------------\n";
        cout<<"| If you want to display all books in ascending order   | press 6|\n";
        cout<<" ----------------------------------------------------------------\n";
        cout<<"| If you want to display all books in descending order  | press 7|\n";
        cout<<" ----------------------------------------------------------------\n";
        cout<<"| If you want to display the most 5 popular books       | press 8|\n";
        cout<<" ----------------------------------------------------------------\n";
        cout<<"| If you want to Exit                                   | press 9|\n";
        cout<<" ----------------------------------------------------------------\n";
        cin>>n;

        switch(n){
            case 1:
                Lib.add_book();
                break;
            case 2:
                Lib.del_book();
                break;
            case 3:
                Lib.upd_book();
                break;
            case 4:
                Lib.find_book();
                break;
            case 5:
                Lib.save_to_file();
                break;
            case 6:
                Lib.display_sorted_books(1);
                break;
            case 7:
                Lib.display_sorted_books(2);
                break;
            case 8:
                Lib.display_most_popular_books();
                break;
            case 9:
                Lib.save_to_file();return 0;
                break;
            default:
                cout<<"Please choose a correct number\n";
        }

        cout<<"\nDo you want to do a new operation (Y/N)? :  ";
        cin>>chr;
    }while(chr=='y'||chr=='Y');

    Lib.save_to_file();

    return 0;
}



