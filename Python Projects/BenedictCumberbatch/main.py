import random as r
first_names = []
last_names = []
def main():
    global first_names
    global last_names
    while True:
        text = input("Press enter to see a new Benedict Cumberbatch ")
        if text == 'no':
            break
        if first_names == []:
            first_names = fill_list('/mnt/c/Users/AaronTheNerd/Documents/Personal-Coding-Projects/Python Projects/BenedictCumberbatch/first_names.txt')[:]
        if last_names == []:
            last_names = fill_list('/mnt/c/Users/AaronTheNerd/Documents/Personal-Coding-Projects/Python Projects/BenedictCumberbatch/last_names.txt')[:]
        first_name = ""
        try:
            first_name = first_names[r.randrange(len(first_names))]
        except:
            print("First names failed to load")
            break
        last_name = ""
        try:
            last_name = last_names[r.randrange(len(last_names))]
        except:
            print("Last names failed to load")
            break
        print('\n', first_name, last_name, '\n')

def fill_list(FILE_PATH):
    l = []
    try:
        file_in = open(FILE_PATH, 'r')
        for line in file_in:
            l.append(line.rstrip().title())
        file_in.close()
        return l
    except:
        print (FILE_PATH, "failed to load")
        return []

if __name__ == '__main__':
    main()