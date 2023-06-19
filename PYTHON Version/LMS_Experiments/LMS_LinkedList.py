# Define the AccountDetails class
class AccountDetails:
    def __init__(self, student_id, librarian_id, student_name, librarian_name, s_key, l_key, violation):
        self.student_id = student_id
        self.librarian_id = librarian_id
        self.student_name = student_name
        self.librarian_name = librarian_name
        self.s_key = s_key
        self.l_key = l_key
        self.violation = violation

    def set_violation(self, violation):
        self.violation = violation


# Define the BookDetails class
class BookDetails:
    def __init__(self, book_num, isbn, book_title, book_author, publication_year, book_quantity):
        self.book_num = book_num
        self.isbn = isbn
        self.book_title = book_title
        self.book_author = book_author
        self.publication_year = publication_year
        self.book_quantity = book_quantity

    def set_book_num(self, book_num):
        self.book_num = book_num

    def set_isbn(self, isbn):
        self.isbn = isbn

    def set_book_title(self, book_title):
        self.book_title = book_title

    def set_book_author(self, book_author):
        self.book_author = book_author

    def set_publication_year(self, publication_year):
        self.publication_year = publication_year

    def set_book_quantity(self, book_quantity):
        self.book_quantity = book_quantity
