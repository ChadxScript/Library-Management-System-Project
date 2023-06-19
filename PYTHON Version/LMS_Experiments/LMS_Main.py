# From User import
import LMS_Vars
import LMS_LinkedList
import LMS_Utility
import LMS_Login

# From System import
import os
import sys





# ----------------------[STUDENT]----------------------


# ----------------------[LIBRARIAN]----------------------


# ----------------------


# ----------------------[MAIN?]----------------------
# Initialize empty lists
account_list = []
book_list = []
book_request_list = []

# Create directories
os.makedirs(LMS_Vars.LMS_FOLDER_DB, exist_ok=True)
os.makedirs(LMS_Vars.LMS_LOGS, exist_ok=True)

LMS_Vars.KEY = LMS_Utility.retrieve_key()
if LMS_Vars.KEY is not None:
    LMS_Vars.KEY_EXIST = True
else:
    LMS_Vars.KEY_EXIST = False

account_list.extend(LMS_Utility.retrieve_accounts(LMS_Vars.KEY_EXIST, LMS_Vars.KEY))


choice = LMS_Utility.insert_card()
if choice == 1:
    account_list.append(LMS_Login.register_student(account_list))
    LMS_Utility.save_accounts(account_list, LMS_Vars.KEY)
    save_accounts_fd()
    logs("IN", LMS_Vars.FILL)

    LMS_Vars.CURRENT_STUDENT_ID, LMS_Vars.CURRENT_LIBRARIAN_ID,
    LMS_Vars.CURRENT_STUDENT_NAME, LMS_Vars.CURRENT_LIBRARIAN_NAME,
    LMS_Vars.CURRENT_S_KEY, LMS_Vars.CURRENT_L_KEY,
    LMS_Vars.CURRENT_VIOLATION = LMS_Utility.retrieve_account_fd(LMS_Vars.KEY_EXIST, LMS_Vars.KEY)
elif choice == 2:
    account_list.append(LMS_Login.register_librarian(account_list))
    save_accounts()
    save_accounts_fd()
    logs("IN", LMS_Vars.FILL)

    LMS_Vars.CURRENT_STUDENT_ID, LMS_Vars.CURRENT_LIBRARIAN_ID,
    LMS_Vars.CURRENT_STUDENT_NAME, LMS_Vars.CURRENT_LIBRARIAN_NAME,
    LMS_Vars.CURRENT_S_KEY, LMS_Vars.CURRENT_L_KEY,
    LMS_Vars.CURRENT_VIOLATION = LMS_Utility.retrieve_account_fd(LMS_Vars.KEY_EXIST, LMS_Vars.KEY)
elif choice == 3:
    exit_message()
    sys.exit(0)
elif choice == 4:
    LMS_Vars.CURRENT_STUDENT_ID, LMS_Vars.CURRENT_LIBRARIAN_ID,
    LMS_Vars.CURRENT_STUDENT_NAME, LMS_Vars.CURRENT_LIBRARIAN_NAME,
    LMS_Vars.CURRENT_S_KEY, LMS_Vars.CURRENT_L_KEY,
    LMS_Vars.CURRENT_VIOLATION = LMS_Utility.retrieve_account_fd(LMS_Vars.KEY_EXIST, LMS_Vars.KEY)
    user_login()
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
