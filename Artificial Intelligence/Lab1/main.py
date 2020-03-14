from ConsoleInterface import ConsoleInterface
from GeneratorService import GeneratorService
from Generators import NormalGenerator, BinomialGenerator, GeometricGenerator, LaplaceGenerator
              
def main():
    gs = GeneratorService({ "normal" : NormalGenerator(),
                            "bino" : BinomialGenerator(),
                            "geo" : GeometricGenerator(),
                            "laplace" : LaplaceGenerator()
                            })
    ci = ConsoleInterface(gs)
    ci.run()
    
    
if __name__ == "__main__":
    main()