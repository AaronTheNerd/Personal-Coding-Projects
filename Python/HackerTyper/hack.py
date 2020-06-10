import time
def main():
    FILE_PATH = '/mnt/c/Users/AaronTheNerd/Documents/Personal-Coding-Projects/Python Projects/HackerTyper/src.txt'
    file_in = open(FILE_PATH, 'r')
    for line in file_in:
        for word in line.split(' '):
            if (word == ""):
                print('   ', end=' ', flush=True)
            else:
                print(word, end=' ', flush=True)
            time.sleep(0.25)
        print()
    print("I'm in the mainframe")

if __name__ == '__main__':
    main()