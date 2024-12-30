#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std; // namespace std ���

class Book {
public:
	string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {}

    // map�� ����ϱ� ���� <������ �߰�
    bool operator<(const Book& other) const {
        return tie(title, author) < tie(other.title, other.author);
    }
};

class BookManager {
private:
    vector<Book> books; // å ��� ����

public:
	// å �߰� �޼���
	void addBook(const string& title, const string& author) {
		books.push_back(Book(title, author)); // push_back ���
		cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << endl;
	}
     
	// ��� å ��� �޼���
	void displayAllBooks() const {
		if (books.empty()) {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return;
        }

        cout << "���� ���� ���:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // �Ϲ����� for�� ���
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    // å �������� �˻� �޼���
    void searchByTitle(const string& title) {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].title == title) {
                cout << "- " << books[i].title << " by " << books[i].author << " å�� �ֽ��ϴ�." << endl;
                return;
            }
        }
        cout << "������ " << title << "�� å�� �������� �ʽ��ϴ�." << endl;
        cout << "ö�ڰ� �ùٸ��� Ȯ�� �� �ٽ� �˻��غ�����." << endl;
    }

    // �۰��� �˻� �޼���
    void searchByAuthor(const string& author) {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].author == author) {
                cout << "- " << books[i].title << " by " << books[i].author << " å�� �ֽ��ϴ�." << endl;
                return;
            }
        }
        cout << "�۰� �̸��� " << author << "�� å�� �������� �ʽ��ϴ�." << endl;
        cout << "ö�ڰ� �ùٸ��� Ȯ�� �� �ٽ� �˻��غ�����." << endl;
    }


    Book* findBookByTitle(const string& title) {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].title == title) {
                return &books[i];
            }
        }
        return nullptr;
    }

    Book* findBookByAuthor(const string& author) {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].author == author) {
                return &books[i];
            }
        }
        return nullptr;
    }
};

class BorrowManager {
private:
    map<Book, int> stock;
    int maxQuantity = 3;

public:
    // å �߰��� ��� ����ȭ
    void initializeStock(const Book& book, int quantity) {
        stock[book] = maxQuantity;
	}

	// ��� 1�� �̻��̸� �뿩 ���� ���� �뿩�ϸ� ���-1
    void borrowBook(const string& titleOrAuthor) {
        for (map<Book, int>::iterator it = stock.begin(); it != stock.end(); ++it) {
            if ((it->first.title == titleOrAuthor || it->first.author == titleOrAuthor) && it->second >= 1) {
                cout << "�뿩�Ͻðڽ��ϱ�?" << endl;
                cout << "�� : 1 ========= �ƴϿ� : 2" << endl;
                int choice;
                cin >> choice;
                if (choice == 1) {
                    it->second--;
                    cout << "�뿩�� �Ϸ�Ǿ����ϴ�. ���� ��� : "<< it->second << endl;
                }
                else {
                    cout << "�뿩�� ����߽��ϴ�." << endl;
                }
                return;
            }
        }
            cout << "�뿩 ������ å�� �����ϴ�." << endl;
    }

	// ��� 3�̸��� å�̸� �ݳ� ���� ���� �ݳ��ϸ� ���+1
    void returnBook(const string& titleOrAuthor) {
        for (map<Book, int>::iterator it = stock.begin(); it != stock.end(); ++it) {
            if ((it->first.title == titleOrAuthor || it->first.author == titleOrAuthor) && it->second < 3) {
                cout << "�ݳ��Ͻðڽ��ϱ�?" << endl;
                cout << "�� : 1 ========= �ƴϿ� : 2" << endl;
                int choice;
                cin >> choice;
                if (choice == 1) {
                    it->second++;
                    cout << "�ݳ��� �Ϸ�Ǿ����ϴ�. ���� ��� : " << it->second << endl;
                }
                else {
                    cout << "�ݳ��� ����߽��ϴ�." << endl;
                }
                return;
            }
        }
        cout << "�ݳ� ������ å�� �����ϴ�." << endl;
    }

	// �뿩���θ� �� �� �־�� �Ѵ�. ����, �۰�, ��� ��� 
	void displayStock() {
        for (auto it : stock) {
            cout << it.first.title << " by " << it.first.author << " : " << it.second << "�� �ֽ��ϴ�.";
            cout << "......" << maxQuantity - it.second << "�� �뿩��" << "..." << endl;
        }
	}
};

int main() {
    BookManager manager;
    BorrowManager borrowManager;

    // ������ ���� ���α׷��� �⺻ �޴��� �ݺ������� ����Ͽ� ����� �Է��� ó���մϴ�.
    // ���α׷� ���Ḧ �����ϱ� ������ ��� �����մϴ�.
    while (true) {
        cout << "\n================������ ���� ���α׷�================" << endl;
        cout << "0. ����" << endl; // ���α׷� ����
        cout << "1. å �߰�" << endl; // å ������ �Է¹޾� å ��Ͽ� �߰�
        cout << "2. ��� å ���" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "3. �������� �˻�" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "4. �۰��� �˻�" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "5. ������ ��ü �뿩 ��Ȳ" << endl; 
        cout << "6. �뿩" << endl; 
        cout << "7. �ݳ�" << endl; 
        cout << "====================================================" << endl;
        cout << "����: ";

        int choice; // ������� �޴� ������ ����
        cin >> choice;

        if (choice == 1) {
            // 1�� ����: å �߰�
            // ����ڷκ��� å ����� ���ڸ��� �Է¹޾� BookManager�� �߰��մϴ�.
            string title, author;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, title); // ���� �Է� (���� ����)
            cout << "å ����: ";
            getline(cin, author); // ���ڸ� �Է� (���� ����)
            manager.addBook(title, author); // �Է¹��� å ������ �߰�

            // å ����� �����ϴ� ManagerŬ�������� �߰��� å�� ��� ����ȭ
            Book* foundBook = manager.findBookByTitle(title);
            if (foundBook != nullptr) {
                borrowManager.initializeStock(*foundBook, 3);
            }
            else {
                cout << "��� ������ �����߽��ϴ�." << endl;
            }
        }
        else if (choice == 2) {
            // 2�� ����: ��� å ���
            // ���� BookManager�� ����� å ����� ����մϴ�.
            manager.displayAllBooks();
        }
        else if (choice == 3) {
            // 3�� ����: å �������� �˻�
            // 
            string title;
            cout << "�˻��� å�� ������ �Է��ϼ��� : " << endl;
            cin.ignore();
            getline(cin, title);
            manager.searchByTitle(title);

            // �ٷ� �ش� å �뿩�� ������ �����
            borrowManager.borrowBook(title);
        }
        else if (choice == 4) {
            // 4�� ����: �۰� �̸����� �˻�
            //
            string author;
            cout << "�˻��� å�� ���ڸ� �Է��ϼ��� : " << endl;
            cin.ignore();
            getline(cin, author);
            manager.searchByAuthor(author);

            // �ٷ� �ش� å �뿩�� ������ �����
            borrowManager.borrowBook(author);
        }
        else if (choice == 5) {
            // 5�� ����: ������ ��ü �뿩 ��Ȳ ���.
            //
            borrowManager.displayStock();
        }
        else if (choice == 6) {
            // 6�� ����: �����̳� �۰��� �뿩���� �˻� �� �뿩.
            //
            string titleOrAuthor;
            cout << "�뿩�� å�� �����̳� ������ �̸��� �Է��ϼ��� : " << endl;
            cin.ignore();
            getline(cin, titleOrAuthor);
            borrowManager.borrowBook(titleOrAuthor);
        }
        else if (choice == 7) {
            // 7�� ����: �ݳ�.
            //
            string titleOrAuthor;
            cout << "�ݳ��� å�� �����̳� ������ �̸��� �Է��ϼ��� : " << endl;
            cin.ignore();
            getline(cin, titleOrAuthor);
            borrowManager.returnBook(titleOrAuthor);
        }
        else if (choice == 0) {
            // 0�� ����: ����
            // ���α׷��� �����ϰ� ����ڿ��� �޽����� ����մϴ�.
            cout << "���α׷��� �����մϴ�." << endl;
            break; // while ���� ����
        }
        else {
            // �߸��� �Է� ó��
            // �޴��� ���� ��ȣ�� �Է����� ��� ��� �޽����� ����մϴ�.
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
        }
    }

    return 0; // ���α׷� ���� ����
}
