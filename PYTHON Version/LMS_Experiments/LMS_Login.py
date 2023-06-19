import LMS_Vars
import LMS_LinkedList
import LMS_Utility
import os
import sys


# ----------------------[LOGIN]----------------------
def register_student(account_list):
    count = 0
    is_valid = False

    while not is_valid:
        if count < 3:
            LMS_Utility.cls()
            print("\n\n\t\t\t\t\t\t\tAPPLICATION FORM")
            print("\n\t\tENTER YOUR INFORMATION: ")
            print("\t\t==========================================================================================")
            student_name = input("\n\t\tEnter Student Name: ")
            student_id = input("\n\t\tEnter Student ID: ")
            print("\n\n\t\t==========================================================================================")

            if LMS_Utility.check_account(1, student_id, account_list) == 2:
                s_key = 1
                l_key = 0
                librarian_id = LMS_Vars.FILL
                librarian_name = LMS_Vars.FILL
                violation = 0

                account = LMS_LinkedList.AccountDetails(student_id, librarian_id, student_name, librarian_name,
                                                        s_key, l_key, violation)
                print("REGISTRATION SUCCESSFUL")
                is_valid = True
                return account
            else:
                print("ERROR.")
                print("DUPLICATED STUDENT ID")
                print("PLEASE TRY AGAIN")
                count += 1
        else:
            print("TOO MANY UNSUCCESSFUL ATTEMPTS")
            print("PLEASE TRY AGAIN LATER")
            sys.exit(0)


def register_librarian(account_list):
    count = 0
    is_valid = False

    while not is_valid:
        if count < 3:
            LMS_Utility.cls()
            print("\n\n\t\t\t\t\t\t\tAPPLICATION FORM ADMIN\n\n")
            print("\n\t\tPLEASE ENTER THE FOLLOWING INFORMATION TO CONFIRM")
            print("\t\t==========================================================================================")
            librarian_name = input("\n\t\tEnter Librarian Name: ")
            librarian_id = input("\n\t\tEnter Librarian ID: ")
            print("\n\n\t\t==========================================================================================")

            if librarian_name == LMS_Vars.ADMIN_FILL_NAME and librarian_id == LMS_Vars.ADMIN_FILL_ID:
                s_key = 0
                l_key = 1
                student_id = LMS_Vars.FILL
                student_name = LMS_Vars.FILL
                violation = 0

                account = LMS_LinkedList.AccountDetails(student_id, librarian_id, student_name, librarian_name,
                                                        s_key, l_key, violation)

                print("REGISTRATION SUCCESSFUL")
                is_valid = True

                if LMS_Utility.check_account(2, librarian_id, account_list) == 2:
                    return account
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
                LMS_Utility.cls()
                print("\n\n\t\t\t\t\t\t\tSTUDENT LOG IN")
                print("\n\t\tENTER YOUR INFORMATION: ")
                print("\t\t==========================================================================================")
                student_id = input("\n\t\tEnter Student ID: ")

                if student_id == LMS_Vars.CURRENT_STUDENT_ID:
                    logs("IN", LMS_Vars.FILL)
                    is_valid = True
                else:
                    print("Wrong ID")
                    LMS_Utility.pause()
                    count += 1
            else:
                print("ERROR.")
                print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
                print("PLEASE TRY AGAIN LATER")
                LMS_Utility.pause()
                sys.exit(0)
    elif LMS_Vars.CURRENT_S_KEY == 0 and LMS_Vars.CURRENT_L_KEY == 1:
        count = 0
        while not is_valid:
            if count < 3:
                LMS_Utility.cls()
                print("\nLOG IN\n")
                librarian_id = input("ENTER LIBRARIAN ID: ")
                if librarian_id == LMS_Vars.ADMIN_FILL_ID:
                    logs("IN", Vars.FILL)
                    is_valid = True
                else:
                    print("\n\nERROR.")
                    print("WRONG LIBRARIAN ID")
                    print("PLEASE TRY AGAIN.")
                    LMS_Utility.pause()
                    count += 1
            else:
                print("ERROR.")
                print("TOO MANY UNSUCCESSFUL ATTEMPTS.")
                print("PLEASE TRY AGAIN LATER")
                LMS_Utility.pause()
                sys.exit(0)
    else:
        LMS_Utility.cls()
        print("SYSTEM ERROR.")
        LMS_Utility.pause()
        LMS_Utility.cls()