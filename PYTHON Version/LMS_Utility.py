import random
import os


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


def scan_screen(x):
    if x == 1:
        print("WELCOME USER!")
    else:
        print("WELCOME TO LMS NEW USER!!")
