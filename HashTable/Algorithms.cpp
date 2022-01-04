#include "algorithms.h"

using namespace std;
int Search(HashTable* URL[], string url)
{
    int hashValue = HashFunction(url); //gọi hash function để tạo hash value
    
    int valueLinear = 1;
    while (URL[hashValue]->key != url && valueLinear < HASHTABLESIZE)
    {
        hashValue = (hashValue + valueLinear) % HASHTABLESIZE;
        valueLinear++;
    }
    if (URL[hashValue]->key == url)
        return hashValue;
    return -1;
}
void Insert(HashTable* URL[], string url)
{
    int hashValue = HashFunction(url);

    hashValue = CollisionResolutionInsert(URL, hashValue);

    URL[hashValue]->check = true;
    URL[hashValue]->key = url;

    //Tìm url cha
    string url2 = url;
    url2.erase(url2.rfind('/'), url.length());//url2 là url phân cấp trước nó
    int indexParent = Search(URL, url2); //tìm index cha

    if (indexParent >= 0 && URL[indexParent]->check)
    {
        Node* temp = URL[indexParent]->headNext;
        if (temp == nullptr)
        {
            temp = new Node();
            temp->next = nullptr;
            temp->index = hashValue;
            URL[indexParent]->headNext = temp;
        }
        else
        {
            while (temp->next != nullptr) temp = temp->next;
            Node* node = new Node();
            node->next = nullptr;
            node->index = hashValue;
            temp->next = node;
        }
        URL[hashValue]->prev = indexParent;
    }
}
void InsertLink(HashTable* URL[], string local, string url)
{
    int hashValue = Search(URL, url);//tìm index của liên kết cần chèn

    int indexParent = Search(URL, local);//tìm vị trí cần chèn
    Node* temp = URL[indexParent]->headNext;
    if (temp == nullptr)
    {
        temp = new Node();
        temp->next = nullptr;
        temp->index = hashValue;
    }
    else
    {
        while (temp->next != nullptr) temp = temp->next;

        Node* node = new Node();
        node->next = nullptr;
        node->index = hashValue;
        temp->next = node;
    }
}
void InsertURL(HashTable* URL[], string parent)
{
    int selection;
    cout << "1. Chen con" << endl;
    cout << "2. Chen 1 lien ket" << endl;
    cout << "-----------------------" << endl << endl;
    cout << "Nhap lua chon: ";

    string option;
    cin >> option;
    if (option != "1" && option != "2")
        selection = 1000;
    else
        selection = option[0] - '0';

    string url;
    if (selection == 1)
    {
        cout << "Nhap url: ";
        cin >> url;
        
        string url2 = url;
        if (url2.find("https://")==0)
            url2.erase(url2.rfind('/'), url.length());//cắt chuỗi url

        if (parent != url2)
        {
            cout << "Vui long nhap dung dia chi co " << parent << endl;
            system("pause >> null");
        }
        else
        {
            Insert(URL, url);
            cout << "Chen thanh cong!";
            system("pause >> null");
        }
    }
    else if (selection == 2)
    {
        cout << "Nhap url: ";
        cin >> url;
        int indexParent = Search(URL, url);
        if (indexParent < 0)
        {
            cout << "Khong tim thay lien ket can them vao!";
            system("pause >>null");
        }
        else
        {
            InsertLink(URL, parent, url);
            cout << "Chen thanh cong!";
            system("pause >> null");
        }
    }
    else
    {
        cout << "Nhap lua chon sai!!";
        system("pause >> null");
    }
}
void CheckLink(HashTable* URL[])
{
    string url1, url2;
    cout << "Nhap url1: ";
    cin >> url1;
    cout << "Nhap url2: ";
    cin >> url2;

    int hashValue1 = Search(URL, url1);
    int hashValue2 = Search(URL, url2);
    
    if (hashValue1 == -1 || hashValue2 == -1)
    {
        if (hashValue1 == -1 && hashValue2 == -1)
            cout << "Khong tim thay ca 2 url!";
        else if (hashValue1 == -1)
            cout << "Khong tim thay url: " << url1;
        else
            cout << "Khong tim thay url: " << url2;
        system("pause >> null");
        return;
    }
    if (URL[hashValue1]->prev == hashValue2 || URL[hashValue2]->prev == hashValue1)
        cout << url1 << " va " << url2 << " lien ket voi nhau";
    else
        cout << url1 << " va " << url2 << " khong lien ket voi nhau";
    system("pause >> null");
}
bool Delete (HashTable* URL[], string url)
{
    int hashValue = Search(URL, url);
    //xoa index cua ds next co lien quan den con
    if (hashValue < 0)
        return false;
    int indexParent = URL[hashValue]->prev;
    if (indexParent >= 0)
    {
        Node* temp = URL[indexParent]->headNext;
        while (temp->index != hashValue && temp->next != nullptr) temp = temp->next;

        if (temp == URL[indexParent]->headNext)
            URL[indexParent]->headNext = temp->next;
        else
        {
            Node* tempNext = URL[indexParent]->headNext;
            while (tempNext->next->index != hashValue && tempNext->next != nullptr) tempNext = tempNext->next;
            tempNext->next = temp->next;
        }
    }

    int k = 0;
    int arrayHashValue[50];
    Node* temp_n = URL[hashValue]->headNext;
    while (temp_n != nullptr)
    {
        if (URL[temp_n->index]->key.find(URL[hashValue]->key) == 0)//kiem tra cac next co cung url cha khong
            arrayHashValue[k++] = temp_n->index;
        temp_n = temp_n->next;
    }
    delete URL[hashValue];//xoa vi tri hashvalue
    URL[hashValue] = new HashTable;

    //xoa cac next con co lien quan
    int i = 0;
    while (i != k)
    {
        Node* node = URL[arrayHashValue[i]]->headNext;
        while (node != nullptr)
        {
            if (URL[node->index]->key.find(URL[arrayHashValue[i]]->key) == 0)
                arrayHashValue[k++] = node->index;
            node = node->next;
        }
        delete URL[arrayHashValue[i]];
        URL[arrayHashValue[i]] = new HashTable;
        i++;
    }
    return true;
}
void GoToWeb(HashTable* URL[])
{
    int selection;
    string url;
    cout << "Nhap dia chi trang web: ";
    cin >> url;
    int hashValue = Search(URL, url);
    int temp = hashValue, n = 0;
    int road[50];

    if (hashValue == -1) //!URL[hashValue]->check
    {
        cout << "Khong ton tai dia chi nay!!";
        system("pause >> null");
        return;
    }
    do {
        system("cls");
        cout << "URL hien tai: " << URL[hashValue]->key << endl << endl;
        cout << "Cac lien ket: " << endl;
        int i = 0;
        Node* temp = URL[hashValue]->headNext;
        while (temp != nullptr)
        {
            cout << i + 1 << ". " << URL[temp->index]->key << endl;
            temp = temp->next; i++;
        }
        if (i == 0)
            cout << "Trong!!" << endl << endl;
        cout << "\nCac chuc nang: " << endl;
        cout << i + 1 << ". Truy cap den web." << endl;
        cout << i + 2 << ". Chen 1 url." << endl;
        cout << "-1. Tro lai." << endl;
        cout << "0. Thoat." << endl;
        cout << "------------------------------------" << endl << endl;
        cout << "Nhap lua chon: ";
        string option;
        cin >> option;
        if (option == "-1")
            selection = -1;
        else if (option.length() > 2)
            selection = 1000;
        else if (option.length() == 2)
            selection = option[0] * 10 + option[1] - '0';
        else
            selection = option[0] - '0';

        if (selection == -1)
            if (n == 0)
            {
                cout << "Khong tro lai duoc nua!";
                system("pause >> null");
            }
            else {
                hashValue = road[n - 1]; n--;
            }
        else if (selection == i + 1)
            system(string("start " + URL[hashValue]->key).c_str());
        else if (selection == i + 2)
            InsertURL(URL, URL[hashValue]->key);
        else if (selection >= -1 && selection < i + 1 && selection != 0)
        {
            road[n++] = hashValue;
            Node* node = URL[hashValue]->headNext;
            int j = 0;
            while (j != selection - 1)
            {
                node = node->next;
                j++;
            }
            hashValue = node->index;
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
