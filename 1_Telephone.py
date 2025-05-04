size = 10
client_list = [None] * size

def add_client():
    client_id = int(input("Client ID: "))
    name = input("Client Name: ")
    telephone = input("Client Telephone Number: ")
    client_details = [client_id, name, telephone]

    index = client_id % size
    if client_list[index] is None:
        client_list[index] = client_details
        print("Client details added at index", index, ":", client_details)
    else:
        found = False
        for j in range(1, int((size - 1) / 2)):
            t = (index + j * j) % size
            if client_list[t] is None:
                client_list[t] = client_details
                print("Client details added at index", t, ":", client_details)
                found = True
                break
        if not found:
            print("Hash table is full, unable to add client.")

    print("\nClient List:", client_list)

def search_client():
    client_id = int(input("Enter Client ID to search: "))
    index = client_id % size
    cnt = 0
    for i in range(size):
        if client_list[index] is not None:
            cnt += 1
            if client_list[index][0] == client_id:
                print("Client found at index", index, ":", client_list[index])
                print("\nNumber of comparisons required to search Client ID %d: %d" % (client_id, cnt))
                break
        index = (index + 1) % size
    else:
        print("Client with ID %d not found." % client_id)
        print("\nNumber of comparisons required: %d" % cnt)

def quadratic_probing():
    print("\n----- Quadratic Probing -----")
    client_id = int(input("Enter Client ID: "))
    name = input("Enter Client Name: ")
    telephone = input("Enter Client Telephone Number: ")
    client_details = [client_id, name, telephone]

    index = client_id % size
    found = False
    for j in range(1, int((size - 1) / 2)):
        t = (index + j * j) % size
        if client_list[t] is None:
            client_list[t] = client_details
            print("Client details added at index", t, ":", client_details)
            found = True
            break
    if not found:
        print("Hash table is full, unable to add client.")

    print("\nClient List:", client_list)

def Main():
    while True:
        print("\n----- Client Management System -----")
        print("1. Add Client")
        print("2. Search Client")
        print("3. Quadratic Probing")
        print("4. Exit")

        choice = int(input("Enter your choice: "))

        if choice == 1:
            add_client()
        elif choice == 2:
            search_client()
        elif choice == 3:
            quadratic_probing()
        elif choice == 4:
            print("Exiting...")
            break
        else:
            print("Invalid choice. Please try again.")

Main()
