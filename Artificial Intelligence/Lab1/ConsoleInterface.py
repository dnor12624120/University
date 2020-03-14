class Command():
    def __init__(self, desc, func):
        self.__desc = desc
        self.__func = func


    @property
    def desc(self):
        return self.__desc

    
    @desc.setter
    def desc(self, d):
        self.__desc = d
    
    
    @property
    def func(self):
        return self.__func
    
    
    @func.setter
    def func(self, f):
        self.__func = f
        
    
    def __str__(self):
        return self.__desc
    
    
class ConsoleInterface():
    def run(self):
        while self.__running == True:
            for c in self.__menu:
                print(c)
            user_input = input(">")
            if int(user_input) < 0 or int(user_input) > len(self.__menu):
                print("Invalid option.")
            else:
                self.__menu[int(user_input)].func()
        
        
    def initMenu(self):
        self.__menu.append(Command("0. Exit", self.exit))
        self.__menu.append(Command("1. Generate with normal distribution", self.genNormal))
        self.__menu.append(Command("2. Generate with binomial distribution", self.genBino))
        self.__menu.append(Command("3. Generate with geometric distribution", self.genGeo))
        self.__menu.append(Command("4. Generate with laplace distribution", self.genLaplace))


    def __init__(self, service):
        self.__running = True
        self.__menu = []
        self.__service = service
        self.initMenu()
        self.run()
        
        
    def exit(self):
        self.__running = False
        
        
    def genNormal(self):
        mu = float(input("Enter mu.\n"))
        sigma = float(input("Enter sigma.\n"))
        n = int(input("Enter range.\n"))
        self.__service.showNormal(mu, sigma, n)
        
        
    def genBino(self):
        N = float(input("Enter n\n"))
        P = float(input("Enter p.\n"))
        n = int(input("Enter range.\n"))
        self.__service.showBino(N, P, n)
        

    def genGeo(self):
        p = float(input("Enter p.\n")) 
        n = int(input("Enter range.\n"))
        self.__service.showGeo(p, n)
        

    def genLaplace(self):
        mu = float(input("Enter mu.\n"))
        lmbda = float(input("Enter lambda.\n"))
        n = int(input("Enter range.\n"))
        self.__service.showLaplace(mu, lmbda, n)
        
