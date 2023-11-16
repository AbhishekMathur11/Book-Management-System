import datetime

class Book:
    def __init__(self, title, author, publication_date, isbn, copies):
        self.title = title
        self.author = author
        self.publication_date = publication_date
        self.isbn = isbn
        self.copies = copies
        self.available_copies = copies

    def display_info(self):
        print(f"Title: {self.title}")
        print(f"Author: {self.author}")
        print(f"Publication Date: {self.publication_date}")
        print(f"ISBN: {self.isbn}")
        print(f"Copies available: {self.available_copies}")

class Library:
    def __init__(self, name):
        self.name = name
        self.books = []

    def add_book(self, book):
        self.books.append(book)

    def search_books(self, title=None, author=None, isbn=None):
        results = []
        for book in self.books:
            if (title and title.lower() in book.title.lower()) or \
               (author and author.lower() in book.author.lower()) or \
               (isbn and isbn == book.isbn):
                results.append(book)
        return results

    def borrow_book(self, book, borrower_name):
        if book.available_copies > 0:
            book.available_copies -= 1
            print(f"{borrower_name} has successfully borrowed {book.title}.")
        else:
            print(f"Sorry, no available copies of {book.title}.")

    def return_book(self, book, borrower_name):
        if book.available_copies < book.copies:
            book.available_copies += 1
            print(f"{borrower_name} has successfully returned {book.title}.")
        else:
            print(f"{borrower_name}, you did not borrow {book.title} from this library.")

# Example usage:
book1 = Book("The Great Gatsby", "F. Scott Fitzgerald", "1925-04-10", "978-0743273565", 5)
book2 = Book("To Kill a Mockingbird", "Harper Lee", "1960-07-11", "978-0061120084", 3)

library = Library("City Library")
library.add_book(book1)
library.add_book(book2)

# Searching for books
results = library.search_books(title="Great Gatsby")
for result in results:
    result.display_info()

# Borrowing and returning books
library.borrow_book(book1, "Alice")
library.return_book(book1, "Alice")
library.borrow_book(book1, "Bob")
library.borrow_book(book1, "Charlie")

# Displaying book information after transactions
for book in library.books:
    book.display_info()
