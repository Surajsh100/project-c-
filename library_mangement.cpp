#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

class Book
{
    public:
    string title;
    string author;
    string ISBN;
    bool available;

    Book(string t, string a, string i, bool av=true){
        title = t;
        author=a;
        ISBN=i;
        available=av;
    }
};
class library
{
    vector<Book>books;
    public:
    library()
    {
        loadbooks();
    }
   
    void addbook();
    void deletebook();
    void searchbook();
    void checkoutbook();
    void displaybook();
    void returnbook();
    void loadbooks();
    void savebooks();
};
void library :: savebooks()
    {
        ofstream file("books.txt");
        for(auto &book : books)
        {
            file << book.title << ", "<<book.author << " , "<< book.ISBN << " , "<< book.available <<"\n";
        }
        file.close();
    }
 void library :: loadbooks()
    {
        ifstream file("books.txt");
        if(!file) 
        return; //if file does not exist, return

        string line,title,author,ISBN;
        bool available;

        while(getline(file,line))
        {
            stringstream ss(line);
            getline(ss,title,',');
            getline(ss,author,',');
            getline(ss,ISBN,',');
            ss >> available;
            books.push_back(Book(title,author,ISBN,available));
        }
        file.close();
    }
void library ::  addbook()
{
   
     string title,author,ISBN;
     
     cout<<"Enter book ISBN number :";
     cin>>ISBN;
     cin.ignore();
     cout<<"Enter book title :";
     getline(cin,title);
     cout<<"Enter book autor name :";
     getline(cin,author);

     books.push_back(Book(title, author, ISBN,true));
     savebooks();
     cout<<"Book Added successfully!\n";
     
}
void library :: deletebook()
{
    string ISBN;
    cin.ignore();
    cout<<"Enter ISBN to delete:";
    getline(cin,ISBN);

    for(auto it=books.begin(); it!= books.end(); ++it)
    {
        if(it-> ISBN == ISBN)
        {
            books.erase(it);
            savebooks();
            cout<<"Book Deleted Successfully!\n";
            return;
        }
    }
    cout<<"Book Not Found\n";
}
void library :: searchbook()
{
    string keyword;
    cin.ignore();
    cout<<" Enter Title , Author , or ISBN :";
    getline(cin,keyword);

    for(auto &book : books)
    {
        if(book.title == keyword || book.author == keyword || book.ISBN == keyword)
        {
            cout<< "found :"<<book.title<<" by "<<book.author << "(ISBN: "<<book.ISBN<<")\n";
            return;
        }
    }
    cout<<"Book Not Found!\n";
}
void library ::checkoutbook()
{
    string ISBN;
    cin.ignore();   

    cout<<"Enter ISBN to checkout:";
    getline(cin,ISBN);

    for(auto &book : books)
    {
        if(book.ISBN == ISBN && book.available)
        {
            book.available=false;
            savebooks();
            cout<<"Book checked out successfully!\n";
            return;
        }
    }
    cout<<"Book NOt Available !\n";
}
void library :: displaybook()
{
    if(books.empty())
    {
        cout<<"No books available in the library.\n";
        return;
    }
    cout<<"Boooks in library:\n";
    for(auto &book : books)
    {
        cout<<book.title<<"by"<<book.author<<"(ISBN:"<<book.ISBN<<") -"
        <<(book.available ? "Available": "Checked OUt ")<<"\n";
    }
}
void library :: returnbook()
{
    string ISBN;
    cin.ignore();
    cout<<"Enter ISBN to return :";
    getline(cin,ISBN);

    for(auto &book : books)
    {
        if(book.ISBN == ISBN && !book.available)
        {
            book.available=true;
            savebooks();
            cout<<"Book Returned Successfully!\n";
            return;
        }
    }
    cout<<"Invalid ISBN or book Not Checked out!\n";
}
int main()
{
    library lib;
    while(true)
    {
        cout<<"1. Add book"<<endl;  
        cout<<"2. Delete book"<<endl;
        cout<<"3. Search book"<<endl;
        cout<<"4. checkout book "<<endl;
        cout<<"5. Display all books"<<endl;
        cout<<"6. Return book "<<endl;
        cout<<"7. Exit "<<endl;
        int ch;
        cin>>ch;
        switch(ch)
        {
            case 1: lib.addbook();
                    break;
            case 2: lib.deletebook();
                    break;
            case 3: lib.searchbook();
                    break;
            case 4: lib.checkoutbook();
                    break;
            case 5: lib.displaybook();
                    break;
            case 6: lib.returnbook();
                    break;
            case 7: exit(0);

            default: cout<<"INvlid choice\n";
        }

    }
}