# From User import
import LMS_Vars
import LMS_LinkedList
import LMS_Utility

# From System import
import os


# ----------------------[LOGIN]----------------------
def insert_card():
    # Check if card is inserted or not
    while not os.path.exists(LMS_Vars.LMS_CHECK_FD):
        try:
            with open(LMS_Vars.LMS_CHECK_FD, 'w'):
                pass
        except IOError as e:
            print(f"ERROR: {e}")
        # loading()
        # cls()

    # Create directory for the user details
    os.makedirs(LMS_Vars.LMS_FLASH_DRIVE, exist_ok=True)
    # front()

    if os.path.exists(LMS_Vars.LMS_FD_USER_DETAILS):
        retrieve_key()
        retrieve_accounts()
        LMS_Utility.scan_screen(1)
        return 4
    else:
        retrieve_key()
        retrieve_accounts()
        LMS_Utility.scan_screen(2)
        user_choice = LMS_Utility.prompts(10)
        return user_choice


def retrieve_key():
    if os.path.exists(LMS_Vars.LMS_KEY):
        try:
            with open(fkey, 'r') as readKey:
                str_key = readKey.readline().strip()
                LMS_Vars.KEY = int(str_key)
                LMS_Vars.KEY_EXIST = True
        except IOError as e:
            print("ERROR:", e)
    else:
        LMS_Vars.KEY_EXIST = False


def retrieve_accounts():
    # retrieve accounts from database
    if not os.path.exists(LMS_Vars.LMS_ACCOUNTS):
        try:
            open(LMS_Vars.LMS_ACCOUNTS, 'w').close()
        except IOError as e:
            print(f"ERROR: {e}")
    else:
        with open(LMS_Vars.LMS_ACCOUNTS, 'r') as f2p:
            for line in f2p:
                tokens = line.strip().split(",")

                if not Vars.KEY_EXIST:
                    # Scan the plain text in the file because there is no key yet
                    student_id = tokens[0]
                    librarian_id = tokens[1]
                    student_name = tokens[2]
                    librarian_name = tokens[3]
                    s_key = int(tokens[4])
                    l_key = int(tokens[5])
                    violation = int(tokens[6])

                    # Add the decrypted value to the list
                    accounts = LMS_LinkedList.AccountDetails(student_id, librarian_id, student_name, librarian_name,
                                                             s_key, l_key, violation)
                    account_list.append(accounts)
                else:
                    # Decrypting
                    student_id = decryptString(tokens[0], KEY)
                    librarian_id = decryptString(tokens[1], KEY)
                    student_name = decryptString(tokens[2], KEY)
                    librarian_name = decryptString(tokens[3], KEY)
                    s_key = decryptInt(int(tokens[4]), KEY)
                    l_key = decryptInt(int(tokens[5]), KEY)
                    violation = decryptInt(int(tokens[6]), KEY)

                    # Add the decrypted value to the list
                    accounts = LMS_LinkedList.AccountDetails(student_id, librarian_id, student_name, librarian_name,
                                                             s_key, l_key, violation)
                    account_list.append(accounts)

    # Retrieve account details from flash drive
    if os.path.exists(LMS_Vars.LMS_FD_USER_DETAILS):
        with open(LMS_Vars.LMS_FD_USER_DETAILS, 'r') as f2p:
            for line in f2p:
                tokens = line.strip().split(",")

                if not Vars.KEY_EXIST:
                    LMS_Vars.CURRENT_STUDENT_ID = tokens[0]
                    LMS_Vars.CURRENT_LIBRARIAN_ID = tokens[1]
                    LMS_Vars.CURRENT_STUDENT_NAME = tokens[2]
                    LMS_Vars.CURRENT_LIBRARIAN_NAME = tokens[3]
                    LMS_Vars.CURRENT_S_KEY = int(tokens[4])
                    LMS_Vars.CURRENT_L_KEY = int(tokens[5])
                    LMS_Vars.CURRENT_VIOLATION = int(tokens[6])
                else:
                    # Decrypting
                    LMS_Vars.CURRENT_STUDENT_ID = decryptString(tokens[0], KEY)
                    LMS_Vars.CURRENT_LIBRARIAN_ID = decryptString(tokens[1], KEY)
                    LMS_Vars.CURRENT_STUDENT_NAME = decryptString(tokens[2], KEY)
                    LMS_Vars.CURRENT_LIBRARIAN_NAME = decryptString(tokens[3], KEY)
                    LMS_Vars.CURRENT_S_KEY = decryptInt(int(tokens[4]), KEY)
                    LMS_Vars.CURRENT_L_KEY = decryptInt(int(tokens[5]), KEY)
                    LMS_Vars.CURRENT_VIOLATION = decryptInt(int(tokens[6]), KEY)


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
                tokens = line.strip().split(",")

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


def register_student():
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

            if checkAccount(1, studentID) == 2:
                s_key = LMS_Vars.CURRENT_S_KEY = 1
                l_key = LMS_Vars.CURRENT_L_KEY = 0
                librarian_id = LMS_Vars.FILL
                librarian_name = LMS_Vars.FILL
                LMS_Vars.CURRENT_STUDENT_ID = student_id
                LMS_Vars.CURRENT_STUDENT_NAME = student_name
                violation = LMS_Vars.CURRENT_VIOLATION = 0

                account = AccountDetails(student_id, librarian_id, student_name, librarian_name,
                                         s_key, l_key, violation)
                accountList.append(account)
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

            if librarianName == LMS_Vars.ADMIN_FILL_NAME and librarianID == LMS_Vars.ADMIN_FILL_ID:
                s_key = LMS_Vars.CURRENT_S_KEY = 0
                l_key = LMS_Vars.CURRENT_L_KEY = 1
                student_id = LMS_Vars.FILL
                student_name = LMS_Vars.FILL
                LMS_Vars.CURRENT_LIBRARIAN_NAME = librarian_name
                LMS_Vars.CURRENT_LIBRARIAN_ID = librarian_id
                violation = LMS_Vars.CURRENT_VIOLATION = 0

                account = AccountDetails(student_id, librarian_id, student_name, librarian_name,
                                         s_key, l_key, violation)

                if checkAccount(2, librarianID) == 2:
                    accountList.append(account)

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

    if LMS_Vars.CURRENT_S_KEY == 1 and LMS_Vars.CURRENT_L_KEY == 0:
        count = 0
        while not is_valid:
            if count < 3:
                cls()
                print("\n\n\t\t\t\t\t\t\tSTUDENT LOG IN")
                print("\n\t\tENTER YOUR INFORMATION: ")
                print("\t\t==========================================================================================")
                student_id = input("\n\t\tEnter Student ID: ")

                if student_id == LMS_Vars.CURRENT_STUDENT_ID:
                    logs("IN", LMS_Vars.FILL)
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
    elif LMS_Vars.CURRENT_S_KEY == 0 and LMS_Vars.CURRENT_L_KEY == 1:
        count = 0
        while not is_valid:
            if count < 3:
                cls()
                print("\nLOG IN\n")
                librarian_id = input("ENTER LIBRARIAN ID: ")
                if librarian_id == LMS_Vars.ADMIN_FILL_ID:
                    logs("IN", Vars.FILL)
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


# ----------------------[LIBRARIAN]----------------------


# ----------------------


# ----------------------[MAIN?]----------------------
# Initialize empty lists
account_List = []
book_list = []
book_request_list = []

# Create directories
os.makedirs(LMS_Vars.LMS_FOLDER_DB, exist_ok=True)
os.makedirs(LMS_Vars.LMS_LOGS, exist_ok=True)

choice = insert_card()
if choice == 1:
    register_student()
    save_accounts()
    save_accounts_fd()
    logs("IN", LMS_Vars.FILL)
elif choice == 2:
    register_librarian()
    save_accounts()
    save_accounts_fd()
    logs("IN", LMS_Vars.FILL)
elif choice == 3:
    exit_message()
    sys.exit(0)
else:
    print("INVALID RETURN VALUE")

retrieve_books()
if not LMS_Vars.KEY_EXIST:
    # Get temporary key if there is no key yet
    # If the user exit the program the data will still be encrypted
    get_key()

    # Check files if existed
    # If existing, save the database on the key
    with open(LMS_Vars.LMS_ACCOUNTS):
        if os.path.exists(LMS_Vars.LMS_ACCOUNTS):
            save_accounts()
    with open(LMS_Vars.LMS_FD_USER_DETAILS):
        if os.path.exists(LMS_Vars.LMS_FD_USER_DETAILS):
            save_accounts_fd()
    with open(LMS_Vars.LMS_BOOKS):
        if os.path.exists(LMS_Vars.LMS_BOOKS):
            save_accounts_fd()
    with open(LMS_Vars.LMS_BOOK_REQUESTS):
        if os.path.exists(LMS_Vars.LMS_BOOK_REQUESTS):
            save_accounts_fd()

# Student
if LMS_Vars.CURRENT_S_KEY == 1 and LMS_Vars.CURRENT_L_KEY == 0:
    while True:
        choice = LMS_Utility.menu(1)
        if choice == 1:
            LMS_Utility.display_books(book_list)
        elif choice == 2:
            LMS_Utility.display_books(book_list)
            borrow_books()
        elif choice == 3:
            returb_book()
        elif choice == 4:
            request_book()
        elif choice == 5:
            view_violation()
        elif choice == 6:
            exit_message()
            save_accounts()
            save_accounts_fd()
            save_books()
            logs("OUT", LMS_Vars.FILL)
        else:
            print("INVALID INPUT")
            print("PLEASE TRY AGAIN")

# Librarian
elif LMS_Vars.CURRENT_S_KEY == 0 and LMS_Vars.CURRENT_L_KEY == 1:
    while True:
        choice = LMS_Utility.menu(2)
        if choice == 1:
            LMS_Utility.display_books(book_list)
            choice2 = LMS_Utility.prompts(2)
            if choice2 == 1:
                insert_existing_book()
            elif choice2 == 2:
                insert_new_book()
            else:
                print("CANCELLED")
        elif choice == 2:
            display_books(book_list)
            edit_books()
        elif choice == 3:
            LMS_Utility.display_books(book_list)
            choice2 = LMS_Utility.prompts(3)
            if choice2 == 1:
                remove_book_copy()
            elif choice2 == 2:
                remove_book()
            else:
                print("CANCELLED")
        elif choice == 4:
            book_requests()
        elif choice == 5:
            change_key()
            save_accounts()
            save_accounts_fd()
            save_books()
            save_book_requests()
        elif choice == 6:
            LMS_Utility.display_books(book_list)
        elif choice == 7:
            display_logs()
        elif choice == 8:
            exit_message()
            save_accounts()
            save_accounts_fd()
            save_books()
            logs("OUT", LMS_Vars.FILL)
        else:
            print("INVALID INPUT")
            print("PLEASE TRY AGAIN")
