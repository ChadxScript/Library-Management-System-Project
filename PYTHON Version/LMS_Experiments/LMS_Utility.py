# LMS files imports
import LMS_Vars
import LMS_LinkedList
import LMS_Utility

# System imports
import random
import os
import datetime


def insert_card():
    # Check if card is inserted or not
    while not os.path.exists(LMS_Vars.LMS_CHECK_FD):
        try:
            with open(LMS_Vars.LMS_CHECK_FD, 'w'):
                pass
        except IOError as e:
            print(f"ERROR: {e}")
        # loading()
        LMS_Utility.cls()

    # Create directory for the user details
    os.makedirs(LMS_Vars.LMS_FLASH_DRIVE, exist_ok=True)
    # front()

    if os.path.exists(LMS_Vars.LMS_FD_USER_DETAILS):
        # retrieve_key()
        # retrieve_accounts()
        LMS_Utility.scan_screen(1)
        return 4
    else:
        # retrieve_key()
        # retrieve_accounts()
        LMS_Utility.scan_screen(2)
        user_choice = LMS_Utility.prompts(10)
        return user_choice


def retrieve_key():
    if os.path.exists(LMS_Vars.LMS_KEY):
        try:
            with open(LMS_Vars.LMS_KEY, 'r') as readKey:
                # str_key = readKey.readline().strip()
                # LMS_Vars.KEY = int(str_key)
                key = readKey.readline().rstrip()
                return key
        except IOError as e:
            print("ERROR:", e)
    else:
        return None


def retrieve_accounts(key_exist, key):
    accounts_list = []  # Initialize an empty list to store the accounts

    # Retrieve accounts from the database file
    if os.path.exists(LMS_Vars.LMS_ACCOUNTS):
        with open(LMS_Vars.LMS_ACCOUNTS, 'r') as f2p:
            for line in f2p:
                tokens = line.strip().split(",/,")

                if not key_exist:
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
                    student_id = decrypt(tokens[0], key)
                    librarian_id = decrypt(tokens[1], key)
                    student_name = decrypt(tokens[2], key)
                    librarian_name = decrypt(tokens[3], key)
                    s_key = decrypt(int(tokens[4]), key)
                    l_key = decrypt(int(tokens[5]), key)
                    violation = decrypt(int(tokens[6]), key)

                # Create an AccountDetails object
                account = LMS_LinkedList.AccountDetails(student_id, librarian_id, student_name, librarian_name,
                                                        s_key, l_key, violation)
                # Add the account to the list
                accounts_list.append(account)

    # Return the list of accounts
    return accounts_list



def retrieve_account_fd(key_exist, key):
    # Retrieve account details from flash drive
    if os.path.exists(LMS_Vars.LMS_FD_USER_DETAILS):
        with open(LMS_Vars.LMS_FD_USER_DETAILS, 'r') as f2p:
            for line in f2p:
                tokens = line.strip().split(",/,")

                if not key_exist:
                    current_student_id = tokens[0]
                    current_librarian_id = tokens[1]
                    current_student_name = tokens[2]
                    current_librarian_name = tokens[3]
                    current_s_key = int(tokens[4])
                    current_l_key = int(tokens[5])
                    current_violation = int(tokens[6])
                else:
                    # Decrypting
                    current_student_id = decrypt(tokens[0], key)
                    current_librarian_id = decrypt(tokens[1], key)
                    current_student_name = decrypt(tokens[2], key)
                    current_librarian_name = decrypt(tokens[3], key)
                    current_s_key = decrypt(int(tokens[4]), key)
                    current_l_key = decrypt(int(tokens[5]), key)
                    current_violation = decrypt(int(tokens[6]), key)
                return (
                    current_student_id,
                    current_librarian_id,
                    current_student_name,
                    current_librarian_name,
                    current_s_key,
                    current_l_key,
                    current_violation,
                )


def retrieve_books():
    # Retrieve books from Database
    if not os.path.exists(LMS_Vars.LMS_BOOKS):
        if LMS_Vars.CURRENT_S_KEY == 1 and LMS_Vars.CURRENT_L_KEY == 0:
            print("LIBRARY IS CURRENTLY EMPTY")
            print("NO BOOKS TO BE FOUND :(")
            print("PLEASE COME BACK LATER. SORRY FOR INCONVENIENCE.")
            pause()
            # logs("OUT", Vars.FILL)
            # exit(0)
        elif LMS_Vars.CURRENT_S_KEY == 0 and LMS_Vars.CURRENT_L_KEY == 1:
            print("LIBRARY IS CURRENTLY EMPTY")
            print("NO BOOKS TO BE FOUND :(")
            print("PLEASE ADD BOOKS.")
            pause()
        else:
            print("SYSTEM ERROR.")
            pause()
    else:
        with open(LMS_Vars.LMS_BOOKS, 'r') as f2p:
            for line in f2p:
                tokens = line.strip().split(",/,")

                if not Vars.KEY_EXIST:
                    book_num = int(tokens[0])
                    isbn = tokens[1]
                    book_title = tokens[2]
                    book_author = tokens[3]
                    publication_year = int(tokens[4])
                    book_quantity = int(tokens[5])

                    # Add the decrypted value to the list
                    book = LMS_LinkedList.BookDetails(book_num, isbn, book_title, book_author,
                                                      publication_year, book_quantity)
                    book_list.append(book)
                else:
                    # Decrypting
                    book_num = decryptInt(int(tokens[0]), KEY)
                    isbn = decryptString(tokens[1], KEY)
                    book_title = decryptString(tokens[2], KEY)
                    book_author = decryptString(tokens[3], KEY)
                    publication_year = decryptInt(int(tokens[4]), KEY)
                    book_quantity = decryptInt(int(tokens[5]), KEY)

                    # Add the decrypted value to the list
                    book = LMS_LinkedList.BookDetails(book_num, isbn, book_title, book_author,
                                                      publication_year, book_quantity)
                    book_list.append(book)


def save_accounts(account_list, key):
    if not os.path.exists(LMS_Vars.LMS_ACCOUNTS):
        try:
            open(LMS_Vars.LMS_ACCOUNTS, 'w').close()
        except IOError as e:
            print(f"ERROR: {e}")
            pause()
            cls()

    try:
        with open(LMS_Vars.LMS_ACCOUNTS, 'w', encoding='UTF-8') as fwrite:
            for account in account_list:
                # Encrypting
                encrypted_student_id = encrypt(account.student_id, key)
                encrypted_librarian_id = encrypt(account.librarian_id, key)
                encrypted_student_name = encrypt(account.student_name, key)
                encrypted_librarian_name = encrypt(account.librarian_name, key)
                encrypted_s_key = encrypt(account.s_key, key)
                encrypted_l_key = encrypt(account.l_key, key)
                encrypted_violation = encrypt(account.violation, key)

                # Saving
                fwrite.write(
                    f"{encrypted_student_id},/,"
                    f"{encrypted_librarian_id},/,"
                    f"{encrypted_student_name},/,"
                    f"{encrypted_librarian_name},/,"
                    f"{encrypted_s_key},/,"
                    f"{encrypted_l_key},/,"
                    f"{encrypted_violation}"
                )
                fwrite.write('\n')
    except IOError as e:
        print(f"ERROR: {e}")
        pause()
        cls()


def save_accounts_fd(account_list, lms_fd_user_details, current_s_key, current_l_key,
                     current_student_id, current_librarian_id):
    if not os.path.exists(lms_fd_user_details):
        try:
            open(lms_fd_user_details, 'w').close()
        except IOError as e:
            print(f"ERROR: {e}")
            pause()
            cls()

    if current_s_key == 1 and current_l_key == 0:
        try:
            with open(lms_fd_user_details, 'w', encoding='UTF-8') as fwrite:
                for account in account_list:
                    if current_student_id == account.student_id:
                        # Encrypting
                        encrypted_student_id = encryptString(account.student_id, KEY)
                        encrypted_librarian_id = encryptString(account.librarian_id, KEY)
                        encrypted_student_name = encryptString(account.student_name, KEY)
                        encrypted_librarian_name = encryptString(account.librarian_name, KEY)
                        encrypted_s_key = encryptInt(account.s_key, KEY)
                        encrypted_l_key = encryptInt(account.l_key, KEY)
                        encrypted_violation = encryptInt(account.violation, KEY)

                        # Saving
                        fwrite.write(
                            f"{encrypted_student_id},/,"
                            f"{encrypted_librarian_id},/,"
                            f"{encrypted_student_name},/,"
                            f"{encrypted_librarian_name},/,"
                            f"{encrypted_s_key},/,"
                            f"{encrypted_l_key},/,"
                            f"{encrypted_violation}"
                        )
                        fwrite.write('\n')
        except IOError as e:
            print(f"ERROR: {e}")
            pause()
            cls()

    elif current_s_key == 0 and current_l_key == 1:
        try:
            with open(lms_fd_user_details, 'w', encoding='UTF-8') as fwrite:
                for account in account_list:
                    if current_librarian_id == account.librarian_id:
                        # Encrypting
                        encrypted_student_id = encryptString(account.student_id, KEY)
                        encrypted_librarian_id = encryptString(account.librarian_id, KEY)
                        encrypted_student_name = encryptString(account.student_name, KEY)
                        encrypted_librarian_name = encryptString(account.librarian_name, KEY)
                        encrypted_s_key = encryptInt(account.s_key, KEY)
                        encrypted_l_key = encryptInt(account.l_key, KEY)
                        encrypted_violation = encryptInt(account.violation, KEY)

                        # Saving
                        fwrite.write(
                            f"{encrypted_student_id},/,"
                            f"{encrypted_librarian_id},/,"
                            f"{encrypted_student_name},/,"
                            f"{encrypted_librarian_name},/,"
                            f"{encrypted_s_key},/,"
                            f"{encrypted_l_key},/,"
                            f"{encrypted_violation}"
                        )
                        fwrite.write('\n')
        except IOError as e:
            print(f"ERROR: {e}")
            pause()
            cls()

    else:
        print("ERROR.")
        print("UNABLE TO SAVE IN FILE")
        pause()
        cls()


def save_books(book_list, lms_books):
    if not os.path.exists(lms_books):
        try:
            open(lms_books, 'w').close()
        except IOError as e:
            print(f"ERROR: {e}")
            pause()
            cls()

    try:
        with open(lms_books, 'w', encoding='UTF-8') as fwrite:
            for book in book_list:
                # Encrypting
                encrypted_book_num = encryptInt(book.book_num, KEY)
                encrypted_isbn = encryptString(book.isbn, KEY)
                encrypted_book_title = encryptString(book.book_title, KEY)
                encrypted_book_author = encryptString(book.book_author, KEY)
                encrypted_publication_year = encryptInt(book.publication_year, KEY)
                encrypted_book_quantity = encryptInt(book.book_quantity, KEY)

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


def save_book_requests(book_requests_list, lms_book_requests):
    if not os.path.exists(lms_book_requests):
        try:
            open(lms_book_requests, 'w').close()
        except IOError as e:
            print(f"ERROR: {e}")
            pause()
            cls()

    try:
        with open(lms_book_requests, 'w', encoding='UTF-8') as fwrite:
            for book in book_requests_list:
                # Encrypting
                encrypted_book_num = encryptInt(book.book_num, KEY)
                encrypted_isbn = encryptString(book.isbn, KEY)
                encrypted_book_title = encryptString(book.book_title, KEY)
                encrypted_book_author = encryptString(book.book_author, KEY)
                encrypted_publication_year = encryptInt(book.publication_year, KEY)
                encrypted_book_quantity = encryptInt(book.book_quantity, KEY)

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


def encrypt(plain_text, key):
    encrypted = bytearray()
    for i in range(len(plain_text)):
        encrypted.append(plain_text[i] ^ key[i % len(key)])
    return encrypted


def decrypt(encrypted_text, key):
    decrypted = bytearray()
    for i in range(len(encrypted_text)):
        decrypted.append(encrypted_text[i] ^ key[i % len(key)])
    return decrypted


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
                input()  # Consume the newline character
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
                input()  # Consume the newline character
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
                    # pause()
            except ValueError as e:
                print("\nERROR: " + str(e))
                # pause()
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
                    # pause()
            except ValueError as e:
                print("\nERROR: " + str(e))
                # pause()
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
                    # pause()
            except ValueError as e:
                print("\nERROR: " + str(e))
                # pause()
    elif choice == "INSERT_NEW_BOOK_TRY_AGAIN":
        while not isValid:
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
                    # pause()
            except ValueError as e:
                print("\nERROR: " + str(e))
                # pause()
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
                    # pause()
            except ValueError as e:
                print("\nERROR: " + str(e))
                # pause()
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
                    # pause()
            except ValueError as e:
                print("\nERROR: " + str(e))
                # pause()
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
                    # pause()
            except ValueError as e:
                print("\nERROR: " + str(e))
                # pause()
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
                    # pause()
            except ValueError as e:
                print("\nERROR: " + str(e))
                # pause()
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
        # pause()
        cls()

    return user_num


def display_books(book_list):
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


def display_current_book(book_list, x):
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


def display_book_requests(book_request_list):
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


def check_account(x, user_id, account_list):
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


def verify_account(x, current_user_id):
    print("=========================================================================================================="
          "=========================================================="
          + "===================================================")
    if x == 1:
        # -----------------[STUDENT]-----------------
        user_student_id = input("ENTER STUDENT ID: ")
        return user_student_id == current_user_id
    else:
        # -----------------[LIBRARIAN]-----------------
        user_student_id = input("ENTER LIBRARIAN ID: ")
        return user_student_id == current_user_id


def get_book_number(book_list):
    new_book_num = 0
    is_valid = False
    while not is_valid:
        new_book_num = random.randint(1, 10**6)

        for books in book_list:
            if books.book_num != new_book_num:
                is_valid = True
                break

    return new_book_num


def get_isbn(x, book_list):
    random_isbn_string = ""
    is_valid = False
    if x == 10:
        while not is_valid:
            random_isbn_int = random.randint(10**9, 10**9)
            random_isbn_string = str(random_isbn_int)

            if len(random_isbn_string) == x:
                if check_isbn(random_isbn_string, x, book_list):
                    is_valid = True
    elif x == 13:
        while not is_valid:
            random_isbn_int = random.randint(10**12, (10**13)-1)
            random_isbn_string = str(random_isbn_int)

            if len(random_isbn_string) == x:
                if check_isbn(random_isbn_string, x, book_list):
                    is_valid = True
    else:
        print("\n\nWRONG PARAMETER.")
        print("PLEASE CHECK THE CODE.")
        pause()
        cls()

    return random_isbn_string


def check_isbn(isbn_string, x, book_list):
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


def check_books(x, string_title, string_author, b_num, book_list):
    if x == 1:
        for book in book_list:
            if book.book_title == string_title and book.book_author == string_author:
                display_current_book(book_list, book.book_num)
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


def get_key(lms_key_path):
    while True:
        new_key = random.randint(1, 100)
        if new_key > 0:
            break

    if not os.path.exists(lms_key_path):
        try:
            with open(lms_key_path, 'w') as fwrite:
                fwrite.write(str(new_key))
        except IOError as e:
            print(f"ERROR: {e}")
            pause()
            cls()


def logs(lms_logs, current_s_key, current_l_key, current_student_name, current_librarian_name, status, item):
    curr_date = datetime.datetime.now().strftime("%Y-%m-%d")
    curr_time = datetime.datetime.now().strftime("%H:%M:%S")

    fp = os.path.join(lms_logs, curr_date + ".txt")
    if current_s_key == 1 and current_l_key == 0:
        try:
            with open(fp, 'w') as fwrite:
                fwrite.write(
                    f"{curr_date}\t{curr_time}\t{current_student_name}\t{status}\t{item}\n"
                )
        except IOError as e:
            print(f"ERROR: {e}")
            pause()
            cls()

    elif current_s_key == 0 and current_l_key == 1:
        try:
            with open(fp, 'w') as fwrite:
                fwrite.write(
                    f"{curr_date}\t{curr_time}\t{current_librarian_name}\t{status}\t{item}\n"
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
