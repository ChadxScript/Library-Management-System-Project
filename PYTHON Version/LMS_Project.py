import os
import sys
import time
import random
import string
import datetime
# import sanamayUI

# ----------------------[GLOBAL VARIABLES]----------------------
LMS_FOLDER_DB = "./LMS Database"
LMS_LOGS = f"{LMS_FOLDER_DB}/LMS Logs"
LMS_ACCOUNTS = f"{LMS_FOLDER_DB}/ACCOUNTS.txt"
LMS_BOOKS = f"{LMS_FOLDER_DB}/BOOKS.txt"
LMS_BOOK_REQUESTS = f"{LMS_FOLDER_DB}/BOOK_REQUESTS.txt"
LMS_KEY = f"{LMS_FOLDER_DB}/KEY.txt"

LMS_CHECK_FD = "D:\\LMS_Check.txt"
LMS_FLASH_DRIVE = "D:\\LMS Details"
LMS_FD_USER_DETAILS = f"{LMS_FLASH_DRIVE}\\USER_DETAILS.txt"
LMS_FD_BORROWED_BOOKS = f"{LMS_FLASH_DRIVE}\\BORROWED_BOOKS.txt"

FILL = "NONE"
ADMIN_FILL_NAME = "LibrarianADMIN"
ADMIN_FILL_ID = "LibrarianADMIN123"

CURRENT_S_KEY = 0
CURRENT_L_KEY = 0
CURRENT_VIOLATION = 0
CURRENT_STUDENT_ID = ""
CURRENT_STUDENT_NAME = ""
CURRENT_LIBRARIAN_ID = ""
CURRENT_LIBRARIAN_NAME = ""
KEY = "".encode()
KEY_EXIST = False


# ----------------------[LINKEDLIST]----------------------
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


# ----------------------[LOGIN]----------------------
def register_student():
    global CURRENT_S_KEY
    global CURRENT_L_KEY
    global CURRENT_STUDENT_ID
    global CURRENT_STUDENT_NAME
    global CURRENT_LIBRARIAN_ID
    global CURRENT_LIBRARIAN_NAME
    global CURRENT_VIOLATION
    count = 0
    is_valid = False

    while not is_valid:
        if count < 3:
            cls()
            print("\n\n\t\t\t\t\t\t\tAPPLICATION FORM")
            print("\n\t\tENTER YOUR INFORMATION: ")
            print("\t\t==========================================================================================")
            student_name = input("\n\t\tEnter Student Name: ")
            student_id = input("\n\t\tEnter Student ID: ")
            print("\n\n\t\t==========================================================================================")

            if check_account(1, student_id) == 2:
                s_key = CURRENT_S_KEY = 1
                l_key = CURRENT_L_KEY = 0
                CURRENT_STUDENT_ID = student_id
                CURRENT_STUDENT_NAME = student_name
                librarian_id = CURRENT_LIBRARIAN_ID = FILL
                librarian_name = CURRENT_LIBRARIAN_NAME = FILL
                violation = CURRENT_VIOLATION = 0

                account = AccountDetails(student_id, librarian_id, student_name, librarian_name,
                                         s_key, l_key, violation)
                account_list.append(account)

                print("REGISTRATION SUCCESSFUL")
                is_valid = True
            else:
                print("ERROR.")
                print("DUPLICATED STUDENT ID")
                print("PLEASE TRY AGAIN")
                count += 1
        else:
            print("TOO MANY UNSUCCESSFUL ATTEMPTS")
            print("PLEASE TRY AGAIN LATER")
            sys.exit(0)


def register_librarian():
    global CURRENT_S_KEY
    global CURRENT_L_KEY
    global CURRENT_STUDENT_ID
    global CURRENT_STUDENT_NAME
    global CURRENT_LIBRARIAN_ID
    global CURRENT_LIBRARIAN_NAME
    global CURRENT_VIOLATION
    count = 0
    is_valid = False

    while not is_valid:
        if count < 3:
            cls()
            print("\n\n\t\t\t\t\t\t\tAPPLICATION FORM ADMIN\n\n")
            print("\n\t\tPLEASE ENTER THE FOLLOWING INFORMATION TO CONFIRM")
            print("\t\t==========================================================================================")
            librarian_name = input("\n\t\tEnter Librarian Name: ")
            librarian_id = input("\n\t\tEnter Librarian ID: ")
            print("\n\n\t\t==========================================================================================")

            if librarian_name == ADMIN_FILL_NAME and librarian_id == ADMIN_FILL_ID:
                s_key = CURRENT_S_KEY = 0
                l_key = CURRENT_L_KEY = 1
                student_id = CURRENT_STUDENT_ID = FILL
                student_name = CURRENT_STUDENT_NAME = FILL
                CURRENT_LIBRARIAN_ID = librarian_id
                CURRENT_LIBRARIAN_NAME = librarian_name
                violation = 0

                account = AccountDetails(student_id, librarian_id, student_name, librarian_name,
                                         s_key, l_key, violation)
                if check_account(2, librarian_id) == 2:
                    account_list.append(account)

                print("REGISTRATION SUCCESSFUL")
                is_valid = True

            else:
                print("INVALID INPUT.")
                print("CREDENTIALS DO NOT MATCH")
                print("PLEASE TRY AGAIN")
                count += 1
        else:
            print("TOO MANY UNSUCCESSFUL ATTEMPTS")
            print("PLEASE TRY AGAIN LATER")
            sys.exit(0)


def user_login():
    is_valid = False

    if CURRENT_S_KEY == 1 and CURRENT_L_KEY == 0:
        count = 0
        while not is_valid:
            if count < 3:
                cls()
                print("\n\n\t\t\t\t\t\t\tSTUDENT LOG IN")
                print("\n\t\tENTER YOUR INFORMATION: ")
                print("\t\t==========================================================================================")
                student_id = input("\n\t\tEnter Student ID: ")

                if student_id == CURRENT_STUDENT_ID:
                    logs("IN", FILL)
                    is_valid = True
                else:
                    print("Wrong ID")
                    pause()
                    count += 1
            else:
                print("ERROR.")
                print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
                print("PLEASE TRY AGAIN LATER")
                pause()
                sys.exit(0)
    elif CURRENT_S_KEY == 0 and CURRENT_L_KEY == 1:
        count = 0
        while not is_valid:
            if count < 3:
                cls()
                print("\nLOG IN\n")
                librarian_id = input("ENTER LIBRARIAN ID: ")
                if librarian_id == ADMIN_FILL_ID:
                    logs("IN", FILL)
                    is_valid = True
                else:
                    print("\n\nERROR.")
                    print("WRONG LIBRARIAN ID")
                    print("PLEASE TRY AGAIN.")
                    pause()
                    count += 1
            else:
                print("ERROR.")
                print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
                print("PLEASE TRY AGAIN LATER")
                pause()
                sys.exit(0)
    else:
        cls()
        print("SYSTEM ERROR.")
        pause()
        cls()


# ----------------------[STUDENT]----------------------
def borrow_books():
    count = 0
    is_valid = False
    is_found = False

    user_book_num = prompts(1)

    if CURRENT_VIOLATION == 0:
        # search the book
        for book in book_list:
            if book.book_num == user_book_num:
                is_found = True

                # get current date and time
                curr_date = datetime.datetime.now().strftime("%Y-%m-%d")
                curr_year, curr_month, curr_day = curr_date.split('-')

                display_current_book(user_book_num)

                if verify_account(1):
                    temp = book.book_title
                    while not is_valid:
                        if count < 3:
                            print("BOOK COPIES TO BE BORROWED: ")
                            try:
                                user_num = int(input())
                                if 0 < user_num < book.bookQuantity:
                                    is_valid = True
                                    new_book_quant = book.book_quantity - user_num
                                    book.setBookQuantity(new_book_quant)

                                    try:
                                        with open(LMS_FD_USER_DETAILS, 'a', encoding='UTF-8') as fwrite:
                                            # -------------------encrypting-------------------
                                            encrypted_curr_year = encrypt(curr_year)
                                            encrypted_curr_month = encrypt(curr_month)
                                            encrypted_curr_day = encrypt(curr_day)
                                            encrypted_book_num = encrypt(book.book_num)
                                            encrypted_isbn = encrypt(book.isbn)
                                            encrypted_book_title = encrypt(book.book_title)
                                            encrypted_book_author = encrypt(book.book_author)
                                            encrypted_pub_year = encrypt(book.publication_year)
                                            encrypted_book_quant = encrypt(str(user_num))

                                            # -------------------saving-------------------
                                            fwrite.write(
                                                f"{encrypted_curr_year},/,"
                                                f"{encrypted_curr_month},/,"
                                                f"{encrypted_curr_day},/,"
                                                f"{encrypted_book_num},/,"
                                                f"{encrypted_isbn},/,"
                                                f"{encrypted_book_title},/,"
                                                f"{encrypted_book_author},/,"
                                                f"{encrypted_pub_year},/,"
                                                f"{encrypted_book_quant}\n"
                                            )

                                            print("THE BOOK (", temp, ") SUCCESSFULLY BORROWED.")
                                            save_books()
                                            logs("BORROWED BOOK", temp)
                                            pause()
                                            cls()
                                    except IOError as e:
                                        print(f"ERROR: {e}")
                                        pause()
                                        cls()
                                else:
                                    print("INVALID INPUT")
                                    print("PLEASE SPARE AT LEAST 1 COPY OF THE BOOK :(")
                                    print("PLEASE TRY AGAIN")
                                    cls()
                                    count += 1
                            except ValueError:
                                print("INVALID INPUT.")
                                print("PLEASE ENTER A VALID NUMBER.")
                                pause()
                                count += 1
                        else:
                            print("ERROR.")
                            print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
                            print("PLEASE TRY AGAIN LATER")
                            pause()
                            is_valid = True
                else:
                    print("TRANSACTION CANCELLED.")
                    print("INPUT DO NOT MATCH TO YOUR CREDENTIALS.")
                    print("PLEASE TRY AGAIN LATER")
                    pause()
                break
        if not is_found:
            print("BOOK NUMBER:", user_book_num, "NOT FOUND.")
            pause()
    else:
        print("TRANSACTION CANCELLED.")
        print("YOU HAVE A VIOLATION")
        print("PLEASE SETTLE YOUR VIOLATION FIRST AND TRY AGAIN LATER.")
        pause()


def return_book():
    global CURRENT_VIOLATION
    is_found = False
    is_acc_found = False

    cls()

    if verify_account(1):
        if os.path.exists(LMS_FD_BORROWED_BOOKS):
            # get current date and time
            curr_date = datetime.datetime.now().strftime("%Y-%m-%d")
            curr_year, curr_month, curr_day = curr_date.split('-')

            # Read file
            try:
                with open(LMS_FD_BORROWED_BOOKS, 'r') as f2p:
                    for line in f2p:
                        tokens = line.strip().split(",/,")

                        # Decrypt tokens
                        borrowed_year = int(decrypt(tokens[0]))
                        borrowed_month = int(decrypt(tokens[1]))
                        borrowed_day = int(decrypt(tokens[2]))
                        borrowed_book_num = int(decrypt(tokens[3]))
                        borrowed_isbn = decrypt(tokens[4])
                        borrowed_book_title = decrypt(tokens[5])
                        borrowed_book_author = decrypt(tokens[6])
                        borrowed_pub_year = int(decrypt(tokens[7]))
                        borrowed_book_quantity = int(decrypt(tokens[8]))

                        # Check penalty
                        for account in account_list:
                            if account.student_id == CURRENT_STUDENT_ID:
                                is_acc_found = True
                                if curr_year > borrowed_year:
                                    # Penalty here
                                    kept = curr_year - borrowed_year
                                    print("YOU KEPT THE BOOK FOR (", kept, ") YEAR(S)!? WTF?")
                                    print("CONGRATS!")
                                    print("YOU HAVE A VIOLATION OF 3 OR KUNG ANO MAN")
                                    account.set_violation(3)
                                    CURRENT_VIOLATION = 3
                                elif curr_month > borrowed_month:
                                    # Penalty here
                                    kept = curr_month - borrowed_month
                                    print("YOU KEPT THE BOOK FOR (", kept, ") MONTH(S)!? WTF?")
                                    print("CONGRATS!")
                                    print("YOU HAVE A VIOLATION OF 2 OR KUNG ANO MAN")
                                    account.set_violation(2)
                                    CURRENT_VIOLATION = 2
                                elif (curr_day - borrowed_day) >= 3:
                                    # Penalty here
                                    kept = curr_day - borrowed_day
                                    print("YOU KEPT THE BOOK FOR (", kept, ") DAY(S)!? WTF?")
                                    print("CONGRATS!")
                                    print("YOU HAVE A VIOLATION OF 1 OR KUNG ANO MAN")
                                    account.set_violation(1)
                                    CURRENT_VIOLATION = 1
                                else:
                                    # No penalty
                                    kept = curr_day - borrowed_day
                                    print("YOU KEPT THE BOOK FOR (", kept, ") DAY(S).")
                                    print("CONGRATS!")
                                    print("YOU DON'T HAVE A VIOLATION OR KUNG ANO MAN")
                                    account.set_violation(0)
                                    CURRENT_VIOLATION = 0
                                break

                        if is_acc_found:
                            save_accounts()
                            save_accounts_fd()
                        else:
                            print("SYSTEM ERROR")
                            print("ACCOUNT NOT FOUND IN LIST")
                            pause()
                            cls()

                        # Return the book to the database
                        for book in book_list:
                            if book.book_num == borrowed_book_num:
                                is_found = True
                                new_book_quant = book.book_quantity + borrowed_book_quantity
                                book.set_book_quantity(new_book_quant)
                                print("BOOK (", borrowed_book_title, ") SUCCESSFULLY RETURNED.")
                                save_accounts()
                                logs("RETURNED BOOK", borrowed_book_title)
                                pause()
                                cls()
                                break

                        if not is_found:
                            books = BookDetails(borrowed_book_num, borrowed_isbn, borrowed_book_title,
                                                borrowed_book_author, borrowed_pub_year, borrowed_book_quantity)
                            book_list.append(books)
                            print("BOOK (", borrowed_book_title, ") SUCCESSFULLY RETURNED.")
                            save_books()
                            logs("RETURNED BOOK", borrowed_book_title)
                            pause()
                            cls()
            except IOError as e:
                print(f"ERROR: {e}")
                pause()
                cls()

            # Remove BORROWED_BOOKS.txt
            try:
                os.remove(LMS_FD_BORROWED_BOOKS)
            except OSError as e:
                print(f"ERROR: {e}")
                pause()
                cls()
        else:
            print("ERROR.")
            print("NO BOOKS TO BE RETURNED.")
            pause()
    else:
        print("TRANSACTION CANCELLED.")
        print("INPUT DOES NOT MATCH YOUR CREDENTIALS.")
        print("PLEASE TRY AGAIN LATER.")
        pause()


def request_book():
    cls()
    count = 0
    count2 = 0
    valid_random_isbn = ""
    is_valid = False
    is_correct = False
    is_cancelled = False

    if CURRENT_VIOLATION == 0:
        while not is_valid:
            if count < 3:
                cls()

                book_num = get_book_number()
                print("BOOK ID:", book_num)

                book_title = input("INPUT BOOK TITLE: ")

                book_author = input("INPUT BOOK AUTHOR: ")

                pub_year = int(input("INPUT PUBLICATION YEAR: "))

                book_quantity = int(input("INPUT BOOK QUANTITY: "))

                user_num = prompts(4)
                if user_num == 1:  # student knows the book's ISBN
                    if 0 < pub_year <= 2006 and book_quantity > 0:
                        user_isbn = input("\n\nENTER VALID 10-DIGIT ISBN: ")
                        length = len(user_isbn)
                        if length == 10 and check_isbn(user_isbn, 10):
                            valid_random_isbn = user_isbn
                            is_valid = True
                            is_cancelled = False
                        else:
                            print("\nMODIFICATION UNSUCCESSFUL.")
                            print("INVALID ISBN.")
                            pause()
                            cls()
                            count += 1
                    elif pub_year > 2006 and book_quantity > 0:
                        user_isbn = input("\n\nENTER VALID 13-DIGIT ISBN: ")
                        length = len(user_isbn)
                        if length == 13 and check_isbn(user_isbn, 13):
                            valid_random_isbn = user_isbn
                            is_valid = True
                            is_cancelled = False
                        else:
                            print("\nMODIFICATION UNSUCCESSFUL.")
                            print("INVALID ISBN.")
                            pause()
                            cls()
                            count += 1
                    else:
                        print("\nMODIFICATION UNSUCCESSFUL.")
                        print("INVALID INPUT.")
                        pause()
                        cls()
                        count += 1
                elif user_num == 2:  # student doesn't know the book's ISBN
                    if 0 < pub_year <= 2006 and book_quantity > 0:
                        valid_random_isbn = get_isbn(10)
                        is_valid = True
                        is_cancelled = False
                    elif pub_year > 2006 and book_quantity > 0:
                        valid_random_isbn = get_isbn(13)
                        is_valid = True
                        is_cancelled = False
                    else:
                        print("\nMODIFICATION UNSUCCESSFUL.")
                        print("INVALID INPUT.")
                        pause()
                        cls()
                        count += 1
                elif user_num == 3:  # cancelled
                    is_valid = True
                    is_cancelled = True
                else:
                    print("WRONG RETURN VALUE")
                    pause()
                    cls()

                if is_valid and not is_cancelled:
                    if check_books(1, book_title, book_author, 0):
                        while not is_correct:
                            if count2 < 3:
                                if verify_account(1):
                                    is_correct = True
                                    # ----------------- encryption -----------------
                                    encrypted_book_num = encrypt(str(book_num))
                                    encrypted_isbn = encrypt(valid_random_isbn)
                                    encrypted_book_title = encrypt(book_title)
                                    encrypted_book_author = encrypt(book_author)
                                    encrypted_pub_year = encrypt(str(pub_year))
                                    encrypted_book_quant = encrypt(str(book_quantity))

                                    # ----------------- saving -----------------
                                    book = BookDetails(encrypted_book_num, encrypted_isbn, encrypted_book_title,
                                                       encrypted_book_author, encrypted_pub_year, encrypted_book_quant)
                                    book_request_list.append(book)
                                    save_book_requests()
                                    logs("REQUEST BOOK", book_title)

                                    print("\nBOOK (", book_title, ") SUCCESSFULLY REQUESTED.")
                                    pause()
                                    cls()
                                else:
                                    print("ERROR.")
                                    print("INPUT DOES NOT MATCH YOUR CREDENTIALS.")
                                    print("PLEASE TRY AGAIN")
                                    pause()
                                    cls()
                                    count2 += 1
                            else:
                                print("ERROR.")
                                print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
                                print("PLEASE TRY AGAIN LATER")
                                pause()
                                cls()
                                is_correct = True
                    else:
                        user_num = prompts(5)
                        if user_num == 1:
                            while not is_correct:
                                if count2 < 3:
                                    if verify_account(2):
                                        count = 0
                                        count2 = 0
                                        is_correct = True
                                        is_valid = False
                                    else:
                                        print("ERROR.")
                                        print("INPUT DOES NOT MATCH YOUR CREDENTIALS.")
                                        print("PLEASE TRY AGAIN")
                                        pause()
                                        cls()
                                        count2 += 1
                                else:
                                    print("ERROR.")
                                    print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
                                    print("PLEASE TRY AGAIN LATER")
                                    pause()
                                    cls()
                                    is_correct = True
                        else:
                            print("PLEASE TRY AGAIN LATER")
                            pause()
                            cls()
                            is_correct = True
                elif is_valid and is_cancelled:
                    print("\nMODIFICATION CANCELLED.")
                    pause()
                    cls()
            else:
                print("ERROR.")
                print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
                print("PLEASE TRY AGAIN LATER")
                pause()
                cls()
                is_valid = True
    else:
        print("TRANSACTION CANCELLED.")
        print("YOU HAVE A VIOLATION")
        print("PLEASE SETTLE YOUR VIOLATION FIRST AND TRY AGAIN LATER.")
        pause()
        cls()


def view_violation():
    global CURRENT_VIOLATION
    cls()
    is_found = False
    # locate the account
    for account in account_list:
        if account.student_id == CURRENT_STUDENT_ID:
            is_found = True
            if account.violation != 0:
                print("YOU HAVE VIOLATION OF: ", account.violation)
                user_num = prompts(8)
                if user_num == 1:
                    account.set_violation(0)
                    CURRENT_VIOLATION = 0
                    save_accounts()
                    save_accounts_fd()
                    logs("SETTLED VIOLATION", FILL)

                    print("CONGRATULATIONS! YOU SETTLED YOUR VIOLATION.")
                    pause()
                    cls()
                else:
                    print("PLEASE SETTLE YOUR VIOLATION FIRST.")
                    pause()
                    cls()
            else:
                print("CONGRATULATIONS! YOU DON'T HAVE ANY VIOLATION.")
                pause()
                cls()
    if not is_found:
        print("SYSTEM ERROR")
        print("ACCOUNT NOT FOUND IN LIST")
        pause()
        cls()


# ----------------------[LIBRARIAN]----------------------
def insert_existing_book():
    count = 0
    count2 = 0
    is_valid = False
    is_num = False
    cls()
    display_books()

    while not is_valid:
        if count < 3:
            try:
                print("ENTER BOOK NUMBER: ")
                user_num = int(input())
                # input()  # Consume the newline character

                # Check if book exists
                for book in book_list:
                    if book.book_num == user_num:
                        is_valid = True

                        print("BOOK SELECTED: ")
                        display_current_book(book.book_num)

                        while not is_num:
                            if count2 < 3:
                                print("\n\nENTER BOOK COPIES TO BE INSERTED: ")
                                try:
                                    user_num = int(input())
                                    # input()  # Consume the newline character
                                    if user_num > 0:
                                        if verify_account(2):
                                            is_num = True
                                            new_book_quant = book.book_quantity + user_num
                                            book.set_book_quantity(new_book_quant)
                                            print("\nMODIFICATION SUCCESSFUL.\n")
                                            print("BOOK LIST:")
                                            display_books()
                                            print("\n\nBOOK SELECTED:")
                                            display_current_book(book.book_num)
                                            save_books()
                                            logs("ADD EXISTING BOOK", book.book_title)
                                            pause()
                                            cls()
                                        else:
                                            print("INVALID INPUT")
                                            print("CREDENTIALS DO NOT MATCH")
                                            print("PLEASE TRY AGAIN.")
                                            pause()
                                            cls()
                                            count2 += 1
                                    else:
                                        print("\n\nINVALID INPUT.")
                                        print("PLEASE TRY AGAIN")
                                        pause()
                                        cls()
                                        count2 += 1
                                except ValueError as e:
                                    print(f"\nERROR: {e}")
                                    pause()
                                    cls()
                                    count2 += 1
                            else:
                                print("ERROR.")
                                print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
                                print("PLEASE TRY AGAIN LATER")
                                pause()
                                cls()
                                is_num = True

                        break
                if not is_valid:
                    print("ERROR")
                    print("WRONG BOOK NUMBER OR BOOK NUMBER DOES NOT EXIST")
                    print("PLEASE TRY AGAIN")
                    pause()
                    cls()
                    count += 1
            except ValueError as e:
                print(f"\nERROR: {e}")
                pause()
                cls()
        else:
            print("ERROR.")
            print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
            print("PLEASE TRY AGAIN LATER")
            pause()
            cls()
            is_valid = True


def insert_new_book():
    cls()
    count = 0
    count2 = 0
    valid_random_isbn = ""
    is_valid = False
    is_correct = False

    while not is_valid:
        if count < 3:
            cls()

            book_num = get_book_number()
            print("BOOK ID: " + str(book_num))

            print("INPUT BOOK TITLE: ")
            book_title = input()

            print("INPUT BOOK AUTHOR: ")
            book_author = input()

            print("INPUT PUBLICATION YEAR: ")
            pub_year = int(input())

            print("INPUT BOOK QUANTITY: ")
            book_quantity = int(input())

            # input()  # Consume the newline character

            user_num = prompts(4)
            if user_num == 1:  # librarian knows the book's ISBN
                if 0 < pub_year <= 2006 and book_quantity > 0:
                    print("\n\nENTER VALID 10-DIGIT ISBN: ")
                    user_isbn = input()
                    if len(user_isbn) == 10:
                        if check_isbn(user_isbn, 10):
                            valid_random_isbn = user_isbn
                            is_valid = True
                        else:
                            print("\nMODIFICATION UNSUCCESSFUL.")
                            print("INVALID ISBN.")
                            pause()
                            cls()
                            count += 1
                    else:
                        print("\nMODIFICATION UNSUCCESSFUL.")
                        print("INVALID ISBN.")
                        pause()
                        cls()
                        count += 1
                elif pub_year > 0 and pub_year > 2006 and book_quantity > 0:
                    print("\n\nENTER VALID 13-DIGIT ISBN: ")
                    user_isbn = input()
                    if len(user_isbn) == 13:
                        if check_isbn(user_isbn, 13):
                            valid_random_isbn = user_isbn
                            is_valid = True
                        else:
                            print("\nMODIFICATION UNSUCCESSFUL.")
                            print("INVALID ISBN.")
                            pause()
                            cls()
                            count += 1
                    else:
                        print("\nMODIFICATION UNSUCCESSFUL.")
                        print("INVALID ISBN.")
                        pause()
                        cls()
                        count += 1
                else:
                    print("\nMODIFICATION UNSUCCESSFUL.")
                    print("INVALID PUBLICATION YEAR.")
                    pause()
                    cls()
                    count += 1
            elif user_num == 2:  # librarian doesn't know the book's ISBN
                # will generate valid ISBN based on pub year
                if 0 < pub_year <= 2006 and book_quantity > 0:
                    valid_random_isbn = get_isbn(10)
                    is_valid = True
                elif pub_year > 0 and pub_year > 2006 and book_quantity > 0:
                    valid_random_isbn = get_isbn(13)
                    is_valid = True
                else:
                    print("\nMODIFICATION UNSUCCESSFUL.")
                    print("INVALID PUBLICATION YEAR.")
                    pause()
                    cls()
                    count += 1
            elif user_num == 3:  # cancelled
                print("\nMODIFICATION CANCELLED.")
                is_valid = True
                pause()
                cls()
            else:
                print("WRONG RETURN VALUE")
                pause()
                cls()

            if is_valid:
                if check_books(1, book_title, book_author, 0):
                    while not is_correct:
                        if count2 < 3:
                            if verify_account(2):
                                is_correct = True
                                book = BookDetails(book_num, valid_random_isbn, book_title, book_author,
                                                   pub_year, book_quantity)
                                book_list.append(book)
                                save_books()
                                logs("ADDED NEW BOOK", book_title)

                                print("\nBOOK ( " + book_title + " ) SUCCESSFULLY ADDED.")
                                pause()
                                cls()
                            else:
                                print("ERROR.")
                                print("INPUT DOES NOT MATCH YOUR CREDENTIALS.")
                                print("PLEASE TRY AGAIN")
                                pause()
                                cls()
                                count2 += 1
                        else:
                            print("ERROR.")
                            print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
                            print("PLEASE TRY AGAIN LATER")
                            pause()
                            cls()
                            is_correct = True
                else:
                    user_num = prompts(5)
                    if user_num == 1:
                        while not is_correct:
                            if count2 < 3:
                                if verify_account(2):
                                    count = 0
                                    count2 = 0
                                    is_correct = True
                                    is_valid = False
                                else:
                                    print("ERROR.")
                                    print("INPUT DOES NOT MATCH YOUR CREDENTIALS.")
                                    print("PLEASE TRY AGAIN")
                                    pause()
                                    cls()
                                    count2 += 1
                            else:
                                print("ERROR.")
                                print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
                                print("PLEASE TRY AGAIN LATER")
                                pause()
                                cls()
                                is_correct = True
                    else:
                        print("PLEASE TRY AGAIN LATER")
                        pause()
                        cls()
                        is_correct = True
        else:
            print("ERROR.")
            print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
            print("PLEASE TRY AGAIN LATER")
            pause()
            cls()
            is_valid = True


def edit_books():
    cls()
    ch = 0
    count = 0
    is_correct = False
    is_found = False

    while not is_correct:
        if count < 3:
            if verify_account(2):
                cls()
                is_correct = True

                print("\n\nENTER BOOK NUMBER TO BE EDITED: ")
                user_book_num = int(input())

                for book in book_list:
                    if book.book_num == user_book_num:
                        is_found = True
                        while ch != 6:
                            print("\n\n\nBOOK NUMBER: " + str(book.book_num))
                            print("ISBN: " + book.isbn)
                            print("BOOK TITLE: " + book.book_title)
                            print("BOOK AUTHOR: " + book.book_author)
                            print("BOOK PUBLICATION YEAR: " + str(book.publication_year))
                            print("BOOK QUANTITY: " + str(book.book_quantity))
                            ch = prompts(6)
                            if ch == 1:
                                print("INPUT NEW VALID BOOK NUMBER: ")
                                new_book_num = int(input())
                                if check_books(2, None, None, new_book_num):
                                    book.set_book_num(new_book_num)
                                    save_books()
                                    logs("EDIT BOOK NUMER", book.book_num)
                                else:
                                    print("ERROR.")
                                    print("BOOK NUMBER ALREADY EXIST.")
                                    pause()
                                    cls()
                            elif ch == 2:
                                print("INPUT NEW VALID BOOK TITLE: ")
                                new_book_title = input()
                                if check_books(1, new_book_title, book.book_author, 0):
                                    logs("EDIT BOOK TITLE",
                                         "FROM ( " + book.book_title + " ) TO ( " + new_book_title + " )")
                                    book.set_book_title(new_book_title)
                                    save_books()
                                else:
                                    print("ERROR.")
                                    print("BOOK DETAILS ALREADY EXIST.")
                                    pause()
                                    cls()
                            elif ch == 3:
                                print("INPUT NEW VALID BOOK AUTHOR: ")
                                new_book_author = input()
                                if check_books(1, book.book_title, new_book_author, 0):
                                    logs("EDIT BOOK AUTHOR",
                                         "FROM ( " + book.book_author + " ) TO ( " + new_book_author + " )")
                                    book.set_book_author(new_book_author)
                                    save_books()
                                else:
                                    print("ERROR.")
                                    print("BOOK DETAILS ALREADY EXIST.")
                                    pause()
                                    cls()
                            elif ch == 4:
                                print("INPUT NEW VALID BOOK PUBLICATION YEAR: ")
                                new_book_year = int(input())
                                curr_date = datetime.date.today()
                                if 0 < new_book_year < curr_date.year:
                                    logs("EDIT BOOK PUB.YEAR",
                                         "FROM ( " + str(book.publication_yea) + " ) TO ( " + str(new_book_year) + " )")
                                    book.set_publication_year(new_book_year)

                                    # update the ISBN base on the new pub date
                                    if new_book_year <= 2006:
                                        new_isbn = get_isbn(10)
                                    else:
                                        new_isbn = get_isbn(13)
                                    logs("EDIT BOOK ISBN",
                                         "FROM ( " + book.isbn + " ) TO ( " + new_isbn + " )")
                                    book.set_ISBN(new_isbn)
                                    save_books()
                                    pause()
                                    cls()
                                else:
                                    print("ERROR.")
                                    print("INVALID BOOK PUBLICATION YEAR.")
                                    pause()
                                    cls()
                            elif ch == 5:
                                print("INPUT NEW VALID BOOK QUANTITY: ")
                                new_book_quant = int(input())
                                if new_book_quant > 0:
                                    logs("EDIT BOOK QUANTITY",
                                         "FROM ( " + str(book.book_quantity) + " ) TO ( " + str(new_book_quant) + " )")
                                    book.set_book_quantity(new_book_quant)
                                    save_books()
                                else:
                                    print("ERROR.")
                                    print("INVALID BOOK QUANTITY.")
                                    pause()
                                    cls()
                            elif ch == 6:
                                print("\n\nBOOK SUCCESSFULLY EDITED.")
                                pause()
                                cls()
                            else:
                                print("\n\nSELECT 1 - 6 ONLY.")
                                pause()
                                cls()
                        save_books()
                        logs("EDIT BOOK", book.book_title)
                        break

                if not is_found:
                    print("ERROR NOT FOUND.")
                    print("WRONG BOOK NUMBER OR IT DOES NOT EXIST")
                    print("PLEASE TRY AGAIN LATER")
                    pause()
                    cls()
                    is_correct = False
                    count += 1
            else:
                print("INVALID INPUT")
                print("DOES NOT MATCH TO YOUR CREDENTIALS")
                print("PLEASE TRY AGAIN")
                pause()
                cls()
                count += 1
        else:
            print("ERROR.")
            print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
            print("PLEASE TRY AGAIN LATER")
            pause()
            cls()
            is_correct = True


def remove_book_copy():
    cls()
    count = 0
    count2 = 0
    is_valid = False
    is_correct = False

    while not is_valid:
        if count < 3:
            cls()
            print("\n\nENTER BOOK NUMBER TO REMOVE A COPY: ")
            user_book_num = int(input())
            for book in book_list:
                if book.book_num == user_book_num:
                    is_valid = True
                    while not is_correct:
                        if count2 < 3:
                            print("\n\nBOOK SELECTED: ")
                            display_current_book(user_book_num)

                            print("ENTER NUMBER OF COPIES TO REMOVE: ")
                            user_quantity = int(input())
                            if 0 < user_quantity < book.book_quantity:
                                if verify_account(2):
                                    is_correct = True
                                    new_quant = book.book_quantity - user_quantity
                                    book.set_book_quantity(new_quant)
                                    display_books()
                                    print("\n\nMODIFICATION SUCCESSFUL.")
                                    display_current_book(user_book_num)

                                    save_books()
                                    logs("REMOVE A COPY", book.book_title)
                                    pause()
                                    cls()
                                else:
                                    print("INVALID INPUT")
                                    print("DOES NOT MATCH TO YOUR CREDENTIALS")
                                    print("PLEASE TRY AGAIN")
                                    pause()
                                    cls()
                                    count2 += 1
                            else:
                                print("ERROR.")
                                print("INVALID QUANTITY.")
                                pause()
                                cls()
                                count2 += 1
                    break

            if not is_valid:
                print("ERROR NOT FOUND.")
                print("WRONG BOOK NUMBER OR IT DOES NOT EXIST")
                print("PLEASE TRY AGAIN LATER")
                pause()
                cls()
                count += 1
        else:
            print("ERROR.")
            print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
            print("PLEASE TRY AGAIN LATER")
            pause()
            cls()
            is_valid = True


def remove_book():
    cls()
    count = 0
    count2 = 0
    is_valid = False
    is_correct = False

    while not is_valid:
        if count < 3:
            cls()
            print("\n\nENTER BOOK NUMBER TO REMOVE: ")
            user_book_num = int(input())
            for book in book_list:
                if book.book_num == user_book_num:
                    is_valid = True
                    while not is_correct:
                        if count2 < 3:
                            print("\n\nBOOK SELECTED: ")
                            display_current_book(user_book_num)

                            if verify_account(2):
                                is_correct = True
                                logs("REMOVED BOOK", book.book_title)
                                book_list.remove(book)
                                display_books()
                                print("\n\nMODIFICATION SUCCESSFUL.")

                                save_books()
                                pause()
                                cls()
                            else:
                                print("INVALID INPUT")
                                print("DOES NOT MATCH TO YOUR CREDENTIALS")
                                print("PLEASE TRY AGAIN")
                                pause()
                                cls()
                                count2 += 1
                    break

            if not is_valid:
                print("ERROR NOT FOUND.")
                print("WRONG BOOK NUMBER OR IT DOES NOT EXIST")
                print("PLEASE TRY AGAIN LATER")
                pause()
                cls()
                count += 1
        else:
            print("ERROR.")
            print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
            print("PLEASE TRY AGAIN LATER")
            pause()
            cls()
            is_valid = True


def book_requests():
    cls()
    count = 0
    count2 = 0
    is_found = False
    is_correct = False

    if os.path.exists(LMS_BOOK_REQUESTS):
        try:
            with open(LMS_BOOK_REQUESTS, 'r') as f2p:
                cls()
                lines = f2p.readlines()

                for line in lines:
                    tokens = line.split(",/,")

                    req_book_num = int(decrypt(tokens[0]))
                    req_isbn = decrypt(tokens[1])
                    req_book_title = decrypt(tokens[2])
                    req_book_author = decrypt(tokens[3])
                    req_publication_year = int(decrypt(tokens[4]))
                    req_book_quant = int(decrypt(tokens[5]))

                    req_book = BookDetails(req_book_num, req_isbn, req_book_title, req_book_author,
                                           req_publication_year, req_book_quant)
                    book_request_list.append(req_book)

                # Display contents
                print("\nBOOK REQUESTS")
                display_book_requests()

                # Approve or disapprove
                user_num = prompts(7)
                if user_num == 1:  # Approve book request
                    while not is_found:
                        if count < 3:
                            cls()
                            print("ENTER BOOK NUMBER: ")
                            user_num = int(input())
                            for req_book in book_request_list:
                                if req_book.book_num == user_num:
                                    is_found = True
                                    while not is_correct:
                                        if count2 < 3:
                                            if verify_account(2):
                                                is_correct = True
                                                book_list.append(req_book)
                                                book_request_list.remove(req_book)
                                                save_books()
                                                save_book_requests()
                                                logs("APPROVED BOOK", req_book.book_title)

                                                print("BOOK (", req_book.book_title, ") APPROVED.")
                                                pause()
                                                cls()
                                            else:
                                                print("INVALID INPUT")
                                                print("DOES NOT MATCH TO YOUR CREDENTIALS")
                                                print("PLEASE TRY AGAIN")
                                                pause()
                                                cls()
                                                count2 += 1
                                    break

                            if not is_found:
                                print("ERROR")
                                print("WRONG BOOK NUMBER OR BOOK NUMBER DOES NOT EXIST")
                                print("PLEASE TRY AGAIN")
                                pause()
                                cls()
                                count += 1
                        else:
                            print("ERROR.")
                            print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
                            print("PLEASE TRY AGAIN LATER")
                            pause()
                            cls()
                            is_found = True
                elif user_num == 2:  # Disapprove book
                    while not is_found:
                        if count < 3:
                            cls()
                            print("ENTER BOOK NUMBER: ")
                            user_num = int(input())
                            for req_book in book_request_list:
                                if req_book.book_num == user_num:
                                    is_found = True
                                    while not is_correct:
                                        if count2 < 3:
                                            if verify_account(2):
                                                is_correct = True
                                                book_request_list.remove(req_book)
                                                save_books()
                                                save_book_requests()
                                                logs("DISAPPROVED BOOK", req_book.book_title)

                                                print("BOOK (", req_book.book_title, ") DISAPPROVED.")
                                                pause()
                                                cls()
                                            else:
                                                print("INVALID INPUT")
                                                print("DOES NOT MATCH TO YOUR CREDENTIALS")
                                                print("PLEASE TRY AGAIN")
                                                pause()
                                                cls()
                                                count2 += 1
                                    break

                            if not is_found:
                                print("ERROR")
                                print("WRONG BOOK NUMBER OR BOOK NUMBER DOES NOT EXIST")
                                print("PLEASE TRY AGAIN")
                                pause()
                                cls()
                                count += 1
                        else:
                            print("ERROR.")
                            print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
                            print("PLEASE TRY AGAIN LATER")
                            pause()
                            cls()
                            is_found = True
                elif user_num == 3:  # Save and exit
                    save_books()
                    save_book_requests()
                else:
                    print("INVALID INPUT.")
                    pause()
                    cls()
        except FileNotFoundError as e:
            print("\nERROR:", e)
            pause()
            cls()
        except IOError as e:
            print("\nERROR:", e)
            pause()
            cls()
    else:
        print("ERROR.")
        print("NO BOOK REQUESTS YET.")
        pause()
        cls()


def change_key():
    global KEY
    cls()
    new_key = ""
    count = 0
    is_valid = False
    # srand = random.Random()

    if verify_account(2):
        user_num = prompts(9)
        if user_num == 1:  # Generate random valid key
            while not is_valid:
                # new_key = srand.randint(1, 100)
                new_key = " " + string.digits + string.ascii_letters
                new_key = new_key.encode()
                if new_key != KEY:
                    is_valid = True

            # Save the key to the file
            if not os.path.exists(LMS_KEY): 
                try:
                    open(LMS_KEY, 'w').close()
                except IOError as e:
                    print("ERROR:", e)
                    pause()
                    cls()

            try:
                with open(LMS_KEY, 'w') as fwrite:
                    fwrite.write(new_key)
            except IOError as e:
                print("ERROR:", e)
                pause()
                cls()

            KEY = new_key
            print("KEY IS SET TO:", KEY)
            pause()
            cls()
        elif user_num == 2:  # Librarian will enter the new key
            while not is_valid:
                if count < 3:
                    try:
                        new_key = input("ENTER VALID KEY: ")
                        new_key = new_key.encode()
                        if new_key != KEY:
                            KEY = new_key
                            is_valid = True
                            # Save the key to the file
                            if not os.path.exists(LMS_KEY):
                                try:
                                    open(LMS_KEY, 'w').close()
                                except IOError as e:
                                    print("ERROR:", e)
                                    pause()
                                    cls()

                            try:
                                with open(LMS_KEY, 'w') as fwrite:
                                    fwrite.write(KEY)
                            except IOError as e:
                                print("ERROR:", e)
                                pause()
                                cls()

                        else:
                            print("PLEASE ENTER 'NEW' AND 'VALID' KEY.")
                            print("PLEASE TRY AGAIN.")
                            pause()
                            cls()
                            count += 1
                    except ValueError as e:
                        print("ERROR:", e)
                        pause()
                        cls()
                        count += 1
        else:
            print("WRONG RETURN VALUE.")
            print("PLEASE CHECK THE CODE.")
            pause()
            cls()
    else:
        print("INVALID INPUT")
        print("CREDENTIALS DO NOT MATCH")
        print("PLEASE TRY AGAIN LATER.")
        pause()
        cls()

    # Check if the files exist
    # If they exist, save the data to the new key
    if os.path.exists(LMS_ACCOUNTS):
        save_accounts()
    if os.path.exists(LMS_FD_USER_DETAILS):
        save_accounts_fd()
    if os.path.exists(LMS_BOOKS):
        save_books()
    if os.path.exists(LMS_BOOK_REQUESTS):
        save_book_requests()


def display_logs():
    count = 0
    is_valid = False
    is_valid2 = False

    while not is_valid:
        if count < 3:
            cls()
            display_directory_content()
            print("\n\n!DO NOT INCLUDE THE .txt EXTENSION!")
            user_str = input("\n\nENTER DATE (YYYY-MM-DD): ")
            fp = os.path.join(LMS_LOGS, user_str + ".txt")

            if os.path.exists(fp):
                with open(fp, 'r') as f2p:
                    print("\n| %-11s | %-11s | %-50s | %-10s | %-10s |" % ("DATE", "TIME", "NAME", "STATUS", "ITEM"))
                    for line in f2p:
                        tokens = line.strip().split("\t")
                        print("| %-11s | %-11s | %-50s | %-10s | %-10s |" % (tokens[0], tokens[1], tokens[2], tokens[3],
                                                                             tokens[4]))

                while not is_valid2:
                    print("\n\nDO YOU WANT TO VIEW OTHER DATES? ")
                    print("[1] YES")
                    print("[2] NO")
                    try:
                        user_num = int(input("-> "))
                        if 1 <= user_num <= 2:
                            if user_num == 1:
                                is_valid2 = True
                            else:
                                is_valid = True
                                is_valid2 = True
                        else:
                            print("INVALID INPUT")
                            print("PLEASE TRY AGAIN.")
                            pause()
                            cls()
                    except ValueError as e:
                        print("\nERROR:", e)
                        pause()
                        cls()
                is_valid2 = False
                pause()
            else:
                print("ERROR.")
                print("FILE (", user_str + ".txt ) NOT FOUND.")
                print("PLEASE TRY AGAIN.")
                pause()
                cls()
                count += 1
        else:
            print("ERROR.")
            print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
            print("PLEASE TRY AGAIN LATER")
            pause()
            cls()
            is_valid = True
    cls()


def display_directory_content():
    # directory = os.path.join(LMS_LOGS)

    # Get the contents of the directory
    files = os.listdir(LMS_LOGS)

    # Display the contents of the directory
    if files:
        for file in files:
            print(file)
    print("\n\n")


# ----------------------[UTILITY]----------------------
def insert_card():
    # Check if card is inserted or not
    while not os.path.exists(LMS_CHECK_FD):
        try:
            with open(LMS_CHECK_FD, 'w'):
                pass
        except IOError as e:
            print(f"ERROR: {e}")
        loading()
        cls()

    # Create directory for the user details
    os.makedirs(LMS_FLASH_DRIVE, exist_ok=True)
    front()

    if os.path.exists(LMS_FD_USER_DETAILS):
        retrieve_key()
        retrieve_books()
        retrieve_accounts()
        retrieve_account_fd()
        scan_screen(1)
        return 4
    else:
        retrieve_key()
        retrieve_books()
        retrieve_accounts()
        retrieve_account_fd()
        scan_screen(2)
        return prompts(10)


def retrieve_key():
    global KEY
    global KEY_EXIST
    if os.path.exists(LMS_KEY):
        try:
            with open(LMS_KEY, 'r') as readKey:
                KEY = readKey.readline().rstrip()
                KEY = KEY.encode()
                KEY_EXIST = True
        except IOError as e:
            print("ERROR:", e)
    else:
        retrieve_books()
        KEY_EXIST = True
        # Get temporary key if there is no key yet
        # If the user exit the program the data will still be encrypted
        get_key()

        # Check files if existed
        # If existing, save the database on the key
        if os.path.exists(LMS_ACCOUNTS):
            save_accounts()
        if os.path.exists(LMS_FD_USER_DETAILS):
            save_accounts_fd()
        if os.path.exists(LMS_BOOKS):
            save_books()
        if os.path.exists(LMS_BOOK_REQUESTS):
            save_book_requests()


def retrieve_accounts():
    # Retrieve accounts from the database file
    if os.path.exists(LMS_ACCOUNTS):
        with open(LMS_ACCOUNTS, 'r') as f2p:
            for line in f2p:
                tokens = line.strip().split(",/,")

                if not KEY_EXIST:
                    # Scan the plain text in the file because there is no key yet
                    student_id = tokens[0]
                    librarian_id = tokens[1]
                    student_name = tokens[2]
                    librarian_name = tokens[3]
                    s_key = int(tokens[4])
                    l_key = int(tokens[5])
                    violation = int(tokens[6])
                else:
                    # Decrypting
                    student_id = decrypt(tokens[0])
                    librarian_id = decrypt(tokens[1])
                    student_name = decrypt(tokens[2])
                    librarian_name = decrypt(tokens[3])
                    s_key = int(decrypt(tokens[4]))
                    l_key = int(decrypt(tokens[5]))
                    violation = int(decrypt(tokens[6]))

                # Create an AccountDetails object
                account = AccountDetails(student_id, librarian_id, student_name, librarian_name,
                                         s_key, l_key, violation)
                # Add the account to the list
                account_list.append(account)


def retrieve_account_fd():
    global CURRENT_S_KEY
    global CURRENT_L_KEY
    global CURRENT_VIOLATION
    global CURRENT_STUDENT_ID
    global CURRENT_STUDENT_NAME
    global CURRENT_LIBRARIAN_ID
    global CURRENT_LIBRARIAN_NAME

    # Retrieve account details from flash drive
    if os.path.exists(LMS_FD_USER_DETAILS):
        with open(LMS_FD_USER_DETAILS, 'r') as f2p:
            for line in f2p:
                tokens = line.strip().split(",/,")

                if not KEY_EXIST:
                    CURRENT_STUDENT_ID = tokens[0]
                    CURRENT_LIBRARIAN_ID = tokens[1]
                    CURRENT_STUDENT_NAME = tokens[2]
                    CURRENT_LIBRARIAN_NAME = tokens[3]
                    CURRENT_S_KEY = int(tokens[4])
                    CURRENT_L_KEY = int(tokens[5])
                    CURRENT_VIOLATION = int(tokens[6])
                else:
                    # Decrypting
                    CURRENT_STUDENT_ID = decrypt(tokens[0])
                    CURRENT_LIBRARIAN_ID = decrypt(tokens[1])
                    CURRENT_STUDENT_NAME = decrypt(tokens[2])
                    CURRENT_LIBRARIAN_NAME = decrypt(tokens[3])
                    CURRENT_S_KEY = int(decrypt(tokens[4]))
                    CURRENT_L_KEY = int(decrypt(tokens[5]))
                    CURRENT_VIOLATION = int(decrypt(tokens[6]))


def retrieve_books():
    # Retrieve books from Database
    if not os.path.exists(LMS_BOOKS):
        if CURRENT_S_KEY == 1 and CURRENT_L_KEY == 0:
            print("LIBRARY IS CURRENTLY EMPTY")
            print("NO BOOKS TO BE FOUND :(")
            print("PLEASE COME BACK LATER. SORRY FOR INCONVENIENCE.")
            pause()
            # logs("OUT", Vars.FILL)
            # exit(0)
        elif CURRENT_S_KEY == 0 and CURRENT_L_KEY == 1:
            print("LIBRARY IS CURRENTLY EMPTY")
            print("NO BOOKS TO BE FOUND :(")
            print("PLEASE ADD BOOKS.")
            pause()
        else:
            print("LMS - SYSTEM ERROR.")
            pause()
    else:
        with open(LMS_BOOKS, 'r') as f2p:
            for line in f2p:
                tokens = line.strip().split(",/,")

                if not KEY_EXIST:
                    book_num = int(tokens[0])
                    isbn = tokens[1]
                    book_title = tokens[2]
                    book_author = tokens[3]
                    publication_year = int(tokens[4])
                    book_quantity = int(tokens[5])

                    # Add the decrypted value to the list
                    book = BookDetails(book_num, isbn, book_title, book_author,
                                       publication_year, book_quantity)
                    book_list.append(book)
                else:
                    # Decrypting
                    book_num = int(decrypt(tokens[0]))
                    isbn = decrypt(tokens[1])
                    book_title = decrypt(tokens[2])
                    book_author = decrypt(tokens[3])
                    publication_year = int(decrypt(tokens[4]))
                    book_quantity = int(decrypt(tokens[5]))

                    # Add the decrypted value to the list
                    book = BookDetails(book_num, isbn, book_title, book_author,
                                       publication_year, book_quantity)
                    book_list.append(book)


def save_accounts():
    if not os.path.exists(LMS_ACCOUNTS):
        try:
            open(LMS_ACCOUNTS, 'w').close()
        except IOError as e:
            print(f"ERROR: {e}")
            pause()
            cls()

    try:
        with open(LMS_ACCOUNTS, 'w', encoding='UTF-8') as fwrite:
            for account in account_list:
                # Encrypting
                encrypted_student_id = encrypt(str(account.student_id))
                encrypted_librarian_id = encrypt(str(account.librarian_id))
                encrypted_student_name = encrypt(str(account.student_name))
                encrypted_librarian_name = encrypt(str(account.librarian_name))
                encrypted_s_key = encrypt(str(account.s_key))
                encrypted_l_key = encrypt(str(account.l_key))
                encrypted_violation = encrypt(str(account.violation))

                # Saving
                fwrite.write(
                    f"{encrypted_student_id},/,"
                    f"{encrypted_librarian_id},/,"
                    f"{encrypted_student_name},/,"
                    f"{encrypted_librarian_name},/,"
                    f"{encrypted_s_key},/,"
                    f"{encrypted_l_key},/,"
                    f"{encrypted_violation}\n"
                )
    except IOError as e:
        print(f"ERROR: {e}")
        pause()
        cls()


def save_accounts_fd():
    if not os.path.exists(LMS_FD_USER_DETAILS):
        try:
            open(LMS_FD_USER_DETAILS, 'w').close()
        except IOError as e:
            print(f"ERROR: {e}")
            pause()
            cls()

    if CURRENT_S_KEY == 1 and CURRENT_L_KEY == 0:
        try:
            with open(LMS_FD_USER_DETAILS, 'w', encoding='UTF-8') as fwrite:
                for account in account_list:
                    if CURRENT_STUDENT_ID == account.student_id:
                        # Encrypting
                        encrypted_student_id = encrypt(str(account.student_id))
                        encrypted_librarian_id = encrypt(str(account.librarian_id))
                        encrypted_student_name = encrypt(str(account.student_name))
                        encrypted_librarian_name = encrypt(str(account.librarian_name))
                        encrypted_s_key = encrypt(str(account.s_key))
                        encrypted_l_key = encrypt(str(account.l_key))
                        encrypted_violation = encrypt(str(account.violation))

                        # Saving
                        fwrite.write(
                            f"{encrypted_student_id},/,"
                            f"{encrypted_librarian_id},/,"
                            f"{encrypted_student_name},/,"
                            f"{encrypted_librarian_name},/,"
                            f"{encrypted_s_key},/,"
                            f"{encrypted_l_key},/,"
                            f"{encrypted_violation}\n"
                        )
        except IOError as e:
            print(f"ERROR: {e}")
            pause()
            cls()

    elif CURRENT_S_KEY == 0 and CURRENT_L_KEY == 1:
        try:
            with open(LMS_FD_USER_DETAILS, 'w', encoding='UTF-8') as fwrite:
                for account in account_list:
                    if CURRENT_LIBRARIAN_ID == account.librarian_id:
                        # Encrypting
                        encrypted_student_id = encrypt(str(account.student_id))
                        encrypted_librarian_id = encrypt(str(account.librarian_id))
                        encrypted_student_name = encrypt(str(account.student_name))
                        encrypted_librarian_name = encrypt(str(account.librarian_name))
                        encrypted_s_key = encrypt(str(account.s_key))
                        encrypted_l_key = encrypt(str(account.l_key))
                        encrypted_violation = encrypt(str(account.violation))

                        # Saving
                        fwrite.write(
                            f"{encrypted_student_id},/,"
                            f"{encrypted_librarian_id},/,"
                            f"{encrypted_student_name},/,"
                            f"{encrypted_librarian_name},/,"
                            f"{encrypted_s_key},/,"
                            f"{encrypted_l_key},/,"
                            f"{encrypted_violation}\n"
                        )
        except IOError as e:
            print(f"ERROR: {e}")
            pause()
            cls()

    else:
        print("ERROR.")
        print("UNABLE TO SAVE IN FILE")
        pause()
        cls()


def save_books():
    if not os.path.exists(LMS_BOOKS):
        try:
            open(LMS_BOOKS, 'w').close()
        except IOError as e:
            print(f"ERROR: {e}")
            pause()
            cls()

    try:
        with open(LMS_BOOKS, 'w', encoding='UTF-8') as fwrite:
            for book in book_list:
                # Encrypting
                encrypted_book_num = encrypt(str(book.book_num))
                encrypted_isbn = encrypt(str(book.isbn))
                encrypted_book_title = encrypt(str(book.book_title))
                encrypted_book_author = encrypt(str(book.book_author))
                encrypted_publication_year = encrypt(str(book.publication_year))
                encrypted_book_quantity = encrypt(str(book.book_quantity))

                # Saving
                fwrite.write(
                    f"{encrypted_book_num},/,"
                    f"{encrypted_isbn},/,"
                    f"{encrypted_book_title},/,"
                    f"{encrypted_book_author},/,"
                    f"{encrypted_publication_year},/,"
                    f"{encrypted_book_quantity}\n"
                )
    except IOError as e:
        print(f"ERROR: {e}")
        pause()
        cls()


def save_book_requests():
    if not os.path.exists(LMS_BOOK_REQUESTS):
        try:
            open(LMS_BOOK_REQUESTS, 'w').close()
        except IOError as e:
            print(f"ERROR: {e}")
            pause()
            cls()

    try:
        with open(LMS_BOOK_REQUESTS, 'w', encoding='UTF-8') as fwrite:
            for book in book_request_list:
                # Encrypting
                encrypted_book_num = encrypt(str(book.book_num))
                encrypted_isbn = encrypt(str(book.isbn))
                encrypted_book_title = encrypt(str(book.book_title))
                encrypted_book_author = encrypt(str(book.book_author))
                encrypted_publication_year = encrypt(str(book.publication_year))
                encrypted_book_quantity = encrypt(str(book.book_quantity))

                # Saving
                fwrite.write(
                    f"{encrypted_book_num},/,"
                    f"{encrypted_isbn},/,"
                    f"{encrypted_book_title},/,"
                    f"{encrypted_book_author},/,"
                    f"{encrypted_publication_year},/,"
                    f"{encrypted_book_quantity}"
                )
                fwrite.write('\n')
    except IOError as e:
        print(f"ERROR: {e}")
        pause()
        cls()


def encrypt(plain_text):
    global KEY
    plain_text = plain_text.encode()
    encrypted = bytearray()
    for i in range(len(plain_text)):
        encrypted.append(plain_text[i] ^ KEY[i % len(KEY)])
    return encrypted.hex()


def decrypt(encrypted_text):
    global KEY
    decrypted = bytearray.fromhex(encrypted_text)
    plain_text = bytearray()
    for i in range(len(decrypted)):
        plain_text.append(decrypted[i] ^ KEY[i % len(KEY)])
    return plain_text.decode()


def menu(x):
    user_num = 0
    is_valid = False
    cls()

    while not is_valid:
        print("\n\n\nMENU\n")

        if x == 1:  # student
            print("\n\n\t\t\t\t\t\t\tSTUDENT LIBRARY  MENU")
            print("\n\t\tCHOOSE YOUR CATEGORY: ")
            print("\t\t==========================================================================================")
            print("\n\t\t    [1] DISPLAY BOOKS \t\t[2] BORROW BOOKS \t\t[3] RETURN BOOKS")
            print("\n\n\t\t    [4] REQUEST BOOKS \t\t[5] VIEW VIOLATIONS \t\t[6] SAVE AND EXIT")
            print("\n\n\t\t==========================================================================================")
            print("\n\t\t-> ")

            try:
                user_num = int(input())
                # input()  # Consume the newline character
                if 1 <= user_num <= 6:
                    is_valid = True
                else:
                    print("INVALID INPUT.")
                    print("PLEASE TRY AGAIN")
                    pause()
                    cls()
            except ValueError as e:
                print("ERROR:", e)
                pause()
                cls()
        else:  # librarian
            print("\t\t==========================================================================================")
            print("\n\t\t    [1] ADD BOOKS \t\t[2] EDIT BOOKS \t\t[3] REMOVE BOOKS")
            print("\n\n\t\t    [4] BOOK REQUESTS \t\t[5] CHANGE KEY \t\t[6] DISPLAY BOOKS")
            print("\n\n\t\t    [7] DISPLAY LOGS \t\t[8] SAVE & EXIT \t\t")
            print("\n\n\t\t==========================================================================================")
            print("\n\t\t-> ")

            try:
                user_num = int(input())
                # input()  # Consume the newline character
                if 1 <= user_num <= 8:
                    is_valid = True
                else:
                    print("INVALID INPUT.")
                    print("PLEASE TRY AGAIN")
                    pause()
                    cls()
            except ValueError as e:
                print("\nERROR:", e)
                pause()
                cls()

    return user_num


def prompts(x):
    user_num = 0
    is_valid = False

    options = {
        1: "BORROW_BOOKS",
        2: "ADD_BOOKS",
        3: "REMOVE_BOOKS",
        4: "INSERT_NEW_BOOK_ISBN",
        5: "INSERT_NEW_BOOK_TRY_AGAIN",
        6: "EDIT_BOOKS",
        7: "BOOK_REQUEST_OPTIONS",
        8: "VIEW_VIOLATION",
        9: "CHANGE_KEY",
        10: "INSERT_CARD"
    }

    choice = options.get(x, "")

    if choice == "BORROW_BOOKS":
        print("\n\nINPUT BOOK NUMBER: ")
        user_num = int(input())
    elif choice == "ADD_BOOKS":
        while not is_valid:
            print("\n\nINSERT EXISTING BOOK?")
            print("[1] YES")
            print("[2] NO")
            print("[3] CANCEL")
            print("-> ")
            try:
                user_num = int(input())
                if 0 < user_num <= 3:
                    return user_num
                else:
                    print("INVALID INPUT.")
                    print("PLEASE TRY AGAIN")
                    pause()
            except ValueError as e:
                print("\nERROR: " + str(e))
                pause()
    elif choice == "REMOVE_BOOKS":
        while not is_valid:
            print("\n\nREMOVE BOOK")
            print("[1] REMOVE 'X' NUMBER OF COPY")
            print("[2] REMOVE ALL BOOK COPIES")
            print("[3] CANCEL")
            print("-> ")
            try:
                user_num = int(input())
                if 0 < user_num <= 3:
                    return user_num
                else:
                    print("INVALID INPUT.")
                    print("PLEASE TRY AGAIN")
                    pause()
            except ValueError as e:
                print("\nERROR: " + str(e))
                pause()
    elif choice == "INSERT_NEW_BOOK_ISBN":
        while not is_valid:
            print("DO YOU KNOW THE BOOKS' ISBN? ")
            print("[1] YES")
            print("[2] NO")
            print("[3] CANCEL")
            print("-> ")
            try:
                user_num = int(input())
                if 0 < user_num <= 3:
                    return user_num
                else:
                    print("INVALID INPUT.")
                    print("PLEASE TRY AGAIN")
                    pause()
            except ValueError as e:
                print("\nERROR: " + str(e))
                pause()
    elif choice == "INSERT_NEW_BOOK_TRY_AGAIN":
        while not is_valid:
            print("BOOK ALREADY EXISTS.")
            print("DO YOU WANT TO TRY AGAIN?")
            print("[1] YES")
            print("[2] NO")
            print("-> ")

            try:
                user_num = int(input())
                if 0 < user_num <= 2:
                    return user_num
                else:
                    print("INVALID INPUT.")
                    print("PLEASE TRY AGAIN")
                    pause()
            except ValueError as e:
                print("\nERROR: " + str(e))
                pause()
    elif choice == "EDIT_BOOKS":
        while not is_valid:
            print("CHANGE BOOK DETAILS")
            print("[1] BOOK NUMBER")
            print("[2] BOOK TITLE")
            print("[3] BOOK AUTHOR")
            print("[4] BOOK PUBLICATION YEAR")
            print("[5] BOOK QUANTITY")
            print("[6] SAVE & EXIT")
            print("-> ")
            try:
                user_num = int(input())
                if 0 < user_num <= 6:
                    return user_num
                else:
                    print("INVALID INPUT.")
                    print("PLEASE TRY AGAIN")
                    pause()
            except ValueError as e:
                print("\nERROR: " + str(e))
                pause()
    elif choice == "BOOK_REQUEST_OPTIONS":
        while not is_valid:
            print("OPTIONS")
            print("[1] APPROVE BOOK REQUEST")
            print("[2] DISAPPROVE BOOK REQUEST")
            print("[3] SAVE & EXIT")
            print("-> ")
            try:
                user_num = int(input())
                if 0 < user_num <= 3:
                    return user_num
                else:
                    print("INVALID INPUT.")
                    print("PLEASE TRY AGAIN")
                    pause()
            except ValueError as e:
                print("\nERROR: " + str(e))
                pause()
    elif choice == "VIEW_VIOLATION":
        while not is_valid:
            print("DO YOU WANT TO SETTLE YOUR VIOLATION?")
            print("[1] YES")
            print("[2] NO")
            print("-> ")
            try:
                user_num = int(input())
                if 0 < user_num <= 2:
                    return user_num
                else:
                    print("INVALID INPUT.")
                    print("PLEASE TRY AGAIN")
                    pause()
            except ValueError as e:
                print("\nERROR: " + str(e))
                pause()
    elif choice == "CHANGE_KEY":
        while not is_valid:
            print("SELECT METHOD TO USE")
            print("[1] GENERATE RANDOM VALID KEY")
            print("[2] ENTER OWN VALID KEY")
            print("-> ")
            try:
                user_num = int(input())
                if 0 < user_num <= 2:
                    return user_num
                else:
                    print("INVALID INPUT.")
                    print("PLEASE TRY AGAIN")
                    pause()
            except ValueError as e:
                print("\nERROR: " + str(e))
                pause()
    elif choice == "INSERT_CARD":
        while not is_valid:
            print("\n\n\t\t\t\t\t\t\tNEW USER DETECTED")
            print("\n\t\tCHOOSE YOUR CATEGORY: ")
            print("\t\t==========================================================================================")
            print("\n\t\t\t[1] STUDENT \t\t\t[2] LIBRARIAN \t\t\t[3] CANCEL")
            print("\n\n\t\t==========================================================================================")
            print("\n\t\t-> ")
            try:
                user_num = int(input())
                if 1 <= user_num <= 3:
                    return user_num
                else:
                    print("Invalid. Try again.")
            except ValueError as e:
                print("ERROR:", e)
    else:
        cls()
        print("\n\nINVALID PARAMETER.")
        pause()
        cls()

    return user_num


def display_books():
    cls()
    print(
        "============================================================================================================"
        "========================================================"
        + "===================================================")

    print("| %-8s | %-15s | %-74s | %-82s | %-9s | %-8s |" %
          ("BOOK NUM", "ISBN", "BOOK TITLE", "BOOK AUTHOR", "PUB. YEAR", "QUANTITY"))
    print(
        "============================================================================================================"
        "========================================================"
        + "===================================================")

    for book in book_list:
        print("| %-8s | %-15s | %-74s | %-82s | %-9s | %-8s |" %
              (book.book_num, book.isbn, book.book_title, book.book_author,
               book.publication_year, book.book_quantity))

    print(
        "============================================================================================================"
        "========================================================"
        + "===================================================")
    print("\n\n")


def display_current_book(x):
    print(
        "============================================================================================================"
        "========================================================"
        + "===================================================")

    print("| %-8s | %-15s | %-74s | %-82s | %-9s | %-8s |" %
          ("BOOK NUM", "ISBN", "BOOK TITLE", "BOOK AUTHOR", "PUB. YEAR", "QUANTITY"))
    print(
        "============================================================================================================"
        "========================================================"
        + "===================================================")

    for book in book_list:
        if book.book_num == x:
            print("| %-8s | %-15s | %-74s | %-82s | %-9s | %-8s |" %
                  (book.book_num, book.isbn, book.book_title, book.book_author,
                   book.publication_year, book.book_quantity))

    print(
        "============================================================================================================"
        "========================================================"
        + "===================================================")
    print("\n\n")


def display_book_requests():
    cls()
    print(
        "============================================================================================================"
        "========================================================"
        + "===================================================")

    print("| %-8s | %-15s | %-74s | %-82s | %-9s | %-8s |" %
          ("BOOK NUM", "ISBN", "BOOK TITLE", "BOOK AUTHOR", "PUB. YEAR", "QUANTITY"))
    print(
        "============================================================================================================"
        "========================================================"
        + "===================================================")

    for book in book_request_list:
        print("| %-8s | %-15s | %-74s | %-82s | %-9s | %-8s |" %
              (book.book_num, book.isbn, book.book_title, book.book_author,
               book.publication_year, book.book_quantity))

    print(
        "============================================================================================================"
        "========================================================"
        + "===================================================")
    print("\n\n")


def check_account(x, user_id):
    is_found = False
    if x == 1:
        # -----------------[STUDENT]-----------------
        for accounts in account_list:
            if accounts.student_id == user_id:
                return 1
        if not is_found:
            return 2
    else:
        # -----------------[LIBRARIAN]-----------------
        for accounts in account_list:
            if accounts.librarian_id == user_id:
                return 1
        if not is_found:
            return 2


def verify_account(x):
    print("=========================================================================================================="
          "=========================================================="
          + "===================================================")
    if x == 1:
        # -----------------[STUDENT]-----------------
        user_student_id = input("ENTER STUDENT ID: ")
        return user_student_id == CURRENT_STUDENT_ID
    else:
        # -----------------[LIBRARIAN]-----------------
        user_student_id = input("ENTER LIBRARIAN ID: ")
        return user_student_id == CURRENT_LIBRARIAN_ID


def get_book_number():
    new_book_num = 0
    is_valid = False
    while not is_valid:
        new_book_num = random.randint(1, 10 ** 6)

        for books in book_list:
            if books.book_num != new_book_num:
                is_valid = True
                break

    return new_book_num


def get_isbn(x):
    random_isbn_string = ""
    is_valid = False
    if x == 10:
        while not is_valid:
            random_isbn_int = random.randint(10 ** 9, 10 ** 9)
            random_isbn_string = str(random_isbn_int)

            if len(random_isbn_string) == x:
                if check_isbn(random_isbn_string, x):
                    is_valid = True
    elif x == 13:
        while not is_valid:
            random_isbn_int = random.randint(10 ** 12, (10 ** 13) - 1)
            random_isbn_string = str(random_isbn_int)

            if len(random_isbn_string) == x:
                if check_isbn(random_isbn_string, x):
                    is_valid = True
    else:
        print("\n\nWRONG PARAMETER.")
        print("PLEASE CHECK THE CODE.")
        pause()
        cls()

    return random_isbn_string


def check_isbn(isbn_string, x):
    summ = 0
    if x == 10:
        for i in range(9):
            c = isbn_string[i]

            if not c.isdigit():
                return False

            digit = int(c)
            summ += digit * (x - i)

        # Check if last char is a digit or 'X'
        last_char = isbn_string[9]
        if not last_char.isdigit() and last_char != 'X':
            return False

        # else if last char is 'X'
        last_digit = 10 if last_char == 'X' else int(last_char)
        summ += last_digit

        # check if ISBN is existing or not
        for book in book_list:
            if book.isbn == isbn_string:
                return False

        # return True if sum is divisible by 11
        return summ % 11 == 0

    elif x == 13:
        for i in range(12):
            c = isbn_string[i]

            if not c.isdigit():
                return False

            # multiply the digit by 1 if the index is even else
            # multiply the digit by 3 if the index is odd
            digit = int(c)
            summ += digit if i % 2 == 0 else digit * 3

        # Check if last char is a digit or 'X'
        last_char = isbn_string[12]
        if not last_char.isdigit() and last_char != 'X':
            return False

        # else if last char is 'X'
        last_digit = 10 if last_char == 'X' else int(last_char)
        summ += last_digit

        # check if ISBN is existing or not
        for book in book_list:
            if book.isbn == str:
                return False

        # return True if sum is divisible by 10
        return summ % 10 == 0

    else:
        print("\n\nWRONG PARAMETERS.")
        print("PLEASE CHECK THE CODE.")
        pause()
        cls()
        return False


def check_books(x, string_title, string_author, b_num):
    if x == 1:
        for book in book_list:
            if book.book_title == string_title and book.book_author == string_author:
                display_current_book(book.book_num)
                return False
    elif x == 2:
        for book in book_list:
            if book.book_num == b_num:
                return False
    elif x != 1 and x != 2:
        print("\n\nWRONG PARAMETERS.")
        print("PLEASE CHECK THE CODE.")
        pause()
        cls()
        return False
    else:
        return True


def get_key():
    global KEY
    generate_key = " " + string.digits + string.ascii_letters
    KEY = ''.join(random.choice(generate_key) for _ in range(10))
    KEY = KEY.encode()

    if not os.path.exists(LMS_KEY):
        try:
            with open(LMS_KEY, 'wb') as fwrite:
                fwrite.write(KEY)
        except IOError as e:
            print(f"ERROR: {e}")
            pause()
            cls()


def logs(status, item):
    curr_date = datetime.datetime.now().strftime("%Y-%m-%d")
    curr_time = datetime.datetime.now().strftime("%H:%M:%S")

    fp = os.path.join(LMS_LOGS, curr_date + ".txt")
    if CURRENT_S_KEY == 1 and CURRENT_L_KEY == 0:
        try:
            with open(fp, 'w') as fwrite:
                fwrite.write(
                    f"{curr_date}\t{curr_time}\t{CURRENT_STUDENT_NAME}\t{status}\t{item}\n"
                )
        except IOError as e:
            print(f"ERROR: {e}")
            pause()
            cls()

    elif CURRENT_S_KEY == 0 and CURRENT_L_KEY == 1:
        try:
            with open(fp, 'w') as fwrite:
                fwrite.write(
                    f"{curr_date}\t{curr_time}\t{CURRENT_STUDENT_NAME}\t{status}\t{item}\n"
                )
        except IOError as e:
            print(f"ERROR: {e}")
            pause()
            cls()


def cls():
    os.system("cls" if os.name == "nt" else "clear")


def pause():
    input("\nPRESS ENTER KEY TO CONTINUE...")


def scan_screen(x):
    if x == 1:
        print("WELCOME USER!")
    else:
        print("WELCOME TO LMS NEW USER!!")


def loading():
    animation = "|/-\\"
    for i in range(10):
        time.sleep(0.1)  # Add a small delay to control the speed of the animation
        print(f"\rLoading {animation[i % len(animation)]}", end="", flush=True)


def front():
    print("LIBRARY MANAGEMENT SYSTEM")


def exit_message():
    print("HAVE A GREAT DAY")
    print("HOPE TO SEE YOU AGAIN")
    print("PLEASE CUM AGAIN ≖‿≖")
    sys.exit()


# ----------------------[MAIN]----------------------
# Initialize empty lists
account_list = []
book_list = []
book_request_list = []

# Create directories
os.makedirs(LMS_FOLDER_DB, exist_ok=True)
os.makedirs(LMS_LOGS, exist_ok=True)

choice_main = insert_card()
if choice_main == 1:
    register_student()
    save_accounts_fd()
    save_accounts()
    logs("IN", FILL)
elif choice_main == 2:
    register_librarian()
    save_accounts_fd()
    save_accounts()
    logs("IN", FILL)
elif choice_main == 3:
    exit_message()
    sys.exit()
elif choice_main == 4:
    user_login()
else:
    print("INVALID INPUT")

'''
retrieve_books()
if not KEY_EXIST:
    # Get temporary key if there is no key yet
    # If the user exit the program the data will still be encrypted
    get_key()

    # Check files if existed
    # If existing, save the database on the key
    if os.path.exists(LMS_ACCOUNTS):
        save_accounts()
    if os.path.exists(LMS_FD_USER_DETAILS):
        save_accounts_fd()
    if os.path.exists(LMS_BOOKS):
        save_accounts_fd()
    if os.path.exists(LMS_BOOK_REQUESTS):
        save_accounts_fd()
'''

# ----------------------[STUDENT MENU]----------------------
if CURRENT_S_KEY == 1 and CURRENT_L_KEY == 0:
    while True:
        choice_student_menu = menu(1)
        if choice_student_menu == 1:
            display_books()
        elif choice_student_menu == 2:
            display_books()
            borrow_books()
        elif choice_student_menu == 3:
            return_book()
        elif choice_student_menu == 4:
            request_book()
        elif choice_student_menu == 5:
            view_violation()
        elif choice_student_menu == 6:
            exit_message()
            save_accounts()
            save_accounts_fd()
            save_books()
            logs("OUT", FILL)
        else:
            print("INVALID INPUT")
            print("PLEASE TRY AGAIN")

# ----------------------[LIBRARIAN MENU]----------------------
elif CURRENT_S_KEY == 0 and CURRENT_L_KEY == 1:
    while True:
        choice_lib_menu = menu(2)
        if choice_lib_menu == 1:
            display_books()
            choice2 = prompts(2)
            if choice2 == 1:
                insert_existing_book()
            elif choice2 == 2:
                insert_new_book()
            else:
                print("CANCELLED")
        elif choice_lib_menu == 2:
            display_books()
            edit_books()
        elif choice_lib_menu == 3:
            display_books()
            choice2 = prompts(3)
            if choice2 == 1:
                remove_book_copy()
            elif choice2 == 2:
                remove_book()
            else:
                print("CANCELLED")
        elif choice_lib_menu == 4:
            book_requests()
        elif choice_lib_menu == 5:
            change_key()
            save_accounts()
            save_accounts_fd()
            save_books()
            save_book_requests()
        elif choice_lib_menu == 6:
            display_books()
        elif choice_lib_menu == 7:
            display_logs()
        elif choice_lib_menu == 8:
            exit_message()
            save_accounts()
            save_accounts_fd()
            save_books()
            logs("OUT", FILL)
        else:
            print("INVALID INPUT")
            print("PLEASE TRY AGAIN")
