# Portfolio
This portfolio contains the projects I have been working on.

# 1st Proyect
This first project consists of a web page in which the user has to guess a specific number that is between 1 and 100.

# 2nd Proyect
The second project is about a Simplified Accounting System for Customer and Receipt Management.
This accounting system, developed in C, allows for basic customer and receipt management (invoices, credit notes, debit notes, and receipts). It includes a user authentication module with differentiated roles (administrator/user) and data persistence via plain text files.

Main entities to manage:
- Clients: Contact and tax information for the entity to which the receipts are issued.
- Receipts: Financial records associated with clients.
- Users: Credentials and roles for accessing the system.

Authentication: Login system with usernames and passwords. Allows you to differentiate roles (administrator and regular user), with only the administrator having access to user management.

Search:
  - Search for clients by CUIT (Tax ID).
  - Search for receipts by number.
  - Search for receipts by client CUIT (Tax ID).

Reports: Client list and receipt list.

File name(s) and storage path(s):
  - clients.txt: Stores customer information. Expected to be in the same directory as the executable.
  - receipts.txt: Stores receipt information. Expected to be in the same directory as the executable.
  - users.txt: Stores system user information. Expected to be in the same directory as the executable.

The project is organized into the following modules (.c/.h):
  - main.c: Contains the main function that initializes the program, loads data, manages the main menu flow, and saves data upon exit. It includes the login function and the main system menu.
  - users.h / users.c:
    - users.h: Defines the User structure and function prototypes for user management.
    - users.c: Implements functions for loading, saving, authenticating users, listing, adding, deleting, and modifying users, as well as the specific menu for user management (only accessible by administrators).
  - clients.h / clients.c:
    - clients.h: Defines the Client structure and function prototypes for client management.
    - clients.c: Implements functions for loading, saving, listing, adding, modifying, and deleting clients, searching for clients by CUIT, and a menu for client management. It also includes the hasAssociatedReceipts function to validate whether a client has receipts before deleting them.
  - receipts.h / receipts.c:
    - receipts.h: Defines the Receipt structure and function prototypes for managing receipts, including the Date structure.
    - receipts.c: Implements functions for loading, saving, listing, adding, modifying, and deleting receipts, searching by customer number or CUIT, and a menu for managing receipts. Includes validations for dates and the existence of the associated customer.
- dataTypes.h: Defines the data structures (User, Date, Client, Receipt) and constants (MAX_USERS, MAX_CLIENTS, MAX_RECEIPTS) used throughout the program.
- utils.h / utils.c:
    - utils.h: Prototypes utility functions, such as cleanBuffer().
    - utils.c: Implements auxiliary functions, such as clearing the input buffer.
