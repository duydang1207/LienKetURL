#include "algorithms.h"

void MENU(HashTable* URL[])
{
    int selection;
    do 
    {
        system("cls");
        cout << "----------------MENU-----------------" << endl << endl;
        cout << "1. Den 1 trang web" << endl;
        cout << "2. Kiem tra 2 trang web co lien ket" << endl;
        cout << "3. Xoa 1 url" << endl;
        cout << "0. Thoat" << endl;
        cout << "------------------------------------" << endl << endl;
        cout << "Nhap lua chon: ";
        string option;
        cin >> option;
        if (option.length() > 1)
            selection = 1000;
        else
            selection = option[0] - '0';
        //
        if (selection == 1)
            GoToWeb(URL);
        else if (selection == 2)
        {
            CheckLink(URL);
        }
        else if (selection == 3)
        {
            string url;
            cout << "Nhap url can xoa: ";
            cin >> url;
            if (Delete(URL, url))
                cout << "Xoa thanh cong";
            else
                cout << "Khong tim thay url";
            system("pause >> null");
           
        }
        else if (selection == 0)
            break;
        else
        {
            cout << "Nhap lua chon sai!!";
            system("pause >> null");
        }
    } while (selection != 0);
}
int main()
{
    HashTable* URL[HASHTABLESIZE];
    for (int i = 0; i < HASHTABLESIZE; i++)
        URL[i] = new HashTable;
    Insert(URL, "https://utex.hcmute.edu.vn");
    Insert(URL, "https://utex.hcmute.edu.vn/login");
    Insert(URL, "https://utex.hcmute.edu.vn/login/index.php");
    Insert(URL, "https://utex.hcmute.edu.vn/my");
    Insert(URL, "https://utex.hcmute.edu.vn/?redirect=0");
    Insert(URL, "https://utex.hcmute.edu.vn/course");
    Insert(URL, "https://utex.hcmute.edu.vn/course/view.php?id=5004");
    Insert(URL, "https://utex.hcmute.edu.vn/course/view.php?id=6138");
    Insert(URL, "https://utex.hcmute.edu.vn/course/view.php?id=12354");

    Insert(URL, "https://www.facebook.com");
    Insert(URL, "https://www.facebook.com/dhspkt.hcmute");
    Insert(URL, "https://www.facebook.com/UTE.Confession");
    Insert(URL, "https://www.facebook.com/fit.hcmute.edu.vn");

    Insert(URL, "https://www.youtube.com");
    Insert(URL, "https://www.youtube.com/results?search_query=hash+table+");
    Insert(URL, "https://www.youtube.com/watch?v=dblIL2V57qU");
    Insert(URL, "https://www.youtube.com/watch?v=VdCQLfXYfuI");
    Insert(URL, "https://www.youtube.com/watch?v=gX54HnLpiog");

    InsertLink(URL, "https://utex.hcmute.edu.vn/course/view.php?id=5004", 
        "https://www.youtube.com/watch?v=dblIL2V57qU");
    InsertLink(URL, "https://utex.hcmute.edu.vn/course/view.php?id=6138",
        "https://www.youtube.com/watch?v=gX54HnLpiog");
    InsertLink(URL, "https://www.facebook.com/dhspkt.hcmute",
        "https://www.youtube.com/watch?v=VdCQLfXYfuI");
    InsertLink(URL, "https://www.youtube.com/watch?v=VdCQLfXYfuI",
        "https://www.facebook.com/dhspkt.hcmute");
    InsertLink(URL, "https://utex.hcmute.edu.vn/course/view.php?id=5004",
        "https://www.youtube.com/watch?v=VdCQLfXYfuI");
    
    MENU(URL);

    return 0;
}