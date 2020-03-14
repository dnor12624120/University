from ConsoleInterface import ConsoleInterface
from Service import Service

def main():
    s = Service()
    ci = ConsoleInterface(s)
    ci.run()

if __name__ == "__main__":
    main()